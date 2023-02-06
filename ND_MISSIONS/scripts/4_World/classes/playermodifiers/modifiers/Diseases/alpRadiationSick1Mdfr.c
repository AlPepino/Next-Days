// Script File



class alpRadiationSick1Mdfr: ModifierBase
{


	

	
	override void Init()
	{

		m_ID 								= rModifiers.MDF_ALPRADIATIONSICK1;
		m_TickIntervalInactive 				= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 				= DEFAULT_TICK_TIME_ACTIVE;//DEFAULT_TICK_TIME_ACTIVE;

	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L1 && player.GetSingleAgentCount(alpeAgents.RADIATION) < ALP_RADPOISON.L2 );
		
	}

	override void OnActivate(PlayerBase player)
	{
		/*
		if( player.m_NotifiersManager ) 
			player.m_NotifiersManager.ActivateByType(alpeNotifiers.NTF_RADIATIONSICK);		
		*/
		
		player.IncreaseDiseaseCount();
		
		player.GetRP().SetRadiationSickStage( ALP_RADIATION_SICKSTAGE.L1 );
		
	}
	
	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);

	}

	override void OnDeactivate(PlayerBase player)
	{
		player.DecreaseDiseaseCount();
		
		player.GetRP().SetRadiationSickStage( ALP_RADIATION_SICKSTAGE.NONE );
		
		/*
		if( player.m_NotifiersManager ) 
			player.m_NotifiersManager.DeactivateByType(alpeNotifiers.NTF_RADIATIONSICK);	
		*/		
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) < ALP_RADPOISON.L0 || player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L2 );
	}

	override void OnTick(PlayerBase player, float deltaT)
	{

		

		//thirsty
		float metabolic_speed = PlayerConstants.METABOLIC_SPEED_WATER_SPRINT;
		float water = player.GetStatWater().Get();
		player.GetStatWater().Add( (-metabolic_speed * deltaT) );
					

		
	}

};