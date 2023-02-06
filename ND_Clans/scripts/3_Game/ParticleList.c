modded class ParticleList
{

  static const int ALP_SPARKS        = RegisterParticle( "ND_Clans/data/sparks/", "alp_sparks" );

};

class alp_DynamiteExplosion : EffectParticle
{
	void alp_DynamiteExplosion()
	{
		SetParticleID(ParticleList.EXPLOSION_LANDMINE);
	}
}