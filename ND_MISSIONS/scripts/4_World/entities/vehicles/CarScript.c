
/*!
	Base script class for all motorized wheeled vehicles.
*/
modded class CarScript extends Car
{

	
	bool 						alp_Lock;
	int							alp_CarID;
	


	bool						alp_AlarmSound;
	

	
	bool 						alp_EnableCutDownTrees			= false; 	
	float 						alp_RequiredImpulseToCutDown 	= 100000;
	float 						alp_DamageRatioWhenHitTree		= 0.065;	
	float 						alp_DamageRatioWhenHitAI		= 0.065;	
	float 						alp_DamageRatioWhenHitAnyOther 	= 0.065;

	float 						alp_DamageLight 				= 150;		
	float 						alp_DamageHeavy 				= 750;			
	float 						alp_DamageToKillCrew 			= 3000;	
	
	bool						alp_HasCustomProperties;
	
	protected bool 				alp_IsMissionObject 				= false;
	

	
	
	void CarScript()
	{
		//alpPluginNDmissionsSystem.CarsCount = alpPluginNDmissionsSystem.CarsCount + 1;

		
		alp_AlarmSound = false;

		RegisterNetSyncVariableInt("alp_CarID");
		RegisterNetSyncVariableBool("alp_AlarmSound");

		
		if ( GetGame().IsServer()  )
		{								

			alpPluginNDmissionsSystem.AddVehicleToStat( GetType() );
			
			alpVehicleBehavior properties = GetND().GetRP().GetVehicleProperties( GetType() );
			if ( properties )
			{
				alp_HasCustomProperties = true;
				
				alp_EnableCutDownTrees = properties.EnableCutDownTrees;
				alp_RequiredImpulseToCutDown = properties.RequiredImpulseToCutDown;
				alp_DamageRatioWhenHitTree = properties.DamageContactCoefHitTree;
				alp_DamageRatioWhenHitAI = properties.DamageContactCoefHitAI;
				alp_DamageRatioWhenHitAnyOther = properties.DamageContactCoefHitAnyOther;
				
				alp_DamageLight = properties.DamageLight;	
				alp_DamageHeavy = properties.DamageHeavy;
				alp_DamageToKillCrew = properties.DamageToKillCrew;		
			}		
		}		

	}
	void ~CarScript(){
		//alpPluginNDmissionsSystem.CarsCount = alpPluginNDmissionsSystem.CarsCount + 1;	
		
		if ( GetGame() && GetGame().IsMultiplayer() && GetGame().IsServer() ) {
			alpPluginNDmissionsSystem.RemoveVehicleFromStat( GetType()  );
			
		}
		
			
	}	
	
	int GetAlpCarID()
	{
		return alp_CarID;
	}
	void SetAlpCarID(int carid)
	{
		alp_CarID = carid;
	}	

	string GetServerWorldID()
	{
		return GetNetworkIDString();
	}
		
	bool HasCustomProperties()
	{
		return alp_HasCustomProperties;
	}
	
	bool CanCutTreeALP()
	{
		return alp_EnableCutDownTrees;
	}
	
	float RequiredImpulseToCutDownALP()
	{
		return alp_RequiredImpulseToCutDown;
	}
	float DamageContactCoefHitTreeALP()
	{
		return alp_DamageRatioWhenHitTree;
	}		
	float DamageContactCoefHitAIALP()
	{
		return alp_DamageRatioWhenHitAI;
	}
	float DamageContactCoefHitAnyOtherALP()
	{
		return alp_DamageRatioWhenHitAnyOther;
	}	
	float DamageLightALP()
	{
		return alp_DamageLight;
	}	
	float DamageHeavyALP()
	{
		return alp_DamageHeavy;
	}		
	float DamageToKillCrewALP()
	{
		return alp_DamageToKillCrew;
	}		
	
	override void EEInit()
	{
		super.EEInit();
		
		
		if ( GetGame().IsServer() )
		{
			if ( alp_CarID == 0 ) 
				SetCarID();

		}		
	}

	protected void SetCarID()
	{
		alp_CarID = Math.RandomIntInclusive( 1, int.MAX - 1 );
		SetSynchDirty();
	}

	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );

		Param2 <bool,int> data = new Param2<bool,int>(alp_Lock,alp_CarID);
		ctx.Write( data );
		ctx.Write( alp_IsMissionObject );

	}
	
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		bool result = super.OnStoreLoad( ctx, version );
		
		if (! GetND().IsFirstRun()  )
		{
			Param2 <bool,int> data = new Param2<bool,int>(0,0);
			if ( !ctx.Read( data ) ){
				result = false;;	
			}
			
			alp_Lock 				= data.param1;
			alp_CarID 				= data.param2;

			
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetVehicleLockState,100,false, alp_Lock );
			
			if ( alp_CarID == 0 )
			{
				SetCarID();	
				SetSynchDirty();
			}							

							
			if ( !ctx.Read( alp_IsMissionObject ) ){
				result = false;;	
			}
		}		
		
		return result;
		/*
		if ( super.OnStoreLoad( ctx, version ) )
		{
			if (! GetND().IsFirstRun() )
			{
				Param2 <bool,int> data = new Param2<bool,int>(0,0);
				ctx.Read( data );
				
				alp_Lock 				= data.param1;
				alp_CarID 				= data.param2;

				
				SetVehicleLockState( alp_Lock );
				if ( alp_CarID == 0 )
				{
					SetCarID();	
					SetSynchDirty();
				}							

				ctx.Read( alp_IsMissionObject );				
	
			}

			
			return true;
		}
		else return false;
		*/
	}		
	
	protected void SetVehicleLockState( bool state)
	{
		alp_Lock = state;
		
		if (state)	
		{
			GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
			
			if ( state && GetND().GetRP().GetVehicleOptions().IndestructibleLockedVehicle  )
			{
				LockVehicleAttachmentsALP( false );
				SetAllowDamage( false );
			}
							
		}
		SetSynchDirty();
	}
	void LockVehicleALP( bool state)
	{
		alp_Lock = state;
		
		if (state)	
		{
			GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
			
			if ( state && GetND().GetRP().GetVehicleOptions().IndestructibleLockedVehicle  )
			{
				LockVehicleAttachmentsALP( false );
				SetAllowDamage( false );
			}				
		}
		else
		{
			GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
			
			if (GetND().GetRP().GetVehicleOptions().IndestructibleLockedVehicle  )
			{
				LockVehicleAttachmentsALP( true );
				SetAllowDamage( true );
			}			
		}
	
	}
	void LockVehicleAttachmentsALP(bool state)
	{
		int attachments_count = GetInventory().AttachmentCount();

		
		for ( int i = 0; i < attachments_count; i++ )
		{
			ItemBase item = ItemBase.Cast( GetInventory().GetAttachmentFromIndex( i ) );
			
			if ( item )
			{
				item.SetAllowDamage( state );	
			}
		}
		
	}
	
	void MissionLockVehicleALP( bool state)
	{
		alp_Lock = state;
		
		if (state)	
		{
			GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
			
			LockVehicleAttachmentsALP( false );
			SetAllowDamage( false );				
		}
		else
		{
			GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
			
			LockVehicleAttachmentsALP( true );
			SetAllowDamage( true );		
		}
	
	}

	

	
	float GetDamageContactCoefALP(IEntity other)
	{
		float coef = DamageContactCoefHitAnyOtherALP();
		
		EntityAI ent;
		
		if ( Class.CastTo(ent, other))
		{
			if (ent.IsTree())
			{
				return DamageContactCoefHitTreeALP();	
			}
			if (ent.IsMan() || ent.IsZombie() || ent.IsAnimal() )
			{
				return DamageContactCoefHitAIALP();		
			}		
		}
		
		return coef;
	}
	
	override void CheckContactCache()
	{
		if ( !GetND().GetRP().GetVehicleOptions().IndestructibleVehicles && !HasCustomProperties() )
		{
			super.CheckContactCache();
			return;
		}		
		
		int contactZonesCount = m_ContactCache.Count();
		if ( contactZonesCount == 0 )
			return;
		
				
		if ( GetND().GetRP().GetVehicleOptions().IndestructibleVehicles )
		{
			m_ContactCache.Clear();
			return;
		}
		
		if ( HasCustomProperties() )
		{
			bool playLightSound = false;
			bool playHeavySound = false;	
			float hitTreeDamage = 0;	
			
			WoodBase plant;
			PlayerBase driver;
		
			for ( int i = 0; i < contactZonesCount; ++i)
			{
				string zoneName = m_ContactCache.GetKey(i);
				array<ref CarContactData> data = m_ContactCache[zoneName];
	
				float dmg;
		
				int contactCount = data.Count();
				for ( int j = 0; j < contactCount; ++j )
				{
					dmg = data[j].impulse * GetDamageContactCoefALP( data[j].other );

					if ( CanCutTreeALP() && Class.CastTo(plant, data[j].other ) )
					{
						hitTreeDamage = hitTreeDamage + data[j].impulse;
						
					}
				}	
				//Print( hitTreeDamage );
				if ( hitTreeDamage > RequiredImpulseToCutDownALP() && plant && Class.CastTo(driver, CrewMember(0) ) && plant.GetHealth01("","") > 0 )
				{
					plant.OnTreeCutDown(driver);
					plant.SetHealth("","",0);
					
				}
				
				if ( dmg < DamageLightALP() )
					continue;
				
				int pddfFlags;
	
				if ( dmg < DamageHeavyALP() )
				{				
					playLightSound = true;
					pddfFlags = ProcessDirectDamageFlags.NO_TRANSFER;
				}
				else
				{	
					DamageCrew(dmg);
					playHeavySound = true;	
					pddfFlags = 0;
				}
				
				ProcessDirectDamage( DT_CUSTOM, null, zoneName, "EnviroDmg", "0 0 0", dmg, pddfFlags );
			}
			
			if (playLightSound)
				SynchCrashLightSound( true );
			
			if (playHeavySound)
				SynchCrashHeavySound( true );
			
			UpdateHeadlightState();
			UpdateLights();
			
			m_ContactCache.Clear();		
		}
		

	}
	
	override void DamageCrew(float dmg)
	{
		if ( !HasCustomProperties() )
		{
			super.DamageCrew(dmg);
			return;
		}			
		
		for ( int c = 0; c < CrewSize(); ++c )
		{
			Human crew = CrewMember( c );
			if ( !crew )
				continue;

			PlayerBase player;
			if ( Class.CastTo(player, crew ) )
			{
				if ( dmg > DamageToKillCrewALP() )
				{		
					player.SetHealth(0.0);
				}
				else
				{
					float shockTemp = Math.InverseLerp(GameConstants.CARS_CONTACT_DMG_THRESHOLD, GameConstants.CARS_CONTACT_DMG_KILLCREW, dmg);
					float shock = Math.Lerp( 50, 100, shockTemp );
					float hp = Math.Lerp( 2, 60, shockTemp );

					// These should ideally be ProcessDirectDamage...
					player.AddHealth("", "Shock", -shock );
					player.AddHealth("", "Health", -hp );
					//Print( "SHOCK..........." + shock );
					//Print( "HEALTH..........." + hp );
				}
			}
		}
	}	
	
	
	
	void PlayAlarmSound()
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{		
			EffectSound sound =	SEffectManager.PlaySound("alp_CarAlarm_SoundSet", GetPosition() );
			sound.SetSoundAutodestroy( true );
			alp_AlarmSound = false;
		}
	}
	
	override float OnSound( CarSoundCtrl ctrl, float oldValue )
	{
		float value = super.OnSound( ctrl, oldValue);
		
		if ( GetGame().IsServer() )
		{
			if ( alp_AlarmSound )
				alp_AlarmSound = false;
		}

		return value;
	}	
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
				
		if (alp_AlarmSound )
			PlayAlarmSound();
		
	}
	
	void ActivateAlarmSystem()
	{
		alp_AlarmSound = true;	
	}
	void DisableAlarmSystem()
	{
		alp_AlarmSound = false;	
	}	


	override void OnEngineStart()	
	{
		super.OnEngineStart();
		SetMissionObjectState( false );	
		
		PlayerBase player = PlayerBase.Cast(CrewMember(0));		
		if (player)
		{
			player.GetRP().SetCar ( this );
		}	


		//unlock car
		if (alp_Lock)
		{
			LockVehicleALP( false );			
		}
	
	}
	
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if (! GetND().IsFirstRun() && IsMissionObject() )
		{	
			GetGame().ObjectDelete( this );
		}				
	}		
	bool IsMissionObject()
	{
		return alp_IsMissionObject;
	}
	
	void SetMissionObjectState(bool state)
	{
		alp_IsMissionObject	= state;
	}	
	
	ref alpTraderItemConfig alp_TraderItemConfig;
	
	alpTraderItemConfig GetTraderItemConfig()
	{
		//kontorla existence v input od uzivatele
		
		
		//default z configu
		if ( !alp_TraderItemConfig)
		{
			alp_TraderItemConfig = alpTraderCoreBase.GetTraderItemConfig( GetType() );
			
			if (!alp_TraderItemConfig )
			{
				alp_TraderItemConfig = new alpTraderItemConfig( GetType(), 0, 0,0 ,0, 0, 0, 0);
			}

		}
		
	
		return alp_TraderItemConfig;
	}		
	
	
	int GetAttachmentCountALP()
	{		
		//return GetInventory().AttachmentCount();
		EntityAI attachment;
		int attcount = GetInventory().AttachmentCount();
		int count = 0;
		for (int att = 0; att < attcount; att++)
		{	
			attachment = GetInventory().GetAttachmentFromIndex(att);
			if ( attachment.IsItemBase() && attachment.HasAnyCargo())
			{
				count++;
			}
		}							
		return count;
	}
	
	string GetNameALP()
	{		
		string name = GetType() + "_"  + GetQuantityALP().ToString() + "_" + GetHealthLevelALP().ToString() + "_" + GetAttachmentCountALP().ToString() + "_" + GetCargoCountALP().ToString();
		return name;
	}
	int GetCargoCountALP()
	{
		int cargo = 0;
		
		if ( HasAnyCargo() )
			cargo = GetInventory().GetCargo().GetItemCount();		
		
		return cargo;
	}
	
	float GetQuantityALP()
	{
		return 1;
	}
		
	float GetHealthLevelALP()
	{
		float level = 1;
		
		switch (GetHealthLevel())
		{
			case 1:
			{
				level = 0.75;
				break;
			}
			case 2:
			{
				level = 0.50;
				break;
			}			
			case 3:
			{
				level = 0.25;
				break;
			}
			case 4:
			{
				level = 0;
				break;
			}			
		}
		return level;
	}	
	

	int GetDefaultPrice()
	{
		int price = 0;
		alpTraderItemConfig config = GetTraderItemConfig();		
		if ( !config || ( !config.CanBuy &&  !config.CanSell ) )
		{
			return price;
		}
		
		
		
		price = (int) config.Price * GetHealthLevelALP();
		
		
		return price;
	}	
		
};
