class CfgPatches
{
	class ND_MISSIONS_data
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS",
			"DZ_Data",
		};
	};
};
class CfgVehicles
{
	class Static;
	class Inventory_Base: Static
	{
		class TraderItem
		{
			CategoryID = 174;
			Price = 100;
			CanBuy = 1;
			CanSell = 1;
			RequiredReputation = 0;
			ReputationRatioSelling = 0;
			ReputationRatioBuying = 0;
		};
		class Protection
		{
			biological=0;
			chemical=0;
			radiation=0;
			hasdosimeter=0;			
			filterefficiency=0;	
		};		
	};



};