class CfgPatches
{
	class ND_Clans_data_RaidDamage
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_Clans"
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;

	class BaseBuildingBase: Inventory_Base
	{
		DynamiteDamageRatioOwnerOn = 1;
		DynamiteDamageRatioOwnerOff = 1;
	};
	
	class Fence: BaseBuildingBase
	{
		DynamiteDamageRatioOwnerOn = 1.0;
		DynamiteDamageRatioOwnerOff = 0.5;		
	}
	
	class Watchtower: BaseBuildingBase
	{
		DynamiteDamageRatioOwnerOn = 0.5;
		DynamiteDamageRatioOwnerOff = 0.25;		
	}	
};