


// Script File

modded class PlayerBase extends ManBase
{
	
	//PlotPole
	ref alpAuthorize										alp_Authorize;	
	alp_PlotPole											alp_PlotPoleManage;
	
	int alp_ClanID = -1;
	
	float												alp_Time;
	const float											ALP_TIMEFORCHECKMESSAGES = 1.0;		
	vector												alp_LastKnownPosition = "0 0 0";	
	
	override void Init(){
		super.Init();
		
		RegisterNetSyncVariableInt("alp_PlayerID");	
		RegisterNetSyncVariableInt("alp_ClanID");	
		
		alp_Authorize 	= new alpAuthorize(this);		
	}	
	
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick( deltaTime );		
		
		if ( GetGame().IsClient() && IsControlledPlayer() && IsAlive() )
		{
			alp_Time += deltaTime;
			if (alp_Time >= ALP_TIMEFORCHECKMESSAGES)
			{
				CheckPlotPole();
			}		
		}
	/*
		if ( GetND().GetClans().GetOptions().EnableClans )		
		{//show players in map
			alpClanData clan = GetRP().GetClan();
			if ( GetGame().IsServer() && GetGame().IsMultiplayer() && clan  )
			{
				alp_Time += deltaTime;
			
				if ( alp_Time > 3 && GetRP().HasPDA() )								
				{
					alp_Time = 0;
					
					vector pos = GetPosition();
					pos[1] = 0;
					
					if ( alpUF.VectorDistance( pos , alp_LastKnownPosition ) > 5 ) 
					{
						alp_LastKnownPosition = pos;
						
						float x,y;
						
						x = pos[0];
						y = pos[2];
						
						GetND().GetClans().SendPostionToClanMate(clan, GetPlayerID(), x, y );
						//Print("Tvoje Pozice je " + alp_LastKnownPosition );
					}
																				
				}
			}							
		
		}
	*/

	}	
	
	
	override int GetClanID(){
		return alp_ClanID;
	}
		
	int GetPlayerID(){
		return alp_PlayerID;
	}
	
	void SetClanID(int id ){
		alp_ClanID = id;
	}

	bool IsAuthorized(ItemBase item){
		return alp_Authorize.IsAuthorized(item);
	}
	
	bool IsAuthorized(){
		return alp_Authorize.IsAuthorized();
	}	
	

	
	override void SetActionsRemoteTarget( out TInputActionMap InputActionMap){		
		super.SetActionsRemoteTarget(InputActionMap);	
		AddAction(alpAddFriendAction);
		AddAction(alpActionClaimBed);
		AddAction(alpActionReleaseBed);
	}	

	
	void CheckPlotPole(){//client only

		float	dist;
		
		int 	pID,cID;	
		pID = GetPlayerID();
		cID = GetClanID();		
		int 	id = GetPlayerID();		
		int     r;

		bool home;
		
		foreach (EntityAI ent : ClientData.PlotPoleList){
			alp_PlotPole pp = alp_PlotPole.Cast(ent);
								
			if (pp){
				if (pp.alp_Radius ){
					dist = alpUF.VectorDistance(pp.GetPosition(), GetPosition());					
					r = pp.GetRadius();					
					//check home status
					if ( pp.IsAuthorized(pID,cID) && dist <= r ){
						home = true;
					}
					
					if ( dist <= r && !pp.alp_AlertMessage ) {
						//message
						if ( pp.IsAuthorized(pID,cID) ) {
							GetHudALP().SendMessageALP(ALPMSTYPE.SMPERSONAL,"#pp_welcome_home");
						}
						if ( !pp.IsAuthorized(pID,cID)  && !GetND().GetClans().GetBases().DisableNotfYouAreInEnemyTerritory ){
							GetHudALP().SendMessageALP(ALPMSTYPE.SMPERSONAL,"#pp_you_are_in_enemy_territory");
						}						
						pp.alp_AlertMessage = true;	
					}
					if ( dist > r && pp.alp_AlertMessage) {
						//message
						if ( pp.IsAuthorized(pID,cID) && pp.alp_OwnerID > 0) {
							GetHudALP().SendMessageALP(ALPMSTYPE.SMPERSONAL,"#pp_you_left_home");							
						}
						if ( !pp.IsAuthorized(pID,cID) && pp.alp_OwnerID > 0 && !GetND().GetClans().GetBases().DisableNotfYouAreInEnemyTerritory) {
							GetHudALP().SendMessageALP(ALPMSTYPE.SMPERSONAL,"#pp_you_left_enemy_territory");
						}						
						pp.alp_AlertMessage = false;						
					}
				}
			}
		}	
		if (home) {//disable home status 			
			if ( GetND().GetClans().GetOptions().Enable3rdPersonCameraAtHome ) {
				GetRP().SetHome( true , true );									
			} else {
				if ( IsInVehicle() )
					GetRP().SetHome( true , true );	
				else
					GetRP().SetHome( true , false );	
			}			
		} else {
			if ( GetND().GetClans().GetOptions().Enable3rdPersonCameraAtSafeZone ) {
				if ( IsInVehicle() )
					GetRP().SetHome( false , true );	
				else
					GetRP().SetHome( false , GetSyncData().GetElement( alpRPelements.ISINTRADERZONE ).GetValue() );											
			} else {
				if ( IsInVehicle() )
					GetRP().SetHome( false , true );	
				else
					GetRP().SetHome( false , false );	
			}						
		}
	}			
	
	Hud GetHudALP()
	{
		Hud hud;
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if (player)
		{
			return player.m_Hud;
		}
		return null;
	}			
	
	bool IsPossibleFillBottle()
	{
		if (m_Environment && m_Environment.IsInShelter() )
		{
			return false;
		}
		return true;
	}
				
}