
class alpPluginNDnotf extends alpPlugin
{
	
	ref alpOptionsNotf										alp_OptionsNotf;
	
	ref array<ref alpServerMessageTemplate>					alp_ServerMessages;

	ref alpServerMessageCollector							alp_ServerMessagesCollector;
	
	ref alpMessagesLocationLabel							alp_LocationLabels;
	ref map<int,string>										alp_CurrencyMapped;
	
	
	void ~alpPluginNDnotf()
	{
		delete alp_OptionsNotf;
		delete alp_ServerMessages;
		delete alp_ServerMessagesCollector;
		delete alp_LocationLabels;					
		delete alp_CurrencyMapped;	
				
	}	
	
	override void Init() 
	{
		//symbols
		alp_LocationLabels = new alpMessagesLocationLabel;		
		
		//load file
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() )
		{	
			//setting
			if (!FileExist(ALP_ROOTFOLDER + ALP_NOTF) )
			{ 
				alp_OptionsNotf  = new alpOptionsNotf;
				JsonFileLoader< alpOptionsNotf>.JsonSaveFile(ALP_ROOTFOLDER + ALP_NOTF,  alp_OptionsNotf);
			}
			else 
			{
				JsonFileLoader< alpOptionsNotf>.JsonLoadFile(ALP_ROOTFOLDER + ALP_NOTF, alp_OptionsNotf );	
			}
				
			JsonFileLoader< alpOptionsNotf>.JsonSaveFile(ALP_ROOTFOLDER + ALP_NOTF,  alp_OptionsNotf);				
			

			
			//check if folder exists
			if (!FileExist(ALP_NOTF_FOLDER)) MakeDirectory(ALP_NOTF_FOLDER);	
			
			//read server messages
			JsonFileLoader< array<ref alpServerMessageTemplate>>.JsonLoadFile( ALP_NOTF_SERVERMESSAGES, alp_ServerMessages );	
			
			if ( !alp_ServerMessages)
			{
				alp_ServerMessages = new array<ref alpServerMessageTemplate>;
				
				FillTemplateServerMessages(alp_ServerMessages);
				
				JsonFileLoader< array<ref alpServerMessageTemplate>>.JsonSaveFile( ALP_NOTF_SERVERMESSAGES, alp_ServerMessages );	
			}
			
			InitMessages(alp_ServerMessages);		
			
			//start regular messages	
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( alp_ServerMessagesCollector.StartRegularMessages,0);
		}	
		else
		{
			alp_OptionsNotf  = new alpOptionsNotf;	
			
			
			//map currency
			alp_CurrencyMapped = new map<int,string>;
			map<int, ref alpCurrency> currencies = alpBANK.GetCurencies().GetCurrencies();	
			if ( 	currencies )
			{
				for (int c = 0; c < currencies.Count();c++)
				{
					alpCurrency currency = currencies.GetElement(c);
					alp_CurrencyMapped.Set(c,currency.Name);
				}			
			}				
		}
		
	}
	

	void InitMessages(array<ref alpServerMessageTemplate> messages)
	{

		alp_ServerMessagesCollector = new alpServerMessageCollector();
		
		for ( int i = 0 ; i < messages.Count(); i++ )
		{
			alp_ServerMessagesCollector.AddMessage( messages.Get(i) );
		}
		
	}
	
	
	void FillTemplateServerMessages(ref array<ref alpServerMessageTemplate> messages)
	{
		alpServerMessageTemplate message = new alpServerMessageTemplate(ALPMSTYPE.SMPERSONAL,"Some important  message showing just once on connect",{-3,0,0},0,5);
		messages.Insert(message);
		
		alpServerMessageTemplate message1 = new alpServerMessageTemplate(ALPMSTYPE.SMPERSONAL,"Some important  message showing every spawning",{-2,0,0},0,5);
		messages.Insert(message1);
		
		alpServerMessageTemplate message2= new alpServerMessageTemplate(ALPMSTYPE.SMINFO,"Looping message per 1800 second",{-1,0,0},-1,1800);
		messages.Insert(message2);
		
		alpServerMessageTemplate message3= new alpServerMessageTemplate(ALPMSTYPE.SMIMPORTANT,"Important server message (restart) showing in exact time (hh:mm:ss)",{15,0,0},0,0);
		messages.Insert(message3);
	
	}
	
	
	override void OnConnectManaged( PlayerBase player )
	{	

		ScriptRPC rpc = GetND().GetInitRPC( GetID() );					
		rpc.Write( alp_OptionsNotf );
		rpc.Write( alp_ServerMessages );
			
		GetND().SendGameRPC( rpc, player );
	
		alp_ServerMessagesCollector.StartOnConnectMessages(player);
			
		

	}	
	
	override void OnSpawnManaged( PlayerBase player )
	{	
		
		alp_ServerMessagesCollector.StartOnSpawnMessages(player);
	}	
	
	override void ReadInitRPC( PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		ctx.Read( alp_OptionsNotf );		
		ctx.Read( alp_ServerMessages );		

		InitMessages( alp_ServerMessages );
	}	
	
	override void ReadSyncRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{
		int rpc,type,npcid, questID,mID;
		string text;
		vector pos;
		ctx.Read( rpc );
		ctx.Read( type );
		
		switch ( rpc )
		{
			
			case ALP_RPC_PLUGIN_NOTF.MESSAGE:
			{				
				if ( GetHud() )
				{
					ctx.Read( text ); 
					GetHud().SendMessageALP(type, text, "0 0 0");	
				}
				break;
			}		
			case ALP_RPC_PLUGIN_NOTF.MESSAGE_POSITION:
			{
				if ( GetHud() )
				{
					ctx.Read( text ); 
					ctx.Read( pos );					
					GetHud().SendMessageALP(type, text, pos);	
				}
				break;
			}			
			case ALP_RPC_PLUGIN_NOTF.MESSAGE_RAID_ALERT:
			{				
				if ( GetHud() )
				{
					ctx.Read( pos );
					GetHud().SendMessageALP(type, "#pp_someone_is_trying_to_get_into_your_base", pos);	
				}
				break;
			}					
			case ALP_RPC_PLUGIN_NOTF.PERSONAL:
			{
				if ( GetHud() )
				{
					ctx.Read( text ); 
					GetHud().SendMessageALP(type, text, "0 0 0");	
				}				
				break;
			}				
			case ALP_RPC_PLUGIN_NOTF.MOSTWANTED:
			{
				if ( GetHud() )												
				{
					int playerID, fromID, curID, reward;
					ctx.Read( text ); 						
					ctx.Read( pos ); 
					ctx.Read( playerID );
					ctx.Read( fromID );
					ctx.Read( curID );
					ctx.Read( reward );
		
					string messageWanted;
					if ( reward )
					{
						messageWanted = "#alp_wanted #pos (" + text + " - #alp_atm_reward: " + alpUF.NumberToString(reward,1) + " " + alp_CurrencyMapped.GetElement( curID) + ")";
					}
					else
					{
						messageWanted = "#alp_wanted #pos (" + text + ")";
					}
					
					//add to most wanted array
					AddToMostWanted( fromID,curID,reward, playerID, text, messageWanted, pos );				
					
					GetHud().SendMessageALP(type, messageWanted, pos);	
				}				
				break;
			}			
			case ALP_RPC_PLUGIN_NOTF.MISSION:
			{				
				if ( GetHud() )
				{	
					ctx.Read( mID );			
					ctx.Read( text ); 
					ctx.Read( pos ); 
					alpMission mission;
					if ( mID >= 0 ) {
						mission = GetND().GetMS().GetMission( mID );	
					} 
						
					if ( mID < 0 || ( mission && GetND().IsMissionKnown( mID, mission.alp_MissionStarted , mission.GetTemplate().requiredLevel ) ) ){
						GetHud().SendMessageALP(type, text, pos);
					}	
				}				
				break;
			}					
			case ALP_RPC_PLUGIN_NOTF.SM:
			{
				if ( GetHud() && alp_ServerMessagesCollector)
				{
					alpServerMessageTemplate message = alp_ServerMessagesCollector.GetServerMessage( type );
					type = message.Type;
					text = message.Message;					
					
					GetHud().SendMessageALP(type, text);		
				}						
				break;
			}			
			case ALP_RPC_PLUGIN_NOTF.QUEST_START:
			{	
				if ( GetHud() )
				{
					ctx.Read( npcid );
					ctx.Read( questID );  	
					ShowQuestMessage( type, 1 , npcid, questID );							
				}	
				break;					
			}	
			case ALP_RPC_PLUGIN_NOTF.QUEST_END:
			{	
				if ( GetHud() )
				{
					ctx.Read( npcid );					
					ctx.Read( questID);  
					ShowQuestMessage( type, 2 , npcid, questID );						
				}					
				break;
			}					
		}
				
	}		
	
	
	void ShowQuestMessage( int type, int message_type,  int npcid, int qid )
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		int level;
		if ( player && player.GetIdentity() ){
			level = player.GetIdentity().GetPlayerLevel();
		}	
				
		alpTraderQuest quest = GetND().GetQuest(  qid );
		
		if ( quest && quest.RequiredLevel <= level )
		{

			vector pos = GetND().GetActiveQuestPosition( npcid );	
			string message;
			if ( message_type == 1 )
			{
				message = quest.StartMessage;
			}
			else
			{
				message = quest.EndMessage;
			}
			
			string itemName = GetDisplayName( quest.WantedItem ); ;

			int itemCount = quest.WantedRequiredCount;
			
			if ( itemCount > 0 )
			{
				itemName = itemName + " (" + itemCount  +  "x)";
			}
			
			string rewardName = quest.RewardItem;
			
			if ( rewardName != STRING_EMPTY && quest.RewardGivenCount )
			{
				rewardName = GetDisplayName( rewardName ); ;
				int rewardCount = quest.RewardGivenCount;
				rewardName = rewardName + " (" + rewardCount  +  "x); ";	

			}
			if ( quest.RewardPrice )
			{
				//alpTraderItemConfig config = alpTraderCoreBase.GetTraderItemConfig( quest.WantedItem );		
				int currency = GetND().GetActiveQuestCurrency( npcid );	 
				EntityAI ent = EntityAI.Cast( GetGame().CreateObject( quest.WantedItem, "0 0 0", true, false, false ) );
				int price;				
				if ( ent )
				{
					if ( ent.IsTransport() )
					{
						CarScript car = CarScript.Cast( ent );
						
						price = car.GetDefaultPrice();
					}
					else
					{
						ItemBase itm = ItemBase.Cast( ent );
						price = itm.GetDefaultPrice();
					}
					
					GetGame().ObjectDelete( ent );
				}
				price = (int) ( price * quest.RewardPrice * quest.WantedRequiredCount * alpBANK.GetCurrencyRate( currency ) );
				
				rewardName = rewardName + "#trader_cart_money " + alpUF.NumberToString( price,1) + " " + alp_CurrencyMapped.GetElement( currency ) + "; "; 
			}	
			if ( quest.RewardReputation )
			{
				rewardName = rewardName + " " + quest.RewardReputation + " EXP";
			}	
			message.Replace( "#item" , itemName );
			message.Replace( "#reward" , rewardName );
			//+ 

			GetHud().SendMessageALP( type , message , pos);	

		}

	}
	
	string GetDisplayName(string type )
	{
		string name,subclass_path;
		if ( GetGame().IsKindOf( type, "Inventory_Base") || GetGame().IsKindOf( type , "CarScript")  )
		{
			subclass_path = "CfgVehicles " + type + " displayName";		
			
			if ( GetGame().ConfigGetText( subclass_path , name ) )
			{
				type = name;
			}
		}
		else if ( GetGame().IsKindOf( type, "Weapon_Base") )
		{
			subclass_path = "CfgWeapons " + type + " displayName";		
			
			if ( GetGame().ConfigGetText( subclass_path , name ) )
			{
				type = name;
			}		
		}
		else if ( GetGame().IsKindOf( type, "Magazine_Base") )
		{
			subclass_path = "CfgMagazines " + type + " displayName";		
			
			if ( GetGame().ConfigGetText( subclass_path , name ) )
			{
				type = name;
			}				
		}

		return type;
	}
	
	
	void AddToMostWanted(int from, int currency, int reward, int player, string name, string title, vector position)
	{
		int timeStamp = g_Game.GetTime();
		
		vector real = position;
		
		string label = GetLocationsLabels().GetLocation2( position );
		
		title.Replace("#pos", label );
		
		alpMostWanted wanted = new alpMostWanted(from,player,currency,reward, name, title, real, position, "ND_MISSIONS\\gui\\images\\mostwanted.paa");
		
		GetND().SetMostWanted( player, wanted );
					
	}
	
	Hud GetHud()
	{
		Hud hud;
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if (player)
		{
			return player.m_Hud;
		}
		return null;
	}
	
	alpOptionsNotf GetOptions()
	{
		return alp_OptionsNotf;
	}		

	alpMessagesLocationLabel GetLocationsLabels()
	{
		return alp_LocationLabels;
	}
	
	void SendMissionMessage( int type, int mID, string text, vector pos, PlayerBase player, bool toAll = false )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		rpc.Write( ALP_RPC_PLUGIN_NOTF.MISSION );
		rpc.Write( type );	
		rpc.Write( mID );
		rpc.Write( text );	
		rpc.Write( pos );	
		
		if ( toAll )
		{
			GetND().SendGameRPC( rpc, player, true,true,true );		
		}
		else
		{
			GetND().SendGameRPC( rpc, player );		
		}
		
	}

	void SendEchoAboutWantedPerson( int type, string text, vector pos , int playerID, int from, int currency, int reward)
	{
		
		
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		rpc.Write( ALP_RPC_PLUGIN_NOTF.MOSTWANTED );		
		
		rpc.Write( type );	
		rpc.Write( text );	
		rpc.Write( pos );	
		rpc.Write( playerID );
		rpc.Write( from );
		rpc.Write( currency );
		rpc.Write( reward );
		GetND().SendGameRPC( rpc, null , true,true,true );			
		
	}	
	
	
	void SendQuestMessage(int npcid, int quest, int type = 1 )
	{
		//1 - start, 2 - end
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		
					
		if ( type == 1 )
		{
			rpc.Write( ALP_RPC_PLUGIN_NOTF.QUEST_START );	
		}
		else
		{
			rpc.Write( ALP_RPC_PLUGIN_NOTF.QUEST_END );	
		}
		type = ALPMSTYPE.MMPERSONAL;
		rpc.Write( type  );	
		rpc.Write( npcid );	
		rpc.Write( quest );	

		GetND().SendGameRPC( rpc, null , true,true,true );				
	}
	
	void SendPersonalMessage( string text, PlayerBase player )
	{
		
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		rpc.Write( ALP_RPC_PLUGIN_NOTF.PERSONAL );		
		
		rpc.Write( ALPMSTYPE.SMPERSONAL );	
		rpc.Write( text );	
		
		GetND().SendGameRPC( rpc, player );			
		
	}	
	
	void SendGlobalMessage( int type, string text )
	{
		
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		rpc.Write( ALP_RPC_PLUGIN_NOTF.MESSAGE );		
		
		rpc.Write( type );	
		rpc.Write( text );	
		
		GetND().SendGameRPC( rpc, null , true,true,true );			
		
	}	
	
	void SendMessage( PlayerBase player, int type, string text )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		rpc.Write( ALP_RPC_PLUGIN_NOTF.MESSAGE );		
		
		rpc.Write( type );	
		rpc.Write( text );	
		
		GetND().SendGameRPC( rpc, player );			
	}
	
	void SendMessageWithPosition( PlayerBase player, int type, string text, vector pos )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		rpc.Write( ALP_RPC_PLUGIN_NOTF.MESSAGE_POSITION );		
		
		rpc.Write( type );	
		rpc.Write( text );	
		rpc.Write( pos );
		GetND().SendGameRPC( rpc, player );			
	}	
	
	void SendRaidAlert( PlayerBase player, int type, vector pos )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		rpc.Write( ALP_RPC_PLUGIN_NOTF.MESSAGE_RAID_ALERT );		
		
		rpc.Write( type );	
		rpc.Write( pos );
		GetND().SendGameRPC( rpc, player );			
	}		
	
}//ALP_RPC_PLUGIN_NOTF.MISSION
