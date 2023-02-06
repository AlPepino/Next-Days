
class alpStatBase
{
	
	WrapSpacerWidget alp_Parent;
	ref Widget alp_Main;
	ImageWidget alp_Icon;
	
	ref array<ref TStringArray> alp_Hints = new array<ref TStringArray>;
	
	WrapSpacerWidget alp_HintPanel = NULL;
	


	
	
	
	void AddHint( TStringArray text )
	{
		alp_Hints.Insert(text);
	}
	
	void OnMouseEnter(int x, int y)
	{
	 	if (alp_Hints.Count() > 0 )
		{
			if ( alp_HintPanel == NULL )
			{
				alp_HintPanel = GetHintPanel(x,y);		
			}
		
		}
	}
	
	

	
	void OnMouseLeave()
	{
		if (alp_HintPanel)
		{
			alp_HintPanel.Show(false);
			alp_HintPanel= NULL;
		}	
	}
	
	WrapSpacerWidget GetHintPanel(int x, int y)
	{
		Widget root;
		root =  GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/tipsPanel.layout" ) ;	
		
		
		WrapSpacerWidget panel = WrapSpacerWidget.Cast( root.FindAnyWidget("InfoToPlayerWindow") );
		
		if (panel)
		{
			
			
			TextWidget title = TextWidget.Cast ( panel.FindAnyWidget("Title") );
			
			title.SetText( alp_Hints.Get(0).Get(0) );
			
			for (int i=1; i< alp_Hints.Count(); i++)
			{
				
				if (alp_Hints.Get(i).Count() < 2 )
				{					
					Widget itemC1 = Widget.Cast( root.FindAnyWidget("ItemOne" + i.ToString() ) );
					
					MultilineTextWidget titleC1 = MultilineTextWidget.Cast( root.FindAnyWidget("OneTitle"  + i.ToString() ) );	
					titleC1.SetText (  alp_Hints.Get(i).Get(0) );
					
					panel.AddChild ( itemC1 );
				}				
				else
				{
					Widget itemC2 =  Widget.Cast( root.FindAnyWidget("ItemTwo" + i.ToString() ) );
					
					MultilineTextWidget titleC2 = MultilineTextWidget.Cast( root.FindAnyWidget("TwoTitle"  + i.ToString() ) );	
					MultilineTextWidget valueC2 = MultilineTextWidget.Cast( root.FindAnyWidget("TwoValue"  + i.ToString() ) );	
					
					titleC2.SetText (  alp_Hints.Get(i).Get(0) );
					valueC2.SetText (  alp_Hints.Get(i).Get(1) );
					
					panel.AddChild( itemC2 );
				}
				
			}
			
			ShowPanel( panel, x, y );
		}
		
		return panel;
	}
	Widget GetWidget()
	{
		return alp_Main;
	}	
	


	void ShowPanel(Widget panel, int x, int y)
	{
		int sx,sy,posX,posY;
		float pw,ph;
		GetScreenSize(sx,sy);
		panel.GetSize(pw,ph);
		
		if ( (x + pw) > sx )
			posX = x - pw;
		else
			posX = x;
		
		if ( (y+ ph) > sy )
			posY = y - ph;
		else
			posY = y;
		
		panel.SetPos( posX, posY );
	}
}