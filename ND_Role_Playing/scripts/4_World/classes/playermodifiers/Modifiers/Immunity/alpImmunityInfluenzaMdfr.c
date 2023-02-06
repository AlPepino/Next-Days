// Script File


class alpImmunityInfluenzaMdfr: ModifierBase
{
	

	float m_RegenTime;
	
	override void Init()
	{
		
		m_TrackActivatedTime			= true;
		m_ID 							= rModifiers.MDF_IMMUNITY_INFLUENZA;
		m_TickIntervalInactive 			= DEFAULT_TICK_TIME_INACTIVE_LONG;
		m_TickIntervalActive 			= DEFAULT_TICK_TIME_ACTIVE;
		m_IsPersistent=true;
		m_RegenTime 					= GetND().GetRP().GetDiseases().ImmunityInfluenza;

	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		return false;
	}

	override void OnActivate(PlayerBase player)
	{
		if( player.GetNotifiersManager() ) player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
	}
	
	override void OnReconnect(PlayerBase player)
	{				
		OnActivate(player);
	}

	override void OnDeactivate(PlayerBase player)
	{
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

	}
	

};