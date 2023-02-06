class CfgPatches
{
	class ND_MISSIONS_data_ATM
	{
		units[]={	
			"alp_ATM"
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
	class HouseNoDestruct;
	class alp_ATM : HouseNoDestruct
	{
		scope = 1;
		model = "ND_MISSIONS\data\ATM\ATM.p3d";
		
	};


};
