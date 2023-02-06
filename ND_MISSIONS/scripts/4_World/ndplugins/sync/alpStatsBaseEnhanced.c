enum alpRPelementsEnahnced
{

	HEALTH,
	BLOOD,
	WATER,
	FOOD,	
	STOMACH,
	
	RADIATIONDOSES,
	FATIGUE,
	
	TEMPERATURE,
	RADIATIONSICKSTAGE,
	
	STAMINAPROGRES,
	
	RAD_RESISTPROGRES,
	
	TOXIC_RESISTPROGRES,

	REPUTATIONPROGRES,
	
	HUNTINGPROGRES,
	
	SCORE,
/*	
	SAVED_STAMINA_LEVEL,
	SAVED_STAMINA_PROGRESS,
	
	SAVED_RAD_RESIST_LEVEL,
	SAVED_RAD_RESIST_PROGRESS,	
	
	SAVED_TOXIC_RESIST_LEVEL,
	SAVED_TOXIC_RESIST_PROGRESS,	
	
	SAVED_REPUTATION_LEVEL,
	SAVED_REPUTATION_PROGRESS,	
	
	SAVED_HUNTING_LEVEL,
	SAVED_HUNTING_PROGRESS,	
	
	SAVED_SOFTSKILLS,
	SAVED_HARDSKILLS,
	
	SAVED_COLDRESIST,
*/	

	TRADER_BALANCE,
	PLAYER_BALANCE,	
	
	COUNT
}




class alpStatsBaseEnhanced
{

	int		alp_Type;

		
	float   alp_Value;
	float 	alp_LastValue = -99999999;
	
	PlayerBase alp_Player;
	
	void alpStatsBaseEnhanced(PlayerBase player)
	{
		alp_Player = player;
	}
	
	bool GetValue(out float value)
	{//if last value != current value return true
		
		
		if ( GetGame().IsServer() )
			return GetValueServer(value);
		else
			return GetValueClient(value);		
	
	}
	
	void SetValue(float value)
	{
		alp_Value = value;//used on client only
	}
	
	
	protected bool GetValueServer(out float value)
	{
	
		return false;
	}
	
	protected bool GetValueClient(out float value)
	{
		if (alp_LastValue != alp_Value )
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
	
	int GetType()
	{
		return alp_Type;
	}
	
	bool IsPlayerStats()
	{
		return false;
	}
	
	bool IsRadiationStats()
	{
		return false;	
	}
	bool IsTraderStats()
	{
		return false;
	}
}