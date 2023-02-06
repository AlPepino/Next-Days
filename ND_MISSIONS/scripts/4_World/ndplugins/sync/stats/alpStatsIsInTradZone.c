
class alpStatsIsInTradeZone extends alpStatsBase
{

	
	void alpStatsIsInTradeZone(PlayerBase player)
	{
		alp_Type = alpRPelements.ISINTRADERZONE;
		NUM_OF_BITS = 1;
	}
	
	override void Update()
	{
		alp_Value = alp_Player.GetRP().IsInTradeZone();
	}
	
	override void SetValue(int value)
	{
		alp_Value = value;
		
		alp_Player.GetRP().SetInTradeZone( value );
	}	
		

}


