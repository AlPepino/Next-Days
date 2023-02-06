modded class AnimalBase extends DayZAnimal
{
	/*
	override void RegisterTransportHit(Transport transport)
	{
		if ( GetNextDays().GetOptions().GetRP().VehicleCollisionDamageRatio > 0)
		{
			m_TransportHitVelocity = GetVelocity(transport);		
			if (m_TransportHitVelocity.Length() > 0.1)
			{
				float damage = m_TransportHitVelocity.Length() *  GetNextDays().GetOptions().GetRP().VehicleCollisionDamageRatio;
				transport.ProcessDirectDamage( DT_CUSTOM, this, "Front", "TransportHit", "0 0 0", damage );
			}
		}
		super.RegisterTransportHit(transport);
	}	
	*/
	
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);

		if (GetGame().IsServer() && killer)
		{
			PlayerBase player;
			if (Class.CastTo(player, EntityAI.Cast(killer).GetHierarchyRootPlayer()))
			{
				PlayerKillAnimalALP( player );	
			}
		}
		
	}	
	
	void PlayerKillAnimalALP( PlayerBase player )
	{

		if ( GetND().GetRP().GetPerksOptions().EnablePerkReputation )
		{		
			if (player.GetRP().IsHero())
			{
				IncreaseReputationALP( player,	ALP_RP_HERO);
			}	
			else 
			{
				IncreaseReputationALP( player,	ALP_RP_BANDIT);
			}
			player.GetStatCountAnimals().Add(1);
		}		
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkHunting )
		{			
			player.GetRP().ChangeHunting( GetEXPtoHunting() );		
		}		
	}
	
	float GetEXPtoHunting()
	{
		
		
		return GetND().GetRP().GetPerkHunting().KillAnimal;
	}	
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{

		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		
		
		//hunting skill
		if ( GetND().GetRP().GetPerksOptions().EnablePerkHunting )
		{			
			PlayerBase player;
			
			if ( source && ( Class.CastTo(player, source.GetHierarchyRootPlayer()) || Class.CastTo(player, source) ) )
			{
				float damage = -BonusDamageALP(damageResult.GetDamage(dmgZone,"Health"), player );			
				AddHealth("","Health", damage);
			}	
		}			
		
		//HOTFIX for grenade killing
		Grenade_Base grenade;
		TrapBase trap;
		if ( !IsAlive() && ( Class.CastTo( grenade, source ) || Class.CastTo( trap, source )  ) )
		{
			if ( grenade )
			{
				if ( grenade.alp_LastOwner ) 
				{
					PlayerKillAnimalALP( grenade.alp_LastOwner);	
				}			
			}
			if ( trap )
			{
				if (trap.alp_LastOwner ) 
				{
					PlayerKillAnimalALP( trap.alp_LastOwner);	
				}			
			
			}

			
		}			
	}	
	
	float BonusDamageALP(float damage, PlayerBase player)
	{
		
		float bonus  = GetND().GetRP().GetPerkHuntingDamageMdf(  player.GetStatPerkHunting().Get() );	
	
		damage *= bonus;
		
		return damage;	
	}
		
	void IncreaseReputationALP( PlayerBase player, int role)
	{				
		player.GetRP().ChangeReputation(   GetND().GetRP().GetReputationBonusKillAnimal(role) );			
	}	
}

//wolf
modded class Animal_CanisLupus extends AnimalBase
{
	override void IncreaseReputationALP( PlayerBase player, int role)
	{
		player.GetRP().ChangeReputation(   GetND().GetRP().GetReputationBonusKillWolf(role) );			
	}
	
	
	override float GetEXPtoHunting()
	{
		
		return GetND().GetRP().GetPerkHunting().KillWolf;
	}	

}

//bear
modded class Animal_UrsusArctos extends AnimalBase
{
	override void IncreaseReputationALP( PlayerBase player, int role)
	{	
		player.GetRP().ChangeReputation(   GetND().GetRP().GetReputationBonusKillBear(role) );			
	}
	
	override float GetEXPtoHunting()
	{
		
		return GetND().GetRP().GetPerkHunting().KillBear;
	}	

}

//deer
modded class Animal_CervusElaphus extends AnimalBase
{
	override float GetEXPtoHunting()
	{
		
		return GetND().GetRP().GetPerkHunting().KillDeer;
	}	
}


//boar
modded class Animal_SusScrofa extends AnimalBase
{
	override float GetEXPtoHunting()
	{
		
		return GetND().GetRP().GetPerkHunting().KillBoar;
	}	
}