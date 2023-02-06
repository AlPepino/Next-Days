enum alpDEFENDAREA{
	NONE,
	STARTED,
	FINISHED
}

//noRadiation Zone 
class alpConquerDefendMission extends alpMission
{

	
	int m_EventDefentArea;
	
	float m_TimeCounter;
	float m_MessageTime;
	int m_TimeRequired;
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
		m_EventDefentArea 	= 0;
		
		m_TimeRequired = GetTemplate().countdownDefentArea;
		
	}
	
//-------------------------------------------------------------------
//***************************//
//Rewrite default methods
//***************************//		

	override protected bool CheckSecuredCondition(float timeslice){						
		if ( alp_Setting & alpMISSION_SETTING.MISSION_CLEARED && m_EventDefentArea == alpDEFENDAREA.FINISHED ) {
			return true;
		}	
		return false;
	}

	override protected void ActionClearedArea(float timeslice){
		if ( m_EventDefentArea != alpDEFENDAREA.FINISHED) {
			if ( alp_Setting & alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED || alp_Setting & alpMISSION_SETTING.MISSION_OCCUPIED ){
				if ( alp_Setting & alpMISSION_SETTING.MISSION_OCCUPIED ){//start
					if ( m_EventDefentArea == alpDEFENDAREA.NONE ) {
						m_TimeCounter = timeslice;
						m_MessageTime = 0;
						m_EventDefentArea = alpDEFENDAREA.STARTED;
						GetND().GetNotf().SendMissionMessage( ALPMSTYPE.MMCAPTURE, GetID(), "#alp_cd_start " + "#pos",GetPosition(),null,true); 
					} else {//update
						
						m_TimeCounter += timeslice;
						if ( m_TimeCounter >= m_TimeRequired ) {//finish
							m_EventDefentArea = alpDEFENDAREA.FINISHED;
							GetND().GetNotf().SendMissionMessage( ALPMSTYPE.MMDEFEND, GetID(), "#alp_cd_end",GetPosition(),null,true); 
							//NASTAVIT PRIVATNI TIMESTAMP U MISE PRI UKONCENI, dat flag a nahrat hracum tento klic?
						}
					}								
				} else {
					if ( m_EventDefentArea == alpDEFENDAREA.STARTED ) {//interupt
						m_EventDefentArea = alpDEFENDAREA.NONE;
					}											
				}	
				UpdateMissionMessageStage( timeslice );							
			} else {
				if ( m_EventDefentArea != alpDEFENDAREA.NONE ){
					m_EventDefentArea = alpDEFENDAREA.NONE;
				}					
			}
		}			
	}
	
	void UpdateMissionMessageStage(float timeslice){
		if ( m_EventDefentArea != alpDEFENDAREA.FINISHED) {
			m_MessageTime += timeslice;
			if ( m_MessageTime >= 15 ) {
				m_MessageTime = 0;
				//messsage to players in mission
								
				string m = "#alp_cd_continue (#alp_cd: " + GetTimeStamp() + ")";
				int typemessage = ALPMSTYPE.MMDEFEND;
				if ( alp_Setting & alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED  ){
					m = "#alp_cd_fight";
					typemessage = ALPMSTYPE.MMCONQUER;
				}
				for(int i = 0; i < alp_Insiders.Count(); i++)
				{	
					alpMissionInsider ins = alp_Insiders.Get(i);
					PlayerBase player;
					if ( ins.alp_DamageZone && Class.CastTo( player, ins.GetObject() ) && player.IsAlive() ) {
						GetND().GetNotf().SendMissionMessage( typemessage,GetID(), m ,GetPosition(),player);					
					}
				}								
			}	
		}
	}
	
	string GetTimeStamp(){
		int hour,min,sec;
		int time = Math.Floor( m_TimeCounter );
		int remainingTime = m_TimeRequired - time;
		
		hour = (int) Math.Floor( remainingTime / 3600 );
		min = remainingTime - ( hour * 3600 );
		min = (int) Math.Floor( min / 60 );	
		sec = remainingTime - ( hour * 3600 ) - ( min * 60 );	
		string messageTime;
		if ( hour ) {
			messageTime	+= hour.ToString() + "h ";
		}
		if ( min ) {
			messageTime	+= min.ToString() + "m ";
		}
		if ( sec ) {
			messageTime	+= sec.ToString() + "s";
		}				
		return messageTime;
	}
	
	override void SetPrivateTimeStemp(alpMission mission) {//spawning mission onsecured
		if ( mission &&  mission.alp_MissionStarted ) {//private mission	
			for(int i = 0; i < alp_Insiders.Count(); i++)
			{	
				alpMissionInsider ins = alp_Insiders.Get(i);
				PlayerBase player;
				if ( ins.alp_DamageZone && Class.CastTo( player, ins.GetObject() ) && player.IsAlive() ) {
					GetND().GetMS().SendRPC_RegisterMission( player , mission.GetID() , mission.alp_MissionStarted );				
				}
			}				
		}
	}
}