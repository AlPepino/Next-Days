


class alpStatsDiseases extends alpStatsBase
{

	
	
	
	void alpStatsDiseases(PlayerBase player)
	{
		alp_Type = alpRPelements.DISEASES;
		NUM_OF_BITS = 17;
	}
	
	override void Update()
	{
		alp_Value = alp_Player.GetRP().GetDiseases();
	}
	


}


