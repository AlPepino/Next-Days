

class alpCreaturesPlugin extends alpPlugin
{

	
	ref alpCreaturesOptions					alp_OptionsCreatures;


	void ~alpCreaturesPlugin()
	{
		delete alp_OptionsCreatures;
	}
	


	override void Init() 
	{
		super.Init();
		
		
		alp_OptionsCreatures  			= new alpCreaturesOptions;

		
		//load file
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() )
		{
			
			
			if (!FileExist(ALP_CREATURES_FOLDER	) )
			{ 
				MakeDirectory(ALP_CREATURES_FOLDER);		
			}			
			
			//Options basic
			if (!FileExist(ALP_CREATURES_FILE	) )
			{ 			
				JsonFileLoader< alpCreaturesOptions>.JsonSaveFile(ALP_CREATURES_FILE,  alp_OptionsCreatures);
			}
			else 
			{
				JsonFileLoader< alpCreaturesOptions>.JsonLoadFile(ALP_CREATURES_FILE, alp_OptionsCreatures );	
			}
				
			JsonFileLoader< alpCreaturesOptions>.JsonSaveFile(ALP_CREATURES_FILE,  alp_OptionsCreatures);		
			

		}
		
		
	}

	
	alpCreaturesOptions GetOptions()
	{
		return alp_OptionsCreatures;
	}
	
	
	bool IsZombieMonster(string type)
	{		
		if ( GetOptions().ZombiesMonster.Find( type ) != -1 )
		{
			return true;
		}		
		return false;	
	}
	
	array<ref alpZombieBehavior> GetZombieCivil()
	{
		array<ref alpZombieBehavior> behavior;
		
		
		JsonFileLoader< array<ref alpZombieBehavior> >.JsonLoadFile(ALP_CREATURES_ZED_C_FILE, behavior );	
		
		
		if ( behavior && behavior.Count() > 0 )
		{
			return behavior;		
		}
		else
		{
			behavior =  new array<ref alpZombieBehavior>;
			
			behavior.Insert( new alpZombieBehavior( 0 , 0.2 , 3 , 2 , 0.25,1 ) );
			behavior.Insert( new alpZombieBehavior( 1 , 0.4 , 2 , 1 , 0.0,1 ) );
			behavior.Insert( new alpZombieBehavior( 2 , 0   , 1 , 0 , 0.0 ) );		
			
			
			JsonFileLoader< array<ref alpZombieBehavior> >.JsonSaveFile(ALP_CREATURES_ZED_C_FILE, behavior );	
		
		}
	
		return behavior;
	
	}

		
	array<ref alpZombieBehavior> GetZombieCivilNBC()
	{
		array<ref alpZombieBehavior> behavior;
		
		
		JsonFileLoader< array<ref alpZombieBehavior> >.JsonLoadFile(ALP_CREATURES_ZED_C_NBC_FILE, behavior );	
		
		
		if ( behavior && behavior.Count() > 0 )
		{
			return behavior;		
		}
		else
		{
			behavior =  new array<ref alpZombieBehavior>;
			
			behavior.Insert( new alpZombieBehavior( 0 , 0.2 , 3 , 2 , 0.25,2 ,3,3,1 ) );
			behavior.Insert( new alpZombieBehavior( 1 , 0.4 , 2 , 1 , 0.0 ,2  ,2,2,1) );
			behavior.Insert( new alpZombieBehavior( 2 , 0   , 1 , 0 , 0.0 ,1 ,1,1,1) );	
			
			
			JsonFileLoader< array<ref alpZombieBehavior> >.JsonSaveFile(ALP_CREATURES_ZED_C_NBC_FILE, behavior );	
		
		}
	
		return behavior;
	
	}
	
	
	array<ref alpZombieBehavior> GetZombieMilitary()
	{
		array<ref alpZombieBehavior> behavior;
		
		
		JsonFileLoader< array<ref alpZombieBehavior> >.JsonLoadFile(ALP_CREATURES_ZED_M_FILE, behavior );	
		
		
		if ( behavior && behavior.Count() > 0 )
		{
			return behavior;		
		}
		else
		{
			behavior =  new array<ref alpZombieBehavior>;
			
			behavior.Insert( new alpZombieBehavior( 1 , 0.1, 3,  2 , 0.5,2 ) );
			behavior.Insert( new alpZombieBehavior( 2 , 0.2 , 2,  1 , 0.0,2 ) );
			behavior.Insert( new alpZombieBehavior( 3 , 0   , 1,  0 , 0.0,1 ) );	
			
			
			JsonFileLoader< array<ref alpZombieBehavior> >.JsonSaveFile(ALP_CREATURES_ZED_M_FILE, behavior );	
		
		}
	
		return behavior;
	
	}	
	array<ref alpZombieBehavior> GetZombieMilitaryNBC()
	{
		array<ref alpZombieBehavior> behavior;
		
		
		JsonFileLoader< array<ref alpZombieBehavior> >.JsonLoadFile(ALP_CREATURES_ZED_M_NBC_FILE, behavior );	
		
		
		if ( behavior && behavior.Count() > 0 )
		{
			return behavior;		
		}
		else
		{
			behavior =  new array<ref alpZombieBehavior>;
			
			behavior.Insert( new alpZombieBehavior( 1 , 0.1, 3,  2 , 0.5 ,4 , 6,6,1) );
			behavior.Insert( new alpZombieBehavior( 2 , 0.2 , 2,  1 , 0.0,4 ,4,4,1 ) );
			behavior.Insert( new alpZombieBehavior( 3 , 0   , 1,  0 , 0.0,2 ,2,2,1 ) );
			
			
			JsonFileLoader< array<ref alpZombieBehavior> >.JsonSaveFile(ALP_CREATURES_ZED_M_NBC_FILE, behavior );	
		
		}
	
		return behavior;
	
	}	
	
	array<ref alpZombieBehavior> GetZombieMonster()
	{
		array<ref alpZombieBehavior> behavior;
		
		
		JsonFileLoader< array<ref alpZombieBehavior> >.JsonLoadFile(ALP_CREATURES_ZED_MONSTER_FILE, behavior );	
		
		
		if ( behavior && behavior.Count() > 0 )
		{
			return behavior;		
		}
		else
		{
			behavior =  new array<ref alpZombieBehavior>;
			
			behavior.Insert( new alpZombieBehavior( 1 , 0.025, 6,  4 , 0.5 ,10 , 10,10,1) );
			behavior.Insert( new alpZombieBehavior( 2 , 0.05 , 4,  3 , 0.0,  8 , 6,6,1 ) );
			behavior.Insert( new alpZombieBehavior( 3 , 0.1   , 2,  2 , 0.0, 6 , 2,2,1 ) );
			
			
			JsonFileLoader< array<ref alpZombieBehavior> >.JsonSaveFile(ALP_CREATURES_ZED_MONSTER_FILE, behavior );	
		
		}
	
		return behavior;
	
	}		
}
