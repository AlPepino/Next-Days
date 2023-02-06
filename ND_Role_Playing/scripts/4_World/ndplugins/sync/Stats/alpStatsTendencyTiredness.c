class alpStatsTendencyTiredness extends alpStatsBase
{
	protected int TENDENCY_MASK = 7;// first x bits
	protected int SERIOUSNESS_BIT_MASK = 7;// second x bits
	protected int SERIOUSNESS_BIT_OFFSET = 3;//bit offset - points to where seriousness bit starts(TODO: get as log from mask)
	
	int		alp_ValueLast = -99999;
		
	
	PluginPlayerStatus 	m_ModulePlayerStatus;
	
	void alpStatsTendencyTiredness(PlayerBase player)
	{
		m_ModulePlayerStatus = PluginPlayerStatus.Cast(GetPlugin(PluginPlayerStatus));
		
		alp_Type = alpRPelements.TDCY_TIREDNESS;
		NUM_OF_BITS = 6;
	}
	
	override void Update()
	{
		//alp_Value = alp_Player.GetStatTiredness().Get();
	}
	
	
	override void SetValue(int value)
	{
		alp_Value = value;
		
		//tendency 
		
		UpdateHUD();
	}	

	
	bool IsValueChanged()
	{
		return !(alp_Value == alp_ValueLast);
	}
	
	void UpdateHUD()
	{
		alp_ValueLast = alp_Value;
		
		int seriousness = alp_Value >> SERIOUSNESS_BIT_OFFSET;
		int tendency = TENDENCY_MASK & alp_Value;		
		
		if(tendency > 3) 
		{
			tendency = -(tendency - 3);
		}		
		
		m_ModulePlayerStatus.DisplayTendency(NTFKEY_ALPTIREDNESS, tendency, TranslateLevelToStatus(seriousness));
	}
	
	int BitToDec(int mask, int index, int length)
	{
		int value = mask & (GetCompareMask() << index);
		value = value >> index;
		return value;
	}


	int TranslateLevelToStatus(int level)
	{
		if( level == DSLevels.WARNING )
			return 2;
		if( level == DSLevels.CRITICAL )
			return 3;
		if( level == DSLevels.BLINKING )
			return 4;
		if( level == DSLevels.EXTRA )
			return 5;
		return 1;
	}
	
	void SetSeriousnessLevel( DSLevels level )
	{
		alp_Value = (~(SERIOUSNESS_BIT_MASK << SERIOUSNESS_BIT_OFFSET)) & alp_Value;//clear the last value
		alp_Value = (level << SERIOUSNESS_BIT_OFFSET)  | alp_Value;
	}	
	void SetTendency(int tendency)
	{
		alp_Value = (~TENDENCY_MASK) & alp_Value;//clear the last value
		alp_Value =  tendency | alp_Value;//insert the new one
		//PrintString(m_Value.ToString());
	}	
}


