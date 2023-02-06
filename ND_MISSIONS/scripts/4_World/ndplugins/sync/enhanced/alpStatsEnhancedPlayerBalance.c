
class alpStatsEnhancedPlayerBalance extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedPlayerBalance(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.PLAYER_BALANCE;
	}
		
	
	override protected bool GetValueServer(out float value)
	{

		alp_Value = (float) alp_Player.GetRP().GetCart().GetBankBalance();
		
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

	override bool IsTraderStats()
	{
		return true;
	}	

}