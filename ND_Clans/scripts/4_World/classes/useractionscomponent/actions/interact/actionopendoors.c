
modded class ActionOpenDoors: ActionInteractBase
{

	//redone due to compatibility with mods
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		bool condition = super.ActionCondition( player, target, item ); 
		
		if ( !condition && target && IsBuilding(target) )
		{
			Building building;
			if( Class.CastTo(building, target.GetObject()) )
			{
				int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
				if ( doorIndex != -1 )
				{
					if( !IsInReach(player, target, UAMaxDistances.DEFAULT) ) 
						return false;
					
					if ( !building.IsDoorOpen(doorIndex) )
					{
						if ( building.IsDoorLocked(doorIndex) )
						{
							BuildingBase bb = BuildingBase.Cast( building );
							int idPP = player.GetPlayerID();
							if ( bb  && bb.IsEnabledFingerPringLock()  )
							{							
								if ( bb.GetOwnerID() == idPP ||  VerifyClanPermission( player , bb ) )
								{
									return true;	
								}			
							} 				
						}			
					}
					
				}
			}
		}
		return condition;
		
	}

	override void OnStartServer( ActionData action_data )
	{
		BuildingBase building;
		if( Class.CastTo(building, action_data.m_Target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(action_data.m_Target.GetComponentIndex());
			if( doorIndex != -1 )
			{
				if ( building.IsDoorLocked(doorIndex) )
				{
					building.UnlockDoor(doorIndex);
				}
			}
		}
		
		super.OnStartServer(  action_data );
	}

	override void OnStartClient( ActionData action_data )
	{
		BuildingBase building;
		if( Class.CastTo(building, action_data.m_Target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(action_data.m_Target.GetComponentIndex());
			if( doorIndex != -1 )
			{
				if ( building.IsDoorLocked(doorIndex) )
				{
					SEffectManager.PlaySound("alp_UnLockingHouse_SoundSet", action_data.m_Player.GetPosition() );	
					building.UnlockDoor(doorIndex);
				}
			}
		}
		
		super.OnStartClient(  action_data );
	}	
	
	bool VerifyClanPermission( PlayerBase player, BuildingBase building){//.alp_ClanID
		int clanID = player.GetClanID();		
		if ( clanID < 0 ) {
			return false;
		}		
		if ( clanID != building.GetClanID() ) {
			return false;
		}				
		if ( !building.CanUseFingerPrints() ) {
			return false;
		}
		return true;
	}
		
};