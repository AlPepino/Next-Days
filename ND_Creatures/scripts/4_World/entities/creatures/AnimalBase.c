
modded class AnimalBase
{
	override void EEInit()
	{
		super.EEInit();

		if ( GetGame().IsServer() && IsAnimalCustomed() ){
			
			m_AreaTimeCheck = Math.RandomInt(-30,2);
			
			
			
			/*
			if ( !alpPluginNDmissionsSystem.CansSpawnAI(this ) ) {
				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(g_Game.ObjectDelete,1,false,this);
				return;			
			}
			*/
		}
		
		
		
	}
	
	bool IsAnimalCustomed()
	{
		return GetND().GetCreatures().GetOptions().EnableCretures;	
	}	
	
	float m_AreaTimeCheck;
	override bool	ModCommandHandlerBefore(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		bool ret = super.ModCommandHandlerBefore( pDt,  pCurrentCommandID,  pCurrentCommandFinished);	

		if (!ret && IsAnimalCustomed() )
		{
			//check if the zombie can exists
			m_AreaTimeCheck += pDt;
			if ( m_AreaTimeCheck > 2 ) {						
				m_AreaTimeCheck = 0;
				
				if ( !alpPluginNDmissionsSystem.CansSpawnAI(this ) ) {
					SetHealth("","",0);
					return true;
				}
			}
		}
		return ret;
	}	
}