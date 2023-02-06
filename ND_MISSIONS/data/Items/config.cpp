class CfgPatches
{
	class ND_MISSIONS_data_Items
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS",
			"ND_MISSIONS_data",
			"DZ_Gear_Navigation",				
		};
	};
};
class MapDefaults;
class CfgVehicles
{
	class ItemMap;
	class ChernarusMap: ItemMap
	{
		itemSize[]={1,1};	
		class MapProperties: MapDefaults
		{
			scaleMin=0.01;
			scaleMax=0.75;
		};		
	}	

}