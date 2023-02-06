
modded class MapMenu extends UIScriptedMenu
{
	override Widget Init()
	{
		layoutRoot = super.Init();		
		ShowAllMarkersALP();
		return layoutRoot;
	}	
	

	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);
		
		switch (w.GetUserID())
		{
			case IDC_CANCEL:
				Close();
				return true;
		}

		return false;
	}
	
	void ShowAllMarkersALP()
	{
		MapWidget m = MapWidget.Cast(layoutRoot.FindAnyWidget("Map"));

		
		if (m)
		{	

			alpMAPMARKERS.ShowALLMissionsALP(m);
			alpMAPMARKERS.ShowALLRestictedAreasALP(m);
			alpMAPMARKERS.ShowClanMemebersOnMapALP(m);
		}

		
	}

		
}
