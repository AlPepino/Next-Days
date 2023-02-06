
modded class BrokenLegsMdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		
		player.GetRP().SetDisease(alpDiseases.BROKEN_LEGS );

	}
	

	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		player.GetRP().UnsetDisease(alpDiseases.BROKEN_LEGS);
	}
};
