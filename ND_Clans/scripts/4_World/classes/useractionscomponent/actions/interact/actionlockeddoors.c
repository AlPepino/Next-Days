
modded class ActionLockedDoors: ActionInteractBase
{


	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;
		//if( IsDamageDestroyed(action_data.m_Target) ) return false;
		if( !IsBuilding(target) ) return false;
		if( !IsInReach(player, target, UAMaxDistances.DEFAULT) ) return false;

		Building building;
		if( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 )
			{
				if  (building.IsDoorLocked(doorIndex))
				{
					int idPP = player.GetPlayerID();	
					BuildingBase bb = BuildingBase.Cast( building );
					if ( bb  && bb.IsEnabledFingerPringLock() && ( bb.GetOwnerID() == idPP ||  VerifyClanPermission( player , bb ) ) )
					{					

						return false;	
					}
					return true;
				}
								
			}
		}
		return false;
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

