class alpActionServerConsoleCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAInteractLoop(3);
	}
};

class alpActionServerConsole extends ActionInteractLoopBase
{
	string alp_Title;
	
	void alpActionServerConsole()
	{
		m_CallbackClass		= alpActionServerConsoleCB;
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
		return alp_Title;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item ){
		if ( !target ) 
			return false;
		
		if ( GetGame().IsClient() ) {
			if ( target.GetComponentIndex() != 1 ){
				return false;
			}
			
			alp_ServerConsole console = alp_ServerConsole.Cast(target.GetObject());
			
			int actionType = console.GetTypeOfManagedMissionAction();
			if ( console && console.IsSetSettingALP(alpMISSIONTRIGGER.ENABLED) && console.IsUnlockedALP() && !console.IsRuinedALP() && !console.IsDamagedALP() && actionType ) {
				SetTextALP( actionType, console.IsSwapedActionTitle() );
				return true;
			}	
			return false;
		}
		return true;
	}
	
	void SetTextALP(int action, bool swapedTitle) {
		
		
		if ( action == alpMMACTION.ACTIVE || action == alpMMACTION.SET_TIME_TO_ACTIVE || action == alpMMACTION.CANCEL_DEACTIVE_TIME ) {
			alp_Title = "#alp_action_console_deactivate";
		} else {
			alp_Title = "#alp_action_console_activate";			
		}
		
		if ( !swapedTitle ) {
			if ( alp_Title == "#alp_action_console_activate" ) {
				alp_Title = "#alp_action_console_deactivate";
			} else {
				alp_Title = "#alp_action_console_activate";
			}
		} 	

	}

	override void OnEndServer( ActionData action_data )
	{
		alp_ServerConsole console = alp_ServerConsole.Cast(action_data.m_Target.GetObject());
				
		if (console){ 
			console.MakeReadyMissionAction(action_data.m_Player);
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