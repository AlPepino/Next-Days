
class alpPluginNDoptions extends alpPlugin
{

	//ref alpOptionsND	alp_OptionsND;

	override void Init() 
	{
		//load file
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() )
		{	
			//init BankBalance
			if ( GetGame().IsServer() )
			{
				alpBANK.InitServerSide();
			}
			/*
			if (!FileExist(ALP_ROOTFOLDER + ALP_OPTIONS) )
			{ 
				alp_OptionsND  = new alpOptionsND;
				JsonFileLoader< alpOptionsND>.JsonSaveFile(ALP_ROOTFOLDER + ALP_OPTIONS,  alp_OptionsND);
			}
			else 
			{
				JsonFileLoader< alpOptionsND>.JsonLoadFile(ALP_ROOTFOLDER + ALP_OPTIONS, alp_OptionsND );	
			}
				
			JsonFileLoader< alpOptionsND>.JsonSaveFile(ALP_ROOTFOLDER + ALP_OPTIONS,  alp_OptionsND);			
			*/
		}
		/*
		else
		{
			//alp_OptionsND = new alpOptionsND();
		}
		*/
	}
	
/*
	override void ReadInitRPC( PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		ctx.Read( alp_OptionsND );		

	}	
	
	
	alpOptionsND GetOptions()
	{
		return alp_OptionsND;
	}	
	
	override void OnConnectManaged( PlayerBase player )
	{	
		if (GetGame().IsServer() )
		{	
		
			
			ScriptRPC rpc = GetND().GetInitRPC( GetID() );					
			rpc.Write( alp_OptionsND );
			
			GetND().SendGameRPC( rpc, player );
		}
			
		
	}	
*/			
}

