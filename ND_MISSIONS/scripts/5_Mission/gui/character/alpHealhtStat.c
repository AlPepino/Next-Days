class alpHealhtStat extends alpStatBase
{


	ProgressBarWidget alp_Bar;
	TextWidget alp_Text;
	
	float alp_Value;
	
	bool alp_NoBar;
	
	string alp_Unit;
	
	void alpHealhtStat(string img, WrapSpacerWidget w, float value = 0, bool nobar = false, string unit = "")
	{
		alp_Value = value;
		alp_Parent = w;
		alp_NoBar = nobar;
		alp_Unit = unit;
		
		Widget root = GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/healthStat.layout" ,w);	
		
		
		alp_Main = Widget.Cast( root.FindAnyWidget("STAT_panel") );

		alp_Bar = ProgressBarWidget.Cast( root.FindAnyWidget("STAT_progress") );
		alp_Text = TextWidget.Cast( root.FindAnyWidget("STAT_text") );
		alp_Icon = ImageWidget.Cast( root.FindAnyWidget("STAT_icon") );					
		
		alp_Icon.LoadImageFile(0,img);
		
		if (alp_NoBar)
		{
			alp_Bar.Show(false);
			alp_Text.Show(true);
		}
		
		
		SetValue( alp_Value );
		
		
		

		
		
	}
	
	void SetValue(float value)
	{
		alp_Value = value;
		
		
		
		if (alp_NoBar)
		{
			
			string text = value.ToString() + alp_Unit;
			alp_Text.SetText(text);
		}
		else
		{
			alp_Bar.SetCurrent( value );
		}		
	}
	
	float GetValue()
	{
		return alp_Value;
	}

	

	
}