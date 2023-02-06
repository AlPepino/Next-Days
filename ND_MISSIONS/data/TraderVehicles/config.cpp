class CfgPatches
{
	class ND_MISSIONS_data_TraderVehicles
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS",
			"ND_MISSIONS_data",
		};
	};
};
class CfgVehicles
{
	class Car;
	class CarScript : Car
	{
		class TraderItem
		{
			CategoryID=198;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarScript;
	class CivilianSedan : CarScript
	{
		class TraderItem
		{
			CategoryID=198;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarScript;
	class Hatchback_02 : CarScript
	{
		class TraderItem
		{
			CategoryID=198;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarScript;
	class OffroadHatchback : CarScript
	{
		class TraderItem
		{
			CategoryID=198;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarScript;
	class Sedan_02 : CarScript
	{
		class TraderItem
		{
			CategoryID=198;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarScript;
	class Truck_01_Base : CarScript
	{
		class TraderItem
		{
			CategoryID=199;
			Price=600000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CarScript;
	class Offroad_02 : CarScript
	{
		class TraderItem
		{
			CategoryID=201;
			Price=1500000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
};
