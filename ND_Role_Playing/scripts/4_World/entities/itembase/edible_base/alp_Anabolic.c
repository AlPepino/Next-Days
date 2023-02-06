class alp_Anabolic: Epinephrine
{

	
	override void OnApply(PlayerBase player)
	{
		//player.GiveShock(100);
		player.GetStaminaHandler().SetStamina(100);
		
		if( player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ANABOLIC ) )//effectively resets the timer
		{
			player.GetModifiersManager().DeactivateModifier( rModifiers.MDF_ANABOLIC );
		}
		player.GetModifiersManager().ActivateModifier( rModifiers.MDF_ANABOLIC );
	}
};