class alpMission extends alpMissionBase
{
	
	
	
	int alp_Count_ALL_AI;
	//first enter feature
	int alp_FirstEnterTime;
	bool alp_AllowedFirstEnterEcho;
	
	//quest item
	string alp_WantedItem;	
	int alp_NPC_id;
	int alp_QuestID;
	
	void SetQuestMissions(int npc_id, int quest_id, string wantedItem)
	{
		alp_WantedItem = wantedItem;
		alp_NPC_id = npc_id;
		alp_QuestID = quest_id;
	}
	
	int GetRegisteredNPC()
	{
		return alp_NPC_id;
	}
	int GetQuestID()
	{
		return alp_QuestID;
	}	
	
	protected void InitVariables(int setting = 0)
	{

		
		//basic init
		alp_StartAt				= 0;
		alp_EndAt				= 0;
		
		
		if ( GetTemplate().saveMissionStage ) {
			if ( setting ) {
				alp_Setting = setting;
			} else {
				alp_Setting = alp_Setting | alpMISSION_SETTING.SAVE_STAGE; 
			}
			
		} else {
			alp_Setting 			= 0;				
		}
		if ( alp_Setting == alpMISSION_SETTING.SAVE_STAGE || alp_Setting == 0 ) {
			SetSetting( alpMISSION_SETTING.MISSION_IDLE );	
		}
			

		alp_MissionStarted		= 0;
		
		if ( GetTemplate().showMissionStatus ) 
			SetSetting( alpMISSION_SETTING.MISSION_STATUS );	
		
		if ( GetTemplate().isActive ) 
			RemoveSetting( alpMISSION_SETTING.MISSION_IDLE );			
		
		if ( GetTemplate().showNameWhoStartedMission ) {
			alp_IsFirstEnter	= true;
			alp_AllowedFirstEnterEcho = true;
			alp_FirstEnterTime = 180;
		}
			
		
		if ( GetTemplate().isPrivateMission ) {
			alp_MissionStarted	= GetND().GetTimeStamp();//GetGame().GetTime();		
			//Print("tahle mise je private " + alp_MissionStarted );
		}
		
		alp_Touched 			= false;
		alp_Deactivated 		= false;
		alp_SpawnRadiusAI		= 1000; 

		alp_MissionLifeTime		= GetTemplate().lifeTime;
		
		
		alp_EventOnEnter		= false;
		alp_EventOnSecured		= false;
		
		if (GetTemplate().lifeTime == 0)
			alp_Permanent = true;

		if (GetTemplate().timeRespawn > 0)
			alp_RespawnLoot	= true;
		
		alp_RespawnLootLifeTime	= GetTemplate().timeRespawn;
		
		alp_LootContainer		= new array< ref alpMissionElement>;
		alp_Structures 			= new array< ref alpMissionElement>;
		
		alp_ToxicZones			= new array< ref alpMissionElement>;

		alp_NPC 				= new array< ref alpMissionElement>;
		alp_Vehicles			= new array< ref alpMissionElement>;
		
		alp_StaticAI 			= new array< EntityAI>;
		alp_DynamicAI 			= new array< EntityAI>;	
		alp_CountAI_static		= 0;
		alp_CountAI_dynamic		= 0;
		alp_CountAI_dead_static	= 0;
		alp_CountAI_dead_dynamic= 0;		

		
		if ( alp_MissionAI && alp_MissionAI.Count() > 0 ) {
			alp_AvailableDynamicAI	= true;
			alp_AvailableDynamicInRestockAI = true;
			alp_AvailableStaticInRestockAI = true;		
		} else {
			alp_AvailableDynamicAI	= false;
			alp_AvailableDynamicInRestockAI = false;
			alp_AvailableStaticInRestockAI = false;		
		}

		
		alp_Insiders 			= new array<ref alpMissionInsider>;	
		
		alp_OccupiedManagement.ClearFlags();
	
	}

	override protected bool CanBeSpawned()
	{
		if ( super.CanBeSpawned() ){
			if ( !CanMissionExist( GetTemplate().spawnWhenActiveMissions, GetTemplate().spawnWhenDeactiveMissions ) ) {
				return false;
			}
			string group = GetTemplate().missionGroup;
			if (!GetND().GetMS().HasGroupPermission(group)){
				return false;
			}								
			return true;
		}
		return false;
		
	}	
	
	bool CanMissionExist( array<string> mustBeActive, array<string> mustBeDeactive ){
		int countActive = mustBeActive.Count();
		int countDeactive = mustBeDeactive.Count();
		if (  countActive || countDeactive  ) {
			bool isActive;
			bool areDeactive = true;
			
			if ( !countActive ) {
				isActive = true;
			} else {
				isActive = false;				
			}		
			
			foreach( string active : mustBeActive ){				
				array<ref alpMission> ams = GetND().GetMS().GetMissionByName(active);
				if (ams){
					foreach( alpMission ms : ams ) {
						if ( ms.IsActive() ) {
							isActive = true;
							break;
						}
					}					
				}

			}	
			foreach( string deactive : mustBeDeactive ){
				array<ref alpMission> deams = GetND().GetMS().GetMissionByName(deactive);				
				if (deams){
					foreach( alpMission deam : deams ) {
						
						if ( deam.IsActive() ) {
							areDeactive = false;
							break;
						}
					}					
				}				

			}						
			if ( isActive && areDeactive ) {
				return true;
			} else {
				return false;
			}
		}		
		return true;
	}
	
	
	void LoadMission( alpMissionStore s ){
		m_Hive = s;
Print("ALPMS: load mission from hive: " + alp_Name);//log		
		InitVariables(s.m_Setting);	
		alp_EventOnEnter = true;//no dynamic NPC and zones
		//SpawnStructures() && SpawnControlPanels() && SpawnLoot() && SpawnVehicles() && SpawnNPC() && SpawnToxicZone()
		
		LoadStructures();
		LoadControlPanels();
		LoadLoots();
		LoadCars();
		LoadToxicZones();
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.LoadNPCs,2000);
			
		alp_Active = true;
		
		alp_Position = s.m_Position;				
		alp_Angle    = s.m_Angle;		
		alp_ParendId = s.m_ParendId;	
		
		InitMissionValues(s.m_DamageRadius, s.m_Radiation);
		alp_CleanRadius = s.m_CleanRadius;
		EstimateSides(); //make squar instead of circle
		if (!IsCleared()){
			SpawnAIstatic();
		}													
		alp_Restock -= 1;		
		alp_LastSetting = alp_Setting;
		alp_LastRadiationSetting = alp_Setting & alpMISSION_SETTING.RADIATION_ACTIVE;			
		alp_LastEndingSetting = IsMissionEnded();		
		//timestemp
		alp_StartAt = GetND().GetTimeStamp();//GetGame().GetTime();		
		GetND().GetMS().SendRPC_Update( this );//update data to clients	
Print("ALPMS: load mission from hive: " + alp_Name + " was successfull");		
		/*
		int delay = GetTemplate().postponeEventOnStart * 1000;
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.EvenetOnStart, delay);		
		*/	
		//change group count			
		GetND().GetMS().ChangeGroupLimit( GetTemplate().missionGroup,1);		
	}
	
	
	
	override alpMissionBase SpawnMission(vector pos = "0 0 0", vector angle = "0 0 0", int parentID = -1 )
	{

		Print("ALPMS: spawning mission: " + alp_Name);//log			
		InitVariables();

		if ( GetTemplate().isManaged && GetTemplate().isPositionRelativeToMasterMission )
		{
			alp_Position = pos;				
			alp_Angle    = angle;
		}		
		
		m_Hive = alpMHIVE.RegisterMission(this);
		m_Hive.UpdateSetting(alp_Setting);//save paramteres
		if ( IsMissionCreated() )
		{
			alp_Active = true;
			alp_ParendId = parentID;
			
			InitMissionValues();
			
			//CleanRadius must be equel or higher than max of alp_SafeRadius; alp_DamageRadius
			int maxRadius = Math.Max(alp_SafeRadius,alp_DamageRadius);
			alp_CleanRadius = Math.Max( alp_CleanRadius, maxRadius);

			
			EstimateSides(); //make squar instead of circle
		
			if (!IsCleared()){
				SpawnAIstatic();
			}													
			alp_Restock -= 1;		
			alp_LastSetting = alp_Setting;
			alp_LastRadiationSetting = alp_Setting & alpMISSION_SETTING.RADIATION_ACTIVE;			
			alp_LastEndingSetting = IsMissionEnded();
			
			//timestemp
			alp_StartAt = GetND().GetTimeStamp();//GetGame().GetTime();			
			
			GetND().GetMS().SendRPC_Update( this );//update data to clients
									
			if ( GetTemplate().sendInfo && GetTemplate().startMessage != "" )
			{				
				//GetND().GetNotf().SendMissionMessage(  alp_SendInfoStart	, GetID(), GetTemplate().startMessage, GetPosition(), null, true );
				
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( GetND().GetNotf().SendMissionMessage, 1000, false, alp_SendInfoStart	, GetID(), GetTemplate().startMessage, GetPosition(), null, true );
			}
			
			Print("ALPMS: spawning mission on position: " + GetPosition().ToString() + " was successfull");
			
			int delay = GetTemplate().postponeEventOnStart * 1000;
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.EvenetOnStart, delay);
			
			//NPC flag
			alp_AllNPCspawned = false;
			
			//change group count			
			GetND().GetMS().ChangeGroupLimit( GetTemplate().missionGroup,1);
			

			m_Hive.InitMission(this);//save paramteres
			return this;
		}
		else
		{
			Print("ALPMS: spawning mission on position: " + GetPosition().ToString() + " isn't possible");
			DespawnMissionObjects();
			RespawnMission( GetMissionRespawnTime() );			
			return null;
		}
	}
			
		
	bool IsMissionCreated()
	{
		return MetExtraConditions() && SetPosition() && SpawnStructures() && SpawnControlPanels() && SpawnLoot() && SpawnVehicles() && SpawnNPC() && SpawnToxicZone();
	
	}	
	
	
	protected bool MetExtraConditions(){
		if ( alp_Restock < 0 )//no infinity mission restock any more;
			return false;			
		
		int maxVehicles = GetTemplate().maxCountVehiclesInGame;
		if ( maxVehicles && !alpPluginNDmissionsSystem.CanSpawnVehicleInMission( maxVehicles, GetTemplate().vehicleTypes ) ) {
			//Print("Nelze vytvorit misi, limit vozidel " + maxVehicles + " typu " + GetTemplate().vehicleTypes );
			return false;
		}
		return true;
	}
//-------------------------------------------------------------------
//***************************//
//First spawn condition - verification available spot
//***************************//		
	protected bool SetPosition()
	{
		if ( GetTemplate().isManaged && GetTemplate().isPositionRelativeToMasterMission )
		{				
			return true;
		}
		
		
		
		array<float> coordinates = GetFreeCoordinates();
		int count = coordinates.Count();
		if ( count >= 4 )
		{
			alp_Position = Vector( coordinates.Get(0), coordinates.Get(1), coordinates.Get(2) );
			alp_Angle = Vector(  coordinates.Get(3), 0 , 0 );
			alp_Angle = alp_Angle.GetRelAngles();
			if ( count >= 5 ) {
				alp_MinH = coordinates.Get(4);
			}
			
			return true;
		} 
		else
		{
			return false;
		}
				
	}
				
		
//-------------------------------------------------------------------
//***************************//
//Acces to foreign variables
//***************************//	
	protected alpLoot GetLoots(string title)
	{
		return GetND().GetMS().alp_LootMap.Get(title);
	}
	
	protected alpVehicles GetVehicles(string title)
	{
		return GetND().GetMS().alp_VehiclesMap.Get(title);
	}	
	

	
	array<float> GetFreeCoordinates()
	{
		return GetND().GetMS().GetFreePlace().GetPosition( this );
	}		
	
//=============================================================================================//
//=============================================================================================//
//CLASS METHODS CLIENT ONLY
//=============================================================================================//	
//=============================================================================================//

	
	void ClientTouch( float timeslice )
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer());
		
		if ( player )
		{
			if ( IsActive() ) {
				//server mission time
				alp_MissionTime = GetND().GetTimeStamp();//GetGame().GetTime();				
				if ( IsAreaClear() ) {
					if ( alp_AspectRatioB ) {			
						if ( Math.IsPointInRectangle(alp_CleanRadiusPointB,alp_CleanRadiusPointA,player.GetPosition()) ){
							alp_Touched = true;				
							GetND().GetMS().SendRPC_INOUT( player , GetID() );						
						}
					} else if ( alpUF.VectorDistance( GetPosition(),player.GetPosition()) <= GetCleanRadius() ) {
						alp_Touched = true;				
						GetND().GetMS().SendRPC_INOUT( player , GetID() );					
						
					}
				}
					
			}				
		}
		

		
	}
	
	
	void AddInsider(Object obj){
		if ( obj ) {
			alpMissionInsider ins;		
			for(int n = 0; n < alp_Insiders.Count(); n++)
			{
				ins = alp_Insiders.Get(n);
				
				if (  obj == ins.GetObject() )
					return;
			}
			ins = new alpMissionInsider(obj);
			alp_Insiders.Insert(ins);
			
			if ( obj.IsMan() ) 
				OnEnterPlayer( PlayerBase.Cast(obj) );			
		}

	}	
	
	protected void OnEnterPlayer(PlayerBase player) 
	{
		ClientEnterZoneRPC(player);
	};	
	
	protected void ClientEnterZoneRPC(PlayerBase player)
	{
				
		if (GetTemplate().pagerInfo && GetTemplate().pagerMessageIn != "" )
		{
			GetND().GetNotf().SendMissionMessage(  alp_PagerInfoIn	, GetID(),GetTemplate().pagerMessageIn, GetPosition(), player );
		}

	}	
	
	protected void ClientLeftZoneRPC(PlayerBase player)
	{
		GetND().GetMS().SendRPC_INOUT( player , GetID() );
		
		if (GetTemplate().pagerInfo && GetTemplate().pagerMessageOut != "" )
		{
			GetND().GetNotf().SendMissionMessage( alp_PagerInfoOut	,  GetID(), GetTemplate().pagerMessageOut, GetPosition(), player );

		}		
				
	}		

	
	protected void OnLeavePlayer(PlayerBase player) 
	{
		ClientLeftZoneRPC(player);
	}	
//-------------------------------------------------------------------
//***************************//
//mision managing methods
//***************************//	
	override int GetCurrentTime(){
		int current = alpPluginNDmissionsSystem.GetCurrentTime();	
		return current;
	}
	


	protected bool IsEndTime() {
		int current = alpPluginNDmissionsSystem.GetCurrentTime();
		
		int delta = Math.AbsInt( current - alp_EndTime );
		
		if ( delta <= 3 ) {
			return true;
		} else {
			return false;
		}
	}


	protected bool CheckExpiredCondition(float timeslice){
		if ( !CanMissionExist( GetTemplate().despawnWhenDeactiveMissions, GetTemplate().despawnWhenActiveMissions  ) ) {
			return true;
		}	
		if ( GetTemplate().isDeterminedByExactTime && IsEndTime() ) {
			return true;
		}		
		
		if ( GetTemplate().conditionMaxPlayers && GetTemplate().conditionMaxPlayers <  GetPlayersCount()  ) {
			return true;
		}
		if ( alp_SpawnInNightOnly && !GetGame().GetWorld().IsNight() ) {
			return true;
		}							
		if ( ( alp_Setting & alpMISSION_SETTING.MISSION_IDLE ) && !IsPermanent() ) {
			alp_MissionLifeTime -= timeslice;		
			if ( alp_MissionLifeTime <= 0 ) {			
				return true;
			}			
		}			
		return false;
	}
	
	
	protected bool CheckFailedCondition(float timeslice){	
		return false;
	}
	
	
	protected bool CheckSecuredCondition(float timeslice){		
		//new despawn condition
		bool availableLoot = false;
		if ( GetTemplate().lootMustBeTakenOff ) {
			if ( alp_LootContainer && alp_LootContainer.Count() > 0 ){
				for( int i = 0; i < alp_LootContainer.Count();){
					ItemBase itm = ItemBase.Cast( alp_LootContainer.Get(i).Get() );
					if ( !itm || itm.IsRuined() || ( itm.GetHierarchyRoot() && itm.GetHierarchyRoot().IsMan() ) ) {
						int id = alp_LootContainer.Get(i).GetID();
						m_Hive.RemoveLoot(id);	
						alp_LootContainer.Remove(i);		
						continue;
					}
					availableLoot = true;
					i++;
				}
			}
		}		
		//Print("MIse " + alp_Name + " available loot "  + 	availableLoot + " ai " + IsNotAavailableAnyAI() );
		//Print("KONTROLA LOOTU " + availableLoot + " mise " + alp_Name + " je vycisteno " + (alp_Setting & alpMISSION_SETTING.MISSION_CLEARED) );		

		if ( ( alp_Setting & alpMISSION_SETTING.MISSION_CLEARED || IsNotAavailableAnyAI() )  && !availableLoot ) {
			return true;
		}	
		return false;
	}

	protected void ActionUnsecuredArea(float timeslice){
		//if reinforcment
		/*
		if ( ( alp_Count_ALL_AI <= 0 && IsAvailableRestockAI() ) ) { //cleared		
			
			
		if ( !alp_AvailableDynamicAI && alp_AvailableDynamicInRestockAI ) {
			alp_SpawnRadiusAI		= 1000; 
		}
		*/
	}

	protected void ActionClearedArea(float timeslice){
	
	}
	protected void ActionOccupiedArea(float timeslice){
	
	}
	
	bool IsMission() {
		if ( GetTemplate().lootMustBeTakenOff ) {
			return true;
		}
			
		
		if ( alp_Type == ALP_MISSIONTYPEID.noradiation ||   alp_Type == ALP_MISSIONTYPEID.radiation || alp_Type == ALP_MISSIONTYPEID.trader || alp_Type == ALP_MISSIONTYPEID.savemerchants) {
			return false;
		}
		return true;
	}
	
	protected void CheckMissionStage(float timeslice){               

		
		//expired
		if ( CheckExpiredCondition( timeslice ) ) {
			SetExpired();
			return;
		}
		//failed
		if ( !( alp_Setting & alpMISSION_SETTING.MISSION_IDLE ) && CheckFailedCondition( timeslice ) ) {//check only if the mission started
			SetFailed();
			return;
		}				
		//secured			
		if ( IsMission() && !( alp_Setting & alpMISSION_SETTING.MISSION_IDLE ) /*&& ( alp_Setting & alpMISSION_SETTING.MISSION_OCCUPIED )*/ && CheckSecuredCondition( timeslice ) ) {//check only if the mission started and its final stage
			SpawnLoot(true);
			SpawnVehicles(true);
			UnlockLoot();
			SetSecured();
			return;
		}
					
		if ( alp_Setting & alpMISSION_SETTING.MISSION_UNSECURED && !IsCleared() )  {			
			if ( ! IsAvailableDynamicAI() ) {
				CheckAI();
			} 	
			ActionUnsecuredArea(timeslice);
		}		
		
		if ( alp_Setting & alpMISSION_SETTING.MISSION_CLEARED  )  {
			ActionClearedArea(timeslice);							
		}

		if ( alp_Setting & alpMISSION_SETTING.MISSION_OCCUPIED  || alp_Setting & alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED )  {
			ActionOccupiedArea(timeslice);			
		}		
					
	}
	
	override void ManageMission(float timeslice)
	{
		if ( IsActive() )
		{	
			//server mission time
			alp_MissionTime = GetND().GetTimeStamp();//GetGame().GetTime();	
			
			UpdateInsiders();//check insiders first than mission managment
			
			if ( !IsMissionEnded() ){		
				CheckMissionStage(timeslice);//verify mission stage
			}
			
			//check if is not override mission for despawn
			if ( IsMissionEnded() ) {
				if ( !alp_EndAt ) {//end timestamp
					alp_EndAt = GetND().GetTimeStamp();//GetGame().GetTime();
				}
				if ( !alp_EventOnSecured ) {//start event when mission is secured
					EventOnMissionSecured();
					alp_EventOnSecured = true;
				}				
				if ( IsCountdownExpired(timeslice) && GetTemplate().forceCheckDespawnCondition ) {
					DespawnMission();
					return;											
				}
				if ( IsCountdownExpired(timeslice) && IsAreaClear() ) {
					DespawnMission();
					return;					
				}				
			}
			
			if ( IsAreaClear() ) {
				if ( alp_AllowedFirstEnterEcho && !alp_IsFirstEnter ) {
					if ( alp_FirstEnterTime < 0 ) {
						alp_IsFirstEnter = true; 
						alp_FirstEnterTime = 180;
					} else {
						alp_FirstEnterTime -= timeslice;
					}					
				}
				
				// 
				if ( !IsCleared() && !alp_SpawnedStaticAI && alp_AvailableStaticInRestockAI  && alp_StaticAI.Count() > 0  ) {//1 - tolerance	
					SpawnAIstatic();	
				}
				
				alp_RespawnLootLifeTime -= timeslice;
				if ( IsLootRespawnEnabled() && alp_RespawnLootLifeTime <=0  ){//loot respawn
					alp_RespawnLootLifeTime = GetTemplate().timeRespawn; 	
					RespawnLoot();
				}		

				
			} 				
			//if 	( alp_LastEndingSetting != IsMissionEnded()  || alp_LastRadiationSetting != ( alp_Setting & alpMISSION_SETTING.RADIATION_ACTIVE )  || (  ( alp_Setting & alpMISSION_SETTING.MISSION_STATUS || GetTemplate().saveMissionStage ) && alp_LastSetting != alp_Setting ) ) {//change mission setting, client sync
			if 	( alp_LastSetting != alp_Setting  ) {//change mission setting, client sync

				if ( alp_LastEndingSetting != IsMissionEnded() && alp_CountdownDespawn ) {
					GetND().GetMS().SendRPC_Update( this, null);//full update data to clients		
				} else if ( alp_Setting & alpMISSION_SETTING.MISSION_STATUS  || alp_LastRadiationSetting != ( alp_Setting & alpMISSION_SETTING.RADIATION_ACTIVE ) || alp_Type == ALP_MISSIONTYPEID.savemerchants  ) {
					GetND().GetMS().SendRPC_Update( this, null, false, true );//update misison setting to clients		
				}								
				alp_LastEndingSetting = IsMissionEnded();		
				alp_LastRadiationSetting = alp_Setting & alpMISSION_SETTING.RADIATION_ACTIVE;
				alp_LastSetting = alp_Setting;									

							
			}			
			
		}
	}	
	
	

	
		
	protected void UpdateInsiders()
	{	
		alp_Touched 				= false;
		bool changedSpawnRadiusAI 	= false;
		
		RemoveOccupied();//clear occupied flags
		
		for(int i = 0; i < alp_Insiders.Count(); )
		{	
			alpMissionInsider ins = alp_Insiders.Get(i);
			PlayerBase player;
									
			if ( Class.CastTo( player, ins.GetObject() ) && player.GetIdentity() && player.IsAlive() ) {

				alp_Touched = true;		
				
				int distance = (int) alpUF.VectorDistance ( GetPosition() , player.GetPosition() );
				
				//test rectangle
				bool outOfRectangle = false;
				if ( alp_AspectRatioB ) {	
					if ( !Math.IsPointInRectangle(alp_CleanRadiusPointB,alp_CleanRadiusPointA, player.GetPosition()) ){
						outOfRectangle = true;
					}
				}
				
				if ( distance <= GetCleanRadius() && !outOfRectangle )
				{
					if ( distance <= GetDamageRadius() && !( alp_AspectRatioB && !Math.IsPointInRectangle(alp_SafeRadiusPointB,alp_SafeRadiusPointA, player.GetPosition())  ) ){
												
						VerifyPlayer( player.GetClanID() , player.GetArmBandType(), player.GetIdentity().GetName() );//set ocuppied or hostile occupied
						
						//first enter
						if ( alp_IsFirstEnter ){
							
							alp_IsFirstEnter = false;
							ShowPlayerName(  player , (float) distance  );
						}
						
						//add some effects alp_DamageZone
						if ( !alp_Deactivated ) {
							InteractionOnInsiders ( player , (float) distance  );
						}
						
						if ( !ins.alp_DamageZone)
						{
							ins.alp_DamageZone = true;
							OnEnter( player );
						}	

						//spawn dynamic AI
						if (!IsCleared() && IsAvailableDynamicAI() && alp_AvailableDynamicInRestockAI && alp_SpawnRadiusAI > distance )
						{
							alp_SpawnRadiusAI 		= distance;	
							changedSpawnRadiusAI	= true;			
						}
						
						//manage slave mission
						if (!alp_EventOnEnter)
						{
							//spawn dynamic TOXIC zones
							SpawnDynamicToxicZone();
							//spawn dynamic NPC
							SpawnNPCdynamic();
							//set setting on enter
							SetSettingOnEnter();
							
							alp_EventOnEnter = true;
							int delay = GetTemplate().postponeEventOnEnterSafeRadius * 1000;
							GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.EventOnEnterSafeRadius, delay);
						}
						
					}	else {
						if ( ins.alp_DamageZone){
							ins.alp_DamageZone = false;
							OnLeave( player );
						}						
					}
					
				}
				else {
					//obj left area
					OnLeavePlayer( player );
					
					alp_Insiders.Remove(i);
					continue;						
				}
				
			} else {
				alp_Insiders.Remove(i);
				continue;			
			}
			i++;
		}

		//if not occupied, clear flags
		if ( !IsOccupied() ) {
			alp_OccupiedManagement.ClearFlags();	
		}
		
		if ( changedSpawnRadiusAI  ) {
			SpawnAIdynamic ( alp_SpawnRadiusAI );		
		}
	}	
	
	
	void SetSettingOnEnter(){
	
	}
//-------------------------------------------------------------------
//***************************//
//Second spawn condition - spawn structures
//***************************//	
	
	protected bool SpawnControlPanels()
	{
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - spawning control panels");	//log	
		
		vector position;
		int index = 0;
		foreach (alpMissionAddControlPanel structure : GetTemplate().controlPanels)
		{
			EntityAI ent;	
			
			position 	= GetWorldPosition( structure.position, 0, structure.noPlaceOnSurface, structure.minH);	
			Object obj 	= GetGame().CreateObject(structure.className ,position,false,false,true);
			if ( alpUF.NoCollisionObjects(obj) &&  Class.CastTo( ent , obj ) )
			{			
				//setlifetime
				ent.SetLifetimeMax(ALP_LIFETIMEMAX);
				ent.SetLifetime(ALP_LIFETIMEMAX);
				
				ent.SetYawPitchRoll( GetWorldOrientation( structure.yaw,structure.pitch,structure.roll  ) );		
				
				if ( !structure.noPlaceOnSurface )							
					ent.PlaceOnSurface();		
						
				vector pos = ent.GetPosition();				
				if ( pos[1] < position[1] && alp_Position[1] != 0)
				{
					ent.SetPosition( position );
				} 
				
			
				

				
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CustomControlPanel,100,false, ent , structure );
				//CustomControlPanel( ent , structure );
				if (! structure.makePersist) {
					alpMissionElement e = new alpMissionElement(ent);	
					alp_Structures.Insert( e );
				} else {
					alpMissionElement e2 = new alpMissionElement(ent , true );	
					alp_Structures.Insert( e2 );				
				}
					
				
				
				
				UpdateNavmesh( ent );

				m_Hive.AddPanel(structure.className, ent.GetID(),index, ent.GetPosition(),ent.GetYawPitchRoll(),0);
			}
			else 
			{
				if ( obj )
					GetGame().ObjectDelete(obj);					
				//cancel mission spawn and info about this step
				Print("ALPMS: SpawnStructures - " + structure.className + " - " + position + " - control panels was not spawned successfully");	//log	
				return false;
			}
			index++;
		}
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - control panels spawned successfully");	//log	
		return true;
	}	
	
	void CustomControlPanel(EntityAI ent, alpMissionAddControlPanel config){
		
		alp_ServerConsole console;
		if ( config.missionTriggerSetting && config.managedMission !="" && Class.CastTo( console, ent )  ) {

			array<ref alpMission> missions;
			missions = GetND().GetMS().GetMissionByName( config.managedMission );			

			if ( missions ){
				int sharedID = -1;
				bool wasfound = false;
				foreach (alpMission mission : missions ){	
					if ( mission.GetParentID() ==  mission.GetID() ) {
						sharedID =  mission.GetID();
					}								
					if ( mission.GetParentID() == - 1 ) {
						mission.SetParentID( mission.GetID() );
						console.SetMissionManage( config, GetID() );
						console.alp_MissionManaged =  mission.GetID();
						wasfound = true;
						break;
					}			
				}
				if ( sharedID != -1 && !wasfound) {
					console.SetMissionManage( config, GetID() );
					console.alp_MissionManaged =  sharedID;
				}				
			}		
		}			
		
	}	
		
	protected bool SpawnStructures()
	{
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - spawning structures");	//log	
		
		vector position;
		int index = 0;
		foreach (alpMissionAddSpawn structure : GetTemplate().structures)
		{
			EntityAI ent;	
			
			position 	= GetWorldPosition( structure.position, 0, structure.noPlaceOnSurface, structure.minH );	
			Object obj 	= GetGame().CreateObject(structure.className ,position);
			//Object obj = GetGame().CreateObjectEx(structure.className, position, ECE_KEEPHEIGHT | ECE_NOSURFACEALIGN ); 

			if ( alpUF.NoCollisionObjects(obj) && Class.CastTo( ent , obj ) )
			{			
				//setlifetime
				ent.SetLifetimeMax(ALP_LIFETIMEMAX);
				ent.SetLifetime(ALP_LIFETIMEMAX);

				ent.SetYawPitchRoll( GetWorldOrientation( structure.yaw,structure.pitch,structure.roll  ) );		

				if ( !structure.noPlaceOnSurface ) {
					ent.PlaceOnSurface();	
				} else {	
					//vector rawpos = GetPosition() + structure.position;			
					//ent.SetPosition( rawpos );
				}
			
				vector pos = ent.GetPosition();				
				if ( !structure.noPlaceOnSurface && pos[1] < position[1] && alp_Position[1] != 0)//HOTFIX PLACEMENT
				{
					ent.SetPosition( position );
				} 
				
			
				
				if ( ent.IsKindOf("Wreck_UH1Y") )
				{
					Wreck_UH1Y uh1y = Wreck_UH1Y.Cast( ent );
					uh1y.SetMissionObjectState( true );
					uh1y.EEOnALPCreate();
				}
				
				if ( ent.IsKindOf("Wreck_Mi8") )
				{
					Wreck_Mi8 mi8 = Wreck_Mi8.Cast( ent );
					mi8.SetMissionObjectState( true );	
					mi8.EEOnALPCreate();			
				}

				if ( ent.IsKindOf("Wreck_Mi8_Crashed") )
				{
					Wreck_Mi8 mi8crashed = Wreck_Mi8.Cast( ent );
					mi8crashed.SetMissionObjectState( true );				
					mi8crashed.EEOnALPCreate();
				}
								
				
				//fireplice in building				
				BuildingWithFireplace bwf;
				if (structure.makeFire && Class.CastTo( bwf, ent ) )
				{
					SetIndoorFireplace( bwf , structure.makePersist );
				}
				
				CustomStructure( ent );
				
				if (! structure.makePersist){
					alpMissionElement e = new alpMissionElement(ent);	
					alp_Structures.Insert( e );				
				} else {
					alpMissionElement e2 = new alpMissionElement(ent, true);	
					alp_Structures.Insert( e2 );										
				}				
				
				
				UpdateNavmesh( ent );

				m_Hive.AddStructure(structure.className, ent.GetID(),index, ent.GetPosition(),ent.GetYawPitchRoll(),0);
			}
			else 
			{
				if ( obj )
					GetGame().ObjectDelete(obj);					
				//cancel mission spawn and info about this step
				Print("ALPMS: SpawnStructures - " + structure.className + " - " + position + " - structure was not spawned successfully");	//log	
				return false;
			}
			index++;
		}
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - structures spawned successfully");	//log	
		return true;
	}	
	
	void CustomStructure(EntityAI ent)
	{
		
		BuildingBase building = BuildingBase.Cast(ent);
		if ( building )
		{
			building.SetLockALP(false);	
		}	
		
	}
	
	protected void UpdateNavmesh(Object obj ){
		if ( obj.CanAffectPathgraph() ){
			GetGame().UpdatePathgraphRegionByObject( obj );		
			//GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( GetGame().UpdatePathgraphRegionByObject, 100, false, obj );		
		}		
	}	
	
	void SetIndoorFireplace( BuildingWithFireplace bwf , bool isPersist)
	{
		for (int i=0; i < 10 ; i++)
		{
			if ( bwf.HasSelection( FireplaceIndoor.FIREPOINT_PLACE_ROT +  i.ToString() ) )
			{
				
				vector fire_point_pos_world, fire_point_rot_world;
				
				if ( FireplaceIndoor.CanPlaceFireplaceInSelectedSpot( bwf , i, fire_point_pos_world, fire_point_rot_world ) )
				{
					Object obj = GetGame().CreateObjectEx( "FireplaceIndoor", fire_point_pos_world , ECE_PLACE_ON_SURFACE );	
								
					vector smoke_point_pos = bwf.GetSelectionPositionMS( FireplaceIndoor.FIREPOINT_SMOKE_POSITION +  i.ToString() );
					vector smoke_point_pos_world = bwf.ModelToWorld( smoke_point_pos );		
					
					FireplaceIndoor fp_indoor = FireplaceIndoor.Cast( obj );
					if ( fp_indoor )
					{
						int fire_point_index = FireplaceIndoor.GetFirePointIndex( FireplaceIndoor.FIREPOINT_PLACE_ROT +  i.ToString() );
						
						fp_indoor.SetFirePointIndex( fire_point_index );
						
						fp_indoor.SetSmokePointPosition( smoke_point_pos_world );		
						
						vector fprot = vector.Zero;
						fprot[0] = 0;
						fp_indoor.SetOrientation( fprot );
							
						fp_indoor.GetInventory().CreateAttachment("Firewood");	
									
						fp_indoor.GetInventory().CreateAttachment("Paper");				
						
						fp_indoor.SetMissionObjectState( true );
						
						GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(fp_indoor.StartFire,1000,false,true);
						
						fp_indoor.alp_PermaFire = true;
															
						
						
						fp_indoor.Synchronize();	
						
						if (!isPersist) {
							alpMissionElement e = new alpMissionElement(fp_indoor);	
							alp_Structures.Insert( e );						
						}																		
					}									
				}
				
		
			}					
		
		}
		
	
	}		
	
//-------------------------------------------------------------------
//***************************//
//Third spawn condition - spawn loot and loot containers
//***************************//	
	protected bool SpawnLoot(bool missionSecured = false)
	{
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - spawning loot");	//log	
		vector position;
		int index = 0;
		foreach (alpMissionAddCargo loot : GetTemplate().loot)
		{
			
			if ( loot.spawnWhenMissionIsSecured && !missionSecured  ) {
				continue;
			}
			if ( !loot.spawnWhenMissionIsSecured && missionSecured  ) {
				continue;
			}			
			
			float chance = 1;
			if ( loot.chance > 0 )
				chance = loot.chance;
			
			if ( chance >= Math.RandomFloat01() )
			{
			
				autoptr array<string> loot_types = new array<string>;
		
				string loot_source = loot.className;

				loot_source.Split(";", loot_types );
				
				if ( loot_types )
				{
					string loot_type = loot_types.GetRandomElement();
					float minH = loot.minH;

					position = GetWorldPosition(loot.position,0, false,minH);	
							
					ItemBase item;
					Object obj = GetGame().CreateObject(loot_type ,position,false,false,true);
					//Object obj = GetGame().CreateObjectEx(loot_type, position, ECE_PLACE_ON_SURFACE );
					if ( Class.CastTo( item , obj ) )
					{	
						//setlifetime
						//item.SetLifetimeMax(ALP_LIFETIMEMAX);
						//item.SetLifetime(ALP_LIFETIMEMAX);				
						
						item.SetYawPitchRoll( GetWorldOrientation(loot.yaw,loot.pitch,loot.roll  ) );

						//place on surface
						if ( alp_Position[1] == 0)
						{	
										
							item.PlaceOnSurface();	
							vector tempPos = item.GetPosition() + Vector(0,minH, 0);
							item.SetPosition( tempPos );
						}				
						
						if ( loot.positionOffset > 0 )
						{
							float xOff  = Math.RandomFloatInclusive(-1*Math.AbsFloat( loot.positionOffset ),Math.AbsFloat( loot.positionOffset) );
							float yOff  = Math.RandomFloatInclusive(-1*Math.AbsFloat( loot.positionOffset ),Math.AbsFloat( loot.positionOffset) );
								
							vector tempV = Vector( position[0] + xOff , position[1] + minH , position[2] + yOff );
							item.SetPosition( tempV );
							item.PlaceOnSurface();
						}					
					
						
						if ( item.IsItemTent() )//kontrola zda to neni stan a pripadne ho rozbalit				
							TentBase.Cast(item).Pitch ( true );
		
						item.Open();
						
						//spawn QUEST ITEM first
						if ( loot.spawnQuestItem && alp_WantedItem !="" )
						{
							item.GetInventory().CreateInInventory( alp_WantedItem );
						}
						
						
						int count = 0;
						int maxCount = loot.lootMaxCount;
						foreach (alpLootCargo cargo : loot.cargo)
						{
							
							alpLoot items = GetLoots(cargo.title);
							if (items) 
							{
								if ( SpawnCargo(item,items,cargo.chance, loot.locked) ) {
									count++; 
								};	
							}
							else
							{
								if ( SpawnEntityInCargo(item, cargo.title, cargo.chance ) ){
									count++; 
								};
								
							}
							
												
							if ( maxCount && count >= maxCount ){
								break;
							}
						}										
						//item.Close();
						CloseLoot( item );
						//Stashed
						if (loot.stashed && item.ConfigGetBool("canBeDigged") )
						{
							item = DigItem(item);	
							if ( item ) {
								Print("ALPMS: SpawnLoot - " + loot_type + " - " + position + " - loot was digged successfully");	//log
							} else {
								Print("ALPMS: SpawnLoot - " + loot_type + " - " + position + " - loot was not digged successfully");	//log
							}
						}
						
						//isFirePlace FirePlace
						if (!loot.stashed && item.IsKindOf("FireplaceBase") )
						{												
							SetFirePlace(item, loot.locked);								
						}
						
						
						
		
						//trapbase
						if (!loot.stashed && item.IsInherited(TrapBase) )
						{					
							SetTrap(item);							
						}
						
						//check loot item by mod
						SpawnLootEvent( item );
					
						//mission objects flag
						item.SetMissionObjectState( true );
						
						if ( loot.locked )
						{
							item.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT); 	
						}
						
						if (! loot.makePersist) {
							alpMissionElement e = new alpMissionElement(item);	
							alp_LootContainer.Insert( e );						
						}	else {
							alpMissionElement e2 = new alpMissionElement(item, true );	
							alp_LootContainer.Insert( e2 );														
						}					
						m_Hive.AddLoot(loot_type, item.GetID(),index, item.GetPosition(),item.GetYawPitchRoll(),0);
					}
					else 
					{
						if ( obj )
							GetGame().ObjectDelete(obj);					
						//cancel mission spawn and info about this step
						Print("ALPMS: SpawnLoot - " + loot_type + " - " + position + " - loot was not spawned successfully");	//log
						return false;
					}					
				}
				
			
		
			}
			index++;
		}
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - loot spawned successfully");	//log
		return true;
	}	
	
	void UnlockLoot(){
		int i;
		for ( i=0;i<alp_LootContainer.Count();i++)
		{
			ItemBase item = ItemBase.Cast( alp_LootContainer.Get(i).Get() );
			
			if ( item && !item.GetInventory().IsInventoryUnlocked() ) {
				item.GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);				
			}
			
		}	
		for ( i=0;i<alp_Vehicles.Count();i++)
		{
			EntityAI ent =  EntityAI.Cast( alp_Vehicles.Get(i).Get() );
			
			if ( ent && !ent.GetInventory().IsInventoryUnlocked() ) {
				if ( ent.IsInherited(	HelicopterScript ) ){
					HelicopterScript hel = HelicopterScript.Cast( ent );
					if ( hel ) {
						hel.MissionLockVehicleALP(false);
					}					
				} else if ( ent.IsInherited(	CarScript ) ) {
					CarScript car = CarScript.Cast( ent );
					if ( car ) {
						car.MissionLockVehicleALP(false);
					}						
				}						
			}
			
		}		
	}
	
	void CloseLoot(ItemBase item ) {
		item.Close();
		//item.SetSynchDirty();
	}
	
	void SpawnLootEvent(ItemBase item)
	{
#ifdef NAMALSK_TERRAIN	
		//set random smoke on Cargo Container
		alp_Misc_cargo_cont_net1 cargoCont;
				
		if ( item.GetType() == "alp_Misc_cargo_cont_net1" && Class.CastTo( cargoCont, item) /*&& GetTemplate().visualEffect */)				
		{
			cargoCont.alp_SmokeType = Math.RandomIntInclusive(1,5);			
		}
#endif 			
	}	

	void SetTrap(ItemBase item)
	{
		TrapBase trap;
		
		if ( Class.CastTo(trap, item))
		{	
			trap.SetMissionObjectState( true );
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(trap.SetActive,1000);	
		}
	}
		
	void SetFirePlace(ItemBase item, bool locked = false)
	{
		FireplaceBase fire;
		ItemBase itm;
		ItemBase pot;
		BarrelHoles_ColorBase barrel;
		if ( Class.CastTo( fire, item))
		{

			if (Class.CastTo(barrel,fire) )
			{
				barrel.Open();
			}
			

			
			
			fire.GetInventory().CreateInInventory("Firewood");					
			fire.GetInventory().CreateInInventory("Paper");
			
			if ( !barrel ) {
				itm = ItemBase.Cast( fire.GetInventory().CreateInInventory("Tripod") );			
				if ( locked )
				{
					if (itm)
					{
	
						pot = ItemBase.Cast( fire.GetInventory().CreateInInventory("Pot") );						
				
						if (pot)
						{
							pot.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
						}
						itm.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
					}
					else
					{
	
						pot = ItemBase.Cast( fire.GetInventory().CreateInInventory("Pot") );		
	
						if (pot)
						{
							pot.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
						}
					}
				}
				else
				{
					if (itm)
					{
	
						pot = ItemBase.Cast( fire.GetInventory().CreateInInventory("Pot") );			
		
	
					}
					else
					{
	
						pot = ItemBase.Cast( fire.GetInventory().CreateInInventory("Pot") );		
	
						if (pot)
						{
							
							pot.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
	
						}
					}			
				
				}
				
				if (pot)
				{
					fire.SetCookingEquipment( pot );
					
				}			
			} 
			
			

			fire.RefreshFireplacePhysics();
			fire.RefreshFireplaceVisuals();
			

			fire.GetInventory().CreateInInventory("Rag");
			fire.GetInventory().CreateInInventory("Bark_Oak");
			fire.GetInventory().CreateInInventory("WoodenStick");				
				
			
			
					
			//fire.SetSynchDirty();
			
			fire.SetMissionObjectState( true );
			fire.alp_PermaFire = true;
			
			Object cc_object = GetGame().CreateObjectEx( "ClutterCutterFireplace" , fire.GetPosition(), ECE_PLACE_ON_SURFACE );
			cc_object.SetOrientation ( fire.GetOrientation() );
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( g_Game.ObjectDelete, 12000, false, cc_object );			
			
			
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(fire.StartFire,10000,false,true);
			
			if ( barrel ) {
			//barrel.Open();
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CloseLoot,15000,false,barrel);
			}
		}
	}	
	
	ItemBase DigItem(ItemBase item)
	{
		InventoryLocation target_IL = new InventoryLocation;
		if (!item.GetInventory().GetCurrentInventoryLocation(target_IL))
		{
			return item;
		}		
		
		ItemBase stashed_item;		
		UndergroundStash stash;
		vector pos = item.GetPosition();	
		
		Class.CastTo(stashed_item,  item );
		
		if ( Class.CastTo(stash,  GetGame().CreateObjectEx("UndergroundStash", pos, ECE_PLACE_ON_SURFACE) ) )		
		{
			stash.PlaceOnGround();			
			item.ServerTakeEntityToTargetCargo(stash,item);
			
			stash.SetMissionObjectState( true );
			return stash;
		}
		return item;
	}
	protected void RespawnLoot()
	{		
		for (int i=0;i<alp_LootContainer.Count();i++)
		{
			ItemBase item = ItemBase.Cast( alp_LootContainer.Get(i).Get() );
			if ( item ) {
				bool open = item.IsOpen();
				
				if (!open) 
					item.Open();
				
				if ( item.IsMissionObject() )//respawn mission loot only if is still mission object
				{
					alpUF.RemoveAllItems( item );		
					

					//spawn QUEST ITEM first
					if ( GetTemplate().loot.Get(i) )
					{
						if ( GetTemplate().loot.Get(i).spawnQuestItem && alp_WantedItem !="" )
						{
							item.GetInventory().CreateInInventory( alp_WantedItem );
						}						
					
					}				
						
					//array<ref alpLootCargo> lootCargo = GetTemplate().loot.Get(i).cargo;			
					int count = 0;
					int maxCount = GetTemplate().loot.Get(i).lootMaxCount;									
					foreach (alpLootCargo cargo : GetTemplate().loot.Get(i).cargo)
					{									
						alpLoot loot = GetLoots(cargo.title);

						
						if (loot) 
						{
							if (SpawnCargo(item,loot,cargo.chance) ){
								count++; 
							}
						}
						else
						{
							if (SpawnEntityInCargo(item, cargo.title, cargo.chance )){
								count++; 
							};
							
						}		
																		
						if ( maxCount && count >= maxCount ){
							break;
						}																			
					}				
				}	
				
				if (!open)	
					item.Close();				
			}
		}							
	}
//-------------------------------------------------------------------
//***************************//
//Fourth spawn condition - spawn vehicles
//***************************//		
	protected bool SpawnVehicles(bool missionSecured = false)
	{
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - spawning vehicles");	//log	

		Transport		transport;	
		alpVehicles 	vehicle;
		vector 			position;
		TStringArray 	classNames;
		int index = 0;
		foreach (alpMissionAddVehicle vehicles : GetTemplate().vehicles)
		{
			if ( vehicles.spawnWhenMissionIsSecured && !missionSecured  ) {
				continue;
			}
			if ( !vehicles.spawnWhenMissionIsSecured && missionSecured  ) {
				continue;
			}				
			
			vehicle 		= GetVehicles(vehicles.title);
			classNames 		= vehicle.items.Get( vehicle.items.GetRandomIndex() );
			
			float chance 	= vehicles.chance;
			
			if (chance==0) 
				chance = vehicle.chance;
			
			if (Math.RandomFloat01() > chance) 
				continue;
			
			position 		= GetWorldPosition( vehicles.position );	
			Object obj 		= GetGame().CreateObject( classNames.Get(0) ,position,false,false,true);

		
			
			if ( Class.CastTo( transport , obj ) )
			{
				transport.SetYawPitchRoll( GetWorldOrientation(vehicles.yaw,vehicles.pitch,vehicles.roll  ) );	
				
				for (int i = 1; i < classNames.Count();i++)
				{//attachments
					if (Math.RandomFloat01() <= vehicle.chanceAttachments)
					{
						transport.GetInventory().CreateAttachment(classNames.Get(i));
					}
				}				
				 
				alpUF.FillFluidsToVehicle(transport , (Math.RandomFloat01() <= vehicle.chanceFluid), true,vehicle.minFuelAmount,vehicle.maxFuelAmount );//fill fluids
				int count = 0;
				int maxCount = vehicle.lootMaxCount;				
				foreach (alpLootCargo cargo : vehicle.cargo)
				{//cargo
					alpLoot loots = GetLoots(cargo.title);
					if (loots) 
					{
						if ( SpawnCargo(transport,loots,cargo.chance)){
							count++; 	
						};	
					}				
					else
					{
						if ( SpawnEntityInCargo(transport, cargo.title, cargo.chance ) ){
							count++; 
						};
					}	
																	
					if ( maxCount && count >= maxCount ){
						break;
					}											
				}
				//lock vehicle
				if ( vehicle.locked ) {
					if ( transport.IsInherited(	HelicopterScript ) ){
						HelicopterScript hel = HelicopterScript.Cast( transport );
						if ( hel ) {
							hel.MissionLockVehicleALP(true);
						}					
					} else if ( transport.IsInherited(	CarScript ) ) {
						CarScript car = CarScript.Cast( transport );
						if ( car ) {
							car.MissionLockVehicleALP(true);
						}						
					}
				}								
				
				transport.SetLifetimeMax(ALP_LIFETIMEMAX);//  3888000 ALP_LIFETIMEMAX
				transport.SetLifetime(ALP_LIFETIMEMAX);//  3888000 ALP_LIFETIMEMAX
				
				if (! vehicles.makePersist) {
					alpMissionElement e = new alpMissionElement(transport);	
					alp_Vehicles.Insert( e );				
				} else {
					alpMissionElement e2 = new alpMissionElement(transport);	
					alp_Vehicles.Insert( e2 );							
				}
				
				m_Hive.AddCar(classNames.Get(0), transport.GetID(),index, transport.GetPosition(),transport.GetYawPitchRoll(),0);				
			}	
			else 
			{
				if ( obj )
					GetGame().ObjectDelete(obj);		
				
				Print("ALPMS: SpawnVehicles - " + classNames.Get(0) + " - " + position + " - vehicle was not spawned successfully");	//log					
				return false;				
			}	
			index++;							
		}
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - vehicles spawned successfully");	//log
		return true;
	}	
	
	
//-------------------------------------------------------------------
//***************************//
//Fifth spawn condition - spawn NPC
//***************************//	
	protected void PostponeSpawnNPC(alpMissionAddNPC npc, int index, bool isDynamic = false )
	{
		vector 				position;	
		position = GetWorldPosition(npc.position);	

		vector ori;
		Object obj = GetGame().CreateObject(npc.className ,position,false,false,true);

		Man man;
		if ( Class.CastTo(man,obj))
		{
			//man.EEInit();
			//man.EEInitALP();
			
			
			ori = GetWorldOrientation(npc.yaw,npc.pitch,npc.roll  );
			man.SetYawPitchRoll( ori );	
			man.SetOrientation( ori );
			
			man.PlaceOnSurface();
			vector pos2 = man.GetPosition();
			
			if ( pos2[1] < position[1] )
			{
				man.SetPosition( position );
			} 					
			
			//man.SetAllowDamage( !GetTemplate().godmodTrader );
			
			foreach (string att2 : npc.attachments) //wearing up
			{
				man.GetInventory().CreateInInventory(att2);
			}	
			//cargo
			int count = 0;
			int maxCount = npc.lootMaxCount;			
			foreach (alpLootCargo cargoMan : npc.cargo)
			{
				alpLoot lootMan = GetLoots(cargoMan.title);
				
				if (lootMan) 
				{
					if ( SpawnCargo(man,lootMan,cargoMan.chance) ) {
						count++; 
					};
				}			
				else
				{
					if ( SpawnEntityInCargo(man, cargoMan.title, cargoMan.chance )){
						count++; 
					};
				}	
																
				if ( maxCount && count >= maxCount ){
					break;
				}								
			}						
			//unlock item										
																
			
			if ( npc.IsDead /*&& !npc.StockID */){
				int timeToDeath = npc.IsDead * 1000;
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(man.DecreaseHealth, timeToDeath, false, STRING_EMPTY , STRING_EMPTY ,1000); 
			} else {
				if ( isDynamic ) {
					m_Hive.AddNpcDynamic(npc.className, man.GetID(),index, man.GetPosition(),man.GetYawPitchRoll(),0);	
				} else {
					m_Hive.AddNpc(npc.className, man.GetID(),index, man.GetPosition(),man.GetYawPitchRoll(),0);	
				}
								
			}
				

			SetUpNPC(man,npc );						
			
			man.SetSynchDirty();
			alpMissionElement e = new alpMissionElement(man);	
			alp_NPC.Insert( e );			
		}
		else 
		{
		
			if ( obj )
				GetGame().ObjectDelete(obj);	
			
			Print("ALPMS: SpawnNPC - " + npc.className + " - " + position + " - NPC wasn't spawned successfully");	//log	
			
		}		
	}	
	
	protected void SpawnNPCdynamic()
	{
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - spawning dynamic NPC");	//log					
		int offset = 500;
		int index = 0;
		foreach (alpMissionAddNPC npc : GetTemplate().NPCdynamic)	
		{
			
			if (npc.chance && npc.chance < Math.RandomFloat01() )
			{
				continue;
			}			
		
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.PostponeSpawnNPC,offset,false,npc,index,true);
			offset+=500;
			index++;
		}
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.AllNPCspawned, offset);
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - dynamic NPC spawned successfully");	//log	

	}		
	
	
	protected bool SpawnNPC()
	{
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - spawning NPC");	//log					
		int offset = 500;
		int index = 0;
		foreach (alpMissionAddNPC npc : GetTemplate().NPC)	
		{
			
			if (npc.chance && npc.chance < Math.RandomFloat01() )
			{
				continue;
			}			
		
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.PostponeSpawnNPC,offset,false,npc,index,false);
			offset+=500;
			index++;
		}
		
		if ( !GetTemplate().NPCdynamic.Count() ) {		
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.AllNPCspawned, offset);
		}
		
		
		
		Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - NPC spawned successfully");	//log	
		return true;
	}	
	
	void AllNPCspawned(){
		alp_AllNPCspawned = true;
	}

	void SetUpNPC(Man npc, alpMissionAddNPC template)
	{
		PlayerBase player;
		if ( Class.CastTo( player, npc ) ) {	
			int stance = template.stance;
			if ( !IsCleared() && ( alp_Type == ALP_MISSIONTYPEID.savesurvivors ||  alp_Type == ALP_MISSIONTYPEID.savemerchants ) ) {
				stance = Math.RandomInt(1,2);	
			}			
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(player.ForceStanceALP,1000,false,stance);	
		}
		
		alpNPC trader = alpNPC.Cast( npc );
		if ( trader ) {
			trader.m_AllowedQuestsAtOnce = template.AllowedQuestsAtOnce;
			trader.m_CurrencyFromMissionTemplate = template.CurrencyID;
		}
		
		if ( template.missionTriggerSetting && template.managedMission !="" && trader  ) {

			array<ref alpMission> missions;
			missions = GetND().GetMS().GetMissionByName( template.managedMission );			

			if ( missions ){
				int sharedID = -1;
				bool wasfound = false;
				foreach (alpMission mission : missions ){	
					if ( mission.GetParentID() ==  mission.GetID() ) {
						sharedID =  mission.GetID();
					}			
					if ( mission.GetParentID() == - 1 ) {
						mission.SetParentID( mission.GetID() );
						GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(trader.SetMissionManage,100,false, template , GetID() );
						//trader.SetMissionManage( template , GetID() );
						trader.alp_MissionManaged =  mission.GetID();
						wasfound = true;
						break;
					}			
				}
				if ( sharedID != -1 && !wasfound ) {
					//trader.SetMissionManage( template , GetID() );
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(trader.SetMissionManage,100,false, template , GetID() );
					trader.alp_MissionManaged =  sharedID;
				}
			}		
		}	
	}
	
	void HandleDeathNPC(Man man)
	{
		if (man )
		{	
			man.SetCanBeDestroyed(false);
		}
	}	
	

//-------------------------------------------------------------------
//***************************//
//Sixth spawn condition - spawn TOXIC ZONE
//***************************//	
	protected void SpawnDynamicToxicZone()
	{
		if ( alp_ContaminedAreasDynamic && alp_ContaminedAreasDynamic.Count() > 0 )
		{
			for (int i = 0; i < alp_ContaminedAreasDynamic.Count(); i++ )
			{
				JsonDataContaminatedArea_ALP area = alp_ContaminedAreasDynamic.Get(i).Area;
								
				int delay = alp_ContaminedAreasDynamic.Get(i).timeOffset * 1000;
				
				int positionOffset = alp_ContaminedAreasDynamic.Get(i).positionOffset;
				
				float chance = alp_ContaminedAreasDynamic.Get(i).chance;
				
				if (chance && chance < Math.RandomFloat01() )
				{
					continue;
				}
	
				//create radiation as well
				if ( GetTemplate().radiationSpawnedByContaminedArea )
				{
					int time = GetTemplate().radiationDynamic;
					time *= 1000;		
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetSetting,time,false, alpMISSION_SETTING.RADIATION_ACTIVE);					
				}				

				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CreateToxicZone, delay, false, area,positionOffset,i,true );

			
			}
			
		
		}
	
	}		
	
	protected bool SpawnToxicZone()
	{
		if ( alp_ContaminedAreas && alp_ContaminedAreas.Count() > 0 )
		{
			Print("SPAWNING TOXIC ZONES");
			for (int i = 0; i < alp_ContaminedAreas.Count(); i++ )
			{
				JsonDataContaminatedArea_ALP area = alp_ContaminedAreas.Get(i).Area;
								
				int delay = alp_ContaminedAreas.Get(i).timeOffset * 1000;
				
				int positionOffset = alp_ContaminedAreas.Get(i).positionOffset;
				
				float chance = alp_ContaminedAreas.Get(i).chance;
				
				if (chance && chance < Math.RandomFloat01() )
				{
					continue;
				}
	
				//create radiation as well
				if ( GetTemplate().radiationSpawnedByContaminedArea )
				{
					int time = GetTemplate().radiationDynamic;
					time *= 1000;		
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetSetting,time,false, alpMISSION_SETTING.RADIATION_ACTIVE);					
				}

				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CreateToxicZone, delay, false, area,positionOffset,i,false );

			
			}
			
		
			return true;
		}
		//Print("ERROR IN SPAWNING TOXIC ZONE");
		return true;		
	}	
	void CreateToxicZone(JsonDataContaminatedArea_ALP area, int posOffset, int index, bool isDynamic )
	{
		if (area)
		{
			vector position = {area.Data.Pos[0],area.Data.Pos[1],area.Data.Pos[2] };
			
			position 	= GetWorldPosition(position , posOffset);	
			
			//array<float> pos = { position[0], position[1], position[2]  };
			
				
			Print("ALPMS: mission " + GetName() + " - " + position + " - spawning toxic zone");	//log			
	
			EffectArea toxicZone;
			
			if ( position[1] == 0 )
			{
				position[1] = GetGame().SurfaceRoadY( position[0], position[2] );
				
				Class.CastTo( toxicZone, GetGame().CreateObjectEx( area.Type, position, ECE_PLACE_ON_SURFACE ) );
			}
			else
				Class.CastTo( toxicZone, GetGame().CreateObjectEx( area.Type , position, ECE_NONE ) );			
	
			
			if ( toxicZone )
			{
				toxicZone.SetupZoneData(  GetSetupForToxicZone(area)  );
				
				if ( area.Type == "ContaminatedArea_Dynamic" )
				{	
					toxicZone.SetLifetimeMax( GetTemplate().lifeTime );
					toxicZone.SetLifetime( GetTemplate().lifeTime );
															
				} else {
					toxicZone.SetLifetimeMax( ECE_NOLIFETIME );
					toxicZone.SetLifetime( ECE_NOLIFETIME );								
				}
				
				alpMissionElement e = new alpMissionElement(toxicZone);	
				alp_ToxicZones.Insert( e );					
				
				if ( isDynamic ) {
					m_Hive.AddAreaDynamic(area.Type, toxicZone.GetID(),index, toxicZone.GetPosition(),toxicZone.GetYawPitchRoll(),0);	
				} else {
					m_Hive.AddArea(area.Type, toxicZone.GetID(),index, toxicZone.GetPosition(),toxicZone.GetYawPitchRoll(),0);	
				}
				
				Print("ALPMS: mission " + GetName() + " - " + position + " - toxic zone spawned successfully");	//log	
			}
			else
			{
				Print("ERROR IN SPAWNING TOXIC ZONE");
						
			}	
		}		
	}

	EffectAreaParams GetSetupForToxicZone(JsonDataContaminatedArea_ALP area)
	{
		
		EffectAreaParams params = new EffectAreaParams();

		
		// We feed in all relevant data
		params.m_ParamName =area.AreaName;
		string areaType = area.Type;
		params.m_ParamTriggerType = area.TriggerType;
		JsonDataAreaDataALP data = area.Data;
		
		// World level area data ( Trigger info, world particles, etc... )

		params.m_ParamRadius = data.Radius;
		params.m_ParamPosHeight = data.PosHeight;
		params.m_ParamNegHeight = data.NegHeight;
		params.m_ParamInnerRings = data.InnerRingCount;
		params.m_ParamInnerSpace = data.InnerPartDist;
		params.m_ParamOuterToggle = data.OuterRingToggle;
		params.m_ParamOuterSpace = data.OuterPartDist;
		params.m_ParamOuterOffset = data.OuterOffset;
		params.m_ParamVertLayers = data.VerticalLayers;
		params.m_ParamVerticalOffset = data.VerticalOffset;
		string particleName = data.ParticleName;
		
		// Local level area data ( Player particles and PPE )
		JsonDataPlayerDataALP playerData = area.PlayerData;
		string aroundPartName = playerData.AroundPartName;
		string tinyPartName = playerData.TinyPartName;
		string ppeRequesterType = playerData.PPERequesterType;
		
		// Conversion of particle name to ID for synchronization and loading
		params.m_ParamPartId = ParticleList.GetParticleID( particleName );
		params.m_ParamAroundPartId = ParticleList.GetParticleID( aroundPartName );
		params.m_ParamTinyPartId = ParticleList.GetParticleID( tinyPartName );
		params.m_ParamPpeRequesterType = ppeRequesterType;			
		
		return params;
		
		
	}	

		
//-------------------------------------------------------------------
//***************************//
//Spawning mission AI
//***************************//		
	protected void PostponeSpawnAI(alpMissionAI ai)
	{
		EntityAI ent;
		vector position = GetWorldPosition( ai.position, ai.radius );

		//select ai
		
		
		
		autoptr array<string> creatures = new array<string>;
		
		string sourceAI = ai.className;
		
				
		sourceAI.Split(";", creatures );
		
		if ( creatures )
		{
			string creature = creatures.GetRandomElement();
			
			int flags = ECE_SETUP|ECE_PLACE_ON_SURFACE | ECE_INITAI|ECE_CREATEPHYSICS;
			
			//if ( Class.CastTo( ent , GetGame().CreateObject( creature, position, false, true, true ) ) )
			if ( Class.CastTo( ent , GetGame().CreateObjectEx( creature, position, flags ) ) )
			{
				
				//ent.PlaceOnSurface();
				vector pos2 = ent.GetPosition();
			
				if ( pos2[1] < position[1] )
				{
					ent.SetPosition( position );
				} 							
				int count = 0;
				int maxCount = ai.lootMaxCount;				
				foreach (alpLootCargo cargo : ai.cargo)
				{
					alpLoot loot = GetLoots(cargo.title);
					if (loot) 
					{
						if ( SpawnCargo(ent,loot,cargo.chance) ){
							count++; 
						};
					}
					else
					{
						if ( SpawnEntityInCargo(ent, cargo.title, cargo.chance )){
							count++; 
						};
					}													
					if ( maxCount && count >= maxCount ){
						break;
					}									
				}
				if (ai.type == "dynamic")
				{
					
					alp_DynamicAI.Insert ( ent );	
				}
				else
				{

					alp_StaticAI.Insert ( ent );						
				}				
				SetUnsecured();
				if ( m_SetUpNotAvailableAI ) {//flag HOTFIX
					m_SetUpNotAvailableAI = false;
					alp_AvailableDynamicAI = false;
				}
			}
			else
			{
			
				if (ai.type == "dynamic")
				{
					
					alp_CountAI_dynamic--;	
				}
				else
				{

					alp_CountAI_static--;						
				}			
			}		
	
		}
		
		

	
	}
	protected void SpawnAIstatic(string typAI = "static" )
	{
		alp_AvailableStaticInRestockAI = false;
		
		int offset = 0;

		int i;
		foreach (alpMissionAI ai:  alp_MissionAI)
		{
			if (ai.type == typAI && ai.restock >=0  )
			{	
				ai.restock -=1;
				if ( ai.restock >= 0 ) {
					alp_AvailableStaticInRestockAI = true;
				}				
				
				if (ai.chance && ai.chance < Math.RandomFloat01() )
				{
					continue;
				}
				
				int count = Math.RandomIntInclusive(ai.nominal.Get(0),ai.nominal.Get(1));						
				
				for (i=0;i<count;i++)
				{	
					alp_CountAI_static++;					
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.PostponeSpawnAI,offset,false,ai);
					offset+=100;
				}
			}
		}
		alp_SpawnedStaticAI = true;			
		
	}
	bool m_SetUpNotAvailableAI;
	protected void SpawnAIdynamic(int spawnRadius){	
		bool availableAI;
		bool availableRestockAI;
		int offset = 0;

		int i;
		foreach (alpMissionAI ai:  alp_MissionAI)
		{
			if ( !ai.spawned && ai.type == "dynamic" && ai.restock >=0  && ( ai.spawnRadius >= spawnRadius || ai.spawnRadius == 0 ) )
			{	
				ai.restock -=1;
								
				ai.spawned=true;

				if (ai.chance && ai.chance < Math.RandomFloat01() )
				{
					continue;
				}								
				
				int count = Math.RandomIntInclusive(ai.nominal.Get(0),ai.nominal.Get(1));						
				
				for (i =0;i<count;i++)
				{	
					alp_CountAI_dynamic++;
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.PostponeSpawnAI,offset,false,ai);
					offset+=100;			
				}
			}
			else
			{
				if ( !ai.spawned && ai.type == "dynamic" && ai.restock >=0 )
				{
					availableAI	= true;
				}
			}
			
			if ( ai.restock >= 0 ) {				
				availableRestockAI = true;
			}			
		}
		
		if (!availableAI) {
			//alp_AvailableDynamicAI = false; 			
			m_SetUpNotAvailableAI = true;
			
		}
		
		if ( availableRestockAI ){
			alp_AvailableDynamicInRestockAI = true;
		} else {
			alp_AvailableDynamicInRestockAI = false;
		}
		
	}			
	
	
	private void CheckStaticAI(){
		int i;
		//static AI	
		for (i=0;i<alp_StaticAI.Count();)
		{			
			if ( alp_StaticAI.Get(i) ) 
			{
				if ( !alp_StaticAI.Get(i).IsAlive() ) 
				{
					if ( GetND().GetMS().GetOptions().DeleteDeadMissionAI && IsAreaClear() )
					{
						GetGame().ObjectDelete(alp_StaticAI.Get(i));
					}	
					alp_CountAI_dead_static++;			
					alp_StaticAI.Remove(i);
					continue;					
				}
			}	
			else
			{
				alp_CountAI_dead_static++;								
				alp_StaticAI.Remove(i);
				continue;	
			}
			i++;
		}		
	}
	
	private void CheckDynamicAI(){
		int i;
		//dynamic AI	
		for (i=0;i<alp_DynamicAI.Count();)
		{			
			if ( alp_DynamicAI.Get(i) ) 
			{
				if ( !alp_DynamicAI.Get(i).IsAlive() ) 
				{
					if ( GetND().GetMS().GetOptions().DeleteDeadMissionAI && IsAreaClear() )
					{
						GetGame().ObjectDelete(alp_DynamicAI.Get(i));
					}		
					alp_CountAI_dead_dynamic++;		
					alp_DynamicAI.Remove(i);
					continue;									
				}
				else {	
					
					if ( IsAreaClear() ){	
						GetGame().ObjectDelete(alp_DynamicAI.Get(i));
						alp_DynamicAI.Remove(i);
						continue;	
					}		
					
				}
			}	
			else
			{
				alp_CountAI_dead_dynamic++;	
				alp_DynamicAI.Remove(i);
				continue;	
			}
			i++;
		}			
	}
	
	private void CheckAI()
	{
		
		
		CheckStaticAI();
		CheckDynamicAI();

		int count_Spawned = alp_CountAI_static + alp_CountAI_dynamic;
		int count_dead = alp_CountAI_dead_static + alp_CountAI_dead_dynamic;
		alp_Count_ALL_AI = count_Spawned - count_dead;		
		
		int toleration = (int) ( GetND().GetMS().GetOptions().AllowedRatioAliveMissionAI * count_Spawned );
	
		alp_Count_ALL_AI -= toleration;		
		if ( ( alp_Count_ALL_AI <= 0 && !IsAvailableRestockAI()  ) ) { //cleared						
			SetCleared();					
		} else if ( ( alp_Count_ALL_AI <= 0 && IsAvailableRestockAI() && GetTemplate().aiReinforcement ) || ( alp_Count_ALL_AI > 0 && IsAreaClear() ) ) {//restock and reinforcment AI
			
			foreach (alpMissionAI ai :  alp_MissionAI){
				if ( ai.spawned ) {					
					if ( alp_Count_ALL_AI > 0 && IsAreaClear() ){
						ai.restock +=1;	
						alp_AvailableDynamicInRestockAI	= true;	
						ai.spawned=false;						
					}		
					if (ai.restock >= 0 && alp_Count_ALL_AI <= 0 ){
						alp_AvailableDynamicInRestockAI	= true;	
						ai.spawned=false;
					}					
				}
				//ai.spawned=false;	
			}	
			if ( alp_AvailableDynamicInRestockAI ) {
				alp_SpawnRadiusAI		= 1000;
				alp_AvailableDynamicAI	= true;				
			}
			
			if ( GetTemplate().aiReinforcement && alp_AvailableStaticInRestockAI && !IsAreaClear() ) {//static AI
				alp_SpawnedStaticAI	= false;
				SpawnAIstatic();	
			}	
		}
		
		if (  IsAreaClear() ) {
			alp_CountAI_dynamic = 0;
			alp_CountAI_dead_dynamic = 0;
			if ( alp_AvailableStaticInRestockAI ){
				alp_SpawnedStaticAI	= false;
			}			
		}
		
	}	

//-------------------------------------------------------------------
//***************************//
//Despawning mision methods
//***************************//	

	override void DespawnMission()
	{		
		
		Print("ALPMS: despawning mission " + GetName() + " - " + GetPosition());	//log	
		
		alp_Active = false;

		DespawnMissionObjects();
		
		CleanUp();
	
		if ( GetTemplate().sendInfo && GetTemplate().endMessage != "" )
		{
			GetND().GetNotf().SendMissionMessage(  alp_SendInfoEnd	,GetID(), GetTemplate().endMessage, GetPosition(), null , true);
		}					
		
		GetND().GetMS().SendRPC_Update( this );//update data to clients
		
		RespawnMission( GetMissionRespawnTime() );	
		
		//event on misison despawn
		int delay = GetTemplate().postponeEventOnEnd * 1000;
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.EventOnEnd, delay);

		//change group count			
		GetND().GetMS().ChangeGroupLimit( GetTemplate().missionGroup,-1);			
		
		alpMHIVE.UnRegisterMission( GetID() );
			
	}	
	
	protected void DespawnMissionObjects()
	{
		DeleteAI();
		DeleteStructures();
		DeleteNPC();
		DeleteLoot();
		DeleteVehicles();	
		DeleteToxicZones();
	}
	
	private void DeleteAI()
	{
		int i;

		for (i=0;i < alp_StaticAI.Count();i++)
		{
			if (alp_StaticAI.Get(i))
			{
				if ( alp_StaticAI.Get(i).IsAlive() )
				{
					if ( GetND().GetMS().GetOptions().DeleteAliveMissionAI )
					{	
						GetGame().ObjectDelete(alp_StaticAI.Get(i));
					}						
				}
				else
				{
					if ( GetND().GetMS().GetOptions().DeleteDeadMissionAI )
					{	
						GetGame().ObjectDelete(alp_StaticAI.Get(i));
					}
				}					
				
			}					
								
		}
		alp_StaticAI.Clear();
		
		for (i=0;i < alp_DynamicAI.Count();i++)
		{
			if (alp_DynamicAI.Get(i))
			{
				if ( alp_DynamicAI.Get(i).IsAlive() )
				{
					if ( GetND().GetMS().GetOptions().DeleteAliveMissionAI )
					{	
						GetGame().ObjectDelete(alp_DynamicAI.Get(i));
					}						
				}
				else
				{
					if ( GetND().GetMS().GetOptions().DeleteDeadMissionAI )
					{	
						GetGame().ObjectDelete(alp_DynamicAI.Get(i));
					}
				}					
				
			}					
								
		}
		alp_DynamicAI.Clear();
		
		foreach (alpMissionAI ai:  alp_MissionAI)//refresh default AI numbers
		{
			ai.Refresh();
		}			
	}
	
	private void DeleteToxicZones()
	{
		if ( alp_ToxicZones )
		{
			foreach(alpMissionElement e : alp_ToxicZones){
				if ( e.Get() ){
					GetGame().ObjectDelete( e.Get() );	
				}				
			}		
			alp_ToxicZones.Clear();			
		}
		
		
	}
	
	
	private void DeleteStructures()
	{	
		foreach(alpMissionElement e : alp_Structures)
		{
			if ( e.Get() &&  !e.IsPersist() ){
				GetGame().ObjectDelete( e.Get() );	
			}
		}
		alp_Structures.Clear();		
	}
	
	private void DeleteNPC()
	{		
		//NPC
		foreach(alpMissionElement e : alp_NPC)
		{
			if ( e.Get() ){
				GetGame().ObjectDelete( e.Get() );	
			}
		}
		alp_NPC.Clear();
	}

	private void DeleteLoot()
	{
		foreach (alpMissionElement e : alp_LootContainer)
		{
			if ( e.Get() &&  !e.IsPersist() ){
				ItemBase itm = ItemBase.Cast( e.Get() );
				if (itm && itm.IsMissionObject() ) //mission objects will be deleted only
					GetGame().ObjectDelete(itm);				
			}					

		}
		alp_LootContainer.Clear();
	}	
	
	private void DeleteVehicles()
	{
		foreach (alpMissionElement e : alp_Vehicles){		
			if ( e.Get() &&  !e.IsPersist() ){			
				CarScript car;
				if ( Class.CastTo( car, e.Get()) )
				{
					if (car.IsMissionObject())//mission objects will be deleted only
						GetGame().ObjectDelete(car);	
				}	
				HelicopterScript heli;
				if ( Class.CastTo( heli, e.Get()) )
				{
					if (heli.IsMissionObject() )//mission objects will be deleted only
						GetGame().ObjectDelete(heli);	
				}				
			}
						
		}
		alp_Vehicles.Clear();
	}	
	
	
//-------------------------------------------------------------------
//***************************//
//usefull class methods mision methods
//***************************//	
	protected void ShowPlayerName(PlayerBase player,float distance) {
		//SetSetting( alpMISSION_SETTING.MISSION_STARTED );	
		string name;				
		if ( GetND().GetMS().GetOptions().ShowRealPlayerName ) {
			name = player.GetIdentity().GetName();	
		} else {
			name = player.GetDisplayName();
		}
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( GetND().GetNotf().SendMissionMessage, 3000, false, ALPMSTYPE.MMPERSONAL	, GetID(), name + " #alp_startedmission #pos", GetPosition(), null, true );
		
		//GetND().GetNotf().SendMissionMessage( ALPMSTYPE.MMPERSONAL	, GetID(), name + " #alp_startedmission #pos", GetPosition(), null, true );	
		

	};
	

	
	protected void InteractionOnInsiders(Object obj,float distance) {};

	protected void OnEnter(Object obj ){
		
		RemoveSetting( alpMISSION_SETTING.MISSION_IDLE );	
		
		if (obj.IsMan() && GetTemplate().alertInfo && GetTemplate().alertMessageIn != "")
		{
			GetND().GetNotf().SendMissionMessage( alp_AlertInfoIn	,GetID(),  GetTemplate().alertMessageIn, GetPosition() , PlayerBase.Cast( obj) );	
		}
					
	};
	

	protected void OnLeave(Object obj )
	{
		if (obj.IsMan() && GetTemplate().alertInfo && GetTemplate().alertMessageOut != "")
		{
			GetND().GetNotf().SendMissionMessage(  alp_AlertInfoOut	,GetID(), GetTemplate().alertMessageOut, GetPosition() , PlayerBase.Cast( obj) );
		}
		
	};

	void CleanUp()
	{
		for(int n = 0; n < alp_Insiders.Count(); n++)
		{
			alpMissionInsider ins = alp_Insiders.Get(n);	
			if( ins.GetObject() )
			{
				OnLeave(ins.GetObject() );
			}			
		}
		alp_Insiders.Clear();
	}		



	vector GetWorldOrientation(float yaw, float pitch, float roll)
	{
		vector ori = GetAngle();
					
		ori[0]= yaw + ori[0];
		ori[1]= pitch + ori[1];
		ori[2]= roll + ori[2];
		
		ori = ori.GetRelAngles();
		
		return ori;
	}
	
	vector GetWorldPosition(vector bod, int radius = 0, bool noPlaceOnSurface = false, float minH = 0)
	{
		vector position;
		
	
		position = CorrectPosition(bod, GetAngle() );
		position = GetPosition() + position;

		position = RandomPosition(position[0],position[1],position[2],radius, noPlaceOnSurface, minH,  alp_MinH);	
		
		return position;
	}
	
	protected vector CorrectPosition( vector bod, vector ori)
	{
		float yaw = ori[0];
		
		vector v;
		float len;
		len = bod.Normalize();				
		v = bod.VectorToAngles();
		v[0] = Math.NormalizeAngle( v[0]+yaw);
		v = v.AnglesToVector();	
		v[0] = v[0] *len;
		v[1] = v[1] *len;
		v[2] = v[2] *len;
		return v;
	}
	
	static vector RandomPosition (float x, float h, float y, int radius, bool noPlaceOnSurface = false, float minH = 0, float minMissionH = 0)
    {
        vector pos = vector.Zero;
		float verH;
		x = x + Math.RandomIntInclusive(-1*Math.AbsInt(radius),Math.AbsInt(radius));
		y = y + Math.RandomIntInclusive(-1*Math.AbsInt(radius),Math.AbsInt(radius));
		
		verH = GetGame().SurfaceY(x,y)+ minMissionH;
		if ( !noPlaceOnSurface && h < (verH-minH) ){
			h = verH + minH;
		}
		
				
        pos[0] = x;
		pos[1] = h;
        pos[2] = y;
        return pos;
    }

	
	static bool SpawnEntityInCargo(Object obj, string name, float chance = 1 )
	{
		if ( chance !=1 && chance < Math.RandomFloat01() )
			return false;
		
		
		EntityAI 		ent 		= EntityAI.Cast(obj);
		
		if ( ent  )
		{
			ent.GetInventory().CreateInInventory(name);
			return true;
		}
		return false;
	}
	
	
	
	static bool SpawnCargo(Object obj,alpLoot loots, float chance=0, bool locked = false)
	{
		if ( !loots || !loots.items || !loots.items.Count() )
		{
			return false;
		}
		
		if (chance==0) chance = loots.chance;
		if (Math.RandomFloat01() > chance) return false;	

		EntityAI 		ent 		= EntityAI.Cast(obj);
		EntityAI		newItem;
		if (!ent)
			return false;
		
		string 			className;
		TStringArray 	classNames;
		Weapon_Base		wep;
		int i, quantity;
		float quantityFloat;		

		switch(loots.type)
		{
			case "items":
			{
				className = loots.items.Get(loots.items.GetRandomIndex()).GetRandomElement();
				newItem = ent.GetInventory().CreateInInventory(className);
				if ( newItem && ent.IsKindOf("CarScript") && newItem.GetType() == "alp_CarKey")
				{
					CarScript car;
					alp_CarKey key;
					if ( Class.CastTo(car , ent ) && Class.CastTo(key , newItem ) )
					{
						key.SetAlpKeyID( car.GetAlpCarID() );					
						key.SetSynchDirty();
					}	
				}
				
				if ( loots.quantmax > loots.quantmin && loots.quantmax <= 100 )
				{
					ItemBase item;
					if ( Class.CastTo(item,newItem) )
					{
						quantity = Math.RandomIntInclusive( loots.quantmin, loots.quantmax );
						if ( item.IsMagazine() )
						{
							Magazine_Base mag = Magazine_Base.Cast(item);	
							if ( mag )
							{
								quantityFloat = mag.GetAmmoMax() * ( quantity / 100 );
								quantity = quantityFloat;
								
								mag.ServerSetAmmoCount( quantity );
							}							
						}
						
						if ( item.HasQuantity() )
						{
							quantityFloat = item.GetQuantityMax() * ( quantity / 100 );
							
							quantity = quantityFloat;
							
							item.SetQuantity( quantity );
						}
					}				
				}
				break;
			}
			case "weapons":
			{
				classNames = loots.items.Get(loots.items.GetRandomIndex());
				
				
				
				wep = Weapon_Base.Cast(ent.GetInventory().CreateInInventory(classNames.Get(0)));	
				
				if ( wep && ent.IsPlayer() )
				{
					PlayerBase player = PlayerBase.Cast( ent ) ;
					
					if ( player && !player.GetItemInHands() )
					{
						player.ServerTakeEntityToHands( wep );	
					}
				}
				
				
				if (wep)
				{

					
					bool wasLoaded=false;
					for (i=1;i<classNames.Count();i++)
					{
						string typeAtt = classNames.Get(i);
						
						//Magazine_Base
						
						if ( GetGame().IsKindOf(typeAtt,"Magazine_Base") )
						{
							if ( wasLoaded)
							{
								ent.GetInventory().CreateInInventory(typeAtt);
							}
							else
							{
								wasLoaded = true;
								wep.SpawnAmmo( typeAtt );							
							}
						}
						else
						{
							ItemBase wepAtt = ItemBase.Cast( wep.GetInventory().CreateAttachment(typeAtt) );
						}
						
						
						
						/*
						ItemBase wepAtt = ItemBase.Cast( wep.GetInventory().CreateAttachment(classNames.Get(i)) );
						
						if (wepAtt && wepAtt.IsMagazine() )
						{							
							if ( loots.quantmax > loots.quantmin && loots.quantmax <= 100 )
							{
								quantity = Math.RandomIntInclusive( loots.quantmin, loots.quantmax );
								
								Magazine_Base mag2 = Magazine_Base.Cast(wepAtt);	
								if ( mag2 )
								{
									quantityFloat = mag2.GetAmmoMax() * ( quantity / 100 );		
									quantity = quantityFloat;						
									mag2.ServerSetAmmoCount( quantity );
								}												
							}							

							wep.ShowMagazine();							
						}
						*/
					}	

				}

				break;
			}
			case "equipments":
			{
				className = loots.items.Get(loots.items.GetRandomIndex()).GetRandomElement();
				if (ent.IsZombie()) 
					ent.GetInventory().CreateAttachment(className);
				else
					newItem = ent.GetInventory().CreateInInventory(className);
				break;
			}	
			case "lootset":
			{
				classNames = loots.items.Get(loots.items.GetRandomIndex());

				newItem =  ent.GetInventory().CreateInInventory(classNames.Get(0));
				
				if ( newItem )
				{									
					EntityAI att;
					bool hasAtt = true;
					for (i=1;i<classNames.Count();)
					{
						className = classNames.Get(i);
						if ( hasAtt )
						{
							att = newItem.GetInventory().CreateInInventory(className );
							
							if (!att)
							{
								hasAtt = false;
								continue;
							}
						}
						else
						{
							att = ent.GetInventory().CreateInInventory(className );
						}												
						i++;
					}			
				}																
				break;
			}							
		}				
		if ( locked )
		{
			ItemBase itm;
			if ( Class.CastTo(itm, newItem) || Class.CastTo(itm, wep))
			{
				itm.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
			}
		
		}
		
		if ( newItem || wep )
		{
			return true;
		}
		else
		{
			return false;
		}
	} 	
	
	
	void SetPlayerInRadiation(Object obj,float dist)
	{
		PlayerBase player;
		
		if ( Class.CastTo(player, obj) )
		{
			float radiation,angle;
						
			if ( IsRadioactive() )
			{

				//check if player is above the radiation area
				if ( GetTemplate().heightOfRadiationArea )
				{
					vector vm = GetPosition();
					vector vp = obj.GetPosition();
					
					float hm,hp;
					
					hm = Math.AbsFloat( vm[1] );
					hp = Math.AbsFloat( vp[1] );
					
					hm = Math.AbsFloat( hm - hp );
					
					if ( hm > GetTemplate().heightOfRadiationArea )
					{//out
						player.GetRP().SetRadiation( GetID(), 0 );
						return;
					}
					
				}
				
	
				if ( GetTemplate().enableSineFunction )		
				{
					angle = (dist / alp_DamageRadius * 360) * Math.DEG2RAD;	
					radiation = Math.Sin(angle) * GetTemplate().strengthOfRadiationOffset + alp_Radiation;
				}
				else
				{
					radiation = (1 - (dist/ alp_DamageRadius)) * alp_Radiation;
				}	

				if (  GetTemplate().rainingMultiplyRadiation && player.GetRP().IsRained() ) {
					//radiation = radiation * ( 1 + GetTemplate().rainingMultiplyRadiation );
					radiation *=  GetTemplate().rainingMultiplyRadiation;
				} 	

			}
			//extra adjust radiation according  GetTemplate().countdownBeforeDespawn;
			float mlt = GetRadiationMultiplier();
			
			float radius = alp_DamageRadius * mlt;				
			
			if ( dist <= radius ) {
				radiation = radiation * mlt;			
				player.GetRP().SetRadiation( GetID(), radiation );				
			}			
		}
	}	
	
	protected float GetRadiationMultiplier(){
		float mlt = 1;
		int time;
		if ( alp_TimeToFullRadiation && alp_StartAt ) {//nastaveni posilovani radiace ze startu
			time = alp_MissionTime - alp_TimeToFullRadiation;
			
			if ( time < alp_StartAt ) {
				mlt = ( alp_MissionTime - alp_StartAt ) / alp_TimeToFullRadiation;		
			}
		}
		if ( alp_CountdownDespawn && alp_EndAt ) {//zeslabovani radiace 
			time =  alp_MissionTime - alp_CountdownDespawn;
			
			if ( time <  alp_EndAt ) {
				mlt = ( alp_MissionTime - alp_EndAt ) / alp_CountdownDespawn;	
				mlt = 1 - mlt;					
			} else {
				mlt = 0;
			}
		}
		mlt = Math.Clamp(mlt,0,1);	
		return mlt;
	}
	

	protected void InitMissionValues(int radius = 0, float radiation = 0){}
	
	
	void SetPrivateTimeStemp(alpMission mission) {
		
	}
	
	void EventOnEnd()
	{
		int i;
		string name;

		array<ref alpMission> missions;
		
		for (i=0; i < GetTemplate().eventOnEndDespawn.Count();i++)
		{
			name = 	GetTemplate().eventOnEndDespawn.Get(i);
			
			missions = GetND().GetMS().GetMissionByName( name );
			
			if ( missions )
			{
				foreach (alpMission mission : missions )
				{
					if ( mission.IsActive() && GetID() == mission.GetParentID() )
					{
						mission.SetSecured();
						break;
					}
					
				}
			}

		}
		
		for (i=0; i < GetTemplate().eventOnEndSpawn.Count();i++)
		{
			name = 	GetTemplate().eventOnEndSpawn.Get(i);
			
			missions = GetND().GetMS().GetMissionByName( name );
			
			if ( missions )
			{
				foreach (alpMission mission2 : missions )
				{
					if ( !mission2.IsActive() )
					{
						mission2.SpawnMission( alp_Position, alp_Angle, GetID() );
						break;
					}
					
				}
			}			
		}	
	}		
	
	void EventOnMissionSecured()
	{
		int i;
		string name;

		array<ref alpMission> missions;
		
		for (i=0; i < GetTemplate().eventOnSecureMissionDespawn.Count();i++)
		{
			name = 	GetTemplate().eventOnSecureMissionDespawn.Get(i);
			
			missions = GetND().GetMS().GetMissionByName( name );
			
			if ( missions )
			{
				foreach (alpMission mission : missions )
				{
					if ( mission.IsActive() && GetID() == mission.GetParentID() )
					{
						mission.SetSecured();
						break;
					}
					
				}
			}

		}
		
		for (i=0; i < GetTemplate().eventOnSecureMissionSpawn.Count();i++)
		{
			name = 	GetTemplate().eventOnSecureMissionSpawn.Get(i);
			
			missions = GetND().GetMS().GetMissionByName( name );
			
			if ( missions )
			{
				foreach (alpMission mission2 : missions )
				{
					if ( !mission2.IsActive() )
					{			
						SetPrivateTimeStemp( alpMission.Cast( mission2.SpawnMission( alp_Position, alp_Angle, GetID() ) ) );
						break;
					}
					
				}
			}			
		}	
	}
	
	void EventOnEnterSafeRadius()
	{
		int i;
		string name;

		array<ref alpMission> missions;
		
		
		for (i=0; i < GetTemplate().eventOnEnterSafeRadiusDespawn.Count();i++)
		{
			name = 	GetTemplate().eventOnEnterSafeRadiusDespawn.Get(i);
			
			missions = GetND().GetMS().GetMissionByName( name );
			
			if ( missions )
			{
				foreach (alpMission mission : missions )
				{
					if ( mission.IsActive() && GetID() == mission.GetParentID() )
					{
						mission.SetSecured();
						break;
					}
					
				}
			}
		}
		
		for (i=0; i < GetTemplate().eventOnEnterSafeRadiusSpawn.Count();i++)
		{
			name = 	GetTemplate().eventOnEnterSafeRadiusSpawn.Get(i);
			
			missions = GetND().GetMS().GetMissionByName( name );
			
			if ( missions )
			{
				foreach (alpMission mission2 : missions )
				{
					if ( !mission2.IsActive() )
					{
						mission2.SpawnMission( alp_Position, alp_Angle , GetID() );
						break;
					}
					
				}
			}
		}		
	}		
	void EvenetOnStart()
	{
		int i;
		string name;

		array<ref alpMission> missions;
		
		
		for (i=0; i < GetTemplate().eventOnStartDespawn.Count();i++)
		{
			name = 	GetTemplate().eventOnStartDespawn.Get(i);
			
			missions = GetND().GetMS().GetMissionByName( name );
			
			if ( missions )
			{
				foreach (alpMission mission : missions )
				{
					if ( mission.IsActive() && GetID() == mission.GetParentID() )
					{
						mission.SetSecured();
						break;
					}
					
				}
			}
		}
		
		for (i=0; i < GetTemplate().eventOnStartSpawn.Count();i++)
		{
			name = 	GetTemplate().eventOnStartSpawn.Get(i);
			
			missions = GetND().GetMS().GetMissionByName( name );
			
			if ( missions )
			{
				foreach (alpMission mission2 : missions )
				{
					if ( !mission2.IsActive() )
					{
						mission2.SpawnMission( alp_Position, alp_Angle, GetID() );
						break;
					}
					
				}
			}
		}	
	}	
	
	void LoadNPCs() {		
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - loading NPCs");	//log		
		int count,index, id;
		if ( m_Hive.m_NPCdynamic && m_Hive.m_NPCdynamic.Count() && GetTemplate().NPCdynamic ) {//dynamic
			count = GetTemplate().NPCdynamic.Count();
			foreach( alpMissionElementStore_Base stored : m_Hive.m_NPCdynamic ) {
				index = stored.m_Index;
				if ( index < count ) {
					id = LoadNPC( stored , GetTemplate().NPCdynamic.Get(index) , true); 
					stored.m_ID = id;
				}
			}			
		}		
		if ( m_Hive.m_NPC && m_Hive.m_NPC.Count() && GetTemplate().NPC ) {//static
			count = GetTemplate().NPC.Count();
			foreach( alpMissionElementStore_Base stored2 : m_Hive.m_NPC ) {
				index = stored2.m_Index;
				if ( index < count ) {
					id = LoadNPC( stored2 , GetTemplate().NPC.Get(index) , false); 
					stored2.m_ID = id;
				}
			}			
		}
		//NPC flag
		alp_AllNPCspawned = true;			
		//save changes
		alpMHIVE.Save();		
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - NPC loaded successfully");	//log					
	}
	int LoadNPC(alpMissionElementStore_Base stored, alpMissionAddNPC equip, bool isDynamic) {
		Man man;
		if ( Class.CastTo(man, GetGame().CreateObject(stored.m_Type ,stored.m_Position ,false,false,true) ) ){			
			man.SetYawPitchRoll( stored.m_YPR );
			man.SetOrientation( stored.m_YPR ); 			
			foreach (string att2 : equip.attachments) {
				man.GetInventory().CreateInInventory(att2);
			}				
			//cargo
			int count = 0;
			int maxCount = equip.lootMaxCount;			
			foreach (alpLootCargo cargoMan : equip.cargo){
				alpLoot lootMan = GetLoots(cargoMan.title);				
				if (lootMan) {
					if ( SpawnCargo(man,lootMan,cargoMan.chance) ){
						count++; 
					};
				} else {
					if ( SpawnEntityInCargo(man, cargoMan.title, cargoMan.chance )){
						count++; 
					};
				}	
																
				if ( maxCount && count >= maxCount ){
					break;
				}								
			}				
			SetUpNPC(man,equip );		
			man.SetSynchDirty();	
			alpMissionElement e = new alpMissionElement(man);	
			alp_NPC.Insert( e );							
			return man.GetID();
		}			
		return 0;
	}
	
	
	void LoadStructures() {		
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - loading structures");	//log		
		int count,index, id;
		if ( m_Hive.m_Structures && m_Hive.m_Structures.Count() && GetTemplate().structures ) {
			count = GetTemplate().structures.Count();
			foreach( alpMissionElementStore_Base stored : m_Hive.m_Structures ) {
				index = stored.m_Index;
				if ( index < count ) {
					id = LoadStructure( stored , GetTemplate().structures.Get(index) ); 
					stored.m_ID = id;
				}
			}			
		}				
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - structures loaded successfully");	//log					
	}	
	
	int LoadStructure(alpMissionElementStore_Base stored, alpMissionAddSpawn structure){
		EntityAI ent;
		if ( Class.CastTo(ent, GetGame().CreateObject(stored.m_Type ,stored.m_Position ,false,false,true) ) ){			
			ent.SetYawPitchRoll( stored.m_YPR );
			ent.SetOrientation( stored.m_YPR ); 
	
			//setlifetime
			ent.SetLifetimeMax(ALP_LIFETIMEMAX);
			ent.SetLifetime(ALP_LIFETIMEMAX);			

			if ( ent.IsKindOf("Wreck_UH1Y") ){
				Wreck_UH1Y uh1y = Wreck_UH1Y.Cast( ent );
				uh1y.SetMissionObjectState( true );
				uh1y.EEOnALPCreate();
			}			
			if ( ent.IsKindOf("Wreck_Mi8") ){
				Wreck_Mi8 mi8 = Wreck_Mi8.Cast( ent );
				mi8.SetMissionObjectState( true );	
				mi8.EEOnALPCreate();			
			}
			if ( ent.IsKindOf("Wreck_Mi8_Crashed") ){
				Wreck_Mi8 mi8crashed = Wreck_Mi8.Cast( ent );
				mi8crashed.SetMissionObjectState( true );				
				mi8crashed.EEOnALPCreate();
			}						
			//fireplice in building				
			BuildingWithFireplace bwf;
			if (structure.makeFire && Class.CastTo( bwf, ent ) ){
				SetIndoorFireplace( bwf , structure.makePersist );
			}
			
			CustomStructure( ent );
			if (! structure.makePersist){
				alpMissionElement e = new alpMissionElement(ent);	
				alp_Structures.Insert( e );				
			} else {
				alpMissionElement e2 = new alpMissionElement(ent, true);	
				alp_Structures.Insert( e2 );										
			}			
			UpdateNavmesh( ent );									
			return ent.GetID();
		}				
		return 0;
	}
	void LoadControlPanels() {		
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - loading control panels");	//log		
		int count,index, id;
		if ( m_Hive.m_ControlPanels && m_Hive.m_ControlPanels.Count() && GetTemplate().controlPanels ) {
			count = GetTemplate().controlPanels.Count();
			foreach( alpMissionElementStore_Base stored : m_Hive.m_ControlPanels ) {
				index = stored.m_Index;
				if ( index < count ) {
					id = LoadPanel( stored , GetTemplate().controlPanels.Get(index) ); 
					stored.m_ID = id;
				}
			}			
		}				
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - control panels loaded successfully");	//log					
	}	
	int LoadPanel(alpMissionElementStore_Base stored, alpMissionAddSpawn structure){
		EntityAI ent;
		if ( Class.CastTo(ent, GetGame().CreateObject(stored.m_Type ,stored.m_Position ,false,false,true) ) ){			
			ent.SetYawPitchRoll( stored.m_YPR );
			ent.SetOrientation( stored.m_YPR ); 
	
			//setlifetime
			ent.SetLifetimeMax(ALP_LIFETIMEMAX);
			ent.SetLifetime(ALP_LIFETIMEMAX);			

			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CustomControlPanel,100,false, ent , structure );
			
			if (! structure.makePersist){
				alpMissionElement e = new alpMissionElement(ent);	
				alp_Structures.Insert( e );				
			} else {
				alpMissionElement e2 = new alpMissionElement(ent, true);	
				alp_Structures.Insert( e2 );										
			}			
			UpdateNavmesh( ent );									
			return ent.GetID();
		}				
		return 0;
	}	
	void LoadLoots() {		
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - loading loot");	//log		
		int count,index, id;
		if ( m_Hive.m_Loots && m_Hive.m_Loots.Count() && GetTemplate().loot ) {
			count = GetTemplate().loot.Count();
			foreach( alpMissionElementStore_Base stored : m_Hive.m_Loots ) {
				index = stored.m_Index;
				if ( index < count ) {
					id = LoadLoot( stored , GetTemplate().loot.Get(index) ); 
					stored.m_ID = id;
				}
			}			
		}				
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - loot loaded successfully");	//log					
	}		
	int LoadLoot(alpMissionElementStore_Base stored, alpMissionAddCargo loot){		
		ItemBase ent;
		if ( Class.CastTo(ent, GetGame().CreateObject(stored.m_Type ,stored.m_Position ,false,false,true) ) ){	
			ent.SetYawPitchRoll( stored.m_YPR );
			ent.SetOrientation( stored.m_YPR ); 			
			//setlifetime
			//ent.SetLifetimeMax(ALP_LIFETIMEMAX);
			//ent.SetLifetime(ALP_LIFETIMEMAX);					
			
			if ( ent.IsItemTent() ){//kontrola zda to neni stan a pripadne ho rozbalit				
				TentBase.Cast(ent).Pitch ( true );			
			}			
			ent.Open();			
			//spawn QUEST ITEM first
			if ( loot.spawnQuestItem && alp_WantedItem !="" ){
				ent.GetInventory().CreateInInventory( alp_WantedItem );
			}			
			int count = 0;
			int maxCount = loot.lootMaxCount;
			foreach (alpLootCargo cargo : loot.cargo){				
				alpLoot items = GetLoots(cargo.title);
				if (items) {
					if (SpawnCargo(ent,items,cargo.chance, loot.locked)){
						count++; 
					};	
				} else {
					if (SpawnEntityInCargo(ent, cargo.title, cargo.chance )){
						count++; 
					};
				}				 												
				if ( maxCount && count >= maxCount ){
					break;
				}
			}										
			//ent.Close();	
			CloseLoot( ent );
			//Stashed		
			if (loot.stashed && ent.ConfigGetBool("canBeDigged") ){
				ent = DigItem(ent);	
				if ( ent ) {
					Print("ALPMS: SpawnLoot - " + stored.m_Type + " - " + stored.m_Position + " - loot was digged successfully");	//log
				} else {
					Print("ALPMS: SpawnLoot - " + stored.m_Type + " - " + stored.m_Position + " - loot was not digged successfully");	//log
				}
			}	
			//isFirePlace FirePlace
			if (!loot.stashed && ent.IsKindOf("FireplaceBase") )
			{								
				SetFirePlace(ent, loot.locked);							
			}	
			//trapbase
			if (!loot.stashed && ent.IsInherited(TrapBase) )
			{					
				SetTrap(ent);							
			}				
			//check loot item by mod
			SpawnLootEvent( ent );				
			//mission objects flag
			ent.SetMissionObjectState( true );	
			if ( loot.locked ){
				ent.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT); 	
			}	
			if (! loot.makePersist) {
				alpMissionElement e = new alpMissionElement(ent);	
				alp_LootContainer.Insert( e );						
			}	else {
				alpMissionElement e2 = new alpMissionElement(ent, true );	
				alp_LootContainer.Insert( e2 );														
			}		
			return ent.GetID();													
		}				
		return 0;
	}
	void LoadCars() {		
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - loading cars");	//log		
		int count,index, id;
		if ( m_Hive.m_Cars && m_Hive.m_Loots.Count() && GetTemplate().vehicles ) {
			count = GetTemplate().vehicles.Count();
			foreach( alpMissionElementStore_Base stored : m_Hive.m_Cars ) {
				index = stored.m_Index;
				if ( index < count ) {
					id = LoadCar( stored , GetTemplate().vehicles.Get(index) ); 
					stored.m_ID = id;
				}
			}			
		}				
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - cars loaded successfully");	//log					
	}	
		
	int LoadCar(alpMissionElementStore_Base stored, alpMissionAddVehicle equip){
		Transport ent;
		alpVehicles vehicle	= GetVehicles(equip.title);
		int find = -1;
	
		for (int a = 0;a < vehicle.items.Count();a++){
			if ( stored.m_Type == vehicle.items.Get(a).Get(0) ){
				find = a;
				break;
			}
		}
		if ( find != -1 &&  Class.CastTo(ent, GetGame().CreateObject(stored.m_Type ,stored.m_Position ,false,false,true)  ) ) {
			TStringArray 	classNames = vehicle.items.Get( find );;
			ent.SetYawPitchRoll( stored.m_YPR );
			ent.SetOrientation( stored.m_YPR ); 
			
			for (int i = 1; i < classNames.Count();i++){//attachments
				if (Math.RandomFloat01() <= vehicle.chanceAttachments){
					ent.GetInventory().CreateAttachment(classNames.Get(i));
				}
			}
			alpUF.FillFluidsToVehicle(ent , (Math.RandomFloat01() <= vehicle.chanceFluid), true, vehicle.minFuelAmount,vehicle.maxFuelAmount );//fill fluids			
			
				int count = 0;
				int maxCount = vehicle.lootMaxCount;				
				foreach (alpLootCargo cargo : vehicle.cargo){//cargo
					alpLoot loots = GetLoots(cargo.title);
					if (loots) {
						if (SpawnCargo(ent,loots,cargo.chance)){
							count++; 
						};	
					} else {
						if (SpawnEntityInCargo(ent, cargo.title, cargo.chance )){
							count++; 
						};
					}													
					if ( maxCount && count >= maxCount ){
						break;
					}											
				}	

				//lock vehicle
				if ( vehicle.locked ) {
					if ( ent.IsInherited(	HelicopterScript ) ){
						HelicopterScript hel = HelicopterScript.Cast( ent );
						if ( hel ) {
							hel.MissionLockVehicleALP(true);
						}					
					} else if ( ent.IsInherited(	CarScript ) ) {
						CarScript car = CarScript.Cast( ent );
						if ( car ) {
							car.MissionLockVehicleALP(true);
						}						
					}
				}							
			
			
			ent.SetLifetimeMax(ALP_LIFETIMEMAX);//  3888000 ALP_LIFETIMEMAX
			ent.SetLifetime(ALP_LIFETIMEMAX);//  3888000 ALP_LIFETIMEMAX				
			
			if (! equip.makePersist) {
				alpMissionElement e = new alpMissionElement(ent);	
				alp_Vehicles.Insert( e );				
			} else {
				alpMissionElement e2 = new alpMissionElement(ent);	
				alp_Vehicles.Insert( e2 );							
			}	
			return ent.GetID();					
		}						
		return 0;
	}		
	//LoadToxicZones
	void LoadToxicZones() {		
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - loading ToxicZones");	//log		
		int count,index, id;
		if ( m_Hive.m_ContaminedAreasDynamic && m_Hive.m_NPCdynamic.Count() && GetTemplate().contaminedAreasDynamic ) {//dynamic
			count = GetTemplate().contaminedAreasDynamic.Count();
			foreach( alpMissionElementStore_Base stored : m_Hive.m_ContaminedAreasDynamic ) {
				index = stored.m_Index;
				if ( index < count ) {
					id = LoadToxic( stored , GetTemplate().contaminedAreasDynamic.Get(index).Area  , true); 
					stored.m_ID = id;
				}
			}			
		}		
		if ( m_Hive.m_ContaminedAreas && m_Hive.m_ContaminedAreas.Count() && GetTemplate().contaminedAreas ) {//static
			count = GetTemplate().contaminedAreas.Count();
			foreach( alpMissionElementStore_Base stored2 : m_Hive.m_ContaminedAreas ) {
				index = stored2.m_Index;
				if ( index < count ) {
					id = LoadToxic( stored2 , GetTemplate().contaminedAreas.Get(index).Area , false); 
					stored2.m_ID = id;
				}
			}			
		}		
Print("ALPMS: mission " + GetName() + " - " + GetPosition() + " - ToxicZones loaded successfully");	//log					
	}		
	int LoadToxic(alpMissionElementStore_Base stored, JsonDataContaminatedArea_ALP area, bool isDynamic) {
		EffectArea toxicZone;
		if (  Class.CastTo( toxicZone, GetGame().CreateObjectEx(stored.m_Type , stored.m_Position, ECE_NONE ) ) ) {
			toxicZone.SetupZoneData(  GetSetupForToxicZone(area)  );
			
			if ( area.Type == "ContaminatedArea_Dynamic" ){	
				toxicZone.SetLifetimeMax( GetTemplate().lifeTime );
				toxicZone.SetLifetime( GetTemplate().lifeTime );										
			} else {
				toxicZone.SetLifetimeMax( ECE_NOLIFETIME );
				toxicZone.SetLifetime( ECE_NOLIFETIME );											
			}		
			alpMissionElement e = new alpMissionElement(toxicZone);	
			alp_ToxicZones.Insert( e );		
			
			return toxicZone.GetID();	
		}	
		return 0;
	}	
}