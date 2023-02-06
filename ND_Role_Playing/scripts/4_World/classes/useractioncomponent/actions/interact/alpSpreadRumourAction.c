
class alpSpreadRumourAction: ActionInteractBase
{

	void alpSpreadRumourAction()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTMan(4);
		m_ConditionItem = new CCINone;
	}


	override string GetText()
	{
		return "#npc_gossipmenu";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{

		if (GetGame().IsClient())
		{
			if (GetGame().GetUIManager().FindMenu(ALP_MENU_SPREADRUMOUR) )
				return false;		
		}
		

		alpNPC ntarget = alpNPC.Cast(  target.GetObject() );
		if( ntarget && ntarget.IsAlive() && ntarget.alp_StockID > 0 && ntarget.CanSpreadRumoursMenu() && ntarget.CanSpeakWithMe(player) )
		{
			return true;
		}
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		
		alpNPC npc = alpNPC.Cast( action_data.m_Target.GetObject() );

		if (npc)
		{
			action_data.m_Player.GetRP().GetCart().SetNPCid( npc.alp_StockID,  npc.alp_IDmission  );
			action_data.m_Player.GetSyncData().RegisterToStats( true );
			
			action_data.m_Player.GetSyncData().ForceSync();
			GetND().GetMS().GetTrader().GiveMeStock( npc.alp_StockID , action_data.m_Player, true );
		}		
		

	}
	
	
	override void OnExecuteClient( ActionData action_data )
	{
		
		alpNPC npc = alpNPC.Cast( action_data.m_Target.GetObject() );

		if (npc)
		{
			GetND().GetMS().GetTrader().SetNPC(npc.alp_StockID);						
			action_data.m_Player.GetRP().GetCart().SetNPCid( npc.alp_StockID  );

			if (!GetGame().GetUIManager().FindMenu(ALP_MENU_SPREADRUMOUR))
			{
				GetGame().GetUIManager().EnterScriptedMenu(ALP_MENU_SPREADRUMOUR, NULL);
			}						
			
		}		

	}
	

}