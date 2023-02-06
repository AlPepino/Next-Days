class alpMSoptions 
{
	bool ShowRealPlayerName								= true;
	bool RequiresWalkieTalkie							= true;//enable/disable requirement of WalkieTalkie to pop up mission messages and player's position on map
	bool BaseRadioUncoverAllMissions					= true;
	float RequiredTunedFrequency						= 0;
	bool ShowPlayersOnMap								= false;//show markers on map if RequiresWalkieTalkie == false || RequiresWalkieTalkie == true && Player has working WalkieTalkie	
	bool SetMapPositionToPlayer							= false;
	bool ShowMissionRadius								= true;
	string LabelOfSafeZone 								= "";
	bool DamageSpawnedVehiclesInMission					= true;	
	bool DeleteDeadMissionAI							= true;
	bool DeleteAliveMissionAI							= false;
	float AllowedRatioAliveMissionAI					= 0.1;

	
	bool EnableSafePosition								= false;
	bool UseDefaultSafePosition							= false;
	ref array<ref array<float>> SafePositions			={};
	
	ref array<vector> ArtilleryPositions				= {"-500.00 165.00 5231.69",
		"-500.00 300.00 9934.41",
		"10406.86 192.00 15860.00",
		"4811.75 370.00 15860.00",
		"-500.00 453.00 15860.00"};	
}


class alpOptionsMSradiation 
{
	bool ZombiesResistToxicity							= true;
	bool RadiationAffectsNVG							= true;
	float RadiationResistanceInBuilding 				= 10;//when you stay in building then radiation is decreased by this value
	int	AntiRadBlockDurationEffect						= 180;//time duration of effect radiation protection (in second)
	int EffectAntiRadBlockPills							= 100;//reducing radiation doses by 100 Sv/h
	float AutoRadiationReduce							= 0.1;//reducing recieved radiation doses by 10 Sv/h (on condition you are not in radiation zone)
	int GeigerSoundEffect_Radiation_Low					= 5;
	int GeigerSoundEffect_Radiation_Medium				= 50;
	int GeigerSoundEffect_Radiation_High				= 100;
	
	//float ArmorRatioNBC									= 0.95;  //0-1 default 0.9, if 0 then 0.9
	ref array<float> EfficiencyNBCbyState				= {1.0,0.95,0.75,0.5,0};
	
	int WaterDrainInRadiationPerSec						= 5;   //top hydration is 5000
	int RadiationCapForCalc								= 200;  //  x / 200 * (10/2) * ( 2 - shield / 100 );  ( x/200 * 10 ) - ( x/200 * 10 ) * shield	
	float ArmorRatioNBCforWaterDrain					= 0.80;
	
	bool HeadgearsDetermineBodyProtection				= 0;
	
	bool NotRequiredFilterForRadiation					= false;

	int RadiationLimitToContamineItems					= 50;	
	bool EnableFoodDecontamination						= 0;	
	int RadiationLimitDegradingAttachments				= 100;



	
	float DamageToAttachmentsCoef			= 0.01;
	float DamageToAttachmentsExponent		= 0.3;
	float FilterDamageRatio					= 0.09;
	float ImprovisedFilterDamageRatio		= 0.25;
	

	
}



class alpMissionList 
{
	ref map<string,int>										MissionGroupLimit;
	ref array<ref alpMissionListItem>						MissionList 	= new ref array<ref alpMissionListItem>;
	
}


class alpMissionListItem 
{
	string type;
	string name;
}
