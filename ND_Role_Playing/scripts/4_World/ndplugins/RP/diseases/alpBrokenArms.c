
class alpBrokenArms extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().BrokenArm;
	}
	
	override void CureDisease()
	{
		alp_Player.SetHealth( "RightArm", "Health", 100 );
		alp_Player.SetHealth( "LeftArm", "Health", 100 );
		
		if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_ARMS))
		{
			alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_BROKEN_ARMS);
		}
		
		
	}
}
