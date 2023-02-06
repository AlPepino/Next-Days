modded class Lard extends Edible_Base
{

	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionCreateIndoorFireplace);
		AddAction(ActionCreateIndoorOven);
		

	}
}
