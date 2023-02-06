
class alpCholera extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().Cholera;
	}
	
	override void CureDisease()
	{
		alp_Player.m_AgentPool.SetAgentCount( eAgents.CHOLERA , 0 );
			
		
		if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_CHOLERA))
		{
			alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_CHOLERA);
		}		
	}
			
}
