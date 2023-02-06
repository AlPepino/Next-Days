
class alpSalmonella extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().Salmonella;
	}
	
	
	override void CureDisease()
	{
		alp_Player.m_AgentPool.SetAgentCount( eAgents.SALMONELLA , 0 );
			
		
		if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_SALMONELLA))
		{
			alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_SALMONELLA);
		}		
	}
			
}
