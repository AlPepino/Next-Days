
class alpStatsEnhancedHuntingProgres extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedHuntingProgres(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.HUNTINGPROGRES;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
		int level = 	alp_Player.GetStatPerkHunting().Get();
		int levelCap = GetND().GetRP().GetPerkHuntingLevelCup();
		
		if ( level < levelCap )
		{
			alp_Value = alp_Player.GetStatPerkHuntingProgress().Get() / alp_Player.GetRP().GetHuntingRequiredExp( level + 1 ) * 100;	
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