// Script File


class alpRadiationBlockMdfr: ModifierBase
{
	
	
	float m_RegenTime;
	
	override void Init()
	{
		
		m_TrackActivatedTime			= true;
		m_ID 							= rModifiers.MDF_ALPRADIATIONBLOCK;
		m_TickIntervalInactive 			= 3;
		m_TickIntervalActive 			= 1;//DEFAULT_TICK_TIME_ACTIVE;
		m_IsPersistent=true;
		m_RegenTime 					= 180;
		

		//m_RegenTime 					= GetND().GetMS().GetOptionsRadiation().AntiRadBlockDurationEffect;
		if ( GetND() && GetND().GetMS().GetOptionsRadiation() )
		{
			
			m_RegenTime 					= GetND().GetMS().GetOptionsRadiation().AntiRadBlockDurationEffect;	
			
		}		
		

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
		float doses = player.GetRP().GetRecievedRadiation();
		if ( doses >0)
		{
			
			doses = (GetND().GetMS().GetOptionsRadiation().EffectAntiRadBlockPills/60/60) * -1000;	
					
			player.GetRP().SetRecievedRadiation(doses);
		}							
		
	}
	

};