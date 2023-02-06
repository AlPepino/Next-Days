


modded class DayZPlayerImplement extends DayZPlayer
{

	
	override bool CanClimb( int climbType, SHumanCommandClimbResult climbRes )
	{
		if (super.CanClimb(  climbType,  climbRes ))
		{
			
			
			if( GetND().GetRP().GetPlayerOptions().DisableClimbOverVehicle && climbRes  )
			{	
				CarScript car;
				if (climbRes.m_GrabPointParent && Class.CastTo(car,climbRes.m_GrabPointParent ) )
					return false;	

				if (climbRes.m_ClimbStandPointParent && Class.CastTo(car,climbRes.m_ClimbStandPointParent ) )
					return false;					
				
				if (climbRes.m_ClimbOverStandPointParent && Class.CastTo(car,climbRes.m_ClimbOverStandPointParent ) )
					return false;	
			}
			
			return true;
		}
		else return false;
	}

	override bool CanJump()
	{
		if (super.CanJump())
		{
			if (GetND().GetRP().GetPlayerOptions().DisableClimbOverVehicle)
			{
				autoptr array<Object> nearest_objects = new array<Object>;
				autoptr array<CargoBase> proxy_cargos = new array<CargoBase>;
		
				GetGame().GetObjectsAtPosition( GetPosition() , 6 , nearest_objects, proxy_cargos ); 													
				for (int i = 0; i < nearest_objects.Count();i++)
				{
					CarScript car
					if (Class.CastTo(car,nearest_objects.Get(i) ))
					{
						return false;	
					}
				}		
					
				return true;
			}
			
			
			return true;		
		}
		else
			return false;
	}	
		
}

