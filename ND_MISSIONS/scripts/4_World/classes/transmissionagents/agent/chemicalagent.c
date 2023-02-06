modded class ChemicalAgent extends AgentBase
{

	
	override float GetDieOffSpeedEx(PlayerBase player)
	{
		if( player.GetModifiersManager().IsModifierActive(eModifiers.MDF_CONTAMINATION2) || player.GetModifiersManager().IsModifierActive(eModifiers.MDF_CONTAMINATION3))
		{
			return 0;
		}
		else
		{
			float doses =  super.GetDieOffSpeedEx(player);
			
			doses = doses * ( 1 + player.GetRP().GetProtection().GetNaturalResistanceAgainstChemical() );
			
			return doses;//round-about way of getting the m_DieOffSpeed
		}
	}
}