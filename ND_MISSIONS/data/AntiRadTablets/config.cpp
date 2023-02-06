class CfgPatches
{
	class ND_MISSIONS_data_AntiRadTablets
	{
		units[]={	
			"alp_radboxtablets"
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
	class Edible_Base;
	class Bottle_Base;	
	class VitaminBottle;
	class alp_radboxtablets: VitaminBottle
	{
		displayName="#STR_alp_radtablets_name";
		descriptionShort="#STR_alp_radtablets_desc";	
		varQuantityInit=20;
		varQuantityMin=0;
		varQuantityMax=20;
		canBeSplit=1;
		varQuantityDestroyOnMin=1;		
		hiddenSelections[]=
		{
		"zbytek"
		};		
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\AntiRadTablets\radblocktablets_co.paa"
		};
	};
};
