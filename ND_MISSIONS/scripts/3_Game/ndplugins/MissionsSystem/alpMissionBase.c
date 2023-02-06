
enum alpMISSION_SETTING
{
	NONE=0,
	MISSION_STATUS=1	
	RADIATION_ACTIVE=2,	
	SAVE_STAGE = 4
	MISSION_IDLE=8, //before someone starts mission
	MISSION_UNSECURED=16,
	MISSION_CLEARED=32,
	MISSION_OCCUPIED=64,
	MISSION_HOSTILE_OCCUPIED=128,
	MISSION_SECURED=256,
	MISSION_EXPIRED=512,
	MISSION_FAILED=1024,
}

enum alpMISSIONTRIGGER{
	ENABLED = 1,
	ISPERSISTENT = 2,						
	ACTIVATION_DESPAWN_MISSION = 4,
	ENABLED_DEACTIVATION = 8,
	ISACTIVATED = 16,//saved
	ISCOUNTDOWNED = 32,//saved
	NOTALIVE_DEACTIVATE = 64;				
	CANBELOCKED = 128,
	ISLOCKED = 256,	
	CANBEDAMAGED = 512,						
	ISDAMAGED = 1024 ,						
	ISRUINED = 2048,						
	ECHO_GET_PLAYERS_NEARBY = 4096,
	SWAP_DEFAULT_TITLE = 8192,	
	CAN_BE_USED_ONCE = 16384,	
	IS_DATA_PANEL = 32768,
	CAN_BE_DATA_DELETED = 65536,	
	IS_DATA_DELETED = 131072,
}

//mission insiders   
//-----------------
class alpMissionInsider
{
	//ref OLinkT 	alp_Insider;
	bool alp_DamageZone 			= false;
	
	protected Object m_Object;

	void alpMissionInsider(Object obj)
	{
		//alp_Insider = new OLinkT(obj);
		m_Object = obj;
	}
	
	Object GetObject()
	{
		return m_Object;//alp_Insider.Ptr();
	}
};

class alpMissionElement
{

	Object m_Item;
	int m_ID;
	bool m_IsPersist;

	void alpMissionElement(Object obj, bool isPersist = false)
	{
		m_Item = obj;
		m_ID = obj.GetID();
		m_IsPersist = isPersist;
	}	
	Object Get(){
		return m_Item;
	}
	int GetID(){
		return m_ID;
	}	
	bool IsPersist(){
		return m_IsPersist;
	}
};

/*
class alpMissionElement
{

	EntityAI m_Item;
	int m_ID;
	bool m_IsPersist;

	void alpMissionElement(EntityAI obj, bool isPersist = false)
	{
		m_Item = obj;
		m_ID = obj.GetID();
		m_IsPersist = isPersist;
	}	
	EntityAI Get(){
		return m_Item;
	}
	int GetID(){
		return m_ID;
	}	
	bool IsPersist(){
		return m_IsPersist;
	}
};
*/
		
class alpMissionOccupied
{
	ref alpMissionBase alp_Mission;
	
	int alp_ClanID;
	string alp_ArmBandType;
	string alp_Name;
	
	void alpMissionOccupied(alpMissionBase m){
		alp_Mission = m;
		ClearFlags();
	}
	
	void VerifyPlayer( int cId, string abType, string name ) {
		if ( IsFirstEntry() ) {
			SetPlayer( cId, abType, name );		
			alp_Mission.SetOccupied(); 
		} else {
			alp_Mission.SetHostileOccupied();			
			if ( ( !alp_ClanID && alp_ArmBandType != "" && alp_ArmBandType == abType ) || ( alp_ClanID && alp_ClanID == cId ) ) {
				alp_Mission.SetOccupied();
			} 
		}
	}
	
	void SetPlayer(int cId, string abType, string name ){
		if ( cId <  0 ) {
			cId = 0;
		}
		alp_ClanID = cId;
		alp_ArmBandType = abType;		
		alp_Name = name;				
	}
	
	void ClearFlags(){
		alp_ClanID = 0;
		alp_ArmBandType = "";	
		alp_Name = "";
	}

	bool IsFirstEntry(){
		return  !alp_Mission.IsOccupied();
	}
}

class alpMissionBase 
{
	ref alpMissionStore 								m_Hive;
	//template 
	//-----------------------------------------------------------------------------------------------------------------------------------------	
	ref alpMissionTemplate								alp_Template;
	//mission variables
	//-----------------------------------------------------------------------------------------------------------------------------------------
	//mission start
	bool 												alp_IsFirstEnter;
	//ref Timer 											alp_MissionProgressTimer;
	
	int													alp_Id;//unique ID mission
	int 												alp_ParendId = -1;//parent id for managing slave missions
	int													alp_Setting;//unique setting
	int													alp_LastSetting;//unique setting
	bool 												alp_LastRadiationSetting;
	bool 												alp_LastEndingSetting;
	string												alp_Name;
    int													alp_Type;	

	
	int 												alp_MissionTime;
	int 												alp_StartOffset;	
		
	vector												alp_Position;//position mission
	vector												alp_Angle;//mission azimut
	float 												alp_MinH;
	
	
	int 												alp_Restock;//-1 disable mission respawn
	int													alp_SafeRadius;	//radius for dynamic AI respawn
	int													alp_DistanceRadius;//mission cant be spawned in this range from another missions
	int													alp_CleanRadius;//radius for enabling mission despawn time
	int													alp_DamageRadius;//using for radiation mission only
		
	float												alp_Radiation;	

	float 												alp_AspectRatioB;
	
	 
	vector 												alp_SafeRadiusPointA;
	vector												alp_SafeRadiusPointB;
	vector 												alp_CleanRadiusPointA;
	vector												alp_CleanRadiusPointB;	
		
		
	//mission managing
	//-----------------------------------------------------------------------------------------------------------------------------------------
	
	ref alpMissionOccupied								alp_OccupiedManagement;
	
	int 												alp_StartTime;//start mise podminka
	int 												alp_EndTime;//konec mise podminka
	
	int 												alp_StartAt;//start mise v case
	int 												alp_EndAt;	//konec mise v case
	
	bool												alp_Active 				= false;
	bool												alp_SpawnInNightOnly	= false;
	bool												alp_WasTouched			= false;
	bool												alp_Touched				= false; //someone in radius
	bool												alp_Deactivated 		= false;
	bool												alp_Permanent			= false;//is mission permanent
	bool												alp_RespawnLoot			= false;//respawning loot in containers?
	
	bool												alp_EventOnEnter		= false;//was run event on enter damage radius
	bool												alp_EventOnSecured		= false;
	//float												alp_TimeLifeCheck 		= 0;//variable for saving timeslice	
	

	float												alp_MissionLifeTime;	
	int 												alp_CountdownDespawn = 0;
	int 												alp_TimeToFullRadiation = 0;
	float												alp_RespawnLootLifeTime;

	int 												alp_MissionStarted;
	
	ref Timer											alp_CreateMissionTimer;

	ref array<ref alpMissionInsider> 					alp_Insiders;//array of objects in misison zone
	
	//managing spawned objects
	//-----------------------------------------------------------------------------------------------------------------------------------------
	
	ref array< ref alpMissionElement>					alp_LootContainer;
	ref array< ref alpMissionElement>					alp_Structures;
	
	ref array<ref alpMissionElement>					alp_ToxicZones;
	ref array<ref JsonDataContaminatedAreaALP>			alp_ContaminedAreas;
	ref array<ref JsonDataContaminatedAreaALP>			alp_ContaminedAreasDynamic;
		
	ref array< ref alpMissionElement>					alp_NPC;
	ref array< ref alpMissionElement>					alp_Vehicles;
	
	
	ref array<ref alpMissionAI>							alp_MissionAI;//input config AI 
	ref array< EntityAI>								alp_StaticAI;
	ref array< EntityAI>								alp_DynamicAI;

	bool												alp_AllNPCspawned;
	
	int 												alp_SpawnRadiusAI;

	bool												alp_AvailableDynamicAI;
	bool												alp_AvailableDynamicInRestockAI;
	bool												alp_AvailableStaticInRestockAI;
	bool												alp_SpawnedStaticAI;
	int													alp_CountAI_static;
	int													alp_CountAI_dynamic;
	int													alp_CountAI_dead_static;
	int													alp_CountAI_dead_dynamic;	

	//messages index
	//-----------------------------------------------------------------------------------------------------------------------------------------
	int													alp_SendInfoStart;
	int													alp_SendInfoEnd;
	int													alp_AlertInfoIn;
	int													alp_AlertInfoOut;
	int													alp_PagerInfoIn;
	int													alp_PagerInfoOut;
	
	
	
	void alpMissionBase(int id , string name, int missionType, alpMissionTemplate template)
	{
		alp_Id 				= id;
		alp_Name 			= name;
		alp_Type 			= missionType;

		alp_Template		= template;
		
		alp_Restock			= GetTemplate().restock;
		
		
		//start time 
		int startH,startM,startS;
		int endH,endM,endS;
		string timeText;
		
		array<string> cas = new array<string>;
		if ( GetTemplate().missionStartAt != "" ){
			timeText =  GetTemplate().missionStartAt;
			timeText.Split( ":", cas );
			if ( cas && cas.Count() == 3 ) {
				startH = cas.Get(0).ToInt();
				startM = cas.Get(1).ToInt();
				startS = cas.Get(2).ToInt();
			} 
		}
		if ( GetTemplate().missionEndAt != "" ){
			timeText =  GetTemplate().missionEndAt;
			timeText.Split( ":", cas );
			if ( cas && cas.Count() == 3 ) {
				endH = cas.Get(0).ToInt();
				endM = cas.Get(1).ToInt();
				endS = cas.Get(2).ToInt();
			} 				
		}						
		
		alp_StartTime   	= startH * 3600 + startM * 60 + startS;
		alp_EndTime 		= endH * 3600 + endM * 60 + endS;
		
		alp_SpawnInNightOnly= GetTemplate().spawnInNightOnly;
						
		alp_CleanRadius		= GetTemplate().cleanRadius;
		alp_SafeRadius 		= GetTemplate().safeRadius;
		alp_AspectRatioB 	= GetTemplate().aspectRatioB;
		alp_DamageRadius 	= alp_SafeRadius;		
	
		alp_StartOffset		= GetTemplate().timeOffset;
		
		alp_SendInfoStart	= ALPMSTYPE.MMMISSIONSTART;
		alp_SendInfoEnd		= ALPMSTYPE.MMMISSIONEND;
		alp_AlertInfoIn		= ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut	= ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn		= ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut	= ALPMSTYPE.MMPERSONAL;
		
		alp_ContaminedAreas = GetTemplate().contaminedAreas;	
		alp_ContaminedAreasDynamic = GetTemplate().contaminedAreasDynamic;		
		
		alp_OccupiedManagement = new alpMissionOccupied(this);
		
		alp_CountdownDespawn	= GetTemplate().countdownBeforeDespawn * 1000;
		alp_TimeToFullRadiation = GetTemplate().timeToFullRadiation * 1000;
		
		if (GetGame().IsServer())
		{						
			//alp_MissionProgressTimer = new Timer(CALL_CATEGORY_GAMEPLAY);
			
			//get Mission AI
			alp_MissionAI 			= new array<ref alpMissionAI>;
			string nameFile 		= ALP_MISSIONS_FOLDER  + GetName() + "_AI.json";
			JsonFileLoader<array <ref alpMissionAI>>.JsonLoadFile( nameFile, alp_MissionAI );	
						
		}
		
		OnInit();
	}	
	
	void ~alpMissionBase()
	{
		delete alp_Insiders;
		delete alp_LootContainer;
		delete alp_Structures;
		delete alp_ToxicZones;
		delete alp_ContaminedAreas;
		delete alp_ContaminedAreasDynamic;
		delete alp_NPC;
		delete alp_Vehicles;
		delete alp_MissionAI;
		delete alp_StaticAI;
		delete alp_DynamicAI;
		
		delete alp_OccupiedManagement;

		/*
		if ( alp_MissionProgressTimer ){
			if ( alp_MissionProgressTimer.IsRunning() ){
				alp_MissionProgressTimer.Stop();	
			}
			delete alp_MissionProgressTimer;
		}
		*/
		
	}
	
	
	void SaveTemplate(){
		JsonFileLoader<alpMissionTemplate>.JsonSaveFile( ALP_MISSIONS_FOLDER + alp_Name + ".json", alp_Template );	
	}
	
	
	void VerifyPlayer(int cId, string abType, string name ){
		if ( alp_OccupiedManagement ) {
			alp_OccupiedManagement.VerifyPlayer( cId, abType, name );
		}
	}
	
	void EstimateSides(){
		if ( alp_AspectRatioB ) {
			float a,b;
			
			//safe radius;
			int safeRadius;
			if ( GetGame().IsServer() ) {
				safeRadius = alp_SafeRadius;
			} else {
				safeRadius = alp_DamageRadius;
			}
			a = GetSideA( safeRadius );
			b = a * alp_AspectRatioB;
			
			a = a / 2;
			b = b / 2;
			
			alp_SafeRadiusPointA[0] = alp_Position[0] + a;
			alp_SafeRadiusPointA[1] = alp_Position[1];
			alp_SafeRadiusPointA[2] = alp_Position[2] + b;
			alp_SafeRadiusPointB[0] = alp_Position[0] - a;
			alp_SafeRadiusPointB[1] = alp_Position[1];
			alp_SafeRadiusPointB[2] = alp_Position[2] - b;			

			//Print("Vektor A " + alp_SafeRadiusPointA );
			//Print("Vektor B " + alp_SafeRadiusPointB );
			
			//clean radius;
			//if ( GetGame().IsServer() ){
				a = GetSideA( alp_CleanRadius );
				b = a * alp_AspectRatioB;
				
				a = a / 2;
				b = b / 2;
				
				alp_CleanRadiusPointA[0] = alp_Position[0] + a;
				alp_CleanRadiusPointA[1] = alp_Position[1];
				alp_CleanRadiusPointA[2] = alp_Position[2] + b;
				alp_CleanRadiusPointB[0] = alp_Position[0] - a;
				alp_CleanRadiusPointB[1] = alp_Position[1];
				alp_CleanRadiusPointB[2] = alp_Position[2] - b;			
				
				//Print("Vektor A " + alp_CleanRadiusPointA );
				//Print("Vektor B " + alp_CleanRadiusPointB );			
			//}
			
		}
	}
	
	protected float GetSideA(float radius){
		radius = Math.Pow(radius, 2);
		
		float a = radius / ( 1 + Math.Pow( alp_AspectRatioB , 2 ) );
		
		a = Math.Pow( a , 0.5 );
		return a;
	}	
	
	protected void OnInit()
	{};	
	
	void SetSetting(int setting)
	{
		alp_Setting = (alp_Setting | setting); 
	}
	void RemoveSetting(int setting)
	{
		if (IsSetSetting(setting ))
		{
			alp_Setting = ~setting & alp_Setting;
		}
	}
	
	bool IsRadioactive()
	{
		return alp_Setting & alpMISSION_SETTING.RADIATION_ACTIVE;
	}
	

	bool IsSetSetting(int setting )
	{
		return alp_Setting & setting;
	}

	void SetExpired(){		
		//RemoveSetting( alpMISSION_SETTING.MISSION_UNSECURED | alpMISSION_SETTING.MISSION_CLEARED | alpMISSION_SETTING.MISSION_OCCUPIED);
		SetSetting( alpMISSION_SETTING.MISSION_EXPIRED );
		if ( GetTemplate().saveMissionStage ){
			SaveMissionStage();	
		}	
	}	
	
	void SetFailed(){
		//RemoveSetting( alpMISSION_SETTING.MISSION_UNSECURED | alpMISSION_SETTING.MISSION_CLEARED | alpMISSION_SETTING.MISSION_OCCUPIED);
		SetSetting( alpMISSION_SETTING.MISSION_FAILED );
		if ( GetTemplate().saveMissionStage ){
			SaveMissionStage();	
		}	
	}		
	void SetSecured(){		
		//RemoveSetting( alpMISSION_SETTING.MISSION_UNSECURED | alpMISSION_SETTING.MISSION_CLEARED | alpMISSION_SETTING.MISSION_OCCUPIED);
		SetSetting( alpMISSION_SETTING.MISSION_SECURED );
		if ( GetTemplate().saveMissionStage ){
			SaveMissionStage();	
		}			
	}			
	void SetUnsecured(){
		RemoveSetting( alpMISSION_SETTING.MISSION_CLEARED );
		SetSetting( alpMISSION_SETTING.MISSION_UNSECURED );		
		
		if ( GetTemplate().saveMissionStage ){
			SaveMissionStage();	
		}			
	}
	void SetCleared(){
		RemoveSetting( alpMISSION_SETTING.MISSION_UNSECURED );
		SetSetting( alpMISSION_SETTING.MISSION_CLEARED );	
		
		if ( GetTemplate().saveMissionStage ){
			SaveMissionStage();	
		}			
	}
	
	void RemoveOccupied(){
		RemoveSetting( alpMISSION_SETTING.MISSION_OCCUPIED );
		RemoveSetting( alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED );
	}
	
	void SetOccupied(){
		RemoveSetting( alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED );
		SetSetting( alpMISSION_SETTING.MISSION_OCCUPIED );			
	}
	void SetHostileOccupied(){
		RemoveSetting( alpMISSION_SETTING.MISSION_OCCUPIED );
		SetSetting( alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED );			
	}	
	bool IsOccupied(){
		return alp_Setting & alpMISSION_SETTING.MISSION_OCCUPIED || alp_Setting & alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED;
	}
	
	bool IsCleared() {
		return IsSetSetting( alpMISSION_SETTING.MISSION_CLEARED );
	}
	
	
	void CreateMission()
	{
		
		
		if ( GetTemplate().isManaged )//is managed by master mission
			return;
		
				
		if ( alp_Restock < 0 )//no infinity mission restock any more;
			return;				
				
		int offset = GetOffsetedMissionSpawn();	//offset mission spawn, after first init is set to 0
		if ( GetTemplate().isDeterminedByExactTime ){
			int current = GetCurrentTime(); 	
			int startTime = Math.AbsInt( alp_StartTime - current );
			
			if ( current < alp_StartTime ) {
				startTime = ( 24 * 3600 - 1) - startTime;
			} 

			RespawnMission( startTime + offset );
			
		} else if (  offset > 0 ) {
			RespawnMission( offset );	
		} else 
		{
			if ( !MeetsPlayersCondition() || !GetSpawnChance() || !CanBeSpawned() )//if all condition are not OK then pospone SpawnMission
			{
				RespawnMission( GetMissionRespawnTime() );
			}
			else
			{
				SpawnMission();
			}
		}	
	}

		
	int GetCurrentTime(){
		return 0;
	}
	
	protected void RespawnMission(int offset = 0)
	{
		if (offset > 0 )
		{	
			if ( !alp_CreateMissionTimer )
			{
				alp_CreateMissionTimer = new Timer(CALL_CATEGORY_GAMEPLAY);
				alp_CreateMissionTimer.Run(offset  ,this,"CreateMission",NULL,false);
			}
			else 
			{
				alp_CreateMissionTimer.Run(offset ,this,"CreateMission",NULL,false);	
			}		
		}
	}		
	
	
	int GetID()
	{
		return alp_Id;
	}
	int GetParentID(){
		return alp_ParendId;
	}
	void SetParentID(int id){
		alp_ParendId = id;
	}
	
	string GetName()
	{
		return alp_Name;
	}	
	
	int GetType()
	{
		return alp_Type;
	}
	
	vector GetPosition()
	{
		return alp_Position;
	}	
	
	vector GetAngle()
	{
		return alp_Angle;
	}	
	
	int GetCleanRadius() 
	{
		return alp_CleanRadius;
	}	
	
	int GetSafeRadius()
	{
		return alp_SafeRadius;
	}

	int GetDamageRadius()
	{
		return alp_DamageRadius;
	}
	
	bool IsActive()
	{
		return alp_Active;
	}
	
	bool IsLootRespawnEnabled()
	{
		return alp_RespawnLoot;
	}	
	
	bool IsAvailableDynamicAI()
	{
		return alp_AvailableDynamicAI && !IsMissionEnded();
	}
	
	bool IsAvailableRestockAI(){
		return alp_AvailableDynamicInRestockAI | alp_AvailableStaticInRestockAI;	
	}
	
	
	bool IsNotAavailableAnyAI(){
		return !IsAvailableDynamicAI() && !IsAvailableRestockAI() && !alp_StaticAI.Count() && !alp_DynamicAI.Count();
	}
	
	bool IsMissionEnded(){
		return ( alp_Setting & alpMISSION_SETTING.MISSION_SECURED ||  alp_Setting & alpMISSION_SETTING.MISSION_EXPIRED || alp_Setting & alpMISSION_SETTING.MISSION_FAILED );
	}

	bool IsCountdownExpired(float timeslice){
		if ( alp_CountdownDespawn ) {
			int time =  alp_EndAt + alp_CountdownDespawn;
			if ( time < alp_MissionTime ) {
				return true;
			}
			return false;
		}
		return true;
	}
	
	bool IsAreaClear()
	{
		return !alp_Touched;
	}
	
	bool IsPermanent()
	{
		return alp_Permanent;
	}
	
	void ClientLeftArea (bool state)
	{
		alp_Touched			= !state;	
	}	
	alpMissionTemplate GetTemplate()
	{
		return alp_Template;
	}


	protected bool GetSpawnChance()
	{
		return ( GetTemplate().chance >= Math.RandomFloat01() );
	}
	
	protected int GetOffsetedMissionSpawn()
	{
		int offset = alp_StartOffset;
		alp_StartOffset = 0;
		return offset;
	}
	
	protected bool CanBeSpawned()
	{
		if (!alp_SpawnInNightOnly)
			return true;
		else
		{
			bool isNight = GetGame().GetWorld().IsNight();
			
			if (isNight)
				return true;
			else
			{//override check time for spawning
				return false;		
			}
		}	
	}	
	



	bool MeetsPlayersCondition()
	{
		int conditionMin = GetTemplate().conditionPlayers;
		int conditionMax = GetTemplate().conditionMaxPlayers;
		
		if ( !conditionMin && !conditionMax )
		{
			return true;
		}
		int playersCount = GetPlayersCount();
		if ( conditionMin &&  conditionMax)
		{
			if (playersCount >= conditionMin && playersCount <= conditionMax)
			{
				return true;
			}		
		}
		else if ( conditionMin)
		{
			if (playersCount >= conditionMin)
			{
				return true;
			}	
		}
		else if ( conditionMax)
		{
			if (playersCount <= conditionMax)
			{
				return true;
			}	
		}

		return false;
		
		
	}
	
	protected int GetPlayersCount()
	{
		int countPlayers = 0;
		private array<Man> 	players 	= new array<Man>;
		GetGame().GetPlayers( players );			
		countPlayers = players.Count();		
		
		return countPlayers;
	}

	float GetMissionRespawnTime()
	{
		float respawnTime = GetTemplate().missionRespawn;
		bool isNight = GetGame().GetWorld().IsNight();
		
		if (alp_SpawnInNightOnly && !isNight )
		{
			respawnTime = 30;
		}
		if ( GetTemplate().spawnWhenActiveMissions.Count() || GetTemplate().spawnWhenDeactiveMissions.Count() ) {
			respawnTime =  Math.Clamp(respawnTime, 3 ,86400);
		}
				
		return  respawnTime;
	}			
	
	alpMissionBase SpawnMission(vector pos = "0 0 0", vector angle = "0 0 0", int parentID = -1 ){
		return null;
	}
	
	void ManageMission(float timeslice){}
	
	void DespawnMission(){}	
	
	protected void SaveMissionStage(){
		/*
		int flags = alp_Setting;
		if ( IsMissionEnded() ) {
			flags = 0;
			flags = flags | alpMISSION_SETTING.SAVE_STAGE;
		} 
		*/
		m_Hive.UpdateSetting(alp_Setting);
		alpMHIVE.Save();
	}	
	
	protected bool IsNPCAlive()
	{
		if (!alp_AllNPCspawned){
			return true;		
		}
		bool someLive = false;

		for (int i = 0; i < alp_NPC.Count(); ){
			alpMissionElement e = alp_NPC.Get(i);
			if ( e.Get() && e.Get().IsAlive() ) {	
				someLive = true;					
			} else {
				int id = e.GetID();	
				m_Hive.RemoveNPC(id);				
				alp_NPC.Remove(i);
				continue;				
			}			
			i++;
		}		
		return someLive;
	}		
	
}