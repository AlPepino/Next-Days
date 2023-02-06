class CfgPatches
{
	class ND_MISSIONS_data_Barricade
	{
		units[]={	
			"alp_Barricade",
			"alp_MissionEffects_Alarm",
			"alp_MissionEffects_Explosion",
			"alp_MissionEffects_HeliSmoke",
			"alp_MissionEffects_GasGround",
			"alp_MissionEffects_GasAround",
			"alp_MissionEffects_FalloutAround",
			"alp_MissionEffects_Boiling",
			"alp_MissionEffects_Smoke",
			"alp_MissionEffects_EngineFire",			
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
	class HouseNoDestruct;
	class alp_MissionEffects_Base: HouseNoDestruct
	{
		scope=1;		
		model = "ND_MISSIONS\data\Barricade\free.p3d";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class Melee
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
		};		
	};	
	class alp_MissionEffects_Alarm: alp_MissionEffects_Base
	{
		scope=2;
	};	
	class alp_MissionEffects_Explosion: alp_MissionEffects_Base
	{
		scope=2;
	};		
	class alp_MissionEffects_HeliSmoke: alp_MissionEffects_Base
	{
		scope=2;
	};			
	class alp_MissionEffects_GasGround: alp_MissionEffects_Base
	{
		scope=2;
	};		
	class alp_MissionEffects_GasAround: alp_MissionEffects_Base
	{
		scope=2;
	};		
	class alp_MissionEffects_FalloutAround: alp_MissionEffects_Base
	{
		scope=2;
	};		
	class alp_MissionEffects_Boiling: alp_MissionEffects_Base
	{
		scope=2;
	};		
	class alp_MissionEffects_Smoke: alp_MissionEffects_Base
	{
		scope=2;
	};	
	class alp_MissionEffects_EngineFire: alp_MissionEffects_Base
	{
		scope=2;
	};	
	class alp_MissionEffects_Flare: alp_MissionEffects_Base
	{
		scope=2;
	};		
	class alp_Barricade: HouseNoDestruct	
	{
		scope = 1;
		model = "\DZ\structures_bliss\walls\Wall_Barricade1_4.p3d";
		destrType="DestructBuilding";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class Melee
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=5;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
		};
	};
};
