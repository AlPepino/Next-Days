class CfgPatches
{
	class ND_Role_Playing_data_Anabolic
	{
		units[]={	
			"alp_Anabolic"
		};
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
	class Edible_Base;
	class Epinephrine;
	class alp_Anabolic: Epinephrine
	{
		displayName="$STR_alp_anabolic0";
		descriptionShort="$STR_alp_anabolic1";
		hiddenSelections[]=
		{
		"zbytek"
		};		
		hiddenSelectionsTextures[]=
		{
			"ND_Role_Playing\data\Anabolic\anabolic_co.paa"
		};		
	}
};
