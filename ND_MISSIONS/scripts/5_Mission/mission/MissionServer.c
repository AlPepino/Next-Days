//nextDays

modded class MissionServer extends MissionBase
{
	//ref array<string> alp_PlayerRegister;
	
	override void OnInit(){

		super.OnInit();
		alpND_base.alp_PlayerRegister = new array<string>;
	}
		
	
	override void OnMissionStart(){
		super.OnMissionStart();
					
		GetND().OnStart();		
		
		
	}	
	
	
	override void OnUpdate(float timeslice){
		super.OnUpdate(timeslice);

		GetND().OnUpdate( timeslice );	
	}	
	
		
	
	override void OnMissionFinish(){
		super.OnMissionFinish();
		
		GetND().OnFinish();
		if ( alpND_base.alp_PlayerRegister ){
			alpND_base.alp_PlayerRegister.Clear();
		}
	}	

	
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity){
		super.InvokeOnConnect(player,identity);
		PlayerConnectALP(identity, player);					
	}

	override void OnClientReconnectEvent(PlayerIdentity identity, PlayerBase player){
		super.OnClientReconnectEvent(identity, player);
		PlayerConnectALP(identity, player);
	}	
	
	override void OnClientRespawnEvent(PlayerIdentity identity, PlayerBase player){
		super.OnClientRespawnEvent(identity, player);
		PlayerConnectALP(identity, player);		
	}	
	

	override void OnClientReadyEvent(PlayerIdentity identity, PlayerBase player){
		super.OnClientReadyEvent( identity,  player);
		PlayerConnectALP(identity, player);			
	}	

	override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx){
		PlayerBase player = super.OnClientNewEvent( identity, pos, ctx );		
		if ( player ){
			player.SetPlayerSpawn( true );	
		}		
		return player;		//m_player
	}			

	override void OnClientDisconnectedEvent(PlayerIdentity identity, PlayerBase player, int logoutTime, bool authFailed){	
		PlayerDisconnectALP(identity, player);
		super.OnClientDisconnectedEvent( identity, player, logoutTime, authFailed);
	}		
	
	void PlayerConnectALP(PlayerIdentity identity, PlayerBase player){
		if ( player ){	
			if ( identity ){
				string guid = identity.GetPlainId();
					
				if ( alpND_base.alp_PlayerRegister.Find( guid ) == -1 ){				
					alpND_base.alp_PlayerRegister.Insert( guid );
					GetND().OnConnect( player );	
				} else {//check if the data exists
					GetND().GetMS().SendRPC_VerifyClientData( player );
				}
				
				//Print("HRAC se připojil " + guid );
			}	
			GetND().OnSpawn( player );								
		}	
	} 				
	
	void PlayerDisconnectALP(PlayerIdentity identity, PlayerBase player){
		if ( player ){	
			if ( identity ){
				string guid = identity.GetPlainId();
				alpND_base.alp_PlayerRegister.RemoveItem( guid );
				//Print("HRAC se odpojil " + guid );
			}
			GetND().OnDisconnect( player );			
		}	
				
	} 		
	
	
		
}