
class alpActionUnlockDoorsCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(0.5);
	}
};

class alpActionUnlockDoors: ActionContinuousBase
{
	bool alp_Synchronized;	
	
	void alpActionUnlockDoors()
	{
		m_CallbackClass = alpActionUnlockDoorsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursor;
	}
		
	override string GetText()
	{
		return "#unlock - ID:" + alp_DoorIndex.ToString();
	}
	int alp_DoorIndex = -1;
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		alp_DoorIndex = -1;
		if( !target ) return false;
		//if( IsDamageDestroyed(action_data.m_Target) ) return false;
		if( !IsBuilding(target) ) return false;
		if( !IsInReach(player, target, UAMaxDistances.DEFAULT) ) return false;

		
		BuildingBase building;
		if( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 )
			{
				alp_DoorIndex = doorIndex;
				if ( building.IsDoorLocked(doorIndex) )
				{				

					alp_HouseKey_Base key = alp_HouseKey_Base.Cast(item);
					if ( ( key.GetHouseID() == building.GetKeyID() && (key.GetKeyID() == -1 || key.GetKeyID() == doorIndex  ) ) || key.IsAdminKey() )										
					{
						return true;
					}
				}
				return false;			
			}
		}		
		return false;
	}

	protected void UnlockDoor(ActionTarget target, alp_HouseKey_Base key)
	{
		BuildingBase building;

		if ( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 && ( key.IsAdminKey() || key.GetKeyID() == -1 || key.GetKeyID() == doorIndex ) )
			{
				building.UnlockDoor(doorIndex);
			}
		}
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		UnlockDoor(action_data.m_Target, alp_HouseKey_Base.Cast(action_data.m_MainItem) );
	
	}
	override protected void OnStartAnimationLoopClient( ActionData action_data )
	{
		super.OnStartAnimationLoopClient(action_data);
		
		UnlockingClient(action_data.m_Player, action_data.m_Target, alp_HouseKey_Base.Cast(action_data.m_MainItem) );	
		
	}
		
	protected void UnlockingClient(PlayerBase player, ActionTarget target, alp_HouseKey_Base key)
	{
	
		BuildingBase building;

		if ( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 )
			{
				if ( key.IsAdminKey() || key.GetKeyID() == -1 || key.GetKeyID() == doorIndex )
				{
					SEffectManager.PlaySound("alp_UnLockingHouse_SoundSet", player.GetPosition() );	
				}
				else
				{
					SEffectManager.PlaySound("lockpicker_move_out_SoundSet", player.GetPosition() );	
				}
				
			}		
		}	
	}
};