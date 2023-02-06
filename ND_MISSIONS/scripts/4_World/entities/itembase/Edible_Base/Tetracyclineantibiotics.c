modded class TetracyclineAntibiotics : Edible_Base
{
	override void OnConsume(float amount, PlayerBase consumer)
	{
		//cure radiation disease if it stage is lower than 5
		
		if ( consumer.GetModifiersManager() )
		{
			if (consumer.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK1))
			{
				consumer.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK1);
			}		
	
			if (consumer.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK2))
			{
				consumer.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK2);
							
			}			

			if (consumer.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONSICK3))
			{
				consumer.GetModifiersManager().DeactivateModifier(rModifiers.MDF_ALPRADIATIONSICK3);
							
			}						
		}
		
		
		super.OnConsume( amount,  consumer);
	}
	

}


/*

enum ALP_RADPOISON
{
	L0 = 200,
	L1 = 500,
	L2 = 1000,
	L3 = 3000,
	L4 = 6000,/


*/