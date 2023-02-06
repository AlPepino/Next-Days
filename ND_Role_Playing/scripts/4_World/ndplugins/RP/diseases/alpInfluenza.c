
class alpInfluenza extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().Influenza;
	}
		

	override void CureDisease()
	{
		alp_Player.m_AgentPool.SetAgentCount( eAgents.INFLUENZA , 0 );
			
		
		if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_INFLUENZA))
		{
			alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_INFLUENZA);
		}		
	}
			
}
