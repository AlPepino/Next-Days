class CfgPatches
{
	class ND_Clans_data_HouseKey
	{
		units[]={	
			"alp_HouseKey",
			"alp_AdminHouseKey"
		};
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
	class alp_HouseKey_Base: Inventory_Base
	{
		model = "ND_Clans\data\HouseKey\HouseKey.p3d";
		animClass="Knife";
		rotationFlags=17;
		RestrainUnlockType=0;
		weight=20;
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
					healthLevels[] = {{ 1.0,{ "ND_Clans\data\HouseKey\data\HouseKey.rvmat" } },{ 0.5,{ "ND_Clans\data\HouseKey\data\HouseKey_damage.rvmat" } },{ 0.0,{ "ND_Clans\data\HouseKey\data\HouseKey_destruct.rvmat" } }};
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
	class alp_HouseKey: alp_HouseKey_Base
	{	
		scope=2;
		displayName="$STR_alp_HouseKey";
		descriptionShort="$STR_alp_HouseKey";		
	}
	class alp_AdminHouseKey: alp_HouseKey_Base
	{	
		scope=2;
		displayName="Admin House Key";
		descriptionShort="For unlocking every house";		
	}	
};
