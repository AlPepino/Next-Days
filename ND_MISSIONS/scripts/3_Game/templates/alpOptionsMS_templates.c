//Missions template
//----------------------------------------------------------------------------------------------

//client

class alpMissionData
{
	int id;
	int setting;
	bool active;

	vector position;
	int missionRadius;
	
	
	float	strengthOfRadiation;//added
	int missionStarted;
	int startAt;
	int endAt;


	static alpMissionData CompileDataToClient( alpMissionBase mission )
	{	
		alpMissionData data 	= new alpMissionData;
		data.id 				= mission.alp_Id;
		data.setting 			= mission.alp_Setting;
		data.active 			= mission.alp_Active;

		data.position 			= mission.alp_Position;
		data.missionRadius 		= mission.alp_DamageRadius;
		data.strengthOfRadiation = mission.alp_Radiation;
		data.missionStarted 	= mission.alp_MissionStarted;

		data.startAt 			= mission.alp_StartAt;
		data.endAt 				= mission.alp_EndAt;
		return data;		
	}
}

class alpMissionTemplateClient extends alpMissionData
{
	string name;
	int type;
	int requiredLevel;
	int cleanRadius;
	string title;
	
	int		heightOfRadiationArea;
	float	strengthOfRadiationOffset;	//added
	bool enableSineFunction		=	false;//added
	float rainingMultiplyRadiation	=	0;//added
	
	bool sendInfo;	
	bool showInMap;	
	bool showInMapWhenEnter;
	
	float aspectRatioB; 
	
	vector 	safeRadiusPointA;
	vector	safeRadiusPointB;
	
	int countdownBeforeDespawn;
	int timeToFullRadiation;
	
	override static alpMissionTemplateClient CompileDataToClient( alpMissionBase mission )
	{
		alpMissionTemplateClient data = new alpMissionTemplateClient;
		data.id 				= mission.alp_Id;
		data.setting 			= mission.alp_Setting;
		data.name 				= mission.alp_Name;
		data.active 			= mission.alp_Active;
		data.type 				= mission.alp_Type;	
		data.requiredLevel 		= mission.GetTemplate().requiredLevel;	
		data.position 			= mission.alp_Position;
		data.missionRadius 		= mission.alp_DamageRadius;
		data.cleanRadius 		= mission.alp_CleanRadius;		
		data.strengthOfRadiation = mission.alp_Radiation;		
		data.missionStarted 	= mission.alp_MissionStarted;
		//data.countStarted 		= mission.alp_CountStarted;
		data.startAt 			= mission.alp_StartAt;
		data.endAt 				= mission.alp_EndAt;		
		
		data.strengthOfRadiationOffset	= mission.GetTemplate().strengthOfRadiationOffset;
		data.enableSineFunction = mission.GetTemplate().enableSineFunction;	
		data.rainingMultiplyRadiation = mission.GetTemplate().rainingMultiplyRadiation;	

		data.heightOfRadiationArea = mission.GetTemplate().heightOfRadiationArea;	
		
		
		data.title 				= mission.GetTemplate().mapTitle;
		//data.sendInfo 			= mission.GetTemplate().sendInfo;	//useless
		data.showInMap 			= mission.GetTemplate().showInMap;	
		data.showInMapWhenEnter = mission.GetTemplate().showInMapWhenEnter;
		data.aspectRatioB = mission.GetTemplate().aspectRatioB;
		
		data.safeRadiusPointA = mission.alp_SafeRadiusPointA;
		data.safeRadiusPointB = mission.alp_SafeRadiusPointB;
		
		data.countdownBeforeDespawn = mission.GetTemplate().countdownBeforeDespawn;
		data.timeToFullRadiation 	= mission.GetTemplate().timeToFullRadiation;
		
		//Print(" aspect ratio " +  mission.GetTemplate().aspectRatioB + " vector a " +   mission.alp_SafeRadiusPointA );
		return data;
	}	
	
	float GetRadiusMultiplier(){
		float mlt = 1;
		int time;
		int missionTime = alp_ND_base.GetTimeStamp(); //GetGame().GetTime();
		
		if ( timeToFullRadiation && startAt ) {//nastaveni posilovani radiace ze startu
			int fullRad = timeToFullRadiation * 1000;
			time =  startAt + fullRad;
			if ( time > missionTime ) {//ajust
				mlt = ( missionTime - startAt ) / fullRad;
			}
		}
		if ( countdownBeforeDespawn && endAt ) {//zeslabovani radiace 
			int cdtime = countdownBeforeDespawn * 1000;
			time =  missionTime - cdtime;
			
			if ( time <  endAt ) {
				mlt = ( missionTime - endAt ) / cdtime;	
				mlt = 1 - mlt;					
			} else {
				mlt = 0;
			}						
		/*
			int cdtime = countdownBeforeDespawn * 1000;
			time =  endAt + cdtime;
			if ( time > missionTime ) {
				mlt = ( cdtime - ( missionTime - endAt ) ) / cdtime;
			} else {
				mlt = 0;
			}				
		*/
		}
		return mlt;
	}	
}




class alpMissionTemplate 
{

	bool										active;
	string										missionGroup;
	bool										isManaged;
	bool										isActive;
	int											saveMissionStage;	
	int 										nominal;						//max count of this mission in map at once
	int 										lifeTime;						//mission lifeTime
	int 										restock;						//max events for all server LifeTime	
	int 										safeRadius;						//trigger for spawn dynamic AI
	int 										cleanRadius;	
	
	ref array<string>							eventOnStartSpawn;
	ref array<string>							eventOnStartDespawn;
	int											postponeEventOnStart   = 1;
	ref array<string>							eventOnEnterSafeRadiusSpawn;
	ref array<string>							eventOnEnterSafeRadiusDespawn;
	int											postponeEventOnEnterSafeRadius   = 1;		
	ref array<string>							eventOnEndSpawn;
	ref array<string>							eventOnEndDespawn;
	int											postponeEventOnEnd   = 1;	
	ref array<string>							eventOnSecureMissionSpawn;
	ref array<string>							eventOnSecureMissionDespawn;
	int											postponeEventOnSecureMission   = 1;		
	
	bool										isPositionRelativeToMasterMission;
	ref array<ref array<float>> 				position				=	new array<ref array<float>>;	
	int 										positionOffset;
	float										aspectRatioB			= 0; 

	int											timeOffset;	
	
	float										chance;
	ref array<string>							spawnWhenActiveMissions;	
	ref array<string>							spawnWhenDeactiveMissions;	
	int 										distanceRadius;	
	int											missionSafeSpawnRadius;	
	int											conditionPlayers		=	0;	
	int											maxCountVehiclesInGame	= 	0;
	ref array<string> 							vehicleTypes			=	{};		
	bool										spawnInNightOnly;
	bool 										isDeterminedByExactTime = false;	
	string                                      missionStartAt			= "0:0:0";

	string 										missionEndAt			= "0:0:0";
	ref array<string>							despawnWhenActiveMissions;	
	ref array<string>							despawnWhenDeactiveMissions;		
	int											conditionMaxPlayers		=	0;
	int 										countdownBeforeDespawn  = 0;
	int 										countdownDefentArea		= 0;
	bool										lootMustBeTakenOff;
	bool										forceCheckDespawnCondition;	

	int											missionRespawn;	
	int											timeRespawn;		
	bool										aiReinforcement;
	
	bool										isPrivateMission 		= false;
	int 										requiredLevel;
	bool 										showMissionStatus		= false;
	bool 										showNameWhoStartedMission = false;

	bool										showInMap;						//show point in map
	bool										showInMapWhenEnter;				//show point in map only if you enter cleanRadius
	string										mapTitle;						//map title

	bool										sendInfo;						//messages on mission start/end
	string										startMessage;
	string										endMessage;	

	bool										alertInfo				= false;  //messages when you enter/leave safeRadius (damageRadius)
	string										alertMessageIn;
	string										alertMessageOut;	

	bool										pagerInfo				= false;	//messages when you enter/leave cleanRadius
	string										pagerMessageIn;
	string										pagerMessageOut;

	ref array<ref alpMissionAddControlPanel>	controlPanels			= 	new array<ref alpMissionAddControlPanel>;
	ref array<ref alpMissionAddCargo> 			loot					= 	new array<ref alpMissionAddCargo>;
	ref array<ref alpMissionAddVehicle> 		vehicles				= 	new array<ref alpMissionAddVehicle>;
	ref array<ref alpMissionAddSpawn>			structures				= 	new array<ref alpMissionAddSpawn>;	
	
	bool										godmodTrader;
	bool										godmodPlayers;	
	ref array<ref alpMissionAddNPC>				NPC						= 	new array<ref alpMissionAddNPC>;	
	ref array<ref alpMissionAddNPC>				NPCdynamic				= 	new array<ref alpMissionAddNPC>;
	ref array<ref alpMissionAddSpawn>			spawnPlaceForVehicles	= 	new array<ref alpMissionAddSpawn>;	

	bool										radiationSpawnedByContaminedArea =	false;
	int											radiationDynamic		=	0;
	ref array<int>								radiusOfRadiation		=	new ref array<int>;
	int											heightOfRadiationArea	= 	0;	
	bool										enableDeactivation;	
	bool										enableSineFunction		=	false;
	ref array<float>							strengthOfRadiation		=	new ref array<float>;	
	float										strengthOfRadiationOffset;
	int 										timeToFullRadiation  	=	0;
	float										rainingMultiplyRadiation=   0;		
	
	ref array<ref JsonDataContaminatedAreaALP>	contaminedAreas			= 	new array<ref JsonDataContaminatedAreaALP>;	
	ref array<ref JsonDataContaminatedAreaALP>	contaminedAreasDynamic	= 	new array<ref JsonDataContaminatedAreaALP>;	

//	float										conditionCheckTime		=  180;
//	string 										missionDescription;				//not used now
//	string										textInfo;	
	//ref array<ref array<float>> 				positionCopy			=	new array<ref array<float>>;
//	int											visualEffect;
//	int                                         missionCountDown		=	0;
	
}

class JsonDataContaminatedAreaALP 
{
	int positionOffset;
	int timeOffset;
	float chance;
	ref JsonDataContaminatedArea_ALP Area;

}

class JsonDataContaminatedArea_ALP 
{
	string AreaName;
	string Type;
	string TriggerType;
	JsonDataAreaDataALP Data;
	JsonDataPlayerDataALP PlayerData;
};

class JsonDataAreaDataALP 
{
	ref array<float> Pos;
	float Radius;
	float PosHeight;
	float NegHeight;
	int InnerRingCount;
	int InnerPartDist;
	bool OuterRingToggle;
	int OuterPartDist;
	int OuterOffset;
	int VerticalLayers;
	int VerticalOffset;
	string ParticleName; 
};

class JsonDataPlayerDataALP 
{
	string AroundPartName;
	string TinyPartName;
	string PPERequesterType;
}

//missions addon

class alpMissionAddSpawn 
{
	string 					className;
	bool					makeFire = false;
	bool                    noPlaceOnSurface = false;
	bool 					makePersist = false;
	vector 					position;
	float					minH;	
	float  					yaw;
	float					pitch;
	float					roll;

}
class alpMissionAddControlPanel extends alpMissionAddSpawn
{
	string 							managedMission;	
	string							dataAboutMission;
	string 							missionWhileCountdowningON;
	string 							missionWhileCountdowningOFf;		
	int 							missionTriggerSetting;
	int                             missionSwitchCooldown;
	int                             missionAccesCardID;	
	string 							missionActionMessageON;	
	string 							missionActionMessageOFF;
	int 							missionActionGameplayCountdownedON;
	int 							missionActionGameplayCountdownedOFF;	
	string 							countdownMessageON;	
	string 							countdownMessageOFF;		
	
}

class alpMissionAddVehicle 
{
	bool 					makePersist = false;
	bool 					spawnWhenMissionIsSecured;
	string 					title;
	float					chance;
	vector 					position;
	float  					yaw;
	float					pitch;
	float					roll;

}

class alpMissionAddCargo 
{
	string 							className;
	bool 							spawnWhenMissionIsSecured;
	bool							spawnQuestItem = false;	
	bool 							makePersist = false;
	float 							positionOffset;
	float							chance;
	bool							stashed;
	bool                            locked;
	vector 							position;
	float							minH;
	float  							yaw;
	float							pitch;
	float							roll;
	int								lootMaxCount			=  	0;
	ref array<ref alpLootCargo>		cargo 					= 	new array<ref alpLootCargo>;
}

class alpLootCargo 
{
	string	title;
	float   chance;
}

//Missions template end
//----------------------------------------------------------------------------------------------


//vehicles
class alpVehicles 
{
	string 							title;	
	float							chance;
	bool                            locked;	
	float							chanceAttachments;	
	float							chanceFluid;
	float 							minFuelAmount;
	float 							maxFuelAmount;
	ref array<ref array<string>>	items		= new array<ref array<string>>;
	int								lootMaxCount =  0;	
	ref array<ref alpLootCargo>		cargo 		= new array<ref alpLootCargo>;
}

//vehicles end




class alpProtectionItem 
{
	string type;
	float biological;
	float chemical;
	float radiation;
	bool hasdosimeter;			
	float filterefficiency;
};	


//Radiation suit template end
//----------------------------------------------------------------------------------------------


//loot table
class alpLoot 
{
	string 							title;
	string							type;
	float							chance;
	int								quantmin;
	int								quantmax;		
	
	ref array<ref array<string>>	items		= new array<ref array<string>>;
}

//loot table end

//mission AI
//----------------------------------------------------------------------------------------------
class alpMissionAI 
{
	bool								spawned					= false;
	float                               chance;
	string								className;
	string				 				type;
	ref array<int>						nominal					= new array<int>;
	int									restock;
	int									spawnRadius				= 0;
	vector								position;
	int									radius;
	int								lootMaxCount =  0;		
	ref array<ref alpLootCargo>			cargo 					= 	new array<ref alpLootCargo>;
	int									SafeRestock;
	
	void alpMissionAI(){
		SafeRestock=restock;
	}
	
	void Refresh(){
		restock = SafeRestock;
		spawned = false;
	}

}


