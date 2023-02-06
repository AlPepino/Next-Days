class CfgPatches
{
	class ND_Clans_data_PlotPole
	{
		units[]={	
			"alp_PlotPoleKit",
			"alp_PlotPole"
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
	class alp_PlotPoleKit: Inventory_Base
	{
		scope=2;
		displayName = "$STR_alp_plotpole";
		descriptionShort = "$STR_alp_plotpole_desc";			
		model="ND_Clans\data\PlotPole\plotpolekit.p3d";

		weight=10000;
		itemSize[]={3,8};
		itemBehaviour=2;
		rotationFlags=17;	
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
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
	};	
	
	class alp_PlotPole: Inventory_Base
	{
		scope=2;
		displayName = "$STR_alp_plotpole";
		descriptionShort = "$STR_alp_plotpole_desc";	
		
		model="ND_Clans\data\PlotPole\plotpole.p3d";
		
		bounding="BSphere";
		overrideDrawArea="3.0";
		forceFarBubble="true";
		handheld="false";
		lootCategory="Crafted";
		carveNavmesh=1;
		weight=10000;
		itemSize[]={3,8};
		physLayer="item_large";
		rotationFlags=2;
		inventorySlot[]={};
		
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
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
};
