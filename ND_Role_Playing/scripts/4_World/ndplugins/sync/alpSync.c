

modded class alpSync
{

	
	override void Init()
	{
		super.Init();
		//RegisteStats		
		RegisterElement( new alpStatsStamina( alp_Player ) );
		RegisterElementEnhanced( new alpStatsEnhancedStaminaProgress(alp_Player) );	
		
		RegisterElement( new alpStatsReputation( alp_Player ) );
		RegisterElement( new alpStatsReputationRole( alp_Player ) );			
		RegisterElementEnhanced( new alpStatsEnhancedReputationProgress(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedReputationScore(alp_Player) );	
		
		RegisterElement( new alpStatsHunting( alp_Player ) );
		RegisterElementEnhanced( new alpStatsEnhancedHuntingProgres(alp_Player) );			
		
		RegisterElement( new alpStatsRadResistance( alp_Player ) );
		RegisterElementEnhanced( new alpStatsEnhancedRadResitProgres(alp_Player) );			
				
		RegisterElement( new alpStatsToxicResistance( alp_Player ) );
		RegisterElementEnhanced( new alpStatsEnhancedToxicResistanceProgres(alp_Player) );				
		
		RegisterElement( new alpStatsTendencyTiredness( alp_Player ) );
		RegisterElementEnhanced( new alpStatsEnhancedFatigue(alp_Player) );		
				
		
		RegisterElement( new alpStatsDiseases( alp_Player ) );
		RegisterElementEnhanced( new alpStatsEnhancedTemperature(alp_Player) );
		RegisterElementEnhanced( new alpStatsEnhancedRadiationSickStage(alp_Player) );
		/*
		RegisterElementEnhanced( new alpStatsEnhancedTemperature(alp_Player) );
		RegisterElementEnhanced( new alpStatsEnhancedRadiationSickStage(alp_Player) );
		
		RegisterElementEnhanced( new alpStatsEnhancedStaminaSaved(alp_Player) );
		RegisterElementEnhanced( new alpStatsEnhancedStaminaProgressSaved(alp_Player) );
		
		RegisterElementEnhanced( new alpStatsEnhancedReputationSaved(alp_Player) );
		RegisterElementEnhanced( new alpStatsEnhancedReputationProgressSaved(alp_Player) );		
		
		RegisterElementEnhanced( new alpStatsEnhancedResistanceSaved(alp_Player) );
		RegisterElementEnhanced( new alpStatsEnhancedResistanceProgresSaved(alp_Player) );	
		
		RegisterElementEnhanced( new alpStatsEnhancedResistanceColdSaved(alp_Player) );	

		RegisterElementEnhanced( new alpStatsEnhancedHuntingSaved(alp_Player) );
		RegisterElementEnhanced( new alpStatsEnhancedHuntingProgressSaved(alp_Player) );				
		
		RegisterElementEnhanced( new alpStatsEnhancedSoftSkillSaved(alp_Player) );
		RegisterElementEnhanced( new alpStatsEnhancedHardSkillSaved(alp_Player) );		
		
		RegisterElementEnhanced( new alpStatsEnhancedToxicResistanceSaved(alp_Player) );
		RegisterElementEnhanced( new alpStatsEnhancedToxicResistanceProgresSaved(alp_Player) );			
		*/			
	}

}


