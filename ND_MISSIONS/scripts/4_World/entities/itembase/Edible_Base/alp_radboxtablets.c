class alp_radboxtablets : VitaminBottle
{
	override void OnConsume(float amount, PlayerBase consumer)
	{
				
		if( consumer.GetModifiersManager().IsModifierActive(rModifiers.MDF_ALPRADIATIONBLOCK))//effectively resets the timer
		{
			consumer.GetModifiersManager().DeactivateModifier( rModifiers.MDF_ALPRADIATIONBLOCK );
		}
		consumer.GetModifiersManager().ActivateModifier( rModifiers.MDF_ALPRADIATIONBLOCK );
		
		
		
	}
}