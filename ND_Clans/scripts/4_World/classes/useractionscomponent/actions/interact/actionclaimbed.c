
class alpActionClaimBed: ActionInteractBase
{

	
	void alpActionClaimBed()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  {
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

	override string GetText(){
		return "#pp_claim_bed";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (!GetND().GetClans().GetSpawn().EnableSpawnInBase )
		{
			return false;
		}
		
		if ( target && target.GetParent() ) 
		{	
			if (GetGame().IsClient() )
			{
				BuildingBase building;				
				if ( Class.CastTo(building, target.GetParent() ) && building.GetOwnerID() ){	
					alp_PlotPole pp = alpClansPlugin.GetPlotPole( building.GetOwnerID() );
					int pID = player.GetPlayerID();
					int cID = player.GetClanID();	
					
					if ( pp && pp.IsAuthorizedToClaimBed(pID,cID) ){
						int bedIndex = building.GetBedID( target.GetCursorHitPos()  );	
						if ( bedIndex >= 0 ){
							return true;
						}						
					}
					return false;																
				}			
				return false;					
			} else {
				return true;
			}		
		}
		return false;
	}
	
	override void OnEnd( ActionData action_data )		{

		BuildingBase building;
		if ( Class.CastTo(building, action_data.m_Target.GetParent()) )
		{
			int bedIndex = building.GetBedID(action_data.m_Target.GetCursorHitPos()  );//target.GetCursorHitPos() 
			if ( bedIndex >= 0 )
			{
				int pID = action_data.m_Player.GetPlayerID();
				
				if (GetGame().IsServer() )
				{
					action_data.m_Player.GetPlayerHive().SetClaimedBed( building.GetOwnerID(), building.GetStringID(), bedIndex );
					building.ClaimBed( bedIndex ,pID );		
				}				
				
					
				//building.SetSynchDirty();	
			}
		}
		
	}
	

	
};