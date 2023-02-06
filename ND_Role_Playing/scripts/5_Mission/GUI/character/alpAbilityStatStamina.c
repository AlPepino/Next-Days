
class alpAbilityStatStamina extends alpAbilityStat
{

	override void SetValueProgres(float progress)
	{
		super.SetValueProgres(progress);
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player)
		{
			int level = player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue();		
			int cap = GetND().GetRP().GetPerkStaminaLevelCup();
			
			float rate = ( level / cap ) * 100;	
	
			SetValueLevel( rate );
		}
		

	}	
	

	
}