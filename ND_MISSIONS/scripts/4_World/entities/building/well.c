


modded class Well extends BuildingSuper
{

	
	ref alpResourcesStation alp_Setting;
	
	float alp_LastAmmount;
	float alp_Ammount =  99999999;
	float alp_AmmountMax = 99999999;
	float alp_RefreshPerRestart;
	float alp_ChanceRefresh;	
	
	void Well()
	{
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.InitALP,100);
			
	}	

	void DrainWaterALP(float ammount)
	{
		alp_Ammount -= ammount;
		alp_Ammount = Math.Clamp(alp_Ammount, 0 , alp_AmmountMax );
	
	}
	void AddWaterALP(float ammount)
	{
		alp_Ammount += ammount;
		alp_Ammount = Math.Clamp(alp_Ammount, 0 , alp_AmmountMax );	
		
	}	

	void SaveWellALP()
	{
		if (GetGame().IsServer() && alp_LastAmmount != alp_Ammount )
		{

			
			if ( alp_Setting )
			{		
				alp_Setting.Ammount    		= alp_Ammount;			
				
				JsonFileLoader<ref alpResourcesStation>.JsonSaveFile(ALP_WELLS_FOLDER + GetID().ToString() + ".json",  alp_Setting);	
			}		
		}
	}	
	float GetWaterAmmountMax()
	{	
		return alp_AmmountMax;
	}
	
	float GetWaterAmmount()
	{
		return alp_Ammount;
	}
	
	bool HasWaterALP()
	{	
		return (int) alp_Ammount;
	}
	
	
	
	void SaveCurrentAmmount()
	{
		alp_LastAmmount = alp_Ammount;
	}
	
	
	void InitALP()
	{

		if ( GetGame().IsServer() && GetGame().IsMultiplayer()   && GetND().GetResources().GetOptions().EnableWellManagement  )		
		{

			
			if (!FileExist(ALP_WELLS_FOLDER + GetID().ToString() + ".json"))
			{
					float amount 	= GetND().GetResources().GetDefaultWell().DefaultAmmount;
					float max 		= GetND().GetResources().GetDefaultWell().DefaultAmmountMax;
					float refresh 	= GetND().GetResources().GetDefaultWell().DefaultRefreshPerRestart;
					float chance 	= GetND().GetResources().GetDefaultWell().DefaultChanceRefresh;
							
					alp_Setting = new alpResourcesStation( GetID(), GetND().GetNotf().GetLocationsLabels().GetLocation(  GetPosition() ), GetPosition(), amount,max,refresh,chance );								
				
					JsonFileLoader<ref alpResourcesStation>.JsonSaveFile(ALP_WELLS_FOLDER + GetID().ToString() + ".json",  alp_Setting);	
			}		
			
			JsonFileLoader<ref alpResourcesStation>.JsonLoadFile(ALP_WELLS_FOLDER + GetID().ToString() + ".json",  alp_Setting);	
			
			if ( alp_Setting )
			{
				alp_Ammount				= alp_Setting.Ammount;
				alp_AmmountMax			= alp_Setting.AmmountMax;
				alp_RefreshPerRestart	= alp_Setting.RefreshPerRestart;
				alp_ChanceRefresh		= alp_Setting.ChanceRefresh;	
				
				
				if ( alp_ChanceRefresh >= Math.RandomFloat01() ) //&& !alp_Refreshed)
				{
					//alp_Refreshed = true;
					AddWaterALP(alp_RefreshPerRestart);
					SaveWellALP();
				}
				
			}
		}
	}		
}