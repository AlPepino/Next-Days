class alpDrunkennessMdfr: ModifierBase
{
	static const int AGENT_THRESHOLD_ACTIVATE 	= 100;
	static const int AGENT_THRESHOLD_DEACTIVATE = 20;
	
	static const int WATER_DRAIN_FROM_VOMIT 	= 450;
	static const int ENERGY_DRAIN_FROM_VOMIT 	= 310;		
	
	override void Init()
	{
		m_TrackActivatedTime	= false;
		m_ID 					= rModifiers.MDF_DRUNKENNESS;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}

	override protected bool ActivateCondition(PlayerBase player)
	{
		if (player.GetSingleAgentCount(alpeAgents.DRUNKENNESS) > AGENT_THRESHOLD_ACTIVATE) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	override protected void OnActivate(PlayerBase player)
	{

		if (player.GetNotifiersManager()) player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
		// copy from PainKillersMdfr
		m_Player.m_InjuryHandler.m_ForceInjuryAnimMask = m_Player.m_InjuryHandler.m_ForceInjuryAnimMask | eInjuryOverrides.PAIN_KILLERS_LVL0;
	}

	override protected void OnDeactivate(PlayerBase player)
	{

		
		if (player.GetNotifiersManager()) player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
		
		m_Player.m_InjuryHandler.m_ForceInjuryAnimMask = m_Player.m_InjuryHandler.m_ForceInjuryAnimMask & ~eInjuryOverrides.PAIN_KILLERS_LVL0;
		m_Player.m_InjuryHandler.m_ForceInjuryAnimMask = m_Player.m_InjuryHandler.m_ForceInjuryAnimMask & ~eInjuryOverrides.PAIN_KILLERS_LVL1;
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		if(player.GetSingleAgentCount(alpeAgents.DRUNKENNESS) < AGENT_THRESHOLD_DEACTIVATE) 
		{
			return true;
		}
		else 
		{
			return false;
		}
	}

	override protected void OnTick(PlayerBase player, float deltaT)
	{
		
		//waterloss
		float water_loss = deltaT * 0.2;
		player.GetStatWater().Add(-water_loss);
		
		
		
		
		float drunkenness = player.GetSingleAgentCount(alpeAgents.DRUNKENNESS);

		if (player.IsPlayerSleeping() || player.IsUnconscious())
		{
			return;
		}
		
		
		//heat comfort
		float heatComfort =  Math.Clamp( heatComfort, player.GetStatHeatComfort().GetMin(), player.GetStatHeatComfort().GetMax() );
		

		heatComfort += 0.2;
		player.GetStatHeatComfort().Set( heatComfort );			
		
		
		
		

		if (drunkenness >= 250)
		{
			if (Math.RandomFloat01() < 1 / 15)
			{
				player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_LAUGHTER);
			}
		}

		if (drunkenness >= 600)
		{
			if (Math.RandomFloat01() < 1 / 20)
			{
				SymptomBase symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
					
				if( symptom )
				{
					symptom.SetDuration(5);
				
					if (m_Player.GetStatWater().Get() > (WATER_DRAIN_FROM_VOMIT))
						m_Player.GetStatWater().Add(-1 * WATER_DRAIN_FROM_VOMIT);
					if (m_Player.GetStatEnergy().Get() > (ENERGY_DRAIN_FROM_VOMIT))
						m_Player.GetStatEnergy().Add(-1 * ENERGY_DRAIN_FROM_VOMIT);
				}
			}
		}		
		

		if (drunkenness < 850 || player.IsInVehicle())
		{
			return;
		}

		if (Math.RandomFloat01() < 1 / 25)
		{
			player.SetHealth("", "Shock", 20);
		}
		
		
	}
}