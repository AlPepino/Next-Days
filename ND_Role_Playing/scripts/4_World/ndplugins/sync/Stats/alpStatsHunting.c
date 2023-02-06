class alpStatsHunting extends alpStatsBase
{

	
	void alpStatsHunting(PlayerBase player)
	{
		alp_Type = alpRPelements.HUNTING;
		NUM_OF_BITS = 6;
	}
	
	override void Update()
	{
		alp_Value = alp_Player.GetStatPerkHunting().Get();
	}
	

}

