// Script File

#ifdef EXPANSIONMODNAVIGATION


modded class ExpansionMapMenu extends UIScriptedMenu
{
	override Widget Init()
	{
		layoutRoot = super.Init();		
		
		
		MapWidget m = MapWidget.Cast(layoutRoot.FindAnyWidget("Map"));
		
		if (m)
		{	
			m.ClearUserMarks();
			alpMAPMARKERS.ShowALLMissionsALP(m);	
			alpMAPMARKERS.ShowALLRestictedAreasALP(m);
			alpMAPMARKERS.ShowClanMemebersOnMapALP(m);			
		}						
		
		return layoutRoot;
	}
	
}


#endif 