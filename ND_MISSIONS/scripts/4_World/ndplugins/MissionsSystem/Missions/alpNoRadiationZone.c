//noRadiation Zone
class alpNoRadiationZone extends alpMission
{



//-------------------------------------------------------------------
//***************************//
//adjust default setting
//***************************//			
	override void OnInit()
	{
		//messages setting
		alp_SendInfoStart	= ALPMSTYPE.MMMISSIONSTART;
		alp_SendInfoEnd		= ALPMSTYPE.MMMISSIONEND;
		alp_AlertInfoIn		= ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut	= ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn		= ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut	= ALPMSTYPE.MMPERSONAL;		
	}

	override protected void OnEnter(Object obj )
	{
		super.OnEnter(obj);
		//SetSetting( alpMISSION_SETTING.MISSION_IDLE );									
	};
}