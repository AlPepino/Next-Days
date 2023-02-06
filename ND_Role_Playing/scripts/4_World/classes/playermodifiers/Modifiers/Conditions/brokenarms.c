
modded class BrokenArmsMdfr: ModifierBase
{

	
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);

		
		player.GetRP().SetDisease(alpDiseases.BROKEN_ARMS );

	}
	

	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		player.GetRP().UnsetDisease(alpDiseases.BROKEN_ARMS);
	}
};