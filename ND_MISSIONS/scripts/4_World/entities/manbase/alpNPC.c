// Script File

enum alpPAY_METHODS
{
	CASH,
	BANK,
	BANK_ONLY,
}

enum alpNPC_AVAILABLE_MENU
{
	ALL,
	BUY,
	SELL,
	BANK=4,
	MEDICAL=8,
	SPREADRUMOURS=16,
	BANK_ONLY=32,
	START_MISSION=64,//notused
}


class alpNPC : PlayerBase
{
	//const int ALP_NOT_ACTIVE = - 1;
	string 							m_MissionWhileCountdowningON;
	string 							m_MissionWhileCountdowningOFf;	 	
	
	int alp_ParentMission;
	ref alpMissionAddNPC			alp_MissionManage;
	int 							alp_MissionTriggerSetting;
	int 							alp_MissionManaged;
	int 							alp_MissionSwitchCooldown;

	int 							alp_MissionActionGameplayCountdownedON;;
	int 							alp_MissionActionGameplayCountdownedOFF;
	
	string 							alp_CountdownMessageON;	
	string 							alp_CountdownMessageOFF;		
	
	string 							alp_MissionActionMessageON;	
	string 							alp_MissionActionMessageOFF;
	string						    alp_GiveItemWhenActivate;
	bool                            alp_RewardWasGiven;
	
	
	int 							alp_StockID	 			= 0;
	ref array<int>					alp_QuestsID;	
	ref array<int>  				alp_ActiveQuestsID; 	
	ref map<int,int>				alp_ActiveQuestsTimeStamp;
	int 							m_AllowedQuestsAtOnce;

	int 							alp_IDmission	 		= 0;

	

	int 							alp_TimeOffset			= 60000;//300000; //1 minutu

	ref Timer  						alp_ActionTimer;
	
	bool 							alp_CanRunMission;
	
	int                             m_CurrencyFromMissionTemplate;
	
	bool 							m_ActivatedByPlayer;

	override void InitALP(){			
		RegisterNetSyncVariableInt("alp_StockID");
		RegisterNetSyncVariableBool("alp_CanRunMission");		
		RegisterNetSyncVariableInt("alp_MissionTriggerSetting");
		RegisterNetSyncVariableInt("alp_MissionManaged");
		
		if ( GetGame().IsServer() ){
			alp_ActiveQuestsID = new array<int>;	
			alp_ActiveQuestsTimeStamp = new map<int,int>;
			
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.InitNPCquests,100);		
		}	
	}
	
	void ~alpNPC(){
		if (GetGame() && GetGame().IsServer() && GetGame().IsMultiplayer() ) {					
			FinishNPCQuests();
		}		
	}

	bool HasActiveQuest()
	{
		return alp_ActiveQuestsID.Count() > 0;
	}
	
	void InitNPCquests()
	{
		if ( alp_StockID )
		{
			alp_QuestsID = GetND().GetMS().GetMappedQuests( alp_StockID );

			if ( alp_QuestsID &&  alp_QuestsID.Count() > 0 )
			{

				TryToSetQuest();			
					
			}
			
		}
			
	}
	
	bool CanMakeAnotherQuest(){
		return alp_ActiveQuestsID.Count() < m_AllowedQuestsAtOnce;
	}
	
	void TryToSetQuest()
	{

		if  ( CanMakeAnotherQuest() && GetND().GetMS().IsPossibleSetQuest()  )
		{
			//Print("POKUS SPAWNU, pocet misi " + alp_QuestsID.Count() + ", trader " + alp_StockID );					
			
			int time = GetGame().GetTime();
			
			foreach( int id : alp_QuestsID )
			{
				if ( GetND().GetMS().IsActiveQuest(id) ) {
					continue;
				}
				
				//Print(id);
				alpTraderQuest quest = GetND().GetMS().GetQuest(id);			
				if (quest )
				{
					//Print("POKUS SPAWNU MISE " + quest.MapTitle + ", trader " + alp_StockID );
					int coolDown = quest.LastRun;
					if ( ( quest.Nominal == - 1 || quest.Nominal > 0 ) && time > coolDown )
					{//first conidtion
						if ( quest.Chance >= Math.RandomFloat01() )
						{//second condition		
							int currency = GetCurrencyID();		
							if (  GetND().GetMS().RegisterQuest( alp_StockID, id , GetPosition(), currency ) )
							{//third condition
								
								if (quest.AssociatedMission != "" )
								{//fourth condition
									if (! StartAssociatedMission( quest.AssociatedMission ,id, quest.WantedItem ) ){
										continue;
									}
								}
								//start mission
								if ( quest.Nominal > 0 )
								{
									quest.Nominal--;
								}
								alp_ActiveQuestsID.Insert(id);
								alp_ActiveQuestsTimeStamp.Set(id,time);

								quest.LastRun = time  + ( quest.CoolDown * 1000 );										
								//repeat start Message
								int repeat = quest.RepeatStartMessageEvery * 1000;										
								SendStartMessage( id, time  , repeat );
								
								int lifeTime = quest.LifeTime;									
								if ( lifeTime )
								{
									lifeTime *= 1000; 
									GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.FinishNPCquest,lifeTime,false,id);		
								}								
							}
						}						
					}						
				}					
			}			
		}
		int offset = alp_TimeOffset + 5000 * Math.AbsInt(alp_StockID);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.TryToSetQuest,offset);					
				 
	}
	
	bool StartAssociatedMission(string name, int qid, string wantedItem )
	{
		
		array<ref alpMission> missions;
		missions = GetND().GetMS().GetMissionByName( name );

		if ( missions )
		{

			foreach (alpMission mission : missions )
			{
				if ( !mission.IsActive() )
				{
					//Print("Registrace NPC "  + GetID() );
					
					mission.SetQuestMissions( GetID(), qid, wantedItem );
					
					
					if ( mission.SpawnMission() ){
						return true;
					}

				}
				
			}
		}
		return false;
	}
	void CloseAssociatedMission(string name , int qid)
	{
		
		array<ref alpMission> missions;
		missions = GetND().GetMS().GetMissionByName( name );
		
		if ( missions )
		{
			foreach (alpMission mission : missions )
			{
				if ( mission.IsActive() && mission.GetRegisteredNPC() == GetID() &&  mission.GetQuestID() == qid )
				{
					mission.DespawnMission();
					break;
				}
				
			}
		}
	}	
	
	void SendStartMessage(int quesID, int time , int tick = 0 )
	{

		if ( IsQuestRunning( quesID , time ) )
		{
			GetND().GetNotf().SendQuestMessage(	alp_StockID, quesID );
			if ( tick )
			{
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SendStartMessage,tick,false,quesID,time,tick);	
			}			
		}
	}
	
	bool IsQuestRunning(int id , int time) {
		int find;
		if ( alp_ActiveQuestsTimeStamp.Find(id,find) && time == find ){
			return true;
		}
		return false;
	}
	
	void SendEndMessage(int quest)
	{
		GetND().GetNotf().SendQuestMessage(	alp_StockID, quest,2 );
	}		
	/*
	void UnregisterQuest()
	{
		GetND().GetMS().UnRegisterQuest( alp_StockID );	
		
		int offset = alp_TimeOffset + 1000 * alp_StockID;
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.TryToSetQuest,offset);			
	}
	*/
	void FinishNPCQuests(){
		for (int i = 0; i < alp_ActiveQuestsID.Count();){
			FinishNPCquest( alp_ActiveQuestsID.Get(i));
		}			
	}
	
	void FinishNPCquest(int id){
	
		alpTraderQuest quest = GetND().GetMS().GetQuest(id);	
		if (quest) {		
			//increase cooldown
			int time = GetGame().GetTime();
			quest.LastRun = time  + ( quest.CoolDown * 1000 );	
			
			if (quest.AssociatedMission != "" )
			{
				CloseAssociatedMission( quest.AssociatedMission, id );
			}	
			alp_ActiveQuestsID.RemoveItem(id);
			SendEndMessage(id);	
			GetND().GetMS().UnRegisterQuest( alp_StockID, id );
		}					
	}
		
	
	override bool IsPlayer()
	{
		return false;

	}	
	
	bool CanSellingALP()
	{
		if ( alp_StockID > 0 )
		{
			alpNPCtraderStock stock = alpTraderCoreBase.alp_TraderStockMapped.Get( alp_StockID );
			if ( stock )
			{
				bool setting = stock.EnabledInteractions;
				
				return setting & alpNPC_AVAILABLE_MENU.SELL;			
			}
			return false;

		}
		return false;	
	}	
	bool CanBuingALP()
	{
		if ( alp_StockID > 0 )
		{
			alpNPCtraderStock stock = alpTraderCoreBase.alp_TraderStockMapped.Get( alp_StockID );
			if ( stock )
			{
				bool setting = stock.EnabledInteractions;
				
				return setting & alpNPC_AVAILABLE_MENU.BUY;			
			}
			return false;

		}
		return false;
	}			
	
	
	
	bool CanSpreadRumoursMenu()
	{
		if ( alp_StockID > 0 )
		{
			alpNPCtraderStock stock = alpTraderCoreBase.alp_TraderStockMapped.Get( alp_StockID );
			if ( stock )
			{
				bool setting = stock.EnabledInteractions;
				
				return setting & alpNPC_AVAILABLE_MENU.SPREADRUMOURS;			
			}
			return false;

		}
		return false;	
	}
	
	int GetCurrencyID()
	{
		if ( alp_StockID < 0 ) {		
			return m_CurrencyFromMissionTemplate;
		}
		
		
		
		
		if ( alp_StockID > 0 )
		{
			alpNPCtraderStock stock = alpTraderCoreBase.alp_TraderStockMapped.Get( alp_StockID );
			if ( stock )
			{
				return stock.CurrencyID;		
			}
			return -1;

		}
		return -1;		
	}	
	
	
	bool CanSpeakWithMe(PlayerBase player)
	{
		return true;
	}
	
	
	
	
	override void EEKilled( Object killer ){
		super.EEKilled( killer );
		
		if ( IsEnabledReverseModWhenKilled() ) {
			if ( IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) {
				StartManagedMission(null);	
			} else {
				DespawnManagedMission();
			}
		}
		
		FinishNPCQuests();
	}		























	
//-------------------------	
//MANAGE MISSION (TRIGGER) -  methods
//------------------------
	void SetMissionManage(alpMissionAddNPC control , int parentMission ){
		alp_ParentMission = parentMission;		
		alp_MissionManage = control;	
		m_MissionWhileCountdowningON = control.missionWhileCountdowningON;	
		m_MissionWhileCountdowningOFf = control.missionWhileCountdowningOFf;			
		alp_MissionTriggerSetting 	=  control.missionTriggerSetting;		
		alp_MissionSwitchCooldown 	=  control.missionSwitchCooldown;					
		alp_MissionActionGameplayCountdownedON 	=  control.missionActionGameplayCountdownedON;
		alp_MissionActionGameplayCountdownedOFF	=  control.missionActionGameplayCountdownedOFF;			
		alp_CountdownMessageON 					=  control.countdownMessageON;
		alp_CountdownMessageOFF 				=  control.countdownMessageOFF;
		alp_MissionActionMessageON 				=  control.missionActionMessageON;
		alp_MissionActionMessageOFF 			=  control.missionActionMessageOFF;	
		alp_GiveItemWhenActivate				=  control.giveItemWhenActivate;
		InitMissionStage();
	}	
	protected void InitMissionStage() {		
		alpMission mission = GetManagedMission();
		if ( mission && alp_MissionTriggerSetting && IsSetSettingALP( alpMISSIONTRIGGER.ENABLED ) && !IsRuinedALP() ) {			
			if ( IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED ) ) {
				if ( !IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) {
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(StartManagedMission,100,false,  null );//due to start INIT
				} else {						
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DespawnManagedMission,100);//due to start INIT
				}								
				if ( IsSetSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED ) ){//prepare to deactivate
					SetTimerToAction( alpMMACTION.SET_TIME_TO_DEACTIVE );	
				} 
			} else {
				if ( !IsSetSettingALP( alpMISSIONTRIGGER.ACTIVATION_DESPAWN_MISSION ) ) {					
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DespawnManagedMission,100);//due to start INIT
				} else {						
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
				GetND().GetNotf().SendMissionMessage(  ALPMSTYPE.SMPERSONAL	, alp_MissionManaged , alp_MissionActionMessageON , GetPosition(), null, true );
			}
			if ( ( type == alpMMACTION.DEACTIVE || type == alpMMACTION.SET_TIME_TO_DEACTIVE || type == alpMMACTION.CANCEL_ACTIVE_TIME ) && alp_MissionActionMessageOFF !="" )  {
				GetND().GetNotf().SendMissionMessage(  ALPMSTYPE.SMPERSONAL	, alp_MissionManaged , alp_MissionActionMessageOFF , GetPosition(), null, true );
			}	
			SaveMissionActionStage();
		}
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
			if ( remainingTime  > 3600 ) {//above one hour
				afterDiv = remainingTime % 900;	 //every 15 min message
			} else if ( remainingTime  > 600 ){//above 10 min
				afterDiv = remainingTime % 300;//every 5 min message
			} else if ( remainingTime  > 60 ){//above 1 min 
				afterDiv = remainingTime % 60;//every 1 min message
			} else {//under 1 min
				afterDiv = remainingTime % 20;//every 20s message
			}
			if ( !afterDiv && message != ""  ){//send message
				min = remainingTime % 3600;
				hour = ( remainingTime - min ) / 3600;
				sec = min % 60;
				min = min - sec;			
				if ( hour )
					messageTime	= hour.ToString() + "h ";				
				if ( min ) 
					messageTime	= min.ToString() + "m ";				
				if ( sec || ( !hour && !min ) ) 
					messageTime	= sec.ToString() + "s";				
				message += " (T - " + messageTime + ")";
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
	void StopActionTimer() {
		if ( m_MissionWhileCD ) {
			m_MissionWhileCD.SetSecured();
			m_MissionWhileCD = null;
		}
		alp_TimerStamp = 0;
		if (alp_ActionTimer && alp_ActionTimer.IsRunning() ) {
			alp_ActionTimer.Stop();
			alp_ActionTimer = NULL;
		}
		RemoveSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED  );
	}			
	void SaveMissionActionStage(){
		//if isPersist
		alpMission mission = GetParentMission();
		if ( mission && IsSetSettingALP( alpMISSIONTRIGGER.ISPERSISTENT ) ) {		
			//check allowed changes
			
			int saved = alp_MissionManage.missionTriggerSetting;						
			if (  !(saved & IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED )) || !(saved & IsSetSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED )) ) {//verify changes
				int mask = alpMISSIONTRIGGER.ISACTIVATED | alpMISSIONTRIGGER.ISCOUNTDOWNED;
				saved = saved & (~mask);		 
				saved = saved | IsSetSettingALP( alpMISSIONTRIGGER.ISACTIVATED ) | IsSetSettingALP( alpMISSIONTRIGGER.ISCOUNTDOWNED );
				alp_MissionManage.missionTriggerSetting = saved;						
				mission.SaveTemplate();				
			}
			
			//alp_MissionManage.missionTriggerSetting = alp_MissionTriggerSetting;
			mission.SaveTemplate();		
		}					
		SetSynchDirty();
	}	
	alpMission GetParentMission() {
		return GetND().GetMS().GetMission( alp_ParentMission );
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
	void EnableActionMissionTrigger(){	
			SetSettingALP( alpMISSIONTRIGGER.ENABLED );
			SetSynchDirty();		
	}	
	bool IsEnabledReverseModWhenKilled(){
		if ( alp_MissionTriggerSetting && IsSetSettingALP( alpMISSIONTRIGGER.NOTALIVE_DEACTIVATE | alpMISSIONTRIGGER.ISACTIVATED ) ) {
			return true;
		}
		return false;
	}
	bool IsSetSettingALP(int setting ){
		return alp_MissionTriggerSetting & setting;
	}
	bool IsDamagedALP(){
		return false;	
	}
	bool IsRuinedALP(){
		return false;	
	}			
	bool IsSwapedActionTitle(){
		return IsSetSettingALP( alpMISSIONTRIGGER.SWAP_DEFAULT_TITLE );
	}
//-------------------------	
//MANAGE MISSION (TRIGGER) -  methods (END)
//------------------------
	
}



class alp_SurvivorM_Denis extends alpNPC{
}
class alp_SurvivorM_Mirek extends alpNPC{
}
class alp_SurvivorM_Boris extends alpNPC{
}
class alp_SurvivorM_Cyril extends alpNPC{
}
class alp_SurvivorM_Elias extends alpNPC{
}
class alp_SurvivorM_Francis extends alpNPC{
}
class alp_SurvivorM_Guo extends alpNPC{
}
class alp_SurvivorM_Hassan extends alpNPC{
}
class alp_SurvivorM_Indar extends alpNPC{
}
class alp_SurvivorM_Jose extends alpNPC{
}
class alp_SurvivorM_Kaito extends alpNPC{
}
class alp_SurvivorM_Lewis extends alpNPC{
}
class alp_SurvivorM_Manua extends alpNPC{
}
class alp_SurvivorM_Niki extends alpNPC{
}
class alp_SurvivorM_Oliver extends alpNPC{
}
class alp_SurvivorM_Peter extends alpNPC{
}
class alp_SurvivorM_Quinn extends alpNPC{
}
class alp_SurvivorM_Rolf extends alpNPC{
}
class alp_SurvivorM_Seth extends alpNPC{
}
class alp_SurvivorM_Taiki extends alpNPC{
}
class alp_SurvivorF_Eva extends alpNPC{
}
class alp_SurvivorF_Frida extends alpNPC{
}
class alp_SurvivorF_Gabi extends alpNPC{
}
class alp_SurvivorF_Helga extends alpNPC{
}
class alp_SurvivorF_Judy extends alpNPC{
}
class alp_SurvivorF_Keiko extends alpNPC{
}
class alp_SurvivorF_Linda extends alpNPC{
}
class alp_SurvivorF_Maria extends alpNPC{
}
class alp_SurvivorF_Naomi extends alpNPC{
}

