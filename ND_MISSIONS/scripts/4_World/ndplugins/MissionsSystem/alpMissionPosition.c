

class alpMissionPosition 
{
	
	
	array<float> GetPositionFS(alpMission mission)
	{	
		array<float> coordinates = new array<float>;
		
		if ( alpPluginNDmissionsSystem.FuelStations && alpPluginNDmissionsSystem.FuelStations.Count() > 0 )
		{
			int index;
			index = alpPluginNDmissionsSystem.FuelStations.GetRandomIndex();
			
			FuelStation station =  alpPluginNDmissionsSystem.FuelStations.Get( index );
			/*
			if ( station && station.GetFuelAmmount() > station.GetMinFuelAmmount() ) 
			{//for sure
				alpPluginNDmissionsSystem.FuelStations.RemoveItem( station );	
				return coordinates;
			}
			*/
			
			if (!station || !station.IsAlive() )
			{
				alpPluginNDmissionsSystem.FuelStations.Remove( index );
				
				return 	coordinates;			
			}
			
			vector pos = station.GetPosition();
			float x,h,y;
			x = pos[0];
			h = pos[1];
			y = pos[2];		
			coordinates.Insert(x);
			coordinates.Insert(h);
			coordinates.Insert(y);
			coordinates.Insert(0);//TO DO yaw

				
		
			map<int, ref alpMission> missions  = GetND().GetMS().GetMissions();
			foreach( alpMission mb : missions )
			{				
				if ( mb.IsActive() && mb.GetTemplate().distanceRadius > 0 )
				{
					if ( alpUF.VectorDistance( mb.GetPosition() , pos ) < mission.GetTemplate().distanceRadius )
					{
						coordinates.Clear();
						return coordinates;
					}
				}		
			}		
			//check players in radius
			
			if ( IsSomeOneInRadisu( pos,  mission.GetTemplate().missionSafeSpawnRadius) )
			{
				coordinates.Clear();
				return coordinates;			
			}
			
			//delete fuelstation
			alpPluginNDmissionsSystem.FuelStations.RemoveItem( station );
			
			
			return coordinates;
		}
		
		return coordinates;
	}
	
	array<float> GetPosition(alpMission mission)
	{

		
		
		if ( GetND().GetMS().GetPositions( mission.alp_Name ).Count() == 0 )
		{
			ReCopyArray ( mission);	
		}		
		
		array<float> coordinates = new array<float>;
		array<ref array<float>> positions = GetND().GetMS().GetPositions( mission.alp_Name );
		if (  positions.Count() > 0 )
		{
			int random = positions.GetRandomIndex();
			coordinates = positions.Get( random );
			positions.Remove( random );
			
			float x  = Math.RandomFloatInclusive(-1*Math.AbsFloat( mission.GetTemplate().positionOffset ),Math.AbsFloat( mission.GetTemplate().positionOffset) );
			x = coordinates.Get(0) + x;
			
			float y  = Math.RandomFloatInclusive(-1*Math.AbsFloat( mission.GetTemplate().positionOffset ),Math.AbsFloat( mission.GetTemplate().positionOffset) );
			y = coordinates.Get(2) + y;			
			
			coordinates.Set(0,x);
			coordinates.Set(2,y);
			
			vector tempV = Vector( coordinates.Get(0), coordinates.Get(1), coordinates.Get(2) );
			
			//check mission collision
			map<int, ref alpMission> missions  = GetND().GetMS().GetMissions();
				
			foreach( alpMission mb : missions )
			{	
					
				if ( mb.IsActive() && mb.GetTemplate().distanceRadius > 0 )
				{
					if ( alpUF.VectorDistance( mb.GetPosition() , tempV ) < mission.GetTemplate().distanceRadius )
					{
						coordinates.Clear();
						//Print("SELHALO TO NA COORDIANTECH");
						return coordinates;
					}
				}		
			}		
			//check players in radius
			if ( IsSomeOneInRadisu( tempV,  mission.GetTemplate().missionSafeSpawnRadius) )
			{
				coordinates.Clear();
				return coordinates;			
			}
			
				
			return coordinates;
		}
		else 
		{
			return coordinates;	
		}
		
		
	}
	
	bool IsSomeOneInRadisu(vector position, int radius)
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
		return false;
	}
	
	void ReCopyArray (alpMission mission)
	{
		array<ref array<float>> positions = GetND().GetMS().GetPositions( mission.alp_Name );
		positions.Clear();
		
		for ( int x = 0 ; x < mission.GetTemplate().position.Count(); x++)
		{
			
			array<float> coordinates = new array<float>;
			
			for ( int y = 0; y < mission.GetTemplate().position.Get( x ).Count(); y++)
			{
				float value = mission.GetTemplate().position.Get( x ).Get( y );
				coordinates.Insert(value);
			}			
			positions.Insert( coordinates );
		
		}
		
	}
	
	
	
}