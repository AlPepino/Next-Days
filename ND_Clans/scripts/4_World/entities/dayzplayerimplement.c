modded class DayZPlayerImplement extends DayZPlayer
{
	bool 					alp_Is3rdPerson;
	
	override void HandleView()
	{	
		super.HandleView();
		
		if ( GetGame().GetWorld().Is3rdPersonDisabled() && ( GetND().GetClans().GetOptions().Enable3rdPersonCameraAtHome || GetND().GetClans().GetOptions().Enable3rdPersonCameraAtSafeZone || GetND().GetClans().GetOptions().Enable3rdPersonCameraInVehicle ) ){
			m_Camera3rdPerson = alp_Is3rdPerson;				
		}
		/*
		//! 3rd person camera
		if (GetGame().GetWorld().Is3rdPersonDisabled())
		{
			m_Camera3rdPerson = false;
		}
		else if (camChange)
		{
			m_Camera3rdPerson = !m_Camera3rdPerson;
		}
			*/		
	}
	
	void Set3DcameraALP(bool state){
		alp_Is3rdPerson = state;	
	}	
}