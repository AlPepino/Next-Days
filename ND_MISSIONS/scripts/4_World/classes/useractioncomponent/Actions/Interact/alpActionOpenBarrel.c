// Script File
class alpActionOpenBarrel: ActionInteractBase
{

	void alpActionOpenBarrel()
	{

		//m_Animation = "open";	
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.OpenHood;
	}



	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
		if ( target_object.IsItemBase() )
		{
			alp_Radioactive_Barrel ntarget = alp_Radioactive_Barrel.Cast( target_object );
			if( ntarget )
			{
				if( !ntarget.IsLocked() && !ntarget.IsOpen() )
				{
					return true;
				}
			}
		}
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		Object target_object = action_data.m_Target.GetObject();
		alp_Radioactive_Barrel ntarget = alp_Radioactive_Barrel.Cast( target_object );
		if( ntarget )
		{
			ntarget.Open();
		}
	}
	
	override void OnEndServer( ActionData action_data )
	{
		Object target_object = action_data.m_Target.GetObject();
		alp_Radioactive_Barrel ntarget = alp_Radioactive_Barrel.Cast( target_object );
		if( ntarget )
		{
			ntarget.SoundSynchRemoteReset();
		}
	}
}