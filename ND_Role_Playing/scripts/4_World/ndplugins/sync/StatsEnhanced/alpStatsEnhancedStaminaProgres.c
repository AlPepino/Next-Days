
class alpStatsEnhancedStaminaProgress extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedStaminaProgress(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.STAMINAPROGRES;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
		int level = 	alp_Player.GetStatPerkStamina().Get();
		int levelCap = GetND().GetRP().GetPerkStaminaLevelCup();
		
		if ( level < levelCap )
		{
			alp_Value = alp_Player.GetStatPerkStaminaProgress().Get() / alp_Player.GetRP().GetStaminaRequiredExp( level + 1 ) * 100;	
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