
class alp_WoodenCrate: WoodenCrate
{
	override bool CanPutInCargo( EntityAI parent )
	{
		return false;
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;

	}
};


class alp_WoodenCrate_Base: Container_Base
{
	
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef){

		float health = GetHealth("","Health");
		float damage = damageResult.GetDamage("","Health");
		Print("DAMAGE " + damage );
		if ( damageType == DT_EXPLOSION && damage > 200 && ( ammo == "alp_DynamiteExplosion" || ammo == "Plastic_Explosive_Ammo" ) ){
			GetGame().ObjectDelete( this );
		}	
		
		if ( health < 50 ) {
			GetGame().ObjectDelete( this );
		}
	}
		
	override bool CanPutInCargo( EntityAI parent )
	{
		return false;
	}
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;

	}
};


class alp_WoodenCrateBig : alp_WoodenCrate_Base
{

}
class alp_WoodenCrateBig3x : alp_WoodenCrate_Base
{


	
}
class alp_WoodenCrateBig5x : alp_WoodenCrate_Base
{


	
}