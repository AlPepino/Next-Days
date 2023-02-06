class alpResourcesSetting 
{
	bool EnableFuelstationManagement 					= true;
	
	bool EnableWellManagement						= true;

	ref alpDefaultWellsSetting Wells = new alpDefaultWellsSetting();
	
	ref alpDefaultFuelstationSetting Fuelstations = new alpDefaultFuelstationSetting();
}


class alpDefaultWellsSetting 
{
	float DefaultAmmount					= 15000;
	float DefaultAmmountMax					= 30000;
	float DefaultRefreshPerRestart			= 5000;
	float DefaultChanceRefresh				= 0.50;	
}


class alpDefaultFuelstationSetting 
{
	float DefaultAmmount					= 2000;
	float DefaultAmmountMax					= 10000;
	float DefaultRefreshPerRestart			= 4000;
	float DefaultChanceRefresh				= 0.10;	
}

class alpResourcesStation 
{		
	
	int IDE;
	string Location;
	vector Position;
	float Ammount;
	float AmmountMax;
	float RefreshPerRestart;
	float ChanceRefresh;
	
	void alpResourcesStation(int ide, string loc, vector pos, float ammount, float max, float refresh, float chance)
	{
		IDE = ide;
		Location = loc;
		Position = pos;
		Ammount = ammount;
		AmmountMax = max;
		RefreshPerRestart = refresh;
		ChanceRefresh = chance;
	}
}