
class alpActionManagePlotPole : ActionInteractBase
{
	void alpActionManagePlotPole()	
	{
		m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask        = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;		
	}


	override string GetText()
	{
		return "#pp_title";
	}
	
	override bool HasProgress()
	{
		return false;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		alp_PlotPole plotpole = alp_PlotPole.Cast(targetObject);
		
		if ( plotpole )
		{
			if ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) 
			{
				int playerID = player.GetPlayerID();
				int clanID = player.GetClanID();
				
				if ( plotpole.IsAuthorizedToAccessMenu(playerID,clanID)  )
				{
					
					return true;
				}
				else 
				{					
					return false;
				}
			}			
			
			return true;
		}
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{

		alp_PlotPole plotpole = alp_PlotPole.Cast(action_data.m_Target.GetObject());
		
		if ( plotpole )
		{
			//check if the clanID is actual
			int playerID = action_data.m_Player.GetPlayerID();
			int clanID = action_data.m_Player.GetClanID();	
			plotpole.VerifyActualClanID( playerID, clanID );			
															
			action_data.m_Player.alp_PlotPoleManage = plotpole;					
			
			plotpole.ForceSetSynchDirty(action_data.m_Player);
			
			int stockID = GetStockID( action_data.m_Player.GetPosition() );

			action_data.m_Player.GetRP().GetCart().SetNPCid( stockID ,  0  );//2 par mission ID
			
			action_data.m_Player.GetSyncData().RegisterToStats( true );		
			action_data.m_Player.GetSyncData().ForceSync();
			GetND().GetMS().GetTrader().GiveMeStock( stockID , action_data.m_Player, true );
							
							
		}
	}


	override void OnExecuteClient( ActionData action_data )
	{
		
		alp_PlotPole plotpole = alp_PlotPole.Cast(action_data.m_Target.GetObject());
		
		if ( plotpole )
		{
			int stockID = GetStockID( action_data.m_Player.GetPosition() );
		
			GetND().GetMS().GetTrader().SetNPC(stockID);						
			action_data.m_Player.GetRP().GetCart().SetNPCid( stockID  );			
			
			action_data.m_Player.alp_PlotPoleManage = plotpole;
			if (!GetGame().GetUIManager().FindMenu(ALP_MENU_MANAGE_PLOTPOLE))
			{
						
				GetGame().GetUIManager().EnterScriptedMenu(ALP_MENU_MANAGE_PLOTPOLE, NULL);
			}
		}
	}	

	
	int GetStockID(vector position)
	{
		int stockID = 1;
		
		if ( GetND().GetClans().GetBases().TerritoryCurrency && GetND().GetClans().GetBases().TerritoryCurrency.Count() > 0 )
		{
			for ( int i = 0; i < GetND().GetClans().GetBases().TerritoryCurrency.Count() ; i++ )
			{
				autoptr alpTaxedArea area = GetND().GetClans().GetBases().TerritoryCurrency.Get( i );
				
				vector a = {area.Point1[0], 0, area.Point1[1]};
				vector b = {area.Point2[0], 0, area.Point2[1]};
				
				if ( Math.IsPointInRectangle(a,b,position) )
				{
					stockID = area.StockID;
					break;
				}
				 
			}		
		}		
		return stockID;			
	}

};
