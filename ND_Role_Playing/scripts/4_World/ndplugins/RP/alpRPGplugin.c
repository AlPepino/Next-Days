

modded class alpPluginNDrp extends alpPlugin
{
	
	ref alpOptionsRP_PlayersPerks				alp_OptionsRP_PlayersPerks;
	ref alpPerkStamina							alp_OptionsRP_Perks_Stamina;
	ref alpPerkDayZ								alp_OptionsRP_Perks_Dayz;
	ref alpPerkResistanceCold					alp_OptionsRP_Perks_ResistanceCold;
	ref alpPerkReputation						alp_OptionsRP_Perks_Reputation;
	ref array<ref alpPlayerRecords> 			alp_PlayersRecords;			
	ref alpExpandedInteraction					alp_OptionsRP_Interactions;
	ref alpPerkHunting							alp_OptionsRP_Perks_Hunting;
	ref alpPerkRadResistance					alp_OptionsRP_Perks_RadResistance;	
	ref alpPerkToxicResistance 					alp_OptionsRP_Perks_ToxicResistance;	
	
	ref alpFatigueOptions 						alp_OptionsRP_Fatigue;	
	ref alpDiseasesOptions 						alp_OptionsRP_Diseases;	
	
	void ~alpPluginNDrp()
	{
		delete alp_OptionsRP_PlayersPerks;
		delete alp_OptionsRP_Perks_Stamina;
		delete alp_OptionsRP_Perks_Dayz;
		delete alp_OptionsRP_Perks_ResistanceCold;					
		delete alp_OptionsRP_Perks_Reputation;	
		delete alp_PlayersRecords;		
		delete alp_OptionsRP_Interactions;			
		delete alp_OptionsRP_Perks_Hunting;	
		delete alp_OptionsRP_Perks_RadResistance;	
		delete alp_OptionsRP_Perks_ToxicResistance;	
		delete alp_OptionsRP_Fatigue;	
		delete alp_OptionsRP_Diseases;		
	}

	
	override void Init() 
	{
		super.Init();
		
		
		alp_OptionsRP_PlayersPerks  		= new alpOptionsRP_PlayersPerks;
		alp_OptionsRP_Perks_Stamina 		= new alpPerkStamina;
		alp_OptionsRP_Perks_Dayz  			= new alpPerkDayZ;
		alp_OptionsRP_Perks_ResistanceCold  = new alpPerkResistanceCold;
		alp_OptionsRP_Perks_Reputation 		= new alpPerkReputation;
		alp_PlayersRecords					= new array<ref alpPlayerRecords>;		
		alp_OptionsRP_Interactions			= new alpExpandedInteraction;
		alp_OptionsRP_Perks_Hunting			= new alpPerkHunting;
		alp_OptionsRP_Perks_RadResistance	= new alpPerkRadResistance;
		alp_OptionsRP_Perks_ToxicResistance	= new alpPerkToxicResistance;
		
		alp_OptionsRP_Fatigue				= new alpFatigueOptions;
		alp_OptionsRP_Diseases				= new alpDiseasesOptions;
		
		//load file
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() )
		{

			
			//PERKS
			if (!FileExist(ALP_RP_PLAYERSPERKS_FILE	) )
			{ 			
				JsonFileLoader< alpOptionsRP_PlayersPerks>.JsonSaveFile(ALP_RP_PLAYERSPERKS_FILE,  alp_OptionsRP_PlayersPerks);
			}
			else 
			{
				JsonFileLoader< alpOptionsRP_PlayersPerks>.JsonLoadFile(ALP_RP_PLAYERSPERKS_FILE, alp_OptionsRP_PlayersPerks );	
			}
				
			JsonFileLoader< alpOptionsRP_PlayersPerks>.JsonSaveFile(ALP_RP_PLAYERSPERKS_FILE,  alp_OptionsRP_PlayersPerks);			


			//Diseases
			if (!FileExist(ALP_RP_DISEASES_FILE	) )
			{ 			
				JsonFileLoader< alpDiseasesOptions>.JsonSaveFile(ALP_RP_DISEASES_FILE,  alp_OptionsRP_Diseases);
			}
			else 
			{
				JsonFileLoader< alpDiseasesOptions>.JsonLoadFile(ALP_RP_DISEASES_FILE, alp_OptionsRP_Diseases );	
			}
				
			JsonFileLoader< alpDiseasesOptions>.JsonSaveFile(ALP_RP_DISEASES_FILE,  alp_OptionsRP_Diseases);			
			
			//Fatigue
			if (!FileExist(ALP_RP_FATIGUE_FILE	) )
			{ 			
				JsonFileLoader< alpFatigueOptions>.JsonSaveFile(ALP_RP_FATIGUE_FILE,  alp_OptionsRP_Fatigue);
			}
			else 
			{
				JsonFileLoader< alpFatigueOptions>.JsonLoadFile(ALP_RP_FATIGUE_FILE, alp_OptionsRP_Fatigue );	
			}
				
			JsonFileLoader< alpFatigueOptions>.JsonSaveFile(ALP_RP_FATIGUE_FILE,  alp_OptionsRP_Fatigue);				
			
			//Toxic resistance
			if (!FileExist(ALP_RP_PERKTOXICRESIST_FILE	) )
			{ 			
				JsonFileLoader< alpPerkToxicResistance>.JsonSaveFile(ALP_RP_PERKTOXICRESIST_FILE,  alp_OptionsRP_Perks_ToxicResistance);
			}
			else 
			{
				JsonFileLoader< alpPerkToxicResistance>.JsonLoadFile(ALP_RP_PERKTOXICRESIST_FILE, alp_OptionsRP_Perks_ToxicResistance );	
			}
				
			JsonFileLoader< alpPerkToxicResistance>.JsonSaveFile(ALP_RP_PERKTOXICRESIST_FILE,  alp_OptionsRP_Perks_ToxicResistance);			
			
			//Radiation resistance
			if (!FileExist(ALP_RP_PERKRADRESIST_FILE	) )
			{ 			
				JsonFileLoader< alpPerkRadResistance>.JsonSaveFile(ALP_RP_PERKRADRESIST_FILE,  alp_OptionsRP_Perks_RadResistance);
			}
			else 
			{
				JsonFileLoader< alpPerkRadResistance>.JsonLoadFile(ALP_RP_PERKRADRESIST_FILE, alp_OptionsRP_Perks_RadResistance );	
			}
				
			JsonFileLoader< alpPerkRadResistance>.JsonSaveFile(ALP_RP_PERKRADRESIST_FILE,  alp_OptionsRP_Perks_RadResistance);								
				
			
			//HUNTING
			if (!FileExist(ALP_RP_PERKHUNTING_FILE	) )
			{ 			
				JsonFileLoader< alpPerkHunting>.JsonSaveFile(ALP_RP_PERKHUNTING_FILE,  alp_OptionsRP_Perks_Hunting);
			}
			else 
			{
				JsonFileLoader< alpPerkHunting>.JsonLoadFile(ALP_RP_PERKHUNTING_FILE, alp_OptionsRP_Perks_Hunting );	
			}
				
			JsonFileLoader< alpPerkHunting>.JsonSaveFile(ALP_RP_PERKHUNTING_FILE,  alp_OptionsRP_Perks_Hunting);			
			
			//STAMINA
			if (!FileExist(ALP_RP_PERKSTAMINA_FILE	) )
			{ 			
				JsonFileLoader< alpPerkStamina>.JsonSaveFile(ALP_RP_PERKSTAMINA_FILE,  alp_OptionsRP_Perks_Stamina);
			}
			else 
			{
				JsonFileLoader< alpPerkStamina>.JsonLoadFile(ALP_RP_PERKSTAMINA_FILE, alp_OptionsRP_Perks_Stamina );	
			}
				
			JsonFileLoader< alpPerkStamina>.JsonSaveFile(ALP_RP_PERKSTAMINA_FILE,  alp_OptionsRP_Perks_Stamina);													
			
			//DAYZ SKILL
			if (!FileExist(ALP_RP_PERKSDAYZ_FILE	) )
			{ 			
				JsonFileLoader< alpPerkDayZ>.JsonSaveFile(ALP_RP_PERKSDAYZ_FILE,  alp_OptionsRP_Perks_Dayz);
			}
			else 
			{
				JsonFileLoader< alpPerkDayZ>.JsonLoadFile(ALP_RP_PERKSDAYZ_FILE, alp_OptionsRP_Perks_Dayz );	
			}
				
			JsonFileLoader< alpPerkDayZ>.JsonSaveFile(ALP_RP_PERKSDAYZ_FILE,  alp_OptionsRP_Perks_Dayz);					
			
#ifdef NAMALSK_SURVIVAL		
			//ResistanceCold
			if (!FileExist(ALP_RP_PERKCOLDRESIST_FILE	) )
			{ 			
				JsonFileLoader< alpPerkResistanceCold>.JsonSaveFile(ALP_RP_PERKCOLDRESIST_FILE,  alp_OptionsRP_Perks_ResistanceCold);
			}
			else 
			{
				JsonFileLoader< alpPerkResistanceCold>.JsonLoadFile(ALP_RP_PERKCOLDRESIST_FILE, alp_OptionsRP_Perks_ResistanceCold );	
			}
				
			JsonFileLoader< alpPerkResistanceCold>.JsonSaveFile(ALP_RP_PERKCOLDRESIST_FILE,  alp_OptionsRP_Perks_ResistanceCold);		
#endif 			
			
			//Reputation
			if (!FileExist(ALP_RP_PERKREPUTATION_FILE	) )
			{ 			
				JsonFileLoader< alpPerkReputation>.JsonSaveFile(ALP_RP_PERKREPUTATION_FILE,  alp_OptionsRP_Perks_Reputation);
			}
			else 
			{
				JsonFileLoader< alpPerkReputation>.JsonLoadFile(ALP_RP_PERKREPUTATION_FILE, alp_OptionsRP_Perks_Reputation );	
			}
				
			JsonFileLoader< alpPerkReputation>.JsonSaveFile(ALP_RP_PERKREPUTATION_FILE,  alp_OptionsRP_Perks_Reputation);													
			
			
			//HoF  
			if (!FileExist(ALP_RP_PERKREPUTATIONHOF_FILE	) )
			{ 			
				JsonFileLoader< array<ref alpPlayerRecords>>.JsonSaveFile(ALP_RP_PERKREPUTATIONHOF_FILE,  alp_PlayersRecords);
			}
			else 
			{
				JsonFileLoader< array<ref alpPlayerRecords>>.JsonLoadFile(ALP_RP_PERKREPUTATIONHOF_FILE, alp_PlayersRecords );	
			}
				
			JsonFileLoader< array<ref alpPlayerRecords>>.JsonSaveFile(ALP_RP_PERKREPUTATIONHOF_FILE,  alp_PlayersRecords);							
			//refresh Players name
			UpdatePlayerNamesInRecords();				
			
			//interactions  ALP_RP_INTERACTIONS_FILE
			if (!FileExist(ALP_RP_INTERACTIONS_FILE	) )
			{ 			
				JsonFileLoader< alpExpandedInteraction>.JsonSaveFile(ALP_RP_INTERACTIONS_FILE,  alp_OptionsRP_Interactions);
			}
			else 
			{
				JsonFileLoader< alpExpandedInteraction>.JsonLoadFile(ALP_RP_INTERACTIONS_FILE, alp_OptionsRP_Interactions );	
			}
				
			JsonFileLoader< alpExpandedInteraction>.JsonSaveFile(ALP_RP_INTERACTIONS_FILE,  alp_OptionsRP_Interactions);			
		}	
		
		
	}
	
	override void ReadSyncRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{
		int rpc;

		ctx.Read( rpc );
		
		switch ( rpc )
		{
			case ALP_RPC_PLUGIN_RP.RECORDS:
			{//client
				ctx.Read( alp_PlayersRecords );
				break;
			}	
			case ALP_RPC_PLUGIN_RP.GAINED_EXP:
			{//client
				int typeExp;
				int exp;
				ctx.Read( typeExp );
				ctx.Read( exp );
				ShowExpNotification( typeExp, exp);								
				break;
			}											
		}
				
	}			
	
	override void WriteOnConnectRPC(ref ScriptRPC rpc)
	{
		super.WriteOnConnectRPC( rpc );
		rpc.Write( alp_OptionsRP_PlayersPerks );
		rpc.Write( alp_OptionsRP_Perks_Stamina );
		rpc.Write( alp_OptionsRP_Perks_Reputation );
		//rpc.Write( alp_PlayersRecords );
		rpc.Write( alp_OptionsRP_Interactions );
		rpc.Write( alp_OptionsRP_Perks_Hunting );
		rpc.Write( alp_OptionsRP_Perks_RadResistance );
		rpc.Write( alp_OptionsRP_Perks_ToxicResistance );
		rpc.Write( alp_OptionsRP_Fatigue );
		rpc.Write( alp_OptionsRP_Diseases );
	}	
	
	override void ReadInitRPC( PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		super.ReadInitRPC(  sender,  target,  ctx);
		
		ctx.Read( alp_OptionsRP_PlayersPerks );		
		ctx.Read( alp_OptionsRP_Perks_Stamina );	
		ctx.Read( alp_OptionsRP_Perks_Reputation );
		//ctx.Read( alp_PlayersRecords );
		ctx.Read( alp_OptionsRP_Interactions );
		ctx.Read( alp_OptionsRP_Perks_Hunting );
		ctx.Read( alp_OptionsRP_Perks_RadResistance );
		ctx.Read( alp_OptionsRP_Perks_ToxicResistance );
		ctx.Read( alp_OptionsRP_Fatigue );
		ctx.Read( alp_OptionsRP_Diseases );
	}		

	override void OnSpawnManaged( PlayerBase player )
	{
		super.OnSpawnManaged(player);
		
		SendRPC_HoF(player);	
	}		
	
	void SendRPC_HoF(PlayerBase player)
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		rpc.Write( ALP_RPC_PLUGIN_RP.RECORDS );
		rpc.Write( alp_PlayersRecords );	
		
		GetND().SendGameRPC( rpc, player );	
	}	

	void SendRPC_GainedExp(PlayerBase player, int exp, int type = 0)
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		rpc.Write( ALP_RPC_PLUGIN_RP.GAINED_EXP );
		rpc.Write( type );	
		rpc.Write( exp );
		
		GetND().SendGameRPC( rpc, player );	
	}	
	
	void ShowExpNotification( int type, int exp )
	{

		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		
		if ( player )
		{
			int notfType = ALPMSTYPE.SMGAINEDEXPUP;
			int reputation = 0;
			reputation = Math.AbsInt( player.GetSyncData().GetElement( alpRPelements.REPUTATION).GetValue() );
			
			int expAbs = Math.AbsInt( exp );
			string message;			
			
			if ( reputation )
			{
			
				if ( player.GetRP().IsHero()  )
				{
					if ( exp < 0 )
					{//-
						notfType = ALPMSTYPE.SMGAINEDEXPDOWN;
					}		
				}
				else
				{
					if ( exp > 0 )
					{//-
						//ALPMSTYPE.SMPERSONAL
						notfType = ALPMSTYPE.SMGAINEDEXPDOWN;
					}		
				
				}			
			}

			
			message =  alpUF.NumberToString( expAbs, 1 ) + " EXP";
			
			GetND().GetNotf().GetHud().SendMessageALP( notfType, message );
		}		
		
		


	
		
	}
	
	array<ref alpPlayerRecords>	GetHoFdata()
	{
		return alp_PlayersRecords;
	}	
	
	float GetMinRecord()
	{
		float score = 0;
		int index = alp_PlayersRecords.Count() ;
		
		
		
		if ( index < GetND().GetRP().GetPerkReputation().MaxCountRecords )
			return score;
		
		if (index > 0 )
		{
			score = alp_PlayersRecords.Get(index - 1).Reputation;
		}	
		return score;
	}	
	
	void UpdatePlayerNamesInRecords()
	{
		bool change = false;
	
		for (int i = 0; i < alp_PlayersRecords.Count(); i++)
		{
			alpPlayerRecords record = alp_PlayersRecords.Get(i);
			string name = GetCurrentName( record.GUID );
			if ( name != STRING_EMPTY && name != record.Name )
			{
				change = true;
				record.Name = name;
			}
		}
		
		if ( change )
		{
			JsonFileLoader< array<ref alpPlayerRecords>>.JsonSaveFile(ALP_RP_PERKREPUTATIONHOF_FILE,  alp_PlayersRecords);
		}
	}	

	string GetCurrentName(string guid)
	{
		string name = STRING_EMPTY;
		
		alpStoreValues storevalues;
		JsonFileLoader<ref alpStoreValues>.JsonLoadFile( ALP_RP_FOLDER + guid + ".json", storevalues );
				
		if (storevalues)
		{
			name = storevalues.Name;
		}		
		
		return name;
	}		
	void AddRecords(PlayerBase player, float reputation )
	{
		alpPlayerRecords records = new alpPlayerRecords();
		
		if ( player.GetIdentity() )
		{

			records.GUID 			= player.GetIdentity().GetPlainId();
			records.Name 			= player.GetIdentity().GetName();
			records.Reputation 		= reputation;
			records.KilledPlayers 	= player.GetStatCountPlayers().Get();
			records.SkinnedPlayers 	= player.GetStatCountSkinned().Get();
			records.KilledZombies 	= player.GetStatCountZombies().Get();
			records.KilledAnimals 	= player.GetStatCountAnimals().Get();		
			

			if (alp_PlayersRecords.Count() > GetND().GetRP().GetPerkReputation().MaxCountRecords )
			{
				for (int x = GetND().GetRP().GetPerkReputation().MaxCountRecords; x < alp_PlayersRecords.Count();) 
				{
					alp_PlayersRecords.Remove(x);				
					continue;
				}
			}		
		

			if ( alp_PlayersRecords.Count() == 0) 
			{
				alp_PlayersRecords.Insert(records);
			}
			else 
			{
				int count = alp_PlayersRecords.Count();

				bool saved = false;
				for (int i = 0; i < count;i++)
				{
					alpPlayerRecords r = alp_PlayersRecords.Get(i);
					
					if (Math.AbsFloat(records.Reputation) > Math.AbsFloat(r.Reputation))
					{
						alp_PlayersRecords.InsertAt(records, i);
						saved = true;
						break;
					}
				}	
				if ( !saved && count < 	GetND().GetRP().GetPerkReputation().MaxCountRecords )
				{
					alp_PlayersRecords.Insert(records);
				}
			}


			JsonFileLoader< array<ref alpPlayerRecords>>.JsonSaveFile(ALP_RP_PERKREPUTATIONHOF_FILE,  alp_PlayersRecords);
		}
	}		
	
	alpOptionsRP_PlayersPerks GetPerksOptions()
	{
		return alp_OptionsRP_PlayersPerks;
	}	

	alpDiseasesOptions GetDiseases()
	{
		return alp_OptionsRP_Diseases;
	}
		
	alpFatigueOptions GetFatigue()
	{
		return alp_OptionsRP_Fatigue;
	}	
		
	alpPerkStamina GetPerkStamina()
	{
		return alp_OptionsRP_Perks_Stamina;
	}	
	alpPerkResistanceCold GetPerkColdResistance()
	{
		return alp_OptionsRP_Perks_ResistanceCold;
	}		
	
	alpPerkDayZ GetPerksDayz()
	{
		return alp_OptionsRP_Perks_Dayz;
	}	
	alpPerkReputation GetPerkReputation()
	{
		return alp_OptionsRP_Perks_Reputation;
	}	
	

	alpPerkHunting GetPerkHunting()
	{
		return alp_OptionsRP_Perks_Hunting;
	}	
			
	alpPerkRadResistance GetPerkRadiationResistance()
	{
		return alp_OptionsRP_Perks_RadResistance;
	}	

	alpPerkToxicResistance GetPerkToxicResistance()
	{
		return alp_OptionsRP_Perks_ToxicResistance;
	}		
	alpExpandedInteraction GetInteractions()
	{
		return alp_OptionsRP_Interactions;
	}	
		
	int GetPerkStaminaLevelCup()
	{	
		return  GetPerkStamina().LevelMdf.Count() - 1;
	}		
	
	float GetPerkStaminaMdf(int level)
	{
		float mdf; 
		int cap = GetPerkStaminaLevelCup();
		
		if (level >  cap ) 
			mdf = GetPerkStamina().LevelMdf.Get( cap );
		else 
			mdf = GetPerkStamina().LevelMdf.Get(level);
		
		return mdf;					
	}	
	
	int GetPerkReputationLevelCup()
	{	
		return  GetPerkReputation().LevelMdf.Count() - 1;
	}			
	
	float GetReputationMdf(int id)
	{
		float mdf; 
		int levelCup = GetPerkReputationLevelCup();
		if (id >  levelCup ) 
			mdf = GetPerkReputation().LevelMdf.Get( levelCup );
		else 
			mdf = GetPerkReputation().LevelMdf.Get(id);
		return mdf;					
	}	
	float GetReputationBonusKillPlayer()
	{
		return GetPerkReputation().KillPlayerBonus;	
	}
	float GetReputationBonusSell( int role )
	{
		return GetPerkReputation().Sell[role];	
	}	
	float GetReputationBonusBuy( int role )
	{
		return GetPerkReputation().Buy[role];	
	}		
	float GetReputationBonusKillHero( int role )
	{
		return GetPerkReputation().KillHero[role];	
	}	
	float GetReputationBonusKillBandit( int role )
	{
		return GetPerkReputation().KillBandit[role];	
	}	
	float GetReputationBonusSkinPlayer( int role )
	{
		return GetPerkReputation().SkinPlayer[role];	
	}
	float GetReputationBonusKillZombie( int role )
	{
		return GetPerkReputation().KillZombie[role];	
	}
	float GetReputationBonusKillAnimal( int role )
	{
		return GetPerkReputation().KillAnimal[role];	
	}
	float GetReputationBonusKillWolf( int role )
	{
		return GetPerkReputation().KillWolf[role];	
	}
	float GetReputationBonusKillBear( int role )
	{
		return GetPerkReputation().KillBear[role];	
	}				
	float GetReputationBonusLockPicking( int role )
	{
		return GetPerkReputation().LockPicking[role];	
	}		
	float GetReputationBonusTreatOthers( int role )
	{
		return GetPerkReputation().TreatOthers[role];	
	}	
	float GetReputationBonusDestroyCombLock( int role )
	{
		return GetPerkReputation().DestroyCombLock[role];	
	}		
	float GetReputationBonusDestroyPart( int role )
	{
		return GetPerkReputation().DestroyPart[role];	
	}		
	float GetReputationBonusDigInRadioactiveBarrel( int role )
	{
		return GetPerkReputation().DigInRadioactiveBarrel[role];	
	}		
	
		
	int GetPerkHuntingLevelCup()
	{	
		return  GetPerkHunting().LevelMdf.Count() - 1;
	}		
	
	float GetPerkHuntingMdf(int level)
	{
		float mdf; 
		int cap = GetPerkHuntingLevelCup();
		
		if (level >  cap ) 
			mdf = GetPerkHunting().LevelMdf.Get( cap );
		else 
			mdf = GetPerkHunting().LevelMdf.Get(level);
		
		return mdf;					
	}		
	float GetPerkHuntingDamageMdf(int level)
	{
		float mdf; 
		int cap = GetPerkHuntingLevelCup();
		
		if (level >  cap ) 
			mdf = GetPerkHunting().DamageLevelMdf.Get( cap );
		else 
			mdf = GetPerkHunting().DamageLevelMdf.Get(level);
		
		return mdf;					
	}		
	
	
	int GetPerkRadiationResistanceLevelCup()
	{	
		return  GetPerkRadiationResistance().LevelMdf.Count() - 1;
	}		
	
	float GetPerkRadiationResistanceMdf(int level)
	{
		float mdf; 
		int cap = GetPerkRadiationResistanceLevelCup();
		
		if (level >  cap ) 
			mdf = GetPerkRadiationResistance().LevelMdf.Get( cap );
		else 
			mdf = GetPerkRadiationResistance().LevelMdf.Get(level);
		
		return mdf;					
	}		
	
	int GetPerkToxicResistanceLevelCup()
	{	
		return  GetPerkToxicResistance().LevelMdf.Count() - 1;
	}		
	
	float GetPerkToxicResistanceMdf(int level)
	{
		float mdf; 
		int cap = GetPerkToxicResistanceLevelCup();
		
		if (level >  cap ) 
			mdf = GetPerkToxicResistance().LevelMdf.Get( cap );
		else 
			mdf = GetPerkToxicResistance().LevelMdf.Get(level);
		
		return mdf;					
	}	
}
