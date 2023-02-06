
alpND_world GetND()
{
	if ( !alp_ND_base )
	{
		alp_ND_base = new alpND_world();						
	}
	
	return  alpND_world.Cast( alp_ND_base );

}



class alpND_world extends alpND_base
{
	
	
	override protected void Init()
	{	

		
		
		//set plugins
		AddPlugin( new alpPluginNDoptions( alpPLUGIN_BASE_ID.OPTIONS, alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN ) );
		AddPlugin( new alpPluginNDnotf( alpPLUGIN_BASE_ID.NOTF, alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN ) );
		AddPlugin( new alpPluginNDinfo( alpPLUGIN_BASE_ID.INFO, alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN ) );
		AddPlugin( new alpPluginNDrp( alpPLUGIN_BASE_ID.RP, alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN ) );
		
		AddPlugin( new alpPluginNDresources( alpPLUGIN_BASE_ID.RESOURCES, alpPLUGIN_BASE_EVENTS.ONCONNECT ) );
	 
		//COMPATIBILITY issues MS
		alp_ActiveQuests 	= new  array< ref alpRegisteredQuest>;
		
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() )
		{		
			if (!FileExist(ALP_MISSIONSYSTEM_FOLDER)) MakeDirectory(ALP_MISSIONSYSTEM_FOLDER);

			//basic setting

			JsonFileLoader<autoptr alpMSoptions>.JsonLoadFile(ALP_MISSIONS_DEFAULT_FILE, alp_OptionsMS );	
			if (!alp_OptionsMS)
			{
				alp_OptionsMS  = new alpMSoptions;
				JsonFileLoader< autoptr alpMSoptions>.JsonSaveFile(ALP_MISSIONS_DEFAULT_FILE, alp_OptionsMS);
			}
			else
			{
				JsonFileLoader< autoptr alpMSoptions>.JsonSaveFile(ALP_MISSIONS_DEFAULT_FILE,  alp_OptionsMS);
			}	
			//qusts				
			JsonFileLoader<array<ref alpTraderQuest>>.JsonLoadFile(ALP_MISSIONSYSTEM_QUESTS, alp_Quests );	
			
			if (!alp_Quests)
			{
				alp_Quests  = new array<ref alpTraderQuest>;				
				//example
				
				alp_Quests.Insert( new alpTraderQuest( 1 ) );
								
				JsonFileLoader< array<ref alpTraderQuest>>.JsonSaveFile(ALP_MISSIONSYSTEM_QUESTS,  alp_Quests);
			}	
			//logs
			int y,mm,d;
			int h,m,s;
			GetYearMonthDayUTC(y,mm,d);
			GetHourMinuteSecondUTC(h,m,s);
					
			string timeStamp =  y.ToString() + "-" + mm.ToString() + "-" + d.ToString() + "_" + h.ToString() + "-" + m.ToString() + "-" + s.ToString() + ".log";
			
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.CreateNewTraderLogFile,1,false,timeStamp);
					
					
		}
		if (GetGame().IsClient())
		{
			alp_OptionsMS  = new alpMSoptions;			
			alp_MarkedMission = new array<ref alpMissionTemplateClient>;
			alp_Quests			= new array<ref alpTraderQuest>;
		}		
		AddPlugin( new alpPluginNDmissionsSystem( alpPLUGIN_BASE_ID.MS,  alpPLUGIN_BASE_EVENTS.START | alpPLUGIN_BASE_EVENTS.UPDATE  | alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN | alpPLUGIN_BASE_EVENTS.FINISH ) );
		//MS
		
	}	

//compatibility issues

	override void MarkMissionOnMap()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		alp_MarkedMission = new array<ref alpMissionTemplateClient>;
									
		foreach ( alpMissionBase mission : GetMS().alp_Missions )
		{			
			if (mission.IsActive())
			{
				alpMissionTemplateClient data;				
				data = alpMissionTemplateClient.Cast( alpMissionTemplateClient.CompileDataToClient(mission) );
				 
				
				if (data.showInMapWhenEnter)
				{
					if (mission.alp_Touched || mission.alp_WasTouched || player.GetRP().GetWalkieTalkieType() & alpRADIO.HAS_BASE_RADIO )
					{
						mission.alp_WasTouched	= true;
						alp_MarkedMission.Insert( data );

					}
				}
				else
				{
					alp_MarkedMission.Insert( data );

				}
			}											
		}
		
	}
	override int HasWalkieTalkie()
	{//just client only
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		return  player.GetRP().HasWalkieTalkie();		
	}
	
	
	override int GetRadiationLevel()
	{
		//Print("VOLAM FUNKCI RADIATION LEVEL");
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if ( player)
		{	
			int radiation =   alpGeigerSound.GetSoundTypeValue( player.GetRP().GetRadiation() );
			
			return radiation;
			
		}
		return alpGEIGERSOUNTYPE.NONE;			
	}	


	override void OnSpawn( Man player )
	{
		PlayerBase p = PlayerBase.Cast( player );
		
		if ( p && !p.alp_IsEventOnRunActive ){
			foreach ( alpPluginBase plugin : alp_RegPlugins_EVENT_ONSPAWN )
			{
				plugin.OnSpawn( player );
			}					
			p.alp_IsEventOnRunActive = true;
		}
					
	}	


	/*
	alpOptionsND GetOptions()
	{
		alpPluginNDoptions plugin = alpPluginNDoptions.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.OPTIONS ) );
	
		if ( plugin )
		{
			return plugin.GetOptions();
		}
		
		return null;
	}
	*/
	alpPluginNDnotf	GetNotf()
	{
		
		alpPluginNDnotf plugin = alpPluginNDnotf.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.NOTF ) );
		
		if ( plugin )
		{
			return plugin;
		}
		
		return null;
	}	
	
	alpPluginNDinfo	GetInfo()
	{
		
		alpPluginNDinfo plugin = alpPluginNDinfo.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.INFO ) );
		
		if ( plugin )
		{
			return plugin;
		}
		
		return null;
	}	
	
	alpPluginNDrp	GetRP()
	{
		
		alpPluginNDrp plugin = alpPluginNDrp.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.RP ) );
		
		if ( plugin )
		{
			return plugin;
		}
		
		return null;
	}			
	
	
	alpPluginNDmissionsSystem	GetMS()
	{
		
		alpPluginNDmissionsSystem plugin = alpPluginNDmissionsSystem.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.MS ) );
		
		if ( plugin )
		{
			return plugin;
		}
		
		return null;
	}		
	
	alpPluginNDresources	GetResources()
	{
		
		alpPluginNDresources plugin = alpPluginNDresources.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.RESOURCES ) );
		
		if ( plugin )
		{
			return plugin;
		}
		
		return null;
	}	

	
	//traderLog
	void CreateNewTraderLogFile(string timeStamp){		
		if ( GetMS().GetOptoinsTrader().MakeTraderLogs ) {			
			string path = ALP_LOGS + "trader_" + timeStamp;
			m_FileTraderLogs = OpenFile( path, FileMode.WRITE );
		}			
	}
	
	void MakeTraderLog(string timeStamp, PlayerBase player, int stockID, int akce, string item, int count, int price) {
		price = Math.AbsInt( price );
		if ( m_FileTraderLogs ) {

			string akceTitle;
			if ( akce == 0 ) {
				akceTitle = "buyed"; 			
			} else {
				akceTitle = "sold"; 	
			}
			item = alpUF.GetDisplayName(item);
			if ( player ) {
				string log =  string.Format("%1 | %2 %3 | %4 | %5 | x %6 | for %7 | trader(StockID) %8 | %9", timeStamp, player.GetIdentity().GetPlainId(),player.GetIdentity().GetName() , akceTitle, item, count.ToString(), price.ToString(), stockID.ToString(), player.GetPosition().ToString()  );
				FPrintln( m_FileTraderLogs, log );	
			}
		
		}
		
	}
}



