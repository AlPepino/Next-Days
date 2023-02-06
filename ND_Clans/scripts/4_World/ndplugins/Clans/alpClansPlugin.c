class alpPlayerSpawnTime
{
	int LastSpawnInBase;

}



class alpClansPlugin extends alpPlugin
{
	

	ref array<int>								m_ActivedClans;

	
	ref map<int,ref alpPlayerSpawnTime>			alp_PlayersSpawnTime;
	
	ref map<int,PlayerBase>						alp_Players;
	ref map<int,ref alpClanData>				alp_Clans;
	
	ref alpClans_BasisOptions					alp_OptionsClan_Basic;

	
	ref alpClans_Locking						alp_Clans_Locking;
	
	ref alpClansSpawn							alp_ClansSpawnOption;

	ref alpSpawnSettings						alp_SpawnPlayerManagement;	
	
	void ~alpClansPlugin()
	{
		delete alp_PlayersSpawnTime;
		delete alp_Players;
		delete alp_Clans;
		delete alp_OptionsClan_Basic;					
		delete alp_Clans_Locking;	
		delete alp_ClansSpawnOption;	
		delete alp_SpawnPlayerManagement;		
	}
	
	
	override void Init() 
	{
		super.Init();		
		
		m_ActivedClans				= new array<int>;
		
		alp_OptionsClan_Basic  		= new alpClans_BasisOptions;
		
		alp_Clans_Locking  			= new alpClans_Locking;
		
		alp_ClansSpawnOption  		= new alpClansSpawn;
		
		//load file
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() )
		{
			alp_SpawnPlayerManagement = new alpSpawnSettings;
			
			alp_PlayersSpawnTime = new map<int,ref alpPlayerSpawnTime>;
			alp_Players = new map<int,PlayerBase>;
			alp_Clans = new map<int,ref alpClanData>;
			
			if (!FileExist(ALP_CLANS_FOLDER	) ){ 
				MakeDirectory(ALP_CLANS_FOLDER);		
			}			
			
			//Options basic
			if (!FileExist(ALP_CLANS_OPTIONS_FILE	) ){ 			
				JsonFileLoader< alpClans_BasisOptions>.JsonSaveFile(ALP_CLANS_OPTIONS_FILE,  alp_OptionsClan_Basic);
			}
			else {
				JsonFileLoader< alpClans_BasisOptions>.JsonLoadFile(ALP_CLANS_OPTIONS_FILE, alp_OptionsClan_Basic );	
			}
				
			JsonFileLoader< alpClans_BasisOptions>.JsonSaveFile(ALP_CLANS_OPTIONS_FILE,  alp_OptionsClan_Basic);					
			
			//Locking event
			if (!FileExist(ALP_CLANS_LOCKING_FILE	) ){ 			
				JsonFileLoader< alpClans_Locking>.JsonSaveFile(ALP_CLANS_LOCKING_FILE,  alp_Clans_Locking);
			} else {
				JsonFileLoader< alpClans_Locking>.JsonLoadFile(ALP_CLANS_LOCKING_FILE, alp_Clans_Locking );	
			}
				
			JsonFileLoader< alpClans_Locking>.JsonSaveFile(ALP_CLANS_LOCKING_FILE,  alp_Clans_Locking);	

			//Spawn management
			if (!FileExist(ALP_CLANS_SPAWN_FILE	) ){ 			
				JsonFileLoader< alpClansSpawn>.JsonSaveFile(ALP_CLANS_SPAWN_FILE,  alp_ClansSpawnOption);
			} else {
				JsonFileLoader< alpClansSpawn>.JsonLoadFile(ALP_CLANS_SPAWN_FILE, alp_ClansSpawnOption );	
			}
				
			JsonFileLoader< alpClansSpawn>.JsonSaveFile(ALP_CLANS_SPAWN_FILE,  alp_ClansSpawnOption);												
			//update life time		
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater(this.UpdateLifeTimeManager,2000 );		
		}		
	}

		
	
	alpSpawnSettings GetSpawnManagement()
	{
		return alp_SpawnPlayerManagement;
	}
	

	
	
	void UpdateLifeTimeManager()
	{
		if ( GetBases().EnableLifeTimeManagement )
		{		
			GetLifeTimeManager().UpdateLifeTime();
		}
	}
	
	override void OnSpawnManaged( PlayerBase player )
	{
		int playerID = player.GetPlayerID();
		
		alpPlayerSpawnTime spawnTime;
		
		if ( !alp_PlayersSpawnTime.Find( playerID, spawnTime ) )
		{
			spawnTime = new alpPlayerSpawnTime;
			alp_PlayersSpawnTime.Set( playerID, spawnTime );
		}
		
		//alp_PlayersSpawnTime
		
		if ( !GetOptions().EnableClans )
		{
			return;
		}

							
		int clanID = player.GetPlayerHive().GetStore().ClanID;		
		string name = player.GetIdentity().GetName();
		
		alp_Players.Set( playerID, player);
		
		if ( clanID == -1 )
		{
			return;
		}
			
		
		alpClanData clan;
		
		if ( alp_Clans.Find( clanID ,  clan) )
		{
			if ( clan.IsMember( playerID ) )
			{
				clan.SetMemberOnline( playerID );
				SendClanRPC(player, clan );

				player.GetRP().SetClan( clan );
				
				player.SetClanID(clanID);
			}
		}
		else
		{
			clan = alpClanData.GetClan(clanID,playerID,name);
			
			if ( clan )
			{
				clan.MembersOnline.Clear();
				
				clan.SetMemberOnline( playerID );
				SendClanRPC(player, clan );
				alp_Clans.Set( clan.ClanID, clan );											
				
				player.GetRP().SetClan( clan );
				
				player.SetClanID(clanID);
			}
		
		}
		
		if ( !clan )
		{
			player.GetPlayerHive().GetStore().ClanID = -1;
			player.GetPlayerHive().Save(false);
			player.SetClanID(-1);
	
		}
		if ( player.GetClanID() > 0 ) {
			UpdateClansInGame(player.GetClanID());
		}				
	}

	override void OnDeathManaged( PlayerBase player )
	{
		//alpClanData clan = player;	
		if ( GetGame().IsServer() )
		{
			if ( !GetOptions().EnableClans )
				return;		
		
			int playerID = player.GetPlayerID();
			alp_Players.Remove( playerID );
		}	
		
	}
	
	override void OnDisconnectManaged( PlayerBase player )
	{
		if ( !GetOptions().EnableClans ){
			return;
		}
				
		
		int playerID = player.GetPlayerID();
		
		alpClanData clan = player.GetRP().GetClan();	
		
		if ( clan )
		{
			
			if ( clan.RemoveMemberOnline( playerID) )
			{//no membersOnline
				int clanId = clan.ClanID;
				UpdateClansInGame( clanId ,false);
				alp_Clans.Remove( clanId );
			}
			else
			{			
				SendClanRPC(null, clan );
			}
			alp_Players.Remove( playerID );		
		}
		else
		{
			alp_Players.Remove( playerID );
		}
						
	}
	
	
	alpClans_BasisOptions GetOptions()
	{
		return alp_OptionsClan_Basic;
	}
	
	alpClanBasesOptions GetBases()
	{
		return GetND().GetBases();
	}		
	alpClans_Locking GetLocking()
	{
		return alp_Clans_Locking;
	}		
	alpClansSpawn GetSpawn()
	{
		return alp_ClansSpawnOption;
	}			
	
	
	
	override void OnConnectManaged( PlayerBase player )
	{	

		ScriptRPC rpc = GetND().GetInitRPC( GetID() );					

		WriteOnConnectRPC( rpc );
			
		GetND().SendGameRPC( rpc, player );
		
	}	
		
	void WriteOnConnectRPC(ref ScriptRPC rpc)
	{

		rpc.Write( alp_OptionsClan_Basic );
		rpc.Write( GetND().alp_ClanBasesOptions );
		rpc.Write( alp_ClansSpawnOption );
		rpc.Write( m_ActivedClans );
	}	

	
	
	override void ReadInitRPC( PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		super.ReadInitRPC(  sender,  target,  ctx);
		
		ctx.Read( alp_OptionsClan_Basic );		
		ctx.Read( GetND().alp_ClanBasesOptions );		
		ctx.Read( alp_ClansSpawnOption );	
		ctx.Read( m_ActivedClans );
		
		//TEST HOTFIX ESTATES
		//alpClanBasesOptions
		/*
		if ( GetND().alp_ClanBasesOptions && GetND().alp_ClanBasesOptions.PlotPoleTaxes && GetND().alp_ClanBasesOptions.PlotPoleTaxes.Count() == 0  ) {
			GetND().alp_ClanBasesOptions.InitDefault();
		}
		*/
	}		
	
	override void ReadSyncRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{
		int rpc;

		ctx.Read( rpc );

	
		switch ( rpc )
		{
			case ALP_RPC_PLUGIN_CLANS.CREATENEWCLAN:
			{//Server
				CreateNewClan( PlayerBase.Cast( target), ctx );
				break;
			}		
			case ALP_RPC_PLUGIN_CLANS.DISBAND_CLAN:
			{//Server
				int clanDisband;
				ctx.Read( clanDisband );
				DisbandClan(alp_Clans.Get(clanDisband) );
				break;
			}	
			case ALP_RPC_PLUGIN_CLANS.LEAVE_CLAN:
			{//Server
				LeaveClan(PlayerBase.Cast( target) ,  ctx );
				break;
			}	
			case ALP_RPC_PLUGIN_CLANS.KICK_HIM:
			{//Server
				KickHim(PlayerBase.Cast( target) ,  ctx );
				break;
			}									
			case ALP_RPC_PLUGIN_CLANS.SEND_CLAN_TO_CLIENT:
			{//client 
				RecievedClan(  ctx );
				break;
			}		
			case ALP_RPC_PLUGIN_CLANS.UPDATE_ONLINE_MEMBERS:
			{//client 
				UpdateOnlineMembers(  ctx );
				break;
			}		
			case ALP_RPC_PLUGIN_CLANS.MATE_POSITION:
			{//client 
				UpdateMatePosition(  ctx );
				break;
			}	
			case ALP_RPC_PLUGIN_CLANS.SYNC_PLOTPOLE://sync budov
			{//client  + server ?
				SyncPlotpole(  ctx );
				break;
			}		
			case ALP_RPC_PLUGIN_CLANS.SET_CLAN_ID://sync clan ID on client
			{//client
				SetClanID(  ctx );
				break;
			}											
		}
				
	}	

	
	void SendRPC_VerifyClanID( int clanID, bool connect  )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetID() );
		rpc.Write( ALP_RPC_PLUGIN_CLANS.SET_CLAN_ID );	
		rpc.Write( clanID );
		rpc.Write( connect );	
		GetND().SendGameRPC( rpc, null, true, true, true );	
	}	
	void SetClanID(  ParamsReadContext ctx ){
		int id;
		bool connect;
		ctx.Read( id );	
		ctx.Read( connect );	
		UpdateClansInGame(id,connect);				
	}
		
	void SyncPlotpole(  ParamsReadContext ctx )
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player )
		{
			int id;
			Param7<int,int,int,int,int,int,int> values;
			ctx.Read( id );	
			ctx.Read( values );	
			
			BuildingBase b = player.alp_PlotPoleManage.GetBuilding(id);
			
			if ( b ) {
				b.SetEstateValues( values );
			
			}
		
		}
	}		
		
	void UpdateOnlineMembers(  ParamsReadContext ctx )
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player )
		{
			alpClanData clan = player.GetRP().GetClan();	
			
			if (clan )
			{
				
				ctx.Read( clan.MembersOnline );	
			
			}
		
		}
	}		
	void UpdateMatePosition(  ParamsReadContext ctx )
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player )
		{
			alpClanData clan = player.GetRP().GetClan();	
			
			if (clan )
			{
				Param3<int,float,float> position;
				ctx.Read( position );	
				
				Print("POZICE HRACE " + position.param1 );
				Print("x " + position.param2 );
				Print("y " + position.param3 );
			}
		
		}
	}	
		
	void RecievedClan(  ParamsReadContext ctx )
	{
		alpClanData clan;
		ctx.Read( clan );

		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player )
		{
			player.GetRP().SetClan( clan );
		}		

	}		
	void CreateNewClan( PlayerBase player , ParamsReadContext ctx )
	{
		string name;
		ctx.Read( name );
		int playerID = player.GetPlayerID();
		alpClanData clan = new alpClanData( playerID , name, player.GetIdentity().GetName() );
		
		player.GetPlayerHive().GetStore().ClanID = clan.ClanID;
		player.GetPlayerHive().Save( false );

		clan.SetMemberOnline( playerID );
		SendClanRPC(player, clan );
		
		alp_Clans.Set( clan.ClanID, clan );															
		player.GetRP().SetClan( clan );		
		
		player.SetClanID(clan.ClanID);
		//update clan in game
		if ( player.GetClanID() > 0 ) {
			UpdateClansInGame(clan.ClanID);
		}			
	}
	
	
	void CreateNewClanRPC(PlayerBase player , string name)
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetClans().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_CLANS.CREATENEWCLAN );	

		rpc.Write( name );	
		
		GetND().SendGameRPC( rpc, player );	
		
			
	}	
	
	void DisbandClanRPC(PlayerBase player , int clanID )
	{

		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetClans().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_CLANS.DISBAND_CLAN );	

		rpc.Write( clanID );	
		
		GetND().SendGameRPC( rpc, player );	
			
	}		
	void LeaveClanRPC(PlayerBase player , int clanID )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetClans().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_CLANS.LEAVE_CLAN );	

		rpc.Write( clanID );	
		
		GetND().SendGameRPC( rpc, player );	
			
	}	
	
	void KickHimRPC(PlayerBase player , int clanID , int playerID )
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetClans().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_CLANS.KICK_HIM );	

		rpc.Write( clanID );	
		rpc.Write( playerID );	
		GetND().SendGameRPC( rpc, player );	
			
	}
			
	void AddMember( PlayerBase player, alpClanData clan)
	{
		int id = player.GetPlayerID();
		string name = player.GetIdentity().GetName();
		
		clan.AddMember( id, name );
		
		player.GetPlayerHive().GetStore().ClanID = clan.ClanID;
		player.GetPlayerHive().Save( false );
		player.GetRP().SetClan( clan );
		
		player.SetClanID(clan.ClanID);
		
		SendClanRPC(null,clan);
		
	}
	

	
	void DisbandClan(alpClanData clan)
	{

		SendClanRPC(null,clan,true);
		
		clan.Delete();
		
		int clanID = clan.ClanID;
		
		alp_Clans.Remove( clanID );	
		
		//update clan in game
		UpdateClansInGame(clanID,false);			
	}
	
	void LeaveClan(PlayerBase player , ParamsReadContext ctx )
	{
		int clanID;
		ctx.Read( clanID );
		
		alpClanData clan = alp_Clans.Get( clanID );
		
		SendClanRPC(player,clan,true);
			
	}		
	void KickHim(PlayerBase player , ParamsReadContext ctx )
	{
		int clanID, playerID;
		ctx.Read( clanID );
		ctx.Read( playerID );
		alpClanData clan = alp_Clans.Get( clanID );
		PlayerBase p;
		
		if ( alp_Players.Find( playerID, p ) )
		{
			
			SendClanRPC(p,clan,true);
			GetND().GetNotf().SendMessage( p, ALPMSTYPE.SMPERSONAL, "#ip_kickedfromfromclan " + clan.Name );
		}
		else
		{
			clan.RemoveMember( playerID );
			SendClanRPC(null,clan);
		}
		
			
	}		
	void SendClanRPC(PlayerBase player, alpClanData clan , bool kickHim = false)
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetClans().GetID() );
		
		rpc.Write( ALP_RPC_PLUGIN_CLANS.SEND_CLAN_TO_CLIENT );	

		PlayerBase p;
		
		if (!player)
		{//send to all members
			if ( kickHim )
			{
				rpc.Write( null );	
			}
			else
			{
				rpc.Write( clan );	
			}
			
			array<int> members = clan.MembersOnline;
			
			for(int i ; i < members.Count();i++)
			{
				if ( alp_Players.Find( members.Get(i) , p ) )
				{
					if ( p )
					{
						GetND().SendGameRPC( rpc, p );	
						
						if ( kickHim )
						{
							p.GetPlayerHive().GetStore().ClanID = -1;
							p.GetPlayerHive().Save(false);
							p.GetRP().SetClan(null);
							
							p.SetClanID(-1);
							
							GetND().GetNotf().SendMessage( p, ALPMSTYPE.SMPERSONAL, "#ip_kickedfromfromclan " + clan.Name );
						}						
					}

				}
			}
		
		}
		else
		{//jen hrac, zbytek jen update clenu vyjma kopance
			int pID = player.GetPlayerID();
			
			ScriptRPC rpc2 = GetND().GetSyncRPC( GetND().GetClans().GetID() );
			
			if ( kickHim )
			{
				player.GetPlayerHive().GetStore().ClanID = -1;
				player.GetPlayerHive().Save(false);				
				player.GetRP().SetClan(null);
				
				player.SetClanID(-1);
				
				clan.RemoveMember( pID );
				
				
				
				rpc.Write( null );	
				
				rpc2.Write( ALP_RPC_PLUGIN_CLANS.SEND_CLAN_TO_CLIENT );	
				rpc2.Write( clan );					
			}
			else
			{
				rpc2.Write( ALP_RPC_PLUGIN_CLANS.UPDATE_ONLINE_MEMBERS );	
				rpc2.Write( clan.MembersOnline );						
				
				rpc.Write( clan );	
			}
			
			GetND().SendGameRPC( rpc, player );		
			
			
			//update online members
			
			array<int> members2 = clan.MembersOnline;
			
			for(int x ; x < members2.Count();x++)
			{
				if ( pID != members2.Get(x) )
				{
					if ( alp_Players.Find( members2.Get(x) , p ) )
					{
						if ( p )
						{
							GetND().SendGameRPC( rpc2, p );	
						}
						
					}				
				}


			}			
		}
			
	
	}
	
	void SendPostionToClanMate( alpClanData clan , int playerID, float x, float y)
	{
		ScriptRPC rpc = GetND().GetSyncRPC( GetND().GetClans().GetID() );
		rpc.Write( ALP_RPC_PLUGIN_CLANS.MATE_POSITION );	
		array<int> members = clan.MembersOnline;
		
		Param3<int,float,float> position = new Param3<int,float,float>(playerID,x,y); 
		rpc.Write( position );	
		
		PlayerBase player;
		
		for(int i = 0; i < 	members.Count();i++)
		{
			player = alp_Players.Get( members.Get(i) );
			
			if ( player )
			{
				GetND().SendGameRPC( rpc, player );	
			}				
		}
	}
	
	void SendAlertMessage( vector pos, int playerID, int clanID )
	{

		
		PlayerBase p = alp_Players.Get( playerID );
		
		if ( p )
		{
			GetND().GetNotf().SendRaidAlert(p, ALPMSTYPE.MMPERSONAL, pos );
		}				

		alpClanData clan = alp_Clans.Get( clanID );
		
		if ( clan )
		{
			for(int i=0;i<clan.MembersOnline.Count();i++)
			{
				if ( playerID != clan.MembersOnline.Get(i) )
				{
					 p = alp_Players.Get( clan.MembersOnline.Get(i) );
					if ( p )
					{
						GetND().GetNotf().SendRaidAlert(p, ALPMSTYPE.MMPERSONAL, pos );
					}
				}
			}
		
		}
		
	
		
	}
	
	bool IsClanInGame(int id){
	 	if ( m_ActivedClans && m_ActivedClans.Find( id ) != -1 ){
			return true;
		}
		return false;
	}
	bool IsPlayerInGame(int id){
		if ( ClientData.m_PlayerList && ClientData.m_PlayerList.m_PlayerList ){
			for(int i = 0; i < ClientData.m_PlayerList.m_PlayerList.Count() ;i++ ){
				SyncPlayer player = ClientData.m_PlayerList.m_PlayerList.Get(i);
				if ( player.m_PlayerUniqueID == id ) {
					return true;
				}
			}
		}
		return false;
	}	
	
	void UpdateClansInGame( int cID, bool connect = true)
	{
		if ( cID < 1 ){
			return;	
		} 
		//pripojeni, odeslu pouze zmeny
		bool update = false;
		if ( connect ) {
			if ( m_ActivedClans.Find( cID ) == -1 ) {//request update
				m_ActivedClans.Insert( cID );	
				update = true;
			}
		} else {
			if ( m_ActivedClans.Find( cID ) != -1 ) {//request update
				m_ActivedClans.Remove( cID );
				update = true;
			}				
		}
		if ( GetGame().IsServer() && update ) {
			SendRPC_VerifyClanID( cID, connect );			
		}
	}	
	
	static alp_PlotPole GetPlotPole(int id)
	{
		alp_PlotPole pp;
		
		foreach (EntityAI ent : ClientData.PlotPoleList)
		{
			pp = alp_PlotPole.Cast(ent);								

			if (pp && pp.alp_OwnerID == id )
			{
				break;
			}				
			pp = null;		
		}
	
		return pp;
	}

	
	/*
	static vector GetBedLocation(int house, int bed , int playerID)
	{
		vector pos = "0 0 0";
		BuildingBase bulding = GetOwnedBuilding( house );	
		if ( bulding && bulding.GetEstate().RoomMates[bed] == playerID ){
			pos = bulding.GedBedLocation( bed );	
		}
		
		return pos;
	}	
	*/

	static BuildingBase GetOwnedBuilding( string id ) {
		for ( int i = 0; i < ClientData.EstateList.Count(); i++ ){
			BuildingBase b = BuildingBase.Cast( ClientData.EstateList.Get( i ) );
			if ( b && b.GetStringID() == id ) {
				return b;
			}
		}
		return null;
	}	
		
	
	static void ReleaseBed(int ppID, string house, int bed , int playerID )
	{
		BuildingBase bulding = GetOwnedBuilding( house );
		
		if ( bulding ) {
			bulding.ReleaseOldBed( bed, playerID );	
		}
		
	}
	
	static vector GetBedLocation(int ownerID, string houseID, int bedID , int pID, int clanID )
	{
		vector pos = "0 0 0";
		
		BuildingBase bulding = GetOwnedBuilding( houseID );
		if ( bulding && bulding.GetOwnerID() && bulding.GetEstate().RoomMates[bedID] == pID && ( bulding.GetOwnerID() == pID || bulding.GetClanID() == clanID )) {
			pos = bulding.GedBedLocation( bedID );	
		}
		return pos;
	}	
	
	
	bool CanSpawnInBase(int playerID)
	{
		int time = g_Game.GetTime();

		alpPlayerSpawnTime spawnTime = alp_PlayersSpawnTime.Get(playerID);
		
		if ( spawnTime )
		{
			int last_spawn = spawnTime.LastSpawnInBase;
			
			if ( last_spawn )
			{
				last_spawn += GetSpawn().SpawnInBaseCoolDown * 1000;		
				
				if ( time >= last_spawn )
				{
					spawnTime.LastSpawnInBase = time;
					return true;
				}	
				return false;
			}
			else
			{//first dead on server
				spawnTime.LastSpawnInBase = time;			
				return true;
			}
		}
		
		return false;
	}	

	
}
