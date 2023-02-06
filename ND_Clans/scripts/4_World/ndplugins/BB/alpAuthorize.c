
class alpAuthorize
{
	PlayerBase						m_Player;
	
	void alpAuthorize(PlayerBase player)
	{
		m_Player = player;
	}
		
	
	bool IsAuthorized(ItemBase item)
	{
		if ( GetGame().IsServer() ) 
			return true;

		if ( m_Player.GetSyncData().GetElement( alpRPelements.ISINTRADERZONE ).GetValue() )
			return false;				
		
		bool ispp = false;
		
		if ( item && ( item.IsKindOf("alp_PlotPoleKit") ||  item.IsKindOf("alp_PlotPole") ) ){			
			ispp = true;			
		}

		float	dist;
		int 	pID,cID;		
		int     r;

		pID = m_Player.GetPlayerID();
		cID = m_Player.GetClanID();
		
		foreach (EntityAI ent : ClientData.PlotPoleList){
			alp_PlotPole pp = alp_PlotPole.Cast(ent);
			
			if (pp)
			{				
				if (pp.alp_Radius && (!pp.IsAuthorized(pID,cID) || ( ispp && pp != item ) ) )
				{
					dist = alpUF.VectorDistance(pp.GetPosition(),m_Player.GetPosition());
					
					if ( ispp )
						r = pp.GetMaxRadius() * 2;
					else 	
						r = pp.GetRadius();
							
					if ( dist <= r ) 
						return false;
				}					

			}
		}
		
		if ( GetND().GetClans().GetBases().DisablePlacingObjectOutsideClaimedArea )
		{
			if ( m_Player.GetRP().IsHome() )
				return true;

			//checking safeZone
			if (GetND().GetClans().GetBases().EnableRestrictedArea && GetND().GetClans().GetBases().RestrictedAreas && GetND().GetClans().GetBases().RestrictedAreas.Count() > 0)
			{
				foreach(vector v : GetND().GetClans().GetBases().RestrictedAreas)
				{
					vector tempV = Vector(v[0],0,v[1]);
					dist = alpUF.VectorDistance(tempV,m_Player.GetPosition());
					if ( dist <= v[2] )
						return false;				
				}							
			}									
			//searching for exceptions
			foreach(string exception : GetND().GetClans().GetBases().PlacingExceptions)
			{
				if ( item && ( item.GetType() == exception || item.IsKindOf(exception) ) )
				{					
					return true;
				}
				//hotfix due to fucking foreign mods
				if (exception.Contains("TentBase") && item.IsItemTent() ){
					return true;
				}
				if (exception.Contains("Container") && item.IsContainer() ){
					return true;
				}				
				
			}											
			return false;
		}
		return true;
	}	
	
	bool IsAuthorized()
	{

		float	dist;
		int 	pID,cID;		
		int     r;
		
		
		pID = m_Player.GetPlayerID();
		cID = m_Player.GetClanID();		
		
		
		foreach (EntityAI ent : ClientData.PlotPoleList)
		{
			alp_PlotPole pp = alp_PlotPole.Cast(ent);
			
			if (pp)
			{
				if (pp.alp_Radius && !pp.IsAuthorized(pID,cID) && !m_Player.GetSyncData().GetElement( alpRPelements.ISINTRADERZONE ).GetValue() )
				{
					dist = alpUF.VectorDistance(pp.GetPosition(),m_Player.GetPosition());
					
					r = pp.GetRadius();
					
					if ( dist <= r ) 
						return false;
				}
			}
		}
			
		return true;
	}

	
}