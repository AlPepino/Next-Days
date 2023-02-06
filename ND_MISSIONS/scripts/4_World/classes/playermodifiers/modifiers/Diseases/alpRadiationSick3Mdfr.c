// Script File



class alpRadiationSick3Mdfr: ModifierBase
{
		
	
	static const int 						WATER_DRAIN_FROM_VOMIT = 450;
	static const int 						ENERGY_DRAIN_FROM_VOMIT = 310;	
	
	const ref array<string>					BLEEDINGZONES = {"Head","Neck","Pelvis","Spine","LeftShoulder","LeftArm","LeftArmRoll","LeftForeArm","RightShoulder","RightArm","RightArmRoll","RightForeArm","LeftForeArmRoll","RightForeArmRoll","LeftLeg","LeftLegRoll","LeftUpLeg","LeftUpLegRoll","RightLeg","RightLegRoll","RightUpLeg","RightUpLegRoll","LeftFoot","LeftToeBase","RightFoot","RightToeBase"};



	

	
	override void Init()
	{

		m_ID 								= rModifiers.MDF_ALPRADIATIONSICK3;
		m_TickIntervalInactive 				= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 				= DEFAULT_TICK_TIME_ACTIVE;//DEFAULT_TICK_TIME_ACTIVE;


	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L3 && player.GetSingleAgentCount(alpeAgents.RADIATION) < ALP_RADPOISON.L4 );
		
	}

	override void OnActivate(PlayerBase player)
	{
		/*
		if( player.m_NotifiersManager ) 
			player.m_NotifiersManager.ActivateByType(alpeNotifiers.NTF_RADIATIONSICK);		
		*/
		
		player.IncreaseDiseaseCount();
		player.GetRP().SetRadiationSickStage( ALP_RADIATION_SICKSTAGE.L3 );
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
		
		return ( player.GetSingleAgentCount(alpeAgents.RADIATION) >= ALP_RADPOISON.L4 );
	}

	override void OnTick(PlayerBase player, float deltaT)
	{

		
		//setting illness
		//SetSickness(player);

		//thirsty
		float metabolic_speed = PlayerConstants.METABOLIC_SPEED_WATER_SPRINT;
		float water = player.GetStatWater().Get();
		player.GetStatWater().Add( (-metabolic_speed * deltaT) );
					
		//sickness

		float 		vomit 	= 0.990;
		float 		bleed 	= 0.998;
		float 		infection = 0.850;		
		
		
		//infection
		if (Math.RandomFloat01()  >= infection  ) 
		{
			player.m_AgentPool.AddAgent( eAgents.WOUND_AGENT, m_TickIntervalActive);
		}	
		
		//vomiting
		if (Math.RandomFloat01()  >= vomit) 
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
		//bleeding	
		if (Math.RandomFloat01()  >= bleed) 
		{
			player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection(BLEEDINGZONES.GetRandomElement());	
		}					
	}
	

};