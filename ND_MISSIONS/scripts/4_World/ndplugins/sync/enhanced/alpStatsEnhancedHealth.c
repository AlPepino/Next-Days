class alpStatsEnhancedHealth extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedHealth(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.HEALTH;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
	
		
		alp_Value = alp_Player.GetHealth("GlobalHealth", "Health") / alp_Player.GetMaxHealth("GlobalHealth", "Health") * 100;
		
		if ( alp_Value != alp_LastValue )
		{
			alp_LastValue = alp_Value;
			value = alp_Value;
			return true;
		}
		else
		{
			value = alp_LastValue;
			return false;
		}
	
	}
	
	override bool IsPlayerStats()
	{
		return true;
	}	

}