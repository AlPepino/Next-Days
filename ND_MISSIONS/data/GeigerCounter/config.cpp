class CfgPatches
{
	class ND_MISSIONS_data_GeigerCounter
	{
		units[]={	
			"alp_geiger_counter"
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
	class alp_geiger_counter: Inventory_Base
	{
		scope = 2;
		displayName = "#STR_alp_geiger_name";
		descriptionShort = "#STR_alp_geiger_desc";
		model = "ND_MISSIONS\data\GeigerCounter\geiger_counter.p3d";
		weight = 500;
		itemSize[] = {3,2};
		SingleUseActions[]={509,510};
		animClass="Pistol";
		rotationFlags = 2;
		isMeleeWeapon=1;
		class MeleeModes
		{
			class Default
			{
				ammo="MeleeLightBlunt";
				range=1;
			};
			class Heavy
			{
				ammo="MeleeLightBlunt_Heavy";
				range=1;
			};
			class Sprint
			{
				ammo="MeleeLightBlunt_Heavy";
				range=2.8;
			};
		};
		attachments[]=
		{
			"BatteryD"
		};
		repairableWithKits[]={5,7};
		repairCosts[]={30,25};
		class EnergyManager
		{
			hasIcon=1;
			autoSwitchOff=1;
			energyUsagePerSecond=0.0049999998;
			plugType=1;
			attachmentAction=1;
			updateInterval=2;
		};		
		lootCategory="Tools";		
		lootTag[]=
		{
			"Work",
			"Civilian",
			"Hunting",
			"Military_east",
			"Military_west"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLabels[] = {1.0,0.7,0.5,0.3,0.0};
					healthLevels[] = {{ 1.0,{ "ND_MISSIONS\data\GeigerCounter\data\geiger_counter.rvmat" } },{ 0.5,{ "ND_MISSIONS\data\GeigerCounter\data\geiger_counter_damage.rvmat" } },{ 0.0,{ "ND_MISSIONS\data\GeigerCounter\data\geiger_counter_destruct.rvmat" } }};
				};
			};
		};
	};


};
