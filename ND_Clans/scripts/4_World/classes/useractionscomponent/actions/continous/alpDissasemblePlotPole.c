
class alpActionDisassemblePlotPoleCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(10); //default value can be set in recipes
	}
};



class alpActionDisassemblePlotPole : ActionContinuousBase
{

	
	void alpActionDisassemblePlotPole()	
	{
		m_CallbackClass = alpActionDisassemblePlotPoleCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
	}

	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNonRuined(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINonRuined;
	}	

	
	override string GetText()
	{
		return "#pp_context_menu_pack";
	}
	

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		
		Object targetObject = target.GetObject();
		alp_PlotPole plotpole = alp_PlotPole.Cast(targetObject);
		
		if ( plotpole )
		{
			return true;
		}
		
		return false;
	}

	
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		
		alp_PlotPole plotpole = alp_PlotPole.Cast(action_data.m_Target.GetObject());
		
		if ( plotpole )
		{
			plotpole.Disassemble();
		}
		
		
	}


};
