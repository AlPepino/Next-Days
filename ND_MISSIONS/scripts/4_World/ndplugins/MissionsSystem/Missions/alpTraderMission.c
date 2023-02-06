
//Trader Mission
class alpTraderMission extends alpMission
{

//-------------------------------------------------------------------
//***************************//
//adjust default setting
//***************************//			
	override void OnInit()
	{
		//messages setting
		alp_SendInfoStart	= ALPMSTYPE.MMTRADERSTART;
		alp_SendInfoEnd		= ALPMSTYPE.MMTRADEREND;
		alp_AlertInfoIn		= ALPMSTYPE.SMTRADERIN;
		alp_AlertInfoOut	= ALPMSTYPE.SMTRADEROUT;
		alp_PagerInfoIn		= ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut	= ALPMSTYPE.MMPERSONAL;		
	}

	

//-------------------------------------------------------------------
//***************************//
//Rewrite default methods
//***************************//		
	override protected void OnEnter(Object obj )
	{
		super.OnEnter(obj);
		
		//SetSetting( alpMISSION_SETTING.MISSION_IDLE ); //can be despawned by time
		
		PlayerBase player;
		
		if ( Class.CastTo( player, obj) ) 
		{
			
			bool state = !GetTemplate().godmodPlayers;
			player.GetRP().SetAllowedDamage( state );
			player.GetRP().SetInTradeZone( true );			


					
		}								
	};	

	override protected void OnLeave(Object obj )
	{
		super.OnLeave(obj);
		PlayerBase player;
		if ( Class.CastTo( player, obj) ) 
		{
			player.GetRP().SetAllowedDamage( true );
			player.GetRP().SetInTradeZone( false );			
						
		}		
		
	};		

	override void OnLeavePlayer(PlayerBase player) 	
	{
		super.OnLeavePlayer(player);
		player.GetRP().SetAllowedDamage( true );
		player.GetRP().SetInTradeZone( false );				
	}
	
	override protected bool CheckFailedCondition(float timeslice) {	
		if ( !IsNPCAlive() ) {
			return true;
		}
		return false;
	}	


//-------------------------------------------------------------------
//***************************//
//Private usefull methods
//***************************//		
		

	override void SetUpNPC(Man npc, alpMissionAddNPC template)
	{
		super.SetUpNPC(npc,template);
		
		
		alpNPC trader;
		
		if ( Class.CastTo( trader, npc ) ) //&& template.StockID > 0 )
		{
					
			
			bool state = !GetTemplate().godmodTrader;
			trader.GetRP().SetAllowedDamage( state );

			trader.alp_StockID = template.StockID;
			trader.alp_IDmission = GetID();		
		}
			
	}
}