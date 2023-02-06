
modded class ActionStartEngine: ActionContinuousBase
{

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if (super.ActionCondition( player, target, item ))
		{
			
			
			if (!GetND().GetRP().GetVehicleOptions().RequiredKeyToStartEngine) 
				return true;
			
			CarScript car;
			
			alp_CarKey_Base key;
			
			if ( Class.CastTo(car,player.GetParent()) && Class.CastTo(key, player.GetItemInHands()) )
			{
				if ( car.GetAlpCarID() == key.GetAlpKeyID() || key.IsAdminKey() )				
					return true;
				else
					return false;
			}
			else return false;
			
		}
		else return false;
	
	}

};