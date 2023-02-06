class CfgPatches
{
	class ND_MISSIONS_data_Zombies
	{
		units[]={
			"alp_ZedArmy_M1",
			"alp_ZedArmy_M2",
			"alp_ZedWorker_M1"			
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS",
			"DZ_Characters_Zombies"			
		};
	};
};
class CfgVehicles
{
	class DZ_LightAI;
	class DayZInfected: DZ_LightAI
	{
	};
	class ZombieBase: DayZInfected
	{
		class Cargo
		{
			itemsCargoSize[]={10,5};
			allowOwnedCargoManipulation=1;
			openable=0;
		};			
		
	};
		

	class ZmbM_usSoldier_normal_Woodland;
	class alp_ZedArmy_M1: ZmbM_usSoldier_normal_Woodland
	{
	
	}
	class ZmbM_SoldierNormal;
	class alp_ZedArmy_M2: ZmbM_SoldierNormal
	{
	
	}	
	class ZmbM_HeavyIndustryWorker;
	class alp_ZedWorker_M1: ZmbM_HeavyIndustryWorker
	{
		
	}		
};
