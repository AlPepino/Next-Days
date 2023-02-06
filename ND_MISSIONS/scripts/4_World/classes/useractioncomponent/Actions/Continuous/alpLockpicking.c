
class alpLockpickingCB : ActionContinuousBaseCB
{
	
	override void CreateActionComponent()
	{
		float time = GetND().GetRP().GetVehicleOptions().TimeToForceOpen;
		
		m_ActionData.m_ActionComponent = new CAContinuousTime(time);
	}

};

class alpLockpicking: ActionContinuousBase
{
	
	
	
	void alpLockpicking()
	{
		m_CallbackClass = alpLockpickingCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	

		m_ConditionTarget = new CCTNone;
		m_ConditionItem = new CCINonRuined;
	}
		
	override string GetText()
	{
		return "#unlock";
	}

	
	
		
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;
		
		CarScript car;
		CarDoor carDoor; 
		
		Lockpick lockpick = Lockpick.Cast(item);
		
		if (  !GetND().GetRP().GetVehicleOptions().DisableLocpicking && player && Class.CastTo(carDoor, target.GetObject()) && Class.CastTo(car, target.GetParent()) )
		{
			if ( car.GetInventory().IsInventoryLocked() )
			{
				
				
				if ( GetND().GetRP().GetVehicleOptions().DisableLocpickingInTradeZone && player.GetRP().IsInTradeZone() )
				{
					return false;
				}
				
				return true;
			}
				
			else
				return false;

		}
		else return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		
		CarScript car;
		Lockpick lockpick;
		
		if ( Class.CastTo(car, action_data.m_Target.GetParent()) && Class.CastTo(lockpick, action_data.m_MainItem) )
		{
			car.LockVehicleALP( false );	
			
			lockpick.DecreaseHealth("","",GetND().GetRP().GetVehicleOptions().DamageLockpick);	
		}
	
	}
	

	override void OnFinishProgressClient( ActionData action_data )
	{
		CarScript car;
	
		if ( Class.CastTo(car, action_data.m_Target.GetParent()) )
		{

			if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
				SEffectManager.PlaySound("alp_Locking_SoundSet", car.GetPosition() );	
		}
		
	}		

	
	override void OnStartServer( ActionData action_data )
	{
		super.OnStartServer(action_data);
		
		
		CarScript car;
	
		if ( Class.CastTo(car, action_data.m_Target.GetParent()) )
		{
			car.ActivateAlarmSystem();
			car.SetSynchDirty();
			
			
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(car.DisableAlarmSystem,1000);						
			
		}		
	}
	
};
