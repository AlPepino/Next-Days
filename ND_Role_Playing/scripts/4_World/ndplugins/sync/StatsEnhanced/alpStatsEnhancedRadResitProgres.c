
class alpStatsEnhancedRadResitProgres extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedRadResitProgres (PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.RAD_RESISTPROGRES;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
		int level = 	alp_Player.GetStatPerkRadiationResistance().Get();
		int levelCap = GetND().GetRP().GetPerkRadiationResistanceLevelCup();
		
		if ( level < levelCap )
		{
			alp_Value = alp_Player.GetStatPerkRadiationResistanceProgress().Get() / alp_Player.GetRP().GetRadiationResistanceRequiredExp( level + 1 ) * 100;	
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