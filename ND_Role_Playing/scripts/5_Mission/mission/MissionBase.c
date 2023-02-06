
modded class MissionBase extends MissionBaseWorld
{
 	override UIScriptedMenu CreateScriptedMenuALP(int id)
	{
		UIScriptedMenu menu = super.CreateScriptedMenuALP(id);	
		
		if (!menu)
		{
		
			if (ALP_MENU_SPREADRUMOUR==id)
			{	
				menu = new alpSpreadRumoursMenu;		
			}	
			else if (ALP_MENU_EXAMINATION==id)
			{	
				menu = new alpMedicExaminationMenu;			
			}				
		}		
		return menu;
	}
	


}
