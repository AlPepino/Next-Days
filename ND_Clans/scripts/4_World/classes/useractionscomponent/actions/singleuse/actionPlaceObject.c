
modded class ActionPlaceObject: ActionDeployObject
{
	bool WasPlaced;

    override void OnEndServer(ActionData action_data)
    {
		super.OnEndServer(action_data);
		
        if (action_data.m_MainItem.IsKindOf("alp_PlotPoleKit") && WasPlaced)
        {
				GetGame().ObjectDelete(action_data.m_MainItem);
				WasPlaced = false;
		}
	
    }
	 
	
	
    override void OnFinishProgress(ActionData action_data)
    {
		super.OnFinishProgress(action_data);
		
        if (action_data.m_MainItem.IsKindOf("alp_PlotPoleKit") )
        {
			WasPlaced = true;
		}
	
    }	

	/*
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if ( super.ActionCondition( player, target, item ) )
		{
			
			if ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) 
			{
				if ( player.IsAuthorized(item) )
				{
					return true;
				}
				else 
				{
					return false;
				}
			}
			
			return true;
		}
		else return false;
	}
*/
	
	override void OnStartServer( ActionData action_data )
	{
		super.OnStartServer( action_data );
		
		EntityAI entity_for_placing = action_data.m_MainItem;
		
		if ( entity_for_placing && entity_for_placing.IsKindOf("alp_PlotPoleKit") )
		{
			int playerID = action_data.m_Player.GetPlayerID();
			
			alp_PlotPoleKit ppk = alp_PlotPoleKit.Cast( entity_for_placing );
			
			ppk.alp_PlayerID = playerID;
					
		}
	}	
}