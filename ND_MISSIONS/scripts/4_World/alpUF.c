//Alpepino usefull function
//-------------------------
class alpUF
{
	//maths methods
	//------------------
	static float VectorDistance(vector v1, vector v2) //, bool only2D = true ) //return distance regardless H-coordinate
	{
		/*
		if ( only2D )
		{
			v1[1] = 0;
			v2[1] = 0;
		}
		*/
		if ( v1[1] == 0 || v2[1] == 0)
		{
			v1[1] = 0;
			v2[1] = 0;	
		}
		
		return 	vector.Distance( v1,v2);
	}
	//collsion 
	//------------------
	static bool NoCollisionObjects( Object obj )
	{
		if ( obj ) {
			//collision check	
			vector position = obj.GetPosition();		
			vector minMax[2];
			obj.GetCollisionBox(minMax);			
			float radius = vector.Distance(minMax[0],minMax[1]);
			autoptr array<Object> nearest_objects = new array<Object>;
			autoptr array<CargoBase> proxy_cargos = new array<CargoBase>;
			
			GetGame().GetObjectsAtPosition( position, radius, nearest_objects, proxy_cargos ); 	
			for (int i = 0; i < nearest_objects.Count();i++){
				
				if (nearest_objects.Get(i))
				{
					if (nearest_objects.Get(i).IsBush() || nearest_objects.Get(i).IsTree() && nearest_objects.Get(i).IsCuttable() )
					{
						GetGame().ObjectDelete(nearest_objects.Get(i));
					}
									
				}
			}				
		}

		return true;
	}
	static bool IsColliding( Object obj )
	{
		/*
		vector center;
		float absolute_ofset = 0.05; 
		vector edge_length;
		vector min_max[2];
		array<Object> excluded_objects = new array<Object>;
		array<Object> collided_objects = new array<Object>;		
		excluded_objects.Insert( obj );
		
		obj.GetCollisionBox(min_max);	
		center = GetBoxCenter( min_max );
		edge_length = GetCollisionBoxSize( min_max );
		
		if ( GetGame().IsBoxCollidingGeometry( Vector( center[0], center[1] + absolute_ofset, center[2] ),obj.GetOrientation(), edge_length, ObjIntersectView, ObjIntersectGeom, excluded_objects, collided_objects ) )
		{
			//Debug
//				DrawDebugCollisionBox( min_max, ARGB( 150, 255, 0, 0 ) );
			//
			for (int i = 0; i < collided_objects.Count(); i++)
			{
				//Print(collided_objects.Get(i).GetType());
				EntityAI entity = EntityAI.Cast(collided_objects.Get(i));
				if ( entity  )
					return true;
			}
		}
		return false;
		*/
		
		//collision check		
		vector minMax[2];
		
		obj.GetCollisionBox(minMax);			
		float radius = vector.Distance(minMax[0],minMax[1]);
		vector box = Vector(radius,radius,radius);
		
		array<Object> excluded_objects = new array<Object>;
		array<Object> nearby_objects = new array<Object>;
		excluded_objects.Insert( obj);
	
		if ( GetGame().IsBoxColliding( obj.GetPosition(),obj.GetOrientation(),box, excluded_objects,nearby_objects) )
			return true;
		else
			return false;
		
		
		
		
	}
	static vector GetBoxCenter( vector min_max[2] )
	{
		vector center;
		
		center[0] = ( min_max[1][0] - min_max[0][0] ) / 2;
		center[1] = ( min_max[1][1] - min_max[0][1] ) / 2;
		center[2] = ( min_max[1][2] - min_max[0][2] ) / 2;
		center = Vector( min_max[1][0] - center[0], min_max[1][1] - center[1], min_max[1][2] - center[2] ); //offset to box center
		
		return center;
	}	
	static vector GetCollisionBoxSize( vector min_max[2] )
	{
		vector box_size = Vector( 0, 0, 0 );
		
		box_size[0] = Math.AbsFloat( min_max[1][0] - min_max[0][0] );
		box_size[1] = Math.AbsFloat( min_max[1][1] - min_max[0][1] );
		box_size[2] = Math.AbsFloat( min_max[1][2] - min_max[0][2] );
		
		return box_size;
	}		
	//working with items
	//------------------
	
	static void RemoveAttachments(PlayerBase player)
	{
			ItemBase item;
			for ( int i = 0; i < player.GetInventory().GetAttachmentSlotsCount(); ++i )
			{
				item = ItemBase.Cast( player.GetInventory().FindAttachment(i) );
				if ( item )
				{
					GetGame().ObjectDelete(item);
				}
			}

			ItemBase item_in_hands = ItemBase.Cast( player.GetHumanInventory().GetEntityInHands() );

			if ( item_in_hands )
			{
				GetGame().ObjectDelete(item_in_hands);
			}
	}
	
	static void RemoveAllItems(ItemBase inventory)
	{
		if (inventory)
		{
			array<EntityAI> itemsArray = new array<EntityAI>;
			ItemBase item;
			inventory.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			
			for (int i = 0; i < itemsArray.Count(); i++)
			{				
				if ( Class.CastTo(item, itemsArray.Get(i)) && item!=inventory) 
				{
					GetGame().ObjectDelete(item);
				}
			}		
		}
	}		
	static void RemoveAllItemsFromPlayer(PlayerBase player)
	{
		if (player)
		{
			array<EntityAI> itemsArray = new array<EntityAI>;
			ItemBase item;
			player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			
			for (int i = 0; i < itemsArray.Count(); i++)
			{				
				if ( Class.CastTo(item, itemsArray.Get(i)) && !item.IsInherited(SurvivorBase)) 
				{
					GetGame().ObjectDelete(item);
				}
			}		
		}
	}	

	
	//trader fce
	//------------------
	
	static string GetDisplayName(string className)
	{
		string name;
		TStringArray cfg = {"CfgVehicles ","CfgWeapons ","CfgMagazines ","CfgAmmo "};
		foreach(string p : cfg){
			GetGame().ConfigGetText(p + className + " displayName", name);
			if (name!=""){
				className = name;
				break;
			}
		}
		className.Replace("$UNT$", "");
		return className;
	}

	
	static string NumberToString(float value, int k = 1000)
	{
		int 			v 		= value* k ;		
		string 			text 	= v.ToString();
		int 			len 	= text.Length();
		string 			output  = "";
		int				s=0;
		len -=1;
		for (int i=len; i>=0;i--){
			
			if (s==3 || s==6 || s==9){
				output = text.Get(i) + " " + output;
			}
			else output = text.Get(i) + output;
			s++;
		}
		return output;
	}	
	static void FillFluidsToVehicle( Transport transport , bool fill = true, bool missionObject = false , float minFuel = 0, float maxFuel = 0 )
	{
		CarScript car;
		
		if ( Class.CastTo( car, transport) )
		{
			if ( fill )
			{
				if ( maxFuel ) {
					float fuel = car.GetFluidCapacity( CarFluid.FUEL );					
					float coef = Math.RandomFloatInclusive(minFuel,maxFuel);
					fuel*=coef;
					car.Fill( CarFluid.FUEL,fuel );	
					
				} else {
					car.Fill( CarFluid.FUEL,car.GetFluidCapacity( CarFluid.FUEL ) );				
				}
				
				
				car.Fill( CarFluid.COOLANT, car.GetFluidCapacity( CarFluid.COOLANT ));
				car.Fill( CarFluid.OIL, car.GetFluidCapacity( CarFluid.OIL ));				
			}
			car.SetMissionObjectState ( missionObject );
			return;		
		}
		HelicopterScript heli;
		if ( Class.CastTo( heli, transport) )
		{
			if ( fill )
			{
			}			
			heli.SetMissionObjectState ( missionObject );
			return;
		}		
		
	}		

};
//end Alpepino usefull function
//-------------------------