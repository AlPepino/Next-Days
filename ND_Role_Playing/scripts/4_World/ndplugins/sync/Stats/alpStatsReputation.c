class alpStatsReputation extends alpStatsBase
{

	
	void alpStatsReputation(PlayerBase player)
	{
		alp_Type = alpRPelements.REPUTATION;
		NUM_OF_BITS = 6;
	}
	
	override void Update()
	{
		alp_Value = Math.AbsInt(  alp_Player.GetStatPerkReputation().Get() );
		
		
		if ( alp_Player.GetIdentity() ){
			alp_Player.GetIdentity().SetPlayerLevel( alp_Value );
		}
	}
	

}


