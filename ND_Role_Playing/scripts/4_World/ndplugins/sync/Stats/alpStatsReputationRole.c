class alpStatsReputationRole extends alpStatsBase
{

	
	void alpStatsReputationRole(PlayerBase player)
	{
		alp_Type = alpRPelements.REPUTATION_ROLE;
		NUM_OF_BITS = 1;
	}
	
	override void Update()
	{
		int level = alp_Player.GetStatPerkReputation().Get();
		
		if (level >= 0)
		{
			alp_Value = ALP_RP_HERO; 
		}
		else
		{
			alp_Value = ALP_RP_BANDIT; 
		}
		
	
	}
	

}


