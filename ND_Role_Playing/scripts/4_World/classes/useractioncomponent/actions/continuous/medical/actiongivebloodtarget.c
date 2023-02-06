modded class ActionGiveBloodTarget: ActionContinuousBase
{
	
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if(action_data.m_MainItem && target && action_data.m_Player )
		{
			if (action_data.m_Player.GetRP().IsHero() )
			{
				action_data.m_Player.GetRP().ChangeReputation(  GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_HERO) );				
			}	
			else 
			{	
				action_data.m_Player.GetRP().ChangeReputation(  GetND().GetRP().GetReputationBonusTreatOthers(ALP_RP_BANDIT) );
			}			
			
		}			
		
		
	}
	
	
	
};