
class alpStatsEnhancedReputationProgress extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedReputationProgress(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.REPUTATIONPROGRES;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
		int level = 	Math.AbsInt( alp_Player.GetStatPerkReputation().Get() );
		int levelCap = GetND().GetRP().GetPerkReputationLevelCup();

		if ( level < levelCap )
		{
			alp_Value = Math.AbsFloat( alp_Player.GetStatPerkReputationProgress().Get() ) / alp_Player.GetRP().GetReputationRequiredExp( level + 1 ) * 100;	
		}
		else
		{
			alp_Value = 100;
		}
		
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