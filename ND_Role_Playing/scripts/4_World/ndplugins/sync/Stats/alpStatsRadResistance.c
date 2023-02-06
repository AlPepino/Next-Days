class alpStatsRadResistance extends alpStatsBase
{

	
	void alpStatsRadResistance(PlayerBase player)
	{
		alp_Type = alpRPelements.RAD_RESIST;
		NUM_OF_BITS = 6;
	}
	
	override void Update()
	{
		alp_Value = alp_Player.GetStatPerkRadiationResistance().Get();
	}
	

}


