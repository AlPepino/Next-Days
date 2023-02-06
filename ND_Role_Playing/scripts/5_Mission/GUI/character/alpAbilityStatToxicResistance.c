
class alpAbilityStatToxicResistance extends alpAbilityStat
{

	override void SetValueProgres(float progress)
	{
		super.SetValueProgres(progress);
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player)
		{
			int level = player.GetSyncData().GetElement( alpRPelements.TOXIC_RESIST ).GetValue();		
			int cap = GetND().GetRP().GetPerkToxicResistanceLevelCup();
			
			float rate = ( level / cap ) * 100;	
	
			SetValueLevel( rate );
		}
		

	}	
	

	
}