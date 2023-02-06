class alpPerkStamina 
{
	bool DisableStaminaPerkWhenAiming										= false;//false	
	float PenalizedStaminaSkillAfterDeath[2]								= {0,0.98};//if stamina level is higher than 0 then reached EXP are multiplied by 0.98 after dead

	ref array<float>										LevelMdf		= {1,0.96,0.92,0.88,0.84,0.8,0.76,0.72,0.68,0.64,0.6,0.56,0.52,0.48,0.44,0.4,0.36,0.32,0.28,0.24,0.2,0.16,0.12};
	
	ref array<float>										RequiredExp		= {0,2400,2600,2800,3000,3200,3400,3600,3800,4000,4200,4400,4600,4800,5000,5200,5400,5600,5800,6000,6200,6400,6600};

	float 													AnabolicMdf		= 4;

	float													MoveRun			= 1;
	float													MoveSprint		= 1.5;
	float													ClimbFast		= 1.7;
	float													ClimbSlow		= 1.2;
	float													SwimFast		= 2;
	float													SwimSlow		= 1.5;
	
}

