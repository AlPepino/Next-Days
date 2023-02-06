modded class ContaminationStage2Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		
		player.GetRP().SetDisease(alpDiseases.POISONING_CHEMICAL_2);

	}
	

	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		player.GetRP().UnsetDisease(alpDiseases.POISONING_CHEMICAL_2);
	}
};