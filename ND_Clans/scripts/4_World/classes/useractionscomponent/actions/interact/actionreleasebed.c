
class alpActionReleaseBed: ActionInteractBase
{

	void alpActionReleaseBed()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

	override string GetText()
	{
		return "#pp_release_bed";
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
				
				if ( Class.CastTo(building, target.GetParent() ) && building.GetOwnerID()  ){	
					alp_PlotPole pp = alpClansPlugin.GetPlotPole( building.GetOwnerID() );
					if ( pp ){
						int bedIndex = building.GetOccupiedBedID( target.GetCursorHitPos()  );		
						if ( bedIndex >= 0 ){
							return true;
						}						
					}
					return false;																
				}			
				return false;			
			
			}
			else
			{
				return true;
			}
		
		
		}
		return false;

	}
	
	override void OnEnd( ActionData action_data )		
	{
		
		BuildingBase building;
		if ( Class.CastTo(building, action_data.m_Target.GetParent()) )
		{
			int bedIndex = building.GetOccupiedBedID(action_data.m_Target.GetCursorHitPos()  );//target.GetCursorHitPos() 

			if ( bedIndex >= 0 )
			{
				
				
				if (GetGame().IsServer() )
				{
					action_data.m_Player.GetPlayerHive().ReleaseClaimedBed( building.GetOwnerID(), building.GetStringID(), bedIndex );
					building.ReleaseBed( bedIndex );
				}				
				
				
				

			}
		}
		
	}
	

	
};