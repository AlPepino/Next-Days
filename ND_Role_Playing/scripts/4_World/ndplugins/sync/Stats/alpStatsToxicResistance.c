class alpStatsToxicResistance extends alpStatsBase
{

	
	void alpStatsToxicResistance(PlayerBase player)
	{
		alp_Type = alpRPelements.TOXIC_RESIST;
		NUM_OF_BITS = 6;
	}
	
	override void Update()
	{
		alp_Value = alp_Player.GetStatPerkToxicResistance().Get();
	}
	

}


