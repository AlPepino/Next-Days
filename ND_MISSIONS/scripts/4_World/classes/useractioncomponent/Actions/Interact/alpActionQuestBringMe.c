
// Script File
class alpActionQuestBringMe: ActionInteractBase
{
	void alpActionQuestBringMe()
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

	string alp_WantedItemName;
	override string GetText()
	{
		return "#trader_give_items - " + alp_WantedItemName;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( GetGame().IsClient() )
		{
			alpNPC ntarget = alpNPC.Cast(  target.GetObject() );
			if( ntarget && ntarget.IsAlive()  && ntarget.alp_StockID && ntarget.CanSpeakWithMe(player) && ntarget.IsErectedALP() ) //NPC without trade can be negative marked
			{
			
				int id = ntarget.alp_StockID;

				array<ref alpTraderQuest> quests = GetND().GetQuestByNPC_ID( id );
				
				if ( quests && HasSomethingUsefull( player, quests ) )  				
				{
					return true;
				}

				return false;
			}		
			return false;
		}
		return true;
	}
	
	bool HasSomethingUsefull( PlayerBase player, array<ref alpTraderQuest> quests ) {
		int count;
		string title;
		for(int i = 0; i < quests.Count();i++){
			alpTraderQuest q = quests.Get(i);
			string t = VerifyItemALP( player, q.WantedItemAllowedType , q.WantedItem , q.WantedRequiredCount );
			if ( t != "" ){
				count++;
				title += t + " ";
			}			
		}
		alp_WantedItemName = title;
		return count;
	}
	
	
	string VerifyItemALP(PlayerBase player, string parent , string type , int count)
	{
		int own = 0;

		Transport car = player.GetRP().GetCar();		
		if ( car && count == 1 && ( car.GetType() == type || ( parent != STRING_EMPTY && GetGame().IsKindOf(car.GetType(), parent ) ) ) )
		{			
			return car.GetDisplayName();	
		}
		autoptr array<EntityAI> itemsArray = new array<EntityAI>;
		ItemBase item;
		int i;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		for (i = 0; i < itemsArray.Count(); i++)
		{	
			item = ItemBase.Cast(itemsArray.Get(i));
			if ( item && ( item.GetType() == type  || ( parent != STRING_EMPTY && GetGame().IsKindOf(item.GetType(), parent ) ) )   )
			{
				own += 1;
				if ( own >= count )
				{
					return item.GetDisplayName();
				}
			}			
		}
		return "";	
	}
	
	
	void ReputationReward(PlayerBase player, float exp)
	{
		player.GetRP().ChangeReputation(  exp );	
	}

	override void OnExecuteServer( ActionData action_data )
	{
		alpNPC npc = alpNPC.Cast( action_data.m_Target.GetObject() );

		if (npc)
		{
			action_data.m_Player.GetRP().GetCart().SetNPCid( npc.alp_StockID  );		

			array<int> questsID =  GetND().GetActiveQuestID( npc.alp_StockID  );
			
			foreach ( int qID : questsID ){
				alpTraderQuest quest = GetND().GetQuest(qID);		
				if ( quest )
				{	
					int price = GiveItems( action_data.m_Player , quest );		
					if ( price )
					{//get reward
						if ( quest.RewardPrice )
						{//money
							int currency =  npc.GetCurrencyID(); //GetND().GetActiveQuestCurrency( npc.alp_StockID );	 
							price = (int) ( price * quest.RewardPrice *  alpBANK.GetCurrencyRate( currency ) ); //quest.WantedRequiredCount *
							
							action_data.m_Player.GetRP().GetCart().GiveMeJustMoney( price, currency );
						}
						if ( quest.RewardReputation )
						{//reputation
							ReputationReward( action_data.m_Player, quest.RewardReputation );
						}						
						if ( quest.RewardItem != STRING_EMPTY )
						{//items
							if ( !GetGame().IsKindOf( quest.RewardItem, "CarScript")  )
							{
								bool checkedLootTable = false;
								EntityAI ent;
								for(int i = 0; i < quest.RewardGivenCount; i++)
								{
									
									if ( !checkedLootTable )
									{
										alpLoot loot = GetND().GetMS().alp_LootMap.Get(quest.RewardItem);
										
										if ( loot )
										{
											if ( !alpMission.SpawnCargo(action_data.m_Player,loot, 1) )
											{
												checkedLootTable = true;
												GetGame().CreateObject( quest.RewardItem ,action_data.m_Player.GetPosition(),false,false,true);	
											}
										}
										else
										{
											checkedLootTable = true;
											ent = action_data.m_Player.GetRP().GetCart().InsertIntoCart( quest.RewardItem );
											if (!ent)
											{									
												GetGame().CreateObject( quest.RewardItem ,action_data.m_Player.GetPosition(),false,false,true);	
											}									
										}
										
									}
									else
									{
										ent = action_data.m_Player.GetRP().GetCart().InsertIntoCart( quest.RewardItem );
										if (!ent)
										{									
											GetGame().CreateObject( quest.RewardItem ,action_data.m_Player.GetPosition(),false,false,true);	
										}									
									}

								}
							}
						}					
						
						npc.FinishNPCquest(qID);
						
						string name;				
						if ( GetND().GetMS().GetOptions().ShowRealPlayerName ) {
							name = action_data.m_Player.GetIdentity().GetName();	
						} else {
							name = action_data.m_Player.GetDisplayName();
							
						}
						
						GetND().GetNotf().SendMissionMessage( ALPMSTYPE.MMPERSONAL	, -1, name + " #alp_questcompletedby #pos", npc.GetPosition(), null, true );	
					}
				}
				
			}				
		}	
	}

	int GiveItems( PlayerBase player, alpTraderQuest quest )
	{
	
		string type = quest.WantedItem;
		string parent = quest.WantedItemAllowedType;
		int count = quest.WantedRequiredCount;
		int price,own;
		Transport tr = player.GetRP().GetCar();	
		
		if (tr && tr.IsKindOf("CarScript") ) {
			CarScript car = CarScript.Cast( tr );
			if ( car ) {
				if ( count == 1 && ( car.GetType() == type || ( parent != STRING_EMPTY && GetGame().IsKindOf(car.GetType(), parent ) ) ) )	
				{
		
					price = car.GetDefaultPrice();
					GetGame().ObjectDelete( car );
					if  ( quest.StoreAt ) {
						alpTraderCoreBase.AddCount( quest.StoreAt, type, count );
					}				
					return price;
				}			
			
			}			
		} else if ( tr &&  tr.IsKindOf("HelicopterScript") ) {  
			HelicopterScript heli = HelicopterScript.Cast( tr );
			if ( heli ) {
				if ( count == 1 && ( heli.GetType() == type || ( parent != STRING_EMPTY && GetGame().IsKindOf(heli.GetType(), parent ) ) ) )	
				{
		
					price = heli.GetDefaultPrice();
					GetGame().ObjectDelete( heli );
					if  ( quest.StoreAt ) {
						alpTraderCoreBase.AddCount( quest.StoreAt, type, count );
					}				
					return price;
				}			
			
			}				
		}
		
		

		
		autoptr array<EntityAI> itemsArray = new array<EntityAI>;
		ItemBase item;
		int i;
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		for (i = 0; i < itemsArray.Count(); i++)
		{	

			item = ItemBase.Cast(itemsArray.Get(i));
			if ( item && ( item.GetType() == type  || ( parent != STRING_EMPTY && GetGame().IsKindOf(item.GetType(), parent ) ) )   )
			{
				price += item.GetDefaultPrice();
				own += 1;
				GetGame().ObjectDelete( item );
				if ( own >= count )
				{
					if  ( quest.StoreAt ) {
						alpTraderCoreBase.AddCount( quest.StoreAt, type, count );
					}					
					return price;
				}
			}			
		}
		return 0;	
	}

}