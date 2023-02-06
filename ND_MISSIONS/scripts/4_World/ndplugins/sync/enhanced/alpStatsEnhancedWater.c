class alpStatsEnhancedWater extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedWater(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.WATER;
	}
		
	
	override protected bool GetValueServer(out float value)
	{

		alp_Value = alp_Player.GetStatWater().Get() / alp_Player.GetStatWater().GetMax() * 100;
		
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