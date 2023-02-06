modded class FieldShovel extends ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(alpActionDigInRadioactiveBarrel);
	}
}