class alpStatsStamina extends alpStatsBase
{

	
	void alpStatsStamina(PlayerBase player)
	{
		alp_Type = alpRPelements.STAMINA;
		NUM_OF_BITS = 6;
	}
	
	override void Update()
	{
		alp_Value = alp_Player.GetStatPerkStamina().Get();
	}
	

}


