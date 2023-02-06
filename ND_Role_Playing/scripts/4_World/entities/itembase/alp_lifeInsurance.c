
class alp_Card extends Inventory_Base
{
	int alp_DateStamp;
	
	
	int alp_Validity = -1; 
	
	
	
	void alp_Card()
	{	
		RegisterNetSyncVariableInt("alp_Validity");
		
	}	
	
	override void OnWorkStart()
	{
		
		if (GetGame().IsServer())
		{	
			SetTimeStampALP();
		}
		
	}
	
	float GetMaxEnergyALP()  //1000 means 7 day
	{
		string path = "CfgVehicles " + GetType() + " varEnergyMax";
		float energy = GetGame().ConfigGetFloat(path);
		return energy;
	}
	
	override void OnWork( float consumed_energy )
	{
		super.OnWork(consumed_energy);
		alp_Validity=1;
		
	}
	
	override void OnWorkStop()
	{
		super.OnWorkStop();
		alp_Validity = 0;

	}

	
	override string GetTooltip()
	{
		
		string tooltip = super.GetTooltip();

		
		if ( alp_Validity == -1 )
			tooltip = "#STR_alp_lifeinsurance_notactive";
		
		if ( alp_Validity == 0 )
			tooltip = "#STR_alp_lifeinsurance_expired";
		
		if ( alp_Validity == 1 ) 
		{
			
			float time = ( GetCompEM().GetEnergy() /GetMaxEnergyALP() )  * 7;
			
			string days = time.ToString();
			
			if (days.Length() > 3 )
				days = days.Substring(0,3);
			
			tooltip = tooltip + " " + days;
		}
		
		return tooltip;	
		
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionTurnOnHeatpack);
	}	
	
	bool IsLifeInsuranceValid()
	{
		return alp_Validity & 1;
	}

	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		
		if ( alp_Validity == 1 )
		{
			SetTimeStampALP();			
		}		
        ctx.Write( alp_DateStamp );
		

		
		ctx.Write( alp_Validity );

	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( super.OnStoreLoad( ctx, version ) )
		{
		
			ctx.Read( alp_DateStamp );
			ctx.Read( alp_Validity );
			return true;
		}
		else return false;
	}	
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if ( GetGame().IsServer() && GetCompEM().IsWorking() )
		{
			if (alp_Validity == 1 && alp_DateStamp)
			{
				SetEnergyALP();				
			}

		}
	}
	
	
	void SetEnergyALP()
	{
		
		
		int expiredDays = VerificationCardALP();		
		
		float energy = expiredDays * (1000/7);
								
		GetCompEM().ConsumeEnergy(energy);
		
		energy = GetCompEM().GetEnergy();	
		
		if (energy <= 0)
		{
			alp_Validity = 0;
		}
		
		SetSynchDirty();
	}
	
	
	
	void SetTimeStampALP()
	{
		int year, month, day;
		GetYearMonthDayUTC(year, month, day);			
		alp_DateStamp = year * 365 + month * 30 + day;			
	}
	
	int VerificationCardALP()
	{		
		int year, month, day,days;
		GetYearMonthDayUTC(year, month, day);			
	    days = year * 365 + month * 30	+ day;			
		
		days = days - alp_DateStamp;
		
		return days;
	}		
}


class alp_LifeInsuranceExclusive extends alp_Card
{
}
