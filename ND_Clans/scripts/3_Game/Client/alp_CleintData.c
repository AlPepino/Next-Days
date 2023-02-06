modded class ClientData
{
	static ref array<EntityAI>			PlotPoleList = new array<EntityAI>;	
	static ref array<EntityAI>			EstateList 	 = new array<EntityAI>;	

	
	override static void ResetClientData()
	{
		if( PlotPoleList )
			PlotPoleList.Clear();
		
		if( EstateList )
			EstateList.Clear();		
				
		if( m_PlayerBaseList )
			m_PlayerBaseList.Clear();
		if( m_PlayerList && m_PlayerList.m_PlayerList )
			m_PlayerList.m_PlayerList.Clear();
		if( m_LastNewPlayers && m_LastNewPlayers.m_PlayerList )
			m_LastNewPlayers.m_PlayerList.Clear();
	}

	static void AddPlotPole( EntityAI plotpole )
	{
		if( PlotPoleList )
			PlotPoleList.Insert( plotpole );

	}
	
	static void RemovePlotPole( EntityAI plotpole )
	{
		if( PlotPoleList )
			PlotPoleList.RemoveItem( plotpole );
	}
	
	static void AddEstate( EntityAI estate )
	{
		if( EstateList && EstateList.Find( estate) == -1 )
			EstateList.Insert( estate );

	}
	
	static void RemoveEstate( EntityAI estate )
	{
		if( EstateList )
			EstateList.RemoveItem( estate );
	}
	
}

