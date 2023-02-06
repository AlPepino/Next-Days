
modded class WoundInfectStage1Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		
		player.GetRP().SetDisease(alpDiseases.WOUNDINFECTION_1);

	}
	

	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		if (!player.GetModifiersManager().IsModifierActive(eModifiers.MDF_WOUND_INFECTION2))
			player.GetRP().UnsetDisease(alpDiseases.WOUNDINFECTION_1);
	}	
}

modded class WoundInfectStage2Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		
		player.GetRP().SetDisease(alpDiseases.WOUNDINFECTION_2);

	}
	

	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		player.GetRP().UnsetDisease(alpDiseases.WOUNDINFECTION_2);
	}	
}