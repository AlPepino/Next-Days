modded class MissionGameplay extends MissionBase
{
	override void OnUpdate(float timeslice){
		super.OnUpdate( timeslice );	
	
		if ( GetGame().GetWorld().Is3rdPersonDisabled() && ( GetND().GetClans().GetOptions().Enable3rdPersonCameraAtHome || GetND().GetClans().GetOptions().Enable3rdPersonCameraAtSafeZone || GetND().GetClans().GetOptions().Enable3rdPersonCameraInVehicle ) ){
			Input input = GetGame().GetInput();
		
			if ( input.LocalPress("UAPersonView",false) )
			{
				PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
				
				if ( player )
				{
					player.GetRP().alp_Camera3rdPerson = !player.GetRP().alp_Camera3rdPerson;							
				}			
			}	
		}
	}
	
	override void OnKeyPress(int key){
		super.OnKeyPress(key);
		if (key == KeyCode.KC_ESCAPE){

			if (GetUIManager().FindMenu(ALP_MENU_MANAGE_PLOTPOLE)){
				GetUIManager().CloseMenu(ALP_MENU_MANAGE_PLOTPOLE);
			}			
		}
	}
}
