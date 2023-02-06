class CfgPatches
{
	class ND_MISSIONS_data_Battery9V
	{
		units[]={	
			"Battery9V"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS"		
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class Switchable_Base;
	class Powered_Base;
	class Edible_Base;
	
	class Battery9V: Inventory_Base
	{
		weight=1;
		quantityBar=1;
		varQuantityInit=1000;
		varQuantityMin=0;
		varQuantityMax=1000;
		varQuantityDestroyOnMin=0;
		class EnergyManager
		{
			hasIcon=1;
			switchOnAtSpawn=1;
			isPassiveDevice=1;
			energyStorageMax=1000;
			energyAtSpawn=1000;
			convertEnergyToQuantity=1;
			reduceMaxEnergyByDamageCoef=1;
			powerSocketsCount=1;
			compatiblePlugTypes[]={1};
		};
		class AnimationSources
		{
			class cover
			{
				source="user";
				animPeriod=0.5;
				initPhase=1;
			};
		};	
		hiddenSelections[]=
		{
		"zbytek"
		};		
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\Battery9V\9v_co.paa",
			"ND_MISSIONS\data\Battery9V\9v_co.paa",
			"ND_MISSIONS\data\Battery9V\9v_co.paa",			
			"ND_MISSIONS\data\Battery9V\9v_co.paa",
			"ND_MISSIONS\data\Battery9V\9v_co.paa",
			"ND_MISSIONS\data\Battery9V\9v_co.paa",
			"ND_MISSIONS\data\Battery9V\9v_co.paa"
		};			
	};
};
