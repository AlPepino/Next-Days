
modded class ActionTestBloodSelf
{
	override void OnFinishProgressServer(ActionData action_data)
	{	
		super.OnFinishProgressServer(action_data);

		if ( GetND().GetRP().GetDiseases().MedicalTestReport )
		{		
			alpMedicTestReport.DisplayReport(this, action_data.m_Player, action_data.m_Player);
		}
	}
}