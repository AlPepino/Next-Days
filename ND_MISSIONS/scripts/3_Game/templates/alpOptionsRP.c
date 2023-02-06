
class alpOptionsRP_Players 
{
	bool DisableClimbOverVehicle						= false;
	bool ItemsCanBeRepairedToPristine					= true;
	bool MaskPreventConsume								= true;
	ref TStringArray ExceptionsInMask					= {"Balaclava3Holes_Beige","Balaclava3Holes_Blue","Balaclava3Holes_Black","Balaclava3Holes_Green"};	
	
	bool RaiseZombieAfterDeath							= false;
	bool RaiseZombieFromPlayersBodyOnly					= false;
	int	RaiseZombieTime[2]								= {30,120};
	float RuinDroppedAttch								= 0.5;	
	int AttchLifeTime									= 3600;	
	int ZombieLifeTime									= 3600;	
	int DeadBodyLifeTime								= 180;	
	ref TStringArray MaleZombies						= {"ZmbM_PatrolNormal_Autumn","ZmbM_PatrolNormal_Flat","ZmbM_PatrolNormal_PautRev","ZmbM_PatrolNormal_Summer","ZmbM_SoldierNormal","ZmbM_usSoldier_normal_Desert","ZmbM_usSoldier_normal_Woodland","ZmbM_CitizenASkinny_Blue","ZmbM_CitizenASkinny_Grey","ZmbM_CitizenASkinny_Red","ZmbM_CitizenBFat_Blue","ZmbM_CitizenBFat_Green","ZmbM_CitizenBFat_Red","ZmbM_ClerkFat_Grey","ZmbM_ClerkFat_Khaki","ZmbM_ClerkFat_White","ZmbM_CommercialPilotOld_Blue","ZmbM_CommercialPilotOld_Brown","ZmbM_CommercialPilotOld_Olive","ZmbM_JournalistSkinny","ZmbM_MotobikerFat_Beige","ZmbM_SkaterYoung_Brown","ZmbM_SkaterYoung_Green","ZmbM_SkaterYoung_Grey","ZmbM_usSoldier_Heavy_Woodland","ZmbM_usSoldier_Officer_Desert","ZmbM_usSoldier_normal_Desert","ZmbM_usSoldier_normal_Woodland","ZmbM_FirefighterNormal","ZmbM_NBC_Yellow","ZmbM_NBC_Grey"};	
	ref TStringArray FemaleZombies						= {"ZmbF_PoliceWomanNormal","ZmbF_HikerSkinny_Blue","ZmbF_HikerSkinny_Green","ZmbF_HikerSkinny_Grey","ZmbF_HikerSkinny_Red","ZmbM_NBC_Yellow","ZmbM_NBC_Grey","ZmbF_BlueCollarFat_Blue","ZmbF_BlueCollarFat_Green","ZmbF_BlueCollarFat_Red","ZmbF_BlueCollarFat_White","ZmbF_MechanicNormal_Beige","ZmbF_MechanicNormal_Green","ZmbF_MechanicNormal_Grey","ZmbF_MechanicNormal_Orange","ZmbF_DoctorSkinny","ZmbF_NurseFat","ZmbF_ParamedicNormal_Blue","ZmbF_ParamedicNormal_Green","ZmbF_ParamedicNormal_Red","ZmbF_PatientOld","ZmbF_CitizenANormal_Beige","ZmbF_CitizenANormal_Blue","ZmbF_CitizenBSkinny","ZmbF_Clerk_Normal_Blue","ZmbF_Clerk_Normal_Red","ZmbF_Clerk_Normal_White","ZmbF_JournalistNormal_Blue","ZmbF_JournalistNormal_Green","ZmbF_JournalistNormal_Red","ZmbF_ShortSkirt_beige","ZmbF_ShortSkirt_brown","ZmbF_ShortSkirt_checks","ZmbF_ShortSkirt_green","ZmbF_ShortSkirt_grey","ZmbF_ShortSkirt_white","ZmbF_ShortSkirt_yellow","ZmbF_SkaterYoung_Brown","ZmbF_SkaterYoung_Striped","ZmbF_SkaterYoung_Violet","ZmbF_SurvivorNormal_Blue","ZmbF_SurvivorNormal_Red","ZmbF_SurvivorNormal_White"};
}

class alpOptionsRP_Vehicles 
{
	
	
	
	bool RequiredKeyToStartEngine						= true;
	bool DisableLocpicking								= false;
	
	bool DisableLocpickingInTradeZone					= false;
	bool DisableKeyDuplicationInTradeZone				= false;
	
	bool IndestructibleLockedVehicle					= false;
	bool IndestructibleVehicles							= false;
	
	int TimeToForceOpen									= 60;//time to unlock vehicle by lockpick
	int DamageLockpick									= 40;//damage lockpick after opening vehicle	
	
	bool InitVehiclesProperties							= true;
}
class alpVehicleBehavior 
{
	string Name;
	
	float DamageLight;
	
	float DamageHeavy;
		
	bool EnableCutDownTrees; 	
	
	float RequiredImpulseToCutDown;
	
	float DamageContactCoefHitTree;
	
	float DamageContactCoefHitAI;
	
	float DamageContactCoefHitAnyOther;
	
	float DamageToKillCrew;
	
	void alpVehicleBehavior(string name, bool enable,float impulse, float ratioTree, float ratioAI, float ratioOther, float light, float heavy, float kill)
	{
		Name = name;
		EnableCutDownTrees = enable;
		RequiredImpulseToCutDown = impulse;
		DamageContactCoefHitTree = ratioTree;
		DamageContactCoefHitAI = ratioAI;
		DamageContactCoefHitAnyOther = ratioOther;
		
		DamageLight = light;
		DamageHeavy = heavy;
		DamageToKillCrew = kill;
	}
}