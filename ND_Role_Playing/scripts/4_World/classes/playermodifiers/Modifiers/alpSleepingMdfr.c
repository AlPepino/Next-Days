class alpSleepingMdfr: ModifierBase
{

	
	
	override void Init()
	{
		m_TrackActivatedTime	= false;
		m_ID 					= rModifiers.MDF_SLEEPING;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;//DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;//DEFAULT_TICK_TIME_ACTIVE;
	}

	override protected bool ActivateCondition(PlayerBase player)
	{
		if ( player.IsPlayerSleeping() )
			return true;
		else 
			return false;
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
		if ( !player.IsPlayerSleeping() )
			return true;
		else 
			return false;
	}

	override protected void OnTick(PlayerBase player, float deltaT)
	{
		float rest = GetND().GetRP().GetFatigue().Resting;
		
		bool regeneration = true;
		
		
		if ( !player.IsPlayerInShelter() )
		{
			rest *= GetND().GetRP().GetFatigue().RestingPenaltyShelter;
			regeneration = false;
		}
		
		float heat_comfort = player.GetStatHeatComfort().Get();
		
		
		
		
		if( heat_comfort <= PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING && !player.GetModifiersManager().IsModifierActive( rModifiers.MDF_IMMUNITY_INFLUENZA ) )
		{
			rest *= GetND().GetRP().GetFatigue().RestingPenaltyHeat;
			
			player.InsertAgent(eAgents.INFLUENZA, 1 * deltaT );
			
			regeneration = false;
		}		
		
	
		
		
		player.GetStatTiredness().Add( rest * deltaT );
	
		if (regeneration)
		{
			player.AddHealth("", "Blood", PlayerConstants.SALINE_BLOOD_REGEN_PER_SEC * deltaT * 2);
			player.AddHealth("", "Health", PlayerConstants.HEALTH_REGEN_MAX * deltaT * 4);
		}
		
		
	}
}