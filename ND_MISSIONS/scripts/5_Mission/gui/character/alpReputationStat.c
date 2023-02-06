
class alpReputationStat extends alpStatBase
{
	

	
	ProgressBarWidget alp_BarLevel;
	
	ProgressBarWidget alp_BarProgres;
	

	
	TextWidget alp_Value1;
	
	TextWidget alp_Value2;
	

	
	void alpReputationStat(ref WrapSpacerWidget w, float currentRep=0 , float maxRep=0)
	{


		
		alp_Parent = w;
		
	
		Widget panel = GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/reputationStat.layout",w) ;
		//
			
		alp_Main =  Widget.Cast( panel.FindAnyWidget("BL_recordsBG") );
		
		alp_Value1 =  TextWidget.Cast( panel.FindAnyWidget("ValueC1") );
		alp_Value2 =  TextWidget.Cast( panel.FindAnyWidget("ValueC0") );
		
		
		SetReputationRecord( currentRep, maxRep );

		
	}
	

	void SetReputationRecord( float currentRep=0 , float maxRep=0)
	{
		int color;

		if ( currentRep < 0 )
			color	= COLOR_RED;
		else
			color = COLOR_GREEN;				
		
		
		alp_Value1.SetText( alpUF.NumberToString(currentRep,1) );
		alp_Value1.SetColor( color );
		
	
		if ( maxRep < 0 )
			color	= COLOR_RED;
		else
			color = COLOR_GREEN;
		
		alp_Value2.SetText( alpUF.NumberToString(maxRep,1) );
		alp_Value2.SetColor( color );	
	
	}
	
}