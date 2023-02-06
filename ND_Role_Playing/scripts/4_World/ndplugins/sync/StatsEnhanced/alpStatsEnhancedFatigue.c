class alpStatsEnhancedFatigue extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedFatigue(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.FATIGUE;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
		

					
		alp_Value = alp_Player.GetStatTiredness().Get() /  alp_Player.GetStatTiredness().GetMax() * 100;	
		
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