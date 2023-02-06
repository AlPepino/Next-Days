
class alpZombieBehavior
{
	
	
	int Speed;
	
	float Armor;
	
	float HeavyDamageBonus;
	float DamageBonus;
	
	float ChanceToBreakBone;
	
	float RadiationTouch;
	float ChemicalTouch;
	
	float HealingFactor;
	float ReputationBonus;
	
	void alpZombieBehavior( int speed, float armor,  float heavy, float light, float bone,float exp = 0, float chemicals = 0 , float radiation = 0 , float healing = 0 )
	{
		Speed = Math.Clamp(speed, 0 , 3 );
		Armor = armor;
		HeavyDamageBonus = heavy;
		DamageBonus = light;
		ChanceToBreakBone = bone;
		
		RadiationTouch = radiation;
		
		ChemicalTouch = chemicals;
		
		HealingFactor = healing;
		
		ReputationBonus = exp;
	}
	float GetToxic()
	{
		return ChemicalTouch;		
	}		
	float GetRadiation()
	{
		return RadiationTouch;		
	}	
	float GetHealing()
	{
		return HealingFactor;		
	}
	
	float GetArmor()
	{
		return Armor;
	}
	
	
	float GetSpeed()
	{
		autoptr array<float> speedLimits = {1.7,2.2,2.7,3};	
	
		
		return speedLimits.Get(Speed);
	}
	
	float GetHeavyDamage()
	{
		return HeavyDamageBonus;
	}	
	float GetLightDamage()
	{
		return DamageBonus;
	}	
	float GetBreakChance()
	{
		return ChanceToBreakBone;
	}		
	float GetReputationBonus()
	{
		return ReputationBonus;
	}
	
}




class alpZombieBehaviors
{
	//ref array<string> alp_MonsterTypes;
	
	ref array<ref alpZombieBehavior> alp_Civil;
	ref array<ref alpZombieBehavior> alp_Military;
	
	ref array<ref alpZombieBehavior> alp_CivilNBC;
	ref array<ref alpZombieBehavior> alp_MilitaryNBC;	
	
	ref array<ref alpZombieBehavior> alp_Monster;
	

	
	void alpZombieBehaviors()
	{
		//read setting from configs
		
		alp_Civil = GetND().GetCreatures().GetZombieCivil();
		alp_Military = GetND().GetCreatures().GetZombieMilitary();
		
		alp_CivilNBC = GetND().GetCreatures().GetZombieCivilNBC();
		alp_MilitaryNBC = GetND().GetCreatures().GetZombieMilitaryNBC();
		alp_Monster = GetND().GetCreatures().GetZombieMonster();
		
	}

	
	alpZombieBehavior GetCivilBehavior()
	{
		return alp_Civil.GetRandomElement();
	}
	
	alpZombieBehavior GetMilitaryBehavior()
	{
		return alp_Military.GetRandomElement();
	}
	alpZombieBehavior GetCivilBehaviorNBC()
	{
		return alp_CivilNBC.GetRandomElement();
	}
	
	alpZombieBehavior GetMilitaryBehaviorNBC()
	{
		return alp_MilitaryNBC.GetRandomElement();
	}	
	
	alpZombieBehavior GetZombieMonster()
	{
		return alp_Monster.GetRandomElement();
	}				
	static alpZombieBehaviors GetInstance()
	{
		alpZombieBehaviors zb = new alpZombieBehaviors();	
		
		return zb;
	}
}



modded class ZombieBase
{
	static ref alpZombieBehaviors alp_ZombieBehavior;
	
	float alp_ReputationBonus;
	
	float alp_SpeedMax;
	float alp_LastSpeedMax;
	
	float alp_TimeStempSpeed;
	
	bool alp_OverridenSpeed;
	bool alp_LastOverridenSpeed;
	//damage bonus
	float alp_HeavyAttackMultiply;
	float alp_HeavyAttackMultiplyDay;
	float alp_HeavyAttackMultiplyNight;
	
	float alp_DamageBonus;
	float alp_DamageBonusDay;
	float alp_DamageBonusNight;			
	
	//hit chance to brake bone
	float alp_ChanceToBreakBone;
	
	float alp_Armor;
	
	float alp_RadiationTouch;
	float alp_ChemicalTouch;
	float alp_HealingFactor;
	
	Building alp_Building;	
	
	override void Init()
	{
		super.Init();

		if ( GetGame().IsServer() && IsZombieCustomed() )
		{
			m_AreaTimeCheck = Math.RandomInt(-30,2);
			//Print("START TIME " + m_AreaTimeCheck);
			
			if (!alp_ZombieBehavior)
			{
				alp_ZombieBehavior = alpZombieBehaviors.GetInstance();			
			}
			
			autoptr alpZombieBehavior behavior;
			
			if ( IsMonsterZombie() )
			{
				behavior = alp_ZombieBehavior.GetZombieMonster();
			}
			else
			{
				if ( IsZombieMilitary() )
				{
					if ( IsContaminedZombie() )
					{
						behavior = alp_ZombieBehavior.GetMilitaryBehaviorNBC();
					}
					else
					{
						behavior = alp_ZombieBehavior.GetMilitaryBehavior();
					}
					
				}
				else
				{
					if ( IsContaminedZombie() )
					{
						behavior = alp_ZombieBehavior.GetCivilBehaviorNBC();
					}
					else
					{
						behavior = alp_ZombieBehavior.GetCivilBehavior();	
					}				
							
				}			
			}
			


			alp_SpeedMax = behavior.GetSpeed();
			alp_LastSpeedMax = alp_SpeedMax;
			
			if ( alp_SpeedMax < 3 )
			{
				alp_OverridenSpeed = true;
				alp_LastOverridenSpeed = true;
			}			
		
			alp_HeavyAttackMultiply = behavior.GetHeavyDamage();
			alp_DamageBonus = behavior.GetLightDamage();
			alp_ChanceToBreakBone = behavior.GetBreakChance();
			alp_Armor = behavior.GetArmor();
								
			alp_RadiationTouch = behavior.GetRadiation();
			alp_ChemicalTouch = behavior.GetToxic();
			alp_HealingFactor = behavior.GetHealing();		
			
			
			alp_ReputationBonus = behavior.GetReputationBonus();	

			
			
			//Print("MAXIMALNI RYCHLOST " + alp_SpeedMax );
		}

		
		
	}
	

	
	float GetRadiationTouch()
	{
		return alp_RadiationTouch;
	}	
	float GetChemicalTouch()
	{
		return alp_ChemicalTouch;
	}	
	float GetHealingFactor()
	{
		return alp_HealingFactor;
	}	
	
	float GetChanceToBreakBone()
	{
		return alp_ChanceToBreakBone;
	}
	
	float GetDamageBonusHeavyALP()
	{
		return alp_HeavyAttackMultiply  + alp_DamageBonus;
	}

	float GetDamageBonusLightALP()
	{
		return alp_DamageBonus;	
	}
	
	
		
	
	override void HandleMove(int pCurrentCommandID)
	{
		if ( !IsZombieCustomed())
		{
			super.HandleMove( pCurrentCommandID );
			return;
		}
		
		DayZInfectedInputController ic = GetInputController();
		m_MovementSpeed = ic.GetMovementSpeed();
		
		if ( alp_OverridenSpeed && m_MovementSpeed > alp_SpeedMax )
		{		
			m_MovementSpeed	= alp_SpeedMax;
			ic.OverrideMovementSpeed(true,m_MovementSpeed);
			
			alp_TimeStempSpeed = 0;
		}
		
		if (Math.AbsFloat(m_LastMovementSpeed - m_MovementSpeed) >= 0.9 && m_LastMovementSpeed != m_MovementSpeed)
		{
			SetSynchDirty();
		}
		m_LastMovementSpeed = m_MovementSpeed;
	}	


	//int alp_IsTransport;
	
	float m_AreaTimeCheck;
	
	override bool	ModCommandHandlerBefore(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		bool ret = super.ModCommandHandlerBefore( pDt,  pCurrentCommandID,  pCurrentCommandFinished);	

		if (!ret && IsZombieCustomed() )
		{
			//check if the zombie can exists
			m_AreaTimeCheck += pDt;
			if ( m_AreaTimeCheck > 2 ) {						
				m_AreaTimeCheck = 0;
				
				if ( !alpPluginNDmissionsSystem.CansSpawnAI(this ) ) {
					SetHealth("","",0);
					return true;
				}
			}
			

			DayZInfectedInputController ic = GetInputController();		
			int mindStage = ic.GetMindState();		

			float actualSpeed = ic.GetMovementSpeed();	
			
			alp_TimeStempSpeed += pDt;
			
		

			
			if ( ic.GetMindState() != DayZInfectedConstants.MINDSTATE_CALM && CanOpenUnlockedDoor() )
			{//eliminate loop check
				alp_TimeStempDoors  += pDt;
				//handle doors
				if ( alp_TimeStempDoors > 1.0  && actualSpeed <= 1 ) //&&  pCurrentCommandID == DayZInfectedConstants.COMMANDID_MOVE ) 
				{
					alp_TimeStempDoors = 0;
					int index
					if ( HandleDoors(index) && alp_Building && index >= 0 )
					{	

						if ( !alp_Building.IsDoorOpen(index) && !alp_Building.IsDoorLocked(index) )
						{
							//Print("OTEVIRAM DVERE");
							
							alp_Building.OpenDoor(index);
							
						}	

						alp_Building = null;	
					}					
					/*
					//transport			
					if ( alp_IsTransport == 1 )
					{
						alp_IsTransport = -1;
						
						StartCommand_Vault(2);
						return true;
					}
					DayZInfectedCommandVault vaultCmd = GetCommand_Vault();
					if ( vaultCmd && vaultCmd.WasLand() )
					{
						alp_IsTransport	= 0;		
					}	
					*/				
				}					
			}

						

			if (  alp_OverridenSpeed && actualSpeed == alp_SpeedMax  && alp_TimeStempSpeed > 0.5 )
			{
				ic.OverrideMovementSpeed(false,alp_SpeedMax);		
				
				actualSpeed = ic.GetMovementSpeed();	
				
				if (  actualSpeed > alp_SpeedMax )
				{
					ic.OverrideMovementSpeed(true,alp_SpeedMax);	
					alp_TimeStempSpeed = 0;				
				}						
				
			}	
			


			
		}
		
		return ret;
	}	
	float alp_TimeStempDoors;
	
	
	float alp_LastGlobalHealth = 100;
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{

		if ( alp_Armor && IsZombieCustomed() )
		{
			float damage;

			if ( damageResult )
			{	
				damage = damageResult.GetDamage( dmgZone, "Health");//.GetHighestDamage("Health");
			}
			
			if ( dmgZone != "Head" )
			{
				

				if ( alp_LastGlobalHealth >  40 )
				{
					float transerDamage = 1;
								
					switch ( dmgZone )
					{
						case "LeftLeg":
						case "RightLeg":
							transerDamage = 0.33;
							break;
						case "LeftFoot":
						case "RightFoot":
							transerDamage = 0.1;
							break;				
					}				
					
					alp_LastGlobalHealth = alp_LastGlobalHealth - damage * transerDamage * alp_Armor;
					SetHealth("GlobalHealth","Health",alp_LastGlobalHealth);
					
					AddHealth(dmgZone,"Health", damage  );	
					damage *= alp_Armor;
					AddHealth(dmgZone,"Health", -damage  );		
					
				}
	
			}		

		}

		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

	
		
	}		
	override float ConvertNonlethalDamage(float damage)
	{
		float dmg = super.ConvertNonlethalDamage( damage);
		
		if ( alp_Armor )
		{
			dmg *= alp_Armor;
		}

		return dmg;
	}	
	

		
	
	bool alp_SpeedCallExist;	
	
	
	void SetSpeedALP(int time)
	{

		
		if ( !alp_SpeedCallExist )
		{
			alp_TimeStempSpeed=1;
			alp_OverridenSpeed = true;
			alp_SpeedMax = 1;
		}
	
		
		if ( alp_SpeedCallExist )
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(this.ResetSpeedALP);
		}

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.ResetSpeedALP,time);
		
		
		alp_SpeedCallExist = true;		
	
	}	
	
	void ResetSpeedALP()
	{
		
		alp_SpeedCallExist = false;
		
		alp_SpeedMax = alp_LastSpeedMax;		
		
		alp_OverridenSpeed = alp_LastOverridenSpeed;	
				
		DayZInfectedInputController ic = GetInputController();
		ic.OverrideMovementSpeed(false,1);	
					

	}
	
	override bool EvaluateDamageHitAnimation(EntityAI pSource, string pComponent, string pAmmoType, out bool pHeavyHit, out int pAnimType, out float pAnimHitDir)
	{	
		bool ret = super.EvaluateDamageHitAnimation(pSource, pComponent, pAmmoType,  pHeavyHit, pAnimType, pAnimHitDir);	
		
		if( GetGame().IsServer() && IsZombieCustomed() )
		{
			pHeavyHit = ((GetGame().ConfigGetInt("cfgAmmo " + pAmmoType + " hitAnimation") > 0) || m_HeavyHitOverride);
			

			if ( pHeavyHit )
			{
				SetSpeedALP(2000);
			}
			else
			{
				SetSpeedALP(1000);	
			}
			
			
			
		}			

		return ret;
		 
	}

	
	bool IsContaminedZombie()
	{
		return false;
	}

	bool IsMonsterZombie()
	{
		return GetND().GetCreatures().IsZombieMonster( GetType() );
	}		
	
	
	override float GetReputationBonusALP()
	{
		return 1 + alp_ReputationBonus;
	}		
	
	bool IsZombieCustomed()
	{
		return GetND().GetCreatures().GetOptions().EnableCretures;
	}
	bool CanOpenUnlockedDoor()
	{
		return GetND().GetCreatures().GetOptions().ZombiesCanOpenUnlockedDoor;
	}	

	bool HandleDoors(out int index )
	{
		autoptr array<Object> entList = new array<Object>;
		DayZPlayerUtils.GetEntitiesInCone(this.GetPosition(), this.GetDirection(), TARGET_CONE_ANGLE_CHASE, 2, -1, 2, entList);
		
		vector zed_pos = GetPosition();
		
		//zed_pos = zed_pos + "0 1.0 0"; 
		
		
		zed_pos[1] = zed_pos[1] + 1.2;
		

		
		float last_distance = 10;
		float distance;
		
		bool found = false;
		
		
		if ( entList )
		{		
			for(int i = 0; i < entList.Count() ;i++)
			{

				if (!entList.Get(i) || entList.Get(i) == this || !entList.Get(i).IsBuilding() )
				{
					continue;
				}
					
				
				//Print("KOUKAM NA " + entList.Get(i).GetType() );
				
				TStringArray selections = new TStringArray;
				entList.Get(i).GetSelectionList( selections );						
				
				foreach( string s : selections )
				{
					if ( s.IndexOf("door") != -1 && s.IndexOf("_action") != -1 )
					{					
					
						vector pos_ms = entList.Get(i).GetSelectionPositionMS( s );
						vector pos_ws = entList.Get(i).ModelToWorld( pos_ms );

						distance = vector.Distance( zed_pos, pos_ws);
						if ( distance <= 2 )
						{
							//Print("DVERE " + s + " distance " + distance );
							if ( distance < last_distance )
							{
								last_distance = distance;
								alp_Building = Building.Cast( entList.Get(i) );
								index = GetDoorIndex(alp_Building.GetType(), s);		
								
								found = true;	
							}
						}
					}
					
				}
			}
			
		}			
		return found;
	}
				

	
	int GetDoorIndex(string type, string door)
	{
		
		//Object.GetActionComponentName
		
		
		door = door.Substring(0, door.IndexOf("_") );
		door =  door.Substring( door.Length() - 3, 3 );
		int count = 0;
		int index = -1;
		string path_base = "" + CFG_VEHICLESPATH + " " + type + " Doors";

		string name;
		if (GetGame().ConfigIsExisting(path_base))
		{
			count = GetGame().ConfigGetChildrenCount(path_base);

			for (int i = 0; i < count;i++)
			{
				GetGame().ConfigGetChildName(path_base,i,name);
				
				name = name.Substring( name.Length() - 3, 3 );
				//Print("config name " + name + " hledano " + door );
				if ( name == door )
				{
				
					//Print("ANNO " + name + " - " + door );
					return i;
				}
			}						
			
		}
	
		return index;
	}
				
}