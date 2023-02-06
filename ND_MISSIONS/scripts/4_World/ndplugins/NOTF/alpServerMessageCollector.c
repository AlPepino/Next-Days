
class alpServerMessageCollector
{
	//int 				TimeStamp;		//current reamining loop time
	//int					LoopCount;	
	
	int alp_Index;
	
	ref map<int, ref alpServerMessageTemplate> alp_Messages;
	
	ref map<int, ref alpServerMessageTemplate> alp_MessagesRegular;
	
	ref map<int, ref alpServerMessageTemplate> alp_MessagesOnSpawn;
	
	ref map<int, ref alpServerMessageTemplate> alp_MessagesOnConnect;

	
	void alpServerMessageCollector()
	{
		alp_Messages = new  map<int,ref alpServerMessageTemplate>;
		alp_MessagesRegular = new  map<int,ref alpServerMessageTemplate>;
		alp_MessagesOnSpawn = new  map<int,ref alpServerMessageTemplate>;
		alp_MessagesOnConnect = new  map<int,ref alpServerMessageTemplate>;
		
		alp_Index = 0;
	}
	
	void ~alpServerMessageCollector()
	{
		delete alp_Messages;
		delete alp_MessagesRegular;
		delete alp_MessagesOnSpawn;					
		delete alp_MessagesOnConnect;		
	}	
	
	alpServerMessageTemplate GetServerMessage(int id)
	{
		return alp_Messages.Get(id);			
	}
	
		
	void AddMessage(alpServerMessageTemplate message)
	{
		
		alp_Messages.Set(alp_Index, message );
		
		if ( message.Time.Get(0) == -2 )
		{//on spawn
			alp_MessagesOnSpawn.Set(alp_Index, message );
		}
		else if ( message.Time.Get(0) == -3 )
		{//on connect
			alp_MessagesOnConnect.Set(alp_Index, message );
		}
		else
		{
			alp_MessagesRegular.Set(alp_Index, message );	
		}
		
		alp_Index++;	
	} 
	
/*	
	void SendMessageToClient(int type, string message, Man player = null)
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetNotf().GetID() );			
		rpc.Write( ALP_RPC_PLUGIN_NOTF.MISSION );		
		rpc.Write( type );
		rpc.Write( message );

		if ( player)
		{
			GetND().SendGameRPC( rpc, player );	
		}				
		else
		{
			GetND().SendGameRPC( rpc, player, true,true,true );	
		}
	}
	*/
	void SendServerMessageToClient(int id, Man player = null)
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetNotf().GetID() );					
		rpc.Write( ALP_RPC_PLUGIN_NOTF.SM );
		rpc.Write( id );
		
		if ( player)
		{
			GetND().SendGameRPC( rpc, player );	
		}				
		else
		{
			GetND().SendGameRPC( rpc, player, true,true,true );	
		}
	}	
	
	void ShowServerMessage(int id, Man player = null)
	{
		if (GetGame().IsServer() )
		{
			SendServerMessageToClient(id,player);
			
			alpServerMessageTemplate message = alp_Messages.Get( id );
			
			int time;
			
			if ( message.Time.Get(0) == -2 ||  message.Time.Get(0) == -3 )
			{//on spawn on connect
				if ( message.Loop > 0 )
				{										
					message.Loop--;
					time = message.LoopTime * 1000;					
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.ShowServerMessage,time,false, id, player);	
					
				}	
				else if ( message.Loop < 0 )
				{
					time = message.LoopTime * 1000;					
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.ShowServerMessage,time,false, id, player);		
				}								
			}
			else if ( message.Time.Get(0) == -1 )
			{//loop message
				if ( message.Loop > 0 )
				{										
					message.Loop--;
					time = message.LoopTime * 1000;					
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.ShowServerMessage,time,false, id);	
					
				}	
				else if ( message.Loop < 0 )
				{
					time = message.LoopTime * 1000;					
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.ShowServerMessage,time,false, id);		
				}
			}
			else
			{
				if ( message.Loop > 0 )
				{										
					message.Loop--;
					time = message.LoopTime * 1000;					
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.ShowServerMessage,time,false, id);	
					
				}	
				else if ( message.Loop < 0 )
				{
					time = message.LoopTime * 1000;					
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.ShowServerMessage,time,false, id);		
				}
				else
				{
					time =  (24 * 60 * 60) - message.LoopTime * message.LoopTime;
				}				
			}
						
		}
		else
		{
		
		}
	}
	

	void StartRegularMessages()
	{
		//int timeStamp 			= g_Game.GetTime();
		int hourS,minuteS,secondS, timemessage, timecurrent;
		GetHourMinuteSecondUTC(hourS, minuteS, secondS);	
		
		timecurrent = hourS * 60 * 60 + minuteS * 60 + secondS;
		
		for (int i = 0; i < alp_MessagesRegular.Count(); i++)
		{
			int key = alp_MessagesRegular.GetKey( i );
			alpServerMessageTemplate message = alp_MessagesRegular.GetElement( i );
			
			if ( message.Time.Get(0) >= 0 )
			{
				timemessage = message.Time.Get(0) * 60 * 60 + message.Time.Get(1) * 60 + message.Time.Get(2);
			
				timemessage = timemessage - timecurrent;
				
				if ( timemessage < 0 )
				{
					timemessage = (24 * 60 * 60) + timemessage;	
				}
				
				timemessage *= 1000;
				
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.ShowServerMessage,timemessage,false, key);
				
			}
			else
			{
				timemessage = message.LoopTime * 1000;
				
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.ShowServerMessage,timemessage,false, key);
			}																				
		}
	}
	void StartOnConnectMessages(Man player)
	{
		StartPlayersMessages( player, alp_MessagesOnConnect);
	}	
	void StartOnSpawnMessages(Man player)
	{
		StartPlayersMessages( player, alp_MessagesOnSpawn);
	}	
	
	void StartPlayersMessages(Man player, map<int, ref alpServerMessageTemplate> messages)
	{
		//int timeStamp 			= g_Game.GetTime();
		int timemessage;
		
		for (int i = 0; i < messages.Count(); i++)
		{
			int key = messages.GetKey( i );
			alpServerMessageTemplate message = messages.GetElement( i );

			timemessage = message.LoopTime * 1000;
				
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.ShowServerMessage,timemessage,false, key, player);			
																									
		}	
	}	
}