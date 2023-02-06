
class alpActionLockDoorsCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(0.5);//UATimeSpent.LOCK
	}
};

class alpActionLockDoors: ActionContinuousBase
{

	
	void alpActionLockDoors()
	{
		m_CallbackClass = alpActionLockDoorsCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;
	}
	
	override void CreateConditionComponents()
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTCursor;
	}
		
	override string GetText()
	{
		return "#lock_door - ID:" + alp_DoorIndex.ToString();
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
				
				if (!building.IsDoorOpen(doorIndex) && !building.IsDoorLocked(doorIndex) )
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

	protected void LockDoor(ActionTarget target, alp_HouseKey_Base key)
	{
		BuildingBase building;

		if ( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 && ( key.IsAdminKey() || key.GetKeyID() == -1 || key.GetKeyID() == doorIndex ) )
			{
				building.LockDoor(doorIndex);
			}		
		}
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		LockDoor(action_data.m_Target, alp_HouseKey_Base.Cast(action_data.m_MainItem) );
	}
	
	
	override protected void OnStartAnimationLoopClient( ActionData action_data )
	{
		super.OnStartAnimationLoopClient(action_data);
		
		LockingClient(action_data.m_Player, action_data.m_Target, alp_HouseKey_Base.Cast(action_data.m_MainItem) );		
	}
	
	protected void LockingClient(PlayerBase player, ActionTarget target, alp_HouseKey_Base key)
	{
	
		BuildingBase building;

		if ( Class.CastTo(building, target.GetObject()) )
		{
			int doorIndex = building.GetDoorIndex(target.GetComponentIndex());
			if ( doorIndex != -1 )
			{
				if ( key.IsAdminKey() || key.GetKeyID() == -1 || key.GetKeyID() == doorIndex )
				{
					SEffectManager.PlaySound("alp_LockingHouse_SoundSet", player.GetPosition() );	
				}
				else
				{
					SEffectManager.PlaySound("lockpicker_move_out_SoundSet", player.GetPosition() );	
				}
				
			}		
		}	
	}

	
};