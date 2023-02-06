modded class ActionTestBloodTarget
{
	override void OnFinishProgressServer( ActionData action_data )
	{	
		super.OnFinishProgressServer(action_data);

		PlayerBase ntarget = PlayerBase.Cast( action_data.m_Target.GetObject() );

		if ( GetND().GetRP().GetDiseases().MedicalTestReport  )
		{
			alpMedicTestReport.DisplayReport(this, action_data.m_Player, ntarget);
		}
	}
}