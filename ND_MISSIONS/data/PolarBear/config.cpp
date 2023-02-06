class CfgPatches
{
	class ND_MISSIONS_data_PolarBear
	{
		units[]={	
			"alp_PolarBearPelt"
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

	class Pelt_Base;
	class alp_PolarBearPelt : Pelt_Base	
	{
		scope=2;
		displayName="$STR_CfgVehicles_BearPelt0";
		descriptionShort="$STR_CfgVehicles_BearPelt1";	
		model="\dz\gear\consumables\Pelt_Bear.p3d";
		weight=1200;
		itemSize[]={8,4};
		peltGain=10;
		leatherYield=12;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\consumables\data\pelt_bear.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\consumables\data\pelt_bear.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\consumables\data\pelt_bear_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\consumables\data\pelt_bear_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\consumables\data\pelt_bear_destruct.rvmat"
							}
						}
					};
				};
			};
		};		
		
		
		displayName="$STR_CfgVehicles_BearPelt0";
		descriptionShort="$STR_CfgVehicles_BearPelt1";		
		hiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"ND_MISSIONS\data\PolarBear\polarbearpelt_co.paa"};		
	};
	
	class Animal_UrsusArctos;
	class Animal_UrsusMaritimus: Animal_UrsusArctos
	{
		class Skinning
		{
			class ObtainedPelt
			{
				item="alp_PolarBearPelt";
				count=2;
				itemZones[]=
				{
					"Zone_Pelvis",
					"Zone_Belly"
				};
				quantityCoef=1;
				transferToolDamageCoef=1;
			};
			class ObtainedSteaks
			{
				item="BearSteakMeat";
				count=20;
				itemZones[]=
				{
					"Zone_Belly",
					"Zone_Pelvis"
				};
				countByZone[]={8,8};
				quantityMinMaxCoef[]={0.69999999,1};
			};
			class ObtainedLard
			{
				item="Lard";
				count=2;
				quantityMinMaxCoef[]={0.2,1};
			};
			class ObtainedGuts
			{
				item="Guts";
				count=4;
				quantityMinMaxCoef[]={0.5,0.80000001};
			};
			class ObtainedBones
			{
				item="Bone";
				count=5;
				quantityMinMaxCoef[]={0.30000001,1};
				transferToolDamageCoef=1;
			};
		};
	};	
};
