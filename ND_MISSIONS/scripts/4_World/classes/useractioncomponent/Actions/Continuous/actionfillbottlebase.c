

modded class ActionFillBottleBase: ActionContinuousBase
{

#ifdef NAMALSK_SURVIVAL	
	protected float m_TargetWet = 2.0;

	override int GetLiquidType( PlayerBase player, ActionTarget target, ItemBase item )
	{
		// liquid sources on objects
		if (target.GetObject() && (target.GetObject().IsWell()))
		{
			// wells do not have ice nor freezing water
			m_TargetWet = 0.0;
			
			if  ( player.GetRP().IsRadiationHigh() )
			{
				return LIQUID_RADIOACTIVEWATER; //LIQUID_WATER;  LIQUID_RADIOACTIVEWATER
			}
			else
			{
			
				return LIQUID_WATER; 
			}			
			
		} 
		if (target.GetObject() && target.GetObject().IsFuelStation())
		{
			// gas is also just fine (freezing point different than water (-40C), lets not complicate things more)
			m_TargetWet = 0.0;
			return LIQUID_GASOLINE;
		}

		// liquid sources on surface
		vector pos_cursor = target.GetCursorHitPos();
		string surface_type = "";
		GetGame().SurfaceGetType(pos_cursor[0], pos_cursor[2], surface_type);
		switch (surface_type) 
		{
			case "nam_seaice":
			case "nam_lakeice_ext":
			case "nam_snow":
			{
				m_TargetWet = 3.0;
				if  ( player.GetRP().IsRadiationHigh() )
				{
					return LIQUID_RADIOACTIVEWATER; //LIQUID_WATER;  LIQUID_RADIOACTIVEWATER
				}
				else
				{
				
					return LIQUID_WATER; 
				}
				break;
			}
			case "nam_lakewater_ext":
			{
				m_TargetWet = 2.0;
				if  ( player.GetRP().IsRadiationHigh() )
				{
					return LIQUID_RADIOACTIVEWATER; //LIQUID_WATER;  LIQUID_RADIOACTIVEWATER
				}
				else
				{
				
					return LIQUID_WATER; 
				}
				break;
			}
			default:
			{
				return -1;
			}
		}
		return -1;
	}	
	
#else	
	override int GetLiquidType( PlayerBase player, ActionTarget target, ItemBase item )
	{
		vector pos_cursor = target.GetCursorHitPos();		
		CCTWaterSurface waterCheck = new CCTWaterSurface(UAMaxDistances.DEFAULT, UAWaterType.FRESH);
		
		if ( ( waterCheck.Can(player, target) || (target.GetObject() && target.GetObject().IsWell()) ) &&  Liquid.CanFillContainer(item, LIQUID_WATER )  )
		{
			if  ( player.GetRP().IsRadiationHigh() )
			{
				return LIQUID_RADIOACTIVEWATER; //LIQUID_WATER;  LIQUID_RADIOACTIVEWATER
			}
			else
			{
			
				return LIQUID_WATER; 
			}
		}
		else if ( target.GetObject() && target.GetObject().IsFuelStation() && Liquid.CanFillContainer(item, LIQUID_GASOLINE ) )
		{
			return LIQUID_GASOLINE;
		}
		
		return -1;
	}
#endif		
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Well well;
		FuelStation station;
		
		if ( GetND().GetResources().GetOptions().EnableWellManagement &&  Class.CastTo( well, target.GetObject() )  && GetGame().IsServer() && !well.HasWaterALP() ) 
		{		
			return false;	
		}
		else if ( GetND().GetResources().GetOptions().EnableFuelstationManagement && Class.CastTo( station, target.GetObject() )  && GetGame().IsServer() && !station.HasFuelALP()  )
		{
			return false;
		}
		
		return super.ActionCondition(  player,  target,  item );
	}
	
	override bool ActionConditionContinue( ActionData action_data )
	{
		Well well;
		FuelStation station;
		
		if ( GetND().GetResources().GetOptions().EnableWellManagement && Class.CastTo( well, action_data.m_Target.GetObject() )  && GetGame().IsServer() && !well.HasWaterALP() ) 
		{		
			return false;	
		}
		else if ( GetND().GetResources().GetOptions().EnableFuelstationManagement && Class.CastTo( station, action_data.m_Target.GetObject() )  && GetGame().IsServer() && !station.HasFuelALP() )
		{
			return false;	
		}
		return super.ActionConditionContinue(action_data ) ;
	}
	
	
	override void OnStartServer(ActionData action_data)
	{
		
		super.OnStartServer(action_data);
		Well well;
		if ( GetND().GetResources().GetOptions().EnableWellManagement && Class.CastTo( well, action_data.m_Target.GetObject() )  ) 
		{
			well.SaveCurrentAmmount();
		}

		FuelStation station;
		if ( GetND().GetResources().GetOptions().EnableFuelstationManagement &&  Class.CastTo( station, action_data.m_Target.GetObject() )  ) 
		{
			station.SaveCurrentAmmount();
		}			
	}
	
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		Well well;
		if ( GetND().GetResources().GetOptions().EnableWellManagement  &&  Class.CastTo( well, action_data.m_Target.GetObject() ) ) 
		{
			well.SaveWellALP();
		}		
		FuelStation station;
		if ( GetND().GetResources().GetOptions().EnableFuelstationManagement &&  Class.CastTo( station, action_data.m_Target.GetObject() )  ) 
		{
			station.SaveFuelStationALP();
		}			
	}	
	

	

};