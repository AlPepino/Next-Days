		
modded class ZombieBase extends DayZInfected
{

	float GetReputationBonusALP()
	{
		return 1;
	}


	/*
	override void RegisterTransportHit(Transport transport)
	{
		if (GetNextDays().GetOptions().GetRP().VehicleCollisionDamageRatio > 0)
		{
			m_TransportHitVelocity = GetVelocity(transport);		
			if (m_TransportHitVelocity.Length() > 0.1)
			{
				float damage = m_TransportHitVelocity.Length() * GetNextDays().GetOptions().GetRP().VehicleCollisionDamageRatio;
				transport.ProcessDirectDamage( DT_CUSTOM, this, "Front", "TransportHit", "0 0 0", damage );
			}
		}
		super.RegisterTransportHit(transport);
	}	
	*/
	
	override void EEKilled(Object killer)
	{

		if (GetGame().IsServer() && m_KillerData)
		{	
			PlayerBase player;
			
			if (Class.CastTo(player,m_KillerData.m_Killer)  )
			{
				PlayerKillZombieALP( player);
			}
		}
		
		super.EEKilled(killer);
	}
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);


		//HOTFIX for grenade killing
		Grenade_Base grenade;
		TrapBase trap;
		if ( !IsAlive() && ( Class.CastTo( grenade, source ) || Class.CastTo( trap, source )  ) )
		{
			if ( grenade )
			{
				if ( grenade.alp_LastOwner ) 
				{
					PlayerKillZombieALP( grenade.alp_LastOwner);	
				}			
			}
			if ( trap )
			{
				if (trap.alp_LastOwner ) 
				{
					PlayerKillZombieALP( trap.alp_LastOwner);	
				}			
			
			}

			
		}		
		
		
	}	
	
	void PlayerKillZombieALP(PlayerBase player)
	{
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkReputation )
		{
			float exp;
			if (player.GetRP().IsHero())
			{
				exp =  GetND().GetRP().GetReputationBonusKillZombie(ALP_RP_HERO);				
			}	
			else 
			{
				exp =  GetND().GetRP().GetReputationBonusKillZombie(ALP_RP_BANDIT);		
			}	

			player.GetRP().ChangeReputation(  ( exp * GetReputationBonusALP() ) );	
			player.GetStatCountZombies().Add(1);	
		}
	}
}
		