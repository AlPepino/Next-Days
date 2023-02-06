class CfgPatches
{
	class ND_MISSIONS_data_USD
	{
		units[]={	
			"alp_USD1",
			"alp_USD5",
			"alp_USD10",
			"alp_USD20",		
			"alp_USD50",
			"alp_USD100",			
			"alp_USD500",				
			"alp_USD1000"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS",
			"ND_MISSIONS_data_CZK"
		};
	};
};

class CfgVehicles
{
	class alp_Money;
	
	class alp_USD1: alp_Money
	{
		scope = 2;
		nominalValue=1;
		displayName = "$STR_usd_name";
		descriptionShort = "$STR_koruny_description";	
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\USD\data\USD1_co.paa"
		};			
	}
	class alp_USD5: alp_Money
	{
		scope = 2;
		nominalValue=5;
		displayName = "$STR_usd_name";
		descriptionShort = "$STR_koruny_description";		
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\USD\data\USD5_co.paa"
		};			
	}
	class alp_USD10: alp_Money
	{
		scope = 2;
		nominalValue=10;
		displayName = "$STR_usd_name";
		descriptionShort = "$STR_koruny_description";			
		hiddenSelectionsTextures[]=
		{		
			"ND_MISSIONS\data\USD\data\USD10_co.paa"
		};			
	}	
	class alp_USD20: alp_Money
	{
		scope = 2;
		nominalValue=20;
		displayName = "$STR_usd_name";
		descriptionShort = "$STR_koruny_description";		
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\USD\data\USD20_co.paa"
		};	
	}
	class alp_USD50: alp_Money
	{
		scope = 2;
		nominalValue=50;
		displayName = "$STR_usd_name";
		descriptionShort = "$STR_koruny_description";		
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\USD\data\USD50_co.paa"
		};	
	}
	class alp_USD100: alp_Money
	{
		scope = 2;
		displayName = "$STR_usd_name";
		nominalValue=100;
		descriptionShort = "$STR_koruny_description";		
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\USD\data\USD100_co.paa"
		};	
	}		
	class alp_USD500: alp_Money
	{
		scope = 2;
		displayName = "$STR_usd_name";
		nominalValue=500;
		descriptionShort = "$STR_koruny_description";		
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\USD\data\USD500_co.paa"
		};	
	}		
	class alp_USD1000: alp_Money
	{
		scope = 2;
		nominalValue=1000;
		displayName = "$STR_usd_name";
		descriptionShort = "$STR_koruny_description";		
		hiddenSelectionsTextures[]=
		{			
			"ND_MISSIONS\data\USD\data\USD1000_co.paa"
		};	
	}
};
