class CfgPatches
{
	class ND_MISSIONS_data_CargoContainer
	{
		units[]={	
			"alp_Misc_cargo_cont_net1",
			"alp_WoodenCrate",
			"alp_WoodenCrateBig",
			"alp_WoodenCrateBig3x",
			"alp_WoodenCrateBig5x"
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
	class Container_Base;

	class alp_Misc_cargo_cont_net1: Container_Base	
	{
		displayName="Cargo container";
		descriptionShort="Manipulation is not allowed";
		
		scope=2;
		model="\nst\ns2\build\a2\proxy\Misc_cargo_cont_net1.p3d";

		overrideDrawArea="8.0";

		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;
		quantityBar=1;
		carveNavmesh=1;
		canBeDigged=0;
		heavyItem=1;
		weight=100000;
		
		itemSize[]={40,40};
		
		itemBehaviour=0;

		physLayer="item_large";
		allowOwnedCargoManipulation=1;

		class Cargo
		{
			itemsCargoSize[]={10,100};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
	
	
	class Container_Base;
	class WoodenCrate: Container_Base
	{	
	}
	class alp_WoodenCrate: WoodenCrate
	{
		itemSize[]={10,12};
		class Cargo
		{
			itemsCargoSize[]={10,12};
			openable=0;
			allowOwnedCargoManipulation=1;
		};			
	}	
	
	class alp_WoodenCrate_Base: Container_Base
	{
		scope=0;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
					transferToAttachmentsCoef=0.059999999;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\camping\data\wooden_case.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\camping\data\wooden_case.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\camping\data\wooden_case_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\camping\data\wooden_case_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\camping\data\wooden_case_destruct.rvmat"
							}
						}
					};
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
	}		

	class alp_WoodenCrateBig: alp_WoodenCrate_Base	
	{
		displayName="Cargo container";
		descriptionShort="Manipulation is not allowed";
		
		scope=2;
		model="DZ\structures_bliss\Residential\Misc\Misc_WoodenCrate.p3d";

		overrideDrawArea="8.0";

		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;
		quantityBar=1;
		carveNavmesh=1;
		canBeDigged=0;
		heavyItem=1;
		weight=100000;
		
		itemSize[]={40,40};
		
		itemBehaviour=0;

		physLayer="item_large";
		allowOwnedCargoManipulation=1;

		class Cargo
		{
			itemsCargoSize[]={10,15};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};	
	class alp_WoodenCrateBig3x: alp_WoodenCrate_Base	
	{
		displayName="Cargo container";
		descriptionShort="Manipulation is not allowed";
		
		scope=2;
		model="DZ\structures_bliss\Residential\Misc\Misc_WoodenCrate_3x.p3d";

		overrideDrawArea="8.0";

		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;
		quantityBar=1;
		carveNavmesh=1;
		canBeDigged=0;
		heavyItem=1;
		weight=100000;
		
		itemSize[]={40,40};
		
		itemBehaviour=0;

		physLayer="item_large";
		allowOwnedCargoManipulation=1;

		class Cargo
		{
			itemsCargoSize[]={10,45};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};		
	class alp_WoodenCrateBig5x: alp_WoodenCrate_Base	
	{
		displayName="Cargo container";
		descriptionShort="Manipulation is not allowed";
		
		scope=2;
		model="DZ\structures_bliss\Residential\Misc\Misc_WoodenCrate_5x.p3d";

		overrideDrawArea="8.0";

		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;
		quantityBar=1;
		carveNavmesh=1;
		canBeDigged=0;
		heavyItem=1;
		weight=100000;
		
		itemSize[]={40,40};
		
		itemBehaviour=0;

		physLayer="item_large";
		allowOwnedCargoManipulation=1;

		class Cargo
		{
			itemsCargoSize[]={10,75};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};			
};
