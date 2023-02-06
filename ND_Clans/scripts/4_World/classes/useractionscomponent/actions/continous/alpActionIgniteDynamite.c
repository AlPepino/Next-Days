class alpActionIgniteDynamiteCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime( 3 ); //UATimeSpent.FIREPLACE_IGNITE
	}
}

class alpActionIgniteDynamite: ActionContinuousBase
{
	void alpActionIgniteDynamite()
	{
		m_CallbackClass = alpActionIgniteDynamiteCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_STARTFIRE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH;
		
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
		m_ConditionItem = new CCINonRuined;
	}
		
	override string GetText()
	{
		return "#ignite";
	}

	override bool CanBePerformedFromQuickbar()
	{
		return true;
	}
	


	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
	
		ItemBase target_item = ItemBase.Cast( target.GetObject() );
		
		if ( target_item && item &&  item.CanIgniteItem( target_item ) )
		{

			alp_Dynamite_Base grenade = alp_Dynamite_Base.Cast(target_item);
			if( grenade && grenade.IsPinned() )
			{
				return true;	
			}			
				

		}
		
		return false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		//ItemBase target_item = ItemBase.Cast( action_data.m_Target.GetObject() );
		ItemBase item = action_data.m_MainItem;
		
		alp_Dynamite_Base grenade = alp_Dynamite_Base.Cast( action_data.m_Target.GetObject() );
		if( grenade )
		{
			grenade.Unpin();
			grenade.Activate();
			
			if ( item )
			{
				item.OnIgnitedTarget( grenade );	
			}
		}		
		

	}
	

}