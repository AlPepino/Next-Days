
modded class MissionBase extends MissionBaseWorld
{
 	override UIScriptedMenu CreateScriptedMenuALP(int id)
	{
		UIScriptedMenu menu = super.CreateScriptedMenuALP(id);	
		
		if (!menu)
		{
			if (ALP_MENU_MANAGE_PLOTPOLE==id)
			{	
				menu = new alpPlotPoleMenu;			
			}				
		}		
		return menu;
	}
	


}
