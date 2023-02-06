

modded class alpPlayerHive
{
	float alp_TEMP_reputationEXP;
	
	
	override void WriteSmallSync( ref ScriptRPC rpc)
	{
		super.WriteSmallSync( rpc );
		rpc.Write( alp_StoreValues.BestScore );
	}
	
	override void SyncSmallRPC( ParamsReadContext ctx )
	{
		super.SyncSmallRPC( ctx );
		ctx.Read( alp_StoreValues.BestScore );
	}
	
	

	
	
	override void OnDeath()
	{
		super.OnDeath();
	
		if ( GetPlayer().GetIdentity() )		
		{
			SaveCommonStats();
			
			if ( HasLifeInsurance() )
			{			
				SecureStats();
			}
			else
			{
				SecureStats(true);
			}

					
		
			Save(false);
		}
	}
	override void OnDisconnect()
	{
		super.OnDisconnect();
	
		if ( GetPlayer().GetIdentity() )		
		{
			if (GetPlayer().IsUnconscious() || GetPlayer().IsRestrained())
			{
				// kill character
				SaveCommonStats();
					
				if ( HasLifeInsurance() && !( GetPlayer().IsUnconscious() || GetPlayer().IsRestrained() ) )
				{			
					SecureStats();
				}
				else
				{
					SecureStats(true);
				}				
				
			}			
	
		
			Save(false);
		}
	}
	
	
	override void OnConnect()
	{
		super.OnConnect();
		
		
		if (GetGame().IsServer() )
		{
			if ( GetStore().Event & ALP_SPAWN_EVENT.RESTORE_STATS   )
			{
				RestoreStats();
			}		
		
			
#ifdef NAMALSK_SURVIVAL			
			alp_Player.UpdateColdResistance( 0 );							
#endif 							
			Save(false);
		}
		
	}
	

	void SaveCommonStats()
	{
		
		alp_TEMP_reputationEXP  = GetPlayer().GetRP().GetTotalReputationExp(); 
		
		float savedReputation = alp_TEMP_reputationEXP;
		
		if ( GetND().GetRP().GetPerkReputation().StoreLastSessionInHoF )
		{
			savedReputation = alp_Player.GetStatCurrentScore().Get();//current session	
					
		}
		

		if ( Math.AbsFloat(savedReputation) > Math.AbsFloat(GetStore().BestScore) )
		{
			GetStore().BestScore = savedReputation;
		}
			
		//save record		
		if ( GetND().GetRP().GetPerkReputation().EnableHallOfFame )
		{
			if  ( Math.AbsFloat( savedReputation ) >  Math.AbsFloat( GetND().GetRP().GetMinRecord() ) )
			{
				GetND().GetRP().AddRecords( alp_Player , savedReputation );
			}
		
		}
		
	}
			
	
	protected bool HasLifeInsurance()
	{
		
		if (  GetND().GetRP().GetPerksOptions().SecureReachedSkill  )
		{
			return true;
		}
			
		
		array<EntityAI> itemsArray = new array<EntityAI>;
		ItemBase item;
		alp_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			if (Class.CastTo(item, itemsArray.Get(i)))
			{
		
				if (item.GetType() == "alp_LifeInsuranceExclusive" ) 
				{
					alp_LifeInsuranceExclusive card;
					if ( Class.CastTo(card,item) )
					{
						if ( card.IsLifeInsuranceValid() ) 
							return true;
					}
					
				}
				
			}
		}								
		return false;
	}	
	
	protected void SecureStats(bool withoutLI = false)
	{
		GetStore().Event =  GetStore().Event | ALP_SPAWN_EVENT.RESTORE_STATS;

		int level;
		float exp,exp2;
				
		//stamina		
		level = GetPlayer().GetStatPerkStamina().Get();
		exp = GetPlayer().GetRP().GetTotalStaminaExp();
		if ( !withoutLI && GetND().GetRP().GetPerkStamina().PenalizedStaminaSkillAfterDeath[1] < 1 && level  >=  GetND().GetRP().GetPerkStamina().PenalizedStaminaSkillAfterDeath[0])
		{
			exp *= GetND().GetRP().GetPerkStamina().PenalizedStaminaSkillAfterDeath[1];
		}
		if ( withoutLI )
		{
			exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		}
		
		GetStore().PerkStaminaEXP = exp;
		
		//dayz skills
		exp =  GetPlayer().GetStatPerkSoft().Get(); 
		exp2 =  GetPlayer().GetStatPerkRough().Get(); 
		if ( withoutLI )
		{
			exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
			exp2 *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		}	
		else
		{
			exp *= GetND().GetRP().GetPerksDayz().PenalizedSkillAfterDeath;
			exp2 *= GetND().GetRP().GetPerksDayz().PenalizedSkillAfterDeath;	
		}	
		GetStore().PerkSoftEXP = exp;		
		GetStore().PerkRoughEXP = exp2;	
		
		//resistance cold
#ifdef NAMALSK_SURVIVAL			
		exp = alp_Player.GetStatColdResistance().Get();
		if ( withoutLI )
		{
			exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		}	
		else
		{
			exp *= GetND().GetRP().GetPerkColdResistance().PenalizedSkillAfterDeath;
		}	
		GetStore().PerkResistanceColdEXP = exp;						
#endif 		
		
		//reputation
		level = GetPlayer().GetStatPerkReputation().Get();
		exp = alp_TEMP_reputationEXP;
		if ( !withoutLI && GetND().GetRP().GetPerkReputation().PenalizedReputationSkillAfterDeath[1] < 1 && level  >=  GetND().GetRP().GetPerkReputation().PenalizedReputationSkillAfterDeath[0])
		{
			exp *= GetND().GetRP().GetPerkReputation().PenalizedReputationSkillAfterDeath[1];
		}
		if ( withoutLI )
		{
			exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		}	
		GetStore().PerkReputationEXP = exp;	
		//GetStore().LastScore = exp;
		
		//hunting
		level = GetPlayer().GetStatPerkHunting().Get();
		exp = GetPlayer().GetRP().GetTotalHuntingExp();
		if ( !withoutLI && GetND().GetRP().GetPerkHunting().PenalizedHuntingSkillAfterDeath[1] < 1 && level  >=  GetND().GetRP().GetPerkHunting().PenalizedHuntingSkillAfterDeath[0])
		{
			exp *= GetND().GetRP().GetPerkHunting().PenalizedHuntingSkillAfterDeath[1];
		}
		if ( withoutLI )
		{
			exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		}
		
		GetStore().PerkHuntingEXP = exp;	
		
		//RadiationResistance
		level = GetPlayer().GetStatPerkRadiationResistance().Get();
		exp = GetPlayer().GetRP().GetTotalRadiationResistanceExp();
		if ( !withoutLI && GetND().GetRP().GetPerkRadiationResistance().PenalizedResistanceSkillAfterDeath[1] < 1 && level  >=  GetND().GetRP().GetPerkRadiationResistance().PenalizedResistanceSkillAfterDeath[0])
		{
			exp *= GetND().GetRP().GetPerkRadiationResistance().PenalizedResistanceSkillAfterDeath[1];
		}
		if ( withoutLI )
		{
			exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		}
		
		GetStore().PerkRadiationResistanceEXP = exp;	
		
		//ToxicResistance
		level = GetPlayer().GetStatPerkToxicResistance().Get();
		exp = GetPlayer().GetRP().GetTotalToxicResistanceExp();
		if ( !withoutLI && GetND().GetRP().GetPerkToxicResistance().PenalizedResistanceSkillAfterDeath[1] < 1 && level  >=  GetND().GetRP().GetPerkToxicResistance().PenalizedResistanceSkillAfterDeath[0])
		{
			exp *= GetND().GetRP().GetPerkToxicResistance().PenalizedResistanceSkillAfterDeath[1];
		}
		if ( withoutLI )
		{
			exp *= GetND().GetRP().GetPerksOptions().SecureStatsWithoutLI;
		}
		
		GetStore().PerkToxicResistanceEXP = exp;					
	}	
	
	
	protected void RestoreStats()
	{
		GetStore().Event = ~ALP_SPAWN_EVENT.RESTORE_STATS & GetStore().Event;
		
		int level;
		float exp,exp2;
		
		//stamina
		exp = GetStore().PerkStaminaEXP;
		level = GetPlayer().GetRP().GetStaminaLevelByEXP(exp);
		
		GetPlayer().GetStatPerkStamina().Set( level );
		GetPlayer().GetStatPerkStaminaProgress().Set( exp );
		
		//dayz
		exp = GetStore().PerkSoftEXP;
		exp2 = GetStore().PerkRoughEXP;
		GetPlayer().GetStatPerkSoft().Set( exp );
		GetPlayer().GetStatPerkRough().Set(exp2); 
		
		//namalsk
#ifdef NAMALSK_SURVIVAL			
		exp = GetStore().PerkResistanceColdEXP;
		alp_Player.UpdateColdResistance( exp );
						
#endif 			
		//reputation
		exp = GetStore().PerkReputationEXP;
		int role;
		if (exp < 0 )
		{
			role = -1;
		}		
		else
		{
			role = 1;	
		}
		exp = Math.AbsFloat(exp);		
		level = GetPlayer().GetRP().GetReputationLevelByEXP(exp);		
		GetPlayer().GetStatPerkReputation().Set( level * role );
		GetPlayer().GetStatPerkReputationProgress().Set( exp * role );		
		
		//Hunting
		exp = GetStore().PerkHuntingEXP;
		level = GetPlayer().GetRP().GetHuntingLevelByEXP(exp);
		
		GetPlayer().GetStatPerkHunting().Set( level );
		GetPlayer().GetStatPerkHuntingProgress().Set( exp );		
		
		//RadiationResistance
		exp = GetStore().PerkRadiationResistanceEXP;
		level = GetPlayer().GetRP().GetRadiationResistanceLevelByEXP(exp);
		
		GetPlayer().GetStatPerkRadiationResistance().Set( level );
		GetPlayer().GetStatPerkRadiationResistanceProgress().Set( exp );	
		
		//ToxicResistance
		exp = GetStore().PerkToxicResistanceEXP;
		level = GetPlayer().GetRP().GetToxicResistanceLevelByEXP(exp);
		
		GetPlayer().GetStatPerkToxicResistance().Set( level );
		GetPlayer().GetStatPerkToxicResistanceProgress().Set( exp );				
	}	
	
	void SaveDNA()
	{
		//stamina
		float exp     = alp_Player.GetRP().GetTotalStaminaExp(); 
		GetStore().SavedDNA.StaminaEXP = exp;
		
		//GetStore().SavedDNA.StaminaLevel = alp_Player.GetStatPerkStamina().Get();
		//GetStore().SavedDNA.StaminaProgress = alp_Player.GetStatPerkStaminaProgress().Get();
		
		//dayz skills
		float soft    = alp_Player.GetStatPerkSoft().Get();
		GetStore().SavedDNA.SpecialtySoftEXP 	= soft;	
		float hard   	= alp_Player.GetStatPerkRough().Get();
		GetStore().SavedDNA.SpecialtyRoughEXP 	= hard;
		//namalsk
#ifdef NAMALSK_SURVIVAL			
		float coldEXP    = alp_Player.GetStatColdResistance().Get();		
		GetStore().SavedDNA.ResistanceColdEXP = coldEXP;		
#endif	
		//hunting
		float huntEXP     = alp_Player.GetRP().GetTotalHuntingExp();
		GetStore().SavedDNA.HuntingEXP = huntEXP;		
		
		//GetStore().SavedDNA.HuntingLevel = alp_Player.GetStatPerkHunting().Get();
		//GetStore().SavedDNA.HuntingProgress = alp_Player.GetStatPerkHuntingProgress().Get();		
		
		//rad resist
		float resEXP     =  alp_Player.GetRP().GetTotalRadiationResistanceExp();		
		GetStore().SavedDNA.ResistanceEXP = resEXP;		
		
		//GetStore().SavedDNA.ResistanceLevel = alp_Player.GetStatPerkRadiationResistance().Get();
		//GetStore().SavedDNA.ResistanceProgress = alp_Player.GetStatPerkRadiationResistanceProgress().Get();		
		
		//toxic resist
		
		float toxicEXP     =  alp_Player.GetRP().GetTotalToxicResistanceExp();		
		GetStore().SavedDNA.ResistanceToxicEXP = toxicEXP;		
		
		//GetStore().SavedDNA.ToxicResistanceLevel = alp_Player.GetStatPerkToxicResistance().Get();
		//GetStore().SavedDNA.ToxicResistanceProgress = alp_Player.GetStatPerkToxicResistanceProgress().Get();				
		
		
		
		//reputation
		if ( !GetND().GetRP().GetPerksOptions().ExcludeReputationFromCloning ){
			float reputationEXP     = alp_Player.GetRP().GetTotalReputationExp(); ;	
			GetStore().SavedDNA.ReputationEXP = reputationEXP;			
		}

		
		//GetStore().SavedDNA.ReputationLevel = alp_Player.GetStatPerkReputation().Get();
		//GetStore().SavedDNA.ReputationProgress = alp_Player.GetStatPerkReputationProgress().Get();			
		
		
		Save();
	}	
	
	void LoadDNA()
	{
		//stamina
		float staminaEXP   = GetStore().SavedDNA.StaminaEXP;
		int stamina		= alp_Player.GetRP().GetStaminaLevelByEXP( staminaEXP );
		
		alp_Player.GetStatPerkStamina().Set( stamina );
		alp_Player.GetStatPerkStaminaProgress().Set( staminaEXP );	
		
		//dayz Perks
		float soft    = GetStore().SavedDNA.SpecialtySoftEXP;
		
		float rough   = GetStore().SavedDNA.SpecialtyRoughEXP;
		
		alp_Player.GetStatPerkSoft().Set( soft );
		
		alp_Player.GetStatPerkRough().Set( rough );
		
		if ( alp_Player.GetSoftSkillsManager() )
		{
			alp_Player.GetSoftSkillsManager().InitSpecialty( alp_Player.GetStatSpecialty().Get() );	
		}
		
		//namalsk
#ifdef NAMALSK_SURVIVAL			
		float coldEXP   = GetStore().SavedDNA.ResistanceColdEXP;
		alp_Player.GetStatColdResistance().Set( coldEXP );
		alp_Player.UpdateColdResistance( 0 );
#endif	
		//hunting
		float huntEXP   = GetStore().SavedDNA.HuntingEXP;
		int hunting		= alp_Player.GetRP().GetHuntingLevelByEXP( huntEXP );
		
		alp_Player.GetStatPerkHunting().Set( hunting );
		alp_Player.GetStatPerkHuntingProgress().Set( huntEXP );	
		
		//rad resist
		float resEXP   = GetStore().SavedDNA.ResistanceEXP;
		int resistance	= alp_Player.GetRP().GetRadiationResistanceLevelByEXP( resEXP );
		
		alp_Player.GetStatPerkRadiationResistance().Set( resistance );
		alp_Player.GetStatPerkRadiationResistanceProgress().Set( resEXP );			
		
		
		//toxic resist
		
		float toxicEXP   = GetStore().SavedDNA.ResistanceToxicEXP;
		int toxic	= alp_Player.GetRP().GetToxicResistanceLevelByEXP( toxicEXP );
		
		alp_Player.GetStatPerkToxicResistance().Set( toxic );
		alp_Player.GetStatPerkToxicResistanceProgress().Set( toxicEXP );	
		
				
		//reputation
		if ( !GetND().GetRP().GetPerksOptions().ExcludeReputationFromCloning ){
			float reputationEXP   = GetStore().SavedDNA.ReputationEXP;
			
			int role;
			if (reputationEXP < 0 )
				role = -1;
			else
				role = 1;
			
			
			float repExp 		= 	Math.AbsFloat(reputationEXP);	
			int reputation		= alp_Player.GetRP().GetReputationLevelByEXP( repExp );
					
			alp_Player.GetStatPerkReputation().Set( reputation * role );
			alp_Player.GetStatPerkReputationProgress().Set( repExp * role );				
		}
		
					
	}	
	
}
