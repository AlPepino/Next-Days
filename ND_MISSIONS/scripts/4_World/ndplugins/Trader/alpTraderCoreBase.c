



class alpTraderCoreBase 
{
	//alpNPC alp_NPC;
	
	int alp_NPC_ID;
	
	static bool TRADER_ACTION_BUY;
		
	static autoptr map<int,string>												alp_CurrencyMapped;
	
	autoptr map<string,autoptr array< autoptr alpTraderItemConfig >>			alp_AllItemsByTag;
	static autoptr map<string,autoptr alpTraderItemConfig >						alp_AllItemsByName = new map<string,autoptr alpTraderItemConfig >;
	static autoptr map<int,autoptr alpTraderCategories>							alp_CategoriesMapped = new map<int, ref alpTraderCategories>;
	
	static autoptr map<int,autoptr alpNPCtraderStock>							alp_TraderStockMapped = new map<int,autoptr alpNPCtraderStock>;
	
	static autoptr map<int,autoptr map<string,int>>								alp_TraderMainStock = new map<int,autoptr map<string,int>>;
	
	static autoptr array<string>												alp_AllowedItems = new array<string>;
	
	static autoptr array<autoptr alpTraderCategories>							alp_CategoriesOverride;
	static autoptr array<autoptr alpTraderItemConfig>							alp_ItemsOverride;
	
	
	ref alpMenuCategory															alp_TraderMenu;
	ref array<EntityAI>															alp_ReservedItem;
	
	ref array<ref alpProductCard>         										alp_TraderData;
	ref map<int,ref array< ref alpProductCard>>									alp_TraderDataIndexed;		
	
	
	void ~alpTraderCoreBase()
	{
		delete alp_AllItemsByTag;
		delete alp_TraderMenu;
		delete alp_ReservedItem;
		delete alp_TraderData;
		delete alp_TraderDataIndexed;
		
	}
	
	static string GetCurrencyName(int id )
	{
		//map currency
		if ( !alpTraderCoreBase.alp_CurrencyMapped )
		{
			alpTraderCoreBase.alp_CurrencyMapped = new map<int,string>;
			map<int, ref alpCurrency> currencies = alpBANK.GetCurencies().GetCurrencies();	
			if ( 	currencies )
			{
				for (int c = 0; c < currencies.Count();c++)
				{
					alpCurrency currency = currencies.GetElement(c);
					alpTraderCoreBase.alp_CurrencyMapped.Set(c,currency.Name);
				}			
			}		
		
		}
		string name = alpTraderCoreBase.alp_CurrencyMapped.GetElement( id );
		return name;
	}
	
	alpMenuCategory GetTraderMenu()
	{
		
		if (IsBuyMenu() && !alp_TraderMenu)
		{
			SetBuyMenu();
		}
		if (IsSellMenu())
		{
			SetSellMenu();
		}

		return alp_TraderMenu;
	}

	int GetCount(string name, int npcID )
	{
		alpNPCtraderStock stock = alp_TraderStockMapped.Get(	npcID );
		
		int count = stock.Stock.Get( name );
		return count;
	}
	
	
	
	
	static int AddCount(int npcID, string name, int change  ) 
	{
		int count;
		
		alpNPCtraderStock trader = alp_TraderStockMapped.Get(	npcID );
		if ( trader )
		{	
			map<string,int> stock;
				
			int centralID = trader.CentralStock;
			if ( centralID )
			{
				 stock = GetCentralStockItems(centralID );							
				
			}
			else
			{
				stock = trader.Stock;	
			}			
			
			if ( stock )
			{	
				int current;
				if ( change < 0 )
				{//remove;
					if ( stock.Find( name , current ) )
					{
						count = current + change;
						
						if (count >= 0 )
						{
							stock.Set( name , count );
							return Math.AbsInt( change );
						}					
						else
						{
							stock.Set( name , 0 );
							return current;					
						}
					}
				}
				else
				{
					//cat
					alpTraderCategories cat = GetCategoryByName(name);
					if ( stock.Find( name , current ) )
					{
						count = current + change;
												
						if ( count > cat.StockCap )
						{
							count = cat.StockCap;
						}
						stock.Set( name , count );
						return 0;
					}
					else
					{
						if ( centralID )
						{
							count = change;
													
							if ( count > cat.StockCap )
							{
								count = cat.StockCap;
							}
							stock.Set( name , count );
							return 0;
						}
					}			
				}					
			}	
		}	
		return count;

	}

	array<int> GetStockItems(int id )
	{
		array<int> items;
		alpNPCtraderStock stock = alp_TraderStockMapped.Get(id);
		if ( stock )
		{	
			int centralID = stock.CentralStock;
			if ( centralID )
			{
				map<string,int> centralStock = GetCentralStockItems(centralID );	
				
				if ( centralStock && stock.Stock )
				{
					for( int i = 0; i < stock.Stock.Count();i++)
					{
						int count = centralStock.Get( stock.Stock.GetKey(i) );
						
						stock.Stock.Set( stock.Stock.GetKey(i), count );
					}				
				}			
			}

			items = stock.Stock.GetValueArray();

		}	
		return items;
	}
	
	static map<string,int> GetCentralStockItems(int id )
	{

		map<string,int> stock;
		
		
		if ( !alp_TraderMainStock.Find(id, stock ) )
		{
			string path = ALP_MISSIONS_TRADER_FOLDER + "MainStock_" + id + ".json";
			
			JsonFileLoader< map<string,int>	 >.JsonLoadFile( path, stock );	
			
			if ( ! stock )
			{
				stock = new map<string,int>;
			}		
		
			
			alp_TraderMainStock.Set( id , stock ) ;
		}
		
		return stock;
				
	}
		
	int GetCurrency()
	{
		alpNPCtraderStock stock = alp_TraderStockMapped.Get(	alp_NPC_ID );
		
		int currency = stock.CurrencyID;
		return currency;
	}
	alpNPCtraderStock GetCurrentTrader()
	{
		alpNPCtraderStock stock = alp_TraderStockMapped.Get(	alp_NPC_ID );

		return stock;
	}		
		
	int GetTraderBalance(PlayerBase player)
	{
		int balance;
		
		alpNPCtraderStock stock = alp_TraderStockMapped.Get( player.GetRP().GetCart().GetNPCid() );
		
		if ( stock )
		{
			balance = stock.Cash;
		}
		
		return balance;
	}
	
	static void SaveStock(int stockID)
	{
		alpNPCtraderStock stock = alp_TraderStockMapped.Get( stockID );
		
		if ( stock )
		{
			string path = ALP_MISSIONS_TRADER_FOLDER + "Stock_" + stockID + ".json";
			JsonFileLoader< alpNPCtraderStock	 >.JsonSaveFile( path, stock );
		}
	}

	static void SaveMainStock(int stockID)
	{
		map<string,int> stock = alp_TraderMainStock.Get( stockID );
		
		if ( stock )
		{
			string path = ALP_MISSIONS_TRADER_FOLDER + "MainStock_" + stockID + ".json";
			JsonFileLoader< map<string,int>	 >.JsonSaveFile( path, stock );	
		}
	}	
		
	static bool AddBalanceTrader(int stockID, int change)
	{
		alpNPCtraderStock stock = alp_TraderStockMapped.Get( stockID );
		
		if ( stock )
		{
			int balance = stock.Cash;
			if (  ( change < 0 ) ||  ( balance < ( int.MAX - change ) ) )
			{
				balance += change;
				
				if ( balance < 0 )
				{					
					stock.Cash = 0;
				}
				else
				{
					stock.Cash = balance;
				}
			}			
			
			SaveStock(stockID);
			
			if ( stock.CentralStock )
			{
				SaveMainStock( stock.CentralStock );
			}
			
			return true;	
		}
		return false;						
	}
	
	void SetNPC( int id )
	{
		alp_TraderMenu = null;
		alp_NPC_ID = id;
		
		//set fees
		SetNPCfees(id);
	}
	
	void SetNPCfees(int id)
	{}
	
	void SetSellMenu()
	{
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		alpNPCtraderStock stock = alp_TraderStockMapped.Get( alp_NPC_ID );
		alp_TraderMenu	= new alpMenuCategory();
		
		alp_TraderDataIndexed = new map<int,ref array< ref alpProductCard>>;			
		alp_TraderData	= new array<ref alpProductCard>;		
		
		
		map<string, ref map<string, ref alpTraderItem>> categories = player.GetRP().GetCart().GetItemsToSell();
		
		
		if ( categories && stock)
		{
			for ( int c = 0; c < categories.Count();c++)
			{
				
				map<string, ref alpTraderItem> items = categories.GetElement(c);
				
				if ( items )
				{
					for ( int i = 0; i < items.Count();i++)
					{
						alpTraderItem item = items.GetElement(i);
						int inStock;
						string className = item.GetType();		
						alpTraderItemConfig config = GetTraderItemConfig( className );	
						if ( config && stock.Stock.Find( className, inStock) )
						{									
							alpMenuCategory menu1 = alp_TraderMenu.AddSubMenu(	item.Group, c );
							alpMenuCategory menu2 = menu1.AddSubMenu(	item.Category, c );			
							alpMenuCategory menu3 = menu2.AddSubMenu(	item.Subcategory, c );		
							alpProductCard productCard = new alpProductCard( className, config, item.GetStock(), item.GetItem() );							
							//not sorted
							alp_TraderData.Insert( productCard );
							//sorted
							array< ref alpProductCard> cat;			
							if (!alp_TraderDataIndexed.Find(c, cat))
							{
								cat = new array< ref alpProductCard>;
								alp_TraderDataIndexed.Insert( c, cat);				
							}
							cat.Insert ( productCard );									
						}
					}

				}
			
			}			
		}
	

	}	
	
	
	void SetBuyMenu()
	{
		alpNPCtraderStock stock = alp_TraderStockMapped.Get( alp_NPC_ID );
		alp_TraderMenu	= new alpMenuCategory();
		
		alp_TraderDataIndexed = new map<int,ref array< ref alpProductCard>>;			
		alp_TraderData	= new array<ref alpProductCard>;		
		
	
		if ( stock )
		{
			for ( int i = 0; i < stock.Stock.Count();i++)
			{
				
				string className = stock.Stock.GetKey(i);
				int instock = stock.Stock.GetElement(i);
				
				//verify if the item exists
				if ( GetGame().IsKindOf( className , "Inventory_Base") || GetGame().IsKindOf( className , "CarScript") || GetGame().IsKindOf( className , "Magazine_Base") || GetGame().IsKindOf( className , "Weapon_Base") )
				{
					
					alpTraderItemConfig config = GetTraderItemConfig( className );
					
					if ( config )
					{
						alpTraderCategories category = alp_CategoriesMapped.Get( config.CategoryID );
						
						if ( category )
						{
							int indexedCategory;
							alpMenuCategory menu1 = alp_TraderMenu.AddSubMenu(	category.Groups, config.CategoryID );
							alpMenuCategory menu2 = menu1.AddSubMenu(	category.Category, config.CategoryID );		
							alpMenuCategory menu3 = menu2.AddSubMenu(	category.SubCategory, config.CategoryID );		
							indexedCategory = menu3.GetCategoryID();	
							
							//hotfix for same menu labels
							
												
							alpProductCard productCard = new alpProductCard( className, config );			

							//not sorted
							alp_TraderData.Insert( productCard );
							//sorted
							array< ref alpProductCard> cat;			
							if (!alp_TraderDataIndexed.Find(indexedCategory, cat))
							{
								cat = new array< ref alpProductCard>;
								alp_TraderDataIndexed.Insert( indexedCategory , cat);				
							}
							cat.Insert ( productCard );						
						}
					} 					
				}
				
			}			
		}		

	}

	array<ref alpProductCard>  GetTraderData(int index = -1)
	{
		if (index < 0)
			return alp_TraderData;
		return alp_TraderDataIndexed.Get( index );
	}		
			
	int GetPrice(alpTraderItemConfig config, EntityAI ent = null)
	{
		return config.Price;		
	}	
	
	
	void alpTraderCoreBase(map<int, ref alpMission> missions)
	{
		
		
		//alp_AllItemsByName = new map<string,autoptr alpTraderItemConfig >;
		
		
		
		if ( GetGame().IsClient() )
		{
			ReadCategories();
			
			alp_ReservedItem = new array<EntityAI>;
																
		}
		if ( GetGame().IsServer() )
		{
			
			//user overides
			JsonFileLoader< array<ref alpTraderCategories>	 >.JsonLoadFile( ALP_MISSIONS_TRADER_CATEGORIES_OVERRIDE, alp_CategoriesOverride );	
			
			JsonFileLoader< array<autoptr alpTraderItemConfig>	 >.JsonLoadFile( ALP_MISSIONS_TRADER_ITEMS_OVERRIDE, alp_ItemsOverride );			
			
			ReadCategories();
			
			if ( missions )
			{
				
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.InitTraders,1000,false,missions);
				//InitTraders( missions );
			}
			
			
		}
		
		InitCore();
	}
	
	void InitCore(){}

	
	bool IsBuyMenu()
	{
		return TRADER_ACTION_BUY;
	}
	bool IsSellMenu()
	{
		return !TRADER_ACTION_BUY;
	}	
	
	bool CanPayByCard()
	{
		alpNPCtraderStock trader =	alp_TraderStockMapped.Get( alp_NPC_ID );
		
		if ( trader )
		{
			bool setting = trader.EnabledInteractions;			
			return setting == 0 || setting & alpNPC_AVAILABLE_MENU.BANK;						
		}
		return false;
	}
	
		
	void UpdateStock(int id, array<int> numbers)
	{
		//alpTraderCoreBase
		alpNPCtraderStock stock = alp_TraderStockMapped.Get(id);

		if ( stock && numbers )
		{	
			for (int i = 0 ; i < numbers.Count() ; i++)
			{
				string name = stock.Stock.GetKey(i);
				int count = stock.Stock.GetElement(i);

				stock.Stock.Set( name , numbers.Get(i) );

				
			}
	
		}		
	}
	
	
	array<autoptr alpNPCtraderStock> GetStocks(ref array<int> stockID )
	{
		array<autoptr alpNPCtraderStock>  stocks = new array<autoptr alpNPCtraderStock> ;
		
		stockID = new array<int>;
		
		for (int i = 0; i < alp_TraderStockMapped.Count() ; i++)
		{
			int id = alp_TraderStockMapped.GetKey( i );
			alpNPCtraderStock stock = alp_TraderStockMapped.GetElement( i );
			
			stockID.Insert( id );
			stocks.Insert( stock );
		}

		return stocks;
	}
	
	
	void ReadCategories()
	{
		
		if ( GetGame().IsServer() )
		{
			PrintDefaultCategories();
		}
		
		//alp_CategoriesMapped = new map<int, ref alpTraderCategories>;
		
		array<ref alpTraderCategories>	categories = new array<ref alpTraderCategories>;
		
		string path = "CfgTraders Categories";  //ALP_MISSIONS_TRADER_CATEGORIES_DEFAULT
		
		for(int i = 0; i < GetGame().ConfigGetChildrenCount( path ); i++)
		{
			string className;
			if (!GetGame().ConfigGetChildName(path, i, className))
				continue;	

			
			alpTraderCategories cat = alpTraderCategories.GetCategory(  path + " " + className);
			
			categories.Insert(cat);
		
			alp_CategoriesMapped.Set( cat.CategoryID, cat );
			
		}
		//userUpdate
		if ( alp_CategoriesOverride )
		{
			for ( int x = 0; x < alp_CategoriesOverride.Count();x++)
			{
				alpTraderCategories catUser = alp_CategoriesOverride.Get( x );
				
				alp_CategoriesMapped.Set( catUser.CategoryID, catUser );
			}
		}

		if ( GetGame().IsServer() )
		{//INIT USER INPUT 
			//TO DO
			JsonFileLoader< array<ref alpTraderCategories>	 >.JsonSaveFile( ALP_MISSIONS_TRADER_CATEGORIES_DEFAULT, categories );		
		}
	}
	
	static void PrintDefaultCategories()
	{
		if (FileExist(ALP_MISSIONS_TRADER_CATEGORIES_DEFAULT)) 
			return;
		
		array<ref alpTraderCategories>	categories = new array<ref alpTraderCategories>;
		string path = "CfgTraders Categories";  //ALP_MISSIONS_TRADER_CATEGORIES_DEFAULT
		
		for(int i = 0; i < GetGame().ConfigGetChildrenCount( path ); i++)
		{
			string className;
			if (!GetGame().ConfigGetChildName(path, i, className))
				continue;	

			
			alpTraderCategories cat = alpTraderCategories.GetCategory(  path + " " + className);
			
			categories.Insert(cat);
	
		}	
		JsonFileLoader< array<ref alpTraderCategories>	 >.JsonSaveFile( ALP_MISSIONS_TRADER_CATEGORIES_DEFAULT, categories );
	}		
	
	
	
	void InitTraders(map<int, ref alpMission> missions)
	{
				
		//alp_TraderStockMapped = new map<int,autoptr alpNPCtraderStock>;
		//set all traders and its stock warehauses
		if ( missions )
		{
			array<ref alpMissionAddNPC>	npcs;
			foreach(alpMission mission : missions)
			{
				if (mission.GetType() == ALP_MISSIONTYPEID.trader || mission.GetType() == ALP_MISSIONTYPEID.savemerchants)
				{
					npcs = mission.GetTemplate().NPC;
					
					if ( npcs )
					{
						foreach ( alpMissionAddNPC npc : npcs )
						{
							InitTrader(npc);
						}
					}
					npcs = mission.GetTemplate().NPCdynamic;
					if ( npcs )
					{
						foreach ( alpMissionAddNPC npc2 : npcs )
						{
							InitTrader(npc2);
						}
					}					
				}
				
			}		
		
		}
	
	}
	
	void InitTrader(alpMissionAddNPC npc)
	{
		if ( npc.StockID > 0 )
		{//trader
			int stockid = npc.StockID;
			string path = ALP_MISSIONS_TRADER_FOLDER + "Stock_" + stockid + ".json";
			//overim existenci souboru a pripadne vytvorim
			alpNPCtraderStock trader;
			
			if ( FileExist(path))
			{
				JsonFileLoader< alpNPCtraderStock	 >.JsonLoadFile( path, trader );	
				
				
				if ( trader.CentralStock )
				{
					string path2 = ALP_MISSIONS_TRADER_FOLDER + "MainStock_" + trader.CentralStock + ".json";
					if (!FileExist(path2))
					{
						CreateMainStock( trader );
					}
					else
					{
						UpdateMainStock( trader );
					}						
					
				}				
			}
			else
			{//soubor nexistuje vytvorim
				trader = new alpNPCtraderStock();
				trader.CurrencyID = npc.CurrencyID;
				trader.EnabledInteractions = npc.EnabledInteractions;
				trader.CentralStock = npc.CentralStockID;
													
				SetDefaultItems( trader, npc.AvailableGoodsByTag  );
				
				if ( trader.CentralStock )
				{
					CreateMainStock( trader );
				}
				
				JsonFileLoader< alpNPCtraderStock	 >.JsonSaveFile( path, trader );
			}
			SortMap( trader);
						
			
			//add trader balance to Global Bank
			alpBANK.AddBankCapital( trader.CurrencyID, trader.Cash, false );
			alp_TraderStockMapped.Set( stockid, trader );
		}	
	}
	void UpdateMainStock( alpNPCtraderStock trader )
	{
		string path = ALP_MISSIONS_TRADER_FOLDER + "MainStock_" + trader.CentralStock + ".json";
		
		
		map<string,int> stock;
		
		
		if ( !alp_TraderMainStock.Find( trader.CentralStock, stock ) )
		{
			JsonFileLoader< map<string,int>	 >.JsonLoadFile( path, stock );	
			
			if ( ! stock )
			{
				stock = new map<string,int>;
			}		
		
			alp_TraderMainStock.Set( trader.CentralStock , stock ) ;
		}
		

		for (int i = 0; i < trader.Stock.Count();i++)
		{
			int value;
			if ( !stock.Find( trader.Stock.GetKey(i), value ) )
			{
				stock.Set( trader.Stock.GetKey(i), trader.Stock.GetElement(i) );
			}
			
			
		}
		
		JsonFileLoader< map<string,int>	 >.JsonSaveFile( path, stock );	
				
	}											
	void CreateMainStock( alpNPCtraderStock trader )
	{
		string path = ALP_MISSIONS_TRADER_FOLDER + "MainStock_" + trader.CentralStock + ".json";
		
		
		
		map<string,int> stock;
		
		
		if ( !alp_TraderMainStock.Find( trader.CentralStock, stock ) )
		{
			JsonFileLoader< map<string,int>	 >.JsonLoadFile( path, stock );	
			
			if ( ! stock )
			{
				stock = new map<string,int>;
			}		
		
			
			alp_TraderMainStock.Set( trader.CentralStock , stock ) ;
		}
		

		for (int i = 0; i < trader.Stock.Count();i++)
		{
			stock.Set( trader.Stock.GetKey(i), trader.Stock.GetElement(i) );
		}
		
		JsonFileLoader< map<string,int>	 >.JsonSaveFile( path, stock );	
				
	}
	
	static void SortMap( alpNPCtraderStock stock)
	{
		map<string,int> sorted = new map<string,int>;
		array<string> labels = stock.Stock.GetKeyArray();
		
		labels.Sort();
		
		for (int i = 0; i < labels.Count();i++)
		{		
			string name = labels.Get(i);
			int count = stock.Stock.Get(name);
			sorted.Insert( name, count );
		}
		stock.Stock = sorted;
		
	}	
	void SetDefaultItems(ref alpNPCtraderStock trader, array<string> tags )
	{
		array< autoptr alpTraderItemConfig > items = 	GetTradableItems(tags);
		
		
		
		trader.Stock = new map<string,int>;
		
		for (int i = 0; i < items.Count(); i++)
		{
			alpTraderItemConfig item = items.Get(i);
			
			alpTraderCategories cat = GetCategory( item.CategoryID );

			if ( cat )
			{
				//Print(item.Name);
				trader.Stock.Set( item.Name,cat.RestockCap );
			}						
		}
	}	
	array< autoptr alpTraderItemConfig > GetTradableItems(array<string> tags = null)
	{
		if (!alp_AllItemsByTag )
		{//read all itmes

			InitItemList();
		}
		
		array< autoptr alpTraderItemConfig > items = new array< autoptr alpTraderItemConfig >;
		
		
		for (int i = 0; i < alp_AllItemsByTag.Count(); i++ )
		{
			string tag =  alp_AllItemsByTag.GetKey(i);

			if ( !tags || tags.Count() == 0 || tags.Find( tag ) >= 0 )
			{

				for( int x = 0; x < alp_AllItemsByTag.GetElement(i).Count(); x++ )
				{
					items.Insert( alp_AllItemsByTag.GetElement(i).Get(x) );
				}
			}
		}		
		
		return items;
	}		
	
	static alpTraderCategories GetCategory( int category )
	{
		return alp_CategoriesMapped.Get( category);
	}		
	
	void InitItemList()
	{
		alp_AllItemsByTag = new map<string,ref array< autoptr alpTraderItemConfig >>;
		
		int i, catID, count, scope;
		alpTraderCategories category;	
		string tag;			
		array<autoptr alpTraderItemConfig> items;
		array<autoptr alpTraderItemConfig> itemsTemp = new array<autoptr alpTraderItemConfig>;;
		alpTraderItemConfig itm;
		CEItemProfile profile;
		string className, subclass_path;
		
		//VEHICLES
		for(i = 0; i < GetGame().ConfigGetChildrenCount( CFG_VEHICLESPATH ); i++)
		{			
			if (!GetGame().ConfigGetChildName(CFG_VEHICLESPATH, i, className))
				continue;	
		
			if ( GetGame().IsKindOf( className , "Inventory_Base") || GetGame().IsKindOf( className , "CarScript") )
			{			
				subclass_path = "CfgVehicles " + className + " scope";		
				scope = GetGame().ConfigGetInt(subclass_path);
				
				if ( scope == 2 )
				{	
					ItemBase item = ItemBase.Cast (GetGame().CreateObject( className , "0 0 0",false,false,false) );
					
					if (item)
					{
						itm = GetTraderItemConfig( className );	
						
						profile = item.GetEconomyProfile();
						
						/*
						if ( profile )
						{
							Print("NAME " + item.GetType() + ", nominal: " + profile.GetNominal() );
						}
						*/
						//if ( profile && !item.IsCorpse() && ( item.IsInherited(alp_CoinRare1) || !item.IsInherited(alp_Cash) )   && (    ( profile.GetNominal() > 0 || item.IsPeltBase() || ( item.IsMeat() || item.CanBeCooked() ) || ( item.IsFood() ) || item.IsInherited( CarWheel ) || item.IsInherited( CarDoor ) || item.IsWoodBase() || item.IsInherited( alp_Debitcard ) ) )  )
						if ( profile && !item.IsCorpse() && ( item.IsInherited(alp_CoinRare1) || !item.IsInherited(alp_Cash) )   &&    ( profile.GetNominal() > 0 || item.IsPeltBase() ||  item.IsMeat() ||  item.IsFood() || item.IsInherited( CarWheel ) || item.IsInherited( CarDoor ) || item.IsWoodBase() || item.IsInherited( alp_Debitcard ) )  )
						{

							catID = itm.CategoryID;
							category = GetCategory( catID );	
							if ( category ) {
								tag = category.Tag;	
								count = category.RestockCap;
	
								if (!alp_AllItemsByTag.Find( tag , items))
								{
									items = new array<autoptr alpTraderItemConfig>;
									
									alp_AllItemsByTag.Set( tag, items);
								}
	
								items.Insert( itm );
								itemsTemp.Insert( itm );							
							}

							//Print( className + " MIN: " + profile.GetMin() + " NOMINAL: " + profile.GetNominal() + " PRICE: " + ent.GetTraderItemConfig().Price );
						}
						
						GetGame().ObjectDelete( item );
						continue;
					}
					Transport car = Transport.Cast (GetGame().CreateObject( className , "0 0 0",false,false,false) );
					
					if (car)
					{
						itm = GetTraderItemConfig( className );	

						catID = itm.CategoryID;
						category = GetCategory( catID );	
						tag = category.Tag;	
						count = category.RestockCap;
				
						if (!alp_AllItemsByTag.Find( tag , items))
						{
							items = new array<autoptr alpTraderItemConfig>;
							
							alp_AllItemsByTag.Set( tag, items);
						}							
						
						items.Insert( itm );
						itemsTemp.Insert( itm );
						GetGame().ObjectDelete( car );
					}											
				}				
			}
		}	
		
		//ammo

		for(i = 0; i < GetGame().ConfigGetChildrenCount( CFG_AMMO ); i++)
		{

			if (!GetGame().ConfigGetChildName(CFG_AMMO, i, className))
				continue;	

			
			if ( GetGame().IsKindOf( className , "Ammunition_Base")  )
			{
				
				subclass_path = "CfgAmmo " + className + " scope";		
				scope = GetGame().ConfigGetInt(subclass_path);
				
				if ( scope == 2 )
				{									
					Ammunition_Base ammo = Ammunition_Base.Cast (GetGame().CreateObject( className , "0 0 0",false,false,false) );
					
					if (ammo)
					{
						itm = GetTraderItemConfig( className );		
						profile = ammo.GetEconomyProfile();
						
						if ( profile && profile.GetNominal() > 0 )
						{
							catID = ammo.GetTraderItemConfig().CategoryID;
							category = GetCategory( catID );	
							tag = category.Tag;	
							count = category.RestockCap;
							
							if (!alp_AllItemsByTag.Find( tag , items))
							{
								items = new array<autoptr alpTraderItemConfig>;
								alp_AllItemsByTag.Set( tag, items);	
							}
							
							items.Insert( itm );
							itemsTemp.Insert( itm );
							
						}					
						GetGame().ObjectDelete( ammo );
					}	
					
				}				
			}
		}	
	
		//MAGAZINES
		for(i = 0; i < GetGame().ConfigGetChildrenCount( CFG_MAGAZINESPATH ); i++)
		{
			className;
			if (!GetGame().ConfigGetChildName(CFG_MAGAZINESPATH, i, className))
				continue;	
			
			if ( GetGame().IsKindOf( className , "Magazine_Base")  )
			{			
				subclass_path = "CfgMagazines " + className + " scope";		
				scope = GetGame().ConfigGetInt(subclass_path);
				
				if ( scope == 2 )
				{	
								
					Magazine_Base mag = Magazine_Base.Cast (GetGame().CreateObject( className , "0 0 0",false,false,false) );
					
					if (mag)
					{
						itm = GetTraderItemConfig( className );	
						profile = mag.GetEconomyProfile();
						
						if ( profile && profile.GetNominal() > 0 )
						{
							catID = mag.GetTraderItemConfig().CategoryID;
							category = GetCategory( catID );	
							tag = category.Tag;	
							count = category.RestockCap;
							
							if (!alp_AllItemsByTag.Find( tag , items))
							{
								items = new array<autoptr alpTraderItemConfig>;
								alp_AllItemsByTag.Set( tag, items);	
							}

							
							items.Insert( itm );
							itemsTemp.Insert( itm );
						}
						
						GetGame().ObjectDelete( mag );

					}	
											
				}				
			}
		}	
		//weapons
		for(i = 0; i < GetGame().ConfigGetChildrenCount( CFG_WEAPONSPATH ); i++)
		{
			className;
			if (!GetGame().ConfigGetChildName(CFG_WEAPONSPATH, i, className))
				continue;	

			
			if ( GetGame().IsKindOf( className , "Weapon_Base")  )
			{
				
				subclass_path = "CfgWeapons " + className + " scope";		
				scope = GetGame().ConfigGetInt(subclass_path);
				
				if ( scope == 2 )
				{										
					Weapon_Base wep = Weapon_Base.Cast (GetGame().CreateObject( className , "0 0 0",false,false,false) );
					
					if (wep)
					{
						itm = GetTraderItemConfig( className );	
						profile = wep.GetEconomyProfile();
						
						if ( profile && profile.GetNominal() > 0 )
						{
							catID = wep.GetTraderItemConfig().CategoryID;
							category = GetCategory( catID );	
							tag = category.Tag;	
							count = category.RestockCap;
							
							if (!alp_AllItemsByTag.Find( tag , items))
							{
								items = new array<autoptr alpTraderItemConfig>;
								alp_AllItemsByTag.Set( tag, items);	
							}

							
							items.Insert( itm );
							itemsTemp.Insert( itm );
						}
						
						GetGame().ObjectDelete( wep );;
					}
											
				}				
			}
		}
		if ( GetGame().IsServer() )
		{//INIT USER INPUT 
			//TO DO
			JsonFileLoader< array<autoptr alpTraderItemConfig> >.JsonSaveFile( ALP_MISSIONS_TRADER_ITEMS_DEFAULT, itemsTemp );		
		}		
	
	}	
	
		
	
	static alpTraderCategories GetCategoryByName( string type )
	{
		alpTraderItemConfig config =  GetTraderItemConfig( type);
		
		if ( !config )
			return null;
		
		int id = config.CategoryID;
	
		return GetCategory(id);
	}
	
	static alpTraderItemConfig GetTraderItemConfig(string className)
	{

		if (!alp_AllowedItems || ( GetGame().IsClient() && alp_AllowedItems.Find( className ) < 0 ) )
		{
			
			return null;
		}


		alpTraderItemConfig itemconfig;
			
						
		if ( alp_AllItemsByName && alp_AllItemsByName.Find( className , itemconfig) )
		{

			return itemconfig;
		}
		else
		{
			itemconfig = null;
		} 

			
		bool canBuy, canSell;
		int category, price, requiredReputation;
		float ratioSelling,ratioBuying;
		
		string config;
		
		if ( GetGame().IsKindOf( className , "Weapon_Base")  )
		{
			config = CFG_WEAPONSPATH + " ";
		}
		else if ( GetGame().IsKindOf( className , "Magazine_Base")  )
		{
			config = CFG_MAGAZINESPATH + " ";
		}
		else if ( GetGame().IsKindOf( className , "DefaultAmmo")  )
		{
			config = CFG_AMMO + " ";
		}			
		else
		{
			config = CFG_VEHICLESPATH + " ";
		}			
		
		string subclass_path = config + className + " TraderItem CategoryID";	
		category = GetGame().ConfigGetInt(subclass_path);

		subclass_path = config + className + " TraderItem Price";	
		price = GetGame().ConfigGetInt(subclass_path);
		
		subclass_path = config + className + " TraderItem CanBuy";	
		canBuy = GetGame().ConfigGetInt(subclass_path);
		
		subclass_path = config + className + " TraderItem CanSell";	
		canSell = GetGame().ConfigGetInt(subclass_path);						
		
		subclass_path = config + className + " TraderItem RequiredReputation";	
		requiredReputation = GetGame().ConfigGetInt(subclass_path);		
		
		subclass_path = config + className + " TraderItem SellingBonusReputationRatio";	
		ratioSelling = GetGame().ConfigGetFloat(subclass_path);			
		
		subclass_path = config + className + " TraderItem BuyingPenaltyReputationRatio";	
		ratioBuying = GetGame().ConfigGetFloat(subclass_path);		
		
		//check for overrides
		
		if ( alp_ItemsOverride && alp_ItemsOverride.Count() > 0) 
		{//server side

			foreach (alpTraderItemConfig itm : alp_ItemsOverride )
			{
				if ( itm.Name == className )
				{
					itemconfig = itm;
				}
			}
		}

		if (! itemconfig )
		{

			itemconfig = new alpTraderItemConfig( className, category, price,canBuy ,canSell, requiredReputation, ratioSelling, ratioBuying);		
		}
		
		alp_AllItemsByName.Set( className , itemconfig);
			
		return itemconfig;
	}		

	array<string> GetCarAttachments(string name)
	{
		array<string> atts;
		string attachment;
//Print("HLEDAM " + name );
		if ( GetGame().IsServer() )
		{
			map<string,ref array<string>> carConfig;
			
			JsonFileLoader<map<string,ref array<string>>>.JsonLoadFile( ALP_MISSIONS_TRADER_FOLDER + "CarConfigurator.json", carConfig );

			array<string> temp;
			
			if (carConfig && carConfig.Find( name, temp ) )
			{
//Print("NALEZENO " + temp );				
				atts = new array<string>;
				for (int i = 0; i < temp.Count(); i++ )
				{
					attachment = temp.Get(i);
					atts.Insert( attachment );			
				}				
			}
		}
		return atts;
	}
		
	
	void Restocking()
	{


		if (alp_TraderStockMapped)
		{
			for (int i; i < alp_TraderStockMapped.Count();i++)
			{
				alpNPCtraderStock trader = alp_TraderStockMapped.GetElement(i);
				int stockId = alp_TraderStockMapped.GetKey(i);
				
				//cash
				int cash = trader.Cash;
				int add_cash = trader.CashAddingPerRestock;
				int cash_optimal = trader.CashOptimal;
								
				if ( cash < cash_optimal )
				{
					cash += add_cash;
					
					if ( cash > cash_optimal)
						cash = cash_optimal;
					
					trader.Cash = cash;				
				}
				
				//stock
				if ( trader.CentralStock ){
					SaveStock( stockId);
					continue;
				}
				
				for (int s = 0; s < trader.Stock.Count(); s++)
				{
					string type = trader.Stock.GetKey(s);
					int count  = trader.Stock.GetElement(s);
					
					alpTraderCategories category = GetCategoryByName( type );
					
					if ( category)
					{
						int restock =  category.Restock;
						int stockCap = category.RestockCap;
						
						if ( restock > 0 ) {
							if ( count < stockCap){
								count += restock;								
								if ( count > stockCap){
									count = stockCap;	
								}
								trader.Stock.Set( type, count );						
							}							
						} else if ( restock < 0 ) {
							if ( count > stockCap){
								count += restock;								
								if ( count < stockCap){
									count = stockCap;	
								}
								trader.Stock.Set( type, count );						
							}								
						}
						

					}
				}
				//save changes			
				SaveStock( stockId);				
			}

		}
		
		RestockingCentralStock();
	}		
	void RestockingCentralStock()
	{

		if (alp_TraderMainStock)
		{
			for (int i; i < alp_TraderMainStock.Count();i++)
			{
				int stockId = alp_TraderMainStock.GetKey(i);
				
				map<string,int> stock = alp_TraderMainStock.GetElement(i);
				//stock
				
				if ( stock )
				{
					for (int s = 0; s < stock.Count(); s++)
					{
						string type = stock.GetKey(s);
						int count  = stock.GetElement(s);
						
						alpTraderCategories category = GetCategoryByName( type );
						
						if ( category)
						{
							int restock =  category.Restock;
							int stockCap = category.RestockCap;
							
							
							if ( restock > 0 ) {
								if ( count < stockCap){
									count += restock;								
									if ( count > stockCap){
										count = stockCap;	
									}
									alp_TraderMainStock.GetElement(i).Set( type, count );						
								}							
							} else if ( restock < 0 ) {
								if ( count > stockCap){
									count += restock;								
									if ( count < stockCap){
										count = stockCap;	
									}
									alp_TraderMainStock.GetElement(i).Set( type, count );					
								}								
							}																				
						}
					}								
				}

				//save changes			
				SaveMainStock( stockId);				
			}
		
		}

	}		
	
	static void PrintMagazines()
	{
		//PrintCategories();
		Print("-------------- PRINT MAGAZINES -----------------");
		for(int i = 0; i < GetGame().ConfigGetChildrenCount( CFG_MAGAZINESPATH ); i++)
		{
			string className;
			if (!GetGame().ConfigGetChildName(CFG_MAGAZINESPATH, i, className))
				continue;	

			string subclass_path = "CfgMagazines " + className + " scope";		
			int scope = GetGame().ConfigGetInt(subclass_path);
			
			if ( GetGame().IsKindOf( className , "Magazine_Base") &&  !className.Contains("Placing" ) )
			{
				
				
				subclass_path = "CfgMagazines " + className;
				
				TStringArray pokus = new TStringArray;
				GetGame().ConfigGetFullPath(subclass_path, pokus);		
				
				if ( pokus && pokus.Count()> 1 )
				{
		
					//if (!pokus.Get(1).Contains( "Base" ) ||  pokus.Get(1).Contains( "Inventory_Base" ) ||  pokus.Get(1).Contains( "Container_Base" ) ||  pokus.Get(1).Contains( "WorldContainer_Base" )||  pokus.Get(1).Contains( "Powered_Base" ) ||  pokus.Get(1).Contains( "Edible_Base" ) ||  pokus.Get(1).Contains( "Trap_Base" )||  pokus.Get(1).Contains( "Grenade_Base" ) ||  pokus.Get(1).Contains( "Book_Base" )  ||  pokus.Get(1).Contains( "FishingRod_Base" )||  pokus.Get(1).Contains( "Clothing_Base" ) ||  pokus.Get(1).Contains( "Switchable_Base" )  ||  pokus.Get(1).Contains( "Box_Base" ) ||  pokus.Get(1).Contains( "Bottle_Base" )  )					
					{
						
						Print(pokus.Get(0) + ";" + pokus.Get(1) + ";" + alpUF.GetDisplayName( pokus.Get(0) ) );
					}
  					
				}
				else
				{
					Print(className + ";" + ";" );
				}					
			
			}			
	
		}		
	}
	static void PrintWeapons()
	{
		//PrintCategories();
		Print("-------------- PRINT WEAPONS -----------------");
		for(int i = 0; i < GetGame().ConfigGetChildrenCount( CFG_WEAPONSPATH ); i++)
		{
			string className;
			if (!GetGame().ConfigGetChildName(CFG_WEAPONSPATH, i, className))
				continue;	

			string subclass_path = "CfgWeapons " + className + " scope";		
			int scope = GetGame().ConfigGetInt(subclass_path);
			
			if ( GetGame().IsKindOf( className , "Weapon_Base") &&  !className.Contains("Placing" ) )
			{
				
				
				subclass_path = "CfgWeapons " + className;
				
				TStringArray pokus = new TStringArray;
				GetGame().ConfigGetFullPath(subclass_path, pokus);		
				
				if ( pokus && pokus.Count()> 1 )
				{
		
					//if (!pokus.Get(1).Contains( "Base" ) ||  pokus.Get(1).Contains( "Inventory_Base" ) ||  pokus.Get(1).Contains( "Container_Base" ) ||  pokus.Get(1).Contains( "WorldContainer_Base" )||  pokus.Get(1).Contains( "Powered_Base" ) ||  pokus.Get(1).Contains( "Edible_Base" ) ||  pokus.Get(1).Contains( "Trap_Base" )||  pokus.Get(1).Contains( "Grenade_Base" ) ||  pokus.Get(1).Contains( "Book_Base" )  ||  pokus.Get(1).Contains( "FishingRod_Base" )||  pokus.Get(1).Contains( "Clothing_Base" ) ||  pokus.Get(1).Contains( "Switchable_Base" )  ||  pokus.Get(1).Contains( "Box_Base" ) ||  pokus.Get(1).Contains( "Bottle_Base" )  )					
					{
						//Print("class " + pokus.Get(0) + " : " + pokus.Get(1) );
						Print(pokus.Get(0) + ";" + pokus.Get(1) + ";" + alpUF.GetDisplayName( pokus.Get(0) ) );
					}
  					
				}
				else
				{
					Print(className + ";" + ";" );
				}					
			
			}			
	
		}		
	}	
	static void PrintAmmo()
	{
		//PrintCategories();
		Print("-------------- PRINT AMMO -----------------");
		for(int i = 0; i < GetGame().ConfigGetChildrenCount( CFG_AMMO); i++)
		{
			string className;
			if (!GetGame().ConfigGetChildName(CFG_AMMO, i, className))
				continue;	

			string subclass_path = "CfgAmmo " + className + " scope";		
			int scope = GetGame().ConfigGetInt(subclass_path);
			
			if ( GetGame().IsKindOf( className , "DefaultAmmo") &&  !className.Contains("Placing" ) )
			{
				
				
				subclass_path = "CfgAmmo " + className;
				
				TStringArray pokus = new TStringArray;
				GetGame().ConfigGetFullPath(subclass_path, pokus);		
				
				if ( pokus && pokus.Count()> 1 )
				{
		
					//if (!pokus.Get(1).Contains( "Base" ) ||  pokus.Get(1).Contains( "Inventory_Base" ) ||  pokus.Get(1).Contains( "Container_Base" ) ||  pokus.Get(1).Contains( "WorldContainer_Base" )||  pokus.Get(1).Contains( "Powered_Base" ) ||  pokus.Get(1).Contains( "Edible_Base" ) ||  pokus.Get(1).Contains( "Trap_Base" )||  pokus.Get(1).Contains( "Grenade_Base" ) ||  pokus.Get(1).Contains( "Book_Base" )  ||  pokus.Get(1).Contains( "FishingRod_Base" )||  pokus.Get(1).Contains( "Clothing_Base" ) ||  pokus.Get(1).Contains( "Switchable_Base" )  ||  pokus.Get(1).Contains( "Box_Base" ) ||  pokus.Get(1).Contains( "Bottle_Base" )  )					
					{
						Print("class " + pokus.Get(0) + " : " + pokus.Get(1) );
					}
  					
				}
				else
				{
					Print(className + ";" + ";" );
				}					
			
			}			
	
		}		
	}	
	static void PrintItems()
	{
		//PrintCategories();
		Print("-------------- PRINT ITEMS -----------------");
		for(int i = 0; i < GetGame().ConfigGetChildrenCount( CFG_VEHICLESPATH); i++)
		{
			string className;
			if (!GetGame().ConfigGetChildName(CFG_VEHICLESPATH, i, className))
				continue;	

			string subclass_path = "CfgVehicles " + className + " scope";		
			int scope = GetGame().ConfigGetInt(subclass_path);

			if ( GetGame().IsKindOf( className , "Inventory_Base") &&  !className.Contains("Placing" ) )
			{
				
				
				subclass_path = "CfgVehicles " + className;
				
				TStringArray pokus = new TStringArray;
				GetGame().ConfigGetFullPath(subclass_path, pokus);		
				
				if ( pokus && pokus.Count()> 1 )
				{
		
					//if (!pokus.Get(1).Contains( "Base" ) ||  pokus.Get(1).Contains( "Inventory_Base" ) ||  pokus.Get(1).Contains( "Container_Base" ) ||  pokus.Get(1).Contains( "WorldContainer_Base" )||  pokus.Get(1).Contains( "Powered_Base" ) ||  pokus.Get(1).Contains( "Edible_Base" ) ||  pokus.Get(1).Contains( "Trap_Base" )||  pokus.Get(1).Contains( "Grenade_Base" ) ||  pokus.Get(1).Contains( "Book_Base" )  ||  pokus.Get(1).Contains( "FishingRod_Base" )||  pokus.Get(1).Contains( "Clothing_Base" ) ||  pokus.Get(1).Contains( "Switchable_Base" )  ||  pokus.Get(1).Contains( "Box_Base" ) ||  pokus.Get(1).Contains( "Bottle_Base" )  )					
					{
						//Print("class " + pokus.Get(0) + " : " + pokus.Get(1) );
						Print(pokus.Get(0) + ";" + pokus.Get(1) + ";" + alpUF.GetDisplayName( pokus.Get(0) ) );
					}
  					
				}
				else
				{
					Print(className + ";" + ";" );
				}					
			
			}			
	
		}		
	}		
}