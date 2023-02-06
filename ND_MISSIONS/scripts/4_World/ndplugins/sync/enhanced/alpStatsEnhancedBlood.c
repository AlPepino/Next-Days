class alpStatsEnhancedBlood extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedBlood(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.BLOOD;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
	
		
		alp_Value = alp_Player.GetHealth("", "Blood") / alp_Player.GetMaxHealth("", "Blood") * 100;
		
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