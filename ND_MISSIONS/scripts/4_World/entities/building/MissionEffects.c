class alp_MissionEffects_Base : House {}

class alp_MissionEffects_Alarm : alp_MissionEffects_Base
{
	EffectSound m_SoundEff;
	

 	override void EEInit(){	

		super.EEInit();
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){
			m_SoundEff = SEffectManager.PlaySoundOnObject( "alp_WarningAlarmEffect_SoundSet",this,0,0,true);	
		}		
		
	}
	override void EEDelete(EntityAI parent){				
		if ( m_SoundEff ){		
			m_SoundEff.SoundStop();					
			m_SoundEff = null;
		}	

	}
}
class alp_MissionEffects_HeliSmoke : alp_MissionEffects_Base
{
	Particle m_ParticleEfx;
 	override void EEInit(){	
		super.EEInit();
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.SMOKING_HELI_WRECK, this , Vector(0, 0, 0));
		}			
	}
	override void EEDelete(EntityAI parent){				
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){		
			if ( m_ParticleEfx ) 
				m_ParticleEfx.Stop();			
		}		
	}
}
class alp_MissionEffects_GasGround : alp_MissionEffects_Base
{
	Particle m_ParticleEfx;
 	override void EEInit(){	
		super.EEInit();
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.CONTAMINATED_AREA_GAS_GROUND, this , Vector(-0.5, 0, -1.0));
		}			
	}
	override void EEDelete(EntityAI parent){				
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){		
			if ( m_ParticleEfx ) 
				m_ParticleEfx.Stop();			
		}		
	}
}
class alp_MissionEffects_GasAround : alp_MissionEffects_Base
{
	Particle m_ParticleEfx;
 	override void EEInit(){	
		super.EEInit();
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.CONTAMINATED_AREA_GAS_AROUND, this , Vector(-0.5, 0, -1.0));
		}			
	}
	override void EEDelete(EntityAI parent){				
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){		
			if ( m_ParticleEfx ) 
				m_ParticleEfx.Stop();			
		}		
	}
}

class alp_MissionEffects_Explosion : alp_MissionEffects_Base
{		
	bool m_WasExploded;
	void alp_MissionEffects_Explosion(){
		RegisterNetSyncVariableBool("m_WasExploded");
	}
 	override void EEInit(){	
		super.EEInit();
		
		if ( !m_WasExploded ){
			Explode(DT_EXPLOSION, "LandFuelFeed_Ammo");	
			m_WasExploded = true;
		}
			
	}
	override void OnExplosionEffects(Object source, Object directHit, int componentIndex, string surface, vector pos, vector surfNormal, float energyFactor, float explosionFactor, bool isWater, string ammoType)
	{
		if ( GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() )
		{	
			vector n = surfNormal.VectorToAngles() + "0 90 0";
			Particle p1 = ParticleManager.GetInstance().PlayInWorld(ParticleList.SMOKE_GENERIC_WRECK, pos);
			p1.SetOrientation(n);
		
			Particle p2 = ParticleManager.GetInstance().PlayInWorld(ParticleList.EXPLOSION_LANDMINE, pos);
			p2.SetOrientation(n);

			Particle p3 = ParticleManager.GetInstance().PlayInWorld(ParticleList.IMPACT_METAL_RICOCHET, pos);
			p3.SetOrientation(n);
		
			Particle p4 = ParticleManager.GetInstance().PlayInWorld(ParticleList.IMPACT_GRAVEL_RICOCHET, pos);
			p4.SetOrientation(n);
		}
	}
}

class alp_MissionEffects_FalloutAround : alp_MissionEffects_Base
{
	Particle m_ParticleEfx;
	Particle m_ParticleEfx_big;
	Particle m_ParticleEfx_fast;
 	override void EEInit(){	
		super.EEInit();
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.ALP_SPAD, this , Vector(0, 0, 0));
			m_ParticleEfx_big = ParticleManager.GetInstance().PlayOnObject(ParticleList.ALP_SPAD_BIG, this , Vector(0, 0, 0));
			m_ParticleEfx_fast = ParticleManager.GetInstance().PlayOnObject(ParticleList.ALP_SPAD_FAST, this , Vector(0, 0, 0));
		}	
		
		if ( GetGame() && GetGame().IsServer() && GetGame().IsMultiplayer() ) {					
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetWeatherALP,30000);
		}
		
		//GetWorld		
	}
	
	void SetWeatherALP(){
		Weather pocasi = GetGame().GetWeather();
		Overcast o = pocasi.GetOvercast();
		//Fog mlha = pocasi.GetFog();
		//Rain dest = pocasi.GetRain();
		//mlha.Set(0.2,0,900);
		//dest.Set(0.4,0,900);	
		float actual = o.GetActual();
		actual += 0.05;
		
		actual = Math.Clamp(actual,0,1);
		o.Set(actual,0,600);		
		if ( actual < 1) {			
			int random = Math.RandomInt(2,5);
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetWeatherALP,random*1000);
		}
		
			
	}
	
	override void EEDelete(EntityAI parent){				
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){		
			if ( m_ParticleEfx ) 
				m_ParticleEfx.Stop();			
			if ( m_ParticleEfx_big ) 
				m_ParticleEfx_big.Stop();	
			if ( m_ParticleEfx_fast ) 
				m_ParticleEfx_fast.Stop();				
		}		
		
		if ( GetGame() && GetGame().IsServer() && GetGame().IsMultiplayer() ) {		
			Weather pocasi = GetGame().GetWeather();
			Overcast predpoved = pocasi.GetOvercast();
			//Fog mlha = pocasi.GetFog();
			//Rain dest = pocasi.GetRain();
			//mlha.Set(0.2,0,900);
			//dest.Set(0.4,0,900);						
			predpoved.Set(0,0,0);	
		}		
	}
}

class alp_MissionEffects_Boiling : alp_MissionEffects_Base
{
	Particle m_ParticleEfx;
 	override void EEInit(){	
		super.EEInit();
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.COOKING_BOILING_EMPTY, this , Vector(0, 0, 0));
		}			
	}
	override void EEDelete(EntityAI parent){				
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){		
			if ( m_ParticleEfx ) 
				m_ParticleEfx.Stop();			
		}		
	}
}


class alp_MissionEffects_Smoke : alp_MissionEffects_Base
{
	Particle m_ParticleEfx;
 	override void EEInit(){	
		super.EEInit();
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.BONFIRE_SMOKE, this , Vector(0, 0, 0));
		}			
	}
	override void EEDelete(EntityAI parent){				
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){		
			if ( m_ParticleEfx ) 
				m_ParticleEfx.Stop();			
		}		
	}
}


class alp_MissionEffects_EngineFire : alp_MissionEffects_Base
{
	Particle m_ParticleEfx;
 	override void EEInit(){	
		super.EEInit();
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.SMOKING_CAR_ENGINE, this , Vector(0, 0, 0));
		}			
	}
	override void EEDelete(EntityAI parent){				
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){		
			if ( m_ParticleEfx ) 
				m_ParticleEfx.Stop();			
		}		
	}
}

class alp_MissionEffects_Flare : alp_MissionEffects_Base
{
	Particle m_ParticleEfx;
 	override void EEInit(){	
		super.EEInit();
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){
			m_ParticleEfx = ParticleManager.GetInstance().PlayOnObject(ParticleList.ROADFLARE_BURNING_MAIN, this , Vector(0, 0, 0));
		}			
	}
	override void EEDelete(EntityAI parent){				
		if (GetGame() && GetGame().IsClient() && GetGame().IsMultiplayer() ){		
			if ( m_ParticleEfx ) 
				m_ParticleEfx.Stop();			
		}		
	}
}

