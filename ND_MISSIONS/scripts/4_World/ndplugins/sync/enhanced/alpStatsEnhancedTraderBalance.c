class alpStatsEnhancedTraderBalance extends alpStatsBaseEnhanced
{
		

	void alpStatsEnhancedTraderBalance(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.TRADER_BALANCE;
	}
		
	
	override protected bool GetValueServer(out float value)
	{

		alp_Value = (float) GetND().GetMS().GetTrader().GetTraderBalance(alp_Player);
		
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
/*
	override void SetValue(float value)
	{
		alp_Value = value;//used on client only
		
		
	}	
*/	
	override bool IsTraderStats()
	{
		return true;
	}	

}