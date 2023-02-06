class alpLockVehicleCB : ActionContinuousBaseCB
{

	
	override void CreateActionComponent()
	{
		float time = 0.5;
		
		m_ActionData.m_ActionComponent = new CAContinuousTime(time);
	}
	
};

class alpLockVehicle: ActionContinuousBase
{
	void alpLockVehicle()
	{
		m_CallbackClass = alpLockVehicleCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}
	
	override void CreateConditionComponents()  
	{	

		m_ConditionTarget = new CCTNone;
		m_ConditionItem = new CCINonRuined;
	}
		
	override string GetText()
	{
		return "#key_lock";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		CarScript car;
		CarDoor carDoor; 
		alp_CarKey_Base key = alp_CarKey_Base.Cast(item);
		
		if (  player && !player.GetCommand_Vehicle() && Class.CastTo(carDoor, target.GetObject()) && Class.CastTo(car, target.GetParent()) )
		{
			if ( car.GetInventory().IsInventoryUnlocked() )
			{
				if ( key.GetAlpKeyID() == car.GetAlpCarID() || key.IsAdminKey() )
				{
					//key.GetAlpKeyID = car.GetAlpCarID();
					return true;
				}
				else 
					return false;
			}
				
			else
				return false;

		}
		else return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{	
		
		CarScript car;
		
		
		if ( Class.CastTo(car, action_data.m_Target.GetParent()) )
		{
			car.LockVehicleALP( true );
			/*
			car.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
			car.alp_Lock = true;
			
			if ( GetND().GetRP().GetVehicleOptions().IndestructibleLockedVehicle )
			{

				car.SetAllowDamage( false );	
			}
			*/			
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

};
