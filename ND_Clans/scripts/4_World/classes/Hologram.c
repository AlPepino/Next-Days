
modded class Hologram
{


	
	
	override void EvaluateCollision(ItemBase action_item = null)
	{	
		EntityAI ent;
		if (!action_item)
		{
			ent = m_Player.GetHumanInventory().GetEntityInHands();
		}
		else
		{
			ent = action_item;
		}
		
		if (ent) 
		{

			bool is_surface_water = IsSurfaceWater( m_Projection.GetPosition() );	
			if (ent.IsItemBase() )//|| ent.GetType() == "FenceKit" || ent.GetType() == "WatchtowerKit" || ent.GetType() == "alp_PlotPoleKit" || ent.IsContainer() || ent.IsItemTent() )
			{
				if( is_surface_water || !m_Player.IsAuthorized(ItemBase.Cast(ent))  )
				{
					//Print("PREDMET KOLIDUJE  " + is_surface_water);
					SetIsColliding( true );
					return;
				}
				else
				{
					//Print("PREDMET NEKOLIDUJE a LZE STAVET");
					SetIsColliding( false );
					return	
				}			
			}
			super.EvaluateCollision(action_item);
		}
		super.EvaluateCollision(action_item);
	}

	
}

