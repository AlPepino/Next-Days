
modded class Pelt_Base
{	

	
	
	override bool CanBeRepairedByCrafting()
	{
		if ( !GetND().GetRP().GetPerkHunting().PeltIsNotRepairable )
		{
			return super.CanBeRepairedByCrafting();
		}
		return false;
	}

}
