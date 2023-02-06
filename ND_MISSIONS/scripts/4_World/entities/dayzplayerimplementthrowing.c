modded class DayZPlayerImplementThrowing
{

	override bool CanContinueThrowing(HumanInputController pHic)
	{
		PlayerBase player = PlayerBase.Cast( m_Player );
		
		if (player && player.GetRP().IsInTradeZone() && ! player.GetRP().IsAllowedDamage() ) 
			return false;		
		
		return super.CanContinueThrowing(pHic);
	}

}