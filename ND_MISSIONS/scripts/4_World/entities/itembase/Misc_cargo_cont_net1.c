// Script File
#ifdef NAMALSK_TERRAIN
class alp_Misc_cargo_cont_net1 extends Container_Base
{

	int																	alp_SmokeType		= 0;

	Particle 															m_ParticleEfx;

	void alp_Misc_cargo_cont_net1()
	{
	

		RegisterNetSyncVariableInt("alp_SmokeType");
		
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			 UpdateVisualState();
		}
	}
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			if ( m_ParticleEfx )
				m_ParticleEfx.Stop();
				
		}
	}	
	
	override bool CanPutInCargo( EntityAI parent )
	{
		return false;
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;

	}
	
	protected void UpdateVisualState()
	{
		
		if (GetGame().IsClient())
		{
			switch(alp_SmokeType)
			{
				case 0:{
					break;
				}
				case 1:{
					if (!m_ParticleEfx) m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_RED_LOOP, this, Vector(0, 1, 0));	
					alp_SmokeType = 0;
					break;
				}
				case 2:{
					if (!m_ParticleEfx) m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_PURPLE_LOOP, this, Vector(0, 1, 0));	
					alp_SmokeType = 0;
					break;
				}										
				case 3:{
					if (!m_ParticleEfx) m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_WHITE_LOOP, this, Vector(0, 1, 0));	
					alp_SmokeType = 0;
					break;
				}						
				case 4:{
					if (!m_ParticleEfx) m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_YELLOW_LOOP, this, Vector(0, 1, 0));	
					alp_SmokeType = 0;
					break;
				}											
				case 5:{
					if (!m_ParticleEfx) m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_GREEN_LOOP, this, Vector(0, 1, 0));	
					alp_SmokeType = 0;
					break;
				}						
			}
		}
	
	}


	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
				
		
		UpdateVisualState();
	}		
	
}

#endif


