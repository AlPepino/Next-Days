
modded class ActionBuildPart: ActionContinuousBase
{
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

}