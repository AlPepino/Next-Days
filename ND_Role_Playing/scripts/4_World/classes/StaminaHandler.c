// Script File
modded class StaminaConsumers
{

	
	void UpdateConsumerALP(PlayerBase player)
	{
		if (!player.GetIdentity() )//hotfix
			return;
		
		int level = player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue();
		foreach(StaminaConsumer sc : m_StaminaConsumers)
		{
			float value;
			
			value = sc.GetActivationThreshold() * GetND().GetRP().GetPerkStaminaMdf( level );
			sc.SetActivationThreshold(value);			

						
			value = sc.GetDrainThreshold() * GetND().GetRP().GetPerkStaminaMdf( level );
			sc.SetDrainThreshold(value);	
		}
	
	}	
}

modded class StaminaModifier
{
	void SetDurationALP(float val)
	{
		m_Duration = val;
	}		
}

modded class StaminaModifiers
{
	void UpdateModifiersALP(PlayerBase player)
	{
		if (!player.GetIdentity() )//hotfix
			return;
		
		int level = player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue();
		foreach(StaminaModifier sm : m_StaminaModifiers)
		{
			float value;
			
						
			value = sm.GetMinValue() * GetND().GetRP().GetPerkStaminaMdf( level  );
			sm.SetMinValue(value);
	
		
			value = sm.GetMaxValue() * GetND().GetRP().GetPerkStaminaMdf( level );
			sm.SetMaxValue(value);			
			

			value = sm.GetCooldown() * GetND().GetRP().GetPerkStaminaMdf( level );	
			sm.SetCooldown(value);	
			
			value = sm.GetDuration() * GetND().GetRP().GetPerkStaminaMdf( level );	
			sm.SetDurationALP( value );
			
			if (!GetND().GetRP().GetPerkStamina().DisableStaminaPerkWhenAiming && sm.GetType() == 3 )// EXPONENTIAL to LINEAR
			{
				sm.m_Type = 2;
			}
			
		}	
	}		
	

}


modded class StaminaHandler
{	
	int	 alp_StaminaLevelLast = ALP_VALUE_NOTSET;
	

	float alp_Time 		 = 0;
	
	override void Update(float deltaT, int pCurrentCommandID)
	{
		if ( !GetND().GetRP().GetPerksOptions().EnablePerkStamina )
		{
			super.Update( deltaT, pCurrentCommandID);
			return;
		}
		//recopy due to change Weight Limit 
#ifdef DEVELOPER
		m_Debug = DiagMenu.GetBool(DiagMenuIDs.DM_CHEATS_STAMINA_DISABLE);
		if( m_Debug ) return;
#endif
		if( m_Player )
		{
			// Calculates actual max stamina based on player's load
			if ( GetGame().IsServer() )
			{
				int level = m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue();
				
				//! gets stamina from PlayerStat
				m_Stamina = m_Player.GetStatStamina().Get();
				//! gets the actual players load
				m_PlayerLoad = m_Player.GetPlayerLoad() * GetND().GetRP().GetPerkStaminaMdf( level ) ;
//uprava
				alp_Time += deltaT;

				//! StaminaCap calculation starts when PlayerLoad exceeds STAMINA_WEIGHT_LIMIT_THRESHOLD
				if (m_PlayerLoad >= CfgGameplayHandler.GetStaminaWeightLimitThreshold())
				{
					m_StaminaCap =  Math.Max((CfgGameplayHandler.GetStaminaMax() - (((m_PlayerLoad - CfgGameplayHandler.GetStaminaWeightLimitThreshold())/GameConstants.STAMINA_KG_TO_GRAMS) * CfgGameplayHandler.GetStaminaKgToStaminaPercentPenalty())),CfgGameplayHandler.GetStaminaMinCap());
				}
				else
				{
					m_StaminaCap = CfgGameplayHandler.GetStaminaMax();
				}
			}
			
			// Calculates stamina gain/loss based on movement and load
			m_Player.GetMovementState(m_State);

			switch (pCurrentCommandID)
			{
			case DayZPlayerConstants.COMMANDID_MOVE:
				StaminaProcessor_Move(m_State);
			break;
			case DayZPlayerConstants.COMMANDID_LADDER:
				StaminaProcessor_Ladder(m_State);
			break;
			case DayZPlayerConstants.COMMANDID_SWIM:
				StaminaProcessor_Swimming(m_State);
			break;
			case DayZPlayerConstants.COMMANDID_FALL:	//! processed on event
			case DayZPlayerConstants.COMMANDID_MELEE2:  //! processed on event
			case DayZPlayerConstants.COMMANDID_CLIMB:  //! processed on event
			break;
			default:
				if( !m_IsInCooldown )
				{
					m_StaminaDelta = GameConstants.STAMINA_GAIN_IDLE_PER_SEC;
				}
			break;
			}
			
			//Sets current stamina & stores + syncs data with client
			if (m_Stamina < 0)
			{
				m_Stamina = 0;
			}
			{
				float temp = m_StaminaDelta*deltaT;
				if (temp < 0)
					temp = temp * m_StaminaDepletionMultiplier;
				else
					temp = temp * m_StaminaRecoveryMultiplier;
				
				m_Stamina = Math.Max(0,Math.Min((m_Stamina + temp),m_StaminaCap));
				m_Stamina = m_Stamina - m_StaminaDepletion;
			}

			if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
			{
				m_Player.GetStatStamina().Set(m_Stamina);
				m_Time += deltaT;
				if ( m_Time >= GameConstants.STAMINA_SYNC_RATE )
				{
					m_Time = 0;
					SyncStamina(m_Stamina, m_StaminaCap, m_IsInCooldown);
				}
			}
			else
			{
				m_Player.SetStamina(m_Stamina, m_StaminaCap);
			}

			//! sets exhaustion look of player based on stamina level
			HumanCommandAdditives ad = m_Player.GetCommandModifier_Additives();
			
			float exhaustion_value = 1;
			if ( m_StaminaCap != 0 )
			{
				exhaustion_value = 1-((m_Stamina/(m_StaminaCap*0.01))*0.01);
			}
			
			exhaustion_value = Math.Min(1,exhaustion_value);
			if ( ad )
			{
				// do not apply exhaustion on local client if player is in ADS/Optics (camera shakes)
				if ( m_Player.GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_CLIENT && (m_Player.IsInOptics() || m_Player.IsInIronsights()) )
				{
					ad.SetExhaustion(0, true);
				}
				else
				{
					ad.SetExhaustion(exhaustion_value, true);
				}
			}

			CheckStaminaState();

			m_StaminaDelta = 0;
			m_StaminaDepletion = 0; // resets depletion modifier
			
			//uprava
			if ( alp_Time >= 1 ) alp_Time = 0;
		}			
	}
	
	void UpdateMdfALP()
	{
		RegisterStaminaConsumers();
		RegisterStaminaModifiers();	
	}
	
	override protected void RegisterStaminaConsumers()
	{
		super.RegisterStaminaConsumers();
		if ( GetND().GetRP().GetPerksOptions().EnablePerkStamina )
		{
			m_StaminaConsumers.UpdateConsumerALP(m_Player);
		}

	}	
	override protected void RegisterStaminaModifiers()
	{
		super.RegisterStaminaModifiers();
		if ( GetND().GetRP().GetPerksOptions().EnablePerkStamina )
		{		
			m_StaminaModifiers.UpdateModifiersALP(m_Player);
		}
	}
	
	protected void UpdateStaminaProggres(float exp)
	{
		int currentLevel = m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue();

		if ( GetGame().IsServer() )
		{	
		
				
			if ( m_Player.m_ModifiersManager.IsModifierActive ( rModifiers.MDF_ANABOLIC ) )
			{//boost stamina proggress
				
				exp *= GetND().GetRP().GetPerkStamina().AnabolicMdf;
			}
			
			
			if ( currentLevel < GetND().GetRP().GetPerkStaminaLevelCup() )
			{
				float progress 	= m_Player.GetStatPerkStaminaProgress().Get() + exp;
				float nextLevel = m_Player.GetRP().GetStaminaRequiredExp( currentLevel + 1  );
				
				if ( progress > nextLevel)
				{
					//new level
					progress -= nextLevel;
					currentLevel++;
					//message
	
					GetND().GetNotf().SendMessage( m_Player, ALPMSTYPE.SMLEVELUP, "#ip_you_have_improved_your_stamina" );
					m_Player.GetStatPerkStamina().Set( currentLevel );					
	
								
				}
				//synchronization
				m_Player.GetStatPerkStaminaProgress().Set( progress );			
			}
		}
		//synch current level
		if ( currentLevel != alp_StaminaLevelLast )
		{
			UpdateMdfALP();			
			alp_StaminaLevelLast = currentLevel;
		}
	}
	
    override protected void StaminaProcessor_Move(HumanMovementState pHumanMovementState)
    {
		super.StaminaProcessor_Move(pHumanMovementState);
		if ( GetND().GetRP().GetPerksOptions().EnablePerkStamina )
		{
			if (m_StaminaDelta<0)
			{
				m_StaminaDelta *=  GetND().GetRP().GetPerkStaminaMdf( m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue() );
			}
			else 
			{
				m_StaminaDelta /=  GetND().GetRP().GetPerkStaminaMdf( m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue() );
			}
		
			switch ( pHumanMovementState.m_iMovement )
			{
				case DayZPlayerConstants.MOVEMENTIDX_SPRINT: //sprint			  	
					if ( alp_Time >= 1 ) UpdateStaminaProggres( GetND().GetRP().GetPerkStamina().MoveSprint );
				break;
						
				case DayZPlayerConstants.MOVEMENTIDX_RUN: //jog
					if ( alp_Time >= 1 ) UpdateStaminaProggres(  GetND().GetRP().GetPerkStamina().MoveRun );
			
				break;					
				case DayZPlayerConstants.MOVEMENTIDX_WALK: //walk
	
				break;			
			}		
		
		}
	}	

	override protected void StaminaProcessor_Swimming(HumanMovementState pHumanMovementState)
	{
		super.StaminaProcessor_Swimming(pHumanMovementState);
		if ( GetND().GetRP().GetPerksOptions().EnablePerkStamina )
		{		
			if (m_StaminaDelta<0)
			{
				m_StaminaDelta *= GetND().GetRP().GetPerkStaminaMdf( m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue() );
			}
			else 
			{
				m_StaminaDelta /=  GetND().GetRP().GetPerkStaminaMdf( m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue() );
			}	
			switch ( pHumanMovementState.m_iMovement )
			{
				case 3: //swim fast
					if ( alp_Time >= 1 ) UpdateStaminaProggres( GetND().GetRP().GetPerkStamina().SwimFast);
					break;
				break;
					
				case 2: //swim slow
					if (!m_IsInCooldown)
					{
					if ( alp_Time >= 1 ) UpdateStaminaProggres( GetND().GetRP().GetPerkStamina().SwimSlow );
					}
				break;
			}
		}
					
	}	
	override protected void StaminaProcessor_Ladder(HumanMovementState pHumanMovementState)
	{
		super.StaminaProcessor_Ladder(pHumanMovementState);
		if ( GetND().GetRP().GetPerksOptions().EnablePerkStamina )
		{		
			if (m_StaminaDelta<0)
			{
				m_StaminaDelta *=  GetND().GetRP().GetPerkStaminaMdf( m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue() );
			}
			else 
			{
				m_StaminaDelta /=  GetND().GetRP().GetPerkStaminaMdf( m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue() );
			}				
			switch ( pHumanMovementState.m_iMovement )
			{
				case 2: //climb up (fast)
					if ( alp_Time >= 1 ) UpdateStaminaProggres( GetND().GetRP().GetPerkStamina().ClimbFast );
					break;
				break;
					
				case 1: //climb up (slow)
					if (!m_IsInCooldown)
					{
					if ( alp_Time >= 1 ) UpdateStaminaProggres( GetND().GetRP().GetPerkStamina().ClimbSlow );
					}
				break;
	
			}	
		}	
	}	
	override void DepleteStamina(EStaminaModifiers modifier, float dT = -1)
	{
		super.DepleteStamina(modifier, dT);
		if ( GetND().GetRP().GetPerksOptions().EnablePerkStamina )
		{		
			if (modifier == EStaminaModifiers.HOLD_BREATH && GetND().GetRP().GetPerkStamina().DisableStaminaPerkWhenAiming)
				return;
		
			m_StaminaDepletion *= GetND().GetRP().GetPerkStaminaMdf( m_Player.GetSyncData().GetElement( alpRPelements.STAMINA ).GetValue() );
		}
	}	
}