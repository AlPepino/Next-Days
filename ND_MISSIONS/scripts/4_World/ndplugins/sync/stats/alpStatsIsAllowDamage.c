
class alpStatsIsAllowDamage extends alpStatsBase
{

	
	void alpStatsIsAllowDamage(PlayerBase player)
	{
		alp_Type = alpRPelements.ISALLOWDAMAGE;
		NUM_OF_BITS = 1;
	}
	
	override void Update()
	{
		alp_Value = alp_Player.GetRP().IsAllowedDamage();
	}
	

	override void SetValue(int value)
	{
		alp_Value = value;
		
		alp_Player.GetRP().SetAllowedDamage( value );
	}	
	
}


