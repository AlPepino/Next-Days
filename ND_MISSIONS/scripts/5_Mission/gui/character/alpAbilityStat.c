
class alpAbilityStat extends alpStatBase
{
	

	
	ProgressBarWidget alp_BarLevel;
	
	ProgressBarWidget alp_BarProgres;
	
	
	

	float alp_ValueProgres;
	

	
	void alpAbilityStat(string img,  ref WrapSpacerWidget w, float level, float valueProgres = 0, bool widthIcon = false)
	{

		alp_ValueProgres = valueProgres;

		
		alp_Parent = w;
		
	
		Widget root = GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/abilityStat.layout",w) ;
		//
			
		alp_Main =  Widget.Cast( root.FindAnyWidget("STAT_panel") );
		
		
		
		
		alp_BarLevel = ProgressBarWidget.Cast( root.FindAnyWidget("STAT_level") );
		alp_BarProgres = ProgressBarWidget.Cast( root.FindAnyWidget("STAT_progress") );
		
		if (!widthIcon)		
			alp_Icon = ImageWidget.Cast( root.FindAnyWidget("STAT_icon") );
		else 
			alp_Icon = ImageWidget.Cast( root.FindAnyWidget("STAT_iconW") );
	
				
		alp_Icon.LoadImageFile(0,img);
		alp_Icon.Show(true);
		
		
		SetValueProgres( alp_ValueProgres );
		SetValueLevel( level );
	}
	
	void SetValueLevel(float value)
	{	
		alp_BarLevel.SetCurrent( value );
	}
	
	void SetValueProgres(float progress)
	{
		alp_ValueProgres = progress;
		
		alp_BarProgres.SetCurrent( progress );
	}	
	/*
	float GetValueLevel()
	{
		return alp_ValueLevel;
	}

	float GetValueProgres()
	{
		return alp_ValueProgres;
	}	
	*/
	
}