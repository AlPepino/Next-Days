
class alpActionDecontaminateCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAInteractLoop(UATimeSpent.WASH_HANDS);
	}
};


class alpActionDecontaminate extends ActionInteractLoopBase 
{

	
	void alpActionDecontaminate()
	{
		m_CallbackClass		= alpActionDecontaminateCB;
		m_CommandUID =   DayZPlayerConstants.CMD_ACTIONFB_WASHHANDSWELL; //CMD_ACTIONFB_VIEWNOTE 
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;

	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);

	}

	override string GetText()
	{
		return "#action_decontamination";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return target.GetObject() &&  target.GetObject().GetType() == "Land_Medical_Tent_Shower";
		
	}
	
	override void OnStartServer( ActionData action_data )
	{
		
		Land_Medical_Tent_Shower shower = Land_Medical_Tent_Shower.Cast( action_data.m_Target.GetObject() );		
		
		if ( shower )
		{
			shower.StartShower();
		}
		
		
		
	}
	
	
	
	
	override void OnEndServer( ActionData action_data )
	{
		
		
		action_data.m_Player.GetRP().Decontamination(true);
		
		if (action_data.m_State == UA_FINISHED)
		{
			PluginLifespan module_lifespan = PluginLifespan.Cast( GetPlugin( PluginLifespan ) );
			module_lifespan.UpdateBloodyHandsVisibility( action_data.m_Player, false );
		}	
		
		Land_Medical_Tent_Shower shower = Land_Medical_Tent_Shower.Cast( action_data.m_Target.GetObject() );		
		
		if ( shower )
		{
			shower.StopShower();
		}			
	}
};