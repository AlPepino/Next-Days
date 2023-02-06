class alpActionExamination: ActionInteractBase
{

	
	string alp_Text;
	
	void alpActionExamination()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionTarget = new CCTMan(4);
		m_ConditionItem = new CCINone;
	}


	
	
	override string GetText()
	{
		
		return alp_Text;
		//return "#npc_medicalexamination"; // + alpUF.NumberToString( GetNextDays().GetOptions().GetRP_NPCplus().GetMEfee()  , 1 ) + " #STR_koruny_name";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		int fee;
		int currencyID;

		if (GetGame().IsClient())
		{
			if (GetGame().GetUIManager().FindMenu(ALP_MENU_EXAMINATION) )
				return false;		
		}
		
		alpNPC ntarget = alpNPC.Cast(  target.GetObject() );
		if( ntarget && ntarget.IsAlive() && ntarget.alp_StockID > 0 && ntarget.CanMakeMedicalExamination() && ntarget.CanSpeakWithMe(player) )
		{
			
			fee = player.GetRP().GetMedicalFee( ntarget.alp_StockID , currencyID );
			
			if ( GetGame().IsClient() )
			{
				if ( fee )
				{
					alp_Text = "#npc_medicalexamination " + alpUF.NumberToString( fee  , 1 ) + " " + player.GetRP().GetMedicalFeeCurrenyName();
				}
				else
				{
					alp_Text = "#npc_medicalexamination";
				}			
			}
			if ( GetGame().IsServer() )
			{

				player.GetRP().GetCart().SetNPCid( ntarget.alp_StockID,  ntarget.alp_IDmission  );
				player.GetRP().GetCart().Refresh();
				
				int cash  = player.GetRP().GetCart().GetCash();		
				int totalCash  = player.GetRP().GetCart().GetTotalBalance();	
					
				int isEbank = player.GetRP().GetCart().HasBankAccount();
				
				if ( ( cash >= fee ) || ( isEbank && totalCash >= fee ) )
				{

					//Bank profit
					alpBANK.TakeBusinessProfit(currencyID,  fee  );		
					alpTraderCoreBase.AddBalanceTrader( ntarget.alp_StockID, fee );	
					//pay fee
					int topay = fee;
					int guid = player.GetPlayerHive().GetPlayerID();	
					
					if (isEbank)
					{
						topay += alpBANK.AddBalanceToAccount(guid, currencyID, -fee , player);
						alpBANK.SaveAccount(guid);
					}
					if ( topay )
					{
						cash -= topay;
						
						if ( cash < 0 )
							cash = 0;
						
						player.GetRP().GetCart().GiveMeMoney( cash , currencyID);			
					}
					return true;					
		
				}				
				return false;								
			}

			return true;
		}
		return false;		
		
	}

	override void OnExecuteServer( ActionData action_data )
	{
		
		alpNPC npc = alpNPC.Cast( action_data.m_Target.GetObject() );

		if (npc)
		{
		
			//blood test  
			if ( !action_data.m_Player.HasBloodTypeVisible() && GetND().GetRP().GetInteractions().MedicalFees.EnabledBloodTest )
			{
				
				PluginLifespan module_lifespan = PluginLifespan.Cast( GetPlugin( PluginLifespan ) );
				int blood_type = action_data.m_Player.GetStatBloodType().Get();
			
				module_lifespan.UpdateBloodType( action_data.m_Player, blood_type );
				module_lifespan.UpdateBloodTypeVisibility( action_data.m_Player, true );
				
			}					
			
				
			//run medic examination							
			action_data.m_Player.GetSyncData().RegisterToStats( true );				
			action_data.m_Player.GetSyncData().ForceSync();
			GetND().GetMS().GetTrader().GiveMeStock( npc.alp_StockID , action_data.m_Player, true );			

		}		

	
	}
	
	
	override void OnExecuteClient( ActionData action_data )
	{
		
		alpNPC npc = alpNPC.Cast( action_data.m_Target.GetObject() );

		if (npc)
		{
			GetND().GetMS().GetTrader().SetNPC(npc.alp_StockID);						
			action_data.m_Player.GetRP().GetCart().SetNPCid( npc.alp_StockID  );

			
			if (!GetGame().GetUIManager().FindMenu(ALP_MENU_EXAMINATION) )
			{
				GetGame().GetUIManager().EnterScriptedMenu(ALP_MENU_EXAMINATION, NULL);
			}						
			
		}
		

	}

	

}