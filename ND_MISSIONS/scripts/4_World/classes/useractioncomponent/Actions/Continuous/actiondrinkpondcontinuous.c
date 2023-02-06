modded class ActionDrinkPondContinuous
{

#ifdef NAMALSK_SURVIVAL	

	override void OnFinishProgressServer( ActionData action_data )
	{
		Param1<float> nacdata = Param1<float>.Cast( action_data.m_ActionComponent.GetACData() );
		float amount = nacdata.param1 * UAQuantityConsumed.DRINK;

		EConsumeType m_WaterSourceType = EConsumeType.ENVIRO_POND;
		vector pos_cursor = action_data.m_Target.GetCursorHitPos();
		string surfType;
		int liquidType;
		g_Game.SurfaceUnderObject(action_data.m_Player, surfType, liquidType);

		if ( liquidType == LIQUID_WATER )
		{
			if ( action_data.m_Player.GetRP().IsRadiationHigh() )
			{
				m_WaterSourceType = alpeConsumeType.ENVIRO_POND_CONTAMINED_FREEZING;
			}
			else
			{
				m_WaterSourceType = EConsumeTypeNamalsk.ENVIRO_FREEZING;
			}
		}
		else if ( ( surfType == "nam_snow" ) || ( surfType == "nam_seaice" ) || ( surfType == "nam_lakeice_ext" ) )
		{
			
			if ( action_data.m_Player.GetRP().IsRadiationHigh() )
			{
				m_WaterSourceType = alpeConsumeType.ENVIRO_SNOW_CONTAMINED_FROZEN;
			}
			else
			{
				m_WaterSourceType = EConsumeTypeNamalsk.ENVIRO_FROZEN;
			}			
		}

		action_data.m_Player.Consume( NULL, amount, m_WaterSourceType );
	}

#else	
	
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		//Print("OnFinishProgressServer");
		Param1<float> nacdata = Param1<float>.Cast( action_data.m_ActionComponent.GetACData() );
		float amount = UAQuantityConsumed.DRINK;
		
		if ( action_data.m_Player.GetRP().IsRadiationHigh() )
		{
			action_data.m_Player.Consume(NULL, amount, alpeConsumeType.ENVIRO_POND_CONTAMINED);
		}
		else
		{
			action_data.m_Player.Consume(NULL, amount, EConsumeType.ENVIRO_POND);
		}
		
	}



#endif		
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		
		if ( GetND().GetRP().GetPlayerOptions().MaskPreventConsume )
		{
			EntityAI mask = player.FindAttachmentBySlotName("Mask");
			
			if ( mask && !IsExceptionsALP(mask) )
				return false;
								
		}
		

		return super.ActionCondition(player, target, item);
	}
}