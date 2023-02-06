modded class ActionEatFruit
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