modded class ActionCollectBloodSelf
{
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);


		ItemBase blood = action_data.m_MainItem;
		
		if ( action_data.m_Player.GetRP().GetRadiationSickStage() > 0 )
		{//ruined blood
			blood.SetHealth("","",0);	
		}
		
		
	}
}