
class alpAbilityStatHunting extends alpAbilityStat
{

	override void SetValueProgres(float progress)
	{
		super.SetValueProgres(progress);
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player)
		{
			int level = player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue();		
			int cap = GetND().GetRP().GetPerkHuntingLevelCup();
			
			float rate = ( level / cap ) * 100;	
	
			SetValueLevel( rate );
		}
		

	}	
	

	
}