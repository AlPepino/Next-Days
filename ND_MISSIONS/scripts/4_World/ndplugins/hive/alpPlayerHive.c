

class alpPlayerHive 
{
	string alp_Guid;
	PlayerBase alp_Player;

	protected ref alpStoreValues alp_StoreValues;
	
	
	void alpPlayerHive(PlayerBase player)
	{
		alp_Player	= player;
		
		
		if (GetGame().IsServer())
		{
			alp_Guid = alp_Player.GetIdentity().GetPlainId();	
			
			JsonFileLoader<alpStoreValues>.JsonLoadFile( ALP_RP_FOLDER + alp_Guid + ".json", alp_StoreValues );
			
			if (!alp_StoreValues)
			{
				alp_StoreValues	= new alpStoreValues();
				
				OnFirstConnect();
				
				JsonFileLoader< alpStoreValues>.JsonSaveFile( ALP_RP_FOLDER + alp_Guid + ".json", alp_StoreValues );
			}
			
			JsonFileLoader< alpStoreValues>.JsonLoadFile( ALP_RP_FOLDER + alp_Guid + ".json", alp_StoreValues );			
			
			//unique PlayerID
			alp_Player.alp_PlayerID = GetPlayerID();
			alp_Player.GetIdentity().SetPlayerUniqueID( GetPlayerID() );
			OnConnect();
			
			Save();	
		}
		else
		{
			alp_StoreValues	= new alpStoreValues();
		}
	
	}
	alpStoreValues GetStore()
	{
		return alp_StoreValues;
	}
	
	void Save(bool syncAll = true)
	{
		JsonFileLoader< alpStoreValues>.JsonSaveFile( ALP_RP_FOLDER + alp_Guid + ".json", alp_StoreValues );		
		
		if ( syncAll)
		{
			SendToClientAll();	
		}
		else
		{
			SendToClientSmall();	
		}
	}
	
	
	PlayerBase GetPlayer()
	{
		return alp_Player;
	}
	
	int GetPlayerID()
	{
		return alp_StoreValues.PlayerID;
	}
	
	void SendToClientSmall()
	{
		GetScriptRPC_smallSync().Send(alp_Player, ALP_RPC_PLAYER, true, alp_Player.GetIdentity());
	}	
	
	protected ScriptRPC GetScriptRPC_smallSync()
	{
		ScriptRPC rpc = new ScriptRPC();	
		rpc.Write( ALP_RPC_PLAYER_TYPE.HIVE_SYNC_SMALL );
		WriteSmallSync( rpc );
		return rpc;
	}	
	
	void WriteSmallSync( ref ScriptRPC rpc)
	{
		rpc.Write( alp_StoreValues.PlayerID );
		rpc.Write( alp_StoreValues.Event );	
	}
	
	void SyncSmallRPC( ParamsReadContext ctx )
	{
		ctx.Read( alp_StoreValues.PlayerID );
		ctx.Read( alp_StoreValues.Event );
	}	
	
	
	void SendToClientAll()
	{
		GetScriptRPC_allSync().Send(alp_Player, ALP_RPC_PLAYER, true, alp_Player.GetIdentity());
	}
	protected ScriptRPC GetScriptRPC_allSync()
	{
		ScriptRPC rpc = new ScriptRPC();	
		rpc.Write( ALP_RPC_PLAYER_TYPE.HIVE_SYNC_ALL );
		rpc.Write( alp_StoreValues );
		return rpc;
	}	
	void SyncAllRPC( ParamsReadContext ctx )
	{
		ctx.Read( alp_StoreValues );
	}	
	
	
	void OnFirstConnect()
	{
		alp_StoreValues.Name = GetPlayer().GetIdentity().GetName();
		alp_StoreValues.GUID = GetPlayer().GetIdentity().GetPlainId();		
		alp_StoreValues.PlayerID = GetND().GetNewPlayerID();
		
		//BANK ACCOUNT
		alpBANK.SetBankAccountOnConnect( GetPlayer() , alp_StoreValues.PlayerID );	
		
		
		//GIFT
		int gift[3] = GetND().GetMS().GetOptoinsTrader().GiftToNewPlayer;
		if ( gift && gift[1] != 0 )
		{

			int balance = gift[1];
			
			if ( balance > 0 )
			{
				alpBANK.AddBalanceToAccount(alp_StoreValues.PlayerID,gift[0], balance, GetPlayer() );
			}
			else
			{
				alpBankAccount account = alpBANK.GetBankAccount(alp_StoreValues.PlayerID);		
				if ( account )
				{
					Param6<int,int,int,int,float,int> takeLoan = new Param6<int,int,int,int,float,int>(alp_StoreValues.PlayerID,gift[0],0,Math.AbsInt(balance),0.04,gift[2]);
					alpLoans loan = new alpLoans(takeLoan);
					account.AddLoan( loan );
				}
			}
		}
	}
	
	
	void OnDeath()
	{
	
		
	}

	
	void OnConnect()
	{
	
	}
	void OnDisconnect()
	{
	
	}	
}
