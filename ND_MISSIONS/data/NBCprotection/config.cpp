class CfgPatches
{
	class ND_MISSIONS_data_NBCprotection
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS",
			"ND_MISSIONS_data",			
			"DZ_Data",
			"DZ_Characters_Gloves",
			"DZ_Characters_Headgear",
			"DZ_Characters_Masks",
			"DZ_Characters_Pants",
			"DZ_Characters_Shoes",
			"DZ_Characters_Tops",
			"DZ_Gear_Consumables"
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;	
	class Clothing;		
	class NBCGloves_ColorBase: Clothing
	{
		class Protection
		{
			chemical=1;
			radiation=1;		
		};		
	};
	class SurgicalGloves_ColorBase: Clothing
	{
		class Protection
		{
			chemical=0.5;
			radiation=0.5;	
		};	
	};	
	class NBCHoodBase: Clothing
	{
		class Protection
		{
			chemical=0.5;
			radiation=0.5;		
		};			
	};	
	class GasMask: Clothing
	{
		class Protection
		{
			biological=1.0;
			chemical=0.5;
			radiation=0.5;	
		};		
	};	
	class GP5GasMask: Clothing
	{
		class Protection
		{
			biological=1;
			chemical=1;
			radiation=1;		
		};		
	};	
	class AirborneMask: Clothing
	{
		class Protection
		{
			biological=1.0;
			chemical=0.5;
			radiation=0.5;		
		};		
	};	
	class GP5GasMask_Filter: Inventory_Base
	{
		class Protection
		{
			biological=1;
			chemical=1;
			radiation=1;		
		};		
	};	
	class GorkaPants_ColorBase: Clothing
	{
		class Protection
		{
			chemical=0.25;
			radiation=0.25;			
		};		
	};	

	class FirefightersPants_ColorBase: Clothing
	{
		class Protection
		{
			chemical=0.75;
			radiation=0.75;			
		};		
	};		

	class NBCPantsBase: Clothing
	{
		class Protection
		{
			chemical=1;
			radiation=1;		
		};		
	};	
	class Wellies_ColorBase: Clothing
	{	
		class Protection
		{
			chemical=0.5;
			radiation=0.5;			
		};		
	};	
	class NBCBootsBase: Clothing
	{	
		class Protection
		{
			chemical=1;
			radiation=1;			
		};		
	};	

	class GorkaEJacket_ColorBase: Clothing
	{
		class Protection
		{
			chemical=0.25;
			radiation=0.25;			
		};		
	};	
	class FirefighterJacket_ColorBase: Clothing
	{
		class Protection
		{
			chemical=0.75;
			radiation=0.75;			
		};		
	};	
	class LabCoat: Clothing
	{
		class Protection
		{
			chemical=0.25;
			radiation=0.25;			
		};		
	};		
	class NBCJacketBase: Clothing
	{
		class Protection
		{
			chemical=1;
			radiation=1;	
			hasdosimeter=1;				
		};		
	};		
	
	class GasMask_Filter: Inventory_Base
	{
		class Protection
		{
			biological=1;
			chemical=1;
			radiation=1;		
		};		
	};		
	

	class dzn_lehs_helmet : Clothing
	{
		class Protection
		{
			biological=1;
			chemical=1;
			radiation=1;		
		};			
	}
	class dzn_lehs : Clothing
	{
		class Protection
		{
			biological=1;
			chemical=1;
			radiation=1;	
			hasdosimeter=1;					
		};			
	}	
};
