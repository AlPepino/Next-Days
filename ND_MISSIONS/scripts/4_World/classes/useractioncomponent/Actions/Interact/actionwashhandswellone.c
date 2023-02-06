
modded class ActionWashHandsWellOne extends ActionInteractLoopBase
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Well well;
		
		if ( Class.CastTo( well, target.GetObject() )  && GetND().GetResources().GetOptions().EnableWellManagement && GetGame().IsServer() && !well.HasWaterALP() ) 
		{		
			return false;	
		}		
		
		return super.ActionCondition(  player,  target,  item );

	}


};
