
class alpStatsIsRained extends alpStatsBase
{

	
	void alpStatsIsRained(PlayerBase player)
	{
		alp_Type = alpRPelements.ISRAINED;
		NUM_OF_BITS = 1;
	}
	
	override void Update()
	{
		if ( alp_Player.m_Environment )
		{
			alp_Value = alp_Player.m_Environment.IsRainingALP();
			alp_Player.GetRP().SetRainedState( alp_Value );
		}
		
	}
	

	override void SetValue(int value)
	{
		alp_Value = value;
		
		alp_Player.GetRP().SetRainedState( value );
	}	
	
}


