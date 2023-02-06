class alpPerkRadResistance 
{

	float PenalizedResistanceSkillAfterDeath[2]								= {0,0.99};//if stamina level is higher than 0 then reached EXP are multiplied by 0.98 after dead

	
	ref array<float>										LevelMdf		= {0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95};
	
	ref array<float>										RequiredExp		= {0,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000,2000};	
	
}

