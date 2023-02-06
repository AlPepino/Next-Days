

class alpSpawnSettings_Base
{
	ref alpSpawnSetNewborn NewbornSpawn;

	ref array<ref alpSpawnSetPlayer>	PlayerSpawn;
	
	
	static alpSpawnSettings_Base Load()
	{
		alpSpawnSettings_Base instance = new alpSpawnSettings_Base;
	
		instance.NewbornSpawn = alpSpawnSetNewborn();
		
		instance.PlayerSpawn = new array<ref alpSpawnSetPlayer>;
		instance.PlayerSpawn.Insert( new alpSpawnSetPlayer(1) );
		instance.PlayerSpawn.Insert( new alpSpawnSetPlayer(2) );
		//Options basic
		if (!FileExist(ALP_CLANS_SPAWN_EQUIP_FILE	) )
		{ 			
			JsonFileLoader< alpSpawnSettings_Base>.JsonSaveFile(ALP_CLANS_SPAWN_EQUIP_FILE,  instance);
		}
		else 
		{
			JsonFileLoader< alpSpawnSettings_Base>.JsonLoadFile(ALP_CLANS_SPAWN_EQUIP_FILE, instance );	
		}
			
		JsonFileLoader< alpSpawnSettings_Base>.JsonSaveFile(ALP_CLANS_SPAWN_EQUIP_FILE,  instance);			
	
		
		return instance;
	}
	

}

class alpSpawnSetNewborn
{	
	float Water;
	float Energy;		
	ref array<string> Messages;	
	int	lootMaxCount =  0;		
	ref array<ref alpLootCargo>	 Equipments;
	
	void alpSpawnSetNewborn()
	{
		Water = 2000;
		Energy = 20000;

		Messages = new array<string>;
		
		Messages.Insert("Welcome to our server");
		Messages.Insert("And since it's you I am giving you extra stuff to help you survive");
		Messages.Insert("Good luck!");
		
		Equipments = new array<ref alpLootCargo>;

		alpLootCargo example = new alpLootCargo;
		example.title = "Pistols_1";
		example.chance =1;		
				
		Equipments.Insert( example );
		
		alpLootCargo example2 = new alpLootCargo;
		example2.title = "CIVIL_TOP";
		example2.chance =1;		
				
		Equipments.Insert( example2 );
		
		alpLootCargo example3 = new alpLootCargo;
		example3.title = "CIVIL_PANTS";
		example3.chance =1;		
				
		Equipments.Insert( example3 );
		
		alpLootCargo example4 = new alpLootCargo;
		example4.title = "CIVIL_BOOTS";
		example4.chance =1;		
				
		Equipments.Insert( example4 );						
	}
	
}

class alpSpawnSetPlayerBothRole
{
	ref alpSpawnSetPlayer Hero;
	ref alpSpawnSetPlayer Bandit;
}


class alpSpawnSetPlayer
{ 
	int RequiredcharacterRole; //0,1,2   1-HERO 2-BANDIT
	int RequiredReputationLevel;	
	float Water;
	float Energy;
	ref array<string> Messages;	
	int	lootMaxCount =  0;			
	ref array<ref alpLootCargo>	 Equipments;

	
	void alpSpawnSetPlayer(int template = 1)
	{
			Messages = new array<string>;
			
			Messages.Insert("Augh! This time you get it better");
			Messages.Insert("Good luck!");		
		
			Equipments = new array<ref alpLootCargo>;
		
			alpLootCargo example;
			alpLootCargo example2;
			alpLootCargo example3;
			alpLootCargo example4;
		
		if ( template == 1 )
		{
			RequiredcharacterRole = 0;
			RequiredReputationLevel = 0;
	
			example = new alpLootCargo;
			example.title = "Pistols_1";
			example.chance =1;		
					
			Equipments.Insert( example );
			
			example2 = new alpLootCargo;
			example2.title = "CIVIL_TOP";
			example2.chance =1;		
					
			Equipments.Insert( example2 );
			
			example3 = new alpLootCargo;
			example3.title = "CIVIL_PANTS";
			example3.chance =1;		
					
			Equipments.Insert( example3 );
			
			example4 = new alpLootCargo;
			example4.title = "CIVIL_BOOTS";
			example4.chance =1;		
					
			Equipments.Insert( example4 );				
		
		}
		else if ( template == 2 )
		{
			RequiredcharacterRole = 0;
			RequiredReputationLevel = 5;
	
	
			example = new alpLootCargo;
			example.title = "AssaultRifles_1";
			example.chance =1;		
					
			Equipments.Insert( example );
			
			example2 = new alpLootCargo;
			example2.title = "SOLDIER_TOP";
			example2.chance =1;		
					
			Equipments.Insert( example2 );
			
			example3 = new alpLootCargo;
			example3.title = "SOLDIER_PANTS";
			example3.chance =1;		
					
			Equipments.Insert( example3 );
			
			example4 = new alpLootCargo;
			example4.title = "SOLDIER_BOOTS";
			example4.chance =1;		
					
			Equipments.Insert( example4 );			
		
		
		}
		
		
	}					
}