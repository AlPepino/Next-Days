class alpTirednessMdfr: ModifierBase
{
	ref HumanMovementState		m_MovementState	= new HumanMovementState();
	
	
	override void Init()
	{
		m_TrackActivatedTime	= false;
		m_ID 					= rModifiers.MDF_TIREDNESS;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;//DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}

	override protected bool ActivateCondition(PlayerBase player)
	{
		return 	GetND().GetRP().GetPerksOptions().EnableFatigue;
	}

	override protected void OnActivate(PlayerBase player)
	{
		//player.IncreaseDiseaseCount();
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		//player.DecreaseDiseaseCount();
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		return false;
	}

	
	protected float GetFatigueMdfALP(PlayerBase player,  float fatigue )
	{
		if ( player.HasDisease() ) 
		{
			fatigue *= GetND().GetRP().GetFatigue().FatigueSickMultiplier;
		}
		/*
		if ( player.GetRPG().GetRadiationSickStage() > 0 )
		{
			fatigue *= GetND().GetRP().GetFatigue().FatigueRadiationSickMultiplier;
		}
		
		if ( player.GetRPG().GetRadiation() > 0 && player.GetRPG().GetShield() < 100 )
		{
			fatigue *= GetND().GetRP().GetFatigue().FatigueRadiationMultiplier;
		}		
		*/
		
		float heat_comfort = player.GetStatHeatComfort().Get();
							
		if ( heat_comfort <= PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING )		
		{
			fatigue *= GetND().GetRP().GetFatigue().FatigueHeatMultiplier;
		}					
			

		return fatigue;
	}
	
	
	override protected void OnTick(PlayerBase player, float deltaT)
	{
		player.GetMovementState(m_MovementState);
			
		float fatigue = alpUF.GetTirednessMetabolicSpeed( m_MovementState.m_iMovement );
		
		fatigue = GetFatigueMdfALP(player, fatigue) ;
		
		
		player.GetStatTiredness().Add( -fatigue * deltaT );
		
		float energy = player.GetStatTiredness().Get();	
		
		//PENALTY
		
		if ( energy < 10 )
		{	
			player.AddHealth("GlobalHealth", "Health", -PlayerConstants.LOW_ENERGY_DAMAGE_PER_SEC * deltaT );
		}
		
		if (energy == 0)
		{
			if (Math.RandomFloat01() > 0.95)
			{
				player.SetHealth("", "Shock", 0);
			}		
		
		}
		

	}
}