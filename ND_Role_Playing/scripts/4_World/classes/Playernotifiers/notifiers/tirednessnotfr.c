// Script File
enum alpeNotifiers : eNotifiers
{
	NTF_TIREDNESS,
}



class alpTirednessNotfr: NotifierBase
{

	/*
	default values	
	float FatigueBasal									= 0.0025; //energy loss per second while idle (max energy is 100)
	float FatigueWalk									= 0.005; //energy loss per second while walking (max energy is 100)
	float FatigueJog									= 0.008; //energy loss per second while jogging (max energy is 100)
	float FatigueSprint									= 0.016; //energy loss per second while sprintingn (max energy is 100)	
	*/
	
	
	
	
	private float 	DEC_TRESHOLD_LOW 			= 0;
	private float 	DEC_TRESHOLD_MED 			= -0.01 * ( GetND().GetRP().GetFatigue().FatigueWalk / 0.005 );
	private float 	DEC_TRESHOLD_HIGH			= -0.018 * ( GetND().GetRP().GetFatigue().FatigueJog / 0.008 );
	private float 	INC_TRESHOLD_LOW 			= 0;
	private float 	INC_TRESHOLD_MED 			= 0.05;
	private float 	INC_TRESHOLD_HIGH			= 0.2;	
	
	
	void alpTirednessNotfr(NotifiersManager manager)
	{

	}

	override int GetNotifierType()
	{
		return alpeNotifiers.NTF_TIREDNESS;
	}

	override void DisplayBadge()
	{
	}

	override void HideBadge()
	{
	}
	
	
	
	override void DisplayTendency(float delta)
	{
		//PrintString(delta.ToString());
		int tendency = CalculateTendency(delta, INC_TRESHOLD_LOW, INC_TRESHOLD_MED, INC_TRESHOLD_HIGH, DEC_TRESHOLD_LOW, DEC_TRESHOLD_MED, DEC_TRESHOLD_HIGH);

		EStatLevels energy_level = m_Player.GetStatLevelEnergyALP();
		
		
		//m_Player
		
		alpStatsTendencyTiredness dis_elm = alpStatsTendencyTiredness.Cast( m_Player.GetSyncData().GetElement( alpRPelements.TDCY_TIREDNESS )  ) ;
		
		if( dis_elm )
		{
			dis_elm.SetTendency(tendency);
			dis_elm.SetSeriousnessLevel(energy_level);
			
		}
	}

	override float GetObservedValue()
	{
		return m_Player.GetStatTiredness().Get();
	}		
};