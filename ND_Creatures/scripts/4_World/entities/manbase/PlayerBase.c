


// Script File

modded class PlayerBase extends ManBase
{


	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		
		ZombieBase zed;
		if ( source && Class.CastTo( zed, source ) && damageResult && GetND().GetCreatures().GetOptions().EnableCretures )
		{
			float koef=0;
			
			if (ammo == "MeleeZombie_Heavy")
			{
				koef = zed.GetDamageBonusHeavyALP();
				
				float breakingChance = zed.GetChanceToBreakBone();
				if ( breakingChance )
				{
					if ( dmgZone == "LeftArm" ||  dmgZone == "RightArm" ||  dmgZone == "LeftHand" ||  dmgZone == "RightHand" )
					{			
						if ( breakingChance > Math.RandomFloat01() )
						{
							BreakArmsALP();
						}								
					}
					if ( dmgZone == "LeftLeg" ||  dmgZone == "RightLeg" ||  dmgZone == "LeftFoot" ||  dmgZone == "RightFoot" )
					{	
						if ( breakingChance > Math.RandomFloat01() )
						{
							BreakLegsALP();
						}											
					}				
				
				}
				
			}
			else
			{
				koef = zed.GetDamageBonusLightALP();
			}
			
			float shock = damageResult.GetDamage("","Shock");		
			float health = damageResult.GetDamage("","Health");	
			float blood = damageResult.GetDamage("","Blood");	
			
			float damage = shock + health + blood;
			float affect;
			shock *= koef;		
			health *= koef;	
			blood *= koef;				
			
			if ( zed.GetHealingFactor() )
			{
				affect = damage * 	zed.GetHealingFactor();
				
				zed.AddHealth("","", affect );	
			}
			float shield;		
			if ( zed.GetRadiationTouch() )
			{
				shield = GetRP().GetProtection().GetTotalRadiationShield();
				affect = damage * 	zed.GetRadiationTouch() * (1 - shield) ;
				
				InsertAgent( alpeAgents.RADIATION, affect );
				
			}	
			if ( zed.GetRadiationTouch() )
			{
				shield = GetRP().GetProtection().GetTotalChemicalShield();
				affect = damage * 	zed.GetRadiationTouch() * (1 - shield) ;
				
				InsertAgent( eAgents.CHEMICAL_POISON, affect );
				
			}					

			
			AddHealth("","Health",-health);
			AddHealth("","Shock",-shock);
			
			if( damageResult != null && GetBleedingManagerServer() )
			{			
				GetBleedingManagerServer().ProcessHit(blood, source, component, dmgZone, ammo, modelPos);
			}
		}
		
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);	
		
	
					
	}	
	


}