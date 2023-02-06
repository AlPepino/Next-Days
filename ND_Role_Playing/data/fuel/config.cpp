class CfgPatches
{
	class ND_Role_Playing_data_fuel
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{	
			"DZ_Gear_Cooking",		
			"DZ_Gear_Food",	
			"ND_Role_Playing"
		};
	};
};
class CfgSlots
{
	class Slot_LardALP
	{
		name="LardALP";
		displayName="$STR_Lard0";
		ghostIcon="set:dayz_inventory image:rags";
	};
};	
class CfgVehicles
{
	class Inventory_Base;
	class Edible_Base;	
	class Lard: Edible_Base
	{
		inventorySlot[]+={"LardALP"};		
	}		
	class FireplaceBase;	
	class Fireplace: FireplaceBase
	{
		attachments[]+={"LardALP"};	
		class GUIInventoryAttachmentsProps
		{
			class Fuel
			{
				attachmentSlots[]+={"LardALP"};
			};			
		}			
	}
	class FireplaceIndoor: FireplaceBase
	{
		attachments[]+={"LardALP"};	
		class GUIInventoryAttachmentsProps
		{
			class Fuel
			{
				attachmentSlots[]+={"LardALP"};
			};			
		}	
	}	
	class OvenIndoor: FireplaceBase
	{
		attachments[]+={"LardALP"};	
		class GUIInventoryAttachmentsProps
		{
			class Fuel
			{
				attachmentSlots[]+={"LardALP"};
			};			
		}	
	}
	class BarrelHoles_ColorBase: FireplaceBase
	{
		attachments[]+={"LardALP"};	
		class GUIInventoryAttachmentsProps
		{
			class Fuel
			{
				attachmentSlots[]+={"LardALP"};
			};			
		}			
	}		
};
