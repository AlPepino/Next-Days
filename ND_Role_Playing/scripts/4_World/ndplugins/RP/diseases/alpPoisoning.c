
class alpPoisoning extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().FoodPoisoning;
	}
	
	override void CureDisease()
	{
		alp_Player.m_AgentPool.SetAgentCount( eAgents.FOOD_POISON , 0 );
				
	}
			
}
