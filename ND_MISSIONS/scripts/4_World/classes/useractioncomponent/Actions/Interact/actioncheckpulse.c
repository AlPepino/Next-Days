modded class ActionCheckPulse: ActionInteractBase
{

	
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (super.ActionCondition(player,target,item)){
			PlayerBase ntarget = PlayerBase.Cast(  target.GetObject() );
			if( ntarget && ntarget.IsPlayer())
			{
				return true;
			}
			return false;
		}
		else return false;
	}

}