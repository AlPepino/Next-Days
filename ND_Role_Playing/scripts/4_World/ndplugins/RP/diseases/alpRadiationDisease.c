class alpRadiationDisease extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().RadiationSick;
	}
	
	
	override void CureDisease()
	{	
		
			int radiation = alp_Player.GetRP().GetRecievedRadiation();
		
			if (  alp_Player.GetRP().GetRecievedRadiation() < ALP_RADPOISON.L5 )
			{
				alp_Player.m_AgentPool.SetAgentCount( alpeAgents.RADIATION, 0 );
		
		
				if (alp_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK1))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK1);
				}		
		
				if (alp_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK2))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK2);
								
				}			
	
				if (alp_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK3))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK3);
								
				}		
			
				if (alp_Player.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK4))
				{
					alp_Player.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK4);
								
				}			
			}
					
	}
	
	override bool CanBeCured()
	{
		//return alp_CanBeCured;
		float value;	
		alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.RADIATIONSICKSTAGE).GetValue( value );
		
		if (value <= ALP_RADIATION_SICKSTAGE.L4 )		
			return true;
		else
			return false;
	
	}		
	
	override float GetPrice()
	{
		float price = super.GetPrice();	
		float value,ratio;	
		

		
		if ( alp_Player )
		{
										
				
			alp_Player.GetSyncData().GetElementEnhanced(alpRPelementsEnahnced.RADIATIONSICKSTAGE).GetValue( value );
			
			if (value <= ALP_RADIATION_SICKSTAGE.L4)
			{
				ratio = 100;
			}
			if (value <= ALP_RADIATION_SICKSTAGE.L3)
			{
				ratio = 80;
			}	
			if (value <= ALP_RADIATION_SICKSTAGE.L2)
			{
				ratio = 40;
			}					
			if (value <= ALP_RADIATION_SICKSTAGE.L1)
			{
				ratio = 20;
			}	
		
			
			ratio /= 100;				
		}		
			
		return price * ratio;
	}	
}