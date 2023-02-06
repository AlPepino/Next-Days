class alpTraderItem 
{
	string Group;
	string Category;
	string Subcategory;
	
	EntityAI Item;
	ref array<string> ItemsID;
	
	
	void alpTraderItem( EntityAI ent)
	{
		Item = ent;
		ItemsID = new array<string>;
	}
	
	void AddItem(string id)
	{
		ItemsID.Insert(id);
	}
	
	array<string> GetStock()
	{
		return ItemsID;
	}

	string GetType()
	{
		return Item.GetType();
	}
	
	EntityAI GetItem()
	{
		return Item;
	}
	
}

class alpTraderCart 
{
	PlayerBase alp_Player;
	int alp_NPCID;
	int alp_MissionID;
	
	
	ref map<string,EntityAI> alp_ItemsMapped;
	ref array<ItemBase> alp_AllMoney;
	
	ref array<ref alpProductCard> alp_ReservedProducts;
	

	
	ref map<string, ref map<string, ref alpTraderItem>> alp_ItemsTosell;
	
	void alpTraderCart(PlayerBase player)
	{
		alp_Player = player;
		
		alp_ReservedProducts = new array<ref alpProductCard>;
		alp_AllMoney = new array<ItemBase>;
		
		alp_ItemsMapped = new map<string,EntityAI>;
		alp_ItemsTosell = new map<string, ref map<string, ref alpTraderItem>> ;
		
		//alp_ReadyItemToSell = new array<int>;
		//alp_ReadyItemToBuy = new array<string> ;
		
		
		//GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.Refresh,5000);
	}
	
	EntityAI GetItemByID(string id )
	{
		return alp_ItemsMapped.Get( id );	
	}
	
	bool Confirm()
	{
		if (!CheckCashCondition(0))
		{
			GetND().GetNotf().GetHud().SendMessageALP( ALPMSTYPE.SMPERSONAL, "#trader_info_notpossible"); 
			return false;
		}
		
		
		
		if ( GetND().GetMS().GetTrader().IsBuyMenu() )
		{
			SendItemsToBuy();
		}
		else
		{
			SendItemsToSell();
		}
		ClearCart();	
		GetND().GetMS().GetTrader().SetValidTraderData( false );		
		return true;
	}
	
	void SendItemsToBuy()
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.BUY_ITEMS );	
		
		//map<string,int> items = new map<string,int>;
		
		array<ref Param3<string,int,int>> items = new array<ref Param3<string,int,int>>;	
		
		if ( alp_ReservedProducts )
		{
			foreach( alpProductCard product : alp_ReservedProducts )
			{
				string name = product.GetType();
				int price = product.GetPrice();
				int count = product.GetCountReserved();
				
				items.Insert( new Param3<string,int,int>(name,price,count) );
								 
			}
		}
		
		rpc.Write( items );	
		
		GetND().SendGameRPC( rpc, GetPlayer() );	
		
	}
	void SendItemsToSell()
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetMS().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_MS.TRADER );	
		rpc.Write( ALP_RPC_PLUGIN_MS_TRADER.SELL_ITEMS );	
		
		//map<string,int> items = new map<string,int>;
		
		array<ref Param2<string,int>> items = new array<ref Param2<string,int>>;	
		
		if ( alp_ReservedProducts )
		{
			foreach( alpProductCard product : alp_ReservedProducts )
			{
				
				int price = product.GetPrice();
				int count = product.GetCountReserved();
				array<string> itemsID = product.GetIndexedItemToSell();
				for(int i = 0; i < count;i++)
				{
					items.Insert( new Param2<string,int>(itemsID.Get(i),price) );	
				}
								 
			}
		}
		
		rpc.Write( items );		
		GetND().SendGameRPC( rpc, GetPlayer() );	
	}
	
	
	map<string, ref map<string, ref alpTraderItem>>  GetItemsToSell()
	{
		
		return alp_ItemsTosell;
	}

	void GiveMeMoney(int cash, int currencyID)
	{
		int i,nominal,stack,deposit;
		
		
		
		for (i = 0; i < alp_AllMoney.Count();)
		{
			if ( alpBANK.VerifyBankNote(currencyID, alp_AllMoney.Get(i).GetType()) )
			{
				GetGame().ObjectDelete(alp_AllMoney.Get(i));
			}			
			alp_AllMoney.Remove(i);
		}	

		if ( cash > 0 )
		{
			map<int,ref alpBankNote> banknotes = alpBANK.GetBankNotes( currencyID );	
			array<int> nominals = banknotes.GetKeyArray();		
			nominals.Sort(true);
			
			float count;
			for (i = 0; i < nominals.Count();i++)
			{
				nominal = nominals.Get(i);
				alpBankNote bn = banknotes.Get( nominal );

				count = (float) (cash / nominal); 

				if ( count >= 1 )
				{
					count = Math.Floor(count);	
					cash = cash - count * nominal;	
					stack = bn.Quantity;	
					
					while ( count > 0 )
					{

						count -= stack;
						
						if (count < 0 ) stack += count;
						
						alp_Cash money = alp_Cash.Cast(alp_Player.CreateInInventory( bn.Name ));
						
						if (!money) 
						{	
							money = alp_Cash.Cast(GetGame().CreateObject( bn.Name,GetPlayer().GetPosition(),false,false,true));
						}
						
						if ( money )
						{
							money.SetQuantity(stack);	
						}
									
					}
				}
				
				if ( cash == 0 )
					break;
			}
		}
	}
	void GiveMeJustMoney(int cash, int currencyID)
	{
		int i,nominal,stack,deposit;
			
	
		map<int,ref alpBankNote> banknotes = alpBANK.GetBankNotes( currencyID );	
		array<int> nominals = banknotes.GetKeyArray();		
		nominals.Sort(true);
		
		float count;
		for (i = 0; i < nominals.Count();i++)
		{
			nominal = nominals.Get(i);
			alpBankNote bn = banknotes.Get( nominal );

			count = (float) (cash / nominal); 

			if ( count >= 1 )
			{
				count = Math.Floor(count);	
				cash = cash - count * nominal;	
				stack = bn.Quantity;	
				
				while ( count > 0 )
				{

					count -= stack;
					
					if (count < 0 ) stack += count;
					
					alp_Cash money = alp_Cash.Cast(alp_Player.CreateInInventory( bn.Name ));
					
					if (!money) 
					{	
						money = alp_Cash.Cast(GetGame().CreateObject( bn.Name,GetPlayer().GetPosition(),false,false,true));
					}
					
					if ( money )
					{
						money.SetQuantity(stack);	
					}
								
				}
			}
			
			if ( cash == 0 )
				break;
		}
	}	
	void SetNPCid( int id, int misisonID = 0 )
	{
		alp_NPCID = id;
		alp_MissionID = misisonID;
	}	
	
	int GetNPCid()
	{
		return alp_NPCID;
	}
	int GetMissionID()
	{
		return alp_MissionID;
	}
		
	PlayerBase GetPlayer()
	{
		return alp_Player;
	}
	
	int GetCurrencyID()
	{
		int currency;
		
		alpNPCtraderStock stock = alpTraderCoreBase.alp_TraderStockMapped.Get(	GetNPCid() );
		if ( stock )
		{
			currency = stock.CurrencyID;
		}
		return currency;		
	}
	int HasBankAccount()
	{
		alpNPCtraderStock trader =	alpTraderCoreBase.alp_TraderStockMapped.Get( GetNPCid() );
		
		int method;
		
		if ( trader )
		{
			
			bool setting = trader.EnabledInteractions;			
			
			if ( setting & alpNPC_AVAILABLE_MENU.BANK )
			{
				method = alpPAY_METHODS.BANK;
			}
			if ( setting & alpNPC_AVAILABLE_MENU.BANK_ONLY )
			{
				method = alpPAY_METHODS.BANK_ONLY;
			}			
					
		}
		return method;	
	}
		
	int GetTotalBalance()//client only
	{
		int balance;
		int payMethod = HasBankAccount();
				
		if ( HasBankAccount() )
		{
			float bank;
			GetPlayer().GetSyncData().GetElementEnhanced( alpRPelementsEnahnced.PLAYER_BALANCE).GetValue( bank );
			
			balance+= (int) bank;
			
			if ( payMethod == alpPAY_METHODS.BANK_ONLY )
			{
				return balance;
			}				
		}		
		balance += GetMoney( GetCurrencyID() );

		return balance;
	}	
	
	int GetCash()
	{
		return GetMoney( GetCurrencyID() );
	}
	int GetCredit()
	{
		float bank;
		if ( HasBankAccount() )
		{
			
			GetPlayer().GetSyncData().GetElementEnhanced( alpRPelementsEnahnced.PLAYER_BALANCE).GetValue( bank );
		}	
		return (int) bank;
	}
	
	
	int GetBankBalance()//server side only SYNC
	{
		int currency = GetCurrencyID();
		
		if ( currency >= 0 )
		{
			int balance = alpBANK.GetBalanceInCurrency( GetPlayer().GetPlayerHive().GetPlayerID(), currency );
			return balance;
		}
		
		return 0;
	}
	

	
	void Refresh()
	{
		alp_ItemsMapped.Clear();
		alp_ItemsTosell.Clear();
		alp_AllMoney.Clear();
		
		//int currencyID = GetCurrencyID();
		
		string index;
		string name,subcat,category;
		alpTraderItem traderitem;
		map<string, ref alpTraderItem> traderItems;
		
		array<EntityAI> itemsArray = new array<EntityAI>;
		ItemBase item;
		EntityAI parent;
		
		string parentName = GetPlayer().GetIdentity().GetName();
		
		alp_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		int i;
		for (i = 0; i < itemsArray.Count(); i++)
		{				
			item = ItemBase.Cast(itemsArray.Get(i));
			
			if ( item )
			{	
				if ( item.IsInherited(alp_Cash) &&  item.GetType() != "alp_CoinRare1" )
				{
					alp_AllMoney.Insert( item );
				}		
				else
				{
					name = item.GetNameALP(); 
					subcat = GetParent( item ,  GetPlayer().GetType() );
					category = parentName + parentName + subcat;
								
					if ( !alp_ItemsTosell.Find( category, traderItems) )
					{
						traderItems = new map<string, ref alpTraderItem>;
						alp_ItemsTosell.Set( category, traderItems);
					}					
					
					//category
					if ( !traderItems.Find( name, traderitem) )
					{
						traderitem = new alpTraderItem( item );
						traderitem.Group = parentName;
						traderitem.Category = parentName;
						traderitem.Subcategory = subcat;
						traderItems.Set( name, traderitem);
					}
					index =  item.GetServerWorldID();
					traderitem.AddItem( index );
					alp_ItemsMapped.Set( index , item);
					//index++;						
				}
			}
		}		
		//vehicle
		Transport tr = GetPlayer().GetRP().GetCar();		
		EntityAI itemCar;

		if ( tr && tr.IsKindOf("CarScript") ) {
			CarScript car = CarScript.Cast( tr );
			if ( car ) {
				itemsArray.Clear();
				
				parentName = car.GetDisplayName();
				
				car.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
				
				for (i = 0; i < itemsArray.Count(); i++)
				{	
				
		
					itemCar = EntityAI.Cast(itemsArray.Get(i));
					
					
	
					if ( itemCar  ){	
						if ( itemCar.IsInherited(alp_Cash)  &&  item.GetType() != "alp_CoinRare1"  )
						{
							alp_AllMoney.Insert( ItemBase.Cast(itemCar) );
						}		
						else
						{
							//Print( itemCar.GetType() );
							
							name = GetNameALP(itemCar); 
							subcat = GetParent( itemCar ,  GetPlayer().GetType() );
							category = parentName + parentName + subcat;
										
							if ( !alp_ItemsTosell.Find( category, traderItems) )
							{
								traderItems = new map<string, ref alpTraderItem>;
								alp_ItemsTosell.Set( category, traderItems);
							}					
							
							//category
							if ( !traderItems.Find( name, traderitem) )
							{
								traderitem = new alpTraderItem( itemCar );
								traderitem.Group = parentName;
								traderitem.Category = parentName;
								traderitem.Subcategory = subcat;
								traderItems.Set( name, traderitem);
							}
							if ( itemCar.IsItemBase() ){
								index =  ItemBase.Cast(itemCar).GetServerWorldID();
							} else {
								index =  car.GetServerWorldID();
							}
							
							traderitem.AddItem(  index );
							alp_ItemsMapped.Set(index, itemCar);
							//index++;			ItemBase			
						}						
							
						
		
					}
				}		
			}			
		} else if (tr &&  tr.IsKindOf("HelicopterScript") ) {  
			HelicopterScript heli = HelicopterScript.Cast( tr );
			if ( heli ) {
				itemsArray.Clear();
				
				parentName = heli.GetDisplayName();
				
				heli.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
				
				for (i = 0; i < itemsArray.Count(); i++)
				{	
				
		
					itemCar = EntityAI.Cast(itemsArray.Get(i));
					
					
	
					if ( itemCar  ){	
						if ( itemCar.IsInherited(alp_Cash)  &&  item.GetType() != "alp_CoinRare1"  )
						{
							alp_AllMoney.Insert( ItemBase.Cast(itemCar) );
						}		
						else
						{
							//Print( itemCar.GetType() );
							
							name = GetNameALP(itemCar); 
							subcat = GetParent( itemCar ,  GetPlayer().GetType() );
							category = parentName + parentName + subcat;
										
							if ( !alp_ItemsTosell.Find( category, traderItems) )
							{
								traderItems = new map<string, ref alpTraderItem>;
								alp_ItemsTosell.Set( category, traderItems);
							}					
							
							//category
							if ( !traderItems.Find( name, traderitem) )
							{
								traderitem = new alpTraderItem( itemCar );
								traderitem.Group = parentName;
								traderitem.Category = parentName;
								traderitem.Subcategory = subcat;
								traderItems.Set( name, traderitem);
							}
							if ( itemCar.IsItemBase() ){
								index =  ItemBase.Cast(itemCar).GetServerWorldID();
							} else {
								index =  heli.GetServerWorldID();
							}
							
							traderitem.AddItem(  index );
							alp_ItemsMapped.Set(index, itemCar);
							//index++;			ItemBase			
						}						
		
					}
				}			
			
			}				
		}				

	}
	
	string GetNameALP(EntityAI ent)
	{
		if ( ent.IsTransport() )
		{
			CarScript car = CarScript.Cast( ent );
			
			return car.GetNameALP();
		}
		else
		{
			ItemBase item = ItemBase.Cast( ent );
			
			return item.GetNameALP();		
		}
	}

	int GetMoney(int currency = 0)
	{
//&&  alpBANK.VerifyBankNote(currencyID, item.GetType())
		int m = 0;
		for (int i=0; i<alp_AllMoney.Count();i++)
		{	

			alp_Cash cash = alp_Cash.Cast( alp_AllMoney.Get(i));
		
			if (cash &&  alpBANK.VerifyBankNote(currency, cash.GetType()) )
			{
			
				m += (int) cash.GetMonyeSum();
			}
		}
		return m;		
	}
	
	string GetParent( EntityAI item, string rootParent )
	{
		string parentName = item.GetDisplayName();

		if ( GetGame().IsClient() )
		{
			EntityAI parent = EntityAI.Cast( item.GetHierarchyParent() );
	
			while(parent && parent.GetType() != rootParent )
			{
				parentName = parent.GetDisplayName();
				parent = EntityAI.Cast( parent.GetHierarchyParent() );
			}
		
		}

		return parentName;
	}
	
	int GetTotalAmount()
	{
		int total;
		if ( alp_ReservedProducts )
		{
			foreach( alpProductCard product : alp_ReservedProducts)
			{
				total += product.GetCountReserved() * product.GetPrice();
			}
		}
		return total;	
	}
	
	int GetCountItemsInCart()
	{
		int count;
		if ( alp_ReservedProducts )
		{
			foreach( alpProductCard product : alp_ReservedProducts)
			{
				count += product.GetCountReserved();
			}
		}
		return count;
	}
	
	bool CheckCashCondition(int price )//use in confirm button
	{
		//check balance
		int cost = GetTotalAmount();
		int balance;
		
		if ( GetND().GetMS().GetTrader().IsBuyMenu() )
		{
			balance	= GetTotalBalance();
		}
		else
		{
			float cash;
			GetPlayer().GetSyncData().GetElementEnhanced( alpRPelementsEnahnced.TRADER_BALANCE).GetValue( cash );
			balance = (int) cash;
		}		

		balance = balance - cost - price;
	
		if (balance < 0 )
		{
			//GetND().GetNotf().GetHud().SendMessageALP( ALPMSTYPE.SMPERSONAL, "#trader_info_notpossible"); 					
			return false;
		}
		else
		{
			return true;
		}
	}
	
	bool AddItemToCart(alpProductCard product)
	{

		if (CheckCashCondition( product.GetPrice()) && product.AddReservation() )
		{
			int find = 	alp_ReservedProducts.Find( product );
			if ( find < 0 )
			{
				alp_ReservedProducts.Insert(product);
			}					
			return true;
		}
		return false;
	}
	
	bool RemoveItemFromCart(alpProductCard product)
	{
		if ( alp_ReservedProducts )
		{
			int find = 	alp_ReservedProducts.Find( product );
			
			if ( find < 0 )
			{
				return false;
			}
			else
			{			
				product.RemoveReservation();
				if ( product.GetCountReserved() <= 0 )
				{
					alp_ReservedProducts.RemoveItem( product );			
				}
				return true;
			}
		}	
		return false;
	}
	
	void ClearCart()
	{
		if ( alp_ReservedProducts )
		{
			foreach( alpProductCard product : alp_ReservedProducts)
			{
				product.RemoveReservation( true );
			}
		}
		alp_ReservedProducts.Clear();
	}
	
	array<ref alpProductCard> GetReservedItems()
	{
		return alp_ReservedProducts;
	}
	
	EntityAI InsertIntoCart(string type )
	{
		EntityAI ent;
		
		ent = GetPlayer().GetInventory().CreateInInventory( type );
		
		if ( !ent )
		{
			Transport car = GetPlayer().GetRP().GetCar();
			if (car)
			{
				//unlock car
				if (car.GetInventory().IsInventoryLocked())
				{
					car.GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);		
					ent = car.GetInventory().CreateInInventory(type);
					car.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
				}
				else
				{
					ent = car.GetInventory().CreateInInventory(type);
				}			
			}		
		}
		if (GetGame().IsClient() && !ent)
		{//trader_info_noroom
			GetND().GetNotf().GetHud().SendMessageALP( ALPMSTYPE.SMPERSONAL, "#trader_info_noroom"); 
		}						
		return ent;
	}
	
	EntityAI BuyVehicle( string type )
	{
		EntityAI ent;
		alpMission mission = GetND().GetMS().GetMission( GetMissionID() );
		
		if (mission)
		{
			foreach(alpMissionAddSpawn spawn : mission.GetTemplate().spawnPlaceForVehicles )
			{
				
				vector pos = mission.GetWorldPosition( spawn.position );

				ent = EntityAI.Cast( GetGame().CreateObject( type, pos));
				if (ent)
				{
		//Print("AUTO VYTVORENO");
					if (!alpUF.IsColliding(ent))
					{
						ent.SetYawPitchRoll( mission.GetWorldOrientation(spawn.yaw,spawn.pitch,spawn.roll  ) );	
						CarScript car;
						HelicopterScript heli;
						
						if (Class.CastTo(car, ent) ) {
										
							array<string> atts = GetND().GetMS().GetTrader().GetCarAttachments( type );
							
							if (!atts)
							{//if is not set Attachments

								GetGame().ObjectDelete(ent);
								ent = null;		
								return ent;					
							}
							
							for (int i = 0; i < atts.Count();i++)
							{//attachments
				
								car.GetInventory().CreateInInventory(atts.Get(i));
							}							
							alpUF.FillFluidsToVehicle(car );//fill fluids
							
							//lock car
							if ( !GetND().GetMS().GetOptoinsTrader().NoKeyForBoughtVehicle )
							{
								GiveMeVehicleKey(car.GetAlpCarID());
								car.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
								car.alp_Lock = true;							
							}
							//setlifetime
							ent.SetLifetimeMax(ALP_LIFETIMEMAX);
							ent.SetLifetime(ALP_LIFETIMEMAX);		
							ent.PlaceOnSurface();		
							return ent;
							
						} else if ( Class.CastTo(heli, ent) ) {
							array<string> atts2 = GetND().GetMS().GetTrader().GetCarAttachments( type );
							
							if (!atts2)
							{//if is not set Attachments

								GetGame().ObjectDelete(ent);
								ent = null;		
								return ent;					
							}
							
							for (int i2 = 0; i2 < atts2.Count();i2++)
							{//attachments
				
								heli.GetInventory().CreateInInventory(atts2.Get(i2));
							}							
							//alpUF.FillFluidsToVehicle(car );//fill fluids
							
							//lock car
							/*
							if ( !GetND().GetMS().GetOptoinsTrader().NoKeyForBoughtVehicle )
							{
								GiveMeVehicleKey(car.GetAlpCarID());
								car.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
								car.alp_Lock = true;							
							}
							*/
							//setlifetime
							ent.SetLifetimeMax(ALP_LIFETIMEMAX);
							ent.SetLifetime(ALP_LIFETIMEMAX);		
							ent.PlaceOnSurface();		
							return ent;						
						
						}			
					}
					else
					{
						GetGame().ObjectDelete(ent);
						ent = null;
					}
				}
				
			}					
		
		}
		return ent;		
	}
	
	protected void GiveMeVehicleKey(int carID)
	{
		array<string> keys = {"alp_CarKey","alp_CarKeyBlue","alp_CarKeyGreen","alp_CarKeyYellow","alp_CarKeyWhite","alp_CarKeyPurple","alp_CarKeyBrown"};
		
		alp_CarKey key = alp_CarKey.Cast(GetPlayer().CreateInInventory( keys.GetRandomElement() ));
		
		if (!key)
		{
			key = alp_CarKey.Cast(GetGame().CreateObject( keys.GetRandomElement(),GetPlayer().GetPosition(),false,false,true));
		}
		
		if (key)
		{
			key.SetAlpKeyID( carID );
			key.SetSynchDirty();
		}		
	
			
	}	
}