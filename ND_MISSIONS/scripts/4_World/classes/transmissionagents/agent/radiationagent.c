
class alpRadiationAgent extends AgentBase
{
	override void Init()
	{
		m_Type 					= alpeAgents.RADIATION;
		m_Invasibility 			= 0;
		m_TransferabilityIn		= 0.0;
		m_TransferabilityOut	= 0.0;
		m_Digestibility	 		= 1.0;
		m_TransferabilityAirOut	= 0;
		m_AntibioticsResistance = 1;
		m_MaxCount 				= 100000;
		m_Potency 				= EStatLevels.CRITICAL;
		m_DieOffSpeed 			= 0; //
	}
	
	
	override float GetDieOffSpeedEx(PlayerBase player)
	{

		if( player.GetSingleAgentCount( alpeAgents.RADIATION ) < ALP_RADPOISON.L2 ) 
		{
			float doses = ( GetND().GetMS().GetOptionsRadiation().AutoRadiationReduce / 3600 ) * 1000;
			
			doses = doses * ( 1 + player.GetRP().GetProtection().GetNaturalResistanceAgainstRadiation() );
			
			return doses;
		}
		else
		{
			return 0;//round-about way of getting the m_DieOffSpeed
		}
	}
	
}