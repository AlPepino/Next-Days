ref alpLifeTime								alp_LifeTime;

alpLifeTime GetLifeTimeManager()
{
	if ( !alp_LifeTime )
	{
		alp_LifeTime = new alpLifeTime();
	}

	return alp_LifeTime;
}


class alpLifeTimeItem 
{
	vector Position;
	float Radius;
	int LifeTime
	
	void alpLifeTimeItem(vector v, float radius, int lifetime = ALP_LIFETIMEMAX )
	{
		Position = v;
		Radius = radius;
		LifeTime = lifetime;
	}
}


class alpLifeTime 
{
	
	
	ref array<ref alpLifeTimeItem> alp_Bases;
	
	void alpLifeTime()
	{
		alp_Bases = new array<ref alpLifeTimeItem>;
	}
		
	
	void AddBase( alpLifeTimeItem base)
	{
		alp_Bases.Insert(base);	
	}

	
	void UpdateLifeTime()
	{
		//Print("life time management");
		for ( int i = 0; i < alp_Bases.Count();i++)
		{
			alpLifeTimeItem item = 	alp_Bases.Get(i);					
			SetLifeTime( item.Position, item.Radius, item.LifeTime );
		}
	
	}

	
	
	void SetLifeTime( vector pos, float radius, int lifetime = ALP_LIFETIMEMAX )
	{

		autoptr array<Object> nearest_objects = new array<Object>;
		autoptr array<CargoBase> proxy_cargos = new array<CargoBase>;
		
		GetGame().GetObjectsAtPosition( pos, radius, nearest_objects, proxy_cargos ); 	
		for (int i = 0; i < nearest_objects.Count();i++)
		{
			ItemBase item; 
			float lt;
			if ( Class.CastTo( item, nearest_objects.Get(i) ) && item.IsBuildingALP() )
			{
				lt = item.GetLifetimeMax();
				//SetLifetimeMax( lifetime );
				item.SetLifetime( lt );//  3888000 ALP_LIFETIMEMAX			 					
			}
			else
			{
				Transport vehicle;
				
				if ( Class.CastTo( vehicle, nearest_objects.Get(i) ) )
				{
					lt = vehicle.GetLifetimeMax();
					vehicle.SetLifetime( lt );//  3888000 ALP_LIFETIMEMAX						
				}
			}
		}		
	}			
}