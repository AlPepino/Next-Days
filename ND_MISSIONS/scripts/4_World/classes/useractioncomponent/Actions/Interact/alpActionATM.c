
class alpActionATMCB : ActionInteractLoopBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAInteractLoop(2);
	}
};


class alpActionATM extends ActionInteractLoopBase 
{

	
	void alpActionATM()
	{
		m_CallbackClass		= alpActionATMCB;
		m_CommandUID =   DayZPlayerConstants.CMD_ACTIONFB_VIEWNOTE; //CMD_ACTIONFB_INTERACT 
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
		return "#action_atm";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( target.GetObject()  )
		{
			if ( GetND().GetMS().GetOptoinsTrader().ATM_NotRequiresPaymentCard )
			{//acces without card
				return true;
			}
			
			alp_Debitcard card;			
			if ( Class.CastTo( card, player.GetItemInHands() ) )
			{
				return true;
			}
			return false;
		}
		return false;
		
	}
	
	override void OnStartServer( ActionData action_data )
	{
		if ( GetND().GetMS().GetOptoinsTrader().ATM_NotRequiresPaymentCard )
		{//acces without card
			
			int guid2 = action_data.m_Player.GetPlayerHive().GetPlayerID();
			GetND().GetMS().GetTrader().GiveMeAccount( guid2 , action_data.m_Player );	
			
			return;
		}				
		
		
		alp_Debitcard card;			
		if ( Class.CastTo( card, action_data.m_Player.GetItemInHands() ) )
		{
			//check if is valid
			if ( !card.alp_CARD_ID )
			{
				int guid = action_data.m_Player.GetPlayerHive().GetPlayerID();
				int cardId = card.GetCardID();
				card.SetBankID( guid);	
				alpBANK.RegisterCard( guid, cardId);
			}
			
			GetND().GetMS().GetTrader().GiveMeAccount( card.GetBankID(), action_data.m_Player );
		}		
		

	}
	
	override void OnEndClient( ActionData action_data )
	{
		if (!GetGame().GetUIManager().FindMenu(ALP_MENU_ATM))
		{
			GetGame().GetUIManager().EnterScriptedMenu(ALP_MENU_ATM, NULL);
		}			
	
	}	
	

};