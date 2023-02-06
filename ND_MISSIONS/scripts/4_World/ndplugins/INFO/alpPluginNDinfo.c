
class alpPluginNDinfo extends alpPlugin
{
	ref alpInfoSitesTemplate							alp_InfoSites;


	override void Init() 
	{
		//load file
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() )
		{
			if (!FileExist(ALP_INFO_FOLDER)) MakeDirectory(ALP_INFO_FOLDER);	

			//read info sites
			JsonFileLoader< alpInfoSitesTemplate>.JsonLoadFile( ALP_INFO_FILE , alp_InfoSites );		
			
			if ( alp_InfoSites)			
			{
				ReadInfoContent();				
			}
			else
			{
				//create template
				InitInfoPagesTemplate();
					
			}
		}	
		
		
	}
	void ~alpPluginNDinfo()
	{
		delete alp_InfoSites;				
	}	

	
	override void OnConnectManaged( PlayerBase player )
	{					
		
		ScriptRPC rpc = GetND().GetInitRPC( GetID() );					
		rpc.Write( alp_InfoSites );

							
		GetND().SendGameRPC( rpc, player );

	}	
		

	override void ReadInitRPC( PlayerIdentity sender, Object target, ParamsReadContext ctx)
	{		
		
		ctx.Read( alp_InfoSites );		

	}	
	
	protected void ReadInfoContent()
	{
		foreach(  alpISitem item : alp_InfoSites.Items)
		{
			for (int i = 0; i < item.Text.Count();i++)
			{
				//search data
				if ( item.Text.Get(i).Count() != 1)
					continue;
				
				string fileName = item.Text.Get(i).Get(0);
				FileHandle file = OpenFile ( ALP_INFO_FOLDER +  fileName, FileMode.READ );
				if ( file )
				{
					string line_content;
					item.Text.Get(i).Clear();
					while ( FGets( file,  line_content ) > 0 )
					{				
						item.Text.Get(i).Insert(line_content);
	
					}																		
					CloseFile(file);
				}
			
			}	
		}	
	}	
	
	protected void InitInfoPagesTemplate()
	{

		alpInfoSitesTemplateInput input = new alpInfoSitesTemplateInput();
		
		input.Language = {"English"};
		input.Button1 = {"Donate","https://paypal.me/AlPepino?locale.x=cs_CZ"};
		input.Button5 = {"Discord","https://discord.gg/6dMThNM"};
		
		//init some files
		for (int i = 0; i < 5 ; i ++)
		{
			alpISitem item = new alpISitem();
			string menu = "Some menu " + i;							
			item.Menu = {menu};
			
			array<ref array<string>> text = new array<ref array<string>>;
			string textInput = "m" + i + "_ENG.txt";
			//make file
			FileHandle file = OpenFile ( ALP_INFO_FOLDER + textInput, FileMode.WRITE );		
			if ( file )
			{
				FPrintln(	file, "SOME TEXT");																		
				CloseFile(file);
			}					
					
			item.Text.Insert( {textInput} );
					
			input.Items.Insert(item);
		}
		JsonFileLoader< alpInfoSitesTemplateInput>.JsonSaveFile( ALP_INFO_FILE , input );	
				
		JsonFileLoader< alpInfoSitesTemplate>.JsonLoadFile( ALP_INFO_FILE , alp_InfoSites );	
				
		if (alp_InfoSites)
			ReadInfoContent();				
	}

			
	ref alpInfoSitesTemplate GetData()
	{
		return alp_InfoSites;
	}			
}

