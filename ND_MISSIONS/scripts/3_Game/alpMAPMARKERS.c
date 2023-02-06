enum alpRADIO
{
	NONE = 0,
	ALLOWED_BY_CONFIG_PERSONAL = 1,
	ALLOWED_BY_CONFIG_FIELD = 2,
	HAS_WALKIE_TALKIE = 4 ,
	HAS_BASE_RADIO = 8,
	HAS_GPS = 16,
	HAS_COMPASS = 32,	
}

class alpQuestMarker
{
	float X;
	float Y;
	string Title;
	string MapTitle;
	int Count;
	void AddMarker(float x, float y,string maptitle, string title ){
		X=x;
		Y=y;
		MapTitle = maptitle;
		
		Title += Widget.TranslateString( GetDisplayName( title ) ) + ", ";
		
	}
	
	string GetTitle() {
		return Widget.TranslateString( "#trader_bring_me") + ": " + Title.Substring( 0, Title.Length() - 2);
	}
	
	static string GetDisplayName(string className)
	{
		string name;
		TStringArray cfg = {"CfgVehicles ","CfgWeapons ","CfgMagazines ","CfgAmmo "};
		foreach(string p : cfg){
			GetGame().ConfigGetText(p + className + " displayName", name);
			if (name!=""){
				className = name;
				break;
			}
		}
		className.Replace("$UNT$", "");
		return className;
	}	
}

class alpMAPMARKERS 
{
	static int ALP_COLOR_MISSION = 0xFFFF8C00;//0xFF00FFFF;//0xFF9ACD32/0xFFFFA07A
	
	static ref map<string,ref alpQuestMarker> m_QuestMarkers;
	
	static string GetMissionStatus(int mtype, int setting ){
		string status = "";
		
		if ( setting & alpMISSION_SETTING.MISSION_STATUS ) {//enabled missions status
			string active = " (" + Widget.TranslateString("#alp_mactive") + ")";
			string nonactive = " (" + Widget.TranslateString("#alp_mnonactive") + ")";
			string unsecured = " (" + Widget.TranslateString("#alp_munsecured") + ")";
			string cleared = " (" + Widget.TranslateString("#alp_mcleared") + ")";
			string occupied = " (" + Widget.TranslateString("#alp_moccupied") + ")";
			string conquer = " (" + Widget.TranslateString("#alp_mconquer") + ")";
			string defend = " (" + Widget.TranslateString("#alp_mdefend") + ")";
			string secured = " (" + Widget.TranslateString("#alp_msecured") + ")";
			string expired = " (" + Widget.TranslateString("#alp_mexpired") + ")";
			string failed = " (" + Widget.TranslateString("#alp_mfailed") + ")";
			
			/*
			if ( mtype == ALP_MISSIONTYPEID.radiation || mtype == ALP_MISSIONTYPEID.noradiation  || mtype == ALP_MISSIONTYPEID.trader ) {
				//mise je vždy nastavená jako IDLE
				if  ( !( setting & alpMISSION_SETTING.MISSION_UNSECURED ||   setting & alpMISSION_SETTING.MISSION_CLEARED ||   setting & alpMISSION_SETTING.MISSION_OCCUPIED ||   setting & alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED ) ) {//aktivni
					status = active;		
				} else { //neaktivni
					status = nonactive;		
				}			
				if ( setting & alpMISSION_SETTING.MISSION_UNSECURED ) {
					status = unsecured;		
				}
				if ( setting & alpMISSION_SETTING.MISSION_CLEARED ) {
					status = cleared;		
				}			
				if ( setting & alpMISSION_SETTING.MISSION_OCCUPIED || setting & alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED ) {
					status = occupied;		
				}			
				if ( setting & alpMISSION_SETTING.MISSION_SECURED ) {
					status = secured;		
				}	
				if ( setting & alpMISSION_SETTING.MISSION_EXPIRED ) {
					status = expired;		
				}	
				if ( setting & alpMISSION_SETTING.MISSION_FAILED ) {
					status = failed;		
				}				
				return status;
			}
			*/
			//another missions
			if ( setting & alpMISSION_SETTING.MISSION_IDLE ) {
				status = nonactive;		
			} else {
				status = active;	
			}	
			if ( setting & alpMISSION_SETTING.MISSION_UNSECURED ) {
				status = unsecured;		
			}			
			if ( setting & alpMISSION_SETTING.MISSION_CLEARED ) {
				status = cleared;		
			}			
			if (  setting & alpMISSION_SETTING.MISSION_OCCUPIED || setting & alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED ) {
				status = occupied;		
				if (setting & alpMISSION_SETTING.MISSION_CLEARED && mtype == ALP_MISSIONTYPEID.conquerdefend ) {
					if ( alpMISSION_SETTING.MISSION_HOSTILE_OCCUPIED ) {
						status = conquer;	
					} else {
						status = defend;	
					}
				}
			} 
			if ( setting & alpMISSION_SETTING.MISSION_SECURED ) {
				status = secured;		
			}	
			if ( setting & alpMISSION_SETTING.MISSION_EXPIRED ) {
				status = expired;		
			}	
			if ( setting & alpMISSION_SETTING.MISSION_FAILED ) {
				status = failed;		
			}							
		}		
		return status;
	}
	
	
	static void ShowALLMissionsALP(MapWidget m)
	{
		
		Man player = GetGame().GetPlayer();
		int level;
		if ( player && player.GetIdentity() ){
			level = player.GetIdentity().GetPlayerLevel();
		}
		
		int nav = alp_ND_base.HasWalkieTalkie();
		if ( nav ) 
		{
			if  ( nav & alpRADIO.ALLOWED_BY_CONFIG_PERSONAL || nav & alpRADIO.ALLOWED_BY_CONFIG_FIELD || nav & alpRADIO.HAS_WALKIE_TALKIE || nav & alpRADIO.HAS_BASE_RADIO) {
				alp_ND_base.MarkMissionOnMap(); //update mission possition
				alp_ND_base.UpdateMostWanted(); //update most wanted
				alp_ND_base.UpdateNPCquests(); //update NPC quests			
			}
			
			
			if ( alp_ND_base.alp_OptionsMS.ShowPlayersOnMap && nav & alpRADIO.HAS_GPS )
			{
				//player position - dodelat podminku	
					
				m.AddUserMark(player.GetPosition(), player.GetIdentity().GetName(), COLOR_BLUE, "ND_MISSIONS\\gui\\images\\PlayerIcon.paa" );	
				
				if ( alp_ND_base.alp_OptionsMS.SetMapPositionToPlayer )
				{
					m.SetScale(0.1);				
					m.SetMapPos( player.GetPosition() ); 
				}
			
			}
		}
		//quests
		if ( !m_QuestMarkers) {
			m_QuestMarkers = new map<string,ref alpQuestMarker>;
		}
		 m_QuestMarkers.Clear();
		
		array< ref alpRegisteredQuest> reg_quests = alp_ND_base.GetMarkedRegisteredQuests();
		if ( reg_quests )
		{

			//Print("UROVEN HRACE JE " + level );
			foreach ( alpRegisteredQuest reg : reg_quests ){
				if ( reg ){				
					alpTraderQuest quest = alp_ND_base.GetQuest( reg.Quest );		
					//Print("Vyzadovano " + quest.RequiredLevel );			
					if ( quest && level >= quest.RequiredLevel ){
						string posTxt = reg.PosX.ToString() + ":" + reg.PosY.ToString();
						alpQuestMarker qm;
						if ( !m_QuestMarkers.Find( posTxt, qm ) ){
							qm = new alpQuestMarker();
							m_QuestMarkers.Set(posTxt,qm);
						}		
						qm.AddMarker(	reg.PosX, reg.PosY	, 	quest.MapTitle , quest.WantedItem );												
					}				
				}
			}		
			if ( m_QuestMarkers /* && m_QuestMarkers.GetValueArray() && m_QuestMarkers.GetValueArray().Count() > 0 */ ) {
				
				for(int i = 0; i<m_QuestMarkers.Count();i++){
					alpQuestMarker qM = m_QuestMarkers.GetElement(i);
					if ( qM ) {
						m.AddUserMark( Vector(qM.X, 0,qM.Y ),qM.GetTitle() , COLOR_YELLOW, "ND_MISSIONS\\gui\\images\\smTrader.paa" );
					}						
				} 
				/*
				foreach(alpQuestMarker qM : m_QuestMarkers.GetValueArray() ){
					if ( qM ) {
						m.AddUserMark( Vector(qM.X, 0,qM.Y ),qM.GetTitle() , COLOR_YELLOW, "ND_MISSIONS\\gui\\images\\smTrader.paa" );
					}					
				} 
				*/						
			}

		}
			
		//most wanted
		array< ref alpMostWanted> mostWanted = alp_ND_base.GetMostWanted();
		if ( mostWanted )
		{
			foreach ( alpMostWanted wanted : mostWanted )
			{
				if ( wanted )
				{
					
					m.AddUserMark(wanted.GetRealPostition(), wanted.GetName(), COLOR_RED, wanted.GetIcon() );	
				}
			}		
		}
		
		
		
		string inProgress = "";
		//missions
		array<ref alpMissionTemplateClient>	markedMission = alp_ND_base.GetMarkedMission();
		if ( markedMission )
		{
			foreach (alpMissionTemplateClient data : markedMission)
			{							
				
				//IsMissionKnown
				if ( !alp_ND_base.IsMissionKnown( data.id, data.missionStarted, data.requiredLevel ) ) {
					continue;
				}
				
				inProgress = GetMissionStatus( data.type, data.setting );

				//radoation
				if ( (  (data.showInMap && data.type == ALP_MISSIONTYPEID.radiation && data.setting & alpMISSION_SETTING.RADIATION_ACTIVE ) || (data.showInMap && data.type == ALP_MISSIONTYPEID.radiationMission && data.setting & alpMISSION_SETTING.RADIATION_ACTIVE ) ) && data.position!=vector.Zero && data.missionRadius>0 )
				{
					if (data.showInMap && data.type == ALP_MISSIONTYPEID.radiation) 
						m.AddUserMark(data.position, Widget.TranslateString(data.title) + inProgress, COLOR_RED, "ND_MISSIONS\\gui\\images\\smRadiation.paa");	
					else 
						m.AddUserMark(data.position, Widget.TranslateString(data.title) + inProgress, COLOR_RED, "ND_MISSIONS\\gui\\images\\smRadiation.paa");
					
					if ( alp_ND_base.alp_OptionsMS.ShowMissionRadius )
					{
						//uprava radiusu
						float ur = data.GetRadiusMultiplier() * data.missionRadius;
						if ( ur > 10 ) {
							ShowResctrictedArea(m, data.position, ur , COLOR_RED,  data.aspectRatioB, data.safeRadiusPointA, data.safeRadiusPointB);		
						}						
					}
				}
	
				//others mission
				if (data.showInMap && ( data.type == ALP_MISSIONTYPEID.trader || ( data.type == ALP_MISSIONTYPEID.savemerchants && data.setting & alpMISSION_SETTING.MISSION_CLEARED ) ) && data.position!=vector.Zero )
				{
					m.AddUserMark(data.position, Widget.TranslateString(data.title) + inProgress, COLOR_GREEN, "ND_MISSIONS\\gui\\images\\smTrader.paa");							
				}	
				if (data.showInMap && data.type == ALP_MISSIONTYPEID.carAccident && data.position!=vector.Zero )
				{
					m.AddUserMark(data.position, Widget.TranslateString(data.title) + inProgress, ALP_COLOR_MISSION , "ND_MISSIONS\\gui\\images\\car.paa");							
				}											
				if (data.showInMap && ( data.type == ALP_MISSIONTYPEID.noradiation || ( data.type == ALP_MISSIONTYPEID.radiation && !(data.setting & alpMISSION_SETTING.RADIATION_ACTIVE)  )  ) && data.position!=vector.Zero )
				{
					m.AddUserMark(data.position, Widget.TranslateString(data.title) + inProgress, ALP_COLOR_MISSION, "ND_MISSIONS\\gui\\images\\bod.paa");							
				}				
				if (data.showInMap && ( data.type == ALP_MISSIONTYPEID.noradiationMission || ( data.type == ALP_MISSIONTYPEID.radiationMission && !(data.setting & alpMISSION_SETTING.RADIATION_ACTIVE)  ) ) && data.position!=vector.Zero )
				{
					m.AddUserMark(data.position, Widget.TranslateString(data.title) + inProgress, ALP_COLOR_MISSION, "ND_MISSIONS\\gui\\images\\mmMission.paa");								
				}
				if (data.showInMap && data.type == ALP_MISSIONTYPEID.fuelstation && data.position!=vector.Zero )
				{
					m.AddUserMark(data.position, Widget.TranslateString(data.title) + inProgress, ALP_COLOR_MISSION, "ND_MISSIONS\\gui\\images\\fuel.paa");								
				}		
				//new missions
				if (data.showInMap && ( data.type == ALP_MISSIONTYPEID.savesurvivors || ( data.type == ALP_MISSIONTYPEID.savemerchants && !(data.setting & alpMISSION_SETTING.MISSION_CLEARED) ) ) && data.position!=vector.Zero )
				{
					m.AddUserMark(data.position, Widget.TranslateString(data.title) + inProgress, ALP_COLOR_MISSION, "ND_MISSIONS\\gui\\images\\save.paa");								
				}	
				if (data.showInMap && data.type == ALP_MISSIONTYPEID.conquerdefend && data.position!=vector.Zero )
				{
					m.AddUserMark(data.position, Widget.TranslateString(data.title) + inProgress, ALP_COLOR_MISSION, "ND_MISSIONS\\gui\\images\\flag.paa");								
				}										
				//show restricted area safeZone
				if ( ( data.type == ALP_MISSIONTYPEID.trader || ( data.type == ALP_MISSIONTYPEID.savemerchants && data.setting & alpMISSION_SETTING.MISSION_CLEARED ) ) && data.missionRadius > 0 && alp_ND_base.alp_OptionsMS.ShowMissionRadius )
				{
					ShowResctrictedArea(m, data.position, data.missionRadius, COLOR_GREEN, data.aspectRatioB, data.safeRadiusPointA, data.safeRadiusPointB );	

					if ( alp_ND_base.alp_OptionsMS.LabelOfSafeZone != "" )
					{
						vector pos2 = data.position;
						pos2[2] = pos2[2] + data.missionRadius * 0.5;				
						pos2[0] = pos2[0] - data.missionRadius * 0.75;
						
						m.AddUserMark(pos2, alp_ND_base.alp_OptionsMS.LabelOfSafeZone , COLOR_GREEN, "");			
					}		
				}			
				if (data.type == ALP_MISSIONTYPEID.conquerdefend && data.missionRadius > 0 && alp_ND_base.alp_OptionsMS.ShowMissionRadius )
				{
					ShowResctrictedArea(m, data.position, data.missionRadius, COLOR_YELLOW, data.aspectRatioB, data.safeRadiusPointA, data.safeRadiusPointB );		
				}							
			}	
		}
	}
	
	static void ShowClanMemebersOnMapALP(MapWidget m)
	{
	
	}
	static void ShowALLRestictedAreasALP(MapWidget m)
	{
	
	}
	static void ShowResctrictedArea(MapWidget m, vector position, float radius, int color, float ratioB = 0, vector pointA = "0 0 0", vector pointB = "0 0 0")
	{
		
		if ( !ratioB ){
			float len 		= radius;
			int countPoints = len * 2 * Math.PI / 10;
				
			float angle 	= 360 / countPoints;
			float angle2 	= 0;
			int i;
			for (i = 0; i < countPoints;i++)
			{		
				angle2 = i*angle;				
				vector pos	= vector.Zero;				
				pos[0]= Math.NormalizeAngle(angle2);
				pos = pos.AnglesToVector();	
				pos[0] = pos[0]*len;
				pos[2] = pos[2]*len;
				m.AddUserMark((position + pos) , "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");
							
			}			
		} else {
			float sideA =  Math.AbsFloat(  pointA[0] -  pointB[0] ) ;
			float sideB = Math.AbsFloat( pointA[2] -  pointB[2] );	
		
			float pointsA = Math.Floor( sideA / 10 );	
			float pointsB = Math.Floor( sideB / 10 );	
			
			vector v;

			for (i = 0; i < pointsA;i++){
				v = pointA;
				v[0]= pointA[0] - ( i * 10 );
				m.AddUserMark(v  , "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");	
				v[2] = pointB[2]; 
				m.AddUserMark(v  , "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");
			}
			v = pointA;
			v[0] = pointB[0]; 
			m.AddUserMark(v  , "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");
			v[2] = pointB[2]; 
			m.AddUserMark(v  , "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");
			for (i = 0; i < pointsB;i++){
				v = pointB;
				v[2]= pointB[2] + ( i * 10 );
				m.AddUserMark(v  , "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");	
				v[0] = pointA[0]; 
				m.AddUserMark(v  , "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");
			}	
			v = pointB;
			v[2] = pointA[2]; 
			m.AddUserMark(v  , "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");
			v[0] = pointA[0]; 
			m.AddUserMark(v  , "", color, "ND_MISSIONS\\gui\\images\\Bod.paa");					
		}	
	
	}	
}