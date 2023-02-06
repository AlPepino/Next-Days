modded class AreaExposureMdfr: ModifierBase
{
	
	override void BleedingSourceCreateCheck(PlayerBase player)
	{
		//zohledneni prirozene odolnosti 
		float naturalProtection = player.GetRP().GetProtection().GetNaturalResistance( alpPROTECTION.CHEMICAL );//uberu mnoztvi o prirozenou odolnost
		if ( naturalProtection >= Math.RandomFloat01() ){
			return;
		}	
		//tuning chemicke ochrany	
		
		int free_bs_locations = 0;//bitmask where each bit set to 1 represents available bleeding source location
		set<int> list = player.GetBleedingManagerServer().GetBleedingSourcesLocations();
		
		foreach(int location: alpProtection.alp_InventorySlots )
		{
			//float prot_level = PluginTransmissionAgents.GetProtectionLevelEx(DEF_CHEMICAL, location, m_Player, true);
			
			float prot_level = player.GetRP().GetProtection().GetProtection( DEF_CHEMICAL, location );
			
		
			
			float dice_throw = Math.RandomFloat01();
			if(dice_throw > prot_level)
			{
				free_bs_locations = player.GetBleedingManagerServer().GetFreeBleedingSourceBitsByInvLocation(location) | free_bs_locations;
			}
		}
		
		int num_of_free_bs = Math.GetNumberOfSetBits(free_bs_locations);//gets us the number of bits set to 1, where each represents a free bleeding source location
		
		if ( num_of_free_bs > 0 )
		{
			int random_bs_index = Math.RandomIntInclusive(0, num_of_free_bs - 1 );// - 1 on the max to convert count to index
			int random_bs_bit = Math.Pow(2, Math.GetNthBitSet(free_bs_locations,random_bs_index));
			player.GetBleedingManagerServer().AttemptAddBleedingSourceDirectly(random_bs_bit, eBleedingSourceType.CONTAMINATED);
		}

	}


	
	override void OnActivate(PlayerBase player)
	{
		if (GetND().GetMS().GetOptions().EnableSafePosition )
		{
			if  ( GetND().GetMS().GetOptions().UseDefaultSafePosition ) 
			{
				JsonDataContaminatedAreas data = EffectAreaLoader.GetData();
				if (data)
				{
					MiscGameplayFunctions.TeleportCheck(player, data.SafePositions);
				}			
			}
			else
			{
				if ( GetND().GetMS().GetOptions().SafePositions ) 
				{
					MiscGameplayFunctions.TeleportCheck(player,  GetND().GetMS().GetOptions().SafePositions );
				}
			}
			
		
		}
				
		//make the player cough immediately
		float transmitted = TransmitAgents(player, 1);
		if(transmitted) 
			player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_COUGH);
		
		m_NextEvent1 = Math.RandomFloatInclusive( EVENT_1_INTERVAL_MIN, EVENT_1_INTERVAL_MAX );
	}


	override float TransmitAgents(PlayerBase player, float count)
	{
		
		float protection = player.GetRP().GetProtection().GetProtectionRespiratory( alpPROTECTION.CHEMICAL );
		
		if ( protection < Math.RandomFloat01() )
		{
			
			count *= ( 1 - player.GetRP().GetProtection().GetNaturalResistance( alpPROTECTION.CHEMICAL ) );//uberu mnoztvi o prirozenou odolnost
			count =  super.TransmitAgents( player, count);
		
			return count;
		}
		
		return 0;
		
	}

};


#ifdef NAMALSK_SURVIVAL	

modded class AreaExposureNamPhoenixMdfr: ModifierBase
{

	override void BleedingSourceCreateCheck(PlayerBase player)
	{
		//zohledneni prirozene odolnosti 
		float naturalProtection = player.GetRP().GetProtection().GetNaturalResistance( alpPROTECTION.CHEMICAL );//uberu mnoztvi o prirozenou odolnost
		if ( naturalProtection >= Math.RandomFloat01() ){
			return;
		}	
		//tuning chemicke ochrany	
		
		int free_bs_locations = 0;//bitmask where each bit set to 1 represents available bleeding source location
		set<int> list = player.GetBleedingManagerServer().GetBleedingSourcesLocations();
		
		foreach(int location: alpProtection.alp_InventorySlots )
		{
			//float prot_level = PluginTransmissionAgents.GetProtectionLevelEx(DEF_CHEMICAL, location, m_Player, true);
			
			float prot_level = player.GetRP().GetProtection().GetProtection( DEF_CHEMICAL, location );
			
		
			
			float dice_throw = Math.RandomFloat01();
			if(dice_throw > prot_level)
			{
				free_bs_locations = player.GetBleedingManagerServer().GetFreeBleedingSourceBitsByInvLocation(location) | free_bs_locations;
			}
		}
		
		int num_of_free_bs = Math.GetNumberOfSetBits(free_bs_locations);//gets us the number of bits set to 1, where each represents a free bleeding source location
		
		if ( num_of_free_bs > 0 )
		{
			int random_bs_index = Math.RandomIntInclusive(0, num_of_free_bs - 1 );// - 1 on the max to convert count to index
			int random_bs_bit = Math.Pow(2, Math.GetNthBitSet(free_bs_locations,random_bs_index));
			player.GetBleedingManagerServer().AttemptAddBleedingSourceDirectly(random_bs_bit, eBleedingSourceType.CONTAMINATED);
		}

	}

	override float TransmitAgents(PlayerBase player, float count)
	{
		
		float protection = player.GetRP().GetProtection().GetProtectionRespiratory( alpPROTECTION.CHEMICAL );
		
		if ( protection < Math.RandomFloat01() )
		{
			
			count *= ( 1 - player.GetRP().GetProtection().GetNaturalResistance( alpPROTECTION.CHEMICAL ) );//uberu mnoztvi o prirozenou odolnost
			count =  super.TransmitAgents( player, count);
		
			return count;
		}
		
		return 0;
		
	}


};


#endif