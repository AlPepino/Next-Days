
class alpBleedingDisease extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().Bleeding;
	}
		
	
	override bool IsInfected()
	{
		return alp_Player.IsBleeding();
	}

	override float GetPrice()
	{
		float price = super.GetPrice();	
		
		int count = alp_Player.GetBleedingSourceCount();
		
		if (count > 0 )
		{
			price = price * count;
		}
				
		return price;
	}	
		
	override void CureDisease()
	{

				
		if (alp_Player.GetBleedingManagerServer() )
		{
			alp_Player.GetBleedingManagerServer().RemoveAllSources();	
		}	

		
	}
}