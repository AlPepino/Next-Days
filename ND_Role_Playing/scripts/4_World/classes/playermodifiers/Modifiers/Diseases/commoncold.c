modded class CommonColdMdfr
{
	const int AGENT_THRESHOLD_ACTIVATE = 50;
	const int AGENT_THRESHOLD_DEACTIVATE = 21;
	
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		
		player.GetRP().SetDisease(alpDiseases.COMMONCOLD);

	}
	

	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		player.GetRP().UnsetDisease(alpDiseases.COMMONCOLD);
	}	
}