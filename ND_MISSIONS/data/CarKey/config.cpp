class CfgPatches
{
	class ND_MISSIONS_data_CarKey
	{
		units[]={	
			"alp_CarKey",
			"alp_CarKeyBlue",
			"alp_CarKeyGreen",
			"alp_CarKeyYellow",
			"alp_CarKeyWhite",
			"alp_CarKeyPurple",
			"alp_CarKeyBrown",
			"alp_AdminCarKey"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS"
		};
	};
};
class CfgModels
{
	class carkey
	{
		sections[]=
		{
			"zbytek"
		};
	};	
};
class CfgVehicles
{
	class Inventory_Base;	
	class alp_CarKey_Base: Inventory_Base
	{
		model = "ND_MISSIONS\data\CarKey\carkey.p3d";
		animClass="Knife";
		rotationFlags=17;
		RestrainUnlockType=0;
		weight=4;
		itemSize[]={1,1};
		fragility=0.0099999998;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLabels[] = {1.0,0.7,0.5,0.3,0.0};
					healthLevels[] = {{ 1.0,{ "ND_MISSIONS\data\CarKey\data\CarKey.rvmat" } },{ 0.5,{ "ND_MISSIONS\data\CarKey\data\carkey_damage.rvmat" } },{ 0.0,{ "ND_MISSIONS\data\CarKey\data\carkey_destruct.rvmat" } }};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class lockpicker_move_in
				{
					soundSet="lockpicker_move_in_SoundSet";
					id=110202;
				};
				class lockpicker_move_out
				{
					soundSet="lockpicker_move_out_SoundSet";
					id=110203;
				};
				class lockpicker_loop
				{
					soundSet="lockpicker_loop_SoundSet";
					id=203;
				};
				class lockpicker_end
				{
					soundSet="lockpicker_end_SoundSet";
					id=110204;
				};
			};
		};		
	};	
	class alp_CarKey: alp_CarKey_Base
	{	
		scope=2;
		displayName="$STR_alp_carkey_black";
		descriptionShort="$STR_alp_carkey_black";		
	}
	class alp_AdminCarKey: alp_CarKey_Base
	{	
		scope=2;	
		displayName="Admin Car Key";
		descriptionShort="For unlocking every vehicle";		
	}	
	class alp_CarKeyBlue: alp_CarKey
	{	
		displayName="$STR_alp_carkey_blue";
		descriptionShort="$STR_alp_carkey_blue";	
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"ND_MISSIONS\data\CarKey\data\carkey_blue.paa"};
	};
	class alp_CarKeyGreen: alp_CarKey
	{	
		displayName="$STR_alp_carkey_green";
		descriptionShort="$STR_alp_carkey_green";	
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"ND_MISSIONS\data\CarKey\data\carkey_green.paa"};
	};
	class alp_CarKeyYellow: alp_CarKey
	{
		displayName="$STR_alp_carkey_yellow";
		descriptionShort="$STR_alp_carkey_yellow";	
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"ND_MISSIONS\data\CarKey\data\carkey_yellow.paa"};
	};
	class alp_CarKeyWhite: alp_CarKey
	{	
		displayName="$STR_alp_carkey_white";
		descriptionShort="$STR_alp_carkey_white";	
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"ND_MISSIONS\data\CarKey\data\carkey_white.paa"};
	};
	class alp_CarKeyPurple: alp_CarKey
	{
		displayName="$STR_alp_carkey_purple";
		descriptionShort="$STR_alp_carkey_purple";	
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"ND_MISSIONS\data\CarKey\data\carkey_purple.paa"};
	};
	class alp_CarKeyBrown: alp_CarKey
	{	
		displayName="$STR_alp_carkey_brown";
		descriptionShort="$STR_alp_carkey_brown";	
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"ND_MISSIONS\data\CarKey\data\carkey_brown.paa"};
	};	
};
