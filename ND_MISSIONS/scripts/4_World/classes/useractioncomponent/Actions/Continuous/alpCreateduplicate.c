class alpCreateDuplicateCB : ActionContinuousBaseCB
{
	
	override void CreateActionComponent()
	{
		float time = 45;
		
		m_ActionData.m_ActionComponent = new CAContinuousTime(time);
	}

};

class alpCreateDuplicate: ActionContinuousBase
{
	void alpCreateDuplicate()
	{
		m_CallbackClass = alpCreateDuplicateCB;
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
		return "#key_createduplicate";
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;
		
		CarScript car;
		alp_CarKey key = alp_CarKey.Cast(item);
		
		if (  player && Class.CastTo(car, target.GetObject()) && key.GetAlpKeyID() < 1 )
		{
			if ( car.GetInventory().IsInventoryUnlocked() && car.GetAlpCarID() != 0 )
			{
				int componentIndex = target.GetComponentIndex();
				
				array<string> selections = new array<string>();
				
				car.GetActionComponentNameList( componentIndex, selections );
				
				for ( int i = 0; i < selections.Count(); i++ )
				{
					if ( car.CanReachSeatFromDoors(selections[i], player.GetPosition(), 1.0) )
					{
						if ( GetND().GetRP().GetVehicleOptions().DisableKeyDuplicationInTradeZone && player.GetRP().IsInTradeZone() )
						{
							return false;
						}
						return true;
					}						
				}
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
		alp_CarKey key;
		
		if ( Class.CastTo(car, action_data.m_Target.GetObject()) && Class.CastTo(key, action_data.m_MainItem) )
		{
			key.SetAlpKeyID( car.GetAlpCarID() );
			
			key.SetSynchDirty();
		}
			
	}
	

	

};
