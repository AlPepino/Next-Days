//alpPluginBase




class alpPlugin : alpPluginBase
{

		
	
	override void OnConnect( Man player )
	{
		PlayerBase p = PlayerBase.Cast( player );
		
		OnConnectManaged(p);
	}
	

	
	override void OnSpawn( Man player )
	{
		PlayerBase p = PlayerBase.Cast( player );
		
		OnSpawnManaged(p);
	}
	
	override void OnDeath( Man player )
	{
		PlayerBase p = PlayerBase.Cast( player );	
		OnDeathManaged(p);
	}
	
	override void OnDisconnect( Man player )
	{
		PlayerBase p = PlayerBase.Cast( player );	
		OnDisconnectManaged(p);
	}
	
	void OnConnectManaged( PlayerBase player ){}
	
	void OnSpawnManaged( PlayerBase player ){}

	void OnDeathManaged( PlayerBase player ){}
	
	void OnDisconnectManaged( PlayerBase player ){}
}

