
modded class alpInfoPlayerMenu extends UIScriptedMenu
{
	Widget									alp_WindowHoF;
	TextListboxWidget						alp_HOFlist;
	
	ref alpReputationStat alp_ReputationExtraPanel;
	float alp_ScoreMax;
		
	override Widget Init()
	{
		Widget root = super.Init();
		
		if ( GetND().GetRP().GetPerkReputation().EnableHallOfFame )
		{
			//HoF window
			alp_WindowHoF = Widget.Cast( root.FindAnyWidget( "BodyWindowHallOfFame") ); 
			alp_WindowRegister.Insert( alp_WindowHoF );	
			
			ButtonWidget menu = ButtonWidget.Cast( root.FindAnyWidgetById(14) );
			menu.Show(true);
			
			//HoF data
			Class.CastTo(alp_HOFlist, root.FindAnyWidget("HallOfFameList"));
			InitHOF();
		}	
		
		return root;
	}		
	
	void InitHOF()
	{
		alp_HOFlist.ClearItems();
		alp_HOFlist.SetFlags( WidgetFlags.CENTER );
		int r;
		int count = GetND().GetRP().GetHoFdata().Count();
		
		for (int i = 0; i < count; i++){
			r = i + 1;	
			alp_HOFlist.AddItem(r.ToString(),null,0);	
			alp_HOFlist.SetItem(i,GetND().GetRP().GetHoFdata().Get(i).Name,null,1);
			alp_HOFlist.SetItem(i,alpUF.NumberToString(GetND().GetRP().GetHoFdata().Get(i).Reputation,1),null,2);
			alp_HOFlist.SetItem(i,GetND().GetRP().GetHoFdata().Get(i).KilledPlayers.ToString(),null,3);
			alp_HOFlist.SetItem(i,GetND().GetRP().GetHoFdata().Get(i).SkinnedPlayers.ToString(),null,4);
			alp_HOFlist.SetItem(i,GetND().GetRP().GetHoFdata().Get(i).KilledZombies.ToString(),null,5);
			alp_HOFlist.SetItem(i,GetND().GetRP().GetHoFdata().Get(i).KilledAnimals.ToString(),null,6);
			
		}
				
	}
		
	
	override void InitAbilityStats()
	{
		super.InitAbilityStats();
		int level,cap;
		float progress, levelRate;
		//stamina
		if ( GetND().GetRP().GetPerksOptions().EnablePerkStamina )
		{

			alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.STAMINAPROGRES ).GetValue(progress);
	
			level = alp_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue();
			cap = GetND().GetRP().GetPerkStaminaLevelCup();

			levelRate = ( level / cap ) * 100;			
			 
			
			alpAbilityStatStamina staminaPanel = new alpAbilityStatStamina("set:dayz_gui image:iconShock", alp_StatsGroupAbilityContainer, levelRate, progress );
			alp_AbilityStats.Set( alpRPelementsEnahnced.STAMINAPROGRES , staminaPanel );	//STAMINAPROGRES
			
			
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillHintStamina",500,false, new Param1< alpAbilityStat>(staminaPanel));
		}
	
		//dayz skills
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{
			//soft
			alpAbilityStat specialtySoft;
			
			float soft = Math.AbsFloat( alp_Player.GetSoftSkillsManager().GetSpecialtyLevelSoft() );
			
			if (soft == 1 )
			{
				level = 100;	
				specialtySoft = new alpAbilityStat("set:dayz_gui image:icon_needle", alp_StatsGroupAbilityContainer, level, soft * 100 );		
			}
			else
			{
				level = 0;
				specialtySoft = new alpAbilityStat("set:dayz_gui image:icon_needle", alp_StatsGroupAbilityContainer, level, soft * 100 );				
			}			
				
			alp_AbilityStats.Set( -2 , specialtySoft );	
			
			alp_AbilityBorderOffset += 1;		
			
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillHintSpecialtySoft",500,false, new Param1< alpAbilityStat>(specialtySoft));
			
			
			//rough skill
			alpAbilityStat specialtyHard;
			
			float hard = Math.AbsFloat( alp_Player.GetSoftSkillsManager().GetSpecialtyLevelHard() );
		
			
			if (hard == 1 )
			{
				level = 100;	
				specialtyHard = new alpAbilityStat("set:dayz_gui image:icon_hammer", alp_StatsGroupAbilityContainer, level, hard * 100 );		
			}
			else
			{
				level = 0;
				specialtyHard = new alpAbilityStat("set:dayz_gui image:icon_hammer", alp_StatsGroupAbilityContainer, level, hard * 100 );				
			}			
				
			alp_AbilityStats.Set( -3 , specialtyHard );	
			
			alp_AbilityBorderOffset += 1;		
			
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillHintSpecialtyHard",500,false, new Param1< alpAbilityStat>(specialtyHard));			
		
		}

		//hunting
		if ( GetND().GetRP().GetPerksOptions().EnablePerkHunting )
		{

			alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.HUNTINGPROGRES ).GetValue(progress);
	
			level = alp_Player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue();
			cap = GetND().GetRP().GetPerkHuntingLevelCup();

			levelRate = ( level / cap ) * 100;			
			 
			
			alpAbilityStatHunting HuntingPanel = new alpAbilityStatHunting("ND_MISSIONS/gui/images/HuntingIcon.paa", alp_StatsGroupAbilityContainer, levelRate, progress );
			alp_AbilityStats.Set( alpRPelementsEnahnced.HUNTINGPROGRES , HuntingPanel );	//HuntingPROGRES
			
			
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillHintHunting",500,false, new Param1< alpAbilityStat>(HuntingPanel));
		}				

		
		//Rad resistance
		if ( GetND().GetRP().GetPerksOptions().EnablePerkRadiationResistance )
		{

			alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.RAD_RESISTPROGRES ).GetValue(progress);
	
			level = alp_Player.GetSyncData().GetElement( alpRPelements.RAD_RESIST ).GetValue();
			cap = GetND().GetRP().GetPerkRadiationResistanceLevelCup();

			levelRate = ( level / cap ) * 100;			
			 
			
			alpAbilityStatRadResistance  radResistPanel = new alpAbilityStatRadResistance ("ND_MISSIONS/gui/images/RadiationShield.paa", alp_StatsGroupResistanceContainer, levelRate, progress );
			alp_ResistanceStats.Set( alpRPelementsEnahnced.RAD_RESISTPROGRES , radResistPanel );	
			
			
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillHintRadResistance",500,false, new Param1< alpAbilityStat>(radResistPanel));
		}		
		
		//Toxic resistance
		if ( GetND().GetRP().GetPerksOptions().EnablePerkToxicResistance )
		{

			alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.TOXIC_RESISTPROGRES ).GetValue(progress);
	
			level = alp_Player.GetSyncData().GetElement( alpRPelements.TOXIC_RESIST ).GetValue();
			cap = GetND().GetRP().GetPerkToxicResistanceLevelCup();

			levelRate = ( level / cap ) * 100;			
			 
			
			alpAbilityStatToxicResistance  toxicResistPanel = new alpAbilityStatToxicResistance ("ND_MISSIONS/gui/images/ToxicShield.paa", alp_StatsGroupResistanceContainer, levelRate, progress );
			alp_ResistanceStats.Set( alpRPelementsEnahnced.TOXIC_RESISTPROGRES , toxicResistPanel );	
			
			
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillHintToxicResistance",500,false, new Param1< alpAbilityStat>(toxicResistPanel));
		}					
	}
	
	void FillHintToxicResistance( alpAbilityStat panel)
	{
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.TOXIC_RESIST ).GetValue();
		
		TStringArray title = new TStringArray;		
		title.Insert("#ip_toxicresistence");	
		panel.AddHint( title );
	
		//current level 
		TStringArray title2 = new TStringArray;		
		string t_value2 = level.ToString();
		title2.Insert("#ip_level");		
		title2.Insert(t_value2);	
		panel.AddHint( title2 );

		float value = GetND().GetRP().GetPerkToxicResistanceMdf( level );
		//resistance mdf
		TStringArray title4 = new TStringArray;		
		string t_value4 = value.ToString() + " %";
		title4.Insert("#ip_toxicresistancemdf");		
		title4.Insert(t_value4);	
		panel.AddHint( title4 );		
		
	}	
	
	void FillHintRadResistance( alpAbilityStat panel)
	{
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.RAD_RESIST ).GetValue();
		
		TStringArray title = new TStringArray;		
		title.Insert("#ip_resistence");	
		panel.AddHint( title );
	
		//current level 
		TStringArray title2 = new TStringArray;		
		string t_value2 = level.ToString();
		title2.Insert("#ip_level");		
		title2.Insert(t_value2);	
		panel.AddHint( title2 );

		float value = GetND().GetRP().GetPerkRadiationResistanceMdf( level );
		//resistance mdf
		TStringArray title4 = new TStringArray;		

		string t_value4 = value.ToString() + " %";
		title4.Insert("#ip_resistancemdf");		
		title4.Insert(t_value4);	
		panel.AddHint( title4 );		
		
	}	
	void FillHintStamina( alpAbilityStat panel)
	{
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue();
		
		TStringArray title = new TStringArray;		
		title.Insert("#ip_stamina");	
		panel.AddHint( title );
	
		//current level 
		TStringArray title2 = new TStringArray;		
		string t_value2 = level.ToString();
		title2.Insert("#ip_level");		
		title2.Insert(t_value2);	
		panel.AddHint( title2 );
	

		float value = GetND().GetRP().GetPerkStaminaMdf( level );
		value = ( 1 / value - 1 ) * 100;

		string valueText = value.ToString();		
		if (valueText.Length() > 3 )
		{
			valueText = valueText.Substring(0,3);		
		}
		//stamina mdf
		TStringArray title4 = new TStringArray;		

		string t_value4 = valueText + " %";
		title4.Insert("#ip_staminamdf");		
		title4.Insert(t_value4);	
		panel.AddHint( title4 );						
	
				
	
	}
	
	void FillHintHunting( alpAbilityStat panel)
	{
		
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue();
		
		TStringArray title = new TStringArray;		
		title.Insert("#ip_hunting");	
		panel.AddHint( title );
	
		//current level 
		TStringArray title2 = new TStringArray;		
		string t_value2 = level.ToString();
		title2.Insert("#ip_level");		
		title2.Insert(t_value2);	
		panel.AddHint( title2 );

		
		//skill to skin
		TStringArray title3 = new TStringArray;		
		string t_value3 = GetND().GetRP().GetPerkHunting().RequiredLevelToSkin.ToString();
		title3.Insert("#ip_huntingrequiredskill_to_skin");		
		title3.Insert(t_value3);	
		panel.AddHint( title3 );		

		float value = GetND().GetRP().GetPerkHuntingMdf( level );
		
		value = value * 100 - 100;
		//hunting mdf
		TStringArray title4 = new TStringArray;		
		string t_value4 = value.ToString() + " %";
		title4.Insert("#ip_huntingmdf");		
		title4.Insert(t_value4);	
		panel.AddHint( title4 );						
	
		//damage mdf
		value = GetND().GetRP().GetPerkHuntingDamageMdf( level );
		value = value * 100;
		TStringArray title5 = new TStringArray;		
		string t_value5 = value.ToString() + " %";
		title5.Insert("#ip_huntingdamagemdf");		
		title5.Insert(t_value5);	
		panel.AddHint( title5 );					
	
	}
		
	void FillHintSpecialtySoft( alpAbilityStat panel)
	{
		
		TStringArray title = new TStringArray;		
		title.Insert("#ip_specialtysoft");	
		panel.AddHint( title );
		
	}

	
	void FillHintSpecialtyHard( alpAbilityStat panel)
	{
		
		TStringArray title = new TStringArray;		
		title.Insert("#ip_specialtyrough");	
		panel.AddHint( title );
		
	}	
	
	
	override bool OnClickALP(Widget w)
	{
		if (!super.OnClickALP(w))
		{
			if (w.GetUserID() == 14)//close window
			{
				HideWindows();
				alp_WindowHoF.Show(true);
				return true;
			}	
			return false;		
		}
		return true;
	}		
	
	override void InitReputationStats()
	{
		super.InitReputationStats();
		
		
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkReputation )
		{
			
			alp_StatsGroupReputation.Show(true);
	
			float progres,cap,levelRate;
			int level;
			
			alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.REPUTATIONPROGRES ).GetValue(progres);
			level = alp_Player.GetSyncData().GetElement( alpRPelements.REPUTATION ).GetValue();
			
			cap = GetND().GetRP().GetPerkReputationLevelCup();
			
			levelRate = ( level / cap ) * 100;	
			
			
			string icon = "ND_MISSIONS/gui/images/Reputation/r" + level.ToString() + ".paa";
			alpAbilityStat reputationPanel = new alpAbilityStat(icon, alp_StatsGroupReputationContainer, levelRate, progres , true);
			alp_ReputationStats.Set( alpRPelementsEnahnced.REPUTATIONPROGRES , reputationPanel );				
					
			
			
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillHintReputation",500,false, new Param1< alpAbilityStat>(reputationPanel));
			
			
			float score;			
			
			alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.SCORE ).GetValue(score);


					
			alp_ScoreMax = alp_Player.GetPlayerHive().GetStore().BestScore;
			

			alp_ReputationExtraPanel = new alpReputationStat( alp_StatsGroupReputationContainer , score , alp_ScoreMax );//init by CallLater
			
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "FillReputationRecord",500,false, new Param1< alpReputationStat>(alp_ReputationExtraPanel));
			

		}
	
	}	
	
	override void UpdateReputationStat()
	{
		super.UpdateReputationStat();
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkReputation )
		{		
			float score;			
				
			alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.SCORE ).GetValue(score);		
		
			alp_ReputationExtraPanel.SetReputationRecord( score , alp_ScoreMax );
		}
		
	}	
	
	
	void FillReputationRecord( alpReputationStat panel)
	{
		float score;
		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.SCORE ).GetValue(score);
		
		float scoreMax = alp_Player.GetPlayerHive().GetStore().BestScore;			
		
		panel.SetReputationRecord(score,scoreMax);
		
	}	
	void FillHintReputation( alpAbilityStat panel)
	{
		
		TStringArray title = new TStringArray;		
		title.Insert("#ip_reputation");	
		panel.AddHint( title );

		string role;
		if ( alp_Player.GetRP().IsHero() )
			role="#ip_role_hero";
		else
			role="#ip_role_bandit";	
		
		TStringArray title0 = new TStringArray;		
		title0.Insert(role);	
		panel.AddHint( title0 );		
			
		//current level 
		TStringArray title2 = new TStringArray;		
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.REPUTATION ).GetValue();
		string t_value2 = "#ip_rank" + level.ToString();
		title2.Insert("#ip_level");		
		title2.Insert(t_value2);	
		panel.AddHint( title2 );
	
		//sale
		float value  = Math.Round( (GetND().GetRP().GetReputationMdf( level )  ) * 100 );
		TStringArray title4 = new TStringArray;		
		string t_value4 = value.ToString() + " %";
		title4.Insert("#ip_reputationsalesmdf");		
		title4.Insert(t_value4);	
		panel.AddHint( title4 );						

				
	
	}	
	
	
	override void InitHeathlStats()
	{
		super.InitHeathlStats();
		
		
		if ( GetND().GetRP().GetPerksOptions().EnableFatigue )
		{
		
			float level;

			alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.FATIGUE ).GetValue(level);
	
			
			
			alpHealhtStat fatigue = new alpHealhtStat("set:nd_dayz_gui image:iconTiredness0", alp_StatsGroupHealtContainer, level );
			alp_HealthStats.Set( alpRPelementsEnahnced.FATIGUE , fatigue );	
			
			
			
		}
	
	}	
}
