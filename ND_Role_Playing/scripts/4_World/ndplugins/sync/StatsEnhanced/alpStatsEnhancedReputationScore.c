class alpStatsEnhancedReputationScore extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedReputationScore(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.SCORE;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
		float score;

		if ( GetND().GetRP().GetPerkReputation().StoreLastSessionInHoF )
		{
			score = alp_Player.GetStatCurrentScore().Get();//current session				
		}	
		else
		{
			score = alp_Player.GetRP().GetTotalReputationExp();
		}
		
		
					
		alp_Value = score;	
		
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