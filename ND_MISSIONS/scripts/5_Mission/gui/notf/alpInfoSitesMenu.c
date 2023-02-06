
class alpInfoSitesMenu extends UIScriptedMenu
{
	protected PlayerBase					alp_Player;
	protected XComboBoxWidget 				alp_Language;
	protected ref array<ref ButtonWidget>	alp_Menus = new array<ref ButtonWidget>;

	protected HtmlWidget					alp_BodyText1;
	protected HtmlWidget					alp_BodyText2;
	protected HtmlWidget					alp_BodyText3;
	protected HtmlWidget					alp_BodyText4;
	protected HtmlWidget					alp_BodyText5;
	
	
	override Widget Init()
	{
		/*
		GetGame().GetMission().GetHud().ShowHudUI( false );
		GetGame().GetMission().GetHud().ShowQuickbarUI( false );
		*/
		
		Class.CastTo(alp_Player,GetGame().GetPlayer());
		
		layoutRoot 	= GetGame().GetWorkspace().CreateWidgets("ND_MISSIONS/gui/layouts/InfoSites.layout");
		Class.CastTo(alp_BodyText1, layoutRoot.FindAnyWidget("BodyText1"));
		Class.CastTo(alp_BodyText2, layoutRoot.FindAnyWidget("BodyText2"));
		Class.CastTo(alp_BodyText3, layoutRoot.FindAnyWidget("BodyText3"));
		Class.CastTo(alp_BodyText4, layoutRoot.FindAnyWidget("BodyText4"));
		Class.CastTo(alp_BodyText5, layoutRoot.FindAnyWidget("BodyText5"));
		Class.CastTo(alp_Language, layoutRoot.FindAnyWidget("LanguageList"));
		
		alp_Language.ClearAll();
		
		foreach (string lan : GetND().GetInfo().GetData().Language)
		{
			alp_Language.AddItem(lan);
		}
		
		alp_Language.SetCurrentItem(GetND().GetInfo().GetData().LanID);
		
		for (int i=0;i< GetND().GetInfo().GetData().Items.Count();i++)
		{
			if (i==5) break;//limit for alp_Menus
			
			alpISitem item = GetND().GetInfo().GetData().Items.Get(i);
			
			alp_Menus.Insert(ButtonWidget.Cast(layoutRoot.FindAnyWidget("Menu" + (i + 1))));
			alp_Menus.Get(i).SetText(item.Menu.Get(GetND().GetInfo().GetData().LanID));
			alp_Menus.Get(i).Show(true);
		}
		
		
		//init text
		SetBodyWindows();

		
		//buttons
		ButtonWidget btn;
		if ( GetND().GetInfo().GetData().Button1.Count() == 2 && GetND().GetInfo().GetData().Button1.Get(0) != "" && Class.CastTo(btn,layoutRoot.FindAnyWidgetById(2)) )
		{
			btn.SetText( GetND().GetInfo().GetData().Button1.Get(0) );		
			btn.Show(true);
		}	
		if ( GetND().GetInfo().GetData().Button2.Count() == 2 && GetND().GetInfo().GetData().Button2.Get(0) != "" && Class.CastTo(btn,layoutRoot.FindAnyWidgetById(3)) )
		{
			btn.SetText( GetND().GetInfo().GetData().Button2.Get(0) );		
			btn.Show(true);
		}		
		if ( GetND().GetInfo().GetData().Button3.Count() == 2 && GetND().GetInfo().GetData().Button3.Get(0) != "" && Class.CastTo(btn,layoutRoot.FindAnyWidgetById(4)) )
		{
			btn.SetText( GetND().GetInfo().GetData().Button3.Get(0) );		
			btn.Show(true);
		}		
		if ( GetND().GetInfo().GetData().Button4.Count() == 2 && GetND().GetInfo().GetData().Button4.Get(0) != "" && Class.CastTo(btn,layoutRoot.FindAnyWidgetById(5)) )
		{
			btn.SetText( GetND().GetInfo().GetData().Button4.Get(0) );		
			btn.Show(true);
		}	
		if ( GetND().GetInfo().GetData().Button5.Count() == 2 && GetND().GetInfo().GetData().Button5.Get(0) != "" && Class.CastTo(btn,layoutRoot.FindAnyWidgetById(6)) )
		{
			btn.SetText( GetND().GetInfo().GetData().Button5.Get(0) );		
			btn.Show(true);
		}								
		
		return layoutRoot;
	}
/*
	void ~alpInfoSitesMenu()
	{
		GetGame().GetMission().GetHud().ShowHudUI( true );
		GetGame().GetMission().GetHud().ShowQuickbarUI( true );			
	}	
*/
	
	void SetBodyWindows()
	{
		HideBodyWindows();
		
		string text = GetBodyText(  GetND().GetInfo().GetData().LanID, GetND().GetInfo().GetData().MenuID);
		
		int menuid = GetND().GetInfo().GetData().MenuID;

		switch (menuid)
		{
			case 0:
				alp_BodyText1.SetText( text );
				alp_BodyText1.Update(  );			
				alp_BodyText1.Show( true );	
				break;
			case 1:
				alp_BodyText2.SetText( text );
				alp_BodyText2.Update(  );	
				alp_BodyText2.Show( true );				
				break;
			case 2:
				alp_BodyText3.SetText( text );
				alp_BodyText3.Update(  );	
				alp_BodyText3.Show( true );				
				break;
			case 3:	
				alp_BodyText4.SetText( text );
				alp_BodyText4.Update(  );			
				alp_BodyText4.Show( true );			
				break;
			case 4:			
				alp_BodyText5.SetText( text );
				alp_BodyText5.Update(  );			
				alp_BodyText5.Show( true );	
				break;											
		}
									
	
	}
	
	
	void HideBodyWindows()
	{
		alp_BodyText1.Show( false );
		alp_BodyText2.Show( false );
		alp_BodyText3.Show( false );
		alp_BodyText4.Show( false );
		alp_BodyText5.Show( false );
	
	}
	
	
	private string GetBodyText(int language, int menu)
	{
		string text;
		
		if ( !GetND().GetInfo().GetData().Items.Get(menu) )
			return "Please update your source files according to template";
		
		for ( int i =0 ; i <  GetND().GetInfo().GetData().Items.Get(menu).Text.Get( language).Count() ; i++)
		{
			text += 	GetND().GetInfo().GetData().Items.Get(menu).Text.Get( language).Get(i);	
		}
	
		
		return text;
	
	}
	
	
	private void SetMenus()
	{
		for (int i = 0; i<alp_Menus.Count();i++)
		{
			ButtonWidget bw = alp_Menus.Get(i);
			bw.SetText(GetND().GetInfo().GetData().Items.Get(i).Menu.Get( GetND().GetInfo().GetData().LanID  ));
		}
	}


	override bool OnClick(Widget w, int x, int y, int button)
	{
		string text;
		if (super.OnClick(w, x, y, button))
		{
			return true;
		}
		else {			
			for (int i=0; i < alp_Menus.Count();i++)
			{
				ButtonWidget bw	= alp_Menus.Get(i);
				if (w == bw)
				{
					GetND().GetInfo().GetData().MenuID = i;

					SetBodyWindows();
					
					ScrollWidget.Cast( layoutRoot.FindAnyWidget("ScrollWidget0")).VScrollToPos01(0);

					return true;
				}
			}
			
			switch (w.GetUserID())
			{		
				case 20://change language;					
					GetND().GetInfo().GetData().LanID = alp_Language.GetCurrentItem();
					SetMenus();
				
					SetBodyWindows();
			
					ScrollWidget.Cast( layoutRoot.FindAnyWidget("ScrollWidget0")).VScrollToPos01(0);

					return true;					

				case 2://donate button
					GetGame().OpenURL( GetND().GetInfo().GetData().Button1.Get(1) );
					return true;	
				case 3://discord button
					GetGame().OpenURL( GetND().GetInfo().GetData().Button2.Get(1) );
					return true;
				case 4://discord button
					GetGame().OpenURL( GetND().GetInfo().GetData().Button3.Get(1) );
					return true;
				case 5://discord button
					GetGame().OpenURL( GetND().GetInfo().GetData().Button4.Get(1) );
					return true;
				case 6://discord button
					GetGame().OpenURL( GetND().GetInfo().GetData().Button5.Get(1) );
					return true;														
				
				case 1:
					Close();
					return true;
			}
	
			return false;
		}
	}
	
	override void OnShow()
	{
		super.OnShow();

		SetFocus( layoutRoot );
		GetGame().GetInput().ChangeGameFocus(1);	
		PPEffects.SetBlurMenu( GetND().GetMS().GetOptoinsTrader().NPC_Menu_blur );
		MissionGameplay.Cast( GetGame().GetMission() ).PlayerControlDisable(INPUT_EXCLUDE_ALL);
		GetGame().GetMission().GetHud().ShowHudUI( false );
		GetGame().GetMission().GetHud().ShowQuickbarUI( false );			

	}	
	override void OnHide()
	{
		super.OnHide();
		SetFocus( null );
		PPEffects.SetBlurMenu( 0 );
		GetGame().GetInput().ChangeGameFocus(-1);
		MissionGameplay.Cast( GetGame().GetMission() ).PlayerControlEnable(true);	
		GetGame().GetMission().GetHud().ShowHudUI( true );
		GetGame().GetMission().GetHud().ShowQuickbarUI( true );			
	}	

}
