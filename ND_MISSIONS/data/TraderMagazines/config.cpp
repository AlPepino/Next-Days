class CfgPatches
{
	class ND_MISSIONS_data_TraderMagazines
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
class CfgMagazines
{
	class DefaultMagazine;
	class Magazine_Base : DefaultMagazine
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Ammunition_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=80;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_40mm_Base : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=106;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_Flare : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=103;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CZ75_15Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_FNX45_15Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Glock_15Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Deagle_9rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_BMAG300_Black : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_mag_ak74_60rnd_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_Stanag_60rnd_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Groza_20Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammo_40mm_Base;
	class Ammo_40mm_Explosive : Ammo_40mm_Base
	{
		class TraderItem
		{
			CategoryID=106;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammo_40mm_Base;
	class Ammo_40mm_ChemGas : Ammo_40mm_Base
	{
		class TraderItem
		{
			CategoryID=106;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammo_40mm_Base;
	class Ammo_40mm_Smoke_ColorBase : Ammo_40mm_Base
	{
		class TraderItem
		{
			CategoryID=106;
			Price=2500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammo_Flare;
	class Ammo_FlareRed : Ammo_Flare
	{
		class TraderItem
		{
			CategoryID=103;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammo_Flare;
	class Ammo_FlareGreen : Ammo_Flare
	{
		class TraderItem
		{
			CategoryID=103;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammo_Flare;
	class Ammo_FlareBlue : Ammo_Flare
	{
		class TraderItem
		{
			CategoryID=103;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_338 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=91;
			Price=250;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_22 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=80;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class GCGN_Ammo_3006 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=88;
			Price=150;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_308Win : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_308WinTracer : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_357 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=94;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_380 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class GCGN_Ammo_408Chey : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=99;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_44 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=100;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_45ACP : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=101;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class GCGN_Ammo_50Cal : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_127x55mmAP : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_127x55mm : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_12gaPellets : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=103;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_12gaSlug : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=103;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_12gaRubberSlug : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=103;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_145Cal : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_300ACC : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_45_70mm : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=101;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_46x30 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=101;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_57x28 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=81;
			Price=60;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_57x28AP : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=81;
			Price=60;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_545x39 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=79;
			Price=30;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_545x39Tracer : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=79;
			Price=30;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_MD_Ammo_556x45mm_M855A1 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=80;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_556x45 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=80;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_556x45Tracer : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=80;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_5_7x28mm : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=81;
			Price=60;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_500_SW : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_792x57FOX : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=88;
			Price=150;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_762x25 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_762x39 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_762x39Tracer : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_762x54 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_762x54Tracer : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class GCGN_Ammo_762x51 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class SNAFU_Ammo_762x51 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_93x64 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=89;
			Price=150;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_9x19 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_9x39AP : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_9x39 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_AACBLK : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_762x25fox : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_9x18 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_9x21FOX : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=92;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_ArrowBolt : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=76;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_ArrowBoned : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=76;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_ArrowComposite : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=76;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_DartSyringe : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=76;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_ArrowPrimitive : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=76;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_GrenadeM4 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=106;
			Price=10000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_LAW_HE : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=106;
			Price=250000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_RPG7_HE : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=106;
			Price=250000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_RPG7_AP : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=106;
			Price=250000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_SharpStick : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=76;
			Price=50;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class Ammo_12gaBeanbag : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=103;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_mag_ak74_60rnd_Base;
	class FOX_mag_ak74_60rnd : FOX_mag_ak74_60rnd_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_Mag_Stanag_60rnd_Base;
	class FOX_Mag_Stanag_60rnd : FOX_Mag_Stanag_60rnd_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_357Speedloader_6Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CLIP9x19_10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_M60_100rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFURPD_100rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CZ550_10rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_FAL_10rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_FRF2_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CMAG_10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_MKII_10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CLIP762x39_10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Ruger1022_10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_SVDK_10rnd_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_SVD_10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_VSS_10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=70;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_VSS_10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=70;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_12gaSnaploader_2Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_IJ70_8Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_MP5_15Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Ruger1022_15Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_PM73_15Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_M249_Box200Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_APS_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_ASVAL_20Rnd_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=70;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CZ61_20Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_CZ361 : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Saiga_Drum20Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=68;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_FAL_20rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_FN57_20rnd_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_G3A3_20rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_HK417_20rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_Kedr_20 : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_FAL_20Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CMAG_20Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_SR25_20rnd_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_VAL_20Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=70;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_FAMAS_25Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_UMP_25Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_PM73_25Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_CMAG30300_Black : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_CMAG40300_Black : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_CMAG60300_Black : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_HB_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Aug_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_Bren_30rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_STANAGCoupled_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_EVO_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_FAL_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_FN57_30rnd_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_AK101_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_AK74_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_AKM_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_AKM_Palm30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_Kedr_30 : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CMAG_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_MP5_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Ruger1022_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_STANAG_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUSten_32rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_UZI_32Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=67;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class GCGN_MP7_40Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=67;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CMAG_40Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_Glock_45_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_AK74_45Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_BMAG556_Black : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_CMAG30556_Black : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_PMAG556_Black : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_CMAG40556_Black : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_CMAG60556_Black : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_FAL_50rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_UZI_50Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=67;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CZ527_5rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CLIP762x54_5Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Scout_5Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_SSG82_5rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_SSG69_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Saiga_5Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=68;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_STANAG_60Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_PP19 : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_PP19_64Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUPPSh_71rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_AKM_Drum75Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_1911_7Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_P1_8Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_PM_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_TT_Mag_8Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Saiga_8Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=68;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class AA12_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=68;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_Agram_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_AK12_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_AK308_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUAlligator_5rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUAPS_20rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Arrows_Quiver : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=64;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_AS50_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUASh12_20rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUAUG_30rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_AWM_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_308WinSnaploader_2Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class GCGN_M82_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Bolts_Quiver : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=64;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_Dartgun_CO2 : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUDVL10M2_5rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class GCGN_Mag_FAL_50Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_Fort12_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUGevar_10rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUGM6Lynx_5rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class GCGN_HK416_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNHK417_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUHoneyBadger_30rdMag_Black : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class GCGN_M200_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_KAC_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=67;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUKH9_30rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUVECTOR_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=67;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_AK103_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_PL14HQP_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class GCGN_M110_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_M14_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_M1918A2_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUM1A_20rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class GCGN_M249_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_M300Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class GCGN_M700_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUM96_5rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_mag_AK_ALPHA_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_MP443_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_SKS_TAC : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_mag_SOK94_10rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_SR1_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_MakarovPB_8Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUMDAR_30rndMagB : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUMDAR_60rndMagB : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUMk12_20rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Modified_SA58_30RND_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_MP9_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_MPX_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUP90_50rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=67;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_PPSH41_35Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class FOX_Mag_PPSH41_71Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUPPSKN_30rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_RPK16_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SA58_30RND_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SA58_DrumMag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_Saint_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_ShockCartridge : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_SKS_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SN_Auto_Shotgun_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=68;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SN_M9_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SN_Mp443_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SN_Springfield_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SN_USP_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUAX50_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_FRF2_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUKivaari_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUM24_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUM98B_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_MAR10_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Snafu_PKP_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFURSASS_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Snafu_ScarH_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUT5000_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_PDW_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=67;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_762x54Snaploader_2Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_SR25_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_SR3Vikhr_Mag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=70;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUSRSA2_10rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Mag_CZ550_4rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUTac21_5rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class Tec9_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUThompsonMk2_30rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_U100_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUUzi_32rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=67;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUUzi_72rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=67;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class GCGN_VEPR_10rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class GCGN_Vityaz_Mag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class VR80_Magazine_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=68;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFUVSSK_5rdMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class SNAFU_M76_Mag_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_BMAG300_Black;
	class SNAFUAR15_SPR_100RND_Mag : SNAFU_BMAG300_Black
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mag_Deagle_9rnd;
	class TTC_Deagle_Magazine_7rnd : Mag_Deagle_9rnd
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_50AE : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mag_Glock_15Rnd;
	class TTC_Mag_Glock_17Rnd : Mag_Glock_15Rnd
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mag_CZ75_15Rnd;
	class TTC_Mag_M9_15Rnd : Mag_CZ75_15Rnd
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mag_CZ75_15Rnd;
	class TTC_Mag_M9_Custom_20Rnd : Mag_CZ75_15Rnd
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mag_FNX45_15Rnd;
	class TTC_P320_17Rnd : Mag_FNX45_15Rnd
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_3006 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_300blk : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_300Stanag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_300Cmag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_300Cmag_60rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_303 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=87;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_308Stanag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_338 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=91;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_338mag_10rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_338mag_5rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_4570 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=100;
			Price=250;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_50Beo_mag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_50Beo : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_50BMG : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_8mm : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=90;
			Price=250;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_AG3_Coupled_Magazine_40rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_AKMod_762x54_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_AKMod_762x54_65rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_AVS36_Mag_10rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_AWM_Magazine_5rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_BAR_Magazine_20rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_DMR_556Stanag_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_DMR_762Stanag_20rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_DMR_762Stanag_10rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_DMR_556Stanag_100rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_DMR_556Pmag_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_DMR_556Pmag_40rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_DMR_556Pmag_100rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_AK12_Drum_90rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_G3_Magazine_20rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_HK417_Magazine_20rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_556Cmag_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_Coupled_FAL_Magazine : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_FAL_Magazine : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_GEVAR43_Magazine_10rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_M14_Mag_20rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_556Stanag_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_556Stanag_60rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_M24New_mag_5rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_M24mag_5rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_M82_5rnd_Mag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_MCX_Spear_Magazine_20rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=70;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_277 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=85;
			Price=120;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_STG44_Magazine_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_792x33 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=88;
			Price=80;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_SCARHMag : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_Mag_SVT40_10rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_TAVOR_Magazine_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_TAVOR_Magazine_60rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_XM2010_10rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_Raptr_Drum_45rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=68;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_MP7A1_Mag_40rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_4630 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=78;
			Price=60;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_MPX_Mag_60rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_MPX_Mag_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_PP91_Mag_20rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TTC_UZI_Mag_30rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=66;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TTC_Ammo_44Mag : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=100;
			Price=100;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TF_Ammo_20mm : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TF_Ammo_20mm_HE : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=102;
			Price=3000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TF_Ammo_338LM : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=91;
			Price=500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TF_Ammo_57 : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=81;
			Price=60;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Ammunition_Base;
	class TF_Ammo_40mm_HEDP : Ammunition_Base
	{
		class TraderItem
		{
			CategoryID=106;
			Price=250000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mag_Groza_20Rnd;
	class TF_Mag_OTs_14_Groza_20Rnd : Mag_Groza_20Rnd
	{
		class TraderItem
		{
			CategoryID=70;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_SCAR_H_20rnd_base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_SCAR_H_25rnd_base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_SCAR_H_30rnd_base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_PMAG_25RND_308win_base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_X10_50RND_308win_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_XFAL_50RND_308win_base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_MAR_10_10rnd_base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_Anzio20_3Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=74;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_mag_M14_Base : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AK74_60Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AK74_45Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AKM_Plastic30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AKM_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AKM_10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AKM_PMAG30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_M4_STANAG_30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_M4_PMAG10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_M4_PMAG20Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_M4_PMAG30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_M4_PMAG40Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_FiveSeven_20Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_MP443_18Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=65;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_VPO190_4Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=69;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AK101_Plastic30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AK74_Bakelit30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AK74_Plum30Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AKM_Bakelit40Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_AKM_Steel40Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=71;
			Price=1000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_M240_50Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_M249_200Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_PKM_100Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=73;
			Price=2000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_SR25_20Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magazine_Base;
	class TF_Mag_SVCh308_10Rnd : Magazine_Base
	{
		class TraderItem
		{
			CategoryID=72;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
};
