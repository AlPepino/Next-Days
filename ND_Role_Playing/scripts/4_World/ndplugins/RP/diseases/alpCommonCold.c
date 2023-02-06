



class alpCommonCold extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().Commoncold;
	}
		

	override void CureDisease()
	{
		alp_Player.m_AgentPool.SetAgentCount( eAgents.INFLUENZA , 0 );
			
		
		if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_COMMON_COLD))
		{
			alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_COMMON_COLD);
		}		
	}
	
	override bool IsEnable()
	{
		if ( alp_Player.GetRP().alp_MedicList.Get( alpDiseases.INFLUENZA ).IsInfected() )
		{
			return false;
		}
		
		return true;
	}		
}
