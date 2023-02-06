class alpFrostbite extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().FrostbiteSick;
	}
		

	
	override void CureDisease()
	{
		//Print("LECIM FROSTBITE");
		
#ifdef NAMALSK_SURVIVAL		
		//Print("FROSTBITE" + alp_Player.GetStatFrostbiteZones().Get() );
		
		alp_Player.GetStatFrostbiteZones().Set(0);		
		
		//Print("FROSTBITE" + alp_Player.GetStatFrostbiteZones().Get() );
		
		alp_Player.GetStatFrostbiteEffect().Set(0);
		alp_Player.ForceUpdateFrostbiteZones();
#endif			
	}
	
	override float GetPrice()
	{
		float price = super.GetPrice();	
		


		price = price * GetCoefPrice();
								
		return price;
	}
	
	float GetCoefPrice()
	{
		float ratio;
#ifdef NAMALSK_SURVIVAL			
		int frostbite = alp_Player.GetFrostbiteZones();
		
		if ( frostbite & 1 )
		{
			ratio+=20;
		}
		if ( frostbite & 2 )
		{
			ratio+=20;
		}		
		if ( frostbite & 4 )
		{
			ratio+=20;
		}		
		if ( frostbite & 8 )
		{
			ratio+=20;
		}		
		if ( frostbite & 16 )
		{
			ratio+=10;
		}				
		if ( frostbite & 32 )
		{
			ratio+=10;
		}		
		
		if ( ratio == 0 )
			ratio = 10;
			
#endif
		ratio /= 100;
		
		return ratio;
	}
	
}