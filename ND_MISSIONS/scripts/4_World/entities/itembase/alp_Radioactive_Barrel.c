// Script File
class alp_Radioactive_Barrel : Container_Base
{
	
	//int																	alp_SmokeType		= 0;
	
	bool 																m_IsLocked 			= false;
	
	
	private ref Timer 													m_BarrelOpener;
	ref RainProcurementManager 											m_RainProcurement;

	protected ref OpenableBehaviour 									m_Openable;
	
	float																m_Strength 			= 1;
	


	

	Particle 															m_ParticleEfx;

	
	int 																alp_MissionID		= -1;
	

	void alp_Radioactive_Barrel()
	{

		m_BarrelOpener = new Timer();

		m_Openable = new OpenableBehaviour(false);

		
		RegisterNetSyncVariableBool("m_Openable.m_IsOpened");
		RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
		RegisterNetSyncVariableBool("m_IsPlaceSound");

		//RegisterNetSyncVariableInt("alp_SmokeType");

		
	}
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			if ( m_ParticleEfx ) {
				m_ParticleEfx.Stop();
				m_ParticleEfx = null;
			}
				
				
		}
	}
	
	override void EEInit()
	{
		super.EEInit();
		GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
	}

	override bool CanBeDiggedAlp()
	{
		return true;
	}		

	void alp_Lock(bool lock)
	{
		m_IsLocked = lock;
	}

	bool IsLocked()
	{
		return m_IsLocked;
	}

	override void Open()
	{
		m_Openable.Open();
		m_RainProcurement = new RainProcurementManager( this );
		m_RainProcurement.InitRainProcurement();
		GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
		SoundSynchRemote();

		//SetSynchDirty(); //! called also in SoundSynchRemote - TODO

		UpdateVisualState();
		
		//set radiation
		RestartMission();
		
	}

	override void Close()
	{
		m_Openable.Close();
		m_RainProcurement.StopRainProcurement();
		GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
		SoundSynchRemote();

		//SetSynchDirty(); //! called also in SoundSynchRemote - TODO

		UpdateVisualState();
		//destroy radiation zone
		DestroyMission();
	
	}
	
	protected void DestroyMission()	
	{
		if (alp_MissionID < 0 )
			return;
		
		alpMission mission;
		
		if ( Class.CastTo( mission, GetND().GetMS().GetMission( alp_MissionID )) )
		{
			mission.alp_Deactivated = true;
		}
	}
	protected void RestartMission()
	{
		if (alp_MissionID < 0 )
			return;

		
		alpMission mission;
		
		if ( Class.CastTo( mission, GetND().GetMS().GetMission( alp_MissionID )) )
		{
			mission.alp_Deactivated = false;
		}
		
	}	
	
	override bool IsOpen()
	{
		return m_Openable.IsOpened();
	}

	protected void UpdateVisualState()
	{
		if ( IsOpen() )
		{
			SetAnimationPhase("Lid",1);
			SetAnimationPhase("Lid2",0);
			
			if (GetGame().IsClient()){
				
				if (!m_ParticleEfx) {
					Particle.PlayOnObject(ParticleList.CONTAMINATED_AREA_GAS_SHELL, this, Vector(0, 0, 0));	
					m_ParticleEfx = Particle.PlayOnObject(ParticleList.CONTAMINATED_AREA_GAS_AROUND, this, Vector(0, 0, 0));	
				}
				
/*
				switch(alp_SmokeType){
					case 0:{
						break;
					}
					case 1:{
						if (!m_ParticleEfx) m_ParticleEfx = Particle.PlayOnObject(ParticleList.SMOKING_HELI_WRECK, this, Vector(0, 0, 0));	
						alp_SmokeType = 0;
						break;
					}
					case 2:{
						if (!m_ParticleEfx) m_ParticleEfx = Particle.PlayOnObject(ParticleList.SMOKING_CAR_ENGINE, this, Vector(0, 0.8, 0));	
						alp_SmokeType = 0;
						break;
					}										
					case 3:{
						if (!m_ParticleEfx) m_ParticleEfx = Particle.PlayOnObject(ParticleList.HATCHBACK_COOLANT_OVERHEATED, this, Vector(0, 0.8, 0));	
						alp_SmokeType = 0;
						break;
					}						
					case 4:{
						if (!m_ParticleEfx) m_ParticleEfx = Particle.PlayOnObject(ParticleList.CAMP_NORMAL_SMOKE, this, Vector(0, 0.8, 0));	
						alp_SmokeType = 0;
						break;
					}											
					case 5:{
						if (!m_ParticleEfx) m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_GREEN_LOOP, this, Vector(0, 0.8, 0));	
						alp_SmokeType = 0;
						break;
					}						
				}
*/
			}
			
		}
		else
		{
			SetAnimationPhase("Lid",0);
			SetAnimationPhase("Lid2",1);	
			
			if (GetGame().IsClient())
			{
				if ( m_ParticleEfx ) {
					m_ParticleEfx.Stop();
					m_ParticleEfx = null;
				}				
			}							
		}
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
				
		if ( IsPlaceSound() )
		{
			PlayPlaceSound();
		}
		else
		{
			if ( IsOpen() && IsSoundSynchRemote() && !IsBeingPlaced() )
			{
				SoundBarrelOpenPlay();
			}
			
			if ( !IsOpen() && IsSoundSynchRemote() && !IsBeingPlaced() )
			{
				SoundBarrelClosePlay();
			}
		}
		
		UpdateVisualState();
	}
	
	void SoundBarrelOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "barrel_open_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}

	void Lock(float actiontime)
	{
		m_IsLocked = true;
		m_BarrelOpener.Run(actiontime, this, "Unlock", NULL,false);
	}
	
	void Unlock()
	{
		m_IsLocked = false;
		Open();
	}
	
	void SoundBarrelClosePlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "barrel_close_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	override bool CanDisplayCargo()
	{
		//super
		if( !super.CanDisplayCargo() )
		{
			return false;
		}
		//
		return IsOpen();
	}
	
	override bool CanPutInCargo( EntityAI parent )
	{

		return false;
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{

		return false;

	}
	
	override bool CanReceiveItemIntoCargo(EntityAI cargo)
	{
		return IsOpen();
	}
	
	override bool CanReleaseCargo(EntityAI attachment)
	{
		return IsOpen();
	}
	
	//================================================================
	// ADVANCED PLACEMENT
	//================================================================
	
	override void OnPlacementComplete( Man player, vector position = "0 0 0", vector orientation = "0 0 0"  )
	{		
		super.OnPlacementComplete( player, position, orientation );
			
		SetIsPlaceSound( true );
	}
	
	override string GetPlaceSoundset()
	{
		return "placeBarrel_SoundSet";
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(alpActionOpenBarrel);
		AddAction(alpActionCloseBarrel);

	}	

};

class alp_Barrel_Yellow extends alp_Radioactive_Barrel
{

}
