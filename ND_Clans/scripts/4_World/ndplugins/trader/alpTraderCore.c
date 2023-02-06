modded class alpTraderCore extends alpTraderCoreBase
{


	override bool PluginsOnRPC(int rpc, PlayerBase player, ParamsReadContext ctx )
	{
		if (! super.PluginsOnRPC(rpc,player,ctx) )
		{
			switch ( rpc )
			{//server		
				case ALP_RPC_PLUGIN_MS_TRADER.PP_TAXES:
				{
					PayTaxes( player, ctx );					
					return true;
				}
				case ALP_RPC_PLUGIN_MS_TRADER.ESTATE_BUY:
				{
					BuyEstate( player, ctx );					
					return true;
				}	
				case ALP_RPC_PLUGIN_MS_TRADER.ESTATE_SELL:
				{
					SellEstate( player, ctx );					
					return true;
				}				
				case ALP_RPC_PLUGIN_MS_TRADER.ESTATE_BUY_KEY:
				{
					BuyEstateKey( player, ctx );					
					return true;
				}	
				case ALP_RPC_PLUGIN_MS_TRADER.ESTATE_UPDATE_SETTINGS:
				{
					UpdateEstateSettings( player, ctx );					
					return true;
				}	
				case ALP_RPC_PLUGIN_MS_TRADER.PP_PERMISSION:
				{
					SetPermissionPP( player, ctx );					
					return true;
				}																					
			}
			return false;
		}
		return true;
	}	
	
	void SetPermissionPP(PlayerBase player, ParamsReadContext ctx)
	{	

		int settings;
		ctx.Read(settings);	
	
		//update estate 
		player.alp_PlotPoleManage.SetClanPermission( settings );
		player.alp_PlotPoleManage.SetSynchDirty();

			
		//refresh		
		player.GetSyncData().ForceSync();
		
		int stockID = player.GetRP().GetCart().GetNPCid();	
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player ,true);	
	
	}		
	
	void UpdateEstateSettings(PlayerBase player, ParamsReadContext ctx)
	{	
		Param4<int,int,int,int> values;
		ctx.Read(values);	
		
		int houseID = values.param1;
		int keyID = values.param2;		
		int settings = values.param3;	
		int topay = values.param4;
		

		player.GetRP().GetCart().Refresh();
		
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = player.GetRP().GetCart().GetNPCid();		
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		int cash = player.GetRP().GetCart().GetCash();
		
		int cashTrader = topay;		
		

		
		if ( totalbalance >= topay ) {

			if ( topay > 0 )
			{
				if ( isEbank == alpNPC_AVAILABLE_MENU.BANK_ONLY ){
					topay = alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
					alpBANK.SaveAccount(guid);				
				} else	{
					if (isEbank)
					{
						topay = alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
						alpBANK.SaveAccount(guid);
					}
					if ( topay )
					{
						cash -= topay;
						
						if ( cash < 0 )
							cash = 0;
						
						player.GetRP().GetCart().GiveMeMoney( cash , currency);			
					}					
				
				}				
		
				//Bank profit
				alpBANK.TakeBusinessProfit(currency,  cashTrader  , true);		
				AddBalanceTrader( stockID, cashTrader );			
			}

			//update estate 
			player.alp_PlotPoleManage.UpdateEstateOwnership(player, houseID, keyID, settings);

			player.alp_PlotPoleManage.SetSynchDirty();
			
		}	
		//refresh		
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player ,true);	
	
	}		
	
	void BuyEstateKey(PlayerBase player, ParamsReadContext ctx)
	{	
		Param4<int,int,int,int> values;
		ctx.Read(values);	
		
		int houseID = values.param1;
		int keyID = values.param2;		
		int doorsCount = values.param3;	
		int topay = values.param4;
		

		player.GetRP().GetCart().Refresh();
		
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = player.GetRP().GetCart().GetNPCid();		
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		int cash = player.GetRP().GetCart().GetCash();
		
		int cashTrader = topay;		
		
		if ( totalbalance >= topay ){

			if ( topay > 0 )
			{
				if ( isEbank == alpNPC_AVAILABLE_MENU.BANK_ONLY ){
					topay = alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
					alpBANK.SaveAccount(guid);				
				} else	{
					if (isEbank)
					{
						topay = alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
						alpBANK.SaveAccount(guid);
					}
					if ( topay )
					{
						cash -= topay;
						
						if ( cash < 0 )
							cash = 0;
						
						player.GetRP().GetCart().GiveMeMoney( cash , currency);			
					}					
				
				}				
		
				//Bank profit
				alpBANK.TakeBusinessProfit(currency,  cashTrader  , true);		
				AddBalanceTrader( stockID, cashTrader );	
				//buy universal key
				alp_HouseKey housekey = alp_HouseKey.Cast(player.CreateInInventory("alp_HouseKey" ) ); 
				if (!housekey)
				{
					housekey = alp_HouseKey.Cast(GetGame().CreateObject("alp_HouseKey",player.GetPosition(),false,false,true));
				}
				if (housekey)
				{
					housekey.SetHouseID( keyID );
					housekey.SetKeyID( -1 );//universal key
					housekey.SetSynchDirty();
				}			
				//buy rest keys
				for(int i = 0; i < doorsCount; i++)
				{
					alp_HouseKey doorkey = alp_HouseKey.Cast(player.CreateInInventory("alp_HouseKey" ) ); 
					if (!doorkey)
					{
						doorkey = alp_HouseKey.Cast(GetGame().CreateObject("alp_HouseKey",player.GetPosition(),false,false,true));
					}
					if (doorkey)
					{
						doorkey.SetHouseID( keyID );
						doorkey.SetKeyID( i );//universal key
						doorkey.SetSynchDirty();
					}				
				}				
			}
			
		}	
		//refresh		
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player ,true);		
	
	}		
	
	void BuyEstate(PlayerBase player, ParamsReadContext ctx)
	{	
		Param3<int,int,int> values;
		ctx.Read(values);	
		
		int houseID = values.param1;
		int keyID = values.param2;		
		int topay = values.param3;
		int validto = player.alp_PlotPoleManage.GetValidThru();

		player.GetRP().GetCart().Refresh();
		
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = player.GetRP().GetCart().GetNPCid();		
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		int cash = player.GetRP().GetCart().GetCash();
		
		int cashTrader = topay;		

		if ( totalbalance >= topay ) {

			if ( topay > 0 )
			{
				if ( isEbank == alpNPC_AVAILABLE_MENU.BANK_ONLY ){
					topay = alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
					alpBANK.SaveAccount(guid);				
				} else	{
					if (isEbank)
					{
						topay = alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
						alpBANK.SaveAccount(guid);
					}
					if ( topay )
					{
						cash -= topay;
						
						if ( cash < 0 )
							cash = 0;
						
						player.GetRP().GetCart().GiveMeMoney( cash , currency);			
					}					
				
				}				
		
				//Bank profit
				alpBANK.TakeBusinessProfit(currency,  cashTrader  , true);		
				AddBalanceTrader( stockID, cashTrader );	
				//buy estate
				if ( player.alp_PlotPoleManage.UpdateEstateOwnership(player, houseID, keyID, 1 ) )
				{
					alp_HouseKey housekey = alp_HouseKey.Cast(player.CreateInInventory("alp_HouseKey" ) ); 
					if (!housekey)
					{
						housekey = alp_HouseKey.Cast(GetGame().CreateObject("alp_HouseKey",player.GetPosition(),false,false,true));
					}
					if (housekey)
					{
						housekey.SetHouseID( keyID );
						housekey.SetKeyID( -1 );//universal key
						housekey.SetSynchDirty();
					}			
				}	
				player.alp_PlotPoleManage.SetSynchDirty();
			
			}	
		}	
		//refresh		
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player ,true);	
	
	}		
	void SellEstate(PlayerBase player, ParamsReadContext ctx)
	{	
		Param3<int,int,int> values;
		ctx.Read(values);	
		
		int houseID = values.param1;
		int keyID = values.param2;		
		int topay = values.param3;

		

		player.GetRP().GetCart().Refresh();
		
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = player.GetRP().GetCart().GetNPCid();		
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		int cash = player.GetRP().GetCart().GetCash();
		
		int cashTrader = topay;		

		//sell estate
		if ( player.alp_PlotPoleManage.SellEstateOwnership(player, houseID, keyID, 1 ) ){
			if ( isEbank == alpNPC_AVAILABLE_MENU.BANK_ONLY ){
				topay = alpBANK.AddBalanceToAccount(guid, currency, topay , player);
				alpBANK.SaveAccount(guid);				
			} else	{
				if (isEbank)
				{
					topay = alpBANK.AddBalanceToAccount(guid, currency, topay , player);
					alpBANK.SaveAccount(guid);
				}
				if ( topay )
				{
					cash += topay;
					
					if ( cash < 0 )
						cash = 0;
					
					player.GetRP().GetCart().GiveMeMoney( cash , currency);			
				}							
			}	
			//Bank profit
			alpBANK.TakeBusinessProfit(currency,  -cashTrader  , true);		
			AddBalanceTrader( stockID, -cashTrader );		
		}					
			
		//refresh		
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player ,true);
			
	}		
	void PayTaxes(PlayerBase player, ParamsReadContext ctx)
	{	

		int radius,days,topay;
		
		ctx.Read(radius);			
		ctx.Read(days);
		ctx.Read(topay);

		player.GetRP().GetCart().Refresh();
		
		int guid = player.GetPlayerHive().GetPlayerID();		
		int stockID = player.GetRP().GetCart().GetNPCid();		
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		int cash = player.GetRP().GetCart().GetCash();
		
		int cashTrader = topay;		

		if ( totalbalance >= topay ) {

			if ( topay > 0 )
			{
				if ( isEbank == alpNPC_AVAILABLE_MENU.BANK_ONLY ){
					topay = alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
					alpBANK.SaveAccount(guid);				
				} else	{
					if (isEbank)
					{
						topay = alpBANK.AddBalanceToAccount(guid, currency, -topay , player);
						alpBANK.SaveAccount(guid);
					}
					if ( topay )
					{
						cash -= topay;
						
						if ( cash < 0 )
							cash = 0;
						
						player.GetRP().GetCart().GiveMeMoney( cash , currency);			
					}					
				
				}				
		
				//Bank profit
				alpBANK.TakeBusinessProfit(currency,  cashTrader  , true);		
				AddBalanceTrader( stockID, cashTrader );	
				//tax fee PlotPole
				player.alp_PlotPoleManage.AddProtectionLifeTime(player, days, radius);				
				player.alp_PlotPoleManage.SetSynchDirty();
							
			}
			
		}	
		//refresh		
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player ,true);	
	
	}	
	void SetPermissionRPC(int setting,  PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.PP_PERMISSION );	
		
		rpc.Write( setting );		
				
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}
		
	void PayTaxesRPC(int radius, int days,int fee,  PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.PP_TAXES );	
		
		rpc.Write( radius );		
		rpc.Write( days );	
		rpc.Write( fee );
				
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}		
	void BuyEstatesRPC(Param3<int,int,int> values,  PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ESTATE_BUY );	
		
		rpc.Write( values );		
				
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}
	void SellEstatesRPC(Param3<int,int,int> values,  PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ESTATE_SELL );	
		
		rpc.Write( values );		
				
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}		
	void BuyEstatesKeyRPC(Param4<int,int,int,int> values,  PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ESTATE_BUY_KEY );	
		
		rpc.Write( values );		
				
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}		
	void UpdateEstatesSettingsRPC(Param4<int,int,int,int> values,  PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ESTATE_UPDATE_SETTINGS );	
		
		rpc.Write( values );		
				
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}			


}