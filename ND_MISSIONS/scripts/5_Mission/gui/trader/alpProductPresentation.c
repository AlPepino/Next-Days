class InspectMenuNewALP : InspectMenuNew
{}

class alpProductPresentation 
{
	ref alpProductCard				alp_ProductCard;
	
	Widget 							alp_Root;
	
	TextWidget						alp_Title;
	
	ItemPreviewWidget 				alp_ItemsPreviewPanel;
	
	ButtonWidget					alp_ButtonInspection;
	ButtonWidget 					alp_ButtonPlus;
	ButtonWidget					alp_ButtonMinus;
	
	ImageWidget 					alp_IconInCart;
	TextWidget						alp_InCart;
	ImageWidget 					alp_IconInStock;
	TextWidget						alp_InStock;
	
	Widget							alp_Parent;
		
	void alpProductPresentation( alpProductCard product , Widget parent)
	{
		alp_ProductCard = product;
		alp_Parent = parent;
		

	}
	
	void ~alpProductPresentation()
	{
		if (alp_Root)
		{
			alp_Root.Unlink();
		}
		
	}	
	
	alpProductCard GetProductCard()
	{
		return alp_ProductCard;
	}
	
	Widget GetPanel()
	{
		Widget layout = GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/Item.layout"); //, alp_Parent);	
		
		alp_Root = Widget.Cast( layout.FindAnyWidget("ItemMainPanel"));
		
		alp_Title = TextWidget.Cast( layout.FindAnyWidget("ItemTitle"));
		alp_ItemsPreviewPanel = ItemPreviewWidget.Cast( layout.FindAnyWidget("ItemPreview") );
		
		alp_ButtonInspection = ButtonWidget.Cast( alp_Root.FindAnyWidget("InspectItemButton") );
		
		alp_ButtonPlus = ButtonWidget.Cast( layout.FindAnyWidget("ButtonPlus") );
		ImageWidget.Cast( alp_Root.FindAnyWidget("PlusIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/Plus.paa");
		alp_ButtonMinus = ButtonWidget.Cast( layout.FindAnyWidget("ButtonMinus") );
		ImageWidget.Cast( alp_Root.FindAnyWidget("MinusIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/Minus.paa");
		
		alp_IconInCart = ImageWidget.Cast( layout.FindAnyWidget("InCartIcon") );
		alp_IconInCart.LoadImageFile(0,"ND_MISSIONS/gui/images/Cart.paa");	
		
		alp_InCart = TextWidget.Cast( layout.FindAnyWidget("InCartValue") );
		
		alp_IconInStock = ImageWidget.Cast( layout.FindAnyWidget("AvailableIcon") );
		alp_InStock = TextWidget.Cast( layout.FindAnyWidget("AvailableValue") );	
		
		//reputation
		string iconReputation = "ND_MISSIONS/gui/images/Reputation/r" + GetProductCard().GetRequiredReputation().ToString() + ".paa";	
		ImageWidget.Cast( layout.FindAnyWidget("ItemReputationIcon") ).LoadImageFile(0,iconReputation);	
		
		
		if ( GetND().GetMS().GetOptoinsTrader().ShowAvailableItemInStock )
		{
			alp_InStock.Show( true );
		}
		else
		{
			alp_InStock.Show( false );
		}		
		
		//itemPreview
		EntityAI ent =  GetProductCard().GetEntity();
		if (ent.IsItemTent())
		{
			TentBase tent;
			if ( Class.CastTo( tent, ent) )
			{
				tent.Pitch(true);
			}
		}		
			//FoodStage		EntityAI.edi	
		Edible_Base food;			
		if (ent.IsInherited( Edible_Base) && Class.CastTo(food,ent))
		{
			if ( food.HasFoodStage() )
			{
				food.UpdateVisuals();
			}
		}		
		
		alp_ItemsPreviewPanel.SetItem( ent );
		
		alp_ItemsPreviewPanel.SetModelPosition(Vector(0,0,0.5));		
		alp_ItemsPreviewPanel.SetModelOrientation(vector.Zero);		
		alp_ItemsPreviewPanel.SetView( alp_ItemsPreviewPanel.GetItem().GetViewIndex());					
	
		InspectMenuNew.UpdateItemInfoWeight(alp_Root,ent);
		InspectMenuNew.UpdateItemInfoTemperature(alp_Root,ent);				
		
		InventoryItem iItem = InventoryItem.Cast( ent );
		if (iItem)
		{	
			MultilineTextWidget description = MultilineTextWidget.Cast( alp_Root.FindAnyWidget("ItemDescription"));										
			description.SetText(iItem.GetTooltip());	
				
			if ( iItem.IsInherited( ClothingBase ) )
			{
				HeatIsolation(alp_Root, ItemBase.Cast(iItem) );
			}
			else
			{
				InspectMenuNew.UpdateItemInfoQuantity(alp_Root, ent);
			}
		} else {
			//Print("NELZE VYTVORIT NAHLED " + ent.GetType() );
		}			
	
		alp_Root.Show(false);		
		
		return alp_Root;
	} 							
	
	void Show( bool state )
	{	
		alp_Root.Show( state );		
		
		if ( state )
		{
			Update();
		}			
	}
	void Update()
	{
		alp_Title.SetText( GetProductCard().GetDisplayName() );
		
		
		int itemsInStock = GetProductCard().GetAvailableItem();
		int availableItems = itemsInStock - GetProductCard().GetCountInCart();
		
		if ( GetProductCard().GetAvailableItem() > 0 )
		{
			alp_IconInStock.LoadImageFile(0,"ND_MISSIONS/gui/images/Available.paa");	
			alp_IconInStock.SetColor( COLOR_AVAILABLE_POSITIVE );
			if ( GetProductCard().CanBeTrade() && availableItems > 0 )
			{				
				alp_ButtonPlus.Enable( true );
				alp_ButtonPlus.GetChildren().SetColor( COLOR_AVAILABLE_POSITIVE );					
			}
			else
			{
				alp_ButtonPlus.Enable( false );
				alp_ButtonPlus.GetChildren().SetColor( COLOR_UNAVAILABLE );					
			}			
		}
		else
		{
			alp_IconInStock.LoadImageFile(0,"ND_MISSIONS/gui/images/UnAvailable.paa");	
			alp_IconInStock.SetColor( COLOR_UNAVAILABLE );
			alp_ButtonPlus.Enable( false );
			alp_ButtonPlus.GetChildren().SetColor( COLOR_UNAVAILABLE );			
		}
		//cart in product
		int countInCart = GetProductCard().GetCountInCart();
		if ( countInCart > 0 )
		{
			alp_ButtonMinus.Enable( true );
			alp_ButtonMinus.GetChildren().SetColor( COLOR_AVAILABLE_NEGATIVE );			
			alp_InCart.SetText( countInCart.ToString() );				
			alp_InCart.SetColor( COLOR_AVAILABLE_POSITIVE );
		}
		else
		{
			alp_ButtonMinus.Enable( false );
			alp_ButtonMinus.GetChildren().SetColor( COLOR_UNAVAILABLE );		
			alp_InCart.SetColor( COLOR_UNAVAILABLE );	
			alp_InCart.SetText( "0" );					
		}		
		
		//value
		TextWidget.Cast( alp_Root.FindAnyWidget("ItemValue") ).SetText( alpUF.NumberToString( GetProductCard().GetValue() ,1) );	
		//price
		TextWidget.Cast( alp_Root.FindAnyWidget("ItemPrice") ).SetText( alpUF.NumberToString( GetProductCard().GetPrice(),1) );
		//in cart
		
		alp_InStock.SetText( alpUF.NumberToString(availableItems   ,1) );
		
		
		
		
		//HIDE if there is no available item on stock
		if (!GetND().GetMS().GetOptoinsTrader().ShowItemsWithNoStock && itemsInStock <= 0 )
		{
			alp_Root.Show( false );	
		}
		
		//hide if is not empty
		if ( !GetProductCard().IsEmpty() )
		{
			alp_Root.Show( false );	
		}
		//is item hidden
		string type = GetProductCard().GetType();
		if ( GetND().GetMS().GetTrader().IsBuyMenu() && GetND().GetMS().IsItemHidden( type  ) )
		{
			alp_Root.Show( false );	
		}		
		
		//hide if is not possible sell/buy item

		if ( !GetND().GetMS().GetOptoinsTrader().ShowItemsWithNoStock && !GetProductCard().IsTradAble() )
		{
			alp_Root.Show( false );	
		}
		
	}
	
	void HeatIsolation(Widget root_widget, ItemBase item_base)
	{
		float heatIsolation = MiscGameplayFunctions.GetCurrentItemHeatIsolation( item_base );
		if ( heatIsolation <= GameConstants.HEATISO_THRESHOLD_BAD )
		{
			InspectMenuNew.WidgetTrySetText( root_widget, "ItemQuantityWidget", "#inv_inspect_iso_bad", GetTemperatureColor( 10 ) );
		}
		else if ( ( heatIsolation > GameConstants.HEATISO_THRESHOLD_BAD ) && ( heatIsolation <= GameConstants.HEATISO_THRESHOLD_LOW ) )
		{
			InspectMenuNew.WidgetTrySetText( root_widget, "ItemQuantityWidget", "#inv_inspect_iso_low", GetTemperatureColor( 20 ) );
		}
		else if ( ( heatIsolation > GameConstants.HEATISO_THRESHOLD_LOW ) && ( heatIsolation <= GameConstants.HEATISO_THRESHOLD_MEDIUM ) )
		{
			InspectMenuNew.WidgetTrySetText( root_widget, "ItemQuantityWidget", "#inv_inspect_iso_medium", GetTemperatureColor( 30 ) );
		}
		else if ( ( heatIsolation > GameConstants.HEATISO_THRESHOLD_MEDIUM ) && ( heatIsolation <= GameConstants.HEATISO_THRESHOLD_HIGH ) )
		{
			InspectMenuNew.WidgetTrySetText( root_widget, "ItemQuantityWidget", "#inv_inspect_iso_high", GetTemperatureColor( 50 ) );
		}
		else
		{
			InspectMenuNew.WidgetTrySetText( root_widget, "ItemQuantityWidget", "#inv_inspect_iso_excel", GetTemperatureColor( 70 ) );
		}	

	}	
	
	void InspectItem( EntityAI item )
	{
		alpTraderMenu menu = alpTraderMenu.Cast( GetGame().GetUIManager().FindMenu(ALP_MENU_TRADER) );
		InspectMenuNewALP inspect_menu = InspectMenuNewALP.Cast( menu.EnterScriptedMenu(MENU_INSPECT_ALP) );
		if ( inspect_menu )
		{
			GetGame().GetMission().GetHud().ShowHudUI( false );
			GetGame().GetMission().GetHud().ShowQuickbarUI( false );
			MissionGameplay.Cast( GetGame().GetMission() ).PlayerControlDisable(INPUT_EXCLUDE_ALL);
			inspect_menu.SetItem( item );
		}		


	}	
	
	bool OnClick(Widget w, int x, int y, int button)
	{		

		
				
		if ( w ==	alp_ButtonInspection )
		{

			InspectItem( GetProductCard().GetEntity() );
			return true;		
		}				
		if ( w == alp_ButtonPlus )
		{	
			return AddToCart();
		}

		if ( w == alp_ButtonMinus )
		{

			return RemoveFromCart();
		}		
		
		return false;
		
	}	
	
	bool AddToCart()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player.GetRP().GetCart().AddItemToCart( GetProductCard() ) )
		{
			return true;
		}
		return false;
	}
	
	bool RemoveFromCart()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player.GetRP().GetCart().RemoveItemFromCart( GetProductCard() ) )
		{
			return true;
		}
		return false;
	}	
}
