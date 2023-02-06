
// Script File
class alpActionStartMission: ActionInteractBase
{
	string alp_Title;
	
	void alpActionStartMission()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
		m_ConditionItem = new CCINone;
	}

	string alp_WantedItemName;
	override string GetText()
	{
		return alp_Title;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{

		if ( GetGame().IsClient() )
		{
			alpNPC ntarget = alpNPC.Cast(  target.GetObject() );
			//Print("NPC " + ntarget.alp_MissionTriggerSetting + " mise " + ntarget.alp_MissionManaged);
			int actionType = ntarget.GetTypeOfManagedMissionAction();
			if( ntarget &&  ntarget.IsSetSettingALP(alpMISSIONTRIGGER.ENABLED) && ntarget.IsAlive() && ntarget.IsErectedALP() && ntarget.CanSpeakWithMe(player) && actionType )
			{
			
				SetTextALP( actionType, ntarget.IsSwapedActionTitle() );
				return true;
			}		
			return false;
		}
		return true;
	}
	
	
	void SetTextALP(int action, bool swapedTitle) {
		if ( !swapedTitle ){
			if ( action == 1 ) {
				alp_Title = "#alp_action_npc_talk";
			} else {
				alp_Title = "#alp_action_npc_talkagain";	
			}
		} else {
			if ( action == 1 ) {
				alp_Title = "#alp_action_npc_talkagain";
			} else {
				alp_Title = "#alp_action_npc_talk";	
			}			
		}
	}

	
	override void OnExecuteServer( ActionData action_data )
	{
		alpNPC npc = alpNPC.Cast( action_data.m_Target.GetObject() );
		
		if (npc){
			npc.MakeReadyMissionAction(action_data.m_Player);	

			if ( !npc.alp_RewardWasGiven && npc.alp_GiveItemWhenActivate != "" ) {
					
				GetGame().CreateObjectEx(npc.alp_GiveItemWhenActivate, npc.GetPosition() + ( npc.GetDirection() * 0.5 ), ECE_PLACE_ON_SURFACE);	
					
				npc.alp_RewardWasGiven == true;
				
			}
		}	
	}


}