modded class ActionDrinkWellContinuous : ActionContinuousBase
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		
		if ( GetND().GetRP().GetPlayerOptions().MaskPreventConsume )
		{
			EntityAI mask = player.FindAttachmentBySlotName("Mask");
			
			if ( mask && !IsExceptionsALP(mask) )
				return false;
								
		}
		
		Well well;
		
		if ( Class.CastTo( well, target.GetObject() )  && GetND().GetResources().GetOptions().EnableWellManagement && GetGame().IsServer() && !well.HasWaterALP() ) 
		{		
			return false;	
		}			

		return super.ActionCondition(player, target, item);
	}
	
	override bool ActionConditionContinue( ActionData action_data )
	{
		Well well;
		
		if ( Class.CastTo( well, action_data.m_Target.GetObject() )  && GetND().GetResources().GetOptions().EnableWellManagement && GetGame().IsServer() && !well.HasWaterALP() ) 
		{		
			return false;	
		}
		
		return super.ActionConditionContinue(action_data ) ;
	}	
	
		
	override void OnFinishProgressServer( ActionData action_data )
	{
		Param1<float> nacdata = Param1<float>.Cast( action_data.m_ActionComponent.GetACData() );
		float amount;
		
		Well well;
		if ( GetND().GetResources().GetOptions().EnableWellManagement && Class.CastTo( well, action_data.m_Target.GetObject() ) )
		{					
			
			if(nacdata)
			{
				amount = UAQuantityConsumed.DRINK;
				
				well.DrainWaterALP( amount );
			}
		}
				

		if(nacdata)
		{
			amount = UAQuantityConsumed.DRINK;

			
			if ( action_data.m_Player.GetRP().IsRadiationHigh() )
			{
				action_data.m_Player.Consume(NULL,amount, alpeConsumeType.ENVIRO_WELL_CONTAMINED);
			}
			else
			{
				action_data.m_Player.Consume(NULL,amount, EConsumeType.ENVIRO_WELL);
			}			
			
		}
		
		if ( action_data.m_Player.HasBloodyHands() && !action_data.m_Player.GetInventory().FindAttachment( InventorySlots.GLOVES ) )
		{
			action_data.m_Player.SetBloodyHandsPenalty();
		}
		
	}
	
	override void OnStartServer(ActionData action_data)
	{
		
		super.OnStartServer(action_data);
		Well well;
		if ( Class.CastTo( well, action_data.m_Target.GetObject() )  && GetND().GetResources().GetOptions().EnableWellManagement ) 
		{
			well.SaveCurrentAmmount();
		}		
	}	
	
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		Well well;
		if ( Class.CastTo( well, action_data.m_Target.GetObject() )  && GetND().GetResources().GetOptions().EnableWellManagement ) 
		{
			well.SaveWellALP();
		}		
	}	
}