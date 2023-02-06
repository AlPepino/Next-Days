
modded class Edible_Base extends ItemBase
{
#ifdef NAMALSK_SURVIVAL	

	
	override bool Consume(float amount, PlayerBase consumer)
	{
		
		if ( super.Consume(amount,consumer) ) {
			//Print("PREPIS SURVIVAL MODU");
			if ( consumer) {
				consumer.ConsumeBonusesALP(this,amount);
			}			
			return true;
		}
		return false;
	}			
	
#endif			
}