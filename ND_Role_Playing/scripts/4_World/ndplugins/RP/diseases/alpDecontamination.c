// Script File



class alpDecontaminationDisease extends alpDisease
{

	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().Decontamination;
	}

	override bool IsInfected()
	{
		return !alp_Player.GetRP().WasDecontamined();
		//return true;
		//return alp_Player.GetRP().HasContaminedItems();
	}
	
	override void CureDisease()
	{
		alp_Player.GetRP().Decontamination(true);
				
	}
			

}


