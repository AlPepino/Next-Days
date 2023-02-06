class alpStatsEnhancedRadiationDoses extends alpStatsBaseEnhanced
{
	

	void alpStatsEnhancedRadiationDoses(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.RADIATIONDOSES;
	}
		
	
	override protected bool GetValueServer(out float value)
	{

		if (alp_Player.GetRP().HasDosimeter() )
		{
		
					
			alp_Value =  (float) alp_Player.GetRP().GetRecievedRadiation();	
			
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
		else
		{
			value = alp_LastValue;
			return false;					
		}

	}
	
	override bool IsRadiationStats()
	{
		return true;	
	}
}