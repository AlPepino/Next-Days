
class alpSpawnSettings 
{
	ref map<int,ref alpSpawnSetPlayerBothRole> alp_SpawnSetMaped;
	
	ref alpSpawnSettings_Base alp_SpawnSettings;
	
	void alpSpawnSettings()
	{
	
		alp_SpawnSettings = alpSpawnSettings_Base.Load();
		
		alp_SpawnSetMaped = new map<int,ref alpSpawnSetPlayerBothRole>;
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.Init,0);
	}
	
	void Init()
	{

		int maxLevel = GetND().GetRP().GetPerkReputationLevelCup();
		
		if ( alp_SpawnSettings &&  alp_SpawnSettings.PlayerSpawn )
		{
			for(int i = 0;i<=maxLevel;i++)
			{
				alpSpawnSetPlayerBothRole settings = FindPlayerSet(i);
				
				alp_SpawnSetMaped.Set( i, 	settings );
			
			}
			
		}		

	
	}
	
	alpSpawnSetPlayerBothRole FindPlayerSet(int level)
	{
		alpSpawnSetPlayerBothRole sets = new alpSpawnSetPlayerBothRole;

		int lastLevel = -1;
		foreach( alpSpawnSetPlayer spawnsetHero : alp_SpawnSettings.PlayerSpawn )
		{
			
			if ( spawnsetHero.RequiredReputationLevel <= level && ( spawnsetHero.RequiredReputationLevel > lastLevel || ( spawnsetHero.RequiredReputationLevel == lastLevel && spawnsetHero.RequiredcharacterRole == 1 ) ))
			{
				if ( spawnsetHero.RequiredcharacterRole != 2 )
				{
					lastLevel = spawnsetHero.RequiredReputationLevel;
					sets.Hero = spawnsetHero;
				}

			}
		}		
		lastLevel = -1;
		foreach( alpSpawnSetPlayer spawnsetBandit : alp_SpawnSettings.PlayerSpawn )
		{
			
			if ( spawnsetBandit.RequiredReputationLevel <= level && ( spawnsetBandit.RequiredReputationLevel > lastLevel || ( spawnsetBandit.RequiredReputationLevel == lastLevel && spawnsetBandit.RequiredcharacterRole == 2 ) ))
			{
				if ( spawnsetBandit.RequiredcharacterRole != 1 )
				{
					lastLevel = spawnsetBandit.RequiredReputationLevel;
					sets.Bandit = spawnsetBandit;
				}

			}
		}			
		
		return sets;	
	}
	
	
	alpSpawnSetPlayer GetSpawnSet(int level)
	{
		int id = Math.AbsInt( level );
		
		alpSpawnSetPlayerBothRole settings;
		
		if ( alp_SpawnSetMaped.Find( id, settings) )
		{
			if ( level < 0 )
			{//bandit
				return settings.Bandit;
			}
			else
			{//hero
				return settings.Hero;
			}
		}	
		return null;
	}
	
	alpSpawnSetNewborn GetNewbornSet()
	{
		return alp_SpawnSettings.NewbornSpawn;
	}
}
