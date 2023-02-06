

modded class alpMissionPosition 
{
	
	override bool IsSomeOneInRadisu(vector position, int radius)
	{	
		private array<Man> players 	= new array<Man>;
		GetGame().GetPlayers( players );	
		if( players.Count() > 0 )
		{
			foreach(Man player: players)
			{
				if( player )
				{
					if (alpUF.VectorDistance(position,player.GetPosition()) < radius )
					{
						return true;
					}
				}
			}
		}

		radius = Math.Clamp(radius, 0,30);
		
		if ( radius > 0 ) {
		
			autoptr array<Object> nearest_objects = new array<Object>;
			autoptr array<CargoBase> proxy_cargos = new array<CargoBase>;
				
			GetGame().GetObjectsAtPosition( position , radius , nearest_objects, proxy_cargos ); 						
			for (int x = 0; x < nearest_objects.Count();x++){
				Object obj = nearest_objects.Get(x);				
				if ( obj && obj.GetType() == "alp_PlotPole" ) {
					return true;
				}
			}		
				
		}

		return false;
	}
	
	
}