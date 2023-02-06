
class alpDNAstatsPanelBase
{
	PlayerBase alp_Player;
		
	WrapSpacerWidget alp_Parent;
	Widget alp_Main;

	
	ImageWidget alp_IconSaved;	
	
	ProgressBarWidget alp_BarLevelSaved;	
	ProgressBarWidget alp_BarProgresSaved;	

	ImageWidget alp_Icon;	
	
	ProgressBarWidget alp_BarLevel;	
	ProgressBarWidget alp_BarProgres;			

			
	float alp_SavedTotalExp = -1;


	float alp_SavedLevel;

	float alp_SavedExp;		

	

	float alp_Level;

	float alp_Exp;		
	
	void alpDNAstatsPanelBase(ref WrapSpacerWidget w, string iconSaved, string iconCurrent, bool widthIcon = false )
	{
		alp_Player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		alp_Parent = w;

		Widget root = GetGame().GetWorkspace().CreateWidgets( "ND_Role_Playing/gui/layouts/abilityStat.layout",w) ;
		alp_Main =  Widget.Cast( root.FindAnyWidget("STAT_panel") );
	
		
		alp_BarLevel = ProgressBarWidget.Cast( root.FindAnyWidget("STAT_level0") );
		alp_BarProgres = ProgressBarWidget.Cast( root.FindAnyWidget("STAT_progress0") );		
		
		alp_BarLevelSaved = ProgressBarWidget.Cast( root.FindAnyWidget("STAT_level") );
		alp_BarProgresSaved = ProgressBarWidget.Cast( root.FindAnyWidget("STAT_progress") );			

		
		if (!widthIcon)		
		{
			alp_IconSaved = ImageWidget.Cast( root.FindAnyWidget("STAT_icon") );
			alp_Icon = ImageWidget.Cast( root.FindAnyWidget("STAT_icon0") );
		}
		else 
		{
			alp_IconSaved = ImageWidget.Cast( root.FindAnyWidget("STAT_iconW") );				
			alp_Icon = ImageWidget.Cast( root.FindAnyWidget("STAT_iconW0") );	
		}
		
		SetIcons(iconSaved,iconCurrent);
		
		
		Update();
		
		
	}
	
	void Update()
	{
		SetValueLevel( GetLevel() );
		SetValueProgres( GetProgress() );	
		
		SetExpSaved();
	
	}
	
	void SetIcons(string iconSaved, string iconCurrent)
	{
		alp_IconSaved.LoadImageFile(0,iconSaved);
		alp_Icon.LoadImageFile(0,iconCurrent);
		alp_IconSaved.Show(true);		
		alp_Icon.Show(true);	
	
	}
	
	
	void SetExpSaved()
	{

			
		SetSavedLevelAndProgress();
			
		alp_BarLevelSaved.SetCurrent( alp_SavedLevel );
		alp_BarProgresSaved.SetCurrent( alp_SavedExp );
	
	}
	
	
	void SetSavedLevelAndProgress()
	{
		
	}
	
	
	
	
	void SetValueLevel(float value)
	{
		alp_Level = value;
		
		alp_BarLevel.SetCurrent( value );
	}
	
	void SetValueProgres(float value)
	{
		alp_Exp = value;
		
		alp_BarProgres.SetCurrent( value );
	}
			
	
	float GetLevel()
	{
	
		return 0;
	}
	float GetProgress()
	{
	
		return 0;
	}	
	
	float GetSavedExp()
	{
	
		return 0;
	}	
}


class alpDNAstatsDayzSoft extends alpDNAstatsPanelBase
{
	override void SetSavedLevelAndProgress()
	{
		
		float level = alp_Player.GetPlayerHive().GetStore().SavedDNA.SpecialtySoftEXP * 100;	
		
		if (level == 100 )
		{
			alp_SavedLevel = 100;		
			alp_SavedExp = 100;
		}
		else
		{
			alp_SavedLevel = 0;		
			alp_SavedExp = level;		
		}
		
	}
		
	override float GetLevel()
	{
		float soft = Math.AbsFloat( alp_Player.GetSoftSkillsManager().GetSpecialtyLevelSoft() );	
		
		int level;
		
		if (soft == 1 )
		{
			return 100;		
		}
		else
		{
			return 0;			
		}		
		
	}
	override float GetProgress()
	{
		float soft = Math.AbsFloat( alp_Player.GetSoftSkillsManager().GetSpecialtyLevelSoft() );	
		
		int level;
		
		if (soft == 1 )
		{
			return 100;		
		}
		else
		{
			return soft * 100;				
		}
	}	
		
}

class alpDNAstatsDayzHard extends alpDNAstatsPanelBase
{
	override void SetSavedLevelAndProgress()
	{
		float level = alp_Player.GetPlayerHive().GetStore().SavedDNA.SpecialtyRoughEXP * 100;	
		
		
		if (level == 100 )
		{
			alp_SavedLevel = 100;		
			alp_SavedExp = 100;
		}
		else
		{
			alp_SavedLevel = 0;		
			alp_SavedExp = level;		
		}
	}
		
	override float GetLevel()
	{
		float soft = Math.AbsFloat( alp_Player.GetSoftSkillsManager().GetSpecialtyLevelHard() );	
		
		
		if (soft == 1 )
		{
			return 100;		
		}
		else
		{
			return 0;			
		}		
		
	}
	override float GetProgress()
	{
		float soft = Math.AbsFloat( alp_Player.GetSoftSkillsManager().GetSpecialtyLevelHard() );	
		
		
		if (soft == 1 )
		{
			return 100;		
		}
		else
		{
			return soft * 100;				
		}
	}	
	
}


class alpDNAstatsHunting extends alpDNAstatsPanelBase
{
	override void SetSavedLevelAndProgress()
	{
		float exp   = alp_Player.GetPlayerHive().GetStore().SavedDNA.HuntingEXP;
		int level		= alp_Player.GetRP().GetHuntingLevelByEXP( exp );		

		int levelCap = GetND().GetRP().GetPerkHuntingLevelCup();		
		
		if ( level < levelCap )
		{
			alp_SavedExp = ( Math.AbsFloat( exp ) / alp_Player.GetRP().GetHuntingRequiredExp( level + 1 ) ) * 100;	
						
		}
		else
		{
			alp_SavedExp = 100;
		}			

		alp_SavedLevel = ( level / levelCap ) * 100;
				
	
	}
		
	override float GetLevel()
	{
		
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue();
		int cap = GetND().GetRP().GetPerkHuntingLevelCup();

		float levelRate = ( level / cap ) * 100;			
		
		return levelRate;	
		
	}
	override float GetProgress()
	{
		
		float progress;
		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.HUNTINGPROGRES ).GetValue(progress);
		
		return progress;
	}	
	

}


class alpDNAstatsColdResistance extends alpDNAstatsPanelBase
{
	override void SetSavedLevelAndProgress()
	{
		
		float level = alp_Player.GetPlayerHive().GetStore().SavedDNA.ResistanceColdEXP * 100;	
		
		if (level == 100 )
		{
			alp_SavedLevel = 100;		
			alp_SavedExp = 100;
		}
		else
		{
			alp_SavedLevel = 0;		
			alp_SavedExp = level;		
		}		

		
	}
#ifdef NAMALSK_SURVIVAL			
	override float GetLevel()
	{
		float soft = alp_Player.GetColdResistance();	
		
		
		if (soft == 100 )
		{
			return 100;		
		}
		else
		{
			return 0;			
		}		
		
	}
	override float GetProgress()
	{
		float soft = alp_Player.GetColdResistance();		
		

		if (soft == 100 )
		{
			return 100;		
		}
		else
		{
			return soft;				
		}
	}	
#endif 	

}


class alpDNAstatsRadiationResistance extends alpDNAstatsPanelBase
{
	override void SetSavedLevelAndProgress()
	{
	
		float exp   	= alp_Player.GetPlayerHive().GetStore().SavedDNA.ResistanceEXP;
		int level		= alp_Player.GetRP().GetRadiationResistanceLevelByEXP( exp );		

		int levelCap = GetND().GetRP().GetPerkRadiationResistanceLevelCup();		
		
		if ( level < levelCap )
		{
			alp_SavedExp = ( Math.AbsFloat( exp ) / alp_Player.GetRP().GetRadiationResistanceRequiredExp( level + 1 ) ) * 100;	
						
		}
		else
		{
			alp_SavedExp = 100;
		}			

		alp_SavedLevel = ( level / levelCap ) * 100;
													
			
	}
		
	override float GetLevel()
	{
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.RAD_RESIST ).GetValue();
		int cap = GetND().GetRP().GetPerkRadiationResistanceLevelCup();

		float levelRate = ( level / cap ) * 100;			
		
		return levelRate;
		
	}
	override float GetProgress()
	{
		float progress;
		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.RAD_RESISTPROGRES ).GetValue(progress);
		
		return progress;
	}	
	
}

class alpDNAstatsStamina extends alpDNAstatsPanelBase
{
	override void SetSavedLevelAndProgress()
	{
		
		float exp   = alp_Player.GetPlayerHive().GetStore().SavedDNA.StaminaEXP;
		int level		= alp_Player.GetRP().GetStaminaLevelByEXP( exp );		

		int levelCap = GetND().GetRP().GetPerkStaminaLevelCup();		
		
		if ( level < levelCap )
		{
			alp_SavedExp = ( Math.AbsFloat( exp ) / alp_Player.GetRP().GetStaminaRequiredExp( level + 1 ) ) * 100;	
						
		}
		else
		{
			alp_SavedExp = 100;
		}			

		alp_SavedLevel = ( level / levelCap ) * 100;
	
	}
		
	override float GetLevel()
	{
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue();
		int cap = GetND().GetRP().GetPerkStaminaLevelCup();

		float levelRate = ( level / cap ) * 100;			
		
		return levelRate;	
		
	}
	override float GetProgress()
	{
		float progress;
		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.STAMINAPROGRES ).GetValue(progress);
		
		return progress;
	}	
		
}



class alpDNAstatsReputation extends alpDNAstatsPanelBase
{
	int alp_SavedLevelAbsulte;		
	
	override void SetSavedLevelAndProgress()
	{
		float exp   = alp_Player.GetPlayerHive().GetStore().SavedDNA.ReputationEXP;
		int level		= Math.AbsInt( alp_Player.GetRP().GetReputationLevelByEXP( exp ) );		

		alp_SavedLevelAbsulte = level;
		
		int levelCap = GetND().GetRP().GetPerkReputationLevelCup();		
		
		if ( level < levelCap )
		{
			alp_SavedExp = ( Math.AbsFloat( exp ) / alp_Player.GetRP().GetReputationRequiredExp( level + 1 ) ) * 100;	
						
		}
		else
		{
			alp_SavedExp = 100;
		}			

		alp_SavedLevel = ( level / levelCap ) * 100;
		

	}
		
	override float GetLevel()
	{
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.REPUTATION ).GetValue();
		int cap = GetND().GetRP().GetPerkStaminaLevelCup();

		float levelRate = ( level / cap ) * 100;			
		
		return levelRate;	
		
	}
	override float GetProgress()
	{
		float progress;
		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.STAMINAPROGRES ).GetValue(progress);
		
		return Math.AbsFloat( progress );
	}	
		
	
	override void SetIcons(string iconSaved, string iconCurrent)
	{

		iconSaved = "ND_MISSIONS/gui/images/Reputation/r" + alp_SavedLevelAbsulte.ToString() + ".paa";
		iconCurrent = "ND_MISSIONS/gui/images/Reputation/r" + alp_Player.GetSyncData().GetElement(alpRPelements.REPUTATION).GetValue().ToString() + ".paa";
		
		alp_IconSaved.LoadImageFile(0,iconSaved);
		alp_Icon.LoadImageFile(0,iconCurrent);
		alp_IconSaved.Show(true);		
		alp_Icon.Show(true);	
	
	}	
	
	override void Update()
	{
		SetValueLevel( GetLevel() );
		SetValueProgres( GetProgress() );	
		
		SetExpSaved( );
		SetIcons("","");
	}
		
}


class alpDNAstatsToxicResistance extends alpDNAstatsPanelBase
{
	override void SetSavedLevelAndProgress()
	{
		float exp   = alp_Player.GetPlayerHive().GetStore().SavedDNA.ResistanceToxicEXP;
		int level		= alp_Player.GetRP().GetToxicResistanceLevelByEXP( exp );		

		int levelCap = GetND().GetRP().GetPerkToxicResistanceLevelCup();		
		
		if ( level < levelCap )
		{
			alp_SavedExp = ( Math.AbsFloat( exp ) / alp_Player.GetRP().GetToxicResistanceRequiredExp( level + 1 ) ) * 100;	
						
		}
		else
		{
			alp_SavedExp = 100;
		}			

		alp_SavedLevel = ( level / levelCap ) * 100;									
			
	}
		
	override float GetLevel()
	{
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.TOXIC_RESIST ).GetValue();
		int cap = GetND().GetRP().GetPerkToxicResistanceLevelCup();

		float levelRate = ( level / cap ) * 100;			
		
		return levelRate;	
		
	}
	override float GetProgress()
	{
		float progress;
		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.TOXIC_RESISTPROGRES ).GetValue(progress);
		
		return progress;
	}	
	
}