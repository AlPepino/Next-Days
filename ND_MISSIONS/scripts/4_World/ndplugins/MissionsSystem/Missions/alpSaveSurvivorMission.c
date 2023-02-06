//noRadiation Zone 
class alpSaveSurvivorMission extends alpMission
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
		alp_AlertInfoIn		= ALPMSTYPE.SMPERSONAL;
		alp_AlertInfoOut	= ALPMSTYPE.SMPERSONAL;
		alp_PagerInfoIn		= ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut	= ALPMSTYPE.MMPERSONAL;		
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
		}
				
	}	
	
	
	void SetUpMortality(alpNPC trader){
		bool state = !GetTemplate().godmodTrader;
		trader.GetRP().SetAllowedDamage( state );		
	}
	
	
	
	override protected void ActionClearedArea(float timeslice){
		
		if ( !m_WasStartedSecondPhase ) {
		
		
			if ( alp_NPC && alp_NPC.Count() > 0 ) {
				for( int i = 0; i < alp_NPC.Count();i++ ){
					alpNPC npc = alpNPC.Cast( alp_NPC.Get(i).Get() );
					
					if ( npc && npc.IsAlive() ) {
						//npc.ForceStanceALP(  0 );		
						SetUpMortality(npc);
						GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(npc.ForceStanceALP,500,false,0);	
					}
				}
			}	
			m_WasStartedSecondPhase = true;		
		}

	}	
	
}