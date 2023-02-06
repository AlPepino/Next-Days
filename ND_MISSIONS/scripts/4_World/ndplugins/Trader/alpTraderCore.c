enum alpNPCINTERACTION
{
	UNLOCKKEYBORD,
	ME_FEES,
	ME_CURE_ALL,
	ME_CURE_DISEASE,
	ME_DNA_SAVE,
	ME_DNA_LOAD,	
	SPREADRUMOURS,
	
}
enum alpTRADER_ACTION
{
	SYNC,
	DATA_SYNC_COMPLETED,
	DATA,
	DATA_NOPRICELIST,
	DATA_NOSTOCKLIST,
	DATA_ONLYCATEGORY,
	STOCK,
	BUYING,
	SELLING,
	BANK,
	PLOTPOLE,
	ESTATE,
	NPCPLUS,	
	NPCPLUS_RUMOURS,
	COUNT
}




class alpTraderCore extends alpTraderCoreBase
{
	//client
	bool													alp_AreTraderDataVaild = false;	
	
	bool 													m_CanMakeLogs;
	
	override void InitCore()
	{
		if (GetGame().IsServer() )
		{
			m_CanMakeLogs = GetND().GetMS().GetOptoinsTrader().MakeTraderLogs;
			
			//restocking 
			int restockingTime = GetND().GetMS().GetOptoinsTrader().TraderRestockingPerTime;
			if ( restockingTime  )
			{
				restockingTime *= 1000;
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.Restocking,restockingTime,true);
			}
		
		}
	
	}
	
	void OnRPC( PlayerBase player, ParamsReadContext ctx )
	{
		int rpc;
		ctx.Read( rpc );
		
		switch ( rpc )
		{
			case ALP_RPC_PLUGIN_MS_TRADER.GIVE_ME_ALL_STOCK:
			{//client
				array<int> items;
				ctx.Read( items );
				int stockID = player.GetRP().GetCart().GetNPCid();
				if ( items && items.Count() > 0 )
				{
					UpdateStock( stockID,  items );	
				}
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.GetReadyClientData,1200,false,player);
				break;
			}	
			case ALP_RPC_PLUGIN_MS_TRADER.GIVE_ME_ACCOUNT:
			{//client
				alpBankAccount account;
				ctx.Read( account );
				ctx.Read( alpBANK.alp_BankBalance );
				ctx.Read( alpBANK.alp_PlayerBankBalance );
				ctx.Read( alpBANK.alp_TraderBankBalance );
				alpBANK.SetClientAccount( account );
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.GetReadyClientData,1200,false,player);
				break;
			}
			case ALP_RPC_PLUGIN_MS_TRADER.ATM_CASH:
			{//server
				Param3<int,int,int> cash_transaction; 
				ctx.Read( cash_transaction );			
				
				//vypis co prislo na server
				//Print("HODNOTA 1 ucet " + cash_transaction.param1 );
				//Print("HODNOTA 2 mena " + cash_transaction.param2 );
				//Print("HODNOTA 3 zmena " + cash_transaction.param3 );
					
				player.GetRP().GetCart().Refresh();		
				int currentcash = 	player.GetRP().GetCart().GetMoney( 	cash_transaction.param2 );		
				
				//Print("CASH HRAC " + currentcash );
						
				int cashBack = alpBANK.AddBalanceToAccount(cash_transaction.param1,cash_transaction.param2,cash_transaction.param3, player);	
				
				//Print("CASH_BACK " + cashBack );
							
				if ( cash_transaction.param3 > 0 )
				{//deposit
					currentcash	-= cash_transaction.param3;
				}
				else
				{//withdraw
					if ( cashBack )
					{//not enough cash
						cashBack = cash_transaction.param3 + cashBack;
					}				
					else
					{
						cashBack = cash_transaction.param3;	
					}		
					currentcash	-= cashBack;
				}
			
				//Print("MEL BYCH DOSTAT " + currentcash );
				//Print("MENA JE " + cash_transaction.param2 );
					
				player.GetRP().GetCart().GiveMeMoney( currentcash, cash_transaction.param2);
				GetND().GetMS().GetTrader().GiveMeAccount( cash_transaction.param1, player );
				break;
			}					
			case ALP_RPC_PLUGIN_MS_TRADER.CARD_BLOCK:
			{//server
				int idcard,idaccount;
				ctx.Read( idaccount );
				ctx.Read( idcard );
				alpBANK.BlockCard(idaccount,idcard);
				GetND().GetMS().GetTrader().GiveMeAccount( idaccount, player );	
				break;
			}			
			case ALP_RPC_PLUGIN_MS_TRADER.CARD_CHANGE_PASSWORD:
			{//server
				int pswd;
				ctx.Read( pswd );
				alp_Debitcard card = alp_Debitcard.Cast( player.GetItemInHands() );
				if (card)
				{
					card.SetCardPIN( pswd );
				}
				break;
			}						
			case ALP_RPC_PLUGIN_MS_TRADER.BUY_ITEMS:
			{//server
				array<ref Param3<string,int,int>> itemsToBuy;
				ctx.Read( itemsToBuy );
				BuyItems(player, itemsToBuy);
				break;
			}	
			case ALP_RPC_PLUGIN_MS_TRADER.SELL_ITEMS:
			{//server
				array<ref Param2<string,int>> itemsToSell;
				ctx.Read( itemsToSell );
				SellItems(player, itemsToSell);				
				break;
			}		
			case ALP_RPC_PLUGIN_MS_TRADER.ATM_TAKELOAN:
			{//server
				Param6<int,int,int,int,float,int> takeLoan;
				ctx.Read( takeLoan );
				
				alpBANK.TakeLoan( player, takeLoan );

				GetND().GetMS().GetTrader().GiveMeAccount( takeLoan.param1, player );				
				break;
			}	
			case ALP_RPC_PLUGIN_MS_TRADER.ATM_REPAYLOAN:
			{//server
				Param3<int,int,int> repay;
				ctx.Read( repay );
				alpBANK.PartialLoanRepayment(repay.param1,repay.param2, repay.param3, player );
				GetND().GetMS().GetTrader().GiveMeAccount( repay.param1, player );	
				break;
			}	
			case ALP_RPC_PLUGIN_MS_TRADER.ATM_EXCHANGE:
			{//server
				Param5<int,int,int,int,int> exchange;
				ctx.Read( exchange );
				alpBANK.Exchange(exchange.param1,exchange.param2, exchange.param3, exchange.param4, exchange.param5, player );
				GetND().GetMS().GetTrader().GiveMeAccount( exchange.param1, player );	
				break;
			}
			default :
			{
				PluginsOnRPC(rpc,  player, ctx );
				break;
			}
																			
		}	
	}
	
	bool PluginsOnRPC(int rpc, PlayerBase player, ParamsReadContext ctx )
	{
		return false;	
	}	

	void GetReadyClientData(PlayerBase player)
	{
		player.GetRP().GetCart().Refresh();
		SetValidTraderData( true );	
	}
	
	void SellItems(PlayerBase player, array<ref Param2<string,int>> itemstosell)
	{
		player.GetRP().GetCart().Refresh();
		
		int guid = player.GetPlayerHive().GetPlayerID();
		
		int stockID = player.GetRP().GetCart().GetNPCid();				
		
		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();
		
		int cash = player.GetRP().GetCart().GetCash();
		
		int back;
		int cashTrader;
		
		float reputation,repbonus;
		
		if ( m_CanMakeLogs ){
			
			int y,mm,d;
			int h,m,s;
			GetYearMonthDayUTC(y,mm,d);
			GetHourMinuteSecondUTC(h,m,s);	
			string timeStamp = string.Format("%1/%2/%3 - %1:%2:%3", y.ToString(),mm.ToString(),d.ToString(),h.ToString(), m.ToString(), s.ToString());		
		}
		
		foreach( Param2<string,int> item : itemstosell )
		{
			string index = item.param1;
			int price = item.param2;
			
			EntityAI ent = player.GetRP().GetCart().GetItemByID( index );
			int realTrade = 0;		
			string type;	
			//ammoPile
			if ( ent )
			{
				type = ent.GetType();
				if (ent.IsMagazine() )
				{
					Magazine_Base mag = Magazine_Base.Cast( ent);
					
					if ( mag )
					{
						float fullness = mag.GetAmmoCount() / mag.GetAmmoMax();
						if ( fullness > 0.5 )
						{
							AddCount( stockID, mag.GetType() , 1);
						}
					}
				}
				else
				{
					AddCount( stockID, ent.GetType() , 1);
				}
				//addReputation
				if ( ent.IsTransport() )
				{
					CarScript car = CarScript.Cast( ent );
					if ( car )
					{
						repbonus = car.GetTraderItemConfig().ReputationRatioSelling * price;
						reputation += repbonus;
					}
				}
				else
				{
					ItemBase itm = ItemBase.Cast( ent );
					if (itm )
					{
						repbonus = itm.GetTraderItemConfig().ReputationRatioSelling * price;
						reputation += repbonus;					
					}
				
				}			
				//end reputation
				GetGame().ObjectDelete( ent );			
				if (isEbank)
				{
					back += alpBANK.AddBalanceToAccount(guid, currency, price , player);
					alpBANK.SaveAccount(guid);
				}
				else
				{
					back += price;				
				}
				cashTrader -= price;	
				realTrade++;							
			}
			if ( m_CanMakeLogs  ) {//enabled logs
				GetND().MakeTraderLog( timeStamp, player, stockID, 1, type, realTrade , cashTrader );
			}	
		}
		//add reputation
		if ( reputation )
		{
			reputation *= player.GetReputationMltp(1);
			player.GetRP().ChangeReputation( reputation );	
		}
		
		
		if ( back )
		{
			cash += back;
			player.GetRP().GetCart().GiveMeMoney( cash , currency);
		}
		//Bank profit
		alpBANK.TakeBusinessProfit(currency, Math.AbsInt( cashTrader ) );
		
		//to trader		
		AddBalanceTrader( stockID, cashTrader );

		//refresh
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  player.GetRP().GetCart().GetNPCid(), player );		
	}	
	void BuyItems(PlayerBase player, array<ref Param3<string,int,int>> itemstobuy)
	{

		player.GetRP().GetCart().Refresh();
		
		int guid = player.GetPlayerHive().GetPlayerID();
		
		int stockID = player.GetRP().GetCart().GetNPCid();

		int currency = player.GetRP().GetCart().GetCurrencyID();
		int isEbank = player.GetRP().GetCart().HasBankAccount();		
		
		int totalbalance = player.GetRP().GetCart().GetTotalBalance();
		
		int cash = player.GetRP().GetCart().GetCash();		
		int topay;
		int cashTrader;
		
		float reputation,repbonus;
		
		int i;
		if ( m_CanMakeLogs ){
			int y,mm,d;
			int h,m,s;
			GetYearMonthDayUTC(y,mm,d);
			GetHourMinuteSecondUTC(h,m,s);	
			string timeStamp = string.Format("%1/%2/%3 - %1:%2:%3", y.ToString(),mm.ToString(),d.ToString(),h.ToString(), m.ToString(), s.ToString());
		}		
		foreach( Param3<string,int,int> item : itemstobuy )
		{
			string type = item.param1;
			int price = item.param2;
			int count = item.param3;
								
			count = AddCount( stockID, type, -count);
			int realTrade = 0;
			for(i=0;i<count;i++)
			{	
				topay += price;		
				EntityAI ent = player.GetRP().GetCart().InsertIntoCart( type );		
				if (!ent && ( GetGame().IsKindOf(type,"CarScript") || GetGame().IsKindOf(type,"HelicopterScript") ) )
				{
					ent = player.GetRP().GetCart().BuyVehicle( type );
				}			

				if ( topay > totalbalance || !ent )
				{//return to stock and break loop
					if ( ent )
					{
						GetGame().ObjectDelete(ent);
					}
					AddCount( stockID, type, 1);
					topay -= price;	
					break;
				}
				
				//addReputation
				if ( ent )
				{
					if ( ent.IsTransport() )
					{						
						CarScript car;
						HelicopterScript heli;
						if ( Class.CastTo( car, ent ) )
						{
							repbonus = car.GetTraderItemConfig().ReputationRatioBuying * price;
							reputation -= repbonus;
						} else if ( Class.CastTo( heli, ent ) ) {
							repbonus = heli.GetTraderItemConfig().ReputationRatioBuying * price;
							reputation -= repbonus;												
						}
					}
					else
					{
						ItemBase itm = ItemBase.Cast( ent );
						if (itm )
						{
							repbonus = itm.GetTraderItemConfig().ReputationRatioBuying * price;
							reputation -= repbonus;					
						}
					
					}					
				}	
				//end reputation					
											
				if (ent && ent.GetType() == "alp_Debitcard")
				{//debitCard	
					alp_Debitcard card = alp_Debitcard.Cast( ent );
					
					int cardID = card.GetCardID();
					card.SetBankID( guid);					
					alpBANK.RegisterCard( guid, cardID);

				}
				cashTrader += price;	
				realTrade++;				
			}		
			if ( m_CanMakeLogs  ) {//enabled logs
				GetND().MakeTraderLog( timeStamp, player, stockID, 0, type, realTrade , cashTrader );
			}				
		}
		//add reputation
		if ( reputation )
		{
			reputation *= player.GetReputationMltp(0);
			player.GetRP().ChangeReputation( reputation );	
		}		
		
		if (isEbank)
		{
			topay = alpBANK.AddBalanceToAccount(guid, currency, -topay, player );
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
		
		//refresh		
		player.GetSyncData().ForceSync();
		GetND().GetMS().GetTrader().GiveMeStock(  stockID, player );		
	}

	void GiveMeStock(int id, PlayerBase player , bool empty = false)
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.GIVE_ME_ALL_STOCK );	
		
		
		
		
		array<int> items;
		
		if (!empty)
		{
			items = GetStockItems( id );
			/*
			alpNPCtraderStock stock = alp_TraderStockMapped.Get(id);
			if ( stock )
			{
			
				items = stock.Stock.GetValueArray();
			}
			*/		
		}

		rpc.Write( items );	
		
		GetND().SendGameRPC( rpc, player );	
		
			
	}	
	

	
	
		
	void GiveMeAccount(int id, PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.GIVE_ME_ACCOUNT );	
		
		alpBankAccount account = alpBANK.GetBankAccount( id );		

		rpc.Write( account );	
		rpc.Write( alpBANK.alp_BankBalance );	
		rpc.Write( alpBANK.alp_PlayerBankBalance );	
		rpc.Write( alpBANK.alp_TraderBankBalance );	
		GetND().SendGameRPC( rpc, player );	
		
			
	}		
	void BlockCard(int accountid, int cardid, PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.CARD_BLOCK );	
		
		rpc.Write( accountid );		
		rpc.Write( cardid );	
		
		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );			
	}	

	void Exchange(int accountid, int fromCurrency, int toCurrency, int fromAmmount, int toAmmount,  PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ATM_EXCHANGE );	
		
		Param5<int,int,int,int,int> exchange = new Param5<int,int,int,int,int>(accountid,fromCurrency,toCurrency,fromAmmount,toAmmount);
				
		rpc.Write( exchange );		

		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );	
	}	
		

	void PartialLoanRepayment(int accountid, int currency, int pay,  PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ATM_REPAYLOAN );	
		
		Param3<int,int,int> loan = new Param3<int,int,int>(accountid,currency,pay);
				
		rpc.Write( loan );		

		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );	
	}	
		
	void TakeLoan(int accountid, int currency, int principal, int interest, float rate, int length,  PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ATM_TAKELOAN );	
		
		Param6<int,int,int,int,float,int> loan = new Param6<int,int,int,int,float,int>(accountid,currency,principal,interest,rate,length);
				
		rpc.Write( loan );		

		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );	
	}		
	
	void CashTranscation(int accountid, int currency, int cash, PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.ATM_CASH );	
		
		Param3<int,int,int> transaction = new Param3<int,int,int>(accountid,currency,cash);
				
		rpc.Write( transaction );		

		GetND().SendGameRPC( rpc, player );	
		
		SetValidTraderData( false );	
	}	
		
	void GhangePassword(int pswd, PlayerBase player )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.CARD_CHANGE_PASSWORD );	
				
		rpc.Write( pswd );	
		
		GetND().SendGameRPC( rpc, player );	
		
			
	}	
	
	bool IsTraderSet()
	{
		return alp_AreTraderDataVaild;
	}	
	
	void SetValidTraderData(bool state)
	{
		alp_AreTraderDataVaild = state;
	}
}