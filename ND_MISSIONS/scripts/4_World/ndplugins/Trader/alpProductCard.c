
class alpProductCard
{

	string												alp_ClassName;
	string												alp_DisplayName;	
	EntityAI											alp_EntityAI;
	EntityAI											alp_PlayersEntityAI;
	ref alpTraderItemConfig								alp_Config;
	
	ref array<EntityAI>									alp_ReservedItems;
	
	ref array<string>									alp_InInventory
	

	
	void alpProductCard(string className, alpTraderItemConfig config, array<string> ininventory = null, EntityAI ent = null )
	{
		alp_ReservedItems = new array<EntityAI>;
		
		alp_PlayersEntityAI = ent;
			

		
		alp_ClassName			= className;
		alp_DisplayName			= alpUF.GetDisplayName( alp_ClassName );
		
		alp_Config = config;
		
		alp_InInventory = ininventory;		
	}
	
	void ~alpProductCard()
	{
		if ( alp_EntityAI )
		{
			GetGame().ObjectDelete( alp_EntityAI );
		}
		ClearReservedItems(true);
	}
	array<string> GetIndexedItemToSell()
	{
		return alp_InInventory;
	}
	void ClearReservedItems(bool all = false)
	{
		if ( alp_ReservedItems )
		{
			
			for (int i = 0; i < alp_ReservedItems.Count();)
			{
				EntityAI ent = alp_ReservedItems.Get(i);
				if ( ent )
				{
					GetGame().ObjectDelete( ent );
					alp_ReservedItems.Remove(i);
				}
				if (!all)
				{
					break;
				}				
			}
		}			
	}
	
	EntityAI GetEntity()
	{

		if ( alp_PlayersEntityAI )
		{
			return alp_PlayersEntityAI;
		}
	
		if (!alp_EntityAI)
		{
			alp_EntityAI = EntityAI.Cast( GetGame().CreateObject( alp_ClassName,"0 0 0",true,false,false ) );					
		}

		return alp_EntityAI;
	
	}
	string GetType()
	{
		return alp_ClassName;
	}
	int GetValue()
	{
		int value;
		alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
		
		EntityAI ent = GetEntity();		
		if ( ent.IsTransport() )
		{
			CarScript car = CarScript.Cast( ent );
			if ( car )
			{
				value = car.GetDefaultPrice();
			}				
		}
		else
		{
			ItemBase itm = ItemBase.Cast( ent );
			if ( itm )
			{				
				if ( itm.IsWeapon() )
				{
					array<string> allowedAtt = trader.Stock.GetKeyArray();
					value = itm.GetDefaultPrice(true, allowedAtt);	
				}
				else
				{
					value = itm.GetDefaultPrice();
				}
			}		
		}
		//TO DO TRADER EFFECTS PRICE	
		
		float coef = GetPlayerCoef( trader ) * alpBANK.GetCurrencyRate( trader.CurrencyID );		
		
		return (int) value * coef;
	}	
	int GetPrice()
	{
		alpTraderCategories category = alpTraderCoreBase.alp_CategoriesMapped.Get( alp_Config.CategoryID );
		
		int			stockCap		= category.StockCap;
		float 		sellingRatioMin = category.SellingRatioMin;
		float		sellingRatioMax	= category.SellingRatioMax;
		float 		buingRatioMin	= category.BuingRatioMin;		
		
		float		buy,sell,minB,minS,maxS,delta;
		

		int value = GetValue();

		if (!stockCap) 
		{
			if ( sellingRatioMin != 1 )
			{
				buy = value * (1 - GetSales() );								
				if ( sellingRatioMin != 0 ) sell = value * ( sellingRatioMin + GetSales() );
				if (sell >= buy ) sell = buy * 0.95;
			}
			else 
			{
				buy = value;	
				sell = value * sellingRatioMin;		
			}
		}	
		else 
		{	
			minB = value *  buingRatioMin;
			delta = value - minB;
			delta = delta / stockCap;
			

			
			buy = ( value - Math.Min(GetCount() ,stockCap) * delta );
			
			minS = buy * sellingRatioMin;		
			maxS = buy * sellingRatioMax;		
			delta = maxS - minS;
			delta = delta / stockCap;
			
			
			sell = ( maxS - Math.Min(GetCount() ,stockCap) * delta );
			
			//reputation cost influence
			if ( sellingRatioMin != 1)
			{
				if ( sellingRatioMin != 0 ) sell += buy * GetSales();
			
				buy = buy * (1 - GetSales() );			
				
				if (sell > buy ) sell = buy * 0.95;								
			}
														
		}			
		//TO DO TRADER EFFECTS PRICE	
		alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
		float sale = trader.CashAffectsPrices;


		if ( sale )
		{
			PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
			float cash;
			player.GetSyncData().GetElementEnhanced( alpRPelementsEnahnced.TRADER_BALANCE).GetValue( cash );
			
			int minimal = trader.CashMinimal;
			int optimal = trader.CashOptimal;
			

			if ( cash > minimal && cash < optimal )
			{

				sale = 0;
			}
			else if ( cash <= minimal )
			{
				sale *=-1;	
			}		
		}

		if (GetND().GetMS().GetTrader().IsBuyMenu())
		{
			buy = buy  *( 1 + sale );
			return  (int)  buy;
		}
		else
		{
			sell =  sell * ( 1 + sale );
			return (int)  sell;
		}
	}
	
	
	float GetPlayerCoef(alpNPCtraderStock trader)
	{
		return trader.PricelistRatioHero;	
	}
	
	int GetRequiredReputation()
	{
		return alp_Config.RequiredReputation;
	}
	
	string GetDisplayName()
	{
		return alp_DisplayName;
	}	
	int GetCount()
	{
		int count = GetND().GetMS().GetTrader().GetCount(  GetType() , GetND().GetMS().GetTrader().alp_NPC_ID );	
		return count;
	}
	
	int GetAvailableItem()
	{
		if ( GetND().GetMS().GetTrader().IsBuyMenu() )
		{
			return GetCount();
		}	
		else
		{
			return alp_InInventory.Count();
		}

	}
	
	int alp_Reserved;
	int GetCountInCart()
	{
		return alp_Reserved;
	}
	
	int GetCountReserved()
	{
		return alp_Reserved;
	}
	bool AddReservation()
	{
		
		if ( alp_Reserved < GetAvailableItem() )
		{
			if ( GetND().GetMS().GetTrader().IsBuyMenu() && !GetEntity().IsTransport() )
			{
				PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
				EntityAI ent = player.GetRP().GetCart().InsertIntoCart( GetType() );
				if (!ent)
				{
					return false;
				}
				else
				{
					alp_ReservedItems.InsertAt(ent, 0 );
				}	
			}
			
			alp_Reserved++;
			return true;
		}
		return false;
	}
	
	void RemoveReservation(bool all=false)
	{
		if (alp_Reserved>0)
		{
			if (all)
			{
				alp_Reserved = 0;
				ClearReservedItems(true);
			}
			else
			{
				ClearReservedItems();
				alp_Reserved--;
			}
			
		}
	}
	
	bool IsTradAble()
	{
		if ( GetND().GetMS().GetTrader().IsBuyMenu() )
		{
			return alp_Config.CanBuy;
		}
		else
		{
			return alp_Config.CanSell;
		}
	}
	
	bool CanBeTrade()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if (HasReputation() && IsTradAble() && IsEmpty() && player.GetRP().GetCart().CheckCashCondition( GetPrice() ) )
		{	
			return true;
		}
		else
		{		
			return false;
		}

	}
	
	bool IsEmpty()
	{
		if ( GetND().GetMS().GetTrader().IsBuyMenu() || GetEntity().IsInherited( Magnum_Base ))
			return true;
		
		
		if ( alp_PlayersEntityAI )
		{
			if ( alp_PlayersEntityAI.IsTransport() )
			{
				CarScript car = CarScript.Cast( alp_PlayersEntityAI );
				
				if ( car )
				{
					if ( car.GetCargoCountALP() )  //car.GetAttachmentCountALP() || 
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				return false;
			}
			else
			{
				ItemBase item = ItemBase.Cast( alp_PlayersEntityAI );
				if ( item )
				{
					if ( Weapon_Base.Cast( item.GetHierarchyParent() ) )
					{
						return false;
					}
					
					if ( item.IsWeapon() )
					{
						return true;
					}
					else
					{					
						if ( item.GetAttachmentCountALP() || item.GetCargoCountALP() )
						{
							return false;
						}
						else
						{
							return true;
						}					
					}
			
					
					
					/*
					if ( item.GetAttachmentCountALP() || item.GetCargoCountALP() )
					{
						return false;
					}
					else
					{
						return true;
					}
					*/
				}
				return false;				
			}
		
		}
		return false;
	}
	
	
	//TO DO: reputation skill
	bool HasReputation()
	{
		return true;
	}
	
	float GetSales()
	{
		return 0;
	}

}