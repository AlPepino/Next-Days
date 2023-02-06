modded class ActionCloseDoors: ActionInteractBase
{
	override void OnExecute( ActionData action_data )
	{
		
		super.OnExecute(action_data);

		BuildingBase building;
		
		if( Class.CastTo(building, action_data.m_Target.GetObject()) )
		{
			int idPP = action_data.m_Player.GetPlayerID();
			
			int doorIndex = building.GetDoorIndex(action_data.m_Target.GetComponentIndex());
			
			if( doorIndex != -1 && building.IsEnabledFingerPringLock() && ( idPP == building.GetOwnerID() ||  VerifyClanPermission( action_data.m_Player , building ) ) )
			{
				building.LockDoor(doorIndex);
				
				if (GetGame().IsClient())
					SEffectManager.PlaySound("alp_LockingHouse_SoundSet", action_data.m_Player.GetPosition() );	
			}
		}		
				
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