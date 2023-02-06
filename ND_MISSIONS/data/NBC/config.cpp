class CfgPatches
{
	class ND_MISSIONS_data_NBC
	{
		units[]={	
			"alp_NBCJacketCamo",
			"alp_NBCPantsCamo",
			"alp_NBCHoodCamo",
			"alp_NBCBootsCamo",
			"alp_NBCGlovesCamo",
			"alp_GasMaskCamo",
			"alp_NBCJacketWhite",
			"alp_NBCPantsWhite",
			"alp_NBCHoodWhite",
			"alp_NBCBootsWhite",
			"alp_NBCGlovesWhite",
			"alp_GasMaskWhite"				
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
	class Clothing_Base;
	class Clothing;
	
	class NBCJacketBase;	
	class NBCHoodBase;
	class NBCPantsBase;
	class NBCBootsBase;
	class NBCGloves_ColorBase;
	class GasMask;

	class alp_NBCJacketCamo: NBCJacketBase
	{
		scope=2;
		displayName="NBC Camo Jacket";
		visibilityModifier=0.5;
		itemsCargoSize[]={7,6};		
		hiddenSelections[]=
		{
		"zbytek"
		};	
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\NBC\alp_nbc_jacket_g_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_jacket_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_jacket_camo_co.paa"
		};	
	};
	
	class alp_NBCPantsCamo: NBCPantsBase
	{
		scope=2;
		displayName="NBC Camo Pants";
		visibilityModifier=0.5;
		itemsCargoSize[]={6,5};	
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\NBC\alp_nbc_pants_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_pants_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_pants_camo_co.paa"
		};	
	};	
	class alp_NBCHoodCamo: NBCHoodBase
	{
		scope=2;
		displayName="NBC Camo Hood";
		visibilityModifier=0.5;
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\NBC\alp_nbc_hood_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_hood_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_hood_camo_co.paa"
		};		
	};
	class alp_NBCBootsCamo: NBCBootsBase
	{
		scope=2;
		displayName="NBC Camo Boots";
		visibilityModifier=0.5;
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\NBC\alp_nbc_boots_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_boots_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_boots_camo_co.paa"
		};	
	};	
	class alp_NBCGlovesCamo: NBCGloves_ColorBase
	{
		scope=2;
		displayName="NBC Camo Gloves";
		visibilityModifier=0.5;
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\NBC\alp_nbc_gloves_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_gloves_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_gloves_camo_co.paa"
		};		
	};	
	class alp_GasMaskCamo: GasMask
	{
		
		displayName="NBC Camo GasMask";
		visibilityModifier=0.5;
		hiddenSelections[]=
		{
		"zbytek"
		};			
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\NBC\alp_gasmask_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_gasmask_camo_co.paa",
			"ND_MISSIONS\data\NBC\alp_gasmask_camo_co.paa"
		};			
	};	
	
	class alp_NBCJacketWhite: NBCJacketBase
	{
		scope=2;
		displayName="NBC White Jacket";
		visibilityModifier=0.5;
		heatIsolation=0.5;		
		itemsCargoSize[]={7,6};
		hiddenSelections[]=
		{
		"zbytek"
		};	
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\NBC\alp_nbc_jacket_g_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_jacket_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_jacket_White_co.paa"
		};	
	};
	
	class alp_NBCPantsWhite: NBCPantsBase
	{
		scope=2;
		displayName="NBC White Pants";
		visibilityModifier=0.5;
		heatIsolation=0.5;		
		itemsCargoSize[]={6,5};	
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\NBC\alp_nbc_pants_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_pants_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_pants_White_co.paa"
		};	
	};	
	class alp_NBCHoodWhite: NBCHoodBase
	{
		scope=2;
		displayName="NBC White Hood";
		visibilityModifier=0.5;
		heatIsolation=0.5;		
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\NBC\alp_nbc_hood_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_hood_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_hood_White_co.paa"
		};		
	};
	class alp_NBCBootsWhite: NBCBootsBase
	{
		scope=2;
		displayName="NBC White Boots";	
		visibilityModifier=0.5;
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\NBC\alp_nbc_boots_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_boots_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_boots_White_co.paa"
		};	
	};	
	class alp_NBCGlovesWhite: NBCGloves_ColorBase
	{
		scope=2;
		displayName="NBC White Gloves";
		visibilityModifier=0.5;
		heatIsolation=0.5;
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\NBC\alp_nbc_gloves_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_gloves_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_nbc_gloves_White_co.paa"
		};		
	};	
	class alp_GasMaskWhite: GasMask
	{
		displayName="NBC White GasMask";
		visibilityModifier=0.5;
		hiddenSelections[]=
		{
		"zbytek"
		};			
		hiddenSelectionsTextures[]=
		{
			"ND_MISSIONS\data\NBC\alp_gasmask_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_gasmask_White_co.paa",
			"ND_MISSIONS\data\NBC\alp_gasmask_White_co.paa"
		};			
	};	
};
