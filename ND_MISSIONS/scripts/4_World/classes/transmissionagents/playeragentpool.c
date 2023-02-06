
modded class PlayerAgentPool
{

	override void AddAgent(int agent_id, float count)
	{
		int max_count = m_PluginTransmissionAgents.GetAgentMaxCount(agent_id);
		
		if ( count > 0 )
		{			
			
			float resistance;
			switch (agent_id)
			{
				case alpeAgents.RADIATION:
				{
					
					resistance =  m_Player.GetRP().GetProtection().GetNaturalResistanceAgainstRadiation();
					//Print("COUNT " + count);
					count = count - count * resistance;
					if ( count > 0 )
					{
						//Print("COUNT " + count);
						
						m_Player.GetRP().ImproveRadiationNaturalResistance( count );
					}
					break;
				}
				case eAgents.CHEMICAL_POISON:
				{
					resistance =  m_Player.GetRP().GetProtection().GetNaturalResistanceAgainstChemical();
					count = count - count * resistance;
					if ( count > 0 )
					{
						m_Player.GetRP().ImproveToxicNaturalResistance( count );
					}					
					break;
				}		
			}
		}
				
		
		if(	!m_VirusPool.Contains(agent_id) && count > 0 )//if it contains, maybe add count only ?
		{
			//m_VirusPool.Insert( agent_id, Math.Clamp(count,0,max_count) );
			SetAgentCount(agent_id,count);
		}
		else
		{
			float new_value = m_VirusPool.Get(agent_id) + count;
			//Print(new_value);
			SetAgentCount(agent_id,new_value);
		}
	}

}