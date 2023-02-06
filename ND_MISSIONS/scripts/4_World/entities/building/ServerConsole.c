enum alpMMACTION{
	NONE,
	ACTIVE,
	DEACTIVE,
	SET_TIME_TO_ACTIVE,
	SET_TIME_TO_DEACTIVE,
	CANCEL_ACTIVE_TIME,	
	CANCEL_DEACTIVE_TIME,		
}


class alp_ServerConsole extends BuildingSuper  
{
	
	string                          m_DataAboutMission;
	string 							m_MissionWhileCountdowningON;
	string 							m_MissionWhileCountdowningOFf;	 
	
	
	int 							alp_ParentMission;
	int 							alp_MissionAccesCardID;
	
	ref alpMissionAddControlPanel	alp_MissionManage;

	int 							alp_MissionManaged;		
	int 							alp_MissionTriggerSetting;
	
	int 							alp_MissionSwitchCooldown;	

	int 							alp_MissionActionGameplayCountdownedON;
	int 							alp_MissionActionGameplayCountdownedOFF;
	
	string 							alp_CountdownMessageON;	
	string 							alp_CountdownMessageOFF;			
	string 							alp_MissionActionMessageON;	
	string 							alp_MissionActionMessageOFF;	
		
	ref Timer  						alp_ActionTimer;		
			
	//effects
	protected Particle 		alp_ParticleDamaged;
	protected Particle 		alp_ParticleRuined;

	protected vector		alp_ParticleDamagedPos;	
	protected vector		alp_ParticleRuinedPos;	
	
	int alp_LastSetting;
	
	bool 							m_ActivatedByPlayer;	
			
	void alp_ServerConsole(){
		//alp_Health = 100;
		RegisterNetSyncVariableInt("alp_MissionTriggerSetting");	
		RegisterNetSyncVariableInt("alp_MissionManaged");	
		RegisterNetSyncVariableInt("alp_MissionAccesCardID");	
		
		
		alp_ParticleRuinedPos = GetSelectionPositionMS("misc2"); // WorldToModel(GetPosition());
		alp_ParticleDamagedPos = GetSelectionPositionMS("notebook"); // GetSelectionPositionMS("notebook");
				
		
		if ( GetGame().IsClient() ){
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdateVisualALP ,1000 );
		}
		

		
	}
	void ~alp_ServerConsole()
	{
		DestroyParticle(alp_ParticleDamaged);
		DestroyParticle(alp_ParticleRuined);
		
		delete alp_ActionTimer;
		
		
	}	
	protected void DestroyParticle(Particle p)
	{
		#ifndef SERVER
		if (p != null)
		{
			p.Stop();
		}
		#endif
	}	
		
	override bool IsBuilding()
	{
		return false;
	}
	
	void SetMissionManage(alpMissionAddControlPanel control , int parentMission ){
		alp_ParentMission = parentMission;
		alp_MissionManage = control;
		
		m_DataAboutMission = control.dataAboutMission;	
		
		m_MissionWhileCountdowningON = control.missionWhileCountdowningON;	
		m_MissionWhileCountdowningOFf = control.missionWhileCountdowningOFf;		 
		
		alp_MissionTriggerSetting 	=  control.missionTriggerSetting;		
		alp_MissionSwitchCooldown 	=  control.missionSwitchCooldown;		
		alp_MissionAccesCardID 		=  control.missionAccesCardID;		
		
		alp_MissionActionGameplayCountdownedON 	=  control.missionActionGameplayCountdownedON;
		alp_MissionActionGameplayCountdownedOFF	=  control.missionActionGameplayCountdownedOFF;			
		alp_CountdownMessageON 					=  control.countdownMessageON;
		alp_CountdownMessageOFF 				=  control.countdownMessageOFF;
		alp_MissionActionMessageON 				=  control.missionActionMessageON;
		alp_MissionActionMessageOFF 			=  control.missionActionMessageOFF;								
		
		InitMissionStage();
	}
	
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef){
		if ( IsSetSettingALP( alpMISSIONTRIGGER.CANBEDAMAGED ) && !IsRuinedALP() ) {
			if ( damageType == DT_EXPLOSION && ( ammo == "alp_DynamiteExplosion" || ammo == "Plastic_Explosive_Ammo" ) ){
				SetSettingALP( 	 alpMISSIONTRIGGER.ISRUINED );	
			} else {
				SetSettingALP( 	 alpMISSIONTRIGGER.ISDAMAGED );	
			}	
			SaveMissionActionStage();
		}	

	}
	
	void UpdateVisualALP(){
		
		
		TStringArray textures = GetHiddenSelectionsTextures();		
		string texture;		
						
		if ( IsRuinedALP() ) {
			if (IsEnabledReverseModWhenKilled()){
				if ( IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) {
					StartManagedMission(null);	
				} else {
					DespawnManagedMission();
				}				
			}
			if ( !alp_ParticleRuined ) {
				alp_ParticleRuined = ParticleManager.GetInstance().PlayOnObject(ParticleList.SMOKING_CAR_ENGINE, this , alp_ParticleRuinedPos, Vector(0, 0, 0), true);	
			}			
			texture = textures.Get(1);
		}
		if ( IsDamagedALP() ) {
			if ( !alp_ParticleDamaged ) {
				alp_ParticleDamaged = ParticleManager.GetInstance().PlayOnObject(ParticleList.COOKING_BOILING_DONE, this , alp_ParticleDamagedPos , Vector(0, 0, 0), true);	
			}							
			texture = textures.Get(1);
		} 
		if ( !IsRuinedALP() && !IsDamagedALP() ){//clear effects
			DestroyParticle(alp_ParticleDamaged);
			DestroyParticle(alp_ParticleRuined);	
			alp_ParticleDamaged = null;		
			alp_ParticleRuined = null;			
			texture = textures.Get(0);
		}
		SetObjectTexture(0, texture);
		
	}
	
	override void OnVariablesSynchronized(){
		super.OnVariablesSynchronized();
		if ( alp_LastSetting != alp_MissionTriggerSetting ) {
			alp_LastSetting = alp_MissionTriggerSetting;
			UpdateVisualALP();
		}		
	}
	
	
	
	bool IsEnabledReverseModWhenKilled(){
		if ( alp_MissionTriggerSetting && IsSetSettingALP( alpMISSIONTRIGGER.NOTALIVE_DEACTIVATE | alpMISSIONTRIGGER.ISACTIVATED ) ) {
			return true;
		}
		return false;
	}	
	int GetAccesCardID(){
		return alp_MissionAccesCardID;
	}
	bool CanBeLockedALP(){
		return 	IsSetSettingALP( alpMISSIONTRIGGER.CANBELOCKED );
	}	
	bool IsLockedALP(){
		return 	IsSetSettingALP( alpMISSIONTRIGGER.CANBELOCKED ) && IsSetSettingALP( alpMISSIONTRIGGER.ISLOCKED );
	}
	bool IsUnlockedALP(){
		return  ( !IsSetSettingALP( alpMISSIONTRIGGER.CANBELOCKED ) || ( IsSetSettingALP( alpMISSIONTRIGGER.CANBELOCKED ) && !IsSetSettingALP( alpMISSIONTRIGGER.ISLOCKED ) );
	}	
	void LockConsoleALP(){
		SetSettingALP( 	 alpMISSIONTRIGGER.ISLOCKED );	
		SetSynchDirty();
	}
	void UnlockConsoleALP(){
		RemoveSettingALP( 	 alpMISSIONTRIGGER.ISLOCKED );				
		SetSynchDirty();
	}	
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(alpActionServerConsole);
		AddAction(alpActionServerConsoleLocked);
		AddAction(alpActionServerConsoleLock);
		AddAction(alpActionServerConsoleUnlock);
		
		AddAction(alpActionServerConsoleDownloadData);
		AddAction(alpActionServerConsoleDeleteData);				
	}

	alpMission GetManagedMission() {
		return GetND().GetMS().GetMission( alp_MissionManaged );
	}		
	
	void SetSettingALP(int setting)
	{

				
		alp_MissionTriggerSetting = (alp_MissionTriggerSetting | setting); 
	}
	void RemoveSettingALP(int setting)
	{				                             	
		
		if (IsSetSettingALP(setting ))
		{
			alp_MissionTriggerSetting = ~setting & alp_MissionTriggerSetting;
		}
	}	
	bool IsSetSettingALP(int setting )
	{
		return alp_MissionTriggerSetting & setting;
	}
	bool IsDamagedALP(){
		return IsSetSettingALP( alpMISSIONTRIGGER.ISDAMAGED );	
	}
	bool IsRuinedALP(){
		return IsSetSettingALP( alpMISSIONTRIGGER.ISRUINED );	
	}			
	bool IsSwapedActionTitle(){
		return IsSetSettingALP( alpMISSIONTRIGGER.SWAP_DEFAULT_TITLE );
	}
		
	protected void InitMissionStage() {		
		alpMission mission = GetManagedMission();
		if ( mission && alp_MissionTriggerSetting && IsSetSettingALP( alpMISSIONTRIGGER.ENABLED ) && !IsRuinedALP() ) {			
			if ( IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED ) ) {
				if ( !IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) {
					//StartManagedMission(null);
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(StartManagedMission,100,false,  null );//due to start INIT
				} else {						
					//DespawnManagedMission();
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DespawnManagedMission,100);//due to start INIT
				}				
				if ( IsSetSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED ) ){//prepare to deactivate
					SetTimerToAction( alpMMACTION.SET_TIME_TO_DEACTIVE );	
				} 
			} else {
				if ( !IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) {					
					//DespawnManagedMission();
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DespawnManagedMission,100);//due to start INIT
				} else {						
					//StartManagedMission(null);
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(StartManagedMission,100,false,  null );//due to start INIT
				}				
				if ( IsSetSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED ) ){//prepare to activate
					SetTimerToAction( alpMMACTION.SET_TIME_TO_ACTIVE );	
				} 			
			}
			
		}
		SaveMissionActionStage();
	}
		
	int GetTypeOfManagedMissionAction(){
		alpMission mission = GetManagedMission();
		int type = 0;
		if ( mission && alp_MissionTriggerSetting && IsSetSettingALP( alpMISSIONTRIGGER.ENABLED ) && !IsRuinedALP() && !IsDamagedALP() ) {
			//update synchronizace mise 
			if ( ( mission.IsActive() && !IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) || ( !mission.IsActive() && IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) ) {
				SetSettingALP( alpMISSIONTRIGGER.ISACTIVATED );	
			} else if ( ( !mission.IsActive() && !IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) || ( mission.IsActive() && IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) ) {
				RemoveSettingALP( alpMISSIONTRIGGER.ISACTIVATED );
			}		
				
			if ( !IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED  ) ) { //default setting
				if (  !IsSetSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED)  ){
					if ( alp_MissionActionGameplayCountdownedON ) {
						type =  alpMMACTION.SET_TIME_TO_ACTIVE;
					} else {
						type =  alpMMACTION.ACTIVE;
					}								
				} else {
					type =  alpMMACTION.CANCEL_ACTIVE_TIME;
				}
				
				return type;
			}			
			if ( IsSetSettingALP( alpMISSIONTRIGGER.ENABLED_DEACTIVATION ) && IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED  ) ) {		
				if (  !IsSetSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED)  ){
					if ( alp_MissionActionGameplayCountdownedOFF ) {
						type =  alpMMACTION.SET_TIME_TO_DEACTIVE;
					} else {
						type =  alpMMACTION.DEACTIVE;
					}								
				} else {
					type =  alpMMACTION.CANCEL_DEACTIVE_TIME;
				}				
				return type;		
			}										
		}
		return type;
	}	

	void MakeReadyMissionAction(PlayerBase player){
		int type = GetTypeOfManagedMissionAction();	
		m_ActivatedByPlayer = true;	
		switch ( type ) {
			case alpMMACTION.ACTIVE:		
				SetSettingALP( alpMISSIONTRIGGER.ISACTIVATED );
				if ( !IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) {					
					StartManagedMission(player);
				} else {
					DespawnManagedMission();
				}
				if (m_ActivatedByPlayer && IsSetSettingALP( alpMISSIONTRIGGER.CAN_BE_USED_ONCE ) ) {
					RemoveSettingALP( alpMISSIONTRIGGER.ENABLED );
				}	
				break;
			case alpMMACTION.DEACTIVE:
				RemoveSettingALP( alpMISSIONTRIGGER.ISACTIVATED );
				if ( !IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) {
					DespawnManagedMission();
				} else {
					StartManagedMission(player);
				}	
				if (m_ActivatedByPlayer && IsSetSettingALP( alpMISSIONTRIGGER.CAN_BE_USED_ONCE ) ) {
					RemoveSettingALP( alpMISSIONTRIGGER.ENABLED );
				}					
				break;
			case alpMMACTION.SET_TIME_TO_ACTIVE:
				SetTimerToAction( type );
				break;
			case alpMMACTION.SET_TIME_TO_DEACTIVE:
				SetTimerToAction( type );
				break;
			case alpMMACTION.CANCEL_ACTIVE_TIME:
			case alpMMACTION.CANCEL_DEACTIVE_TIME:
				StopActionTimer();
				break;				
		}		
		if ( type ) {
			
			 if ( !IsSetSettingALP( alpMISSIONTRIGGER.CAN_BE_USED_ONCE ) && alp_MissionSwitchCooldown ) {//do cooldown							
				int cooldown = alp_MissionSwitchCooldown * 1000;
				RemoveSettingALP( alpMISSIONTRIGGER.ENABLED );
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.EnableActionMissionTrigger ,cooldown );
			}		
			//Messages
			if ( ( type == alpMMACTION.ACTIVE || type == alpMMACTION.SET_TIME_TO_ACTIVE || type == alpMMACTION.CANCEL_DEACTIVE_TIME ) && alp_MissionActionMessageON !="" ) {
				GetND().GetNotf().SendMissionMessage(  ALPMSTYPE.SMACTIVATE	, alp_MissionManaged , alp_MissionActionMessageON , GetPosition(), null, true );
			}
			if ( ( type == alpMMACTION.DEACTIVE || type == alpMMACTION.SET_TIME_TO_DEACTIVE || type == alpMMACTION.CANCEL_ACTIVE_TIME ) && alp_MissionActionMessageOFF !="" )  {
				GetND().GetNotf().SendMissionMessage(  ALPMSTYPE.SMACTIVATE	, alp_MissionManaged , alp_MissionActionMessageOFF , GetPosition(), null, true );
			}	

			SaveMissionActionStage();
		}
	}
	
	ref alpMission m_MissionWhileCD;
	alpMission SpawnMissionWhileCountdowning(string name ){
		array<ref alpMission> missions = GetND().GetMS().GetMissionByName( name );
		if ( missions )
		{
			foreach (alpMission mission2 : missions )
			{
				if ( !mission2.IsActive() )
				{
					return alpMission.Cast( mission2.SpawnMission( GetPosition(), GetYawPitchRoll(), alp_MissionManaged ) );
					break;
				}
				
			}
		}	
		return null;
	}
	
	int alp_TimerStamp;
	void SetTimerToAction(int action){

		if ( !IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED  ) ) {
			m_MissionWhileCD = SpawnMissionWhileCountdowning( m_MissionWhileCountdowningON );
		} else {
			m_MissionWhileCD = SpawnMissionWhileCountdowning( m_MissionWhileCountdowningOFf );	
		}				
		
		alp_TimerStamp = 0;
		alp_ActionTimer = new Timer( CALL_CATEGORY_GAMEPLAY );	
		
		alp_ActionTimer.Run(1, this, "TimerActionUpdate", null, true);		
		//set event
		SetSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED );			
	}
	
	void StopActionTimer() {
		if ( m_MissionWhileCD ) {
			m_MissionWhileCD.SetSecured();
			//m_MissionWhileCD.DespawnMission();
			m_MissionWhileCD = null;
		}
		
		alp_TimerStamp = 0;
		if (alp_ActionTimer && alp_ActionTimer.IsRunning() ) {
			alp_ActionTimer.Stop();
			alp_ActionTimer = NULL;
		}
		RemoveSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED  );
	}
	
	
	void TimerActionUpdate() {
		alp_TimerStamp += 1;		
		int timeCounter;
		string message, messageTime;
		
		if ( !IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED  ) ) {
			timeCounter = alp_MissionActionGameplayCountdownedON;
			message = alp_CountdownMessageON;
		} else {
			timeCounter = alp_MissionActionGameplayCountdownedOFF;
			message = alp_CountdownMessageOFF;		
		}
		int remainingTime = timeCounter - alp_TimerStamp;
		int afterDiv;
		int hour,min,sec;
		if ( remainingTime > 0 ) {//countdown
			if ( remainingTime  >= 3600 ) {//above one hour
				afterDiv = remainingTime % 1800;	
			} else if ( remainingTime  >= 1200 ){//above 20 min
				afterDiv = remainingTime % 600;
			} else if ( remainingTime  >= 300 ){//above 5 min 
				afterDiv = remainingTime % 300;
			} else if ( remainingTime  >= 60 ){//above 1 min 
				afterDiv = remainingTime % 60;
			} else {//under 1 min
				afterDiv = remainingTime % 30;	
			}
			
			if ( !afterDiv && message != "" ){//send message
				hour = (int) Math.Floor( remainingTime / 3600 );
				min = remainingTime - ( hour * 3600 );
				min = (int) Math.Floor( min / 60 );	
				sec = remainingTime - ( hour * 3600 ) - ( min * 60 );	

				if ( hour ) {
					messageTime	= hour.ToString() + "h ";
				}
				if ( min ) {
					messageTime	+= min.ToString() + "m ";
				}
				if ( sec ) {
					messageTime	+= sec.ToString() + "s";
				}
				
				message += " (#alp_cd: " + messageTime + ")";
				GetND().GetNotf().SendMissionMessage(  ALPMSTYPE.MMCOUNTDOWN	, -1 , message , GetPosition(), null, true );	
			}
			
		} else {//run event
			alpMission mission = GetManagedMission();
			if ( mission ) {
		
				if ( !IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED ) ) {//activate
					SetSettingALP( alpMISSIONTRIGGER.ISACTIVATED );
					if ( !IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) {
						StartManagedMission(null);
					} else {
						DespawnManagedMission();
					}
								
				} else {//deactivate
					RemoveSettingALP( alpMISSIONTRIGGER.ISACTIVATED );
					if ( !IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) {
						DespawnManagedMission();
					} else {
						StartManagedMission(null);
					}					
				}
				if (/*m_ActivatedByPlayer &&*/ IsSetSettingALP( alpMISSIONTRIGGER.CAN_BE_USED_ONCE ) ) {
					RemoveSettingALP( alpMISSIONTRIGGER.ENABLED );
				}				
			}		
			StopActionTimer();	
			SaveMissionActionStage();		
		}	
	}
		
	void EnableActionMissionTrigger(){	
		SetSettingALP( alpMISSIONTRIGGER.ENABLED );
		SetSynchDirty();	
	}
	
	void StartManagedMission(PlayerBase player){
		alpMission mission = GetManagedMission();
		if ( mission ) {
			if ( !mission.IsActive() ) {											
				mission.SpawnMission( GetPosition(), GetYawPitchRoll(), alp_MissionManaged );					
			}			
			//check if is private mission
			if ( mission.alp_MissionStarted ) {//private mission			
				if ( IsSetSettingALP( alpMISSIONTRIGGER.ECHO_GET_PLAYERS_NEARBY ) ) {
					array<Object> objects_in_vicinity = new array<Object>;
					array<CargoBase> proxyCargos = new array<CargoBase>;	
					array<PlayerBase> allMans = new array<PlayerBase>;
									
					GetGame().GetObjectsAtPosition3D( GetPosition() , 5 , objects_in_vicinity, proxyCargos );	
					for ( int i = 0; i < objects_in_vicinity.Count(); i++ ){
						PlayerBase man  = PlayerBase.Cast( objects_in_vicinity.Get(i) ) ;						
						if ( man && man.IsPlayer()  ) {
							if ( allMans.Find( man ) == -1 ){
								GetND().GetMS().SendRPC_RegisterMission( man , alp_MissionManaged , mission.alp_MissionStarted );
								allMans.Insert(man);
							}						
						}
					}									
				} else if ( player ) {
					GetND().GetMS().SendRPC_RegisterMission( player , alp_MissionManaged , mission.alp_MissionStarted );
				}											
			}			
		}
	}
	
	protected void DespawnManagedMission(){
		alpMission mission = GetManagedMission();
		
		if ( mission ) {
			if ( mission.IsActive() ) {
				mission.SetSecured();
			}	
		}
	}	
	
	
	alpMission GetParentMission() {
		return GetND().GetMS().GetMission( alp_ParentMission );
	}		
	
		
	void SaveMissionActionStage(){
		//if isPersist
		alpMission mission = GetParentMission();
		if ( mission && IsSetSettingALP( alpMISSIONTRIGGER.ISPERSISTENT ) ) {		
			//check allowed changes
			
			int saved = alp_MissionManage.missionTriggerSetting;						
			if (  !(saved & IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED )) || !(saved & IsSetSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED )) || !(saved & IsSetSettingALP( alpMISSIONTRIGGER.ISDAMAGED )) || !(saved & IsSetSettingALP( alpMISSIONTRIGGER.ISLOCKED ))   ) {//verify changes
				int mask = alpMISSIONTRIGGER.ISACTIVATED | alpMISSIONTRIGGER.ISCOUNTDOWNED | alpMISSIONTRIGGER.ISDAMAGED | alpMISSIONTRIGGER.ISLOCKED;
				saved = saved & (~mask);		 
				saved = saved | IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED ) | IsSetSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED ) | IsSetSettingALP( alpMISSIONTRIGGER.ISDAMAGED )| IsSetSettingALP( alpMISSIONTRIGGER.ISLOCKED );
				alp_MissionManage.missionTriggerSetting = saved;						
				mission.SaveTemplate();				
			}
			
			//alp_MissionManage.missionTriggerSetting = alp_MissionTriggerSetting;
			mission.SaveTemplate();		
		}				
		
		SetSynchDirty();
	}

	void RepairConsoleALP() {
		RemoveSettingALP(  alpMISSIONTRIGGER.ISDAMAGED );
		SaveMissionActionStage();
	}
	
	
	void DownloadData(PlayerBase player){
		int count = 0;
		array<ref alpMission> ms = GetND().GetMS().GetMissionByName( m_DataAboutMission );

		if ( ms ) {
		
			array<PlayerBase> allMans = new array<PlayerBase>;
			allMans.Insert(player);
			if ( IsSetSettingALP( alpMISSIONTRIGGER.ECHO_GET_PLAYERS_NEARBY ) ) {
				array<Object> objects_in_vicinity = new array<Object>;
				array<CargoBase> proxyCargos = new array<CargoBase>;	
											
				GetGame().GetObjectsAtPosition3D( player.GetPosition() , 5 , objects_in_vicinity, proxyCargos );	
				for ( int i = 0; i < objects_in_vicinity.Count(); i++ ){
					PlayerBase man  = PlayerBase.Cast( objects_in_vicinity.Get(i) ) ;						
					if ( man && man.IsPlayer()  ) {
						if ( allMans.Find( man ) == -1 ){						
							allMans.Insert(man);
						}						
					}
				}									
			}
			
			foreach(alpMission m : ms ) {
				if ( m.alp_MissionStarted ) {//private mission
					count++;
					int id = m.GetID();
					int time = m.alp_MissionStarted;		
					foreach(PlayerBase p : allMans) {
						GetND().GetMS().SendRPC_RegisterMission( p , id , time );
					}
				}
			}			
		}	
		
		if ( count ) {
			GetND().GetNotf().SendMissionMessage(  ALPMSTYPE.SMACTIVATE	, alp_MissionManaged , "#alp_action_console_download1" , player.GetPosition(), null, true );	
		} else {
			GetND().GetNotf().SendMissionMessage(  ALPMSTYPE.SMACTIVATE	, alp_MissionManaged , "#alp_action_console_download0" , player.GetPosition(), null, true );	
		}
		
		
	}
	void DeleteData(PlayerBase player){
		GetND().GetNotf().SendMissionMessage(  ALPMSTYPE.SMACTIVATE	, alp_MissionManaged , "#alp_action_console_delete1" , player.GetPosition(), null, true );
		SetSettingALP( alpMISSIONTRIGGER.IS_DATA_DELETED );
		SetSynchDirty();			

	}
}


