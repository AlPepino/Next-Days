enum alpSORTEDBY
{
	NAME,
	NAME_REVERSE,
	VALUE,
	VALUE_REVERSE,
	COUNT
}


class alpTraderMenu extends UIScriptedMenu
{

	PlayerBase									alp_Player;
	
	
	//info panel
	Widget									 	alp_RootWindowLoading;
	RichTextWidget								alp_InfoTitle;	
	
	//TRADER WINDOW
	Widget 										alp_RootWindowTrader;
	PlayerPreviewWidget 						alp_PlayerPreviewPanel;
	
	//filtr	
	TextWidget									alp_FiltrTitle;
	EditBoxWidget								alp_FindItem;	
	TextListboxWidget							alp_FiltrList;		

	//bank balances	
	TextWidget									alp_BankAccount;	
	TextWidget									alp_BankAccountTrader;	
	
	//cart
	TextWidget 									alp_CartCash;
	TextWidget 									alp_CartTotal;
	TextWidget 									alp_CartCount;
	
	ButtonWidget								alp_CartBtn;
	ImageWidget									alp_CartIcon;
	
	ButtonWidget								alp_CartEmpty;
	ButtonWidget								alp_CartConfirm;

	//menu
	alpMenuCategory								alp_MainMenu;
	alpMenuCategory								alp_Menu1;
	alpMenuCategory								alp_Menu2;
	alpMenuCategory								alp_Menu3;	
	int											alp_LastSelected1;
	int											alp_LastSelected2;
	int											alp_LastSelected3;		
	
	ref alpTraderButtonContainer				alp_Menu1Buttons;
	ref alpTraderButtonContainer				alp_Menu2Buttons;	
	
	
	ref array<ref alpProductCard>				alp_SelectedItems;	

	ref array<ref alpProductPresentation>>		alp_PresentedItems;	
	
	//ITEMS 
	WrapSpacerWidget							alp_PanelPresentation;
	
	
	int 										alp_LastSortID;	
	
	autoptr map<int,string>						alp_CurrencyMapped;
	
	override Widget Init()
	{
		
		alp_Player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		
	
		//GetGame().GetMission().PlayerControlDisable( INPUT_EXCLUDE_ALL );
		
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("ND_MISSIONS/gui/layouts/GUI_trader.layout");
		
		
		//LOADING PANEL
		alp_RootWindowLoading = Widget.Cast( 	layoutRoot.FindAnyWidget("rootWindowLoading") );
		alp_InfoTitle = RichTextWidget.Cast( 	layoutRoot.FindAnyWidget("InfoTextTrading") );
				
		//TRADER WINDOW
		alp_RootWindowTrader = Widget.Cast( 	layoutRoot.FindAnyWidget("rootWindow") );

		//player		
		alp_PlayerPreviewPanel = PlayerPreviewWidget.Cast( 	layoutRoot.FindAnyWidget("PlayerPreview") );				
		alp_PlayerPreviewPanel.SetPlayer( alp_Player);		

		
		//TRADER WIDGET
		//filtr
		alp_FiltrList = TextListboxWidget.Cast( 	layoutRoot.FindAnyWidget("FiltrList") );
		alp_FiltrTitle = TextWidget.Cast( 	layoutRoot.FindAnyWidget("FilterTitle") );
		alp_FindItem = EditBoxWidget.Cast( 	layoutRoot.FindAnyWidget("FindItemText") );				
		
		//bank alp_BankAccount
		alp_BankAccount = TextWidget.Cast( 	layoutRoot.FindAnyWidget("BankBalanceText") );		
		alp_BankAccountTrader =  TextWidget.Cast( 	layoutRoot.FindAnyWidget("TraderBankBalanceText") );	
		
		
		//Cart		
		alp_CartCash = TextWidget.Cast( 	layoutRoot.FindAnyWidget("CartCashValue") );
		alp_CartTotal = TextWidget.Cast( 	layoutRoot.FindAnyWidget("CartTotalValue") );
		alp_CartCount = TextWidget.Cast( 	layoutRoot.FindAnyWidget("CartCountValue") );
		
		alp_CartBtn = ButtonWidget.Cast( 	layoutRoot.FindAnyWidget("CartBtn") );
		alp_CartIcon = ImageWidget.Cast( 	layoutRoot.FindAnyWidget("CartIcon") );
		
		alp_CartEmpty = ButtonWidget.Cast( 	layoutRoot.FindAnyWidget("EmptyBtn") );
		alp_CartConfirm = ButtonWidget.Cast( 	layoutRoot.FindAnyWidget("ConfirmBtn") );	
		
		//ITEMS PRESENTATION
		alp_PanelPresentation =  WrapSpacerWidget.Cast( layoutRoot.FindAnyWidget("BodyPanel"));
		//alp_PanelPresentationTemp = Widget.Cast( alp_RootWindow.FindAnyWidget("rootContainer") );
								
		//ICONS UPDATE
		ImageWidget.Cast( layoutRoot.FindAnyWidget("BankBalanceIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/BankAccount.paa");
		ImageWidget.Cast( layoutRoot.FindAnyWidget("FindItemIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/Find.paa");
		ImageWidget.Cast( layoutRoot.FindAnyWidget("CartCashIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/Cash.paa");
		ImageWidget.Cast( layoutRoot.FindAnyWidget("TraderBankBalanceIconCash") ).LoadImageFile(0,"ND_MISSIONS/gui/images/Cash.paa");
		ImageWidget.Cast( layoutRoot.FindAnyWidget("CartTotalIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/Bill.paa");
		ImageWidget.Cast( layoutRoot.FindAnyWidget("CartIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/Cart.paa");
		
		ImageWidget.Cast( layoutRoot.FindAnyWidget("ConfirmIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/Confirm.paa");
		ImageWidget.Cast( layoutRoot.FindAnyWidget("EmptyIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/CartEmpty.paa");
		
		//customing trader		
		if ( GetND().GetMS().GetTrader().IsBuyMenu() )
		{
			TextWidget.Cast( layoutRoot.FindAnyWidget("headerTitle") ).SetText("#trader_buing_title");
		}
		else
		{
			TextWidget.Cast( layoutRoot.FindAnyWidget("headerTitle") ).SetText("#trader_selling_title");		
		}
			
		//bank system
		if ( !GetND().GetMS().GetTrader().CanPayByCard() )
		{
			Widget.Cast( layoutRoot.FindAnyWidget("BankPanel") ).Show(false);
		}		
		
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
		
		alp_RootWindowTrader.Show(false);
		alp_RootWindowLoading.Show(true);		
				
		return layoutRoot;
	}
	
	void ~alpTraderMenu()
	{
		alp_Player.GetSyncData().RegisterToEnhancedStatsSync(false);
		alp_Player.GetRP().GetCart().ClearCart();
		
		//GetGame().GetMission().PlayerControlEnable( true );
		
		
		GetND().GetMS().GetTrader().SetValidTraderData( false );
		/*
		if (alp_Cart)
			alp_Cart.ClearCart();	
		*/
		
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if ( GetND().GetMS().GetTrader().IsTraderSet() && alp_RootWindowLoading.IsVisible() )
		{
			//TO DO: postpone + plus info about transaction
			alp_RootWindowTrader.Show( true );
			alp_RootWindowLoading.Show( false );
			
			alp_MainMenu = GetND().GetMS().GetTrader().GetTraderMenu();
			
			InitTrader();

		}
		if ( !GetND().GetMS().GetTrader().IsTraderSet() && alp_RootWindowTrader.IsVisible() )
		{
			alp_RootWindowTrader.Show( false );
			
			alp_RootWindowLoading.Show( true );
			alp_InfoTitle.SetText( "#trader_info_loading" );
		}
	
		if ( alp_RootWindowTrader.IsVisible() )
		{//UPDATE 
			UpdatePlayerPreview();	
			CheckUpdate();
		}

	}
	
	void UpdatePlayerPreview()
	{		
		alp_PlayerPreviewPanel.UpdateItemInHands( alp_Player.GetHumanInventory().GetEntityInHands() );
	}
		
	void InitTrader()
	{
		
		//alp_MainMenu = GetND().GetMS().GetTrader().GetTraderMenu();
		
		//check result
		if (GetND().GetMS().GetTrader().alp_TraderData.Count() == 0 )
		{
			Close();
			return;
		}
			
		
		alp_MainMenu.SetSelected( alp_LastSelected1 );		
		alp_LastSelected1 = alp_MainMenu.GetSelected();

		
		alp_Menu1 = alp_MainMenu.GetSelectedMenu();
		alp_Menu1.SetSelected( alp_LastSelected2 );
		alp_LastSelected2 = alp_Menu1.GetSelected();
		
		alp_Menu2 = alp_Menu1.GetSelectedMenu();
		alp_Menu2.SetSelected( alp_LastSelected3 );		
		
			
		alp_Menu1Buttons = new alpTraderButtonContainer( WrapSpacerWidget.Cast( alp_RootWindowTrader.FindAnyWidget("groupPanel")), alp_MainMenu,alp_LastSelected1 );
	
		alp_Menu2Buttons = new alpTraderButtonContainer( WrapSpacerWidget.Cast( alp_RootWindowTrader.FindAnyWidget("categoryPanel")), alp_Menu1,alp_LastSelected2 );
				
		alp_FiltrList.ClearItems();
		for (int i = 0; i < alp_Menu2.alp_Menu.Count(); i++)
		{
			alp_FiltrList.AddItem( alp_Menu2.alp_Menu.GetKey(i),null,0 );
		}
		alp_FiltrList.SetItemColor(alp_Menu2.GetSelected(),0,ARGB(255,140,140,140));
		
		alp_Menu3 = alp_Menu2.GetSelectedMenu();		

		//FilterTitle
		string title = alp_MainMenu.GetSelectedMenu().alp_Name + " > " + alp_Menu1.GetSelectedMenu().alp_Name + " > " + alp_Menu2.GetSelectedMenu().alp_Name;
		alp_FiltrTitle.SetText( title );
		InitList (alp_Menu3.GetCategoryID() );
			
	
	}	
	
	void InitList(int index = 0)
	{
		SetSelectedData(index);		
		
		alp_PresentedItems = new  array<ref alpProductPresentation>>;
		foreach ( alpProductCard product :	alp_SelectedItems )
		{
			alpProductPresentation item = new alpProductPresentation( product , Widget.Cast( layoutRoot.FindAnyWidget("rootContainer") )  );
			alp_PresentedItems.Insert( item );		
						
		}		
		
		int sort = alp_LastSortID;
		
		ShowItems( sort );
		InitCart();	
	}		
	
	void InitCart()
	{
		//trader cash
		float traderCash,bank;
		alp_Player.GetSyncData().GetElementEnhanced( alpRPelementsEnahnced.TRADER_BALANCE).GetValue( traderCash );
		
		//palyer account
		alp_Player.GetSyncData().GetElementEnhanced( alpRPelementsEnahnced.PLAYER_BALANCE).GetValue( bank );
		alp_BankAccount.SetText( alpUF.NumberToString(bank ,1) + " " + alp_CurrencyMapped.GetElement( alp_Player.GetRP().GetCart().GetCurrencyID() ));
		
				
		int cash, cost, balance;
		//int currency = GetND().GetMS().GetTrader().GetCurrency();
		cash = alp_Player.GetRP().GetCart().GetTotalBalance();//
		
		cost = alp_Player.GetRP().GetCart().GetTotalAmount();
		
		if (GetND().GetMS().GetTrader().IsBuyMenu() )   
		{		
			balance = cash - cost;
			traderCash += cost;
		}
		else
		{
			balance = cash + cost;
			traderCash -= cost;
		}
		alp_BankAccountTrader.SetText( alpUF.NumberToString( traderCash,1) + " " + alp_CurrencyMapped.GetElement( alp_Player.GetRP().GetCart().GetCurrencyID() ) );		
				
		int count = alp_Player.GetRP().GetCart().GetCountItemsInCart();
		alp_CartCash.SetText( alpUF.NumberToString( balance,1) + " " + alp_CurrencyMapped.GetElement( alp_Player.GetRP().GetCart().GetCurrencyID() ));
		alp_CartTotal.SetText( alpUF.NumberToString( cost,1) + " " + alp_CurrencyMapped.GetElement( alp_Player.GetRP().GetCart().GetCurrencyID() ) );
		alp_CartCount.SetText( alpUF.NumberToString(count ,1) );


		
		if ( count > 0)
		{
			alp_CartBtn.Enable(true);
			alp_CartIcon.SetColor( COLOR_AVAILABLE_POSITIVE );
			
			alp_CartEmpty.Enable(true);
			alp_CartConfirm.Enable(true);
			
			alp_CartEmpty.GetChildren().SetColor( COLOR_AVAILABLE_NEGATIVE );		
			alp_CartConfirm.GetChildren().SetColor( COLOR_AVAILABLE_POSITIVE );				
		}
		else
		{
			alp_CartBtn.Enable(false);
			alp_CartIcon.SetColor( COLOR_UNAVAILABLE );
			
			alp_CartEmpty.Enable(false);
			alp_CartConfirm.Enable(false);	
			alp_CartEmpty.GetChildren().SetColor( COLOR_UNAVAILABLE );		
			alp_CartConfirm.GetChildren().SetColor( COLOR_UNAVAILABLE );	
		}
			
	
	}		
	
	void ShowItems(int sort, bool clear = true)
	{
		FilterIconDefaultColor();
		
		alp_LastSortID = sort;
		
		string name = "OrderBy_" + sort + "_Icon";
		ImageWidget icon = ImageWidget.Cast( alp_RootWindowTrader.FindAnyWidget(name) );
		if (icon)
		{
			icon.SetColor( COLOR_UNAVAILABLE );	
		}
		
		//clear presentanion panel
		ScrollWidget.Cast( layoutRoot.FindAnyWidget("RightPanelScroll")).VScrollToPos01(0);
		Widget panel = alp_PanelPresentation.GetChildren();
		while (panel)
		{
			alp_PanelPresentation.RemoveChild( panel );
			panel = alp_PanelPresentation.GetChildren();
		}	
		
	
		
		map<int, ref array<ref alpProductPresentation> > 		byValues = new map<int, ref array<ref alpProductPresentation> >;
		map<string, ref array<ref alpProductPresentation> > 	byNames = new map<string , ref array<ref alpProductPresentation> >;
		
		foreach ( alpProductPresentation product :	alp_PresentedItems )
		{
			int productValue = product.GetProductCard().GetPrice();
			string className = product.GetProductCard().GetDisplayName();
			
			array<ref alpProductPresentation> values;			
			if ( !byValues.Find( productValue, values ) )
			{
				values = new array<ref alpProductPresentation>;
				byValues.Set( productValue, values);
			}
			values.Insert( product );

			array<ref alpProductPresentation> names;			
			if ( !byNames.Find( className, names ) )
			{
				names = new array<ref alpProductPresentation>;
				byNames.Set( className, names);
			}
			names.Insert( product );						
		}
		
		array<string> sortByName = byNames.GetKeyArray();
		array<int> sortByValue = byValues.GetKeyArray();
		
		switch( sort )
		{
			case alpSORTEDBY.NAME:
			{
				sortByName.Sort();
				break;
			}
			case alpSORTEDBY.NAME_REVERSE:
			{
				sortByName.Sort(true);
				break;				
	
			}		
			case alpSORTEDBY.VALUE:
			{
				sortByValue.Sort();
				break;
			}
			case alpSORTEDBY.VALUE_REVERSE:
			{
				sortByValue.Sort(true);
				break;
			}								
		}	
		
		//DISPLAY ITEM
		int i,p;
		array<ref alpProductPresentation> products;
		alpProductPresentation presentation;
		if ( sort == alpSORTEDBY.NAME || sort == alpSORTEDBY.NAME_REVERSE )
		{
			for (i = 0; i < sortByName.Count(); i++ )
			{
				products = byNames.Get( sortByName.Get(i) );
				
				if ( products )
				{
					for ( p = 0; p < products.Count();p++)
					{
						presentation = products.Get(p);
						alp_PanelPresentation.AddChild( presentation.GetPanel() );
						presentation.Show( true );
					}	
				}
			}
		}
		else
		{
			for (i = 0; i < sortByValue.Count(); i++ )
			{
				products = byValues.Get( sortByValue.Get(i) );
				
				if ( products )
				{
					for ( p = 0; p < products.Count();p++)
					{
						presentation = products.Get(p);
						alp_PanelPresentation.AddChild( presentation.GetPanel() );
						presentation.Show( true );
					}	
				}			
			}		
		}
		
	}	
	
	private void FilterIconDefaultColor()
	{
	
		for(int i = 0; i < alpSORTEDBY.COUNT;i++)
		{
			string name = "OrderBy_" + i + "_Icon";
			
			ImageWidget icon = ImageWidget.Cast( alp_RootWindowTrader.FindAnyWidget(name) );
			
			if (icon)
				icon.SetColor( ARGB(255,255,255,255));
		}
	
	}	
	
	private void SetSelectedData(int index)
	{
		alp_SelectedItems = new array<ref alpProductCard>;
		
		array<ref alpProductCard>	selected = GetND().GetMS().GetTrader().GetTraderData( index);
				
		if (selected)
		{			
			if (index < 0)
			{	
				string title;
				if (index == -1)
				{//filter fce
					string find = alp_FindItem.GetText();	
					find.ToLower();					
					for (int i = 0;i< selected.Count();i++)
					{				
						alpProductCard product = selected.Get(i);
						string name = product.alp_DisplayName;
						name.ToLower();
						if (name.IndexOf(find) >= 0)
						{
							alp_SelectedItems.Insert( product);	
						}						
						title = " > \"" + find + "\"";
						alp_FiltrTitle.SetText( title );					
					}					
				}
				if (index == -2)
				{//show cart
					alp_SelectedItems =  alp_Player.GetRP().GetCart().GetReservedItems();	
					title = "#trader_list_cart";
					alp_FiltrTitle.SetText( title );					
				}			
			}		
			else
			{
				alp_SelectedItems = selected;
			}
		}
	
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
				case 500://clear cart
				{
					alp_Player.GetRP().GetCart().ClearCart();
					InitTrader();
					return true;				
				}
				case 501://confir
				{
					//ConfirmCart();	
					alp_Player.GetRP().GetCart().Confirm();				
					return true;				
				}
				case 502://find
				{				
					string find = alp_FindItem.GetText();	
					find.ToLower();	
					find = find.Trim();
					if ( find.Length() > 2 )
					{
						InitList(-1);			
					}								
					return true;						
				}
			}		
			if ( alp_PresentedItems )
			{
				foreach( alpProductPresentation presentation : alp_PresentedItems)
				{
					if (presentation.OnClick(w,x,y,button) )
					{
						//TO DO: referesh cart and balance
						RefreshTrader();
						return true;
					}
				}				
			}
			
			if ( alp_Menu1Buttons.OnClick(w,x,y,button) || alp_Menu2Buttons.OnClick(w,x,y,button) || SortByIconClick(w,x,y,button) || ShowCart(w,x,y,button) )
			{
				return true;			
			}
			if ( alp_FiltrList == w )
			{
				alp_Menu3.SetSelected( alp_FiltrList.GetSelectedRow() );					
				alp_LastSelected3 = alp_FiltrList.GetSelectedRow();
				InitTrader();
				return true;
			}								
			return false;		
		
		}
		else return true;
		
	}	
	
	bool SortByIconClick(Widget w, int x, int y, int button)
	{	
		for(int i = 0; i < alpSORTEDBY.COUNT;i++)
		{
			string name = "OrderBy_" + i + "_Btn";
			ButtonWidget btn = ButtonWidget.Cast( alp_RootWindowTrader.FindAnyWidget( name ) );
			if (btn == w && alp_LastSortID != i )
			{
				ShowItems( i );		
				return true;
			}
		}		
		return false;
		
	}		

	bool ShowCart(Widget w, int x, int y, int button)
	{	
		if ( w == alp_CartBtn)
		{
			InitList(-2);
			return true;
		}		
		return false;
		
	}	
	
	void CheckUpdate()
	{

		//bank balance
		float balance;		
		if ( alp_Player.GetSyncData().GetElementEnhanced( alpRPelementsEnahnced.PLAYER_BALANCE).GetValue( balance ) )
		{
			RefreshTrader();
		}		
		
		//trader cash
		float tradercash;
		
		if ( alp_Player.GetSyncData().GetElementEnhanced( alpRPelementsEnahnced.TRADER_BALANCE).GetValue( tradercash ) )
		{
			RefreshTrader();
		}
		
		if ( alp_MainMenu && alp_MainMenu.GetSelected() != alp_LastSelected1 )
		{
			alp_LastSelected1 = alp_MainMenu.GetSelected();
			InitTrader();	
			return;
		} 
		if ( alp_Menu1 && alp_Menu1.GetSelected() != alp_LastSelected2 )
		{
			alp_LastSelected2 = alp_Menu1.GetSelected();
			InitTrader();	
			return;
		} 		
		
	}
	
	void RefreshTrader()
	{
		InitCart();
		RefreshShownProducts();
		//TO DO WITH SELECTED
	}		

	void RefreshShownProducts()
	{
		if (alp_PresentedItems)
		{
			foreach ( alpProductPresentation product : alp_PresentedItems )
			{
				product.Update();
			}
		}	
	}
	
	override void OnShow()
	{
		super.OnShow();

		SetFocus( layoutRoot );
		GetGame().GetInput().ChangeGameFocus(1);	
		PPEffects.SetBlurMenu( GetND().GetMS().GetOptoinsTrader().NPC_Menu_blur );
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
	