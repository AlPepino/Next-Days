
class alpStatsEnhancedRadiationSickStage extends alpStatsBaseEnhanced
{

	

	void alpStatsEnhancedRadiationSickStage(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.RADIATIONSICKSTAGE;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
		

					
		alp_Value = GetRadSickStage();	
		
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

	int GetRadSickStage()
	{

		
		return alp_Player.GetRP().GetRadiationSickStage();
	}	
		
	override bool IsPlayerStats()
	{
		return true;
	}
}