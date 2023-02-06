
modded class alpStoreValues 
{
	float								PerkStaminaEXP;
	float								PerkSoftEXP;
	float								PerkRoughEXP;
#ifdef NAMALSK_SURVIVAL		
	float								PerkResistanceColdEXP;
#endif 

	float								PerkReputationEXP;
	float								PerkHuntingEXP;
	float								PerkRadiationResistanceEXP;
	float								PerkToxicResistanceEXP;


	float								BestScore;	
	//float                               LastScore;
	ref alpSavedDNA 					SavedDNA = new alpSavedDNA();
}


class alpSavedDNA 
{
	float StaminaEXP;
	
	float SpecialtySoftEXP;
	
	float SpecialtyRoughEXP;
	
	float ResistanceEXP;
	
	float ResistanceToxicEXP;

	float ResistanceColdEXP;
	
	float ReputationEXP;
	
	float HuntingEXP;
	
	/*
	float StaminaLevel;
	float StaminaProgress;
	
	float ResistanceLevel;
	float ResistanceProgress;	
	
	float ToxicResistanceLevel;
	float ToxicResistanceProgress;	

	float ReputationLevel;
	float ReputationProgress;	
	
	float HuntingLevel;
	float HuntingProgress;	
*/
}