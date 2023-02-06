

modded class alpActionDigInRadioactiveBarrel: ActionContinuousBase
{	

	
	override float GetReputationBonus(PlayerBase player ){
		float rep = 0;
		if ( player ) {
			if (player.GetRP().IsHero() ) {
				rep =  GetND().GetRP().GetReputationBonusDigInRadioactiveBarrel(ALP_RP_HERO);			
			} else {	
				rep =  GetND().GetRP().GetReputationBonusDigInRadioactiveBarrel(ALP_RP_BANDIT);	
			}		
		}
		return rep;
	}
}
