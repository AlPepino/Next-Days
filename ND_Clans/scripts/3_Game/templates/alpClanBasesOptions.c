class alpTaxedArea
{
	int Point1[2]
	int Point2[2]
	int StockID;
	
	void alpTaxedArea( int x1, int x2, int y1, int y2, int traderID )
	{
		Point1 = {x1,x2};
		Point2 ={y1,y2};
		StockID = traderID;
	}
}



class alpClanBasesOptions 
{	
	bool EnableNextDaysRaidMechanics					= true;
	bool EnableLifeTimeManagement						= true;
	//int LifeTimeAfterExpiredProtection					= 3600 * 12;	
	bool EnableEstateMenus 								= true;	
	bool DisablePlacingObjectOutsideClaimedArea			= true;//true;		
	ref array<string> PlacingExceptions					= {"alp_PlotPole","alp_PlotPoleKit","Fireplace","TentBase","Container","BearTrap","LandMineTrap"};
	bool EnableRestrictedArea							= 0;//0
	bool ShowRestrictedAreaOnMap						= 0;//0	
	string LabelOfRestrictedArea 						= "Restricted area for building";
	ref array<ref vector> RestrictedAreas				= {	Vector(0,0,0),	Vector(0,0,0) };	

	ref array<ref alpTaxedArea > TerritoryCurrency;	//			= {{	Vector(0,0,0),	Vector(0,0,0) },{	Vector(0,0,0),	Vector(0,0,0) }};

	bool DisableNotfYouAreInEnemyTerritory				= true;

	float EstateManagementMenu_blur						= 0.5;	
		
	int EstateValuePerCubicMeter						= 2000;
	int BuildingTaxPerCubicMeterPerDay					= 8;
	int FingerprintLockValuePerDoor						= 80000;
	int LockProtectionValuePerDoor						= 100000;
	int DurableDoorsValuePerDoor						= 100000;
	int PriceOfHouseKey									= 5000;

		
	ref array<ref alpPlotPoleSettings> PlotPoleTaxes;	//tax fee
	//ref array<ref alpTimeDestrurtion> DestructionTimeInPlotPole;//destruction time	
	
	
	float Raid_Picklock_Tier1[4]						= {10,0.2,0.1,0.25};
	float Raid_Picklock_Tier2[4]						= {20,0.1,0.05,0.5};
	
	//ref alpTimeToBreakageLock TimeToBreakageLockTier1   = new alpTimeToBreakageLock(60.0,600.0);
	
	//ref alpTimeToBreakageLock TimeToBreakageLockTier2  	= new alpTimeToBreakageLock(180.0,1800.0);
	bool IsPossibleToBreakLockTier2						= true;
	
	//ref array<ref alpRaidTools> RaidToolsTier1;
	//ref array<ref alpRaidTools> RaidToolsTier2;
	
	float Raid_TNT_OwnerIsON_Building_Door_Tier1 = 0.5;
	float Raid_TNT_OwnerIsON_Building_Door_Tier2 = 0.25;
	
	float Raid_TNT_OwnerIsOFF_Building_Door_Tier1 = 0.2;
	float Raid_TNT_OwnerIsOFF_Building_Door_Tier2 = 0.1;	
	
	
	ref array<ref alpRaidTNT_BaseBuilding> Override_Raid_TNT_BaseBuilding;
	
	/*
	float Raid_TNT_OwnerIsON_BaseBuilding_Tier1 = 0.5;
	float Raid_TNT_OwnerIsON_BaseBuilding_Tier2 = 0.25;
	
	float Raid_TNT_OwnerIsOFF_BaseBuilding_Tier1 = 0.2;
	float Raid_TNT_OwnerIsOFF_BaseBuilding_Tier2 = 0.1;
	*/
	void alpClanBasesOptions()
	{
		InitDefault();
	}
	void InitDefault(){
		TerritoryCurrency = new array<ref alpTaxedArea >;
		
		//int aa[2] = {1,1};
		
		TerritoryCurrency.Insert( new alpTaxedArea( 0,0 , 15500,7000 ,100 ) );
		TerritoryCurrency.Insert( new alpTaxedArea( 0,7000 , 15500,15500 ,101 ) );
			
		//DestructionTimeInPlotPole = new array<ref alpTimeDestrurtion>;	
		//alpTimeDestrurtion defaultValue = new alpTimeDestrurtion("default",3600,86400);		
		//DestructionTimeInPlotPole.Insert( defaultValue );	
		
		PlotPoleTaxes = new array<ref alpPlotPoleSettings>;

		InitPlotPoleTaxes();		
		
		alpRaidTNT_BaseBuilding example = new alpRaidTNT_BaseBuilding("Fence",1.0,0.5);
		Override_Raid_TNT_BaseBuilding = new array<ref alpRaidTNT_BaseBuilding>;	
		Override_Raid_TNT_BaseBuilding.Insert( example );
	}
	void InitPlotPoleTaxes()
	{
		float ppm = 15.9154943091895;
		
		float cost,r;
		for (int i = 0; i < 20;)
		{
			r = 20 + i * 5;
			cost = 2 * Math.PI * Math.Pow( r , 2 ) * ppm;
			cost = Math.Floor( cost );
			
			alpPlotPoleSettings pps = alpPlotPoleSettings(r,i, cost , 14 );
			
			PlotPoleTaxes.Insert ( pps );
			
			i++;
			i++;
		}
	
	}	
}

class alpPlotPoleSettings 
{
	int Radius;
	int LevelRequirements;
	float Tax;
	int Validity;
	
	void alpPlotPoleSettings(int r, int lr, float t, int v)
	{
		Radius = r;
		LevelRequirements = lr;
		Tax = t;
		Validity = v;
	}
}

class alpRaidTNT_BaseBuilding
{
	string Name;
	float OwnerON;
	float OwnerOFF;
	
	
	void alpRaidTNT_BaseBuilding(string n, float on, float off)
	{
		Name = n;
		OwnerON = on;
		OwnerOFF = off;
	}
	
	string GetType()
	{
		return Name;
	}
	
	float GetOwnerON()
	{
		return OwnerON;
	}	
	
	float GetOwnerOFF()
	{
		return OwnerOFF;
	}		
}

//typedef Param3<string,float,float>  alpRaidTNT_BaseBuilding;