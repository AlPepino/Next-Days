


modded class alpND_world extends alpND_base
{
	
	
	override protected void Init()
	{	
		super.Init();


		//COMPATIBILITY issues Clans
		alp_ClanBasesOptions  		= new alpClanBasesOptions;
		
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() )
		{		
			if (!FileExist(ALP_CLANS_FOLDER	) )
			{ 
				MakeDirectory(ALP_CLANS_FOLDER);		
			}	
			
			//Options bases
			if (!FileExist(ALP_CLANS_BASES_FILE	) )
			{ 			
				JsonFileLoader< alpClanBasesOptions>.JsonSaveFile(ALP_CLANS_BASES_FILE,  alp_ClanBasesOptions);
			}
			else 
			{
				JsonFileLoader< alpClanBasesOptions>.JsonLoadFile(ALP_CLANS_BASES_FILE, alp_ClanBasesOptions );	
			}
				
			JsonFileLoader< alpClanBasesOptions>.JsonSaveFile(ALP_CLANS_BASES_FILE,  alp_ClanBasesOptions);				
		}
		
		AddPlugin( new alpClansPlugin( alpPLUGIN_BASE_ID.CLANS,  alpPLUGIN_BASE_EVENTS.ONCONNECT | alpPLUGIN_BASE_EVENTS.ONSPAWN | alpPLUGIN_BASE_EVENTS.ONDEATH | alpPLUGIN_BASE_EVENTS.ONDISCONNECT ) );		
	}	


	alpClansPlugin	GetClans()
	{
		
		alpClansPlugin plugin = alpClansPlugin.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.CLANS ) );
		
		if ( plugin )
		{
			return plugin;
		}
		
		return null;
	}	

}



