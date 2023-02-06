class CfgPatches
{
	class ND_MISSIONS_data_Suppressors
	{
		units[]={	
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
	class ItemSuppressor;
	class M4_Suppressor: ItemSuppressor
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=40;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\suppressor556.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\suppressor556.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\suppressor556_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\suppressor556_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\suppressor556_destruct.rvmat"
							}
						}
					};
				};
			};
		};		
	}		
	class AK_Suppressor: ItemSuppressor
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=40;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\tgpa.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\tgpa_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\tgpa_destruct.rvmat"
							}
						}
					};
				};
			};
		};		
	};
	class PistolSuppressor: ItemSuppressor
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=50;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\gemtech.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\gemtech.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\gemtech_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\gemtech_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\gemtech_destruct.rvmat"
							}
						}
					};
				};
			};
		};		
	};			
};
