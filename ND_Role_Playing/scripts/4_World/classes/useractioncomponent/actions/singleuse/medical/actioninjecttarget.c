modded class ActionInjectTarget: ActionSingleUseBase
{

	override void OnEndServer( ActionData action_data )
	{
		if (action_data.m_WasExecuted && action_data.m_MainItem )
		{
			if (action_data.m_Player.GetRP().IsHero() )
			{
				action_data.m_Player.GetRP().ChangeReputation(   GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_HERO) );				
			}	
			else 
			{	
				action_data.m_Player.GetRP().ChangeReputation(   GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_BANDIT) );
			}				
		}		
		
		super.OnEndServer( action_data );
	}
		
	
};