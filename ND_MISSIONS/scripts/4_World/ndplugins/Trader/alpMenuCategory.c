
class alpMenuCategory 
{
	int 									alp_LastSelectedMenu;
	int										alp_CategoryID;
	string									alp_Name;
	
	ref map <string, ref alpMenuCategory>	alp_Menu			= new  map <string, ref alpMenuCategory>;

	
	alpMenuCategory AddSubMenu(string name, int id)
	{
		alpMenuCategory submenu;
		
		if (!alp_Menu.Find( name , submenu) )
		{
			submenu = new alpMenuCategory();
			submenu.alp_CategoryID = id;
			submenu.alp_Name = name;
			alp_Menu.Insert( name, submenu);
		}
		return submenu;
	}
	
	
	int	GetSelected()
	{
		int index = -1;
		if (alp_Menu.Count() > 0)
		{		
			 index = Math.Min( alp_LastSelectedMenu, alp_Menu.Count() - 1);	
		}
		return index;
	}
	void SetSelected(int id)
	{
		alp_LastSelectedMenu = id;
	}	
	
	ref map <string, ref alpMenuCategory> GetSelectedSubMenu()
	{
		if (alp_Menu.Count() > 0)
		{
			int index = Math.Min( alp_LastSelectedMenu,alp_Menu.Count() - 1);						
			alpMenuCategory subMenu = alp_Menu.GetElement(index);
			alp_LastSelectedMenu = index;
			return subMenu.alp_Menu;						
		}
		else return null;
	}	
	
	alpMenuCategory GetSelectedMenu()
	{
		if (alp_Menu.Count() > 0)
		{
			int index = Math.Min( alp_LastSelectedMenu,alp_Menu.Count() - 1);
			alpMenuCategory subMenu = alp_Menu.GetElement(index);
			alp_LastSelectedMenu = index;
			return subMenu;						
		}
		else 
		{
			return null;		
		}
	}	
	
	int GetCategoryID()
	{
		return alp_CategoryID;
	}
	void SetCategoryID(int id)
	{
		alp_CategoryID = id;
	}
}
