

class alpPluginNDrp extends alpPlugin
{
	
	ref alpOptionsRP_Players	alp_OptionsRP_Players;
	ref alpOptionsRP_Vehicles	alp_OptionsRP_Vehicles;

	
	ref array<ref alpVehicleBehavior> alp_OptionsRP_Vehicles_Behavior;

	ref map<string,ref alpVehicleBehavior> alp_OptionsRP_Vehicles_BehaviorMaped;
	
	void ~alpPluginNDrp()
	{
		delete alp_OptionsRP_Players;
		delete alp_OptionsRP_Vehicles;
		delete alp_OptionsRP_Vehicles_Behavior;
		delete alp_OptionsRP_Vehicles_BehaviorMaped;					
					
	}	
	
	override void Init() 
	{
		alp_OptionsRP_Players  = new alpOptionsRP_Players;
		alp_OptionsRP_Vehicles  = new alpOptionsRP_Vehicles;
		
		//mapping
		alp_OptionsRP_Vehicles_BehaviorMaped = new map<string,ref alpVehicleBehavior>;		
		
		//load file
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() )
		{
			if (!FileExist(ALP_RP_FOLDER)) MakeDirectory(ALP_RP_FOLDER);	
			
			//setting Players
			if (!FileExist(ALP_RP_PLAYERS_FILE) )
			{ 			
				JsonFileLoader< alpOptionsRP_Players>.JsonSaveFile(ALP_RP_PLAYERS_FILE,  alp_OptionsRP_Players);
			}
			else 
			{
				JsonFileLoader< alpOptionsRP_Players>.JsonLoadFile(ALP_RP_PLAYERS_FILE, alp_OptionsRP_Players );	
			}
				
			JsonFileLoader< alpOptionsRP_Players>.JsonSaveFile(ALP_RP_PLAYERS_FILE,  alp_OptionsRP_Players);			
			
			//setting vehicles
			if (!FileExist(ALP_RP_VEHICLES_FILE) )
			{ 
				JsonFileLoader< alpOptionsRP_Vehicles>.JsonSaveFile(ALP_RP_VEHICLES_FILE,  alp_OptionsRP_Vehicles);
			}
			else 
			{
				JsonFileLoader< alpOptionsRP_Vehicles>.JsonLoadFile(ALP_RP_VEHICLES_FILE, alp_OptionsRP_Vehicles );	
			}
				
			JsonFileLoader< alpOptionsRP_Vehicles>.JsonSaveFile(ALP_RP_VEHICLES_FILE,  alp_OptionsRP_Vehicles);		
			
			if (!FileExist(ALP_RP_VEHICLES_SETTINGS_FILE) )
			{ 
				alp_OptionsRP_Vehicles_Behavior  = new array<ref alpVehicleBehavior>;
				
				if ( GetVehicleOptions().InitVehiclesProperties )
				{
					InitVehiclesProperties( alp_OptionsRP_Vehicles_Behavior );
				}
				
				JsonFileLoader< array<ref alpVehicleBehavior>>.JsonSaveFile(ALP_RP_VEHICLES_SETTINGS_FILE,  alp_OptionsRP_Vehicles_Behavior);
			}
			else 
			{
				JsonFileLoader< array<ref alpVehicleBehavior>>.JsonLoadFile(ALP_RP_VEHICLES_SETTINGS_FILE, alp_OptionsRP_Vehicles_Behavior );	
			}

			
			for (int i = 0; i < alp_OptionsRP_Vehicles_Behavior.Count();i++)
			{
				alpVehicleBehavior vehicle = alp_OptionsRP_Vehicles_Behavior.Get(i);
				if ( vehicle )
				{
					alp_OptionsRP_Vehicles_BehaviorMaped.Set( vehicle.Name, vehicle );
				}
			}	
			
			
			JsonFileLoader< array<ref alpVehicleBehavior>>.JsonSaveFile(ALP_RP_VEHICLES_SETTINGS_FILE,  alp_OptionsRP_Vehicles_Behavior);							
		}	
		
		
	}
	
	



	override void OnConnectManaged( PlayerBase player )
	{	

		ScriptRPC rpc = GetND().GetInitRPC( GetID() );					

		WriteOnConnectRPC( rpc );
			
		GetND().SendGameRPC( rpc, player );
		
	}	
	
	void WriteOnConnectRPC(ref ScriptRPC rpc)
	{
		rpc.Write( alp_OptionsRP_Players );
		rpc.Write( alp_OptionsRP_Vehicles );
	}
	
	override void OnSpawnManaged( PlayerBase player )
	{
		player.LoadPlayerHive();
		//BANK ACCOUNT
		alpBANK.SetBankAccountOnConnect( player );		
		//player.GetPlayerHive().OnConnect();		
	}
	
	
	override void ReadInitRPC( PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		
		ctx.Read( alp_OptionsRP_Players );		
		ctx.Read( alp_OptionsRP_Vehicles );		

	}	
	
	void InitVehiclesProperties( ref array<ref alpVehicleBehavior> properties)
	{
		properties.Insert(  new alpVehicleBehavior("OffroadHatchback",false,10000,0.075,0.075,0.075, 150, 750, 3000 ) );
		properties.Insert(  new alpVehicleBehavior("OffroadHatchback_Blue",false,10000,0.075,0.075,0.075, 150, 750, 3000 ) );
		properties.Insert(  new alpVehicleBehavior("OffroadHatchback_White",false,10000,0.075,0.075,0.075, 150, 750, 3000 ) ); 
		properties.Insert( new alpVehicleBehavior( "CivilianSedan",false,10000,0.065,0.065,0.065, 150, 750, 3000 ) );
		properties.Insert(  new alpVehicleBehavior("CivilianSedan_Black",false,10000,0.065,0.065,0.065, 150, 750, 3000 ) );
		properties.Insert(  new alpVehicleBehavior("CivilianSedan_Wine",false,10000,0.065,0.065,0.065, 150, 750, 3000 ) );
		properties.Insert( new alpVehicleBehavior("Hatchback_02", false,10000,0.070,0.070,0.070 , 150, 750, 3000 ) );
		properties.Insert( new alpVehicleBehavior("Hatchback_02_Black", false,10000,0.070,0.070,0.070, 150, 750, 3000 ) );
		properties.Insert( new alpVehicleBehavior("Hatchback_02_Blue", false,10000,0.070,0.070,0.070, 150, 750, 3000 ) );
		properties.Insert( new alpVehicleBehavior("Sedan_02", false,10000,0.130,0.130,0.130, 150, 750, 3000 ) );
		properties.Insert( new alpVehicleBehavior("Sedan_02_Grey", false,10000,0.130,0.130,0.130 , 150, 750, 3000 ) );
		properties.Insert( new alpVehicleBehavior("Sedan_02_Red", false,10000,0.130,0.130,0.130 , 150, 750, 3000 ) );
		
		properties.Insert( new alpVehicleBehavior("CrSk_Land_Rover_Defender_110", true,2500,0.04,0.02,0.04, 500, 3000, 10000 ) );
		properties.Insert( new alpVehicleBehavior("CrSk_Land_Rover_Defender_110_UN", true,2500,0.04,0.02,0.04, 500, 3000, 10000 ) );
		properties.Insert( new alpVehicleBehavior( "CrSk_Land_Rover_Defender_110_Green", true,2500,0.04,0.02,0.04 , 500, 3000, 10000 ) );
		properties.Insert( new alpVehicleBehavior("Gerph_Zil130", true,500,0.01,0.0,0.00 , 1000, 5000, 10000 ) );	
		properties.Insert( new alpVehicleBehavior("Truck_01_Covered", true,500,0.01,0.0,0.00, 1000, 5000, 10000 ) );
	
	}
	
	alpOptionsRP_Players GetPlayerOptions()
	{
		return alp_OptionsRP_Players;
	}
	alpOptionsRP_Vehicles GetVehicleOptions()
	{
		return alp_OptionsRP_Vehicles;
	}
	alpVehicleBehavior GetVehicleProperties(string vehicle)
	{
		alpVehicleBehavior car;
		
		if ( alp_OptionsRP_Vehicles_BehaviorMaped && alp_OptionsRP_Vehicles_BehaviorMaped.Find( vehicle, car ) )
		{
			return car;
		}
		return null;
	}	
	

	
}
