class CfgPatches
{
	class ND_MISSIONS_data_CZK
	{
		units[]={	
			"alp_Coin1",
			"alp_Coin2",
			"alp_Coin5",
			"alp_CoinRare1",
			"alp_Money10",
			"alp_Money20",
			"alp_Money100",
			"alp_Money500",
			"alp_Money1000"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS"
		};
	};
};
class CfgModels
{
	class money
	{
		sections[]=
		{
			"zbytek"
		};
	};
	class coin
	{
		sections[]=
		{
			"zbytek"
		};
	};
	class coinRare
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
	class Edible_Base;
	class alp_Cash: Inventory_Base 
	{
		nominalQuantity=1;
		nominalValue=1;
	}
	class alp_Coin: alp_Cash
	{
		model = "ND_MISSIONS\data\CZK\coin.p3d";
		weight = 2;
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
					hitpoints = 100;
					healthLabels[] = {1.0,0.7,0.5,0.3,0.0};
					healthLevels[] = {{ 1.0,{ "ND_MISSIONS\data\CZK\data\coin.rvmat" } },{ 0.5,{ "ND_MISSIONS\data\CZK\data\coin_damage.rvmat" } },{ 0.0,{ "ND_MISSIONS\data\CZK\data\coin_destruct.rvmat" } }};
				};
			};
		};		
	}
	class alp_Coin1: alp_Coin
	{
		scope = 2;
		displayName = "$STR_koruny_name";
		descriptionShort = "$STR_koruny_description";	
		hiddenSelections[]=
		{
			"zbytek"
		};			
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\CZK\data\coin1_co.paa"
		};			
	}	
	class alp_Coin2: alp_Coin
	{
		scope = 2;
		displayName = "$STR_koruny_name";
		descriptionShort = "$STR_koruny_description";	
		nominalValue=2;
		hiddenSelections[]=
		{
			"zbytek"
		};			
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\CZK\data\coin2_co.paa"
		};			
	}		
	class alp_Coin5: alp_Coin
	{
		scope = 2;
		displayName = "$STR_koruny_name";
		descriptionShort = "$STR_koruny_description";	
		nominalValue=5;
		hiddenSelections[]=
		{
			"zbytek"
		};			
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\CZK\data\coin5_co.paa"
		};			
	}	
	class alp_CoinRare: alp_Coin
	{
		model = "ND_MISSIONS\data\CZK\coinRare.p3d";
		weight = 4;	
	}	
	class alp_CoinRare1: alp_CoinRare
	{
		scope = 2;
		displayName = "$STR_korunyRare1_name";
		descriptionShort = "$STR_korunyRare_description";	
		hiddenSelections[]=
		{
			"zbytek"
		};			
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\CZK\data\coinRare1_co.paa"
		};			
		class TraderItem	
		{	
			CategoryID=196;
			Price=100000;
			CanBuy=1;
			CanSell=1;
			RequiredReputation=0;
			SellingBonusReputationRatio=0;
			BuyingPenaltyReputationRatio=0;
		};			
	}		
	class alp_Money: alp_Cash
	{
		model = "ND_MISSIONS\data\CZK\money.p3d";
		weight = 2;
		nominalQuantity=100;
		itemSize[] = {1,2};
			canBeSplit=1;
			varQuantityInit=100;
			varQuantityMin=0;
			varQuantityMax=100;
			varQuantityDestroyOnMin=1;		
		rotationFlags = 16;	
		absorbency=1;	
		inventorySlot[]=
		{
			"Paper"
		};		
		lootCategory="Tools";		
		lootTag[]=
		{
			"Civilian",
			"Office"
		};	
		hiddenSelections[]=
		{
			"zbytek"
		};	
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLabels[] = {1.0,0.7,0.5,0.3,0.0};
					healthLevels[] = {{ 1.0,{ "ND_MISSIONS\data\CZK\data\money.rvmat" } },{ 0.5,{ "ND_MISSIONS\data\CZK\data\money_damage.rvmat" } },{ 0.0,{ "ND_MISSIONS\data\CZK\data\money_destruct.rvmat" } }};
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
	}
	class alp_Money10: alp_Money
	{
		scope = 2;
		nominalValue=10;
		displayName = "$STR_koruny_name";
		descriptionShort = "$STR_koruny_description";			
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\CZK\data\money_co.paa"
		};			
	}
	class alp_Money20: alp_Money
	{
		scope = 2;
		nominalValue=20;
		displayName = "$STR_koruny_name";
		descriptionShort = "$STR_koruny_description";		
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\CZK\data\money20_co.paa"
		};	
	}
	class alp_Money50: alp_Money
	{
		scope = 2;
		nominalValue=50;
		displayName = "$STR_koruny_name";
		descriptionShort = "$STR_koruny_description";		
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\CZK\data\money50_co.paa"
		};	
	}
	class alp_Money100: alp_Money
	{
		scope = 2;
		nominalValue=100;
		displayName = "$STR_koruny_name";
		descriptionShort = "$STR_koruny_description";		
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\CZK\data\money100_co.paa"
		};	
	}		
	class alp_Money500: alp_Money
	{
		scope = 2;
		nominalValue=500;
		displayName = "$STR_koruny_name";
		descriptionShort = "$STR_koruny_description";		
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\CZK\data\money500_co.paa"
		};	
	}		
	class alp_Money1000: alp_Money
	{
		scope = 2;
		nominalValue=1000;
		displayName = "$STR_koruny_name";
		descriptionShort = "$STR_koruny_description";			
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\CZK\data\money1000_co.paa"
		};	
	}		
	
};
