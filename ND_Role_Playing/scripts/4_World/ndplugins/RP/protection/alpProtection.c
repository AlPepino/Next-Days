// Script File




modded class alpProtection 
{

	
	/*
	float GetNaturalResistanceAgainstRadiation()
	{		
		return 0;
	}
	float GetNaturalResistanceAgainstChemical()
	{		
		return 0;
	}	
	float GetNaturalResistanceAgainstBiologic()
	{		
		return 0;
	}		
	*/
	
	override float GetNaturalResistanceAgainstRadiation()
	{	
		if ( !GetND().GetRP().GetPerksOptions().EnablePerkRadiationResistance )
		{		
			return 0;
		}		
			
		int level;
		
		level	= alp_Player.GetSyncData().GetElement( alpRPelements.RAD_RESIST ).GetValue();
		
		float resitance	= GetND().GetRP().GetPerkRadiationResistanceMdf( level );

		return resitance/100;
	}	
	

	override float GetNaturalResistanceAgainstChemical()
	{	
		if ( !GetND().GetRP().GetPerksOptions().EnablePerkToxicResistance )
		{		
			return 0;
		}
			
		int level;
		
		level	= alp_Player.GetSyncData().GetElement( alpRPelements.TOXIC_RESIST ).GetValue();
		
		float resitance	= GetND().GetRP().GetPerkToxicResistanceMdf( level );

		return resitance/100;
	}	
}




