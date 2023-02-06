// NextDays - managing all added global plugins


ref alpND_base alp_ND_base;

alpND_base GetGameND()  //GetND GetGameND
{
	if ( !alp_ND_base )
	{
		alp_ND_base = new alpND_base();
	}

	return alp_ND_base;
}




class alpND_base 
{
//INSTANCE	
//--------	
	//client
	string alp_CLIENT_DATA = "$profile:next-days.json";
	int m_ServerTimeDelta;

	static ref array<string> alp_PlayerRegister;
	
	//timestamp missions
	static ref map<int,int>								RegisteredPrivateMissions = new map<int,int>;
	
	protected bool alp_IsVersionValid;
	
	protected bool alp_IsFirstServerRun;	

	protected ref alpPlayersID alp_PlayersID;
	
	
	//plugins
	protected ref map<int, ref alpPluginBase> alp_ActivePlugins;							
				
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_START;				
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_UPDATE;				
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_FINISH;	
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_ONCONNECT;
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_ONSPAWN;
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_ONDEATH;
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_ONRECONNECT;
	protected ref array<ref alpPluginBase> alp_RegPlugins_EVENT_ONDISCONNECT;
	
	
	//compatibility issues
	ref array<ref alpMissionTemplateClient>	alp_MarkedMission; 	 //just for MissionsSystem
	ref alpMSoptions 						alp_OptionsMS;
	ref map<int, ref alpMostWanted>			alp_MostWanted;
	ref array< ref alpMostWanted>			alp_MarkedMostWanted;
	//trader events 
	ref array<ref alpTraderQuest>			alp_Quests;
	ref array< ref alpRegisteredQuest>		alp_ActiveQuests; 
	ref array< ref alpRegisteredQuest> 		alp_MarkedActiveQuests;
	
	
	FileHandle m_FileTraderLogs;
	
//METHODS
//-------	
	
	//CONSTRUCTOR
	void alpND_base()
	{
		g_Game.Event_OnRPC.Insert( OnRPC );			
		
		if ( g_Game.IsServer() )
		{
			VerifyVersionCompatibility();
		}
		
		alp_ActivePlugins 					= new map<int,ref alpPluginBase>;
		
		alp_RegPlugins_EVENT_START 			= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_UPDATE 		= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_FINISH 		= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_ONCONNECT 		= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_ONSPAWN 		= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_ONDEATH 		= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_ONRECONNECT	= new array<ref alpPluginBase>;
		alp_RegPlugins_EVENT_ONDISCONNECT	= new array<ref alpPluginBase>;
		
		//create folders

		
		if (!FileExist(ALP_LOGS)) MakeDirectory(ALP_LOGS);
		if (!FileExist(ALP_NOTF_ROOT)) MakeDirectory(ALP_NOTF_ROOT);
		if (!FileExist(ALP_RP_FOLDER)) MakeDirectory(ALP_RP_FOLDER);	
		if (!FileExist(ALP_RP_FOLDER_ID)) MakeDirectory(ALP_RP_FOLDER_ID);	
		if (!FileExist(ALP_MISSIONS_BANK_FOLDER)) MakeDirectory(ALP_MISSIONS_BANK_FOLDER);//bank accounts

		
		//Player ID Handler
		alp_PlayersID = new alpPlayersID();
		
		
		Init();
		

	}	
	void ~alpND_base()
	{
		delete alp_PlayersID;
		delete alp_ActivePlugins;
		delete alp_RegPlugins_EVENT_START;
		delete alp_RegPlugins_EVENT_UPDATE;					
		delete alp_RegPlugins_EVENT_FINISH;	
		delete alp_RegPlugins_EVENT_ONCONNECT;					
		delete alp_RegPlugins_EVENT_ONSPAWN;	
		delete alp_RegPlugins_EVENT_ONDEATH;	
		delete alp_RegPlugins_EVENT_ONRECONNECT;	
		delete alp_RegPlugins_EVENT_ONDISCONNECT;	
		delete alp_MarkedMission;	
		delete alp_OptionsMS;	
		delete alp_MostWanted;	
		delete alp_MarkedMostWanted;			
		delete alp_Quests;	
		delete alp_ActiveQuests;	
		delete alp_MarkedActiveQuests;		
		
		if ( m_FileTraderLogs ) {
			CloseFile( m_FileTraderLogs );
		}	
	}	
	
	protected void Init(){}	

	
	void RegisterPrivateMission(int id, int time ){
		RegisteredPrivateMissions.Set(id,time);
		if ( GetGame().IsClient() ){
			SaveRegisteredPrivateMissions();
		}		
	}
	
	bool IsMissionKnown(int id, int timeStamp , int requiredLevel ){
		Man player = GetGame().GetPlayer();
		int level;
		if ( player && player.GetIdentity() ){
			level = player.GetIdentity().GetPlayerLevel();
		}				
		int time;
		if ( !timeStamp && !requiredLevel){
			return true;
		}
		
		if ( RegisteredPrivateMissions.Find( id, time ) && time == timeStamp && requiredLevel <= level ) {
			return true;
		}
		return false;
	}	

	int GetNewPlayerID()
	{
		return alp_PlayersID.GetPlayerID();
	}
			
	void AddPlugin(alpPluginBase plugin)
	{
		alp_ActivePlugins.Set( plugin.GetID(), plugin );
		

		if ( plugin.IsEventStart() )
		{
			alp_RegPlugins_EVENT_START.Insert( plugin );
		}	
		if ( plugin.IsEventUpdate() )
		{
			alp_RegPlugins_EVENT_UPDATE.Insert( plugin );
		}
		if ( plugin.IsEventFinish() )
		{
			alp_RegPlugins_EVENT_FINISH.Insert( plugin );
		}		
		if ( plugin.IsEventOnConnect() )
		{
			alp_RegPlugins_EVENT_ONCONNECT.Insert( plugin );
		}				
		if ( plugin.IsEventOnReconnect() )
		{
			alp_RegPlugins_EVENT_ONRECONNECT.Insert( plugin );
		}			
		if ( plugin.IsEventOnSpawn() )
		{
			alp_RegPlugins_EVENT_ONSPAWN.Insert( plugin );
		}	
		if ( plugin.IsEventOnDeath() )
		{
			alp_RegPlugins_EVENT_ONDEATH.Insert( plugin );
		}	
		if ( plugin.IsEventOnDisconnect() )
		{
			alp_RegPlugins_EVENT_ONDISCONNECT.Insert( plugin );
		}							
	}
	
	
	void OnStart()
	{
		
		foreach ( alpPluginBase plugin : alp_RegPlugins_EVENT_START )
		{
			plugin.OnStart();
		}			
	}
	

	
	void OnUpdate( float timeslice )
	{

		foreach ( alpPluginBase plugin : alp_RegPlugins_EVENT_UPDATE )
		{
			plugin.OnUpdate(timeslice);
		}			
	}

	void OnFinish()
	{
		foreach ( alpPluginBase plugin : alp_RegPlugins_EVENT_FINISH )
		{
			plugin.OnFinish();
		}			
	}		
	
	void OnConnect( Man player )
	{	
		foreach ( alpPluginBase plugin : alp_RegPlugins_EVENT_ONCONNECT )
		{
			plugin.OnConnect( player );
		}	
	
	}
	
	void OnReconnect( Man player )
	{
		foreach ( alpPluginBase plugin : alp_RegPlugins_EVENT_ONRECONNECT )
		{
			plugin.OnReconnect( player );
		}		
	}	

	void OnDisconnect( Man player )
	{
		foreach ( alpPluginBase plugin : alp_RegPlugins_EVENT_ONDISCONNECT )
		{
			plugin.OnDisconnect( player );
		}				
	}	
			
	void OnSpawn( Man player )
	{
		foreach ( alpPluginBase plugin : alp_RegPlugins_EVENT_ONSPAWN )
		{
			plugin.OnSpawn( player );
		}			
	}	
	void OnDeath( Man player )
	{
		foreach ( alpPluginBase plugin : alp_RegPlugins_EVENT_ONDEATH )
		{
			plugin.OnDeath( player );
		}			
	}	
	

		
	//compatibility check
	private void VerifyVersionCompatibility()
	{
		
		alp_IsVersionValid = false;
		alp_IsFirstServerRun = false;
		
		
		if (!FileExist(ALP_ROOTFOLDER)) 
		{			
			MakeDirectory(ALP_ROOTFOLDER);	
			
			if (!FileExist(ALP_ROOTFOLDER_OLD)) 
			{
				alp_IsFirstServerRun = true;
			}
		}
				
		alpNDversion version;	
		
		if (!FileExist(ALP_ROOTFOLDER + "ND_version.json"))
		{		
			version = new alpNDversion();				
			JsonFileLoader< alpNDversion>.JsonSaveFile(ALP_ROOTFOLDER + "ND_version.json",  version);
			
			if (!FileExist(ALP_ROOTFOLDER_OLD + "ND_version.json"))
			{
				alp_IsFirstServerRun = true;
			}
		}
		else
		{
			
			JsonFileLoader< alpNDversion>.JsonLoadFile(ALP_ROOTFOLDER + "ND_version.json",  version);
			if ( version.Version == ALP_CURRENTVERSION )
			{
					alp_IsVersionValid = true;			
			}
			else
			{
				version.Version = ALP_CURRENTVERSION;
				JsonFileLoader< alpNDversion>.JsonSaveFile(ALP_ROOTFOLDER + "ND_version.json",  version);
			}
		}		
	
		Print(ALP_TRADEMARK + "IS FIRST SERVER RUN: " + alp_IsFirstServerRun );
		Print(ALP_TRADEMARK + "IS VALID VERSION: " + alp_IsVersionValid );
	}
	
	
	bool IsValid()
	{
		return alp_IsVersionValid;
	}
	
	
	bool IsFirstRun()
	{	
		return alp_IsFirstServerRun;
	}
	
	void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
	{

		if ( rpc_type == ALP_RPC_GAME )
		{
			int type, pluginID;	
		
			ctx.Read(type);
			ctx.Read(pluginID);
			
			switch(type)
			{
				case ALP_RPC_GAME_TYPE.INIT:
				{
					foreach ( alpPluginBase init : alp_RegPlugins_EVENT_ONCONNECT )
					{
						if ( init.GetID() == pluginID )
						{
							init.ReadInitRPC( sender, target, ctx);
							init.SyncInitStatusCompleted();
							break;
						}					
					}											
					break;
				}
				case ALP_RPC_GAME_TYPE.SYNC:
				{
					foreach ( alpPluginBase sync : alp_ActivePlugins )
					{
						if ( sync.GetID() == pluginID )
						{
							sync.ReadSyncRPC( sender, target, ctx);
							break;
						}					
					}											
					break;
				}	
						
			}			
		}
						
	}		

	
	ScriptRPC GetInitRPC(int plugin)
	{
		ScriptRPC rpc = new ScriptRPC();		
		rpc.Write( ALP_RPC_GAME_TYPE.INIT );
		rpc.Write( plugin );
		return rpc;
	}

	ScriptRPC GetSyncRPC(int plugin)
	{
		ScriptRPC rpc = new ScriptRPC();		
		rpc.Write( ALP_RPC_GAME_TYPE.SYNC );
		rpc.Write( plugin );
		return rpc;
	}	

	
		
	void SendGameRPC(ScriptRPC rpc, Man target, bool guaranteed = true, bool toAll = false, bool global = false)
	{
		if ( toAll )
		{
			array<Man> players = new array<Man>;
			GetGame().GetPlayers( players );
				
			for ( int i = 0; i < players.Count(); i++ ){
				if( players.Get(i) ){
					rpc.Send(players.Get(i), ALP_RPC_GAME, guaranteed, players.Get(i).GetIdentity() );	

				}
			}			
			/*
			if ( global )
			{
				array<Man> players = new array<Man>;
				GetGame().GetPlayers( players );
					
				for ( int i = 0; i < players.Count(); i++ ){
					if( players.Get(i) ){
						rpc.Send(players.Get(i), ALP_RPC_GAME, guaranteed, null );	

					}
				}

			}
			else
			{
				rpc.Send(target, ALP_RPC_GAME, guaranteed, null );		
			}
			*/
		}
		else
		{
			rpc.Send(target, ALP_RPC_GAME, guaranteed, target.GetIdentity() );	
		}
	}
	
	void SendPlayerRPC(ScriptRPC rpc, Man target, bool guaranteed = true, bool toAll = false, bool global = false)
	{
		if ( toAll )
		{
			array<Man> players = new array<Man>;
			GetGame().GetPlayers( players );
				
			for ( int i = 0; i < players.Count(); i++ ){
				if( players.Get(i) ){
					rpc.Send(players.Get(i), ALP_RPC_PLAYER, guaranteed, players.Get(i).GetIdentity() );	

				}
			}				
			/*
			if ( global ){
				array<Man> players = new array<Man>;
				GetGame().GetPlayers( players );
					
				for ( int i = 0; i < players.Count(); i++ ){
					if( players.Get(i) ){
						rpc.Send(players.Get(i), ALP_RPC_PLAYER, guaranteed, null );	

					}
				}				
				
			}
			else
			{
				rpc.Send(target, ALP_RPC_PLAYER, guaranteed, null );		
			}
			*/
		}
		else
		{
			rpc.Send(target, ALP_RPC_PLAYER, guaranteed, target.GetIdentity() );	
		}
	}
	
	alpPluginBase	GetPlugin(int id)
	{
		
		alpPluginBase plugin = alp_ActivePlugins.Get( id );
		
		if ( plugin )
		{
			return plugin;
		}
		
		return null;
	}	


//COMPATIBILITY ISSUES
	//just for MissionsSystem
	//-----------------------
	array<ref alpMissionTemplateClient> GetMarkedMission()
	{
		return alp_MarkedMission;
	}
	
	//only client side
	void MarkMissionOnMap(){}
	
	
	int HasWalkieTalkie()
	{
		
		return 0;		
	}
	
	int GetRadiationLevel()
	{
		return 0;		
	}
	//MOST WANTED for notification
	
	array< ref alpMostWanted> GetMostWanted()
	{
		return 	alp_MarkedMostWanted;
	}

	void UpdateMostWanted()
	{
		if ( alp_MostWanted )
		{
			alp_MarkedMostWanted = new array< ref alpMostWanted>;
			
			int currentTime = g_Game.GetTime() - (60 * 5 * 1000); //5 minutes
	
			for (int i = 0; i < alp_MostWanted.Count();)
			{
				alpMostWanted wanted = alp_MostWanted.GetElement(i);
				
				if ( wanted.GetTime() < currentTime )
				{
					alp_MostWanted.RemoveElement(i);
					continue;
				}
				else
				{
					alp_MarkedMostWanted.Insert( wanted );	
				}		
				i++;
			}	
		}
	
	}
	//quests
	array< ref alpRegisteredQuest> GetMarkedRegisteredQuests()
	{
		return 	alp_MarkedActiveQuests;
	}	

	void UpdateNPCquests()
	{
		if ( alp_ActiveQuests )
		{
			if ( alp_MarkedActiveQuests )
			{
				alp_MarkedActiveQuests.Clear();
			}
			else
			{
				alp_MarkedActiveQuests = new array< ref alpRegisteredQuest>;
			}

			
			//Print( "POCET MISI " + alp_ActiveQuests.Count() );
			
			foreach( alpRegisteredQuest quest : alp_ActiveQuests )
			{			
				vector pos = Vector(quest.PosX,0,quest.PosY);
				
				alpRegisteredQuest markedquest = new alpRegisteredQuest(quest.NPC, quest.Quest, pos , quest.CurrencyID );
				alp_MarkedActiveQuests.Insert( markedquest );			
							
			}

		}
	
	}	
	void SetMostWanted(int id, alpMostWanted wanted)
	{
		if (!alp_MostWanted)
		{
			alp_MostWanted = new map<int, ref alpMostWanted>;
		}		
		alp_MostWanted.Set(id, wanted);
	} 	
	
	alpTraderQuest GetQuest(int id )
	{
		if ( alp_Quests && id <  alp_Quests.Count() )
		{
			return alp_Quests.Get(id);		
		}		
		return null;	
	}	
	
	array<ref alpTraderQuest> GetQuestByNPC_ID(int npc_id )
	{
		array<int> questsID = GetActiveQuestID( npc_id );
		array<ref alpTraderQuest> quests = new array<ref alpTraderQuest>;
		for( int i = 0; i < questsID.Count();i++){
			quests.Insert(	GetQuest( questsID.Get(i) ) );
		}
		return quests;	
	}		
	
	array<int> GetActiveQuestID( int npc )
	{
		array<int> questsID = new array<int>;
		if ( alp_ActiveQuests ){
			for ( int i = 0 ; i < alp_ActiveQuests.Count(); i++ ){							
				if ( alp_ActiveQuests.Get(i).NPC == npc ) {
					questsID.Insert( alp_ActiveQuests.Get(i).Quest );
				}
			}			
		}		
		return questsID;
	}
	
	vector GetActiveQuestPosition( int npc )
	{
		vector pos = "0 0 0";
		if ( alp_ActiveQuests )
		{
			for ( int i = 0 ; i < alp_ActiveQuests.Count(); i++ )
			{							
				if ( alp_ActiveQuests.Get(i).NPC == npc )
				{
					pos[0] = alp_ActiveQuests.Get(i).PosX;
					pos[2] = alp_ActiveQuests.Get(i).PosY;
					break;
				}
			}			
		}		
		return pos;
	}
	
	int GetActiveQuestCurrency( int npc )
	{
		int questID = -1;
		if ( alp_ActiveQuests )
		{
			for ( int i = 0 ; i < alp_ActiveQuests.Count(); i++ )
			{							
				if ( alp_ActiveQuests.Get(i).NPC == npc )
				{
					questID = alp_ActiveQuests.Get(i).CurrencyID;
					break;
				}
			}			
		}		
		
		return questID;
	}	
	

	int GetTimeStamp(){
		int time = GetGame().GetTime();
		
		if ( GetGame().IsClient() ){
			time+=	m_ServerTimeDelta;
		}
		return time;
	}
	
	
	void SetServerTimeDelta(int time ) {
		m_ServerTimeDelta = time - GetGame().GetTime();
	}
	
	void SaveRegisteredPrivateMissions(){
		alpClientData data = new alpClientData( GetClientTimeStamp() );		
		data.RegisteredPrivateMissions = RegisteredPrivateMissions;		
		JsonFileLoader< alpClientData>.JsonSaveFile(alp_CLIENT_DATA, data );
	}
	
	void LoadRegisteredPrivateMissions(){
		if (!FileExist(alp_CLIENT_DATA	) ){ 	
			alpClientData data;					
			JsonFileLoader< alpClientData>.JsonLoadFile(alp_CLIENT_DATA, data );

			if ( data ) {
				int actualdate = GetClientTimeStamp() - 1;
				int saveddate = data.date;
				if ( saveddate >= actualdate ){
					if ( data.RegisteredPrivateMissions ) {
						for( int i = 0 ; i < data.RegisteredPrivateMissions.Count();i++){
							RegisterPrivateMission( data.RegisteredPrivateMissions.GetKey(i), data.RegisteredPrivateMissions.GetElement(i) );
						}					
					}
				}				
			}			
		}		
			

	}
	
	int GetClientTimeStamp(){
		int y,m,d;
		GetYearMonthDayUTC(y,m,d);
		int date = y * 365 + m * 30 + d;	
		return date;	
	}
}

