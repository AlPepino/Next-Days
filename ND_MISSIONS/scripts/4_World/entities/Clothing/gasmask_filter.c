
modded class GasMask_Filter : ItemBase
{

	

	override float GetFilterDamageRatio() 
	{
		float ratio = super.GetFilterDamageRatio();
		
		float adjusted = GetND().GetMS().GetOptionsRadiation().FilterDamageRatio;
		
		if ( adjusted ) {
			ratio = adjusted;		
		} 
		
		return ratio;
		//return 0.09; //Health lost per quantity consumed
	}
}

modded class GasMask_Filter_Improvised: GasMask_Filter
{
	override float GetFilterDamageRatio() 
	{
		float ratio = super.GetFilterDamageRatio();
		
		float adjusted = GetND().GetMS().GetOptionsRadiation().ImprovisedFilterDamageRatio;
		
		if ( adjusted ) {
			ratio = adjusted;		
		} 
		
		return ratio;		
		//return 0.25; //Health lost per quantity consumed
	}
}