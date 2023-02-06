
class alpBrokenLegs extends alpDisease
{
	override float GetFee()
	{
		return GetND().GetMS().GetTrader().GetFees().BrokenLeg;
	}
	
	override void CureDisease()
	{
		alp_Player.SetHealth( "RightLeg", "Health", 100 );
		alp_Player.SetHealth( "LeftLeg", "Health", 100 );
		
		if (alp_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_LEGS))
		{
			alp_Player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_BROKEN_LEGS);
		}			
		
		alp_Player.UpdateBrokenLegs(eBrokenLegs.NO_BROKEN_LEGS);
	}
}
