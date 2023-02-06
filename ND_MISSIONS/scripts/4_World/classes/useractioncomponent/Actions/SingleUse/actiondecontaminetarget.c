
class ActionDecontamineTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}

};

class ActionDecontamineTarget: ActionDecontamineBase
{	
	void ActionDecontamineTarget()
	{
		m_CallbackClass = ActionDecontamineTargetCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_SPRAYPLANT;//CMD_ACTIONFB_SPRAYPLANT CMD_ACTIONFB_CLEANWOUNDSTARGET
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}
		
	override string GetText()
	{
		return "#action_decontamination";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( target)
		{
			PlayerBase target_player = PlayerBase.Cast(target.GetObject());
			if(target_player)
			{
				return true;
			}
			
		}
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if( target )
		{
			target.GetRP().Decontamination(true);
			Apply(action_data);
		}
	}
};