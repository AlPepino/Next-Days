class alpClans_BasisOptions 
{

	
	bool EnableClans									= true;
	bool ShowIconsInTradeZone							= true;
	int   ClanMemberIconColor[4]						= {255,255,0,0};//color of icon over the mate
	
	float ShowNickDistance								= 25;//distance to see mate's icon
	float ShowIconDistance								= 100;
	
	//float ShowIconDistanceInOptics						= 650;//distance to see mate's icon in optic		
	
	
	bool EnableCamera									= true;
	bool Enable3rdPersonCameraInVehicle					= true;
	bool Enable3rdPersonCameraAtHome					= true;
	bool Enable3rdPersonCameraAtSafeZone				= true;

	bool SplitQuestReward								= true;
	
}




class alpClans_Locking 
{	
	bool EnableLocking									= true;
	bool ForcerUnlockAllDoors							= false;
	
	float ChanceToLockDoorAfterRestart 					= 0;
	float RatioLockedDoors								= 0.5;
	
	bool IncludingVehiclesWrecks						= false;
}


class alpCLANoptionsClient 
{
	bool ShowPlayersIcontem								= true;

}
