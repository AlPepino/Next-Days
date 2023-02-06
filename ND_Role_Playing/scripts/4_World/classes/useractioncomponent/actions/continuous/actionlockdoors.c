modded class ActionLockDoors: ActionContinuousBase
{


	override void OnFinishProgressServer( ActionData action_data )
	{
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{
			LockDoor(action_data.m_Target);
			
			//Damage the Lockpick
			//float dmg = action_data.m_MainItem.GetMaxHealth() * 0.04; //Multiply max health by 'x' amount depending on number of usages wanted (0.04 = 25)
			
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
			
			float skillLevel = action_data.m_Player.GetSoftSkillsManager().GetSpecialtyLevelSoft();
			float appliedDamage = 5 + 2*skillLevel; 
			MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, appliedDamage);			
			
		}	
		else 
		{
			super.OnFinishProgressServer( action_data );
		}
		
	}
};