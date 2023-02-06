modded class BoneRegenMdfr: ModifierBase
{
	const int LIFETIME = 600;	
	
	private const 	float	MINIMAL_WATER_TO_REGENRATE = 2500;
	private const 	float	MINIMAL_ENERGY_TO_REGENRATE = 4000;
	private const 	float	MINIMAL_BLOOD_TO_REGENRATE = 5000;
	private const 	float	MINIMAL_BLOOD_REQUIRED_TO_REGENERATE_HEALTH = 5000;
	private const	float 	BONE_HEALTH_INCREMENT_PER_SEC = 0.1;
	
	override void Init()
	{
		m_TrackActivatedTime = true;
		m_IsPersistent = true;
		m_ID 					= eModifiers.MDF_BONE_REGEN;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= DEFAULT_TICK_TIME_ACTIVE;
	}

	override bool ActivateCondition(PlayerBase player)
	{
		return false;
	}

	override void OnReconnect(PlayerBase player)
	{
		OnActivate(player);
	}

	override protected void OnActivate(PlayerBase player)
	{
		if (player.GetNotifiersManager()) player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
	}

	override protected void OnDeactivate(PlayerBase player)
	{
		if (player.GetNotifiersManager()) player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
	}

	override protected bool DeactivateCondition(PlayerBase player)
	{
		float attached_time = GetAttachedTime();
		
		if( attached_time >= LIFETIME )
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
		
		player.AddHealth("RightArm","Health",BONE_HEALTH_INCREMENT_PER_SEC * deltaT);		
		player.AddHealth("RightHand","Health",BONE_HEALTH_INCREMENT_PER_SEC * deltaT);
		player.AddHealth("LeftArm","Health",BONE_HEALTH_INCREMENT_PER_SEC * deltaT);
		player.AddHealth("LeftHand","Health",BONE_HEALTH_INCREMENT_PER_SEC * deltaT);		
		player.AddHealth("RightLeg","Health",BONE_HEALTH_INCREMENT_PER_SEC * deltaT);
		player.AddHealth("RightFoot","Health",BONE_HEALTH_INCREMENT_PER_SEC * deltaT);
		player.AddHealth("LeftLeg","Health",BONE_HEALTH_INCREMENT_PER_SEC * deltaT);
		player.AddHealth("LeftFoot","Health",BONE_HEALTH_INCREMENT_PER_SEC * deltaT);		
		player.AddHealth("Torso","Health",BONE_HEALTH_INCREMENT_PER_SEC * deltaT);
		
	}
};