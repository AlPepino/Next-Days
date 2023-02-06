class CfgPatches
{
	class ND_MISSIONS_data_RadioactiveBarrel
	{
		units[]={	
			"alp_Barrel_Yellow"
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
	class alp_Radioactive_Barrel: Container_Base	
	{
		displayName="#STR_alp_radbarel_name";
		descriptionShort="#STR_alp_radbarel_desc";
		model="\dz\gear\containers\55galDrum.p3d";
		overrideDrawArea="8.0";
		forceFarBubble="true";
		SingleUseActions[]={527};
		InteractActions[]={51025,51026};
		ContinuousActions[]={155};
		destroyOnEmpty=0;
		varQuantityDestroyOnMin=0;
		quantityBar=1;
		carveNavmesh=1;
		canBeDigged=0;
		heavyItem=1;
		weight=10000;
		itemSize[]={10,20};
		itemBehaviour=0;
		stackedUnit="ml";
		randomQuantity=2;
		liquidContainerType="1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256 + 512 + 1024 + 2048 + 4096 + 8192 + 16384 + 32768 - (1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256)";
		varQuantityInit=0;
		varQuantityMin=0;
		varQuantityMax=200000;
		absorbency=0.1;
		physLayer="item_large";
		allowOwnedCargoManipulation=1;
		lootTag[]=
		{
			"Work"
		};
		hiddenSelections[]=
		{
			"camoGround"
		};
		class Cargo
		{
			itemsCargoSize[]={10,20};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
		class AnimationSources
		{
			class Lid
			{
				source="user";
				initPhase=0;
				animPeriod=0.0099999998;
			};
			class Lid2
			{
				source="user";
				initPhase=1;
				animPeriod=0.0099999998;
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpBarrelLight_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpBarrel_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="barrel_drop_SoundSet";
					id=898;
				};
			};
		};	
	};
	class alp_Barrel_Yellow: alp_Radioactive_Barrel
	{
		scope=2;
		color="yellow";
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\RadioactiveBarrel\alp_barrel_yellow_co.paa",
		};
		hologramMaterial="Barrel";
		hologramMaterialPath="dz\gear\containers\data";
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{{1,{"ND_MISSIONS\data\RadioactiveBarrel\alp_barrel_yellow.rvmat"}},{0.69999999,{"ND_MISSIONS\data\RadioactiveBarrel\alp_barrel_yellow.rvmat"}},{0.5,{"ND_MISSIONS\data\RadioactiveBarrel\alp_barrel_yellow_damage.rvmat"}},{0.30000001,{"ND_MISSIONS\data\RadioactiveBarrel\alp_barrel_yellow_damage.rvmat"}},{0,{"ND_MISSIONS\data\RadioactiveBarrel\alp_barrel_yellow_destruct.rvmat"}}};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					Health=0;
					Blood=0;
					Shock=0;
				};
			};
		};
	};	
};
