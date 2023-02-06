


class alpPlayersID 
{
	int LAST_PLAYER_ID;
	
	
	void alpPlayersID()
	{

		if (!FileExist(ALP_RP_FOLDER_ID_JSON))
		{
			LAST_PLAYER_ID = 0;
			JsonFileLoader<alpPlayersID>.JsonSaveFile( ALP_RP_FOLDER_ID_JSON,  this);
		}

		
		JsonFileLoader<alpPlayersID>.JsonLoadFile( ALP_RP_FOLDER_ID_JSON,  this);

						
	}
	
	
	int GetPlayerID()
	{
		LAST_PLAYER_ID++;
		Save();
		return LAST_PLAYER_ID;
	}
	
	void Save()
	{
		JsonFileLoader<alpPlayersID>.JsonSaveFile( ALP_RP_FOLDER_ID_JSON,  this);
	}
}
