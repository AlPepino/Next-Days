modded class FireplaceBase extends ItemBase
{
	bool alp_PermaFire;
	
	
		
	
	override protected void SpendFireConsumable ( float amount )
	{
		if ( alp_PermaFire )
		{
			CalcAndSetQuantity();
		}
		else 
		{
			super.SpendFireConsumable( amount );
		}
	}
}