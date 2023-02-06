class alpBrainDisease extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().BrainSick;
	}
	
	override void CureDisease()
	{
		alp_Player.m_AgentPool.SetAgentCount( eAgents.BRAIN , 0 );
			
		
		if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_BRAIN))
		{
			alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_BRAIN);
		}	
	}
}