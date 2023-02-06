class CfgPatches
{
	class ND_Clans_data_dynamite
	{
		units[]={	
			"alp_Dynamite"
		};
		ammo[] = {
			"alp_DynamiteExplosion"
			};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_Clans"
		};
	};
};

class CfgAmmo
{
	class DefaultAmmo;
	class alp_DynamiteExplosion: DefaultAmmo
	{
		hit = 1;
		indirectHit = 0.5;
		indirectHitRange = 1.0;
		particle = "explosion_landmine_01";
		explosive = 1;
		typicalSpeed = 3;
		initSpeed = 3;
		fuseDistance = 1;
		simulation = "shotShell";
		simulationStep=0.050000001;
		soundSetExplosion[]=
		{
			"Landmine_Explosion_SoundSet",
			"Landmine_Explosion_Tail_SoundSet"
		};
		soundHit[]=
		{
			"DZ\sounds\weapons\grenades\hand_grenade_1",
			10,
			1
		};
		soundFly[]=
		{
			"dz\sounds\Weapons\explosions\noise",
			3.1622771e-005,
			1
		};
		soundEngine[]=
		{
			"",
			9.9999983e-005,
			4
		};
		class DamageApplied
		{
			type = "FragGrenade";
			bleedThreshold=1;
			class Health
			{
				damage = 200;
			};
			class Blood
			{
				damage = 100;
			};
			class Shock
			{
				damage = 100;
			};
		};
		class NoiseExplosion
		{
			strength = 100;
			type = "sound";
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;	
	
	class alp_Dynamite_Base : Inventory_Base
	{
		absorbency=0.5;
		lockType=4;
		inventorySlot[]=
		{
			"VestGrenadeA",
			"VestGrenadeB",
			"VestGrenadeC",
			"VestGrenadeD",
			"tripWireAttachment"
		};			
		
	}
	
	

	class alp_Dynamite: alp_Dynamite_Base
	{
		scope=2;
		displayName="#STR_alp_dynamite";
		descriptionShort="#STR_alp_dynamite_desc";			
		
		model = "ND_Clans\data\dynamite\dynamite.p3d";

		weight=1000;
		itemSize[]={2,3};
		
		itemBehaviour=1;
		slopeTolerance=0.15000001;
		yawPitchRollLimit[]={60,60,60};		
		hiddenSelections[]=
		{
			"placing",
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"ND_Clans\data\dynamite\data\dynamite_CO.paa",
			"ND_Clans\data\dynamite\data\dynamite_CO.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"ND_Clans\data\dynamite\data\dynamite.rvmat",
			"ND_Clans\data\dynamite\data\dynamite.rvmat"
		};		
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLabels[] = {1.0,0.7,0.5,0.3,0.0};
					healthLevels[] = {{ 1.0,{ "ND_Clans\data\dynamite\data\dynamite.rvmat" } },{ 0.5,{ "ND_Clans\data\dynamite\data\dynamite_damage.rvmat" } },{ 0.0,{ "ND_Clans\data\dynamite\data\dynamite_destruct.rvmat" } }};
				};
			};
		};		
	
	};	

};
