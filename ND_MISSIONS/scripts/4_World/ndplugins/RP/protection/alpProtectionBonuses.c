


class alpProtectionBonuses 
{
	protected bool alp_HasDosimeter;
	protected float alp_Biological;
	protected float alp_Chemical;
	protected float alp_Radiation;
	
	protected float alp_FilterEfficiency;
	
	protected float alp_HealtLevel;
	protected float alp_Quantity = 1;
	
	protected ItemBase alp_Item;
	
	void alpProtectionBonuses(ItemBase itm)
	{
		alp_Item = itm;
		
		alpProtectionItem item = GetND().GetMS().GetProtectionBonuses( alp_Item.GetType() );
		
		if (!item)
		{
		
			string subclass_path = "CfgVehicles " + alp_Item.GetType() + " Protection hasdosimeter";		
			alp_HasDosimeter = GetGame().ConfigGetInt(subclass_path);
			
			subclass_path = "CfgVehicles " + alp_Item.GetType() + " Protection radiation";		
			alp_Radiation = GetGame().ConfigGetFloat(subclass_path);		
			
			subclass_path = "CfgVehicles " + alp_Item.GetType() + " Protection chemical";		
			alp_Chemical = GetGame().ConfigGetFloat(subclass_path);			
			
			subclass_path = "CfgVehicles " + alp_Item.GetType() + " Protection biological";		
			alp_Biological = GetGame().ConfigGetFloat(subclass_path);		
			
			subclass_path = "CfgVehicles " + alp_Item.GetType() + " Protection filterefficiency";		
			alp_FilterEfficiency = GetGame().ConfigGetFloat(subclass_path);						
		}
		else
		{
			alp_HasDosimeter	= item.hasdosimeter;
			alp_Radiation = item.radiation;
			alp_Chemical = item.chemical;
			alp_Biological = item.biological;
			alp_FilterEfficiency = item.filterefficiency;
		}

		
		UpdateState();		
		
		
	}
	
	ItemBase GetItem()
	{
		return alp_Item;
	}
	
	void UpdateState()
	{
		
		alp_HealtLevel = GetND().GetMS().GetNBCefficiency( alp_Item.GetHealthLevel() );
		
		
		if ( alp_Item.HasQuantity() && alp_Item.GetQuantity() <= 0 )
		{
			alp_Quantity = 0;
		}
		else
		{
			alp_Quantity = 1;
		}

	}
	
	bool HasDosimeter()
	{
		return alp_HasDosimeter;
	}
	float GetFilterEfficiency()
	{
		return alp_FilterEfficiency;
	}	
	
	float GetProtection(int type)
	{	
		UpdateState();
				
		switch (type)
		{
			case alpPROTECTION.RADIATION:				
				return alp_Radiation * alp_HealtLevel * alp_Quantity;
			case alpPROTECTION.BIOLOGICAL:
				return alp_Biological * alp_HealtLevel * alp_Quantity;
			case alpPROTECTION.CHEMICAL:
				return alp_Chemical * alp_HealtLevel * alp_Quantity;
		}	
		return 0;
	}
	

				
	

		
}
