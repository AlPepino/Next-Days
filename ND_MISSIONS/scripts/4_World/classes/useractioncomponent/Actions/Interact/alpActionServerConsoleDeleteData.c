class alpActionServerConsoleDeleteDataCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAInteractLoop(3);
	}
};

class alpActionServerConsoleDeleteData extends ActionInteractLoopBase
{

	
	void alpActionServerConsoleDeleteData()
	{
		m_CallbackClass		= alpActionServerConsoleDeleteDataCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_RESTRAINTARGET;  //CMD_ACTIONFB_INTERACT  CMD_ACTIONFB_HANDCUFFTARGET
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH; // | DayZPlayerConstants.STANCEMASK_CROUCH; STANCEMASK_ERECT
		m_HUDCursorIcon = CursorIcons.CloseHood;
		m_FullBody = true;
	}


	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}
	
	override string GetText(){
		return "#alp_action_console_delete";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item ){
		if ( !target ) 
			return false;
		
		if ( GetGame().IsClient() ) {
			if ( target.GetComponentIndex() != 1 ){
				return false;
			}
			
			alp_ServerConsole console = alp_ServerConsole.Cast(target.GetObject());
			
			if ( console && console.IsUnlockedALP() && !console.IsRuinedALP() && !console.IsDamagedALP() && console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_PANEL)&& console.IsSetSettingALP(alpMISSIONTRIGGER.CAN_BE_DATA_DELETED)  && !console.IsSetSettingALP(alpMISSIONTRIGGER.IS_DATA_DELETED) ) {
				return true;
			}

			return false;
		}
		return true;
	}
	

	override void OnEndServer( ActionData action_data )
	{
		alp_ServerConsole console = alp_ServerConsole.Cast(action_data.m_Target.GetObject());
		
		if ( console ) {
			console.DeleteData(action_data.m_Player);	
		}			
	}
	
	
	override void OnStartClient( ActionData action_data )	
	{
		alp_ServerConsole console;	
		if ( Class.CastTo(console, action_data.m_Target.GetObject()) )
		{
			if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
				SEffectManager.PlaySound("alp_KeyboardEffect_SoundSet", console.GetPosition() );	
		}		
	}
	
}