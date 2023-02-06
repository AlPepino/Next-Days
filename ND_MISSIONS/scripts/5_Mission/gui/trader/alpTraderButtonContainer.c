
class alpTraderButtonContainer 
{
	int COLOR_DEFAULT =  ARGB(129,0,0,0); // ARGB(a,r,g,b);
	int COLOR_SELECTED = ARGB(255,255,102,51); //ARGB(255,213,57,57);
	
	
	int alp_SelectedButton;
	
	WrapSpacerWidget alp_Parent;
	

	
	alpMenuCategory alp_Menu;
	
	ref array<ButtonWidget> alp_Buttons;
	
	ref array<Widget> alp_Root;
	
	void alpTraderButtonContainer( WrapSpacerWidget parent,ref alpMenuCategory menu,  int selected = 0 )
	{
		alp_Menu	= menu;
		alp_Parent	= parent;

		alp_Buttons = new array<ButtonWidget>;
		alp_Root = new array<Widget>;
		
		alp_SelectedButton = selected;
		
	
		
		Init();
	}
	
	void ~alpTraderButtonContainer()
	{
		Clear();	
	}
	void Clear()
	{
		for (int i = 0; i < alp_Root.Count(); i++)
		{
			alp_Parent.RemoveChild (	alp_Root.Get(i) );		
		}	
	}
	
	void Init()
	{
				
		for (int i = 0; i < alp_Menu.alp_Menu.Count(); i++)
		{
			string name = alp_Menu.alp_Menu.GetKey(i);
			AddMenu(name, i);
		}		
		
	
	}
	
	void AddMenu(string name, int ide)
	{
		Widget panel = GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/Button.layout",alp_Parent) ;	
		alp_Root.Insert( panel );
		
		ButtonWidget button = ButtonWidget.Cast( panel.FindAnyWidget("Button"));
		
		TextWidget.Cast( panel.FindAnyWidget("ButtonTitle")).SetText( name );
		
		
		if ( ide == alp_SelectedButton )
		{
			button.SetColor( COLOR_SELECTED );
		}
		
		alp_Buttons.Insert(button);
	}
	
	bool OnClick(Widget w, int x, int y, int button)
	{				
		int i;
		for(i = 0 ; i < alp_Buttons.Count();i++)
		{
			ButtonWidget btn = alp_Buttons.Get(i);
			if ( w == btn )
			{
				EventClick(i);
				return true;			
			}
		}
		return false;
		
	}		
	
	void EventClick(int ide)
	{
		if ( ide == alp_SelectedButton )
			return;
		
		alp_Menu.SetSelected(ide);
	}
}