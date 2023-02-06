class CfgPatches
{
	class ND_MISSIONS_data_AntiRadSpray
	{
		units[]={	
			"alp_DecontaminationSpray"
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
	class DisinfectantSpray;
	class alp_DecontaminationSpray: DisinfectantSpray
	{
		displayName="#STR_alp_decontaminationspray";
		descriptionShort="#STR_alp_decontaminationspray_desc";	
		hiddenSelections[]=
		{
		"zbytek"
		};		
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\AntiRadSpray\antiradspray_co.paa"
		};		
	};
};
