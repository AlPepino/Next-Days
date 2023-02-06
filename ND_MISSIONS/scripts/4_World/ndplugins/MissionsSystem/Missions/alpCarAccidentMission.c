//Car Accident Mission
class alpCarAccidentMission extends alpMission
{



//-------------------------------------------------------------------
//***************************//
//adjust default setting
//***************************//			
	override void OnInit()
	{
		//messages setting
		alp_SendInfoStart	= ALPMSTYPE.MMMISSIONCARSTART;
		alp_SendInfoEnd		= ALPMSTYPE.MMMISSIONCAREND;
		alp_AlertInfoIn		= ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut	= ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn		= ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut	= ALPMSTYPE.MMPERSONAL;		
	}
	
//-------------------------------------------------------------------
//***************************//
//Rewrite default methods
//***************************//		


	override protected bool CheckFailedCondition(float timeslice) {	
		if ( IsVehiclesRuined() ) {
			return true;
		}
		return false;
	}

	override protected bool CheckSecuredCondition(float timeslice) {	
		if ( super.CheckSecuredCondition( timeslice )  && IsVehicleTheft() ) {
			return true;
		}
		return false;
	}

	override protected bool SpawnVehicles(bool missionSecured = false)
	{
		if (super.SpawnVehicles(missionSecured))
		{ 
			if ( GetND().GetMS().GetOptions().DamageSpawnedVehiclesInMission ) 
				DamageCar();	
			
			return true;
		}
		else return false;
	}
	

//-------------------------------------------------------------------
//***************************//
//Private usefull methods
//***************************//		
	private void DamageCar()
	{						
		ItemBase radiator,battery;	
		
		foreach (alpMissionElement e : alp_Vehicles)
		{	
			Transport vehicle;
			
			if ( Class.CastTo( vehicle, e.Get() ) ) {
				Class.CastTo(radiator,vehicle.FindAttachmentBySlotName("CarRadiator"));
				float damage;
				if (radiator)
				{
					damage = Math.RandomFloat(20,80);
					radiator.SetHealth("", "Health",damage);
				}
				
				Class.CastTo(battery,vehicle.FindAttachmentBySlotName("CarBattery"));			
				if (battery)
				{
					damage = Math.RandomFloat(20,80);				
					battery.SetHealth("", "Health",damage);					
				}						
			}				
		}		
	}	
	
	private bool IsVehicleTheft()
	{
		CarScript car;
		foreach (alpMissionElement e : alp_Vehicles)
		{	
			Transport vehicle;
			if ( Class.CastTo( vehicle, e.Get() ) ) {
				if ( Class.CastTo( car, vehicle) )
				{
					if (car.IsMissionObject())
						return false;
				}
				HelicopterScript heli;
				if ( Class.CastTo( heli, vehicle) )
				{
					if (heli.IsMissionObject())
						return false;				
				}				
			}		
		}	
		return true;
	}
	
	private bool IsVehiclesRuined()
	{
		bool ruined = true;
		int id;
		CarScript car;
		
		for( int i = 0; i < alp_Vehicles.Count(); ){
			alpMissionElement e = alp_Vehicles.Get(i);
			Transport vehicle;
			if ( Class.CastTo( vehicle, e.Get() ) ) {
				if ( Class.CastTo( car, vehicle) )
				{
					if (!car.IsRuined()){
						ruined = false;
					} else {
						id = e.GetID();	
						m_Hive.RemoveCar(id);	
						alp_Vehicles.Remove(i);	
						continue;	
					}
						
				}
				HelicopterScript heli;
				if ( Class.CastTo( heli, vehicle) )
				{
					if (!heli.IsRuined()) {
						ruined = false;	
					} else {
						id = e.GetID();	
						m_Hive.RemoveCar(id);	
						alp_Vehicles.Remove(i);	
						continue;					
					}									
				}					
			} else {
				id = e.GetID();	
				m_Hive.RemoveCar(id);		
				alp_Vehicles.Remove(i);				
				continue;
			}		
			i++;
		}

		return ruined;
	}	
}