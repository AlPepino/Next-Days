class alpPerkReputation
{
	bool EnableHallOfFame													= true;
	bool StoreLastSessionInHoF												= false;
	int MaxCountRecords														= 30;		
	float PenalizedReputationSkillAfterDeath[2]								= {0,0.95};//if reputation level is higher than 0 then reached EXP are multiplied by 0.95 after dead

	ref array<float>										LevelMdf		= {0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.10,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.20};
	
	ref array<float>										RequiredExp		= {0,20000,40000,60000,80000,100000,120000,140000,160000,180000,200000,220000,240000,260000,280000,300000,320000,340000,3600000,380000};
	
	float													KillPlayerBonus = 0.05;
	float											Buy[2]					= {1,-1};
	float											Sell[2]					= {1,-1};	
	float											KillHero[2]				= {-2500,-5000};
	float											KillBandit[2]			= {5000,-2500};
	float											SkinPlayer[2]			= {-20000,-5000};
	float											KillZombie[2]			= {500,-50};
	float											KillAnimal[2]			= {-2500,-5000};
	float											KillWolf[2]				= {5000,-5000};
	float											KillBear[2]				= {20000,-20000};
	float											LockPicking[2]			= {-5000,-5000};
	float											TreatOthers[2]			= {2500,5000};
	float											DestroyCombLock[2]		= {-5000,-5000};
	float											DestroyPart[2]			= {-5000,-5000};
	float											DigInRadioactiveBarrel[2] = {20000,20000};

	
	
}

