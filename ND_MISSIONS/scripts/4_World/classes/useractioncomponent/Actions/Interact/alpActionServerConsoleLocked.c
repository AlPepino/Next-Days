class alpActionServerConsoleLocked: ActionInteractBase
{
	string alp_Title;

	void alpActionServerConsoleLocked()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
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
			alp_AccessCard_Base card = alp_AccessCard_Base.Cast(item);				
			if ( console && console.CanBeLockedALP() &&  console.IsLockedALP() && !console.IsRuinedALP() && !console.IsDamagedALP() && ( !card || card.GetKeyID() != console.GetAccesCardID() ) ) {
				SetActionTextALP( console.GetAccesCardID() );
				return true;
			}	
			return false;
		}
		

	
		return true;
	}
	
	void SetActionTextALP(int id){
		
		alp_Title = "#alp_action_console_requirescard";
		
		switch(id){
			case 0:
				alp_Title += " (" + alpUF.GetDisplayName( "alp_AccessCardRed" ) + ")";
				break;
			case 1:
				alp_Title += " (" + alpUF.GetDisplayName( "alp_AccessCardBlue" ) + ")";
				break;
			case 2:
				alp_Title += " (" + alpUF.GetDisplayName( "alp_AccessCardGreen" ) + ")";
				break;
			case 3:
				alp_Title += " (" + alpUF.GetDisplayName( "alp_AccessCardYellow" ) + ")";
				break;								
		}
	}

/*
	override void OnExecuteServer( ActionData action_data ){
	
	}
	
	
	override void OnExecuteClient( ActionData action_data ){
	}

*/		
}