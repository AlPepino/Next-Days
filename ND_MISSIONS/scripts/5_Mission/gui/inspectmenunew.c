//--------------------------------------------------------------------------

modded class InspectMenuNew extends UIScriptedMenu
{
	Widget alp_ValuePanel;
	TextWidget alp_Value;
	
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("gui/layouts/inventory_new/day_z_inventory_new_inspect.layout");
	
		
		Widget parent =  Widget.Cast( layoutRoot.FindAnyWidget("InventoryInfoPanelWidget"));
		
		Widget layout = GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/inspect_value.layout", parent);	
		
		alp_ValuePanel = Widget.Cast( layout.FindAnyWidget("InspectValuePanel"));
		alp_Value = TextWidget.Cast( layout.FindAnyWidget("ItemValue"));		
		
		alp_ValuePanel.Show(false);
		
		return layoutRoot;
	}	
	
	override void SetItem(EntityAI item)
	{
		super.SetItem(item);

		if (item && item.IsItemBase() )
		{
			//my version of liquid
			InspectMenuNew.UpdateItemLiquidTypeALP(layoutRoot, ItemBase.Cast( item ) );
			
			ItemBase itm = ItemBase.Cast(item);
			int price = itm.GetDefaultPrice();
			
			if ( price )
			{
				price = price * alpBANK.GetCurrencyRate( 0 );
				map<int, ref alpCurrency> currencies = alpBANK.GetCurencies().GetCurrencies();	
				if ( currencies && currencies.Count() ){
					alpCurrency currency = currencies.GetElement(0);
					if (currency){
						alp_ValuePanel.Show(true);
						alp_Value.SetText( alpUF.NumberToString( price ,1) + " " + currency.Name );
						//alp_Value.SetText( alpUF.NumberToString( price ,1) + " #STR_koruny_name" );										
					}				
				}				
			}
			else
			{
				alp_ValuePanel.Show(false);
			}
			
		}
		else
		{
			alp_ValuePanel.Show(false);
		}
	}	

	static void UpdateItemLiquidTypeALP(Widget root_widget, ItemBase item)
	{
		
		if ( !item.IsLiquidContainer() )
			return;
		
		int liquid_type = item.GetLiquidType();	

		
		if ( liquid_type == LIQUID_RADIOACTIVEWATER )
		{

#ifdef NAMALSK_SURVIVAL			
			if (item.GetWet() < 1)
				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#alp_inv_inspect_contaminedwater", Colors.COLOR_LIQUID);
			else if ((item.GetWet() >=1) && (item.GetWet() < 2))
				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#alp_inv_inspect_contamined_c_water", Colors.COLOR_LIQUID);
			else
				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#nam_inv_ins_ice", Colors.COLOR_LIQUID);
#else		
			WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#alp_inv_inspect_contaminedwater", Colors.COLOR_LIQUID);
	
#endif				
		}
				
		
	}
	
/*	
#ifdef NAMALSK_SURVIVAL	

	

	static override void UpdateItemInfoLiquidType(Widget root_widget, EntityAI item)
	{
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		
		ItemBase item_base = ItemBase.Cast( item );
		
		if( item_base && item_base.GetQuantity() > 0 && item_base.IsBloodContainer() )
		{
			BloodContainerBase blood_container = BloodContainerBase.Cast( item_base );
			
			if( blood_container.GetBloodTypeVisible() )
			{
				string type;
				bool positive;
				string blood_type_name = BloodTypes.GetBloodTypeName(blood_container.GetLiquidType(), type, positive);

				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_blood: " + blood_type_name, Colors.COLOR_LIQUID);
			}
			else
			{
				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_blood", Colors.COLOR_LIQUID);
			}
		}
		else if( item_base && item_base.GetQuantity() > 0 && item_base.IsLiquidContainer() )
		{
			int liquid_type = item_base.GetLiquidType();
			Print("LIQUID TYPE " + liquid_type );
			switch(liquid_type)
			{
				case LIQUID_RADIOACTIVEWATER:
				{
					if (item_base.GetWet() < 1)
						WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#alp_inv_inspect_contaminedwater", Colors.COLOR_LIQUID);
					else if ((item_base.GetWet() >=1) && (item_base.GetWet() < 2))
						WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#alp_inv_inspect_contamined_c_water", Colors.COLOR_LIQUID);
					else
						WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#nam_inv_ins_ice", Colors.COLOR_LIQUID);
					break;
				}				
				
				case LIQUID_WATER:
				{
					if (item_base.GetWet() < 1)
						WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#nam_inv_ins_water", Colors.COLOR_LIQUID);
					else if ((item_base.GetWet() >=1) && (item_base.GetWet() < 2))
						WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#nam_inv_ins_cwater", Colors.COLOR_LIQUID);
					else
						WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#nam_inv_ins_ice", Colors.COLOR_LIQUID);
					break;
				}
					
				case LIQUID_RIVERWATER:
				{
					if (item_base.GetWet() < 1)
						WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#nam_inv_ins_water", Colors.COLOR_LIQUID);
					else if ((item_base.GetWet() >=1) && (item_base.GetWet() < 2))
						WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#nam_inv_ins_cwater", Colors.COLOR_LIQUID);
					else
						WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#nam_inv_ins_ice", Colors.COLOR_LIQUID);
					break;
				}
					
				case LIQUID_VODKA:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_vodka", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_BEER:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_beer", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_GASOLINE:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_gasoline", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_DIESEL:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_diesel", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_DISINFECTANT:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_disinfectant", Colors.COLOR_LIQUID);
					break;
				}
	
				case LIQUID_SALINE:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_saline", Colors.COLOR_LIQUID);
					break;
				}
				
				default:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "ERROR", Colors.COLOR_LIQUID);
					break;
				}
			}
		}
		else
		{
			WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "");
		}
	}			
	
#else
	
	


	//--------------------------------------------------------------------------
	static override void UpdateItemInfoLiquidType(Widget root_widget, EntityAI item)
	{
		Print("TOTO JE VOLANO");
		if ( item.IsInherited( ZombieBase ) || item.IsInherited( Car ) ) return;
		
		ItemBase item_base = ItemBase.Cast( item );
		
		if( item_base && item_base.GetQuantity() > 0 && item_base.IsBloodContainer() )
		{
			BloodContainerBase blood_container = BloodContainerBase.Cast( item_base );
			
			if( blood_container.GetBloodTypeVisible() )
			{
				string type;
				bool positive;
				string blood_type_name = BloodTypes.GetBloodTypeName(blood_container.GetLiquidType(), type, positive);
				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_blood: " + blood_type_name, Colors.COLOR_LIQUID);
			}
			else
			{
				WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_blood", Colors.COLOR_LIQUID);
			}
		}
		else if( item_base && item_base.GetQuantity() > 0 && item_base.IsLiquidContainer() )
		{
			int liquid_type = item_base.GetLiquidType();
			
			switch(liquid_type)
			{
				case LIQUID_RADIOACTIVEWATER:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#alp_inv_inspect_contaminedwater", Colors.COLOR_LIQUID);
					break;
				}				
				
				case LIQUID_WATER:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_water", Colors.COLOR_LIQUID);
					break;
				}
					
				case LIQUID_RIVERWATER:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_river_water", Colors.COLOR_LIQUID);
					break;
				}
					
				case LIQUID_VODKA:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_vodka", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_BEER:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_beer", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_GASOLINE:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_gasoline", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_DIESEL:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_diesel", Colors.COLOR_LIQUID);
					break;
				}
				
				case LIQUID_DISINFECTANT:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_disinfectant", Colors.COLOR_LIQUID);
					break;
				}
	
				case LIQUID_SALINE:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "#inv_inspect_saline", Colors.COLOR_LIQUID);
					break;
				}
				
				default:
				{
					WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "ERROR", Colors.COLOR_LIQUID);
					break;
				}
			}
		}
		else
		{
			WidgetTrySetText(root_widget, "ItemLiquidTypeWidget", "");
		}
	}
#endif	

*/
};