
//-----------------------------------------------------------------------------------------------
// DayZPlayerTypeCreate - main dayz type config
//-----------------------------------------------------------------------------------------------

modded class ModItemRegisterCallbacks 
{
	


	override void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior) 
	{
		super.RegisterTwoHanded(pType, pBehavior);
		pType.AddItemInHandsProfileIK("alp_PlotPoleKit", "dz/anims/workspaces/player/player_main/player_main_2h.asi", pBehavior,"dz/anims/anm/player/ik/two_handed/advanced_spear.anm");

	}	

}

