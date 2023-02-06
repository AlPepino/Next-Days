modded class FeverMdfr
{
	
	override bool ActivateCondition(PlayerBase player)
	{
		if ( !GetND().GetRP().GetDiseases().FeverActive )
			return false;
		
		
		return super.ActivateCondition( player );
	}	
	
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		
		player.GetRP().SetDisease(alpDiseases.FEVER);

	}
	

	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		player.GetRP().UnsetDisease(alpDiseases.FEVER);
	}	
}
