
class Land_Medical_Tent_Shower extends BuildingSuper  //Land_Medical_Tent_Shower
{
	string LOOP_SOUND = "alp_DecontaminationShower_SoundSet_On";
	
	protected EffectSound 		m_ShowerLoop;
	
	bool alp_IsShowerActive = false;
	
	
	void Land_Medical_Tent_Shower()
	{
		//GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.TestExist,1);
		RegisterNetSyncVariableBool("alp_IsShowerActive");
	}
	
	/*
	void TestExist()
	{
		Print("SPRCHA NA POZICI " + GetPosition() );
	}
	*/
	override bool IsBuilding()
	{
		return false;
	}
	

	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(alpActionDecontaminate);

	}
	
	void StartShower()
	{
		
		if (GetGame().IsServer())
		{
			alp_IsShowerActive = true;
		
			SetSynchDirty();
		}
		
		
		//PlaySoundSet(m_ShowerLoop, LOOP_SOUND, 0,0, true );
	}

	void StopShower()
	{
		
		if (GetGame().IsServer())
		{
			alp_IsShowerActive = false;
		
			SetSynchDirty();
		}
		
		
		//PlaySoundSet(m_ShowerLoop, LOOP_SOUND, 0,0, true );
	}		
	
	Particle m_ParticleEfx;
	
	Particle m_ParticleEfx_2;
	
	Particle m_ParticleEfx_3;
	
	//Particle m_ParticleEfx_4;
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if (alp_IsShowerActive)
		{
			PlaySoundSet(m_ShowerLoop, LOOP_SOUND, 0,0, true );	
			
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.HATCHBACK_COOLANT_OVERHEATED, this, Vector(0.5,-0.7,0.5),Vector(90,0,0) );//Vector(90,0,0)
			
			m_ParticleEfx_2 = Particle.PlayOnObject(ParticleList.HATCHBACK_COOLANT_OVERHEATED, this, Vector(1.5,0.2,0.5),Vector(90,0,90) );//Vector(90,0,0)
			
			m_ParticleEfx_3 = Particle.PlayOnObject(ParticleList.HATCHBACK_COOLANT_OVERHEATED, this, Vector(0.5,0.2,1.5),Vector(90,0,90) );//Vector(90,0,0)
		}
		if (!alp_IsShowerActive)
		{
			if ( m_ShowerLoop )
			{
				m_ShowerLoop.SoundStop();					
				m_ShowerLoop = NULL;
			}	
			
			if ( m_ParticleEfx )
				m_ParticleEfx.Stop();			
			
			if ( m_ParticleEfx_2 )
				m_ParticleEfx_2.Stop();	
			
			if ( m_ParticleEfx_3 )
				m_ParticleEfx_3.Stop();				
		}		
		
	}

}