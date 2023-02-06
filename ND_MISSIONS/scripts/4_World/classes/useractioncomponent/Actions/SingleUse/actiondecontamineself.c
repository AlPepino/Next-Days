class ActionDecontamineSelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}
};


class ActionDecontamineBase: ActionContinuousBase
{
	void Apply( ActionData action_data )
	{
		ItemBase item = action_data.m_MainItem;
		item.AddQuantity(-item.GetDisinfectQuantity());
		
	}
}


class ActionDecontamineSelf: ActionDecontamineBase
{
	float m_GramsConsumedPerUse;//left for legacy reasons
	
	void ActionDecontamineSelf()
	{
		m_CallbackClass = ActionDecontamineSelfCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_SPRAYPLANT;//CMD_ACTIONFB_INTERACT  CMD_ACTIONFB_STITCHUPSELF
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool HasTarget()
	{
		return false;
	}
		
	override string GetText()
	{
		return "#action_decontamination";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		
		return true;
	}
	

	override void OnFinishProgressServer( ActionData action_data )
	{


		action_data.m_Player.GetRP().Decontamination(true);
		
		Apply(action_data);
	}

	
};