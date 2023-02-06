

modded class alpRP 
{
	//plotpole client data
	bool					alp_IamHome					= false;

	bool					alp_Camera3rdPerson;	
	
	
	
	string alp_CLIENT_DATA = "$profile:nextdays.json";
	
	ref alpClanData alp_Clan;
	
	
	ref alpCLANoptionsClient alp_ClanClient;
	
	override void Init()
	{
		super.Init();
				
		if ( GetGame().IsClient()  )
		{
			alp_ClanClient = new alpCLANoptionsClient();

			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.LoadClientData	, 0 );	
		}
		
	}
	
	
	void LoadClientData()
	{
		if ( GetGame().GetPlayer() == GetPlayer() )
		{
			//load cliet
			if (!FileExist(alp_CLIENT_DATA	) )
			{ 			
				JsonFileLoader< alpCLANoptionsClient>.JsonSaveFile(alp_CLIENT_DATA,  alp_ClanClient);
			}
			else 
			{
				JsonFileLoader< alpCLANoptionsClient>.JsonLoadFile(alp_CLIENT_DATA, alp_ClanClient );	
			}
				
			JsonFileLoader< alpCLANoptionsClient>.JsonSaveFile(alp_CLIENT_DATA,  alp_ClanClient);
		}		
	
	}
	


	
	alpCLANoptionsClient GetClientData()
	{
		return alp_ClanClient;
	}
	
	void SetClan(alpClanData clan)
	{
		alp_Clan = clan;
	}
	
	alpClanData GetClan()
	{
		return alp_Clan;
	}
		
	void SaveClientData()
	{
		JsonFileLoader< alpCLANoptionsClient>.JsonSaveFile(alp_CLIENT_DATA,  alp_ClanClient);	
	}
	
	
	bool IsHome()
	{
		return alp_IamHome;
	}	
	
	void SetHome(bool state, bool camera )
	{
		alp_IamHome	= state;
		

		//Print("KONTROLA HOME");
		if ( GetGame().GetWorld().Is3rdPersonDisabled() && ( GetND().GetClans().GetOptions().Enable3rdPersonCameraAtHome || GetND().GetClans().GetOptions().Enable3rdPersonCameraAtSafeZone || GetND().GetClans().GetOptions().Enable3rdPersonCameraInVehicle ) )
		{
			//Print("ANO TESTUJU KAMERU");
			if (camera && alp_Camera3rdPerson )
			{
				//change camera			
				//Print("NASTAVUJU 3 pohled");	
				alp_Player.Set3DcameraALP( true );	

			}
			else
			{
				alp_Player.Set3DcameraALP( false );	
				if (alp_Camera3rdPerson)
				{
					//Print("NASTAVUJU 3 pohled");	
					alp_Camera3rdPerson = false;					
				}
			}
		}
	}	
	
	
	bool HasPDA()
	{
		return true;
	}
}


