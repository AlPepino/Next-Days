modded class ActionEatCan: ActionEatBig
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		
		if ( GetND().GetRP().GetPlayerOptions().MaskPreventConsume )
		{
			EntityAI mask = player.FindAttachmentBySlotName("Mask");
			
			if ( mask && !IsExceptionsALP(mask) )
				return false;
								
		}
		

		return super.ActionCondition(player, target, item);
	}
}

modded class ActionEatSmallCan: ActionEatBig
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		
		if ( GetND().GetRP().GetPlayerOptions().MaskPreventConsume )
		{
			EntityAI mask = player.FindAttachmentBySlotName("Mask");
			
			if ( mask && !IsExceptionsALP(mask) )
				return false;
								
		}
		

		return super.ActionCondition(player, target, item);
	}
};