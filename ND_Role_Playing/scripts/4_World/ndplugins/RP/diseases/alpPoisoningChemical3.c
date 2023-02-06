
class alpPoisoningChemica1_3 extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().ChemicalPoisoningL3;
	}
	
	override void CureDisease()
	{
		alp_Player.m_AgentPool.SetAgentCount( eAgents.CHEMICAL_POISON , 0 );
			
		
		if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_CONTAMINATION3))
		{
			alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_CONTAMINATION3);
		}		
	}
			
}
