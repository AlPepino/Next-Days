

//-----------------------------------------------------------------------------------------------
// DayZPlayerTypeCreate - main dayz type config
//-----------------------------------------------------------------------------------------------

modded class ModItemRegisterCallbacks 
{
	
	override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior) 
	{
		super.RegisterOneHanded(pType, pBehavior);
		pType.AddItemInHandsProfileIK("alp_Card", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/gear/charcoal_tablets.anm");	
		pType.AddItemInHandsProfileIK("alp_Debitcard", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/gear/charcoal_tablets.anm");	
		pType.AddItemInHandsProfileIK("alp_AccesCard_Base", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/gear/charcoal_tablets.anm");	
		pType.AddItemInHandsProfileIK("alp_CarKey_Base", "dz/anims/workspaces/player/player_main/props/player_main_1h_keys.asi", pBehavior,"dz/anims/anm/player/ik/gear/handcuff_keys.anm");	
		pType.AddItemInHandsProfileIK("alp_geiger_counter", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/gear/battery_charger.anm");
		
		pType.AddItemInHandsProfileIK("alp_Coin", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/gear/9v_battery.anm");
		pType.AddItemInHandsProfileIK("alp_Money", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/gear/charcoal_tablets.anm");	
		pType.AddItemInHandsProfileIK("alp_HouseKey_Base", "dz/anims/workspaces/player/player_main/props/player_main_1h_keys.asi", pBehavior,"dz/anims/anm/player/ik/gear/handcuff_keys.anm");			
		
		//pType.AddItemInHandsProfileIK("alp_ItemPDA", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior,"dz/anims/anm/player/ik/gear/personalradio.anm");
		pType.AddItemInHandsProfileIK("alp_ItemPDA", "dz/anims/workspaces/player/player_main/props/player_main_1h_compass.asi", pBehavior,"dz/anims/anm/player/ik/gear/compass.anm");
	}
	
	
	override void RegisterTwoHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior) 
	{
		super.RegisterTwoHanded(pType, pBehavior);
		pType.AddItemInHandsProfileIK("alp_Radioactive_Barrel", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,"dz/anims/anm/player/ik/heavy/55galDrum.anm");

	}	
}

