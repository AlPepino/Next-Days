//alpPluginBase

enum alpPLUGIN_BASE_ID
{	
	OPTIONS=1,//main settings
	NOTF=2,//main settings
	INFO=4,//main settings
	RP=8,
	MS=16,//mission system 
	RESOURCES=32,//wells,fuels
	CLANS=64,//clans,BB
	CREATURES=128,//creatures
}


enum alpPLUGIN_BASE_EVENTS
{
	START=1,
	UPDATE=2,
	FINISH=4,
	ONCONNECT=8,
	ONSPAWN=16,
	ONDEATH=32,
	ONDISCONNECT=64,
	ONRECONNECT=128,
	
	
}


class alpSyncItemCall
{
	Class alp_Adresa;
	string alp_Function;
	
	void alpSyncItemCall(Class callBack, string function)
	{
		alp_Adresa = callBack;	
		alp_Function = function;
	}
	
	void Run()
	{
		GetGame().GameScript.CallFunction(alp_Adresa,alp_Function,null,null);
	}
}

class alpPluginBase 
{
	protected int alp_ID;
	
	protected bool alp_DataInitCompleted;
	
	protected int alp_RegisteredEvents;
	

	
	protected ref array<ref alpSyncItemCall> alp_CallsOnConnect;
	
	
	void ~alpPluginBase()
	{
		delete alp_CallsOnConnect;				
	}	
	
	
	void alpPluginBase(int plugin, int settings)
	{
		alp_ID 					= plugin;
		
		alp_RegisteredEvents 	= settings;
					
		alp_DataInitCompleted	= false;
		
		Init();
	}
	
	int GetID()
	{
		return alp_ID;
	}
		
	bool IsInitCompleted()
	{
		return alp_DataInitCompleted;
	}
	
	void SyncInitStatusCompleted()
	{
		alp_DataInitCompleted	= true;
		RunCallBackOnConnect();
	}
	
	void AddSyncCallEventOnConnect(Class callback, string function)
	{
		
		if ( !alp_CallsOnConnect )
		{
			alp_CallsOnConnect = new  array<ref alpSyncItemCall>;
		}
		
		alp_CallsOnConnect.Insert( 	 new alpSyncItemCall( callback, function ) );
	}
	
	
	void RunCallBackOnConnect()
	{

		if ( alp_CallsOnConnect )
		{
			for (int i = 0; i < alp_CallsOnConnect.Count() ; i++)
			{
				alp_CallsOnConnect.Get(i).Run();
			}
			alp_CallsOnConnect.Clear();
		} 
	}

	void Init() {}
	
	void ReadInitRPC( PlayerIdentity sender, Object target, ParamsReadContext ctx){}	
	
	void ReadSyncRPC(PlayerIdentity sender, Object target, ParamsReadContext ctx){}
	
	bool IsEventStart()
	{
		return 	alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.START;	
	}
	bool IsEventUpdate()
	{
		return 	alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.UPDATE;	
	}	
	bool IsEventFinish()
	{
		return 	alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.FINISH;	
	}	
	
	bool IsEventOnConnect()
	{
		return 	alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.ONCONNECT;	
	}	
	bool IsEventOnSpawn()
	{
		return 	alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.ONSPAWN;	
	}	
	bool IsEventOnDeath()
	{
		return 	alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.ONDEATH;	
	}	
	bool IsEventOnDisconnect()
	{
		return 	alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.ONDISCONNECT;	
	}	
	bool IsEventOnReconnect()
	{
		return 	alp_RegisteredEvents & alpPLUGIN_BASE_EVENTS.ONRECONNECT;	
	}	

	void OnStart(){}	
	
	void OnUpdate( float timeslice ){}

	void OnFinish(){}		
	
	void OnConnect( Man player ){}
	
	void OnReconnect( Man player ){}	

	void OnDisconnect( Man player ){}
	
	void OnSpawn( Man player ){}
	
	void OnDeath( Man player ){}

}

