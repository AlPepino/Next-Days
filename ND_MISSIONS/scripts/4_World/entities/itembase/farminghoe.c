modded class FarmingHoe: ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(alpActionDigInRadioactiveBarrel);
	}
};
