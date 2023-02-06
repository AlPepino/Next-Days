
#ifdef BASICMAP

modded class BasicMapMenu extends UIScriptedMenu
{	

	
	override void UpdateMarkers()
	{
		//DO MISSION MARKERS
		
		super.UpdateMarkers();
		if (m_Map)
		{
			alpMAPMARKERS.ShowALLMissionsALP(m_Map);	
			alpMAPMARKERS.ShowALLRestictedAreasALP(m_Map);
			alpMAPMARKERS.ShowClanMemebersOnMapALP(m_Map);			
		}
		
	}

}
	
	
	
	
	
	
#endif	