//noRadiation Zone 
class alpSaveMerchantsMission extends alpMission
{
	
	bool m_WasStartedSecondPhase;

//-------------------------------------------------------------------
//***************************//
//adjust default setting
//***************************//			
	override void OnInit()
	{
		//messages setting
		alp_SendInfoStart	= ALPMSTYPE.MMMISSIONSTART;
		alp_SendInfoEnd		= ALPMSTYPE.MMMISSIONEND;
		alp_AlertInfoIn		= ALPMSTYPE.SMTRADERIN;
		alp_AlertInfoOut	= ALPMSTYPE.SMTRADEROUT;
		alp_PagerInfoIn		= ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut	= ALPMSTYPE.MMPERSONAL;		
	}

	
	override protected void OnEnter(Object obj )
	{
		RemoveSetting( alpMISSION_SETTING.MISSION_IDLE );	
		
		if ( !IsCleared() ){//stage not ready
			return;
		}
					
		if (obj.IsMan() && GetTemplate().alertInfo && GetTemplate().alertMessageIn != "" )
		{
			GetND().GetNotf().SendMissionMessage( alp_AlertInfoIn	,GetID(),  GetTemplate().alertMessageIn, GetPosition() , PlayerBase.Cast( obj) );	
		}
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
	
		if ( !IsCleared() ){//stage not ready
			return;
		}			
			
		if (obj.IsMan() && GetTemplate().alertInfo && GetTemplate().alertMessageOut != "")
		{
			GetND().GetNotf().SendMissionMessage(  alp_AlertInfoOut	,GetID(), GetTemplate().alertMessageOut, GetPosition() , PlayerBase.Cast( obj) );
		}
			
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

	
	

//-------------------------------------------------------------------
//***************************//
//Rewrite default methods
//***************************//		
	override protected bool CheckFailedCondition(float timeslice) {	
		if ( !IsNPCAlive() ) {
			return true;
		}
		return false;
	}	
	
	
	override void SetUpNPC(Man npc, alpMissionAddNPC template)
	{
		super.SetUpNPC(npc,template);
		
		
		alpNPC trader;
		
		if ( Class.CastTo( trader, npc ) )
		{		
			trader.alp_StockID = template.StockID;
			trader.alp_IDmission = GetID();		
			
			if ( IsCleared() ){
				SetUpMortality( trader );
			}
			
		}
				
	}	
	

	void SetUpMortality(alpNPC trader){
		bool state = !GetTemplate().godmodTrader;
		trader.GetRP().SetAllowedDamage( state );		
		trader.SetSynchDirty();
	}
	
	
	override protected void ActionClearedArea(float timeslice){
		//nastavit vsechny hrace na onEnter a to same NPC
		if ( !m_WasStartedSecondPhase ) {
			int i = 0;
			if ( alp_NPC && alp_NPC.Count() > 0 ) {
				for( i = 0; i < alp_NPC.Count();i++ ){
					alpNPC npc = alpNPC.Cast( alp_NPC.Get(i).Get() );
					
					if ( npc && npc.IsAlive() ) {
						//npc.ForceStanceALP(  0 );		
						SetUpMortality(npc);
						GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(npc.ForceStanceALP,1000,false,0);	
					}
				}
			}	
			for(i = 0; i < alp_Insiders.Count(); i++)
			{	
				alpMissionInsider ins = alp_Insiders.Get(i);
				PlayerBase player;
				if ( ins.alp_DamageZone && Class.CastTo( player, ins.GetObject() ) && player.IsAlive() ) {
					OnEnter(player); 			
				}
			}				
			
			m_WasStartedSecondPhase = true;		
		}

	}	
	
}