
class alpActionServerConsoleRepairCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime( UATimeSpent.BASEBUILDING_REPAIR_FAST );
	}
};

class alpActionServerConsoleRepair: ActionContinuousBase
{

	
	void alpActionServerConsoleRepair()
	{
		m_CallbackClass = alpActionServerConsoleRepairCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody = true;
		m_LockTargetOnUse = false;
		m_Text = "#repair";
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined; //To change?
		m_ConditionTarget 	= new CCTObject(UAMaxDistances.REPAIR);//CCTCursor
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		//Action not allowed if player has broken legs
		if (player.GetBrokenLegs() == eBrokenLegs.BROKEN_LEGS)
			return false;
		
		
		if ( GetGame().IsClient() ) {
			alp_ServerConsole console = alp_ServerConsole.Cast(target.GetObject());
			if ( console && console.IsDamagedALP() && !console.IsRuinedALP() ) {
				return true;
			}
			return false;
		} 
		return true;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{

		alp_ServerConsole console = alp_ServerConsole.Cast( action_data.m_Target.GetObject() );
		if (console){
			console.RepairConsoleALP();
		
			if ( action_data.m_MainItem ) {
				if (action_data.m_MainItem.HasQuantity())
				{
					action_data.m_MainItem.AddQuantity(-35,true);
				}
				else
				{
					MiscGameplayFunctions.DealAbsoluteDmg( action_data.m_MainItem, 35); 
				}					
				
			}	
		}
		
	}

};