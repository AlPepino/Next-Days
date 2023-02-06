

class alpActionServerConsoleUnlock: ActionInteractBase
{

	void alpActionServerConsoleUnlock()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;//CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		//m_HUDCursorIcon = CursorIcons.CloseHood;
	}


	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;//CCINone;CCINonRuined
		m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
	}
	
	override string GetText(){
		return "#alp_action_console_login";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item ){
		
		if ( !target ) 
			return false;
		

		if ( GetGame().IsClient() ) {		
			if ( !item || item.IsRuined() ){
				return false;
			}			
			
			if ( target.GetComponentIndex() != 1 ){
				return false;
			}
			alp_ServerConsole console = alp_ServerConsole.Cast(target.GetObject());
			alp_AccessCard_Base card = alp_AccessCard_Base.Cast(item);
			if ( console && console.IsLockedALP() && !console.IsRuinedALP() && !console.IsDamagedALP() && card && card.GetKeyID()==console.GetAccesCardID()) {
			
				return true;
			}	
			return false;
		}
		

	
		return true;
		
	}


	
	override void OnExecuteServer( ActionData action_data ){
	
		
		alp_ServerConsole console = alp_ServerConsole.Cast( action_data.m_Target.GetObject() );
		if (console){
			console.UnlockConsoleALP();
		}
		ItemBase item =  action_data.m_Player.GetItemInHands();
		if (  item ) {
			MiscGameplayFunctions.DealAbsoluteDmg( item, 20); 
		}

	}
	

	
}


