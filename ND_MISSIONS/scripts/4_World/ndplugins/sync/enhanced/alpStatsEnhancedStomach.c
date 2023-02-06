class alpStatsEnhancedStomach extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedStomach(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.STOMACH;
	}
		
	
	override protected bool GetValueServer(out float value)
	{

		alp_Value = alp_Player.m_PlayerStomach.GetStomachVolume() / PlayerConstants.BT_STOMACH_VOLUME_LVL3 * 100;
		
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