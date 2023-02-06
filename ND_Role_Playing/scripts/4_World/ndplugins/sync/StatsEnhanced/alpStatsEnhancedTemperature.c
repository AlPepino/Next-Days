
class alpStatsEnhancedTemperature extends alpStatsBaseEnhanced
{
	float alp_LastTemp = -1;
	
	bool alp_HasFever;
	

	void alpStatsEnhancedTemperature(PlayerBase player)
	{

		alp_Type	= alpRPelementsEnahnced.TEMPERATURE;
	}
		
	
	override protected bool GetValueServer(out float value)
	{
		

					
		alp_Value = GetTemperatureValue();	
		
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

	float GetTemperatureValue()
	{

		float value;
		if( alp_Player.GetModifiersManager() && alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_FEVER))
		{
			if ( alp_HasFever )
			{
				if (alp_LastTemp > 0 )
				{
					return 	alp_LastTemp;	
				}
				value = Math.RandomFloatInclusive(PlayerConstants.HIGH_TEMPERATURE_L, PlayerConstants.HIGH_TEMPERATURE_H);
				
				alp_LastTemp = value;				
			}
			else
			{
				alp_HasFever = true;
				
				value = Math.RandomFloatInclusive(PlayerConstants.HIGH_TEMPERATURE_L, PlayerConstants.HIGH_TEMPERATURE_H);
				
				alp_LastTemp = value;
			}

		}
		else
		{
			if ( alp_HasFever )
			{
				alp_HasFever = false;
				value = Math.RandomFloatInclusive(PlayerConstants.NORMAL_TEMPERATURE_L, PlayerConstants.NORMAL_TEMPERATURE_H);	
				alp_LastTemp = value;
			}
			else
			{
				if (alp_LastTemp > 0 )
				{
					return 	alp_LastTemp;	
				}
				value = Math.RandomFloatInclusive(PlayerConstants.NORMAL_TEMPERATURE_L, PlayerConstants.NORMAL_TEMPERATURE_H);	
				alp_LastTemp = value;							
			}
						
		}

		return alp_LastTemp;
	}	
		
	override bool IsPlayerStats()
	{
		return true;
	}	
}