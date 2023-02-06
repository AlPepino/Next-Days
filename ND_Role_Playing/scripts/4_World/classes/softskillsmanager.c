
modded class SoftSkillsManager
{	
	float alp_SpecialtyLevelSoft;
	float alp_SpecialtyLevelHard;
	
	override void InitSpecialty( float specialty_level )
	{
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{
			float soft  = m_Player.GetStatPerkSoft().Get();
			float hard  = m_Player.GetStatPerkRough().Get();
			
			SetSpecialtyLevelSoft( soft );
			SetSpecialtyLevelHard( hard );
			
			SynchSpecialtyLevel();	
		}
		else
		{
			super.InitSpecialty( specialty_level );	
		}

	}	

	void SetSpecialtyLevelSoft( float specialty_level )
	{
		//Print("Stavajici SOFT " + alp_SpecialtyLevelSoft + ", pridavam : " +specialty_level );
		alp_SpecialtyLevelSoft = specialty_level;
	}	
	void SetSpecialtyLevelHard( float specialty_level )
	{
		//Print("Stavajici HARD " + alp_SpecialtyLevelHard + ", pridavam : " +specialty_level );
		alp_SpecialtyLevelHard = specialty_level;
	}				
	
	
	override void GetPreciseRoughLevels()
	{
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{		
			m_PreciseLevel =  Math.AbsFloat( alp_SpecialtyLevelSoft );
			m_RoughLevel = alp_SpecialtyLevelHard;
		}
		else
		{
			super.GetPreciseRoughLevels();	
		}
		
	}	
	
	
	override void SynchSpecialtyLevel()
	{	
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{		
			ref Param2<float,float> specialty_level;
			
			if( GetGame().IsServer() )
			{
				specialty_level = new Param2<float,float>( alp_SpecialtyLevelSoft,alp_SpecialtyLevelHard );
				GetGame().RPCSingleParam( m_Player, ALP_RPC_DAYZ_SKILLS_SPECIALTY_SYNC, specialty_level, true, m_Player.GetIdentity() );
			}	
		}
		else
		{
			super.SynchSpecialtyLevel();	
		}
				
		
	
	}
	
	
	override void AddSpecialty( float specialty_weight )
	{
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{		
			if( GetSoftSkillsState() )
			{
				if( !IsCoolDown() )
				{	
						if( specialty_weight < 0 )
						{	
							if( IsLinear() )
							{
								SetSpecialtyLevelSoft( AddLinearPrecise( specialty_weight ) );	
							}
							else
							{
								 SetSpecialtyLevelSoft( AddExponentialPrecise( specialty_weight ) );
							}
	
							m_Player.GetStatPerkSoft().Set( alp_SpecialtyLevelSoft );
							StartCoolDownTimer( Math.AbsFloat( ( specialty_weight * 100 ) ) * COOLDOWN_TIMER );
							SynchSpecialtyLevel();
						}
						else if( specialty_weight > 0 )
						{
							if( IsLinear() )
							{							
								SetSpecialtyLevelHard( AddLinearRough( specialty_weight ) );
							}
							else
							{						
								SetSpecialtyLevelHard( AddExponentialRough( specialty_weight ) );		
							}
	
							m_Player.GetStatPerkRough().Set( alp_SpecialtyLevelHard );
							StartCoolDownTimer( Math.AbsFloat( ( specialty_weight * 100 ) ) * COOLDOWN_TIMER );
							SynchSpecialtyLevel();
						}
						else
						{
							//if the specialty weight for a recipe or UA is set to 0, it will increase neither specialty, nor UA counter
							return;
						}
					}
				else
				{
					StartCoolDownTimer( Math.AbsFloat( ( specialty_weight * 100 ) ) * COOLDOWN_TIMER );		
				}
			}
		}
		else
		{
			super.AddSpecialty( specialty_weight );	
		}		
		
	}	
	
	
	

	
	// ----------------------------------------------------------------------------------------
	float GetSpecialtyLevelSoft()
	{
		return alp_SpecialtyLevelSoft;
	}
	float GetSpecialtyLevelHard()
	{
		return alp_SpecialtyLevelHard;
	}
	
	//-----------------------------------------------------------------------------------------
	
	override float AddLinearPrecise( float specialty_weight )
	{
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{	
			alp_SpecialtyLevelSoft += specialty_weight; 
			SetLastUAValue( specialty_weight );
			alp_SpecialtyLevelSoft = Math.Clamp( alp_SpecialtyLevelSoft, PRECISE_WEIGHT_LIMIT, ROUGH_WEIGHT_LIMIT );
	
			return alp_SpecialtyLevelSoft;			
			
		}
		else
		{
			return super.AddLinearPrecise( specialty_weight );	
		}				
	
	}	
	override float AddLinearRough( float specialty_weight )
	{
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{	
			
			alp_SpecialtyLevelHard += specialty_weight;
			SetLastUAValue( specialty_weight );
			alp_SpecialtyLevelHard = Math.Clamp( alp_SpecialtyLevelHard, PRECISE_WEIGHT_LIMIT, ROUGH_WEIGHT_LIMIT );
	
			return alp_SpecialtyLevelHard;		
			
		}
		else
		{
			return super.AddLinearRough( specialty_weight );	
		}		

	}	
	override float AddExponentialPrecise( float specialty_weight )
	{
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{	
		
			m_UserActionsCounter -= 1;
	
			if( m_UserActionsCounter == 0)
			{
				m_UserActionsCounter = -1;
				alp_SpecialtyLevelSoft = 0;
			}
			
			float adjusted_weight = specialty_weight / Math.Sqrt( Math.AbsInt( m_UserActionsCounter ) );
		
			SetLastUAValue( adjusted_weight );
	
			alp_SpecialtyLevelSoft += adjusted_weight;
			alp_SpecialtyLevelSoft = Math.Clamp( alp_SpecialtyLevelSoft, PRECISE_WEIGHT_LIMIT, ROUGH_WEIGHT_LIMIT );
	
			return alp_SpecialtyLevelSoft;
		}
		else
		{
			return super.AddExponentialPrecise( specialty_weight );	
		}		
		
	}	
	
	override float AddExponentialRough( float specialty_weight )
	{
		
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{	
		
			m_UserActionsCounter += 1;
				
			if( m_UserActionsCounter == 0)
			{
				m_UserActionsCounter = 1;
				alp_SpecialtyLevelHard = 0;
			}
			
			float adjusted_weight = specialty_weight / Math.Sqrt( Math.AbsInt( m_UserActionsCounter ) );
	
			SetLastUAValue( adjusted_weight );
	
			alp_SpecialtyLevelHard += adjusted_weight;
			alp_SpecialtyLevelHard = Math.Clamp( alp_SpecialtyLevelHard, PRECISE_WEIGHT_LIMIT, ROUGH_WEIGHT_LIMIT );
	
			return alp_SpecialtyLevelHard;
			
		}
		else
		{
			return super.AddExponentialRough( specialty_weight );	
		}		

	}	
}
