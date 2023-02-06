#ifdef NAMALSK_SURVIVAL	
modded class Frostbite extends ModifierBase
{
	bool alp_FrostBiteSickShowed = false;
	
	override void OnTick( PlayerBase player, float deltaT )
	{	
		//Next Days
		float mltp = 1;
		if (player.GetModifiersManager().IsModifierActive(rModifiers.MDF_SLEEPING))
		{
			mltp = 5;
		}	
		
		//ND end
		
		
		float currHeatComf = player.GetStatHeatComfort().Get();
		bool isFrostiteApplicable = false;
		if ( currHeatComf < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING )
		{
			isFrostiteApplicable = true;
		}
		float frostbite_timer = ( /*0.1675*/0.01675 * currHeatComf * mltp );

		for ( int i = 0; i < m_SlotCount; i++ )
		{
			// check if the slot of interest does not have frostbite already
			if ( m_FrostbiteTimers[i] > -1.0 )
			{
				// lets check if all is good for this slot and the player character is in lower heat comfort
				if ( !CheckSlotOfInterest( player, m_SlotsOfInterest[i] ) && isFrostiteApplicable )
				{
					m_FrostbiteTimers[i] = m_FrostbiteTimers[i] + ( frostbite_timer * ( ( m_SlotImportance[i] ) / 100.0 ) );
					if ( m_FrostbiteTimers[i] <= -1.0 )
					{
						// timer has reached target value of -1, apply frostbite
						ApplyFrostbite( player, m_SlotsOfInterest[i] );
					}
				} else {
					// does it have timer != 0.0?
					if ( m_FrostbiteTimers[i] < 0.0 )
					{
						// lower it slowly to 0 again
						m_FrostbiteTimers[i] = m_FrostbiteTimers[i] - ( frostbite_timer * ( ( m_SlotImportance[i] ) / 100.0 ) );
					}
					else
					{
						// frostbite risk is gone
					}
				}
			}
			else
			{
				// slot can be ignored, frostbite has been already applied
			}
		}

		if ( m_LastFrostbiteValue != player.GetStatFrostbiteZones().Get() )
		{
			player.ForceUpdateFrostbiteZones();
			
			m_LastFrostbiteValue = player.GetStatFrostbiteZones().Get();

			
			//Next Days			
			if ( m_LastFrostbiteValue > 0 )
			{
				if (!alp_FrostBiteSickShowed)
				{
					player.IncreaseDiseaseCount();
					alp_FrostBiteSickShowed = true;
				}
				
				player.GetRP().SetDisease(alpDiseases.FROSTBITE);
			}
			else
			{
				player.GetRP().UnsetDisease(alpDiseases.FROSTBITE);
				
				m_FrostbiteTimers = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };				
				
				player.DecreaseDiseaseCount();
				alp_FrostBiteSickShowed = false;
			}			
		}

		//string fb_debug = " " + m_FrostbiteTimers[0].ToString() + " " + m_FrostbiteTimers[1].ToString() + " " + m_FrostbiteTimers[2].ToString() + " " + m_FrostbiteTimers[3].ToString() + " " + m_FrostbiteTimers[4].ToString() + " " + m_FrostbiteTimers[5].ToString();
		//Print( fb_debug );
	}

	/*
	override void OnTick( PlayerBase player, float deltaT )
	{	
		
		
		if ( m_LastFrostbiteValue != player.GetStatFrostbiteZones().Get() )
		{						
			
			if ( m_LastFrostbiteValue > 0 )
			{
				player.GetRP().SetDisease(alpDiseases.FROSTBITE);
			}
			else
			{
				player.GetRP().UnsetDisease(alpDiseases.FROSTBITE);
				
				m_FrostbiteTimers = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };				
				
				player.DecreaseDiseaseCount();
			}
		}	
		
		super.OnTick( player, deltaT );	
	}
	*/		
};
#endif	