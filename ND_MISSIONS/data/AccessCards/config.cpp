class CfgPatches
{
	class ND_MISSIONS_data_AccessCards
	{
		units[]={	
			"alp_AccessCardRed",
			"alp_AccessCardBlue",
			"alp_AccessCardGreen",
			"alp_AccessCardYellow"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS",
			"DZ_DATA",
		};
	};
};
class CfgModels
{
	class AccessCards
	{
		sections[]=
		{
			"zbytek"
		};
	};	
};
class CfgVehicles
{
	class Inventory_Base;
	class alp_AccessCard_Base: Inventory_Base 
	{	
		model = "ND_MISSIONS\data\AccessCards\AccessCards.p3d";		
		descriptionShort = "$STR_alp_accesscard_desc";		
		weight = 10;
		itemSize[] = {1,1};	
		rotationFlags = 16;	
		lootCategory="Tools";
		lootTag[]=
		{
			"Civilian",
			"Office"
		};		
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=30;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"ND_MISSIONS\data\AccessCards\data\AccessCard.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"ND_MISSIONS\data\AccessCards\data\AccessCard.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"ND_MISSIONS\data\AccessCards\data\AccessCard_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"ND_MISSIONS\data\AccessCards\data\AccessCard_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"ND_MISSIONS\data\AccessCards\data\AccessCard_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="pickUpPaper_SoundSet";
					id=797;
				};
			};
		};				
		keyid = 0;
	}
	class alp_AccessCardRed: alp_AccessCard_Base 
	{
		scope = 2;		
		displayName = "#STR_alp_accesscard_red";
		hiddenSelections[]=
		{
			"zbytek"
		};			
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\AccessCards\data\AccesCardRed_co.paa"
		};		
		keyid = 0;			
	}		
	class alp_AccessCardBlue: alp_AccessCard_Base 
	{
		scope = 2;		
		displayName = "#STR_alp_accesscard_blue";	
		hiddenSelections[]=
		{
			"zbytek"
		};			
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\AccessCards\data\AccesCardBlue_co.paa"
		};		
		keyid = 1;				
	}	
	class alp_AccessCardGreen: alp_AccessCard_Base 
	{
		scope = 2;		
		displayName = "#STR_alp_accesscard_green";	
		hiddenSelections[]=
		{
			"zbytek"
		};			
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\AccessCards\data\AccesCardGreen_co.paa"
		};	
		keyid = 2;			
	}	
	class alp_AccessCardYellow: alp_AccessCard_Base 
	{
		scope = 2;		
		displayName = "#STR_alp_accesscard_yellow";	
		hiddenSelections[]=
		{
			"zbytek"
		};			
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\AccessCards\data\AccesCardYellow_co.paa"
		};	
		keyid = 3;			
	}		
};
