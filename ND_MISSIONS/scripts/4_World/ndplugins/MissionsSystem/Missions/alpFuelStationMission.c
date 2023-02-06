//noRadiation Zone 
class alpFuelStationMission extends alpMission
{
	ref array<FuelStation> alp_FuelStations

	void ~alpFuelStationMission()
	{
		delete alp_FuelStations;					
	}
//-------------------------------------------------------------------
//***************************//
//adjust default setting
//***************************//			
	override void OnInit()
	{
		//messages setting
		alp_SendInfoStart	= ALPMSTYPE.MMMISSIONSTART;
		alp_SendInfoEnd		= ALPMSTYPE.MMMISSIONEND;
		alp_AlertInfoIn		= ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut	= ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn		= ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut	= ALPMSTYPE.MMPERSONAL;		
		
		alp_FuelStations 	= new array<FuelStation>;
	}
	
//-------------------------------------------------------------------
//***************************//
//First spawn condition - verification available spot
//***************************//		
	override protected bool SetPosition()
	{
		
		
		array<float> coordinates = GetND().GetMS().GetFreePlace().GetPositionFS( this );
		
		if ( coordinates.Count() >= 4 )
		{
			alp_Position = Vector( coordinates.Get(0), coordinates.Get(1), coordinates.Get(2) );
			alp_Angle = Vector(  coordinates.Get(3), 0 , 0 );
			alp_Angle = alp_Angle.GetRelAngles();

			return true;
		} 
		else
		{
			return false;
		}
				
	}	
	
	override bool IsMissionCreated()
	{
		bool condition = super.IsMissionCreated();
		if ( condition )
		{//restock fuel in station nearby
			RestockFuelStation();		
			return true;
		}
		return false;
			
	}
	
	void RestockFuelStation()
	{
		alp_FuelStations.Clear();
		
		array<Object> objects = new array<Object>;
		array<CargoBase> proxyCargos = new array<CargoBase>;
		GetGame().GetObjectsAtPosition( GetPosition() , 50.0, objects, proxyCargos);
	

		int c = objects.Count();
		for (int i = 0; i < c; i++)
		{
			Object o = objects[i];

			if (o && o.IsFuelStation())
			{
				FuelStation fs = FuelStation.Cast(o);
				if (fs && fs.GetFuelAmmount() < fs.GetMinFuelAmmount() )
				{
					
					float max = fs.GetFuelAmmountMax() - fs.GetFuelAmmount();
					
					max = max * Math.RandomFloat(0.4,1.0);
					
					fs.AddFuelALP( max );
					fs.SaveFuelStationALP();
										
					//delete fuelstation
					alpPluginNDmissionsSystem.FuelStations.RemoveItem( fs );					
					
					alp_FuelStations.Insert( fs );
				}
				
			}
		}	
	}
	
	override void DespawnMission()
	{		
		super.DespawnMission();	
		alp_FuelStations.Clear();
		alp_Position = "0 0 0";
	}	
//-------------------------------------------------------------------
//***************************//
//Rewrite default methods
//***************************//		


	override protected bool CheckSecuredCondition(float timeslice) {	
		if ( super.CheckSecuredCondition( timeslice )  &&  !IsAvailableFuel() ) {
			return true;
		}
		return false;
	}
	
	override protected bool CheckFailedCondition(float timeslice) {	
		if ( IsFuelStationRuined() ) {
			return true;
		}
		return false;
	}	

	bool IsAvailableFuel()
	{

		for(int i = 0; i < alp_FuelStations.Count();i++)
		{
			FuelStation fs = alp_FuelStations.Get(i);
			if (fs && fs.GetFuelAmmount() > fs.GetMinFuelAmmount())
			{
				return true;
			}	
		}		
		return false;
	}
	
	bool IsFuelStationRuined()
	{

		for(int i = 0; i < alp_FuelStations.Count();i++)
		{
			FuelStation fs = alp_FuelStations.Get(i);
			if (fs && !fs.IsRuined() )
			{
				return false;
			}	
		}		
		return true;
	}	
}