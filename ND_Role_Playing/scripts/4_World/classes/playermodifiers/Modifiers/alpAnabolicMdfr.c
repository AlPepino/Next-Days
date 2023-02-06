// Script File


class alpAnabolicMdfr: ModifierBase
{
	
	const int 						ANABOLIC_LIFETIME	= 300;		

	
	

	float m_RegenTime;
	
	override void Init()
	{
		
		m_TrackActivatedTime			= true;
		m_ID 							= rModifiers.MDF_ANABOLIC;
		m_TickIntervalInactive 			= 3;
		m_TickIntervalActive 			= 1;//DEFAULT_TICK_TIME_ACTIVE;
		m_IsPersistent=true;
		m_RegenTime 					= ANABOLIC_LIFETIME;

	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		return false;
	}

	override void OnActivate(PlayerBase player)
	{
		//player.GetRPG().alp_AnabolicApplicated = true;
		if( player.GetNotifiersManager() ) player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
		
		
	}
	
	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}

	override void OnDeactivate(PlayerBase player)
	{
		//player.GetRPG().alp_AnabolicApplicated = false;
		if( player.GetNotifiersManager() ) player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
		

	}

	override bool DeactivateCondition(PlayerBase player)
	{
		float attached_time = GetAttachedTime();
		
		if( attached_time >= m_RegenTime )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	override void OnTick(PlayerBase player, float deltaT)
	{	
		player.GetStaminaHandler().SetStamina(100);
	}
	

};