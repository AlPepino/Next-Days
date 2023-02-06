
modded class alpInfoPlayerMenu extends UIScriptedMenu
{
	//clan
	Widget									alp_WindowClan;
	
	EditBoxWidget							alp_NameOfClan;
	
	TextListboxWidget						alp_ClanMembers;
	TextWidget								alp_ClanName;
	
	

	ButtonWidget							alp_ButtonNewClan;
	ButtonWidget							alp_ButtonLeaveClan;
	ButtonWidget							alp_ButtonKickMember;
	
	
	int										alp_MembersCount;

	ref array<ButtonWidget>					alp_ClanButtons
	
	alpClanData 							alp_Clan;
/*
	string									alp_PlayerGuid;
	string 									alp_ClanID;
	
	
	
*/
			
	override Widget Init()
	{
		Widget root = super.Init();
		
		

		if ( GetND().GetClans().GetOptions().EnableClans )
		{
			ButtonWidget menu = ButtonWidget.Cast( root.FindAnyWidgetById(13) );
			menu.Show(true);	
			
			
			Class.CastTo(alp_WindowClan, root.FindAnyWidget("BodyWindowClan")); 	
			
			alp_WindowRegister.Insert( alp_WindowClan );	
					
			
			Class.CastTo(alp_NameOfClan, root.FindAnyWidget("NameOfNewClan"));
			Class.CastTo(alp_ClanMembers, root.FindAnyWidget("ClanMembers"));
			Class.CastTo(alp_ClanName, root.FindAnyWidget("ClanName"));			
			
			alp_ClanButtons = new array<ButtonWidget>;
			

			Class.CastTo(alp_ButtonNewClan, root.FindAnyWidgetById(304));
			alp_ClanButtons.Insert(alp_ButtonNewClan );
			Class.CastTo(alp_ButtonLeaveClan, root.FindAnyWidgetById(305));
			alp_ClanButtons.Insert(alp_ButtonLeaveClan );
			Class.CastTo(alp_ButtonKickMember, root.FindAnyWidgetById(306));			
			alp_ClanButtons.Insert(alp_ButtonKickMember );
			
			
			/*
			alp_ClanID = alp_Player.GetRPG().GetClanID();
			
			
			
			alp_PlayerGuid = alp_Player.GetRPG().GetStore().GUID;
			

			
			*/	
			InitCLan();		
		}	
		
		return root;
	}	

override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (alp_WindowClan && alp_WindowClan.IsVisible() )
		{
			alp_Clan =  alp_Player.GetRP().GetClan();
			
			if ( alp_Clan )
			{
				if ( alp_MembersCount != alp_Clan.Members.Count() )
				{
					InitCLan();
				}			
			}
			else
			{
				if ( alp_MembersCount > 0 )
				{
					alp_MembersCount = 0;
					InitCLan();
				}
			}
			

		}
	}	
		
	void InitCLan()
	{
		alp_Clan =  alp_Player.GetRP().GetClan();
				
		DisableAllClanButtons();
		InitClanList();
		SetDisplayTMIcon();
	}		

	void InitClanList()
	{
		alp_ClanMembers.ClearItems();
		int i;
		
		if ( alp_Clan )
		{
			
			ShowButtonALP( alp_ButtonLeaveClan );
			ShowButtonALP( alp_ButtonKickMember );
			
			//display clan mate
			alp_ClanName.SetText(alp_Clan.Name);	
			
			alp_MembersCount = alp_Clan.Members.Count();
			
			for (i = 0; i < alp_MembersCount; i++)
			{			
				alp_ClanMembers.AddItem(alp_Clan.Members.GetElement(i),null,0);		
				ColorizedMember(i,	alp_Clan.Members.GetKey(i) );				
			}			
		
		}	
		else
		{
			alp_ClanName.SetText("...");	
			ShowButtonALP( alp_ButtonNewClan );
		}		
		
		
	}	
	
	void ColorizedMember(int line, int playerID )
	{
	
		if ( alp_Clan.MembersOnline.Find( playerID ) >= 0 )
		{		
			alp_ClanMembers.SetItemColor(line,0, COLOR_AVAILABLE_POSITIVE  );
		}
		else
		{
			alp_ClanMembers.SetItemColor(line,0, COLOR_UNAVAILABLE  );
		}

	}	
	
	void ShowButtonALP( ButtonWidget btn, bool state = true)
	{
		btn.Show(state);
		btn.Enable(state);	
		
		if ( state)
		{
			btn.SetColor( COLOR_AVAILABLE_POSITIVE );
		}
		else
		{
			btn.SetColor( COLOR_AVAILABLE_NEGATIVE );
		}
					
	}
	
	override bool OnClickALP(Widget w)
	{
		if (!super.OnClickALP(w))
		{
			switch (w.GetUserID())
			{
				case 13://show clan window
				{
					HideWindows();
					alp_WindowClan.Show(true);
					return true;
				}
				case 304://new clan
				{
					CreateNewClan();
					return true;	
				}
				case 305://leave clan	
				{
					LeaveClan();
					return true;		
				}
				case 306://kick
				{
					KickPlayer();	
					return true;	
				}
				case 310://SetCS_DisplayIcon
				{
					SetDisplayTMIcon(true);	
					return true;				
				}

			}	
			return false;		
		}
		return true;
	}	
	
	
	void DisableAllClanButtons()
	{
		for(int i = 0; i < alp_ClanButtons.Count(); i++)
		{
			ShowButtonALP( alp_ClanButtons.Get(i), false  );
		}
	}
		

	void SetDisplayTMIcon(bool change = false)
	{	
		//init checkBox DisplayIcon
		CheckBoxWidget displaIcon = CheckBoxWidget.Cast(layoutRoot.FindAnyWidgetById(310));
		
		if (displaIcon)
		{
			bool state = alp_Player.GetRP().GetClientData().ShowPlayersIcontem;
			
			if ( change )
			{
				state = !state;
				
				alp_Player.GetRP().GetClientData().ShowPlayersIcontem = state;
				alp_Player.GetRP().SaveClientData();
			
			}
			
			displaIcon.SetChecked(state);
					
			
		}
		
	}		
	
	
	void CreateNewClan()
	{
		string name = alp_NameOfClan.GetText();
		
		if ( name == STRING_EMPTY )
		{
			name = alp_Player.GetIdentity().GetName();
		}

		GetND().GetClans().CreateNewClanRPC( alp_Player, name );
		

	}
	
	void LeaveClan()
	{
		
		if ( alp_Clan )
		{
			if ( alp_Player.GetPlayerID() == alp_Clan.ClanID )
			{//disband
				GetND().GetClans().DisbandClanRPC( alp_Player, alp_Clan.ClanID );
			}
			else
			{//leave
				GetND().GetClans().LeaveClanRPC( alp_Player, alp_Clan.ClanID );
			}

		}

	}
	
	void KickPlayer()
	{
		
		if ( alp_Clan )
		{
			int id = alp_ClanMembers.GetSelectedRow();
			if (id >= 0)
			{	
				int playerID = alp_Clan.Members.GetKey(id);
				
				if ( alp_Clan.ClanID != playerID)
				{
					GetND().GetClans().KickHimRPC( alp_Player, alp_Clan.ClanID, playerID );
				}
				
			}

		}

	}	
	
}
