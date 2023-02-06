

modded class ActionFishingNewCB : ActionContinuousBaseCB
{


	override void HandleFishingResultSuccess()
	{
		if ( !GetND().GetRP().GetPerksOptions().EnablePerkHunting  )
		{
			super.HandleFishingResultSuccess();
			return;
		}
		
		if (!GetGame().IsMultiplayer() || GetGame().IsServer())
		{
			int level = m_ActionDataFishing.m_Player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue(); 
			float hunting = GetND().GetRP().GetPerkHuntingMdf( level );			
			
			ItemBase fish;

			if (!m_ActionDataFishing.m_Bait)
				m_ActionDataFishing.InitBait(ItemBase.Cast(m_ActionDataFishing.m_MainItem.FindAttachmentBySlotName("Hook")));
			
			if (!m_ActionDataFishing.IsBaitEmptyHook())
			{
				m_ActionDataFishing.m_Bait.AddHealth(-m_ActionDataFishing.FISHING_DAMAGE);
				MiscGameplayFunctions.TurnItemIntoItem(m_ActionDataFishing.m_Bait,m_ActionDataFishing.m_Bait.ConfigGetString("hookType"),m_ActionDataFishing.m_Player);
			}
			else
			{
				m_ActionDataFishing.m_Bait.AddHealth(-m_ActionDataFishing.FISHING_DAMAGE);
			}
			
			float rnd = Math.RandomFloatInclusive(0.0,1.0);
			if (rnd > ( m_ActionDataFishing.FISHING_GARBAGE_CHANCE / hunting ))
			{
				if (m_ActionDataFishing.m_IsSurfaceSea)
					fish = ItemBase.Cast(GetGame().CreateObjectEx("Mackerel",m_ActionDataFishing.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
				else
					fish = ItemBase.Cast(GetGame().CreateObjectEx("Carp",m_ActionDataFishing.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
				
				//alpExpandedInteraction
				m_ActionDataFishing.m_Player.GetRP().ChangeHunting( GetEXPtoHunting() );	
				
				if (m_ActionDataFishing.m_Player.GetRP().IsHero())
				{
					IncreaseReputationALP( m_ActionDataFishing.m_Player,	ALP_RP_HERO);
				}	
				else 
				{
					IncreaseReputationALP( m_ActionDataFishing.m_Player,	ALP_RP_BANDIT );
				}
				m_ActionDataFishing.m_Player.GetStatCountAnimals().Add(1);								
			}
			else
			{
				if ( !m_ActionDataFishing.m_IsSurfaceSea )
				{
					string junk_type = m_JunkTypes.Get(Math.RandomInt(0,m_JunkTypes.Count()));
					fish = ItemBase.Cast(GetGame().CreateObjectEx(junk_type,m_ActionDataFishing.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
					fish.SetHealth("","Health",fish.GetMaxHealth("","Health") * 0.1);
				}
			}
			
			if (fish)
			{
				//Print("---Caught something: " + fish + "---");
				fish.SetWet(0.3);
				if (fish.HasQuantity())
				{
					float coef = Math.RandomFloatInclusive(0.5, 1.0);
					float item_quantity = fish.GetQuantityMax() * coef;
					item_quantity = Math.Round(item_quantity);
					fish.SetQuantity( item_quantity );
				}
			}
			
			m_ActionDataFishing.m_MainItem.AddHealth(-m_ActionDataFishing.FISHING_DAMAGE / hunting );				

		}
	}
	float GetEXPtoHunting()
	{
		
		return GetND().GetRP().GetPerkHunting().KillAnimal;
	}
	void IncreaseReputationALP( PlayerBase player, int role)
	{						
		player.GetRP().ChangeReputation(   GetND().GetRP().GetReputationBonusKillAnimal( role ) );			
	}	
};


modded class ActionFishingNew: ActionContinuousBase
{
	override int EvaluateFishingResult(ActionData action_data)
	{
		if ( !GetND().GetRP().GetPerksOptions().EnablePerkHunting )
		{			
			return super.EvaluateFishingResult(action_data);
		}
		
		int level = action_data.m_Player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue(); 
		float hunting = GetND().GetRP().GetPerkHuntingMdf( level );		

		if (action_data.m_Player.IsQuickFishing())
			return 1;
		
		FishingActionData fad = FishingActionData.Cast(action_data);
		float rnd = fad.m_Player.GetRandomGeneratorSyncManager().GetRandom01(RandomGeneratorSyncUsage.RGSGeneric);
		float daytime_modifier = 1;
		float hook_modifier = 1;
		float chance;
		
		daytime_modifier = GetGame().GetDayTime();
		if ( (daytime_modifier > 18 && daytime_modifier < 22) || (daytime_modifier > 5 && daytime_modifier < 9) )
		{
			daytime_modifier = 1;
		}
		else
		{
			daytime_modifier = 0.5;
		}
		
		//fishing with an empty hook
		if (fad.IsBaitEmptyHook())
		{
			hook_modifier = 0.05;
		}
		
		chance = 1 - (((fad.FISHING_SUCCESS * daytime_modifier) + fad.m_RodQualityModifier)) * hook_modifier * hunting;
		
		if (rnd > chance)
		{
			return 1;
		}
		else if (rnd < fad.FISHING_BAIT_LOSS && !fad.IsBaitEmptyHook()) // restricts the loss of an empty hook (low chance is enough)
		{
			return 0;
		}
		return -1;
	}
};

