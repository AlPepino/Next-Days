
class alpAddFriendAction: ActionInteractBase
{

	void alpAddFriendAction()
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


	override string GetText()
	{
		return "#ip_addfriend";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !GetND().GetClans().GetOptions().EnableClans || !player.GetRP().GetClan() )
			return false;
		
		PlayerBase ntarget = PlayerBase.Cast(  target.GetObject() );

		if( ntarget && ntarget.IsAlive() && ntarget.GetIdentity() && !ntarget.IsLiftWeapon() && ntarget.GetClanID() == -1  )
		{
			return true;
		}
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		PlayerBase ntarget = PlayerBase.Cast(  action_data.m_Target.GetObject() );
		
		alpClanData clan = action_data.m_Player.GetRP().GetClan();
		if (ntarget && clan)
		{
			GetND().GetClans().AddMember( ntarget, clan);
			
			GetND().GetNotf().SendMessage( ntarget, ALPMSTYPE.SMPERSONAL, "#ip_beenaddedtoclan " + clan.Name );
		}		
		

	}
	
	

}