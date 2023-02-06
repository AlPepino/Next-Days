
modded class alpMAPMARKERS 
{

	/*
	static void ShowClanMemebersOnMapALP(MapWidget m)
	{
	
	}
	*/
	
	
	override static void ShowALLRestictedAreasALP(MapWidget m)
	{
		//show restricted area

		if (alp_ND_base.GetBases().ShowRestrictedAreaOnMap && alp_ND_base.GetBases().EnableRestrictedArea && alp_ND_base.GetBases().RestrictedAreas )
		{	
			for(int a = 0; a < alp_ND_base.GetBases().RestrictedAreas.Count();a++)
			{
				vector pos3 = alp_ND_base.GetBases().RestrictedAreas.Get(a);
				vector tempV = Vector(pos3[0],0,pos3[1]);					
				ShowResctrictedArea(m, tempV, pos3[2], COLOR_YELLOW );						
				
				tempV[2] = pos3[1] + pos3[2] * 0.5;
				tempV[0] = pos3[0] - pos3[2] * 0.75;
				m.AddUserMark(tempV, alp_ND_base.GetBases().LabelOfRestrictedArea , COLOR_YELLOW, "");	
				
			}														
		}	
		
	}

}