


modded class alpND_world extends alpND_base
{
	
	
	override protected void Init()
	{	
		super.Init();

		
		AddPlugin( new alpCreaturesPlugin( alpPLUGIN_BASE_ID.CREATURES,  0 ) );		
	}	


	alpCreaturesPlugin	GetCreatures()
	{
		
		alpCreaturesPlugin plugin = alpCreaturesPlugin.Cast( alp_ActivePlugins.Get( alpPLUGIN_BASE_ID.CREATURES ) );
		
		if ( plugin )
		{
			return plugin;
		}
		
		return null;
	}	

}



