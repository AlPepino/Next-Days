

class alp_Barricade : House
{

			
	void alp_Barricade(){

		
	}


	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef){

		float health = GetHealth("","Health");
		float damage = damageResult.GetDamage("","Health");
		
		if ( damageType == DT_EXPLOSION && damage > 200 && ( ammo == "alp_DynamiteExplosion" || ammo == "Plastic_Explosive_Ammo" ) ){
			GetGame().ObjectDelete( this );
		}	
		
		if ( health < 50 ) {
			GetGame().ObjectDelete( this );
		}
	}

}


