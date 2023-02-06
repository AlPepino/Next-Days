

modded class MissionGameplay extends MissionBase
{
	UAInput 							alp_UAInfoSites;
	alpInfoSitesMenu 					alp_InfoSites;
	
	alpInfoPlayerMenu 					alp_CharStats;
	UAInput 							alp_UAstats;	
	
	override void OnInit()
	{
		super.OnInit();
		
		alp_UAInfoSites = GetUApi().GetInputByName("UA_ALP_MENU_INFO_PAGES");	
		alp_UAstats = GetUApi().GetInputByName("UA_ALP_MENU_INFO_PLAYER");
	}
	
	
    override void OnUpdate(float timeslice) 
	{
        super.OnUpdate(timeslice);
		
		
		if ( !GetGame().IsMultiplayer() )
			return;
		
		//GetND().OnUpdate( timeslice );	

		if ( GetND().GetNotf().GetOptions().EnableGameInfo && alp_UAInfoSites.LocalPress())
		{
			if (!alp_InfoSites)
			{
				alp_InfoSites = alpInfoSitesMenu.Cast( GetUIManager().EnterScriptedMenu(ALP_MENU_INFO_PAGES, NULL) );
			
			}	
		}		
		if ( GetND().GetNotf().GetOptions().EnableCharacterInfo && alp_UAstats.LocalPress()  )
		{
			if (!alp_CharStats)
			{
				alp_CharStats = alpInfoPlayerMenu.Cast( GetUIManager().EnterScriptedMenu(ALP_MENU_INFO_PLAYER, NULL) );
			}	
		}		
		
 		
	}

	
	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		
		if (key == KeyCode.KC_ESCAPE)
		{		
			if (alp_InfoSites)
			{
				alp_InfoSites.Close();
				alp_InfoSites=NULL;			
			}	
			if (alp_CharStats)
			{
				alp_CharStats.Close();
				alp_CharStats=NULL;			
			}	
			if (GetUIManager().FindMenu(ALP_MENU_TRADER) && !GetUIManager().FindMenu(MENU_INSPECT_ALP))
			{
				GetUIManager().CloseMenu(ALP_MENU_TRADER);
			}	
			if (GetUIManager().FindMenu(MENU_INSPECT_ALP) )
			{
				GetUIManager().CloseMenu(MENU_INSPECT_ALP);
			}				
			if (GetUIManager().FindMenu(ALP_MENU_ATM))
			{
				GetUIManager().CloseMenu(ALP_MENU_ATM);
			}			
			//supp ND-Role-Playing
			if (GetUIManager().FindMenu(ALP_MENU_SPREADRUMOUR))
			{
				GetUIManager().CloseMenu(ALP_MENU_SPREADRUMOUR);
			}	
			if (GetUIManager().FindMenu(ALP_MENU_EXAMINATION))
			{
				GetUIManager().CloseMenu(ALP_MENU_EXAMINATION);
			}				
		}		
	}	
 
 

}
