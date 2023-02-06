

modded class alpTraderCore extends alpTraderCoreBase
{
	static ref alpMedicalFees alp_Fees;
	
	alpMedicalFees GetFees()
	{
		return alp_Fees;
	}
	

	override bool PluginsOnRPC(int rpc, PlayerBase player, ParamsReadContext ctx )
	{
		if (! super.PluginsOnRPC(rpc,player,ctx) )
		{
			switch ( rpc )
			{//server		
				case ALP_RPC_PLUGIN_MS_TRADER.SPREAD_RUMOURS:
				{
					SpreadRumours( player, ctx );					
					return true;
				}
				case ALP_RPC_PLUGIN_MS_TRADER.ME_CURE_DISEASE:
				{
					CureDisease( player, ctx );					
					return true;
				}
				case ALP_RPC_PLUGIN_MS_TRADER.ME_DNA_SAVE:
				{
					SaveDNA( player, ctx );					
					return true;
				}
				case ALP_RPC_PLUGIN_MS_TRADER.ME_DNA_LOAD:
				{
					LoadDNA( player, ctx );					
					return true;
				}												
			}
			return false;
		}
		return true;
	}	

	
	override void SetNPCfees(int id)
	{
		alpNPCtraderStock trader = GetCurrentTrader();
		
		float currencyRate,coef;
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		int level = player.GetSyncData().GetElement( alpRPelements.REPUTATION ).GetValue();
		float sale = 	GetND().GetRP().GetReputationMdf( level );		
		
		if ( trader )
		{
			currencyRate = alpBANK.GetCurrencyRate( trader.CurrencyID );	
		
			
			if (player.GetRP().IsHero())
			{
				coef = trader.PricelistRatioHero;	
			}
			else
			{
				coef = trader.PricelistRatioBandit;	
			}
			
			alp_Fees = GetND().GetRP().GetInteractions().GetMedicalFees( currencyRate, coef, sale );
		}		
		
	}	
	void LoadDNA(PlayerBase player, ParamsReadContext ctx)
	{	

		int topay;
		
		ctx.Read(topay);		

		player.GetRP().GetCart().Refresh();
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = player.GetRP().GetCart().GetNPCid();		
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		int cash = player.GetRP().GetCart().GetCash();
		
		int cashTrader = topay;		

		if ( cash >= topay || ( isEbank && 	totalbalance >= topay )  )
		{
		
			if (isEbank)
			{
				topay += alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
				alpBANK.SaveAccount(guid);
			}
			if ( topay )
			{
				cash -= topay;
				
				if ( cash < 0 )
					cash = 0;
				
				player.GetRP().GetCart().GiveMeMoney( cash , currency);			
			}		
			//Bank profit
			alpBANK.TakeBusinessProfit(currency,  cashTrader  );		
			AddBalanceTrader( stockID, cashTrader );
			
			//Load DNA	
			player.GetPlayerHive().LoadDNA();				
		}	
		//refresh		
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player ,true);	
	
	}	
		
	void SaveDNA(PlayerBase player, ParamsReadContext ctx)
	{	

		int topay;
		
		ctx.Read(topay);			

		player.GetRP().GetCart().Refresh();
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = player.GetRP().GetCart().GetNPCid();		
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		int cash = player.GetRP().GetCart().GetCash();
		
		int cashTrader = topay;		

		if ( cash >= topay || ( isEbank && 	totalbalance >= topay )  )
		{
		
			if (isEbank)
			{
				topay += alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
				alpBANK.SaveAccount(guid);
			}
			if ( topay )
			{
				cash -= topay;
				
				if ( cash < 0 )
					cash = 0;
				
				player.GetRP().GetCart().GiveMeMoney( cash , currency);			
			}		
			//Bank profit
			alpBANK.TakeBusinessProfit(currency,  cashTrader  );		
			AddBalanceTrader( stockID, cashTrader );
			
			//save DNA	
			player.GetPlayerHive().SaveDNA();				
		}	
		//refresh		
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player ,true);	
	
	}	
	
	void CureDisease(PlayerBase player, ParamsReadContext ctx)
	{	

		int disease,topay;
		
		ctx.Read(disease);
		ctx.Read(topay);			

		player.GetRP().GetCart().Refresh();
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = player.GetRP().GetCart().GetNPCid();		
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		int cash = player.GetRP().GetCart().GetCash();
		
		int cashTrader = topay;		

		if ( cash >= topay || ( isEbank && 	totalbalance >= topay ) && player.GetRP().alp_MedicList.Get( disease ).IsInfected() )
		{
		
			if (isEbank)
			{
				topay += alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
				alpBANK.SaveAccount(guid);
			}
			if ( topay )
			{
				cash -= topay;
				
				if ( cash < 0 )
					cash = 0;
				
				player.GetRP().GetCart().GiveMeMoney( cash , currency);			
			}		
			//Bank profit
			alpBANK.TakeBusinessProfit(currency,  cashTrader  );		
			AddBalanceTrader( stockID, cashTrader );
			
			//cure	
			player.GetRP().alp_MedicList.Get( disease ).CureDisease();				
		}	
		//refresh		
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player ,true);	
	
	}
	void SpreadRumours(PlayerBase player, ParamsReadContext ctx)
	{	

		int gain,topay;
		
		ctx.Read(gain);
		ctx.Read(topay);			

		player.GetRP().GetCart().Refresh();
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = player.GetRP().GetCart().GetNPCid();		
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		int cash = player.GetRP().GetCart().GetCash();
		
		int cashTrader = topay;		

		if ( cash >= topay || ( isEbank && 	totalbalance >= topay ) )
		{
		
			if (isEbank)
			{
				topay += alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
				alpBANK.SaveAccount(guid);
			}
			if ( topay )
			{
				cash -= topay;
				
				if ( cash < 0 )
					cash = 0;
				
				player.GetRP().GetCart().GiveMeMoney( cash , currency);			
			}		
			//Bank profit
			alpBANK.TakeBusinessProfit(currency,  cashTrader  );		
			AddBalanceTrader( stockID, cashTrader );
			
			//gain reputation
			player.GetRP().ChangeReputation( gain );			
		}	
		//refresh		
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player ,true);	
	
	}	
	
	
	void CureDiseaseRPC(int disease, int pay, PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ME_CURE_DISEASE );	
		
		rpc.Write( disease );		
		rpc.Write( pay );	
		
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}		
	
	

	void SpreadRumoursRPC(int gain, int pay, PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.SPREAD_RUMOURS );	
		
		rpc.Write( gain );		
		rpc.Write( pay );	
		
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}			
	
	void SaveDNARPC( int pay, PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ME_DNA_SAVE );	
			
		rpc.Write( pay );	
		
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}		
	void LoadDNARPC( int pay, PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ME_DNA_LOAD );	
			
		rpc.Write( pay );	
		
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}	
}