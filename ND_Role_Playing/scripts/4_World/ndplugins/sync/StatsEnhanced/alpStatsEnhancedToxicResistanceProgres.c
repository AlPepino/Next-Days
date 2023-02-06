
class alpStatsEnhancedToxicResistanceProgres extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedToxicResistanceProgres(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.TOXIC_RESISTPROGRES;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
		int level = alp_Player.GetStatPerkToxicResistance().Get() ;

		int levelCap = GetND().GetRP().GetPerkToxicResistanceLevelCup();

		if ( level < levelCap )
		{
			alp_Value =	alp_Player.GetStatPerkToxicResistanceProgress().Get() / alp_Player.GetRP().GetToxicResistanceRequiredExp( level + 1 ) * 100;	
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