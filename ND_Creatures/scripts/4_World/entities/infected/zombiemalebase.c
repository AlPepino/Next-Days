
modded class ZmbM_NBC_Yellow extends ZombieMaleBase
{
	/*
	override bool ResistContaminatedEffect()
	{
		return true;
	}
	*/
	
	override bool IsContaminedZombie()
	{
		return true;
	}	
};

modded class ZmbM_NBC_Grey extends ZombieMaleBase
{
/*
	override bool ResistContaminatedEffect()
	{
		return true;
	}
	
	override bool IsZombieMilitary()
	{
		return true;
	}
*/
	override bool IsContaminedZombie()
	{
		return true;
	}
};



