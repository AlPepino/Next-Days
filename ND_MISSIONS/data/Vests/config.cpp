class CfgPatches
{
	class ND_MISSIONS_data_Vests
	{
		units[]={	
			"alp_UKAssVest_White",
			"alp_HighCapacityVest_White"
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
	class Clothing_Base;
	class Clothing;
	class HighCapacityVest_Black;
	class UKAssVest_Camo;	
	class alp_UKAssVest_White: UKAssVest_Camo
	{	
		hiddenSelections[]=
		{
		"zbytek"
		};	
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\Vests\alp_UKAssVest_White_co.paa",
			"ND_MISSIONS\data\Vests\alp_UKAssVest_White_co.paa",
			"ND_MISSIONS\data\Vests\alp_UKAssVest_White_co.paa"
		};				
	}
	class alp_HighCapacityVest_White: HighCapacityVest_Black
	{	
		visibilityModifier=0.55000000;
		hiddenSelections[]=
		{
		"zbytek"
		};	
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\Vests\alp_HighCapacityVest_White_co.paa",
			"ND_MISSIONS\data\Vests\alp_HighCapacityVest_White_co.paa",
			"ND_MISSIONS\data\Vests\alp_HighCapacityVest_White_co.paa"
		};			
		
	}
};
