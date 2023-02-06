modded class CAContinuousFill : CAContinuousBase
{
	
	override int Execute( ActionData action_data )
	{
		
		
		Well well;
		FuelStation station;
		
		if ( GetND().GetResources().GetOptions().EnableWellManagement && Class.CastTo( well, action_data.m_Target.GetObject() )  ) 
		{
			if ( !action_data.m_Player )
			{
				return UA_ERROR;
			}			
			if ( action_data.m_MainItem.GetQuantity() >= action_data.m_MainItem.GetQuantityMax() || !well.HasWaterALP() )
			{
				return UA_FINISHED;
			}			
			else
			{				
				if ( m_SpentQuantity_total < m_TargetUnits  )
				{
					m_SpentQuantity += m_AdjustedQuantityFilledPerSecond * action_data.m_Player.GetDeltaT();
					m_TimeElpased += action_data.m_Player.GetDeltaT();
									
					if ( m_TimeElpased >= m_DefaultTimeStep )
					{						
						float water = well.GetWaterAmmount();
						
						if ( m_SpentQuantity <= water )
						{					
							
							well.DrainWaterALP( m_SpentQuantity );
							CalcAndSetQuantity( action_data );
							m_TimeElpased = 0;	
						}
						else
						{							
							m_SpentQuantity = water;					
														
							well.DrainWaterALP( m_SpentQuantity );
							CalcAndSetQuantity( action_data );
							m_TimeElpased = 0;							
						}

						
						//Setup(action_data);	//reset data after repeat
					}
					return UA_PROCESSING;
				}
				else
				{
					CalcAndSetQuantity( action_data );
					OnCompletePogress(action_data);
					return UA_FINISHED;
				}			
			}
				
			
			return UA_FINISHED;
		}
		else if ( GetND().GetResources().GetOptions().EnableFuelstationManagement && Class.CastTo( station, action_data.m_Target.GetObject() )   )
		{
			if ( !action_data.m_Player )
			{
				return UA_ERROR;
			}			
			if ( action_data.m_MainItem.GetQuantity() >= action_data.m_MainItem.GetQuantityMax() || !station.HasFuelALP() )
			{
				return UA_FINISHED;
			}			
			else
			{
				
				if ( m_SpentQuantity_total < m_TargetUnits  )
				{
					m_SpentQuantity += m_AdjustedQuantityFilledPerSecond * action_data.m_Player.GetDeltaT();
					m_TimeElpased += action_data.m_Player.GetDeltaT();
									
					if ( m_TimeElpased >= m_DefaultTimeStep )
					{						
						float fuel = station.GetFuelAmmount();
						
						if ( m_SpentQuantity <= fuel )
						{					
							
							station.DrainFuelALP( m_SpentQuantity );
							CalcAndSetQuantity( action_data );
							m_TimeElpased = 0;	
						}
						else
						{							
							m_SpentQuantity = fuel;					
														
							station.DrainFuelALP( m_SpentQuantity );
							CalcAndSetQuantity( action_data );
							m_TimeElpased = 0;							
						}

						//Setup(action_data);	//reset data after repeat
					}
					return UA_PROCESSING;
				}
				else
				{
					CalcAndSetQuantity( action_data );
					OnCompletePogress(action_data);
					return UA_FINISHED;
				}			
			}			
			return UA_FINISHED;			
		}
		else return super.Execute( action_data );
	}			
		

};