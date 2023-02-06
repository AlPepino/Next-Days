modded class ActionForceConsume
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase ntarget = PlayerBase.Cast(target.GetObject());

		if ( GetND().GetRP().GetPlayerOptions().MaskPreventConsume )
		{
			EntityAI mask = ntarget.FindAttachmentBySlotName("Mask");
			
			if ( mask && !IsExceptionsALP(mask) )
				return false;
								
		}	
		
		
		return super.ActionCondition(player, target, item);
	}
	
	

}