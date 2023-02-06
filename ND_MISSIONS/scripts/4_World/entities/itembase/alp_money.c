class alp_Cash extends Inventory_Base
{
	int GetMoneyValue()
	{
		int value = 1;
		
		string subclass_path = "CfgVehicles " + GetType() + " nominalValue";
		value = GetGame().ConfigGetInt(subclass_path);
		
		return value;
	}			
	int GetMonyeSum()
	{	
		if (GetQuantity()>0)
		{
		 	return GetMoneyValue() * GetQuantity();
		}
		else 
		{
			return GetMoneyValue();
		}
	
	}
	
	override string GetDisplayName()
	{
		string sdt = super.GetDisplayName();
		return FormatNumber(GetMonyeSum()) + " " + sdt;
	}
	
	string FormatNumber(float value)
	{		
		int 			v 		= value;		
		string 			text 	= v.ToString();
		int 			len 	= text.Length();
		string 			output  = "";
		int				s=0;
		len -=1;
		for (int i=len; i>=0;i--){
			
			if (s==3 || s==6 || s==9){
				output = text.Get(i) + " " + output;
			}
			else output = text.Get(i) + output;
			s++;
		}
		return output;
	}	
/*	
	int GetCurrencyType()
	{
		return 0;
	}
*/
}

class alp_Coin extends alp_Cash{}

class alp_Money extends alp_Cash
{
	//================================================================
	// IGNITION ACTION
	//================================================================
	override bool HasFlammableMaterial()
	{
		return true;
	}
	
	override bool CanBeIgnitedBy( EntityAI igniter = NULL )
	{
		if ( GetHierarchyParent() ) return false;
		
		return true;
	}
	
	override bool CanIgniteItem( EntityAI ignite_target = NULL )
	{
		return false;
	}
	
	override void OnIgnitedTarget( EntityAI ignited_item )
	{
	}
	
	override void OnIgnitedThis( EntityAI fire_source )
	{
		Fireplace.IgniteEntityAsFireplace( this, fire_source );
	}

	override bool IsThisIgnitionSuccessful( EntityAI item_source = NULL )
	{
		return Fireplace.CanIgniteEntityAsFireplace( this );
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionCreateIndoorFireplace);
		AddAction(ActionCreateIndoorOven);
		AddAction(ActionAttach);
		AddAction(ActionDetach);
	}	
	
}

class alp_CoinRare1 extends alp_Coin {}
class alp_Coin1 extends alp_Coin {}
class alp_Coin2 extends alp_Coin {}
class alp_Coin5 extends alp_Coin {}

class alp_Money10 extends alp_Money {}
class alp_Money20 extends alp_Money{}
class alp_Money50 extends alp_Money{}
class alp_Money100 extends alp_Money{}
class alp_Money500 extends alp_Money{}
class alp_Money1000 extends alp_Money{}


class alp_USD1 extends alp_Money{}

class alp_USD5 extends alp_Money{}
class alp_USD10 extends alp_Money{}
class alp_USD20 extends alp_Money{}
class alp_USD50 extends alp_Money{}
class alp_USD100 extends alp_Money{}
class alp_USD500 extends alp_Money{}
class alp_USD1000 extends alp_Money{}