modded class ContaminationStage1Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		
		player.GetRP().SetDisease(alpDiseases.POISONING_CHEMICAL_1);

	}
	

	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		player.GetRP().UnsetDisease(alpDiseases.POISONING_CHEMICAL_1);
	}
};