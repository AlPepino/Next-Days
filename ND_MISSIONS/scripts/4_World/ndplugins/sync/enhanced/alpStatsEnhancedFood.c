class alpStatsEnhancedFood extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedFood(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.FOOD;
	}
		
	
	override protected bool GetValueServer(out float value)
	{

		alp_Value = alp_Player.GetStatEnergy().Get() / alp_Player.GetStatEnergy().GetMax() * 100;
		
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