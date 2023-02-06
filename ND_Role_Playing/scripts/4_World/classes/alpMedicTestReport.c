
class alpMedicTestReport
{
	static void DisplayReport(ActionBase action, PlayerBase player, PlayerBase target)
	{
		EStatLevels immunityLevel = target.GetImmunityLevel();
		string immunityLevelStr;
		switch (immunityLevel)
		{
			
			case EStatLevels.GREAT: immunityLevelStr = "GREAT"; break;
			case EStatLevels.HIGH: immunityLevelStr = "HIGH"; break;
			case EStatLevels.MEDIUM: immunityLevelStr = "MEDIUM"; break;
			case EStatLevels.LOW: immunityLevelStr = "LOW"; break;
			case EStatLevels.CRITICAL: immunityLevelStr = "CRITICAL"; break;

		
		}
		
		string positive = "#me_disease_pozitive";
		string negative = "#me_disease_negative";
		
		string stateCholera,stateInfluenza,statePoisoning,stateWound,stateContamination,stateDrunkenness, stateSalmonela,stateRadiation;
		
		if (target.m_ModifiersManager)
		{
			if (target.GetSingleAgentCount( alpeAgents.RADIATION >= ALP_RADPOISON.L1 ) )
				stateRadiation = positive;
			else
				stateRadiation = negative;			
			
			if (target.m_ModifiersManager.IsModifierActive( eModifiers.MDF_SALMONELLA) )
				stateSalmonela = positive;
			else
				stateSalmonela = negative;			
			
			if (target.m_ModifiersManager.IsModifierActive( rModifiers.MDF_DRUNKENNESS) )
				stateDrunkenness = positive;
			else
				stateDrunkenness = negative;			
			
			if (target.m_ModifiersManager.IsModifierActive( eModifiers.MDF_CHOLERA) )
				stateCholera = positive;
			else
				stateCholera = negative;
			
			if (target.m_ModifiersManager.IsModifierActive( eModifiers.MDF_INFLUENZA) )
				stateInfluenza = positive;
			else
				stateInfluenza = negative;		
			
			if (target.m_ModifiersManager.IsModifierActive( eModifiers.MDF_POISONING) )
				statePoisoning = positive;
			else
				statePoisoning = negative;		
			
			if (target.m_ModifiersManager.IsModifierActive( eModifiers.MDF_WOUND_INFECTION1) || target.m_ModifiersManager.IsModifierActive( eModifiers.MDF_WOUND_INFECTION2))
				stateWound = positive;
			else
				stateWound = negative;							
			
			if (target.m_ModifiersManager.IsModifierActive( eModifiers.MDF_CONTAMINATION1) || target.m_ModifiersManager.IsModifierActive( eModifiers.MDF_CONTAMINATION2) || target.m_ModifiersManager.IsModifierActive( eModifiers.MDF_CONTAMINATION3))
				stateContamination = positive;
			else
				stateContamination = negative;				
		}
		
		
		action.SendMessageToClient(player, "#me_medical_record:");
		action.SendMessageToClient(player, "#me_immunity_desc: " + immunityLevelStr);
		action.SendMessageToClient(player, "#me_drunkenness_desc: " + target.GetSingleAgentCount(alpeAgents.DRUNKENNESS).ToString() + " (" + stateDrunkenness + ")");
		
		action.SendMessageToClient(player, "#me_cholera_desc: " + target.GetSingleAgentCount(eAgents.CHOLERA).ToString() + " (" + stateCholera + ")");
		action.SendMessageToClient(player, "#me_salmonella_desc: " + target.GetSingleAgentCount(eAgents.SALMONELLA).ToString() + " (" + stateSalmonela + ")");
		action.SendMessageToClient(player, "#me_influenza_desc: " + target.GetSingleAgentCount(eAgents.INFLUENZA).ToString() + " (" + stateInfluenza + ")");
		action.SendMessageToClient(player, "#me_poisoning_desc: " + target.GetSingleAgentCount(eAgents.FOOD_POISON).ToString() + " (" + statePoisoning + ")");
		action.SendMessageToClient(player, "#me_woundinfection_desc: " + target.GetSingleAgentCount(eAgents.WOUND_AGENT).ToString() + " (" + stateWound + ")");
		action.SendMessageToClient(player, "#me_poisoningchemical_desc: " + target.GetSingleAgentCount(eAgents.CHEMICAL_POISON).ToString()+ " (" + stateContamination + ")");

		
		if ( target.GetRP() )
		{						
			action.SendMessageToClient(player, "#me_radiationdisease_desc: " + target.GetRP().GetRecievedRadiation() + " (" + stateRadiation + ")");
		}
	}
}