
class alpPluginNDresources extends alpPlugin
{
	ref alpResourcesSetting alp_ResourcesSetting;

	void ~alpPluginNDresources()
	{
		delete alp_ResourcesSetting;					
	}
	override void Init() 
	{
		//load file
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() )
		{
			if (!FileExist(ALP_RESOURCES_FOLDER)) MakeDirectory(ALP_RESOURCES_FOLDER);	
			
			if (!FileExist(ALP_WELLS_FOLDER)) MakeDirectory(ALP_WELLS_FOLDER);	
			if (!FileExist(ALP_FUELS_FOLDER)) MakeDirectory(ALP_FUELS_FOLDER);	

			//read info sites
			JsonFileLoader< alpResourcesSetting>.JsonLoadFile( ALP_RESOURCES_FILE , alp_ResourcesSetting );		
			
			if ( !alp_ResourcesSetting)			
			{
				alp_ResourcesSetting = new alpResourcesSetting();
				
				JsonFileLoader< alpResourcesSetting>.JsonSaveFile( ALP_RESOURCES_FILE , alp_ResourcesSetting );				
			}

		}	
		
		
	}
	

	override void OnConnectManaged( PlayerBase player )
	{	

		ScriptRPC rpc = GetND().GetInitRPC( GetID() );					

		WriteOnConnectRPC( rpc );
			
		GetND().SendGameRPC( rpc, player );
		
	}	
	
	void WriteOnConnectRPC(ref ScriptRPC rpc)
	{
		rpc.Write( alp_ResourcesSetting );

	}
	
	
	
	override void ReadInitRPC( PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		
		ctx.Read( alp_ResourcesSetting );		
	

	}		
	
	
	alpResourcesSetting GetOptions()
	{
		return alp_ResourcesSetting;
	}
	alpDefaultWellsSetting GetDefaultWell()
	{
		return alp_ResourcesSetting.Wells;
	}

	alpDefaultFuelstationSetting GetDefaultFuelstations()
	{
		return alp_ResourcesSetting.Fuelstations;
	}
		
}

