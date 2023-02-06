enum alpDiseases
{
	DECONTAMINATION = -2,//non-sync
	BLEEDING = -1, //non-sync
	NONE = 0,
	BRAINDISEASE = 1,
	COMMONCOLD = 2,
	CHOLERA = 4,
	INFLUENZA = 8,
	SALMONELLA = 16,
	WOUNDINFECTION_1 = 32,
	WOUNDINFECTION_2 = 64,
	POISONING = 128,
	FEVER = 256,
	BROKEN_ARMS = 512,	
	BROKEN_LEGS = 1024,	
	RADIATION = 2048,	
	FROSTBITE = 4096,
	POISONING_CHEMICAL_1 = 8192,
	POISONING_CHEMICAL_2 = 16384,
	POISONING_CHEMICAL_3 = 32768,
	DRUNKENNESS = 65536,
}


modded class alpRP
{
	//fatigue
	int						alp_FatigueStatus			= 0;	
	
	//diseases
	protected int alp_Diseases;	
	
	ref map<int, ref alpDisease> alp_MedicList;
	
	
	bool alp_WasDecontamined;
	
	override void Init()
	{
		super.Init();
				
		CreateDiseasesList();
		
		if ( GetGame().IsClient() )
		{
			alp_WasDecontamined = false;
		}
	}
	
	
	void SetDecontaminationEvent( bool state )
	{
		alp_WasDecontamined = state;
	}
	
	bool WasDecontamined()
	{
		return alp_WasDecontamined;
	}
	
	
	
	void CreateDiseasesList()
	{
		alp_MedicList = new map<int, ref alpDisease>;
		
		alp_MedicList.Set(alpDiseases.DECONTAMINATION,new alpDecontaminationDisease(alp_Player,alpDiseases.DECONTAMINATION,"#action_decontamination",true,true,"set:ccgui_enforce image:Icon40WalrusUpgradeMarshes"));
		
		alp_MedicList.Set(alpDiseases.BLEEDING,new alpBleedingDisease(alp_Player,alpDiseases.BLEEDING,"#me_bleeding_desc",true,true,"set:dayz_gui image:iconBleeding"));
		
		alp_MedicList.Set(alpDiseases.BRAINDISEASE,new alpBrainDisease(alp_Player,alpDiseases.BRAINDISEASE,"#me_braindisease_desc",true,true,"set:dayz_gui image:iconBacteria"));
		alp_MedicList.Set(alpDiseases.COMMONCOLD,new alpCommonCold(alp_Player,alpDiseases.COMMONCOLD,"#me_commoncold_desc",true,true,"set:dayz_gui image:iconTemperature4"));
		alp_MedicList.Set(alpDiseases.CHOLERA,new alpCholera(alp_Player,alpDiseases.CHOLERA,"#me_cholera_desc",true,true,"set:dayz_gui image:iconBacteria"));
		alp_MedicList.Set(alpDiseases.INFLUENZA,new alpInfluenza(alp_Player,alpDiseases.INFLUENZA,"#me_influenza_desc",true,true,"set:dayz_gui image:iconBacteria"));
		alp_MedicList.Set(alpDiseases.SALMONELLA,new alpSalmonella(alp_Player,alpDiseases.SALMONELLA,"#me_salmonella_desc",true,true,"set:dayz_gui image:iconBacteria"));
		alp_MedicList.Set(alpDiseases.WOUNDINFECTION_1,new alpWoundInfection1(alp_Player,alpDiseases.WOUNDINFECTION_1,"#me_woundinfection_desc",true,true,"set:dayz_gui image:iconBacteria"));
		alp_MedicList.Set(alpDiseases.WOUNDINFECTION_2,new alpWoundInfection2(alp_Player,alpDiseases.WOUNDINFECTION_2,"#me_woundinfection_desc",true,true,"set:dayz_gui image:iconBacteria"));
		alp_MedicList.Set(alpDiseases.POISONING,new alpPoisoning(alp_Player,alpDiseases.POISONING,"#me_poisoning_desc",true,true,"set:dayz_gui image:iconPoisoned"));
		
		alp_MedicList.Set(alpDiseases.FEVER,new alpFever(alp_Player,alpDiseases.FEVER,"#me_fever_desc",true,false,"set:dayz_gui image:iconBacteria"));
		
		alp_MedicList.Set(alpDiseases.DRUNKENNESS,new alpFever(alp_Player,alpDiseases.DRUNKENNESS,"#me_drunkenness_desc",true,false,"set:dayz_gui image:iconBacteria"));
		
		alp_MedicList.Set(alpDiseases.BROKEN_ARMS,new alpBrokenArms(alp_Player,alpDiseases.BROKEN_ARMS,"#me_brokenarms_desc",true,true,"set:dayz_gui image:iconBone"));
		alp_MedicList.Set(alpDiseases.BROKEN_LEGS,new alpBrokenLegs(alp_Player,alpDiseases.BROKEN_LEGS,"#me_brokenlegs_desc",true,true,"set:dayz_gui image:iconBone"));
		
		alp_MedicList.Set(alpDiseases.RADIATION,new alpRadiationDisease(alp_Player,alpDiseases.RADIATION,"#me_radiationdisease_desc",true,true,"set:nd_dayz_gui image:radiation"));
		
		
		alp_MedicList.Set(alpDiseases.POISONING_CHEMICAL_1,new alpPoisoningChemica1_1(alp_Player,alpDiseases.POISONING_CHEMICAL_1,"#me_poisoningchemical_desc",true,true,"set:dayz_gui image:iconSkull"));
		alp_MedicList.Set(alpDiseases.POISONING_CHEMICAL_2,new alpPoisoningChemica1_2(alp_Player,alpDiseases.POISONING_CHEMICAL_2,"#me_poisoningchemical_desc",true,true,"set:dayz_gui image:iconSkull"));
		alp_MedicList.Set(alpDiseases.POISONING_CHEMICAL_3,new alpPoisoningChemica1_3(alp_Player,alpDiseases.POISONING_CHEMICAL_3,"#me_poisoningchemical_desc",true,true,"set:dayz_gui image:iconSkull"));
		
#ifdef NAMALSK_SURVIVAL			
		alp_MedicList.Set(alpDiseases.FROSTBITE,new alpFrostbite(alp_Player,alpDiseases.FROSTBITE,"#me_frostbite_desc",true,true,"set:nam_gui_icons image:coldresistfull2"));		
#endif		
	}		
	
	//fatigue
	void SetFatigueStatus(int status)
	{
		alp_FatigueStatus = status;
	}
	
	int GetFatigueStatus()
	{
		return alp_FatigueStatus;
	}		
	
	override void ImproveToxicNaturalResistance(float exp)
	{
		if ( !GetND().GetRP().GetPerksOptions().EnablePerkToxicResistance )
			return;
				
		
		int currentLevel 		=  alp_Player.GetStatPerkToxicResistance().Get();
		int 	maxLevel		= GetND().GetRP().GetPerkToxicResistanceLevelCup();		
		
		if ( currentLevel < maxLevel )
		{
			
			float addProgress 	= alp_Player.GetStatPerkToxicResistanceProgress().Get() + exp;
			
			float nextLevel   	= GetToxicResistanceRequiredExp( alp_Player.GetStatPerkToxicResistance().Get() + 1 );							
			
							
			if ( addProgress >= nextLevel)
			{
				//get a new level
				addProgress -= nextLevel;
				currentLevel ++;	
				//message	
				GetND().GetNotf().SendMessage( alp_Player, ALPMSTYPE.SMLEVELUP, "#ip_you_have_gained_natural_toxic_resistance" );	
									
			}
			//synchronization				
			alp_Player.GetStatPerkToxicResistanceProgress().Set( addProgress );		
			alp_Player.GetStatPerkToxicResistance().Set( currentLevel );		
			
		}		
	}
		
	override void ImproveRadiationNaturalResistance(float exp)
	{
		if ( !GetND().GetRP().GetPerksOptions().EnablePerkRadiationResistance )
			return;
		
		
		int currentLevel 		=  alp_Player.GetStatPerkRadiationResistance().Get();
		int 	maxLevel		= GetND().GetRP().GetPerkRadiationResistanceLevelCup();
		
		
		if ( currentLevel < maxLevel )
		{
			float addProgress 	= alp_Player.GetStatPerkRadiationResistanceProgress().Get() + exp;
			float nextLevel   	= GetRadiationResistanceRequiredExp( alp_Player.GetStatPerkRadiationResistance().Get() + 1 );							
					
									
			if ( addProgress >= nextLevel)
			{
				//get a new level
				addProgress -= nextLevel;
				currentLevel ++;	
				//message	
				GetND().GetNotf().SendMessage( alp_Player, ALPMSTYPE.SMLEVELUP, "#ip_you_have_gained_natural_radiation_resistance" );			
											
			}
			//synchronization				
			alp_Player.GetStatPerkRadiationResistanceProgress().Set( addProgress );		
			alp_Player.GetStatPerkRadiationResistance().Set( currentLevel );		
					
		}		
	}	
		
	
	void ChangeHunting( float inc )
	{
		if ( GetND().GetRP().GetPerksOptions().EnablePerkHunting )
		{		
		
			int 	currentLevel 	= alp_Player.GetStatPerkHunting().Get();				


			int 	maxLevel		= GetND().GetRP().GetPerkHuntingLevelCup();
			
			
			//skills
			
			if ( currentLevel < maxLevel )
			{
				float exp 			= alp_Player.GetStatPerkHuntingProgress().Get() + inc;
				float nextLevel   	= GetHuntingRequiredExp( currentLevel + 1 );							
					
									
				if ( exp >= nextLevel)
				{
					//get a new level
					exp -= nextLevel;
					currentLevel ++;	
					//message	
					GetND().GetNotf().SendMessage( alp_Player, ALPMSTYPE.SMLEVELUP, "#ip_you_have_improved_your_hunting_skill" );	
											
				}
			
				alp_Player.GetStatPerkHuntingProgress().Set( exp );		
				alp_Player.GetStatPerkHunting().Set( currentLevel );		
					
			}	
		}			
	}
		
	
	override void ChangeReputation( float inc )
	{
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkReputation )
		{
			alp_Player.GetStatCurrentScore().Add( inc );//current session
			
			if ( GetND().GetRP().GetPerksOptions().EnableGainedReputationNotification )
			{
				int gainedExp = (float) inc;
				
				GetND().GetRP().SendRPC_GainedExp( GetPlayer(), gainedExp );
			}

			
			int 	level 			= alp_Player.GetStatPerkReputation().Get();				
			int		currentLevel	= level;
			float 	exp 			= alp_Player.GetStatPerkReputationProgress().Get();	
			int 	maxLevel		= GetND().GetRP().GetPerkReputationLevelCup();
			
			exp += inc;
			
			VerifyReputationLevel( exp, level, maxLevel);
			
			if ( Math.AbsInt(level) < Math.AbsInt(currentLevel) )
			{
				//degrade
				GetND().GetNotf().SendMessage( alp_Player, ALPMSTYPE.SMLEVELDOWN, "#ip_you_have_been_promoted_to" + " " +  "#ip_rank" + Math.AbsInt( level ));
			}
			if ( Math.AbsInt(level) > Math.AbsInt(currentLevel) )
			{
				//promote
				GetND().GetNotf().SendMessage( alp_Player, ALPMSTYPE.SMLEVELUP, "#ip_you_have_been_promoted_to" + " " + "#ip_rank" + Math.AbsInt( level ));
			}		
			
			//saving stats
			alp_Player.GetStatPerkReputation().Set(level);				
			alp_Player.GetStatPerkReputationProgress().Set( exp );		
		}
	}		
	
	
	private void VerifyReputationLevel(out float exp, out int level, int maxLevel)
	{
		float 	reqExp,min,max,check,currentExp;
		
		if ( Math.AbsInt(level) == maxLevel )
			reqExp = int.MAX - 1;
		else
			reqExp = GetReputationRequiredExp( Math.AbsInt(level) + 1 ); 				

		if ( level == 0 )
		{
			min = -1 * reqExp;
			max = reqExp;
		}
		if ( level < 0 )
		{
			min = -1 * reqExp;
			max = 0;
		}	
		if ( level > 0 )
		{
			min = 0;
			max = 1 * reqExp;
		}						
		
		check = Math.Clamp( exp, min, max );
		
		if ( exp > check )//promote
		{
			if ( check == 0 ) //degrade bandit
			{
				currentExp =  GetReputationRequiredExp( Math.AbsInt(level)  ); 		
				
				exp -= currentExp;
			}
			else
			{
				exp -= check;
			}
			
			level += 1;

			VerifyReputationLevel( exp, level, maxLevel);
			return;
		}
		if ( exp < check )//degrade
		{
			if ( check == 0 ) //degrade hero
			{
				currentExp =  GetReputationRequiredExp( Math.AbsInt(level)  ); 		
				
				exp += currentExp;
			}
			else
			{
				exp -= check;
			}
				
			level -= 1;

			VerifyReputationLevel( exp, level, maxLevel);
			return;
		}		
		
	}	
	
	
	
	int GetStaminaLevelByEXP(out float exp)
	{
		int level;
		int levelCap = GetND().GetRP().GetPerkStaminaLevelCup();
		for (level = 0; level < levelCap; )
		{
			float levelExp = GetStaminaRequiredExp(level + 1);
			
			if (exp >= levelExp)
			{
				level++;
				exp -= levelExp;			
			}
			else
				break;			
		}					
		return level;	
	}	
	
	float GetStaminaRequiredExp(int id)
	{
		int levelCup = GetND().GetRP().GetPerkStaminaLevelCup();
		if (id >   levelCup ) 
		{
			
			return 	GetND().GetRP().GetPerkStamina().RequiredExp.Get( levelCup );
		}
		else
		{
			return GetND().GetRP().GetPerkStamina().RequiredExp.Get(id);
		}
			
	}		
	
	float GetTotalStaminaExp()
	{
		float exp;
		for (int i = 0; i <= alp_Player.GetStatPerkStamina().Get(); i++)
		{
			exp += GetStaminaRequiredExp(i);
		}			
		exp += alp_Player.GetStatPerkStaminaProgress().Get();
		return exp;	
	}
	
	
	
	//reputation
	float GetTotalReputationExp()
	{
		float exp;
		int role 
		int level = alp_Player.GetStatPerkReputation().Get();
		
		if (level < 0)
			role = -1;
		else
			role = 1;
		
		for (int i = 0; i <= Math.AbsInt( level ); i++)
		{
			exp += GetReputationRequiredExp(i);
		}		
		exp *= role;	
		exp += alp_Player.GetStatPerkReputationProgress().Get();
		return exp;
	}	
	
	float GetReputationRequiredExp(int id)
	{
		int levelCup = GetND().GetRP().GetPerkReputationLevelCup();
		if (id >   levelCup ) 
		{
			
			return 	GetND().GetRP().GetPerkReputation().RequiredExp.Get( levelCup );
		}
		else
		{
			return GetND().GetRP().GetPerkReputation().RequiredExp.Get(id);
		}
			
	}	
	int GetReputationLevelByEXP(out float exp)
	{
		int level;
		int levelCap = GetND().GetRP().GetPerkReputationLevelCup();
		for (level = 0; level < levelCap; )
		{
			float levelExp = GetReputationRequiredExp(level + 1);
			
			if (exp >= levelExp)
			{
				level++;
				exp -= levelExp;			
			}
			else
				break;			
		}					
		return level;	
	}	
	
	int GetHuntingLevelByEXP(out float exp)
	{
		int level;
		int levelCap = GetND().GetRP().GetPerkHuntingLevelCup();
		for (level = 0; level < levelCap; )
		{
			float levelExp = GetHuntingRequiredExp(level + 1);
			
			if (exp >= levelExp)
			{
				level++;
				exp -= levelExp;			
			}
			else
				break;			
		}					
		return level;	
	}		
	float GetHuntingRequiredExp(int id)
	{
		int levelCup = GetND().GetRP().GetPerkHuntingLevelCup();
		if (id >   levelCup ) 
		{
			
			return 	GetND().GetRP().GetPerkHunting().RequiredExp.Get( levelCup );
		}
		else
		{
			return GetND().GetRP().GetPerkHunting().RequiredExp.Get(id);
		}
			
	}		
	
	float GetTotalHuntingExp()
	{
		float exp;
		for (int i = 0; i <= alp_Player.GetStatPerkHunting().Get(); i++)
		{
			exp += GetHuntingRequiredExp(i);
		}			
		exp += alp_Player.GetStatPerkHuntingProgress().Get();
		return exp;	
	}
	
	
	float GetRadiationResistanceRequiredExp(int id)
	{
		int levelCup = GetND().GetRP().GetPerkRadiationResistanceLevelCup();
		if (id >   levelCup ) 
		{
			
			return 	GetND().GetRP().GetPerkRadiationResistance().RequiredExp.Get( levelCup );
		}
		else
		{
			return GetND().GetRP().GetPerkRadiationResistance().RequiredExp.Get(id);
		}
			
	}		
	
	float GetTotalRadiationResistanceExp()
	{
		float exp;
		for (int i = 0; i <= alp_Player.GetStatPerkRadiationResistance().Get(); i++)
		{
			exp += GetRadiationResistanceRequiredExp(i);
		}			
		exp += alp_Player.GetStatPerkRadiationResistanceProgress().Get();
		return exp;	
	}	
	int GetRadiationResistanceLevelByEXP(out float exp)
	{
		int level;
		int levelCap = GetND().GetRP().GetPerkRadiationResistanceLevelCup();
		for (level = 0; level < levelCap; )
		{
			float levelExp = GetRadiationResistanceRequiredExp(level + 1);
			
			if (exp >= levelExp)
			{
				level++;
				exp -= levelExp;			
			}
			else
				break;			
		}					
		return level;	
	}	
	
	
	float GetToxicResistanceRequiredExp(int id)
	{
		int levelCup = GetND().GetRP().GetPerkToxicResistanceLevelCup();
		if (id >   levelCup ) 
		{
			
			return 	GetND().GetRP().GetPerkToxicResistance().RequiredExp.Get( levelCup );
		}
		else
		{
			return GetND().GetRP().GetPerkToxicResistance().RequiredExp.Get(id);
		}
			
	}		
	
	float GetTotalToxicResistanceExp()
	{
		float exp;
		for (int i = 0; i <= alp_Player.GetStatPerkToxicResistance().Get(); i++)
		{
			exp += GetToxicResistanceRequiredExp(i);
		}			
		exp += alp_Player.GetStatPerkToxicResistanceProgress().Get();
		return exp;	
	}	
	int GetToxicResistanceLevelByEXP(out float exp)
	{
		int level;
		int levelCap = GetND().GetRP().GetPerkToxicResistanceLevelCup();
		for (level = 0; level < levelCap; )
		{
			float levelExp = GetToxicResistanceRequiredExp(level + 1);
			
			if (exp >= levelExp)
			{
				level++;
				exp -= levelExp;			
			}
			else
				break;			
		}					
		return level;	
	}			
	bool IsHero()
	{	
		return !alp_Player.GetSyncData().GetElement( alpRPelements.REPUTATION_ROLE ).GetValue();	
	}	
	
	
	
	void SetDisease(int value)
	{
		alp_Diseases = alp_Diseases | value;
	}
	void UnsetDisease(int value)
	{
		
		alp_Diseases = alp_Diseases & (~value);
	}
	
	
	int GetDiseases()
	{
		if (GetGame().IsClient())
		{
			
			return GetPlayer().GetSyncData().GetElement(alpRPelements.DISEASES).GetValue();
		}
		else
		{
			return alp_Diseases;
		}		
	}
	
	bool IsInfected(int disease)
	{		
		return GetDiseases() & disease;
	}		
		
	
	bool HasAnyContaminedItems()	
	{
			
		if ( GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems )
		{	
			array<EntityAI> itemsArray = new array<EntityAI>;
			ItemBase item;		
			
			alp_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			
			for (int i = 0; i < itemsArray.Count(); i++)
			{				
				item = ItemBase.Cast(itemsArray.Get(i));	
				if ( item && ( item.GetAgents() & alpeAgents.RADIATION ) )
				{
					return true;
				}
			}
			return false;
		}
		else
		{
			return false;
		}

	}
	
	string alp_MedicalFeeCurrency;
	
	string GetMedicalFeeCurrenyName()
	{
		return alp_MedicalFeeCurrency;
	}
	
	int GetMedicalFee(int traderID , out int currencyID )
	{

		alpMedicalFees fees;
		alpNPCtraderStock trader = alpTraderCoreBase.alp_TraderStockMapped.Get(	traderID );
		
		float currencyRate,coef;
		
		//PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		int level = GetPlayer().GetSyncData().GetElement( alpRPelements.REPUTATION ).GetValue();
		float sale = 	GetND().GetRP().GetReputationMdf( level );		
		
		if ( trader )
		{
			currencyID = trader.CurrencyID;
			
			alp_MedicalFeeCurrency = alpTraderCoreBase.GetCurrencyName( trader.CurrencyID );	 
			
			currencyRate = alpBANK.GetCurrencyRate( trader.CurrencyID );	
			
			
			if ( IsHero() )
			{
				coef = trader.PricelistRatioHero;	
			}
			else
			{
				coef = trader.PricelistRatioBandit;	
			}
			
			fees = GetND().GetRP().GetInteractions().GetMedicalFees( currencyRate, coef, sale );
			
			if ( fees )
			{
				return fees.Fee;
			}
		}	
		return 0;		
	}
}


