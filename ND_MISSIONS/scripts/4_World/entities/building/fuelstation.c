
modded class FuelStation extends BuildingSuper
{
	bool alp_WAS_ADDED;
	
	int alp_MIN_FUEL = 500;

	ref alpResourcesStation alp_Setting;
	
	float alp_LastAmmount;
	float alp_Ammount =  99999999;
	float alp_AmmountMax = 99999999;
	float alp_RefreshPerRestart;
	float alp_ChanceRefresh;
	
	void FuelStation()
	{
			
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.InitALP,100);	
		
	}
	void ~FuelStation()
	{
		delete alp_Setting;	
		
		
	}
	int GetMinFuelAmmount()
	{
		return alp_MIN_FUEL;
	}
	float GetRestockFuelAmmount()
	{
		return alp_RefreshPerRestart;
	}	

	void DrainFuelALP(float ammount)
	{
		alp_Ammount -= ammount;
		alp_Ammount = Math.Clamp(alp_Ammount, 0 , alp_AmmountMax );
	
		CheckMissionCondition();
	}
	
	void CheckMissionCondition()
	{		
		if ( GetGame().IsServer() && !alp_WAS_ADDED  && alp_Ammount < alp_MIN_FUEL )
		{		
			alp_WAS_ADDED = true;
			if ( alpPluginNDmissionsSystem.FuelStations.Find( this ) < 0 )
			{
				alpPluginNDmissionsSystem.FuelStations.Insert( this );
			}				

		}		
	}
	
	void AddFuelALP(float ammount)
	{
		alp_Ammount += ammount;
		alp_Ammount = Math.Clamp(alp_Ammount, 0 , alp_AmmountMax );	
		
	}	
	
	void SaveFuelStationALP()
	{
		if (GetGame().IsServer() && alp_LastAmmount != alp_Ammount )
		{
			
			if ( alp_Setting )
			{
				
				alp_Setting.Ammount    		= alp_Ammount;			
				
				JsonFileLoader<ref alpResourcesStation>.JsonSaveFile(ALP_FUELS_FOLDER + GetID().ToString() + ".json",  alp_Setting);	
			}		
		}
	}
	
		
	float GetFuelAmmountMax()
	{	
		return alp_AmmountMax;
	}
	
	float GetFuelAmmount()
	{
		return alp_Ammount;
	}
	
	bool HasFuelALP()
	{	
		return (int) alp_Ammount;
	}
	
	
	
	void SaveCurrentAmmount()
	{
		alp_LastAmmount = alp_Ammount;
	}
	
	
	void InitALP()
	{
	
		if (  GetGame().IsServer() && GetGame().IsMultiplayer()  &&  GetND().GetResources().GetOptions().EnableFuelstationManagement  )		
		{
	
			if (!FileExist(ALP_FUELS_FOLDER + GetID().ToString() + ".json"))
			{
					float amount 	= GetND().GetResources().GetDefaultFuelstations().DefaultAmmount;
					float max 		= GetND().GetResources().GetDefaultFuelstations().DefaultAmmountMax;
					float refresh 	= GetND().GetResources().GetDefaultFuelstations().DefaultRefreshPerRestart;
					float chance 	= GetND().GetResources().GetDefaultFuelstations().DefaultChanceRefresh;

					alp_Setting = new alpResourcesStation( GetID(), GetND().GetNotf().GetLocationsLabels().GetLocation(  GetPosition() ), GetPosition(), amount,max,refresh,chance );								
				
					JsonFileLoader<ref alpResourcesStation>.JsonSaveFile(ALP_FUELS_FOLDER + GetID().ToString() + ".json",  alp_Setting);	
			}		
			
			JsonFileLoader<ref alpResourcesStation>.JsonLoadFile(ALP_FUELS_FOLDER + GetID().ToString() + ".json",  alp_Setting);	
			
			if ( alp_Setting )
			{
				alp_Ammount				= alp_Setting.Ammount;
				alp_AmmountMax			= alp_Setting.AmmountMax;
				alp_RefreshPerRestart	= alp_Setting.RefreshPerRestart;
				alp_ChanceRefresh		= alp_Setting.ChanceRefresh;	
				
				
				if (alp_ChanceRefresh && alp_ChanceRefresh >= Math.RandomFloat01() ) //&& !alp_Refreshed)
				{
					//alp_Refreshed = true;
					AddFuelALP(alp_RefreshPerRestart);
					SaveFuelStationALP();
				}
				CheckMissionCondition();

				
			}
		}
	}
	
	


}
