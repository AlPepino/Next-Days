modded class MissionBase extends MissionBaseWorld
{

	void MissionBase()
	{
		GetND();
	}
	
	override UIScriptedMenu CreateScriptedMenu(int id)
	{
		UIScriptedMenu menu = NULL;
		menu = super.CreateScriptedMenu(id);
		if (menu)
		{
			menu.SetID(id);
		}
		else 
		{
			menu = CreateScriptedMenuALP(id);		
			if ( menu )
			{
				menu.SetID(id);	
			}
		}
		return menu;
	}

 	UIScriptedMenu CreateScriptedMenuALP(int id)
	{					
		UIScriptedMenu menu;	
			
		switch(id)
		{
			case ALP_MENU_INFO_PAGES:
			{
				menu = new alpInfoSitesMenu;
				break;
			}
			case ALP_MENU_INFO_PLAYER:
			{
				menu = new alpInfoPlayerMenu;
				break;
			}	
			case ALP_MENU_TRADER:
			{	
				menu = new alpTraderMenu;
				break;
			}				
			case ALP_MENU_ATM:
			{	
				menu = new alpATMmenu;
				break;
			}		
			case MENU_INSPECT_ALP:
			{	
				menu = new InspectMenuNewALP;
				break;
			}				
		}	
		return menu;	
	
	}	


}
