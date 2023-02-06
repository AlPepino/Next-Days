		
modded class ZombieBase extends DayZInfected
{
	

	override bool FightAttackLogic(int pCurrentCommandID, DayZInfectedInputController pInputController, float pDt)
	{
		
		
		if ( GetND().GetMS().GetOptoinsTrader().KillZombiesWhileAttackAtTrader )
		{
			m_ActualTarget = pInputController.GetTargetEntity();
		
			PlayerBase player;
			
			if ( Class.CastTo( player, m_ActualTarget) && !player.GetRP().IsAllowedDamage() )
			{
				m_AllTargetObjects.Clear();
				SetHealth01("","",0);
				
				return false;
			}
		}
		
		return super.FightAttackLogic( pCurrentCommandID,  pInputController,  pDt);

		
	}	
	
	override bool ResistContaminatedEffect()
	{
		bool  isResisted = super.ResistContaminatedEffect();
		
		if ( GetND().GetMS().GetOptionsRadiation().ZombiesResistToxicity )
		{		
			return true;
		}	
		return isResisted;
	}

}
		