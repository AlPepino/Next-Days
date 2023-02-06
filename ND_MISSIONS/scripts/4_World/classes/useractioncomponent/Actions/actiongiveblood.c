
modded class ActionGiveBloodSelf: ActionContinuousBase
{
	override void OnEndServer(ActionData action_data)
	{
		ActionGiveBloodData action_data_b = ActionGiveBloodData.Cast( action_data );		
		//cure radiation disease if it stage is lower than 5		

			int radiation = action_data_b.m_Player.GetRP().GetRecievedRadiation();
		
			if (  action_data_b.m_Player.GetRP().GetRecievedRadiation() < ALP_RADPOISON.L5 )
			{
		
		
				if (action_data_b.m_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK1))
				{
					action_data_b.m_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK1);
				}		
		
				if (action_data_b.m_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK2))
				{
					action_data_b.m_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK2);
								
				}			
	
				if (action_data_b.m_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK3))
				{
					action_data_b.m_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK3);
								
				}		
			
				if (action_data_b.m_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK4))
				{
					action_data_b.m_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK4);
								
				}			
			}		
		
				
		
		super.OnEndServer(action_data);
	}
};


modded class ActionGiveBloodTarget: ActionContinuousBase
{

	override void OnEndServer(ActionData action_data)
	{
		ActionGiveBloodData action_data_b = ActionGiveBloodData.Cast( action_data );
		
		PlayerBase player_target = PlayerBase.Cast(action_data_b.m_Target.GetObject());
	
		//cure radiation disease if it stage is lower than 5

			int radiation = action_data_b.m_Player.GetRP().GetRecievedRadiation();
		
			if ( player_target.GetRP().GetRecievedRadiation() < ALP_RADPOISON.L5 )
			{
		
		
				if (player_target.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK1))
				{
					player_target.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK1);
				}		
		
				if (player_target.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK2))
				{
					player_target.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK2);
								
				}			
	
				if (player_target.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK3))
				{
					player_target.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK3);
								
				}		
			
				if (player_target.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK4))
				{
					player_target.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK4);
								
				}			
			}			
		
				
		super.OnEndServer(action_data);
	}
};