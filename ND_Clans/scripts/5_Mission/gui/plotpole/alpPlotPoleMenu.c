
enum PPMENUALP
{
	TAXES,
	ESTATES,
	KEYS,
	FINGERPRINTS,
	LOCKPICKING,
	IMPROVMENTS,
	SETTINGS,
}

class alpPlotPoleMenu extends UIScriptedMenu
{

	int alp_COLOR_SELECTED = ARGB(220,0,0,0);
	int alp_COLOR_UNSELECTED = ARGB(69,0,0,0);
	
	ref array<int> MENUS = {100,200,300,400,500,600,700};
	
	PlayerBase								alp_Player;	

	int 									alp_Balance;
	

	Widget									alp_Head;
	
	ScrollWidget							alp_ScrollWidget;
	
	WrapSpacerWidget						alp_ItemsContainer;
	
			

	
	ref array<ref alpTaxesItem>				alp_TaxesItem;
	ref array<ref alpEstatesItem>			alp_EstatesItem;
	
	ref array<ref alpDefaultItem>			alp_KeysItem;
	ref array<ref alpDefaultItem>			alp_FingerprintsItem;
	ref array<ref alpDefaultItem>			alp_LockpickingItem;
	ref array<ref alpDefaultItem>			alp_ImprovmentsItem;
	ref array<ref alpPermissionItem>		alp_PermissionsItem;
		
	protected Camera						alp_Camera;
	
	//ref array< BuildingBase>				alp_Buildings;
	
	bool 									alp_IsWindowVisible;
	
	int										alp_CurrentMenu = PPMENUALP.TAXES;
	
	float									alp_Volume;
	
	autoptr map<int,string>					alp_CurrencyMapped;
	
	void ~alpPlotPoleMenu()
	{
		
		alp_Player.GetSyncData().RegisterToEnhancedStatsSync(false);
		alp_Player.GetRP().GetCart().ClearCart();
					
		GetND().GetMS().GetTrader().SetValidTraderData( false );
				
		
		if ( alp_Camera)
		{
			GetGame().ObjectDelete( alp_Camera );
			GetGame().SelectPlayer(null,GetGame().GetPlayer());
		}
	
	
		alpBuildingLabels.ClearLabels();
		
		MissionGameplay ms	= MissionGameplay.Cast( GetGame().GetMission() );
		ms.GetHud().Show( true );		
	}

	override Widget Init()
	{	
		Class.CastTo(alp_Player,GetGame().GetPlayer());
		
		
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/TerritoryManagement.layout");
		
		ImageWidget.Cast( layoutRoot.FindAnyWidget("BalanceIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/Images/Cash.paa");
		ImageWidget.Cast( layoutRoot.FindAnyWidget("TimeIcon") ).LoadImageFile(0,"ND_Clans/gui/Images/time.paa");
		ImageWidget.Cast( layoutRoot.FindAnyWidget("TaxesIcon") ).LoadImageFile(0,"ND_Clans/gui/Images/tax.paa");
		ImageWidget.Cast( layoutRoot.FindAnyWidget("EstateIcon") ).LoadImageFile(0,"ND_Clans/gui/Images/estate.paa");	

		alp_Head	= Widget.Cast( layoutRoot.FindAnyWidget("BodyHead") );	
		
		alp_ScrollWidget = ScrollWidget.Cast( layoutRoot.FindAnyWidget("Body") );
				
		alp_ItemsContainer = WrapSpacerWidget.Cast( layoutRoot.FindAnyWidget("Items") );
		
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
		
		GetEstates();	
		InitStatusHead();
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SetCameraView,200);
		
		SetCurrentMenuALP();

		alp_IsWindowVisible = true;		
	
			
		if ( !GetND().GetClans().GetBases().EnableEstateMenus	||  ( alp_Player.GetPlayerID() != alp_Player.alp_PlotPoleManage.alp_OwnerID &&  !alp_Player.alp_PlotPoleManage.HasClanOwnerPermission() ) )
		{
			ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(200) ).Show(false);	
			ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(300) ).Show(false);	
			ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(400) ).Show(false);	
			ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(500) ).Show(false);	
			ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(600) ).Show(false);	
			ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(700) ).Show(false);	//setting	
		}		
		
		if ( alp_Player.GetPlayerID() != alp_Player.alp_PlotPoleManage.alp_OwnerID )
		{
			ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(700) ).Show(false);	//setting
		}	

		return layoutRoot;
	}
	
	void SetUnselectedMenu(int selected){
		for(int i = 0; i < MENUS.Count();i++){
			if ( selected == MENUS.Get(i) ) { 
				ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(MENUS.Get(i) ) ).SetColor( alp_COLOR_SELECTED );		
			} else {
				ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(MENUS.Get(i) ) ).SetColor( alp_COLOR_UNSELECTED );	
			}			
		}	
	}
	
	void SetCurrentMenuALP(){
		switch(alp_CurrentMenu){
			case PPMENUALP.TAXES:{
				SetUnselectedMenu(100);	
				InitTaxes();		
				break;
			}
			case PPMENUALP.ESTATES:{
				SetUnselectedMenu(200);
				InitEstates();		
				break;
			}		
			case PPMENUALP.KEYS:{
				SetUnselectedMenu(300);
				InitKeys();
				break;
			}	
			case PPMENUALP.FINGERPRINTS:{
				SetUnselectedMenu(400);
				InitFingerprints();
				break;
			}	
			case PPMENUALP.LOCKPICKING:{
				SetUnselectedMenu(500);
				InitLockProtection();
				break;
			}							
			case PPMENUALP.IMPROVMENTS:{
				SetUnselectedMenu(600);
				InitImprovments();
				break;
			}	
			case PPMENUALP.SETTINGS:{
				SetUnselectedMenu(700);
				InitPermission();
				break;
			}											
		}	
	
	}	
	
	void GetEstates(){				
		alpBuildingLabels.ClearLabels();		

		array< BuildingBase> budovy = alp_Player.alp_PlotPoleManage.GetBuildingInRadius();

		alp_Volume = 0;		
		for ( int i = 0; i < budovy.Count();i++) {
			BuildingBase b = budovy.Get(i);
			if ( b && b.GetOwnerID() == alp_Player.alp_PlotPoleManage.alp_OwnerID ){
				alp_Volume += b.GetVolumeALP();
			}	
		}
	}
	
	void InitStatusHead(){
		alp_Balance = alp_Player.GetRP().GetCart().GetTotalBalance();
	
		if (alp_Player.alp_PlotPoleManage)
		{
			int radius = alp_Player.alp_PlotPoleManage.alp_Radius;
			int validity = alp_Player.alp_PlotPoleManage.GetDaysRemain();
			
			validity = Math.Clamp( validity, 0, validity );
			
			TextWidget.Cast( layoutRoot.FindAnyWidget("TerritoryValue") ).SetText( radius.ToString() );			
			TextWidget.Cast( layoutRoot.FindAnyWidget("TimeValue") ).SetText( validity.ToString() );		
		}
		
		TextWidget.Cast( layoutRoot.FindAnyWidget("BalanceText") ).SetText( alpUF.NumberToString( alp_Balance, 1 ) + " " + alp_CurrencyMapped.GetElement( alp_Player.GetRP().GetCart().GetCurrencyID() ) );
	}	
	
	void SetCameraView()
	{
		float radius = alp_Player.alp_PlotPoleManage.alp_Radius;	
		if (radius  > 0 )
		{
			vector positionCamera = GetGame().GetPlayer().GetPosition();
			
			
			float distance = radius * 1.20;
			
			positionCamera[0] = positionCamera[0] - distance * 0.10;
			positionCamera[1] = positionCamera[1] + distance;
			positionCamera[2] = positionCamera[2] + distance * 0.10;			
			
			if (!alp_Camera)
				alp_Camera = Camera.Cast( GetGame().CreateObject( "staticcamera", positionCamera , true ) );
			else
				alp_Camera.SetPosition(positionCamera);
			
			alp_Camera.LookAt( GetGame().GetPlayer().GetPosition() );			
			
			alp_Camera.SetActive(true);
			array< BuildingBase> budovy = alp_Player.alp_PlotPoleManage.GetBuildingInRadius();
			for (int i = 0; i < budovy.Count();i++){
				BuildingBase building = budovy.Get(i); 	
				if (building ){
					alpBuildingLabels.AddItem(building.GetWorldID(), building.GetDisplayName() , building.GetPosition() , alp_Player.alp_PlotPoleManage.alp_OwnerID == building.GetOwnerID() );						
				}
			}					
			alpBuildingLabels.SetBorders( radius );		
			
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(alpBuildingLabels.Update,200);
		}		
	}	
	

	void InitTaxes()
	{
		ClearContainer();
		
		alp_Head.AddChild( GetHeadTaxes() );
						
		alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
		float exchange = alpBANK.GetCurrencyRate( trader.CurrencyID );
		
		for (int i = 0; i < GetND().GetClans().GetBases().PlotPoleTaxes.Count(); i++)
		{
			int rank = GetND().GetClans().GetBases().PlotPoleTaxes.Get(i).LevelRequirements;
			int radius = GetND().GetClans().GetBases().PlotPoleTaxes.Get(i).Radius;
			int validity = GetND().GetClans().GetBases().PlotPoleTaxes.Get(i).Validity;
			int price = GetND().GetClans().GetBases().PlotPoleTaxes.Get(i).Tax * exchange;
			
			int estatesTax = alp_Volume * GetND().GetClans().GetBases().BuildingTaxPerCubicMeterPerDay * validity * exchange;
			
			alpTaxesItem item = new alpTaxesItem(alp_Balance, rank, radius, validity, price, estatesTax );
			alp_ItemsContainer.AddChild( item.GetWidget() );
			
			alp_TaxesItem.Insert( 	item );					
		}		
		

	}	
	
	void InitEstates()
	{
		ClearContainer();
		alp_Head.AddChild( GetHeadEstates() );
		
		alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
		float exchange = alpBANK.GetCurrencyRate( trader.CurrencyID );		
		array< BuildingBase> budovy = alp_Player.alp_PlotPoleManage.GetBuildingInRadius();
		if ( budovy )
		{
			int validity = alp_Player.alp_PlotPoleManage.GetDaysRemain();			
			validity = Math.Clamp( validity, 0, validity );
			
			for (int i = 0; i < budovy.Count(); i++)
			{
				alpEstatesItem item = new alpEstatesItem(alp_Balance, validity, budovy.Get(i), exchange );
				alp_ItemsContainer.AddChild( item.GetWidget() );				
				
				alp_EstatesItem.Insert( item );
			}			
		
		}
		
	}
	void InitKeys()
	{
		ClearContainer();
		alp_Head.AddChild( GetHeadDefault( "#STR_alp_HouseKey" ) );	
		array< BuildingBase> budovy = alp_Player.alp_PlotPoleManage.GetBuildingInRadius();
		if ( budovy )
		{
		
			alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
			float exchange = alpBANK.GetCurrencyRate( trader.CurrencyID );				
			
			for (int i = 0; i < budovy.Count(); i++)
			{
				BuildingBase building = budovy.Get(i);
				
				if ( building && building.GetOwnerID() == alp_Player.alp_PlotPoleManage.alp_OwnerID  )
				{//owned  
					
					int price = GetND().GetClans().GetBases().PriceOfHouseKey * building.GetCountOfDoorsALP() * exchange;
										
					alpDefaultItem item = new alpDefaultItem(alp_Balance, price, building);
					alp_ItemsContainer.AddChild( item.GetWidget() );
					alp_KeysItem.Insert( item );
					 				
				}
			}			
		
		}		
	
	}		
	void InitFingerprints()
	{
		ClearContainer();
		alp_Head.AddChild( GetHeadDefault( "#pp_items_fingerprintlock" ) );	
		array< BuildingBase> budovy = alp_Player.alp_PlotPoleManage.GetBuildingInRadius();
		if ( budovy )
		{
			alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
			float exchange = alpBANK.GetCurrencyRate( trader.CurrencyID );				
			
			for (int i = 0; i < budovy.Count(); i++)
			{
				BuildingBase building = budovy.Get(i);
				
				if ( building && building.GetOwnerID() == alp_Player.alp_PlotPoleManage.alp_OwnerID  )
				{//owned  
					int price = GetND().GetClans().GetBases().FingerprintLockValuePerDoor * building.GetCountOfDoorsALP() * exchange;
										
					alpDefaultItem item = new alpDefaultItem(alp_Balance, price, building);
					alp_ItemsContainer.AddChild( item.GetWidget() );
					alp_FingerprintsItem.Insert( item );
					
					if (building.IsEnabledFingerPringLock())
					{
						item.SetSortedIcon();	
					}				 				
				}
			}				
		}			
	}	
	
	void InitLockProtection()
	{
		ClearContainer();
		alp_Head.AddChild( GetHeadDefault( "#pp_items_lockprotection" ) );	
		array< BuildingBase> budovy = alp_Player.alp_PlotPoleManage.GetBuildingInRadius();
		if ( budovy )
		{
		
			alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
			float exchange = alpBANK.GetCurrencyRate( trader.CurrencyID );		
						
			for (int i = 0; i < budovy.Count(); i++)
			{
				BuildingBase building = budovy.Get(i);
				
				if ( building && building.GetOwnerID() == alp_Player.alp_PlotPoleManage.alp_OwnerID ) // || ( building.GetClanID() == alp_Player.alp_PlotPoleManage.alp_ClanID &&  building.GetClanID() != -1 ) )
				{//owned  
					int price = GetND().GetClans().GetBases().LockProtectionValuePerDoor * building.GetCountOfDoorsALP() * exchange;
										
					alpDefaultItem item = new alpDefaultItem(alp_Balance, price, building);
					alp_ItemsContainer.AddChild( item.GetWidget() );
					alp_LockpickingItem.Insert( item );
					
					if (building.HasLockProtection())
					{
						item.SetSortedIcon();	
					}				 				
				}
			}				
		}			
	}	
	
	
	void InitPermission()
	{
		ClearContainer();

		int clanID = alp_Player.GetClanID();
		
		alpClanData clan = alp_Player.GetRP().GetClan();
		
		if ( clanID != -1 && clan)
		{
			
			//head
			alp_Head.AddChild( GetHeadPermissions( clan.Name ) );	
			
			//acces menu
			alpPermissionItem item = new alpPermissionItem(alpCLAN_PERMISSION.CAN_ACCES_TAX_MENU, "#pp_permission_taxes - #pp_title", alp_Player.alp_PlotPoleManage.HasClanOwnerPermission() );
			alp_ItemsContainer.AddChild( item.GetWidget() );
			alp_PermissionsItem.Insert( item );
			
			//placing
			alpPermissionItem item2 = new alpPermissionItem(alpCLAN_PERMISSION.CAN_PLACE, "#pp_permission_placing",alp_Player.alp_PlotPoleManage.CanPlaceObjects() );
			alp_ItemsContainer.AddChild( item2.GetWidget() );			
			alp_PermissionsItem.Insert( item2 );
			
			//fingerprints
			alpPermissionItem item3 = new alpPermissionItem(alpCLAN_PERMISSION.CAN_USE_FINGERPRINTS, "#pp_permission_fingerprints",alp_Player.alp_PlotPoleManage.CanUseFingerPrints() );
			alp_ItemsContainer.AddChild( item3.GetWidget() );	
			alp_PermissionsItem.Insert( item3 );
			
			//fingerprints
			if ( GetND().GetClans().GetSpawn().EnableSpawnInBase )
			{
				alpPermissionItem item4 = new alpPermissionItem(alpCLAN_PERMISSION.CAN_CLAIM_BED, "#pp_permissions_claimbed",alp_Player.alp_PlotPoleManage.CanClaimBed() );
				alp_ItemsContainer.AddChild( item4.GetWidget() );	
				alp_PermissionsItem.Insert( item4 );				
			}
				

		}		
		
		
		
	}		
	void InitImprovments()
	{
		ClearContainer();
		alp_Head.AddChild( GetHeadDefault( "#pp_items_durabledoorsname" ) );	
		array< BuildingBase> budovy = alp_Player.alp_PlotPoleManage.GetBuildingInRadius();
		if ( budovy )
		{
		
			alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
			float exchange = alpBANK.GetCurrencyRate( trader.CurrencyID );				
			
			for (int i = 0; i < budovy.Count(); i++)
			{
				BuildingBase building = budovy.Get(i);
				
				if ( building && building.GetOwnerID() == alp_Player.alp_PlotPoleManage.alp_OwnerID  )
				{//owned  
					int price = GetND().GetClans().GetBases().DurableDoorsValuePerDoor * building.GetCountOfDoorsALP() * exchange;
										
					alpDefaultItem item = new alpDefaultItem(alp_Balance, price, building);
					alp_ItemsContainer.AddChild( item.GetWidget() );
					alp_ImprovmentsItem.Insert( item );
					
					if (building.HasEnhancedDoors())
					{
						item.SetSortedIcon();	
					}				 				
				}
			}				
		}		
	
	}
		
	Widget GetHeadTaxes()
	{
		Widget root  = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/TaxItemHead.layout");	
		return root;
	}
	Widget GetHeadEstates()
	{
		Widget root  = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/EstateHead.layout");	
		ImageWidget.Cast( root.FindAnyWidget("TimeIcon") ).LoadImageFile(0,"ND_Clans/gui/Images/time.paa");
		return root;
	}
	Widget GetHeadDefault(string subject)
	{
		Widget root  = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/defaultHead.layout");	
		TextWidget.Cast( root.FindAnyWidget( "Subject" )).SetText( subject );
		return root;
	}	
	Widget GetHeadPermissions(string subject)
	{
		Widget root  = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/permissionHead.layout");	
		TextWidget.Cast( root.FindAnyWidget( "Subject" )).SetText( subject );
		return root;
	}		
		
	
	void ClearContainer()
	{
		Widget head = alp_Head.GetChildren();
		if (head){
			head.Unlink();
		}
				
		int i;
		if ( alp_TaxesItem ){
			for(i = 0;i < alp_TaxesItem.Count();i++){
				alp_TaxesItem.Get(i).GetWidget().Unlink();
			}
			alp_TaxesItem.Clear();
		}else{
			alp_TaxesItem = new array<ref alpTaxesItem>;
		}	
		if ( alp_EstatesItem ){
			for(i = 0;i < alp_EstatesItem.Count();i++){
				alp_EstatesItem.Get(i).GetWidget().Unlink();
			}
			alp_EstatesItem.Clear();
		}else{
			alp_EstatesItem = new array<ref alpEstatesItem>;
		}	
		if ( alp_KeysItem ){
			for(i = 0;i < alp_KeysItem.Count();i++){
				alp_KeysItem.Get(i).GetWidget().Unlink();
			}
			alp_KeysItem.Clear();
		}else{
			alp_KeysItem = new array<ref alpDefaultItem>;
		}	
		if ( alp_FingerprintsItem ){
			for(i = 0;i < alp_FingerprintsItem.Count();i++){
				alp_FingerprintsItem.Get(i).GetWidget().Unlink();
			}
			alp_FingerprintsItem.Clear();
		}else{
			alp_FingerprintsItem = new array<ref alpDefaultItem>;
		}	
		if ( alp_LockpickingItem ){
			for(i = 0;i < alp_LockpickingItem.Count();i++){
				alp_LockpickingItem.Get(i).GetWidget().Unlink();
			}
			alp_LockpickingItem.Clear();
		}else{
			alp_LockpickingItem = new array<ref alpDefaultItem>;
		}	
		if ( alp_ImprovmentsItem ){
			for(i = 0;i < alp_ImprovmentsItem.Count();i++){
				alp_ImprovmentsItem.Get(i).GetWidget().Unlink();
			}
			alp_ImprovmentsItem.Clear();
		}else{
			alp_ImprovmentsItem = new array<ref alpDefaultItem>;
		}										
		if ( alp_PermissionsItem ){
			for(i = 0;i < alp_PermissionsItem.Count();i++){
				alp_PermissionsItem.Get(i).GetWidget().Unlink();
			}
			alp_PermissionsItem.Clear();
		}else{
			alp_PermissionsItem = new array<ref alpPermissionItem>;
		}			
		alp_ScrollWidget.VScrollToPos(0);
	}		
	
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if ( !GetND().GetMS().GetTrader().IsTraderSet() && alp_IsWindowVisible )
		{
			alp_IsWindowVisible = false;
			layoutRoot.Show(false);	
		}
		if ( GetND().GetMS().GetTrader().IsTraderSet() && !alp_IsWindowVisible )
		{
			alp_IsWindowVisible = true;
			
			GetGame().GetCallQueue( CALL_CATEGORY_GUI ).CallLater( this.UpdateWindow,300);
		}
		
	}		
	void UpdateWindow()
	{
		GetEstates();
		InitStatusHead();

		SetCurrentMenuALP();
		
		SetCameraView();
		
		layoutRoot.Show(true);	
	}	
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		
		if (!super.OnClick(w, x, y, button))
		{			
			switch (w.GetUserID())
			{
				case 1:
				{
					Close();
					return true;	
				}
				case 100://taxes
				{
					alp_CurrentMenu = PPMENUALP.TAXES;
					SetCurrentMenuALP();
					return true;				
				}
				case 200://estates
				{
					alp_CurrentMenu = PPMENUALP.ESTATES;
					SetCurrentMenuALP();
					return true;				
				}
				case 300://keys
				{
					alp_CurrentMenu = PPMENUALP.KEYS;
					SetCurrentMenuALP();
					return true;				
				}		
				case 400://fingerprints
				{
					alp_CurrentMenu = PPMENUALP.FINGERPRINTS;
					SetCurrentMenuALP();
					return true;				
				}							
				case 500://lockpicking
				{
					alp_CurrentMenu = PPMENUALP.LOCKPICKING;
					SetCurrentMenuALP();
					return true;				
				}	
				case 600://improvments
				{
					alp_CurrentMenu = PPMENUALP.IMPROVMENTS;
					SetCurrentMenuALP();
					return true;				
				}	
				case 700://clan settings
				{
					alp_CurrentMenu = PPMENUALP.SETTINGS;
					SetCurrentMenuALP();
					return true;				
				}													
			}
					
			if ( TaxesOnClick(w,x,y,button) || EstatesOnClick(w,x,y,button) || KeysOnClick(w,x,y,button)  || FingerprintsOnClick(w,x,y,button) || LockProtectionOnClick(w,x,y,button) || DurabelDoorsOnClick(w,x,y,button))
			{
				return true;			
			}	
							
			return false;		
		
		}
		else return false;
		
	}	
	 
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{

		if ( alp_PermissionsItem )
		{
			int settings  = alp_Player.alp_PlotPoleManage.alp_ClanPermission;
			for(int i = 0; i < alp_PermissionsItem.Count();i++)
			{		
				alpPermissionItem item = alp_PermissionsItem.Get(i);
				
				if ( item.GetActionBtn() == w )
				{
					if ( item.GetActionBtn().IsChecked() )
					{//set
						settings = settings | item.GetType();
					}
					else
					{//unset
						settings = settings & (~item.GetType());
					}

					
					GetND().GetMS().GetTrader().SetPermissionRPC(settings, alp_Player);

					return true;
				}
			}
		}
		
		return false;
	}

		
	
	bool TaxesOnClick(Widget w, int x, int y, int button)
	{
		if (alp_TaxesItem)
		{
			for(int i = 0; i < alp_TaxesItem.Count();i++)
			{
				alpTaxesItem item = alp_TaxesItem.Get(i);
				
				if (item.GetActionBtn() == w )
				{
					int tax = item.GetPrice();
					int radius = item.GetRadius();
					int days = item.GetValidity();
					GetND().GetMS().GetTrader().PayTaxesRPC(radius, days, tax, alp_Player);

					return true;
				}
				
			}
		
		}

		return false;
	}	
	
	bool EstatesOnClick(Widget w, int x, int y, int button)
	{
		if (alp_EstatesItem)
		{
			for(int i = 0; i < alp_EstatesItem.Count();i++)
			{
				alpEstatesItem	item = alp_EstatesItem.Get(i);
				
				if ( item.GetActionBtn() == w )
				{//buy
					BuildingBase building = GetBuildingALP(item.GetWorldID() );

					if (building)
					{
			
						int key = Math.RandomIntInclusive( 1, int.MAX - 1 );					
						Param3<int,int,int> values = new Param3<int,int,int>( item.GetWorldID(), key, item.GetEstatePrice() ); 
					
						if ( item.GetActionBtn().GetChildren().GetColor() == COLOR_AVAILABLE_POSITIVE ) {
							GetND().GetMS().GetTrader().BuyEstatesRPC( values, alp_Player);
						} else {
							GetND().GetMS().GetTrader().SellEstatesRPC( values, alp_Player);
						}												
						return true;
					}
				}
			}			
		}		
		return false;
	}	
	bool KeysOnClick(Widget w, int x, int y, int button)
	{
		if (alp_KeysItem)
		{
			for(int i = 0; i < alp_KeysItem.Count();i++)
			{
				alpDefaultItem	item = alp_KeysItem.Get(i);
				
				if ( item.GetActionBtn() == w )
				{//key
					BuildingBase building = GetBuildingALP(item.GetWorldID() );					
					if (building)
					{
						 
						Param4<int,int,int,int> values = new Param4<int,int,int,int>( item.GetWorldID(), building.GetKeyID(), building.GetCountOfDoorsALP(), item.GetPrice() ); 					
						GetND().GetMS().GetTrader().BuyEstatesKeyRPC( values, alp_Player);

						return true;
					}
				}
			}			
		}		
		return false;
	}	
	
	bool FingerprintsOnClick(Widget w, int x, int y, int button)
	{
		
		if (alp_FingerprintsItem)
		{
			for(int i = 0; i < alp_FingerprintsItem.Count();i++)
			{
				alpDefaultItem	item = alp_FingerprintsItem.Get(i);
				
				if ( item.GetActionBtn() == w )
				{//key
					BuildingBase building = GetBuildingALP(item.GetWorldID() );
					if (building)
					{				

						int setting = building.GetHouseSetting() | alpBUILDINGSET.HAS_FINGERPRINTSLOCK;

						Param4<int,int,int,int> values = new Param4<int,int,int,int>( item.GetWorldID(),building.GetKeyID(), setting , item.GetPrice() ); 			
																									
						GetND().GetMS().GetTrader().UpdateEstatesSettingsRPC( values, alp_Player);
						return true;
					}
				}
			}			
		}	
		
		return false;
	}	
	bool LockProtectionOnClick(Widget w, int x, int y, int button)
	{
		if (alp_LockpickingItem)
		{
			for(int i = 0; i < alp_LockpickingItem.Count();i++)
			{
				alpDefaultItem	item = alp_LockpickingItem.Get(i);
				
				if ( item.GetActionBtn() == w )
				{//better lock
					BuildingBase building = GetBuildingALP(item.GetWorldID() );
					if (building)
					{
						int setting = building.GetHouseSetting() | alpBUILDINGSET.HAS_LOCKPICKINGPROTECTION;

						Param4<int,int,int,int> values = new Param4<int,int,int,int>( item.GetWorldID(),building.GetKeyID(), setting , item.GetPrice() ); 			
																									
						GetND().GetMS().GetTrader().UpdateEstatesSettingsRPC( values, alp_Player);						
						
						return true;
					}
				}
			}			
		}		
		return false;
	}		
	bool DurabelDoorsOnClick(Widget w, int x, int y, int button)
	{
		if (alp_ImprovmentsItem)
		{
			for(int i = 0; i < alp_ImprovmentsItem.Count();i++)
			{
				alpDefaultItem	item = alp_ImprovmentsItem.Get(i);
				
				if ( item.GetActionBtn() == w )
				{//durabel doors
					BuildingBase building = GetBuildingALP(item.GetWorldID() );
					if (building)
					{
						int setting = building.GetHouseSetting() | alpBUILDINGSET.HAS_ENHANCEDDOOR;

						Param4<int,int,int,int> values = new Param4<int,int,int,int>( item.GetWorldID(),building.GetKeyID(), setting , item.GetPrice() ); 			
																									
						GetND().GetMS().GetTrader().UpdateEstatesSettingsRPC( values, alp_Player);						
						
						return true;						
					}
				}
			}			
		}		
		return false;
	}		
	BuildingBase GetBuildingALP(int id ){
		array< BuildingBase> budovy = alp_Player.alp_PlotPoleManage.GetBuildingInRadius();
		if (budovy)
		{
			for (int i = 0; i < budovy.Count();i++)
			{
				if ( id == budovy.Get(i).GetWorldID() )
				{
					return budovy.Get(i);
				}
			}
		}	
		return null;
	}	

	
	override bool OnMouseEnter(Widget w, int x, int y)
	{
		int i;
		if (alp_EstatesItem)
		{
			for(i = 0; i < alp_EstatesItem.Count();i++)
			{
				alpEstatesItem	item = alp_EstatesItem.Get(i);
				
				if ( item.GetActionBtn() == w )
				{
					alpBuildingLabels.SelectLabel( item.GetWorldID() );
					return true;
				}
			}		
		}	
		if (alp_KeysItem)
		{
			for(i = 0; i < alp_KeysItem.Count();i++)
			{
				alpDefaultItem	key = alp_KeysItem.Get(i);
				
				if ( key.GetActionBtn() == w )
				{
					alpBuildingLabels.SelectLabel( key.GetWorldID() );
					return true;
				}
			}		
		}	
		if (alp_FingerprintsItem)
		{
			for(i = 0; i < alp_FingerprintsItem.Count();i++)
			{
				alpDefaultItem	fingerprints = alp_FingerprintsItem.Get(i);
				
				if ( fingerprints.GetActionBtn() == w )
				{
					alpBuildingLabels.SelectLabel( fingerprints.GetWorldID() );
					return true;
				}
			}		
		}	
		if (alp_LockpickingItem)
		{
			for(i = 0; i < alp_LockpickingItem.Count();i++)
			{
				alpDefaultItem	lock = alp_LockpickingItem.Get(i);
				
				if ( lock.GetActionBtn() == w )
				{
					alpBuildingLabels.SelectLabel( lock.GetWorldID() );
					return true;
				}
			}		
		}		
		if (alp_ImprovmentsItem)
		{
			for(i = 0; i < alp_ImprovmentsItem.Count();i++)
			{
				alpDefaultItem	doors = alp_ImprovmentsItem.Get(i);
				
				if ( doors.GetActionBtn() == w )
				{
					alpBuildingLabels.SelectLabel( doors.GetWorldID() );
					return true;
				}
			}		
		}								
		return false;
	}
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		if (alp_EstatesItem)
		{
			for(int i = 0; i < alp_EstatesItem.Count();i++)
			{
				alpEstatesItem	item = alp_EstatesItem.Get(i);
				
				if ( item.GetActionBtn() == w )
				{
					alpBuildingLabels.UnSelectLabel( item.GetWorldID() );
					return true;
				}
			}		
		}	
		if (alp_KeysItem)
		{
			for(i = 0; i < alp_KeysItem.Count();i++)
			{
				alpDefaultItem	key = alp_KeysItem.Get(i);
				
				if ( key.GetActionBtn() == w )
				{
					alpBuildingLabels.UnSelectLabel( key.GetWorldID() );
					return true;
				}
			}		
		}	
		if (alp_FingerprintsItem)
		{
			for(i = 0; i < alp_FingerprintsItem.Count();i++)
			{
				alpDefaultItem	fingerprints = alp_FingerprintsItem.Get(i);
				
				if ( fingerprints.GetActionBtn() == w )
				{
					alpBuildingLabels.UnSelectLabel( fingerprints.GetWorldID() );
					return true;
				}
			}		
		}	
		if (alp_LockpickingItem)
		{
			for(i = 0; i < alp_LockpickingItem.Count();i++)
			{
				alpDefaultItem	lock = alp_LockpickingItem.Get(i);
				
				if ( lock.GetActionBtn() == w )
				{
					alpBuildingLabels.UnSelectLabel( lock.GetWorldID() );
					return true;
				}
			}		
		}			
		if (alp_ImprovmentsItem)
		{
			for(i = 0; i < alp_ImprovmentsItem.Count();i++)
			{
				alpDefaultItem	doors = alp_ImprovmentsItem.Get(i);
				
				if ( doors.GetActionBtn() == w )
				{
					alpBuildingLabels.UnSelectLabel( doors.GetWorldID() );
					return true;
				}
			}		
		}							
		return false;
	}	
	
	
	override void OnShow()
	{
		super.OnShow();

		SetFocus( layoutRoot );
		GetGame().GetInput().ChangeGameFocus(1);	
		PPEffects.SetBlurMenu( GetND().GetClans().GetBases().EstateManagementMenu_blur );
		MissionGameplay.Cast( GetGame().GetMission() ).PlayerControlDisable(INPUT_EXCLUDE_ALL);
		GetGame().GetMission().GetHud().ShowHudUI( false );
		GetGame().GetMission().GetHud().ShowQuickbarUI( false );			

	}	
	override void OnHide()
	{
		super.OnHide();
		SetFocus( null );
		PPEffects.SetBlurMenu( 0 );
		GetGame().GetInput().ChangeGameFocus(-1);
		MissionGameplay.Cast( GetGame().GetMission() ).PlayerControlEnable(true);	
		GetGame().GetMission().GetHud().ShowHudUI( true );
		GetGame().GetMission().GetHud().ShowQuickbarUI( true );			
	}	

}
