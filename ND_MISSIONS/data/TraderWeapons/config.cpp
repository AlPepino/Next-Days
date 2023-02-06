class CfgPatches
{
	class ND_MISSIONS_data_TraderWeapons
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
class cfgWeapons
{
	class RifleCore;
	class Rifle_Base : RifleCore
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class PistolCore;
	class Pistol_Base : PistolCore
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_Base;
	class BoltActionRifle_ExternalMagazine_Base : BoltActionRifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class BoltActionRifle_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_Base;
	class BoltActionRifle_InnerMagazine_Base : BoltActionRifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class RifleCore;
	class Archery_Base : RifleCore
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUMDAR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_InnerMagazine_Base;
	class Winchester70_Base : BoltActionRifle_InnerMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class LauncherCore;
	class Launcher_Base : LauncherCore
	{
		class TraderItem
		{
			CategoryID=63;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DefaultWeapon;
	class NonlethalCore : DefaultWeapon
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DefaultWeapon;
	class RifleCore : DefaultWeapon
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class AK74_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_M4_Modular_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUAutoSScript : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class Scout_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_InnerMagazine_Base;
	class Mosin9130_Base : BoltActionRifle_InnerMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class CZ75_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_AKMod_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_AKMod_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class Deagle_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class FNX45_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NonlethalCore;
	class NonlethalPistol : NonlethalCore
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DefaultWeapon;
	class LauncherCore : DefaultWeapon
	{
		class TraderItem
		{
			CategoryID=63;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class DefaultWeapon;
	class PistolCore : DefaultWeapon
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_HONEY_BADGER_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_AK101_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class AK101_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_AK102_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_AK74M_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_AK_ALPHA_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class AKM_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_AKMN_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_AKS74N_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class AKS74UN_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_AN94_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_ASVAL_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class B95_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_PP19_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_ACR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_CZ361_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FNFAL_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FNFAL_PARA_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FNFAL_TAC_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_EVO_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_HK416A7_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_HK416D_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_HK417_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Izh18_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_SR47_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_KOMRAD_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_M16A2_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_M16A3_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class M4A1_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_KEDR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_PPSH41_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SKS_TAC_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SKS_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_SLR_AR15_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_AR15SPR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_SR25_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_SVD_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_SVDM_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_SVDK_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_SVDS_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_UZI_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_SOK94_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FOX_VSS_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shotgun_Base;
	class Izh43Shotgun_Base : Shotgun_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class CZ527_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class FOX_FRF2_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class FOX_SSG69_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_InnerMagazine_Base;
	class FOX_KAR98K_Base : BoltActionRifle_InnerMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class B95_Base;
	class B95 : B95_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class Colt1911_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_FD338_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_FD338_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AKM_Base;
	class AKM : AKM_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Izh43Shotgun_Base;
	class Izh43Shotgun : Izh43Shotgun_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mosin9130_Base;
	class SawedoffMosin9130_Base : Mosin9130_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NonlethalPistol;
	class Shockpistol_Base : NonlethalPistol
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shotgun_Base;
	class FOX_MP153_Base : Shotgun_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M4_Modular_Base;
	class SNAFU_M4556_Modular10_GUN : SNAFU_M4_Modular_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M4_Modular_Base;
	class SNAFU_M4556_Modular14DV_GUN : SNAFU_M4_Modular_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_M4A1_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AKM_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class AA12_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUHoneyBadger_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_Agram_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_AK5C_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_AK103A_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_AK12A_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_AK19_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_AK308_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_AS50_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUASh12_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUAUG_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Aug_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class GCGN_M82_Barret_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class PP19_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_BR18_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_Bren_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class CZ61_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_CZ805_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUDSASA58_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class FAL_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUFAMAS_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Famas_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SCAR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_G3A3_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class GCGN_MP7_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=55;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class GCGN_Vepr_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class GCGN_Vityaz_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUGevar_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUGM6Lynx_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class GP25Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Groza_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class HK416_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class GCGN_HK416_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNHK417_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class IA2_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_CALI_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_KAC_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=55;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUKH9_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUVECTOR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=55;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class GCGN_M110_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_M14_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class M16A2_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_M1918A2_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUM1A_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class GCGN_M1Garand_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class M203Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class GCGN_M249_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class M249_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_M60_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class M79_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=63;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUMarlin1895_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUMk12_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class MK18_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class MP5K_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_MP9_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUP90_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=55;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_PDW_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=55;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class PM73Rak_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUPPSh_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUPPSKN_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_RDB_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class ACR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Repeater_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFURPD_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_RPK16_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Ruger1022_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNSA58_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUSA80_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Saiga_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SG550_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SG552_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_MPX_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SN_Auto_Shotgun_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_MAR10_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_AEK545_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUKivaari_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Snafu_PKP_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Snafu_ScarH_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_SR25_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_ADAR_Modular_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_AR15_Modular_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_LVOA_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_M4300_Modular_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_MK47Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_Saint_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_Saint308_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_SR3Vikhr_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUSten_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SVD_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUTAR21_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Tec9_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUThompsonMk2_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class Trumpet_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_U100_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class UMP45_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUUzi_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=55;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class VR80_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class VSS_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFUVSSK_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_SKS_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_M70_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class SNAFU_M76_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_Base;
	class SNAFUM98B_Base : BoltActionRifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_Base;
	class SNAFURSASS_Base : BoltActionRifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFU_AWM_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class CZ550_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFUDVL10M2_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFU_FRF2_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class GCGN_M200_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFU_M300_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFUM96_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class GCGN_M700_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFUAX50_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFUM24_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFUT5000_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFUAlligator_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFUSRSA2_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SSG82_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_ExternalMagazine_Base;
	class SNAFUTac21_Base : BoltActionRifle_ExternalMagazine_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_InnerMagazine_Base;
	class SNAFU_M48_Base : BoltActionRifle_InnerMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK101_Base;
	class AK101 : AK101_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK74_Base;
	class AK74 : AK74_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AK74_Base;
	class AKS74U : AK74_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AKM;
	class SN_AKM : AKM
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class AKS74UN_Base;
	class FOX_AKS74UN : AKS74UN_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Archery_Base;
	class Crossbow : Archery_Base
	{
		class TraderItem
		{
			CategoryID=52;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Archery_Base;
	class QuickieBow : Archery_Base
	{
		class TraderItem
		{
			CategoryID=52;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Archery_Base;
	class PVCBow : Archery_Base
	{
		class TraderItem
		{
			CategoryID=52;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Archery_Base;
	class RecurveBow : Archery_Base
	{
		class TraderItem
		{
			CategoryID=52;
			Price=1500;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CZ527_Base;
	class CZ527 : CZ527_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Deagle_Base;
	class Deagle : Deagle_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FNFAL_Base;
	class FOX_FNFAL : FNFAL_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FNFAL_PARA_Base;
	class FOX_FNFAL_PARA : FNFAL_PARA_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FNFAL_TAC_Base;
	class FOX_FNFAL_TAC : FNFAL_TAC_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FNX45_Base;
	class FNX45 : FNX45_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_ACR_Base;
	class FOX_ACR : FOX_ACR_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK_ALPHA_Base;
	class FOX_AK_ALPHA : FOX_AK_ALPHA_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK101_Base;
	class FOX_AK101 : FOX_AK101_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK102_Base;
	class FOX_AK102 : FOX_AK102_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AK74M_Base;
	class FOX_AK74M : FOX_AK74M_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AKMN_Base;
	class FOX_AKMN : FOX_AKMN_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AKS74N_Base;
	class FOX_AKS74N : FOX_AKS74N_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_AN94_Base;
	class FOX_AN94 : FOX_AN94_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_ASVAL_Base;
	class FOX_ASVAL : FOX_ASVAL_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_CZ361_Base;
	class FOX_CZ361 : FOX_CZ361_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_EVO_Base;
	class FOX_EVO : FOX_EVO_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_FRF2_Base;
	class FOX_FRF2 : FOX_FRF2_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HK416A7_Base;
	class FOX_HK416A7 : FOX_HK416A7_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HK416D_Base;
	class FOX_HK416D : FOX_HK416D_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HK417_Base;
	class FOX_HK417 : FOX_HK417_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_HONEY_BADGER_Base;
	class FOX_HONEY_BADGER : FOX_HONEY_BADGER_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_KAR98K_Base;
	class FOX_KAR98K : FOX_KAR98K_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_KEDR_Base;
	class FOX_KEDR : FOX_KEDR_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_KOMRAD_Base;
	class FOX_KOMRAD : FOX_KOMRAD_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_M16A2_Base;
	class FOX_M16A2 : FOX_M16A2_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_M16A3_Base;
	class FOX_M16A3 : FOX_M16A3_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_MP153_Base;
	class FOX_MP153 : FOX_MP153_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_PP19_Base;
	class FOX_PP19 : FOX_PP19_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_PPSH41_Base;
	class FOX_PPSH41 : FOX_PPSH41_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SLR_AR15_Base;
	class FOX_SLR_AR15 : FOX_SLR_AR15_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SOK94_Base;
	class FOX_SOK94 : FOX_SOK94_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SR25_Base;
	class FOX_SR25 : FOX_SR25_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SR47_Base;
	class FOX_SR47 : FOX_SR47_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SSG69_Base;
	class FOX_SSG69 : FOX_SSG69_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SVD_Base;
	class FOX_SVD : FOX_SVD_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SVDK_Base;
	class FOX_SVDK : FOX_SVDK_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SVDM_Base;
	class FOX_SVDM : FOX_SVDM_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_SVDS_Base;
	class FOX_SVDS : FOX_SVDS_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_UZI_Base;
	class FOX_UZI : FOX_UZI_Base
	{
		class TraderItem
		{
			CategoryID=55;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FOX_VSS_Base;
	class FOX_VSS : FOX_VSS_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Izh18_Base;
	class Izh18 : Izh18_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Izh43Shotgun;
	class SNAFU_TP82S_Base : Izh43Shotgun
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Launcher_Base;
	class LAWBase : Launcher_Base
	{
		class TraderItem
		{
			CategoryID=63;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Launcher_Base;
	class RPG7Base : Launcher_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Launcher_Base;
	class UnderSlugGrenadeM4 : Launcher_Base
	{
		class TraderItem
		{
			CategoryID=63;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class M4A1_Base;
	class M4A1 : M4A1_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mosin9130_Base;
	class Mosin9130 : Mosin9130_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NonlethalCore;
	class NonlethalRifle : NonlethalCore
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class NonlethalPistol;
	class DartGun : NonlethalPistol
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SNAFUAPS_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class Derringer_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class Flaregun_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SNAFU_Fort12_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class FOX_APS_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class FOX_FN57_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class FOX_MP443_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class FOX_PM_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class FOX_SR1_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class FOX_Glock18C_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class Glock19_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SNAFUChiappaRhino_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SNAFU_PL14HQP_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class LongHorn_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class Magnum_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class MakarovIJ70_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class MakarovPB_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class MKII_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SNAFUMagnum500_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class P1_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class Red9_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SNAFUSWM629_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SN_Mp443_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SN_Glock19_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SN_M9_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SN_Springfield_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class SN_USP_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class FOX_TT_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SawedoffMosin9130_Base;
	class SawedoffMosin9130 : SawedoffMosin9130_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Scout_Base;
	class Scout : Scout_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shockpistol_Base;
	class Shockpistol : Shockpistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shotgun_Base;
	class Izh18Shotgun_Base : Shotgun_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shotgun_Base;
	class Mp133Shotgun_Base : Shotgun_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shotgun_Base;
	class SN_M870_Base : Shotgun_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Shotgun_Base;
	class SNAFU_Trenchgun_Base : Shotgun_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SKS_Base;
	class SKS : SKS_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SKS_TAC_Base;
	class FOX_SKS_TAC : SKS_TAC_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_AR15SPR_Base;
	class SNAFU_AR15SPRBK : SNAFU_AR15SPR_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M4556_Modular10_GUN;
	class M4_6933_Base : SNAFU_M4556_Modular10_GUN
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFU_M4556_Modular14DV_GUN;
	class GCGN_M4A1_Base : SNAFU_M4556_Modular14DV_GUN
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUAutoSScript;
	class GCGN_BenelliM4_Base : SNAFUAutoSScript
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUAutoSScript;
	class Spas12_Base : SNAFUAutoSScript
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUMDAR_Base;
	class SNAFUMDARCAR_Black : SNAFUMDAR_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUMDAR_Base;
	class SNAFUMDARRIF_Black : SNAFUMDAR_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class SNAFUMDAR_Base;
	class SNAFUMDARSBR_Black : SNAFUMDAR_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Winchester70_Base;
	class Winchester70 : Winchester70_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Deagle_Base;
	class TTC_Deagle_Base : Deagle_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Glock19;
	class TTC_Glock17_Base : Glock19
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Colt1911_Base;
	class TTC_Kimber_Base : Colt1911_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CZ75_Base;
	class TTC_M9_Base : CZ75_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class CZ75_Base;
	class TTC_M9_Custom_Base : CZ75_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class FNX45_Base;
	class TTC_P320_Base : FNX45_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_AEK_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_AG3_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_AK12_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_AK12Worn_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AKMod_Base;
	class TTC_AKMod : TTC_AKMod_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_AKMod_Base;
	class TTC_AKModPK : TTC_AKMod_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_AVS36_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Scout_Base;
	class TTC_AWM_Base : Scout_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_BAR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_Beowulf_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_Mk47_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_ModDMR556_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_ModDMR762_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_FAL_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TTC_FD338_Base;
	class TTC_GEVAR43 : TTC_FD338_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_G3_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_HK416_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_HK416Comp_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_HK417_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_HKG28_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_AACHoney_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_AACHoney300blk_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class k98_Base;
	class TTC_kar98k : k98_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTCKAC_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_L85_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_InnerMagazine_Base;
	class TTC_LeeEnfield_base : BoltActionRifle_InnerMagazine_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_M110_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_M14_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_M1A_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_M16A_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_CAR15_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_M16A4_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Winchester70_Base;
	class TTC_M1903_base : Winchester70_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_M1Garand_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_Base;
	class TTC_M24_Base : BoltActionRifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_M4DMR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_M4Tac_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_M82_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_MCX_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_MCX_Spear_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_MK18_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_MP44_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_Base;
	class TTC_MRAD_base : BoltActionRifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Winchester70_Base;
	class TTC_R700_base : Winchester70_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_SCARH_base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_SCARL_base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_SG550_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_SG552_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTCSR25_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_SVT40_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_TAVOR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_VHS_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_AKM_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Winchester1873_Base;
	class TTC_Winchester1873 : Winchester1873_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_Base;
	class TTC_XM2010_Base : BoltActionRifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class B95;
	class TTC_Maverick_Base : B95
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Mp133Shotgun;
	class TTC_Mossberg_Base : Mp133Shotgun
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_Raptr_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=56;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_MP5SD_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_MP7A1_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_MPX_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_PP91_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=54;
			Price=30000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TTC_UZI_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=55;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Magnum;
	class TTC_44Magnum_Base : Magnum
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_M4A1_Base;
	class TF_ADAR2_15_Base : TF_M4A1_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AK101_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AK102_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AK103_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AK104_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AK105_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AK105_Bullpup_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AK74M_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AKMN_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AKS74U_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AN94_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_Anzio20_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class TF_FiveSeven : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_M14_DMR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_M14_EBR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_M14_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_M1A_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=50000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_MAR_10_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=62;
			Price=200000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_SCAR_L_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_SCAR_L_CQC_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_SCAR_H_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_SCAR_H_CQC_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_SCAR_20_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_MK47_CQBR_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_MK47_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class TF_MP443_Base : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_OTs_12_Tiss_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_OTs_14_Groza_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=58;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Pistol_Base;
	class TF_MakarovPB : Pistol_Base
	{
		class TraderItem
		{
			CategoryID=53;
			Price=20000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class TF_AKM_Base;
	class TF_VPO136_Base : TF_AKM_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class BoltActionRifle_Base;
	class TF_VPO190_Base : BoltActionRifle_Base
	{
		class TraderItem
		{
			CategoryID=57;
			Price=40000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_AEK999_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_M16A4_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=59;
			Price=60000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_M240_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_M249_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_PKM_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_PKP_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=61;
			Price=90000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_SR25_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_SVCh_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=60;
			Price=80000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
	class Rifle_Base;
	class TF_M79_Base : Rifle_Base
	{
		class TraderItem
		{
			CategoryID=63;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};
	};
};
