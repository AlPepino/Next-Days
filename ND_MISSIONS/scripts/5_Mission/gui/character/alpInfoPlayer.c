


class alpInfoPlayerMenu extends UIScriptedMenu
{
	int										alp_AbilityBorderOffset;
	
	protected PlayerBase					alp_Player;
	protected ref PlayerPreviewWidget 		alp_CharacterPanelWidget;
	
	
	WrapSpacerWidget						alp_StatsGroupHealt
	WrapSpacerWidget 						alp_StatsGroupHealtContainer;
	
	WrapSpacerWidget						alp_StatsGroupAbility
	WrapSpacerWidget 						alp_StatsGroupAbilityContainer;	
	
	WrapSpacerWidget						alp_StatsGroupResistance
	WrapSpacerWidget 						alp_StatsGroupResistanceContainer;		
	
	Widget 									alp_StatsGroupReputation
	WrapSpacerWidget 						alp_StatsGroupReputationContainer;		
	
	ref map<int, ref alpHealhtStat> 		alp_HealthStats = new map<int, ref alpHealhtStat>;
	
	ref map<int, ref alpAbilityStat> 		alp_AbilityStats = new map<int, ref alpAbilityStat>;
	
	ref map<int, ref alpAbilityStat> 		alp_ResistanceStats = new map<int, ref alpAbilityStat>;
	
	ref map<int, ref alpAbilityStat> 		alp_ReputationStats = new map<int, ref alpAbilityStat>;

	
	ref array<Widget>						alp_WindowRegister = new array<Widget>;
	
	Widget									alp_WindowStats;
	
	ref alpAbilityStat 						alp_FrostResist;
	
	override Widget Init()
	{

		
		Class.CastTo(alp_Player,GetGame().GetPlayer());
		
		layoutRoot 	= GetGame().GetWorkspace().CreateWidgets("ND_MISSIONS/gui/layouts/InfoPlayer.layout");
		
		//stats window
		alp_WindowStats = Widget.Cast( layoutRoot.FindAnyWidget( "BodyWindowStats") ); 
		alp_WindowRegister.Insert( alp_WindowStats );
		
		//group Health
		alp_StatsGroupHealt = WrapSpacerWidget.Cast( layoutRoot.FindAnyWidget( "BL_groupHealth") );
		alp_StatsGroupHealtContainer = WrapSpacerWidget.Cast( layoutRoot.FindAnyWidget( "Bl_groupHealthContainer") );
		//group ability		
		alp_StatsGroupAbility = WrapSpacerWidget.Cast( layoutRoot.FindAnyWidget( "BL_groupAbility") );
		alp_StatsGroupAbilityContainer = WrapSpacerWidget.Cast( layoutRoot.FindAnyWidget( "Bl_groupStatsContainer") );		

		//group Resistance
		alp_StatsGroupResistance = WrapSpacerWidget.Cast( layoutRoot.FindAnyWidget( "BL_groupResistance") );
		alp_StatsGroupResistanceContainer = WrapSpacerWidget.Cast( layoutRoot.FindAnyWidget( "Bl_groupResistanceContainer") );			
		
		//group repuation	
		alp_StatsGroupReputation = Widget.Cast( layoutRoot.FindAnyWidget( "BL_groupReputation") );
		alp_StatsGroupReputationContainer = WrapSpacerWidget.Cast( layoutRoot.FindAnyWidget( "Bl_groupReputationContainer") );			
		alp_StatsGroupReputation.Show(false);
	
		Class.CastTo(alp_CharacterPanelWidget,layoutRoot.FindAnyWidget("BR_PlayerPreview"));
		alp_CharacterPanelWidget.SetPlayer( alp_Player);
		alp_CharacterPanelWidget.UpdateItemInHands( alp_Player.GetHumanInventory().GetEntityInHands() );
		alp_Player.GetSyncData().RegisterToEnhancedStatsSync(true);
		
		InitStats();
								
		layoutRoot.Show(false);
		
		
		
		return layoutRoot;
	}
	
	void ~alpInfoPlayerMenu()
	{
		alp_Player.GetSyncData().RegisterToEnhancedStatsSync(false);
				
		
		//disable hint window 
		
		int i;
		for (i=0;i<alp_ResistanceStats.Count();i++)
		{
			alp_ResistanceStats.GetElement(i).OnMouseLeave();
		}			
		for (i=0;i<alp_AbilityStats.Count();i++)
		{
			alp_AbilityStats.GetElement(i).OnMouseLeave();
		}	
		for (i=0;i<alp_HealthStats.Count();i++)
		{
			alp_HealthStats.GetElement(i).OnMouseLeave();
		}
		for (i=0;i<alp_ReputationStats.Count();i++)
		{
			alp_ReputationStats.GetElement(i).OnMouseLeave();
		}		
						
	}	
	
	void HideWindows()
	{
		for (int i = 0; i< alp_WindowRegister.Count(); i++ )
		{
			alp_WindowRegister.Get(i).Show(false);
		}		
	}
	
	
	
		
	void InitStats()
	{
		//ID container for Health		
		InitHeathlStats();
		InitAbilityStats();
		InitReputationStats();
		//update border health group
		
		/*
		float width,height;
		
		alp_StatsGroupHealt.GetSize( width, height );
		height = 30 + alp_HealthStats.Count() * 36;
		alp_StatsGroupHealt.SetSize(width,height);
		*/
		
		//update border ability group  
		if ( alp_AbilityStats.Count() > 0 )
		{
			
		}
		else
		{
			Widget panel = Widget.Cast( layoutRoot.FindAnyWidget( "BL_groupAbility") );			
			panel.Show( false );
		}
		
		if ( alp_ResistanceStats.Count() > 0 )
		{
			
		}
		else
		{
			Widget panel2 = Widget.Cast( layoutRoot.FindAnyWidget( "BL_groupResistance") );			
			panel2.Show( false );
		}				
		
	}
	
	void InitReputationStats()
	{
	}	
	void InitHeathlStats()
	{
		float value;
		
		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.HEALTH).GetValue(value);
		alp_HealthStats.Set( alpRPelementsEnahnced.HEALTH , new alpHealhtStat("set:dayz_gui image:iconHealth0", alp_StatsGroupHealtContainer, value ) );
		
		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.BLOOD).GetValue(value);
		alp_HealthStats.Set( alpRPelementsEnahnced.BLOOD , new alpHealhtStat("set:dayz_gui image:iconBlood0", alp_StatsGroupHealtContainer, value ) );

		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.WATER).GetValue(value);
		alp_HealthStats.Set( alpRPelementsEnahnced.WATER , new alpHealhtStat("set:dayz_gui image:iconThirsty0", alp_StatsGroupHealtContainer, value ) );

		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.FOOD).GetValue(value);
		alp_HealthStats.Set( alpRPelementsEnahnced.FOOD , new alpHealhtStat("set:dayz_gui image:iconHungry0", alp_StatsGroupHealtContainer, value ) );		
		
		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.STOMACH).GetValue(value);
		alp_HealthStats.Set( alpRPelementsEnahnced.STOMACH , new alpHealhtStat("set:dayz_gui image:iconStomach2", alp_StatsGroupHealtContainer, value ) );	
	}
	
	void InitAbilityStats()
	{
#ifdef NAMALSK_SURVIVAL	
		int progres = alp_Player.GetColdResistance();
		
		int level;
		
		if (progres == 100 )
		{
			level = 100;	
			alp_FrostResist = new alpAbilityStat("set:nam_gui_icons image:coldresistfull2", alp_StatsGroupResistanceContainer, level, progres );		
		}
		else
		{
			level = 0;
			alp_FrostResist = new alpAbilityStat("set:nam_gui_icons image:coldresistfull2", alp_StatsGroupResistanceContainer, level, progres );				
		}	
		
		alp_ResistanceStats.Set( -1 , alp_FrostResist );
		
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillHintColdResistance",500,false, new Param1<alpAbilityStat>(alp_FrostResist));
#endif 		
	}

	void FillHintColdResistance( alpAbilityStat panel)
	{
		
		TStringArray title = new TStringArray;		
		title.Insert("#ip_coldresistance");	
		panel.AddHint( title );
		
	}	
	
	void UpdateHealhtStat()
	{
		for (int i = 0; i < alp_HealthStats.Count(); i++)
		{
			int type = alp_HealthStats.GetKey(i);
						
			float value;
			if ( alp_Player.GetSyncData().GetElementEnhanced(type).GetValue(value) )
			{//update HUD
				alp_HealthStats.GetElement(i).SetValue(value);			
			}				
		}
	}
	
	void UpdateResistanceStat()
	{
		for (int i = 0; i < alp_ResistanceStats.Count(); i++)
		{
			int type = alp_ResistanceStats.GetKey(i);
			
			if ( type >= 0 )
			{			
				float value;	
				if ( alp_Player.GetSyncData().GetElementEnhanced( type ).GetValue(value) )
				{//update HUD
					alp_ResistanceStats.GetElement(i).SetValueProgres(value);		//progres	
				}	
			}				
		}
	}	
	
	void UpdateAbilityStat()
	{
		for (int i = 0; i < alp_AbilityStats.Count(); i++)
		{
			int type = alp_AbilityStats.GetKey(i);
			
			if ( type >= 0 )
			{			
				float value;	
				if ( alp_Player.GetSyncData().GetElementEnhanced( type ).GetValue(value) )
				{//update HUD
					alp_AbilityStats.GetElement(i).SetValueProgres(value);		//progres	
				}	
			}				
		}
	}	
	void UpdateReputationStat()
	{
		for (int i = 0; i < alp_ReputationStats.Count(); i++)
		{
			int type = alp_ReputationStats.GetKey(i);
						
			float value;	
			if ( alp_Player.GetSyncData().GetElementEnhanced( type ).GetValue(value) )
			{//update HUD
				alp_ReputationStats.GetElement(i).SetValueProgres(value);		//progres	
			}					
		}
	}
	
	float alp_TickCounter;
			
	override void Update(float timeslice)
	{
		super.Update(timeslice);		
		UpdateHealhtStat();
		UpdateAbilityStat();
		UpdateResistanceStat();
		UpdateReputationStat();
		
#ifdef NAMALSK_SURVIVAL	
		alp_TickCounter += timeslice;
		
		if ( alp_FrostResist && alp_TickCounter > 1 )
		{
			alp_TickCounter = 0;
			
			int progres = alp_Player.GetColdResistance();
			
			int level;
			
			if (progres == 100 )
			{
				level = 100;		
			}
			else
			{
				level = 0;					
			}	
						
			alp_FrostResist.SetValueLevel(level );
			
			alp_FrostResist.SetValueProgres(progres );
			

		}		
#endif 				
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (super.OnClick(w, x, y, button)){
			return true;
		}
		else {			
		
			switch (w.GetUserID())
			{		
				//main menu				
				return OnClickALP(w);
			}
	
			return false;
		}
	}	
	
	bool OnClickALP(Widget w)
	{
		
		
		if (w.GetUserID() == 1)//close window
		{
			Close();
			return true;
		}
		if (w.GetUserID() == 11)//close window
		{
			HideWindows();
			alp_WindowStats.Show(true);
			return true;
		}		
		return false;
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
	
	override bool OnMouseEnter(Widget w, int x, int y)
	{

		int i =0;
		Widget panel;
		for (i=0;i<alp_HealthStats.Count();i++)
		{
			panel = alp_HealthStats.GetElement(i).GetWidget();			
			if ( w == panel )
			{
				alp_HealthStats.GetElement(i).OnMouseEnter(x,y);
				return true;
			}
		}		
		for (i=0;i<alp_AbilityStats.Count();i++)
		{
			panel = alp_AbilityStats.GetElement(i).GetWidget();			
			if ( w == panel )
			{
				alp_AbilityStats.GetElement(i).OnMouseEnter(x,y);
				return true;
			}
		}
		for (i=0;i<alp_ResistanceStats.Count();i++)
		{
			panel = alp_ResistanceStats.GetElement(i).GetWidget();			
			if ( w == panel )
			{
				alp_ResistanceStats.GetElement(i).OnMouseEnter(x,y);
				return true;
			}
		}		
		for (i=0;i<alp_ReputationStats.Count();i++)
		{
			panel = alp_ReputationStats.GetElement(i).GetWidget();			
			if ( w == panel )
			{
				alp_ReputationStats.GetElement(i).OnMouseEnter(x,y);
				return true;
			}
		}		
		return false;
	}	
	
	override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
	{
		
		int i =0;
		Widget panel;
		for (i=0;i<alp_HealthStats.Count();i++)
		{
			panel = alp_HealthStats.GetElement(i).GetWidget();
			
			if ( w == panel )
			{
				alp_HealthStats.GetElement(i).OnMouseLeave();
				return true;
			}
		}		
		for (i=0;i<alp_AbilityStats.Count();i++)
		{
			panel = alp_AbilityStats.GetElement(i).GetWidget();
			
			if ( w == panel )
			{
				alp_AbilityStats.GetElement(i).OnMouseLeave();
				return true;
			}
		}
		for (i=0;i<alp_ResistanceStats.Count();i++)
		{
			panel = alp_ResistanceStats.GetElement(i).GetWidget();
			
			if ( w == panel )
			{
				alp_ResistanceStats.GetElement(i).OnMouseLeave();
				return true;
			}
		}		
		for (i=0;i<alp_ReputationStats.Count();i++)
		{
			panel = alp_ReputationStats.GetElement(i).GetWidget();
			
			if ( w == panel )
			{
				alp_ReputationStats.GetElement(i).OnMouseLeave();
				return true;
			}
		}		
		return false;
	}
}
