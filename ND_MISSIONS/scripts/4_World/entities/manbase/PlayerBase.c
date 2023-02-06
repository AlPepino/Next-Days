


// Script File

enum alpEntityType
{
	SUICIDE,
	PLAYER,
	ZOMBIE,
	ANIMAL,
	GRENADE,
}


class alpLastHit
{
	int alp_EntityType;
	int alp_HitTime;
	int alp_DamageType;
	string alp_Source;
	string alp_Name;
	//damageType DT_CLOSE_COMBAT/DT_FIRE_ARM/DT_EXPLOSION/DT_CUSTOM   //ammo == "FallDamage" 
	
	void alpLastHit()
	{
		alp_DamageType = DT_CUSTOM;
	}
	
	void RegisterHit(int entity, int time, int type, string source = "", string name = "")
	{
		alp_EntityType = entity;
		alp_HitTime = time;
		alp_DamageType = type;
		alp_Source = source;
		alp_Name = name;
	}
	
	
	bool IsSuicide()
	{
		int time = GetGame().GetTime();
		int lasthit = alp_HitTime + 30000;
		
		if ( lasthit < time || alp_EntityType == alpEntityType.SUICIDE )
		{
			return true;
		}
		return false;
	}	
}




modded class PlayerBase extends ManBase
{

	bool alp_IsEventOnRunActive;
	
	int alp_PlayerID;
	
	
	ref alpSync alp_Sync;
	ref alpRP alp_RP;
	ref alpPlayerHive alp_Hive;

	ref PlayerStatsALP	alp_PlayerStats;
	
	
	ref alpLastHit	alp_LastHitData;

	
	bool alp_IsPlayerSpawn;
	
	
	bool alp_BrainWasDamaged;

	ref array<int> m_ContaminedItems;
	bool m_HasContaminedItems;
	
	override void Init()
	{
		super.Init();
		
		RegisterNetSyncVariableBool("m_HasContaminedItems");	
		
		m_ContaminedItems = new array<int>;
		
		alp_LastHitData = new alpLastHit();
		
		alp_PlayerStats = new PlayerStatsALP( this );
		
		
		alp_Sync = new alpSync( this );
		
		alp_RP = new alpRP( this );
		
		if ( GetGame().IsClient()  )
		{
			LoadPlayerHive();		
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.ClientOnConnect	, 0 );
			
		}
		
		
		
		InitALP();
		
	}
	
	void AddContaminedItem(int id){
		
		
		if ( m_ContaminedItems.Find(id) == -1 ) {
			//Print("ADD ITEM " + id );
			m_ContaminedItems.Insert(id);
		}
		//Print("m_ContaminedItems " + m_ContaminedItems.Count() );
		m_HasContaminedItems = m_ContaminedItems.Count();
	}
	void RemoveContaminedItem(int id){
		m_ContaminedItems.RemoveItem(id);
		m_HasContaminedItems = m_ContaminedItems.Count();
	}
	
	bool HasContaminedItems(){
		return m_HasContaminedItems;
	}
	
	bool IsPlayerSpawn()
	{
		return alp_IsPlayerSpawn;	
	}
	
	void SetPlayerSpawn(bool state )
	{
		alp_IsPlayerSpawn = state;
	}	
	
	void ClientOnConnect()
	{
		if ( GetGame().GetPlayer() == this )
		{
			GetPlayerHive().OnConnect();
		}		
	}
	
	void InitALP(){}
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{
		super.OnStoreSave( ctx );
		
		if ( GetDayZGame().IsServer() && GetDayZGame().IsMultiplayer() )
		{
			GetPlayerStatsALP().SaveStats(ctx);// save stats		
		}		
	}	

	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( super.OnStoreLoad( ctx, version ) )
		{

			if ( GetDayZGame().IsServer() && GetDayZGame().IsMultiplayer() )
			{
				if (!GetPlayerStatsALP().LoadStats(ctx, version))
				{
					Print("---- failed to load NextDays PlayerStats  ----");
					return false;
				}
			}							
			return true;
		}
		return false;
	}		
	
	PlayerStatsALP GetPlayerStatsALP()
	{
		return alp_PlayerStats;	
	}
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		//LoadPlayerHive(); 
		
		//HOTFIX CONTAMINED ITEMS
		array<EntityAI> itemsArray = new array<EntityAI>;
		ItemBase item;

		GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		for (int i = 0; i < itemsArray.Count(); i++)
		{				
			item = ItemBase.Cast(itemsArray.Get(i));
			
			if ( item && item != this && ( item.GetAgents() & alpeAgents.RADIATION ) ) {
				//Print("Je kontaminovano "  + item.GetType() + " ID " + item.GetID() );
				AddContaminedItem(item.GetID());
			}
		}
						
	}

	void LoadPlayerHive()
	{
		alp_Hive = new alpPlayerHive( this );
	}
	
	alpPlayerHive GetPlayerHive()
	{
		return alp_Hive;
	}
	

		
	alpRP GetRP()
	{
		return alp_RP;
	}
	
	alpSync GetSyncData()
	{
		return alp_Sync;
	}	
	
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick( deltaTime );
		
		
		if( !IsPlayerSelected() || !IsAlive() ) 
			return;
		
		if ( GetGame().IsClient() && GetGame().IsMultiplayer() && GetGame().GetPlayer() == this )
		{
			GetND().OnUpdate( deltaTime );	
			
			if( GetSyncData() ) 
			{
				GetSyncData().OnScheduledTick(deltaTime);
			}				
		}
		
		if ( GetGame().IsServer() && GetIdentity() )
		{
			if( GetSyncData() ) 
			{
				GetSyncData().OnScheduledTick(deltaTime);
			}			
		}
	}


	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		
		int type;
		switch(rpc_type)
		{
			case ALP_RPC_PLAYER:
			{
				ctx.Read(type);
				switch (type)
				{
					case ALP_RPC_PLAYER_TYPE.SYNC_REGISTER_ENHANCEDSTATS:
					{
						
						bool state;
						ctx.Read(state);
						GetSyncData().RegisterToStats(state); //regular RP sync					
						break;
					}					
					case ALP_RPC_PLAYER_TYPE.HIVE_SYNC_ALL:
					{
						if( GetPlayerHive() ) 
						{
							GetPlayerHive().SyncAllRPC(ctx); //regular RP sync
						}						
						break;
					}
					case ALP_RPC_PLAYER_TYPE.HIVE_SYNC_SMALL:
					{
						if( GetPlayerHive() ) 
						{
							GetPlayerHive().SyncSmallRPC(ctx); //regular RP sync
						}						
						break;
					}				
				}
				break;	
			}
			case ALP_RPC_PLAYER_SYNC_BIT:
			{
				if( GetSyncData() ) 
				{
					GetSyncData().OnRPC_RP_STATS(ctx); //regular RP sync
				}
				break;			
			}
			case ALP_RPC_PLAYER_SYNC_VALUE://non regular RP sync - enhanced data
			{
				if( GetSyncData() && IsAlive() ) 
				{
					GetSyncData().OnRPC_RP_STATS_ENHANCED(ctx);
				}
				break;						
			}					
		}	
	}	
	
	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item,slot_name);
		
		
		GetRP().GetProtection().ItemAttached(item,slot_name);

	}	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item,slot_name);
		
		GetRP().GetProtection().ItemDetached(item,slot_name);	
	}	
	
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);	
	
		if ( !IsAlive() && damageResult && dmgZone == "Head" && damageResult.GetHighestDamage( "Health" ) >= 20 )
		{
			alp_BrainWasDamaged = true;
		}
		
		
		//death notification
		if (GetGame().IsServer() && GetND().GetNotf().GetOptions().EnableDeathNotification && GetIdentity() &&  ( IsUnconscious() || !IsAlive() )  )
		{	
			if ( source )
			{
				if ( source.IsZombie() )
				{
					alp_LastHitData.RegisterHit( alpEntityType.ZOMBIE , GetGame().GetTime(), damageType , ammo , "#alp_dead_by_infected" );
				}
				else if (   source.IsAnimal()  )
				{
					alp_LastHitData.RegisterHit( alpEntityType.ANIMAL , GetGame().GetTime(), damageType , ammo , "#alp_dead_by_beast" );	
				}
				else
				{//uknown
					alp_LastHitData.RegisterHit( alpEntityType.SUICIDE, GetGame().GetTime(), damageType , ammo );	
				
				}
			}
			else
			{
				alp_LastHitData.RegisterHit( alpEntityType.SUICIDE, GetGame().GetTime(), damageType , ammo );					
			}
		}		
		
		
		//HOTFIX for grenade killing
		Grenade_Base grenade;
		TrapBase trap;
		if (GetGame().IsServer() && !IsAlive() && ( Class.CastTo( grenade, source ) || Class.CastTo( trap, source )  ) )
		{
			PlayerBase pb;
			if ( grenade )
			{
				if ( grenade.alp_LastOwner && this != grenade.alp_LastOwner ) 
				{
					KilledByPlayerALP(grenade.alp_LastOwner, trap.GetDisplayName() );	
				}			
			}
			if ( trap )
			{
				if (trap.alp_LastOwner && this != trap.alp_LastOwner ) 
				{
					KilledByPlayerALP(trap.alp_LastOwner, trap.GetDisplayName() );
				}			
			
			}

			
		}	
		
		
		
		

	}	
	
		
	override void EEKilled(Object killer)
	{	
		super.EEKilled(killer);			
		
		if (GetGame().IsServer()  ) 
		{	
			
			if ( GetIdentity() )
			{
				PlayerBase player;
				if (m_KillerData && Class.CastTo(player,m_KillerData.m_Killer) && this != player && player.GetIdentity() )
				{
					KilledByPlayerALP(player, "" );				
				}
				
				if ( IsPlayer() && GetPlayerHive() )
				{
	
					GetND().OnDeath( this );
					GetPlayerHive().OnDeath();			
				}
				
				if ( GetND().GetNotf().GetOptions().EnableDeathNotification  )
				{
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.DeathNotificationALP,500);
				
				}			
			
			}
			
			if ( GetND().GetRP().GetPlayerOptions().RaiseZombieAfterDeath ) 
			{
				if ( !GetND().GetRP().GetPlayerOptions().RaiseZombieFromPlayersBodyOnly || GetIdentity() )
				{
					int raiseTime = Math.RandomInt( GetND().GetRP().GetPlayerOptions().RaiseZombieTime[0] ,  GetND().GetRP().GetPlayerOptions().RaiseZombieTime[1] ) * 1000;
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.RaiseZombie,raiseTime);			
				}
			
			}
			

		}	
		
		
	}	
	
	void DeathNotificationALP()
	{
		EntityAI weapon;
		PlayerBase killedby;
		bool headshot = false;
		if ( m_KillerData )
		{
			killedby = PlayerBase.Cast( m_KillerData.m_Killer );
			weapon = m_KillerData.m_MurderWeapon;		
			headshot = m_KillerData.m_KillerHiTheBrain;		
		}
		
		if ( !killedby || killedby == this )
		{//tragic accident
			
			if ( !alp_LastHitData.IsSuicide() )
			{
				GetND().GetNotf().SendGlobalMessage( ALPMSTYPE.SMDEATH, GetIdentity().GetName() + " " + alp_LastHitData.alp_Name );	
			}
			else
			{
				GetND().GetNotf().SendGlobalMessage( ALPMSTYPE.SMDEATH, GetIdentity().GetName() + " #alp_dead_by_unr");	
			}
			
						
		}
		else
		{
			string killerName;
			if ( killedby.GetIdentity() )
			{
				killerName = killedby.GetIdentity().GetName();
			}
			else
			{
				killerName = "NPC";
			}
				
			if (!weapon)
			{//hand to hand?
				GetND().GetNotf().SendGlobalMessage( ALPMSTYPE.SMDEATH,  killerName + " #alp_dead_by_killed " + GetIdentity().GetName() + " #alp_dead_by_combat" );	
			}
			else
			{	
				float distance = vector.Distance( killedby.GetPosition(), GetPosition() );
				if ( headshot )
				{
					GetND().GetNotf().SendGlobalMessage( ALPMSTYPE.SMHEADSHOT,  killerName + " #alp_dead_by_killed " + GetIdentity().GetName() + " #alp_dead_by " +  weapon.GetDisplayName() + " (" + alpUF.NumberToString( distance, 1 ) + "m)" );
				}
				else
				{
					GetND().GetNotf().SendGlobalMessage( ALPMSTYPE.SMDEATH,  killerName + " #alp_dead_by_killed " + GetIdentity().GetName() + " #alp_dead_by " +  weapon.GetDisplayName() + " (" + alpUF.NumberToString( distance, 1 ) + "m)" );														
				}												
			}					
		}	
	
	}
	
	
	void RaiseZombie()
	{	
		bool head_shot = false;;
		if ( m_KillerData )
		{	
			head_shot = m_KillerData.m_KillerHiTheBrain;		
		}	
		
		if ( !head_shot && !alp_BrainWasDamaged )
		{
			EntityAI infected = EntityAI.Cast( GetGame().CreateObject(GetZombieClass(),GetPosition(),false,true) );
			
			
			if ( infected )
			{
				//PlayerBase.GetAttachmentByType
	
				foreach ( int i : DefaultCharacterCreationMethods.m_AttachmentSlots )
				{
					EntityAI item = GetInventory().FindAttachment( i );
					if ( item )
					{
						if (  GetInventory().DropEntity( InventoryMode.SERVER, this, item) )
						{
							
							if (! infected.GetInventory().TakeEntityToInventory( InventoryMode.SERVER,FindInventoryLocationType.ANY, item ) )
							{//damage item??
								float damageToAttch = GetND().GetRP().GetPlayerOptions().RuinDroppedAttch;
								if ( damageToAttch )
								{
									damageToAttch *= item.GetMaxHealth("","health");
									item.AddHealth("","",-damageToAttch);		
								}
								item.GetInventory().UnlockInventory( HIDE_INV_FROM_SCRIPT );
								
								float attLifeTime = GetND().GetRP().GetPlayerOptions().AttchLifeTime;
								if ( !item.IsRuined() && attLifeTime ){
									item.SetLifetime( attLifeTime );
								}
								item.PlaceOnSurface();

							} 						
						
						}	
					}
					

				}				
				int zedLifeTime = GetND().GetRP().GetPlayerOptions().ZombieLifeTime * 1000;
				if ( zedLifeTime ){
					//GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(g_Game.ObjectDelete,zedLifeTime,false, infected);
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(infected.SetHealth,zedLifeTime,false, "","",0);
			
					
				}
				
				DeleteBodyAlp();

			}
	
			
		}
		else
		{
			int deleteBody = GetND().GetRP().GetPlayerOptions().DeadBodyLifeTime;
			
			if ( deleteBody )
			{
				deleteBody *= 1000;
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.DeleteBodyAlp,deleteBody);	
			}
		}			
		
					
				
	}
	
	
	void DeleteBodyAlp()
	{
		GetGame().ObjectDelete( this );
	}
	
	
	string GetZombieClass()
	{
		
		
		if ( IsMale() )
		{
			if ( GetND().GetRP().GetPlayerOptions().MaleZombies &&  GetND().GetRP().GetPlayerOptions().MaleZombies.Count() > 0 )
			{
				return  GetND().GetRP().GetPlayerOptions().MaleZombies.GetRandomElement();
			}
			
			return "ZmbM_NBC_Yellow";
		}
		else
		{
			if ( GetND().GetRP().GetPlayerOptions().FemaleZombies &&  GetND().GetRP().GetPlayerOptions().FemaleZombies.Count() > 0 )
			{
				return  GetND().GetRP().GetPlayerOptions().FemaleZombies.GetRandomElement();
			}
						
			return "ZmbM_NBC_Yellow";
		}
	}
	
	override void OnDisconnect()
	{
		GetPlayerHive().OnDisconnect();
		super.OnDisconnect();
		
	}	
	
	
	
	void KilledByPlayerALP(PlayerBase player, string source )	
	{
		//death notification
		if ( GetND().GetNotf().GetOptions().EnableDeathNotification  )
		{
			alp_LastHitData.RegisterHit( alpEntityType.PLAYER, GetGame().GetTime(), DT_EXPLOSION, source, player.GetIdentity().GetName() );			
		}
				
		//reward if the wanted person						
		if ( GetRP().IsDebtor() )
		{
			RewardForKillingMostWanted( player );		
		}
	}
	

	void RewardForKillingMostWanted(PlayerBase player)
	{
		//reward if the wanted person
		int currency = GetRP().alp_RewardForKill[0];
		int reward = GetRP().alp_RewardForKill[1];
		
		if ( reward )
		{
			alpBANK.AddBalanceToAccount( player.GetPlayerHive().GetPlayerID(), currency, reward, player );
			alpBANK.AddExtraLoanFee( GetPlayerHive().GetPlayerID(), currency, reward );
		}

	}	
	
#ifdef NAMALSK_SURVIVAL	
	override bool Consume(ItemBase source, float amount, EConsumeType consume_type )
	{
		PluginTransmissionAgents plugin = PluginTransmissionAgents.Cast( GetPlugin(PluginTransmissionAgents) );
		int agents;

		// enviro liquid
		// standard well source
		if ( consume_type == EConsumeType.ENVIRO_WELL )
		{
			m_PlayerStomach.AddToStomach(Liquid.GetLiquidClassname(LIQUID_WATER), amount, 0 , agents);
			return true;
		}

		// freezing enviro source (namalsk lakes)
		if ( consume_type == EConsumeTypeNamalsk.ENVIRO_FREEZING )
		{
			agents = agents | eAgents.CHOLERA;
			m_PlayerStomach.AddToStomachAndStomachTemp(Liquid.GetLiquidClassname(LIQUID_WATER), amount, 0.0, agents, 1.0, 0.0);
			return true;
		}

		// frozen enviro source (ice and snow)
		if ( consume_type == EConsumeTypeNamalsk.ENVIRO_FROZEN )
		{
			agents = agents | eAgents.CHOLERA;
			m_PlayerStomach.AddToStomachAndStomachTemp(Liquid.GetLiquidClassname(LIQUID_WATER), amount, 0.0, agents, 2.0, -1.0);
			return true;
		}

		// standard enviro water (not present on Namalsk)
		if ( consume_type == EConsumeType.ENVIRO_POND )
		{
			agents = agents | eAgents.CHOLERA;
			m_PlayerStomach.AddToStomach(Liquid.GetLiquidClassname(LIQUID_WATER), amount, 0 , agents);
			return true;
		}
		//ALPEPINO LIQUID
			if ( consume_type == alpeConsumeType.ENVIRO_WELL_CONTAMINED )
			{
				m_PlayerStomach.AddToStomach(Liquid.GetLiquidClassname(LIQUID_RADIOACTIVEWATER), amount, 0 , agents);
				ConsumeBonusesALP( source,  amount,  consume_type);
				return true;
			}		
			if ( consume_type == alpeConsumeType.ENVIRO_POND_CONTAMINED_FREEZING )
			{
				agents = agents | eAgents.CHOLERA;
				m_PlayerStomach.AddToStomachAndStomachTemp(Liquid.GetLiquidClassname(LIQUID_RADIOACTIVEWATER), amount, 0.0, agents, 1.0, 0.0);
				ConsumeBonusesALP( source,  amount,  consume_type);
				return true;
			}		
			if ( consume_type == alpeConsumeType.ENVIRO_SNOW_CONTAMINED_FROZEN )
			{
				agents = agents | eAgents.CHOLERA;
				m_PlayerStomach.AddToStomachAndStomachTemp(Liquid.GetLiquidClassname(LIQUID_RADIOACTIVEWATER), amount, 0.0, agents, 2.0, -1.0);
				ConsumeBonusesALP( source,  amount,  consume_type);
				return true;
			}		
			if ( consume_type == alpeConsumeType.ENVIRO_POND_CONTAMINED )
			{
				agents = agents | eAgents.CHOLERA;
				m_PlayerStomach.AddToStomach(Liquid.GetLiquidClassname(LIQUID_RADIOACTIVEWATER), amount, 0 , agents);
				ConsumeBonusesALP( source,  amount,  consume_type);
				return true;
			}

		//ALPEPINO LIQUID END
		
		// solid or item liquid
		float edible_item_wet = 0.0, edible_item_temp = 0.0;
		Edible_Base edible_item = Edible_Base.Cast(source);
		if ( !edible_item )
		{
			return false;
		}
		agents = edible_item.GetAgents();
		edible_item_wet = edible_item.GetWet();
		edible_item_temp = edible_item.GetTemperature();
		if ( consume_type == EConsumeType.ITEM_SINGLE_TIME || consume_type == EConsumeType.ITEM_CONTINUOUS )
		{
			if (consume_type == EConsumeType.ITEM_SINGLE_TIME)
			{
				plugin.TransmitAgents(edible_item, this, AGT_UACTION_CONSUME, amount);
			}
			if (edible_item.IsLiquidContainer())
			{
				int liquid_type = edible_item.GetLiquidType();
				m_PlayerStomach.AddToStomachAndStomachTemp(Liquid.GetLiquidClassname(liquid_type), amount, 0, agents, edible_item_wet, edible_item_temp);
			}
			else 
			{
				int food_stage_type;
				if ( edible_item.GetFoodStage() )
				{
					food_stage_type = edible_item.GetFoodStage().GetFoodStageType();
				}
				m_PlayerStomach.AddToStomachAndStomachTemp(source.GetType(), amount, food_stage_type, agents, edible_item_wet, edible_item_temp);
			}
			
			if (edible_item_temp >= PlayerConstants.HOT_FOOD_TEMP_LOWER_THRESHOLD) {
				float dmg = -1 * edible_item.CalculateDamageFromTemperature();
				AddHealth("", "Health", dmg);
				AddHealth("", "Shock", dmg * 3);
				
				if (dmg >= 9) {
					SendSoundEvent(EPlayerSoundEventID.TAKING_DMG_HEAVY);
				} else {
					SendSoundEvent(EPlayerSoundEventID.TAKING_DMG_LIGHT);
				}
			}

			edible_item.Consume( amount, this );
			return true;

		}
		return false;		
	}	
	
#else
	
	override bool Consume(ItemBase source, float amount, EConsumeType consume_type )
	{
		if ( ! super.Consume( source, amount, consume_type) )
		{
			int agents;
			if( consume_type == alpeConsumeType.ENVIRO_POND_CONTAMINED || consume_type == alpeConsumeType.ENVIRO_WELL_CONTAMINED )
			{
				if ( consume_type == alpeConsumeType.ENVIRO_POND_CONTAMINED )
				{
					agents = agents | eAgents.CHOLERA;
					//plugin.TransmitAgents(NULL, this, AGT_WATER_POND, amount);
				}
				m_PlayerStomach.AddToStomach(Liquid.GetLiquidClassname(LIQUID_RADIOACTIVEWATER), amount, 0 , agents );
				
				ConsumeBonusesALP( source,  amount,  consume_type);
				return true;
			}				
			return false;			
		}
		ConsumeBonusesALP( source,  amount,  consume_type);
		return true;
		
	}	
	
#endif	
	
	void ConsumeBonusesALP(ItemBase source, float amount, EConsumeType consume_type = EConsumeType.ITEM_SINGLE_TIME)
	{
		
	}
	

	override void SetActionsRemoteTarget( out TInputActionMap InputActionMap)
	{		
		super.SetActionsRemoteTarget(InputActionMap);
		
		AddAction(alpActionBuy);
		AddAction(alpActionSell);
		AddAction(alpActionQuestBringMe);
		AddAction(alpActionStartMission);
		
	}
	
	override bool CanBeRestrained()
	{

		
		if ( !GetRP().IsAllowedDamage() )
		{
			return false;
		}
		return super.CanBeRestrained();
	}	

	override bool IsWeaponRaiseCompleted()
	{				
		if (GetRP().IsInTradeZone() && !GetRP().IsAllowedDamage() ) 
			return false;
				
		return super.IsWeaponRaiseCompleted();//m_WeaponRaiseCompleted;
	}	
	
	override void TogglePlacingLocal(ItemBase item = null)
	{		
		super.TogglePlacingLocal(item);
		
		if ( GetRP().IsInTradeZone() )
			PlacingCancelLocal();

	}			

	
	bool IsErectedALP(){
		HumanMovementState		state 	= new HumanMovementState();
		GetMovementState(state);
		int player_stance = state.m_iStanceIdx;
		if ( player_stance == DayZPlayerConstants.STANCEIDX_ERECT ) {
			return true;
		}
		return false;
	}
	
	
	void ForceStanceALP(int id)
	{
		if ( id >= 0 )
		{			
			HumanCommandMove cm = GetCommand_Move();
			if (cm)
			{
				switch(id){
					case 0: 
						cm.ForceStance( DayZPlayerConstants.STANCEIDX_ERECT );
						break;
					case 1:
						cm.ForceStance(DayZPlayerConstants.STANCEIDX_CROUCH);
						break;
					case 2:
						cm.ForceStance(DayZPlayerConstants.STANCEIDX_PRONE);
						break;					
				}

			}			
		}

	}	
	
	string GetArmBandType() {
		string name = "";		
		EntityAI item = FindAttachmentBySlotName("Armband");
		if ( item ) {
			name = item.GetType();
		}		
		return name;
	}
	
	int GetClanID()
	{
		return 0;
	}	
	
	float GetReputationMltp(int action ) {
		return 0;	
	}
	

	
}