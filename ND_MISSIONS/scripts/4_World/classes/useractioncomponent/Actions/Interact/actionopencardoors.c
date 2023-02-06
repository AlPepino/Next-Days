
modded class ActionOpenCarDoorsOutside: ActionCarDoorsOutside
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if (super.ActionCondition(player, target,item)){
			CarScript car;	
			if ( Class.CastTo(car, target.GetParent()) )
			{
				
				//dodelat podminku z GUID 	
				if ( car.GetInventory().IsInventoryUnlocked() || player.GetCommand_Vehicle() ) return true;
				else return false;
			}
			else return true;
			
		}
		else return false;
	}
	override void OnStartServer( ActionData action_data )
	{
		super.OnStartServer(action_data);
		CarScript car;
		
		//! player inside vehicle
		if( action_data.m_Player && action_data.m_Player.GetCommand_Vehicle() )
		{
			car = CarScript.Cast(action_data.m_Player.GetCommand_Vehicle().GetTransport());
			car.GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);		
		}

	}	

};