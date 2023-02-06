class alpPerkHunting 
{
	//bool DisableStaminaPerkWhenAiming										= false;//false	
	float PenalizedHuntingSkillAfterDeath[2]								= {0,0.98};//if stamina level is higher than 0 then reached EXP are multiplied by 0.98 after dead

	int 													RequiredLevelToSkin	= 0;
	int 													RequiredLevelToGetPelt	= 0;
	int 													AffectPeltQualityByLevel = 1;
	bool 													PeltIsNotRepairable = 1;
	
	ref array<float>										LevelMdf		= {0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1,1.05,1.1,1.15,1.2,1.25,1.3,1.35,1.4,1.45,1.5};
	
	ref array<float>										DamageLevelMdf	= {0,0.02,0.04,0.06,0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.22,0.24,0.26,0.28,0.30,0.32,0.34,0.36,0.38,0.4};
	
	ref array<float>										RequiredExp		= {0,500,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000,12000,13000,14000,15000,16000,17000,18000,19000};
	
	
	float													SkinAnimal		= 200;
	float													KillAnimal		= 100;
	float													KillDeer		= 2000;
	float													KillBoar		= 1000;
	float													KillWolf		= 500;
	float													KillBear		= 1500;	
	
}

