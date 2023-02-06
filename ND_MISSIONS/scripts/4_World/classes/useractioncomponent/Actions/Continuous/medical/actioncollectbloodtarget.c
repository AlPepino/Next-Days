modded class ActionCollectBloodTarget
{
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);

		PlayerBase ntarget = PlayerBase.Cast(action_data.m_Target.GetObject());						
		ItemBase blood = action_data.m_MainItem;
		
		if ( ntarget && ntarget.GetRP() && ntarget.GetRP().GetRadiationSickStage() > 0 )
		{//ruined blood
			blood.SetHealth("","",0);	
		}
				
	}
}