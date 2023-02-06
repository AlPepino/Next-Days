

class alpWoundInfection1 extends alpDisease
{
	
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().WoundInfectionL1;
	}
	
	
	override void CureDisease()
	{

		
		alp_Player.m_AgentPool.SetAgentCount( eAgents.WOUND_AGENT , 0 );
			
		
		if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_WOUND_INFECTION1))
		{
			alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_WOUND_INFECTION1);
		}			
		
		if( alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_DISINFECTION))//effectively resets the timer
		{
			alp_Player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_DISINFECTION );
		}
		alp_Player.GetModifiersManager().ActivateModifier( eModifiers.MDF_DISINFECTION );		
	}
	
	override bool IsEnable()
	{
		if ( alp_Player.GetRP().alp_MedicList.Get( alpDiseases.WOUNDINFECTION_2 ).IsInfected() )
		{
			return false;
		}
		
		return true;
	}	
	
}

class alpWoundInfection2 extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().WoundInfectionL2;
	}
	override void CureDisease()
	{

		alp_Player.m_AgentPool.SetAgentCount( eAgents.WOUND_AGENT , 0 );
			
		if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_WOUND_INFECTION2))
		{
			alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_WOUND_INFECTION2);
		}	
		
		if( alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_DISINFECTION))//effectively resets the timer
		{
			alp_Player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_DISINFECTION );
		}
		alp_Player.GetModifiersManager().ActivateModifier( eModifiers.MDF_DISINFECTION );	
			
		
	}
}
