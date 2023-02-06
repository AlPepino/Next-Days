class CfgPatches
{
	class ND_Role_Playing_data_Pelts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_Role_Playing"
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;	
	
	class Pelt_Base: Inventory_Base
	{
		canBeSplit=1;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=50;
		varQuantityDestroyOnMin=1;
		varStackMax=5;		
	}
};
