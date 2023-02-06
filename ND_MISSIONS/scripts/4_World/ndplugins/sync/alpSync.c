
class alpSync 
{
	PlayerBase					alp_Player;
	
	
	
	
	//bit sync
	ref array<int> 				alp_LastSentStats;
	const int 					NUMBER_OF_ELEMENTS 									= alpRPelements.COUNT;	
	ref alpStatsBase 			alp_Elements[NUMBER_OF_ELEMENTS];	
	
	//float sync
	bool 						alp_IsRegisterToEnhancedStat;
	//bool 						alp_IsRegisterToRadiationStat;
	const int 					NUMBER_OF_ELEMENTS_ENHANCED 						= alpRPelementsEnahnced.COUNT;
	ref alpStatsBaseEnhanced 	alp_ElementsEnhanced[NUMBER_OF_ELEMENTS_ENHANCED];		
	 					
	
	void alpSync(PlayerBase player)
	{
		alp_Player = player;
		
		
		Init();
		
	}
	
	PlayerBase GetPlayer()
	{
		return alp_Player;
	}
	
	void Init()
	{
		//RegisteStats		
		RegisterElement( new alpStatsIsAllowDamage( alp_Player ) );
		RegisterElement( new alpStatsIsInTradeZone( alp_Player ) );		
		
		RegisterElement( new alpStatsIsRained( alp_Player ) );		
		
		
		//RegisterElementEnhancedStats
		RegisterElementEnhanced( new alpStatsEnhancedHealth(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedBlood(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedWater(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedFood(alp_Player) );	
		RegisterElementEnhanced( new alpStatsEnhancedStomach(alp_Player) );	
		
		RegisterElementEnhanced( new alpStatsEnhancedStomach(alp_Player) );		
		
		RegisterElementEnhanced( new alpStatsEnhancedRadiationDoses( alp_Player ) );	
		
		RegisterElementEnhanced( new alpStatsEnhancedTraderBalance( alp_Player ) );	
		RegisterElementEnhanced( new alpStatsEnhancedPlayerBalance( alp_Player ) );
	}
	
	float alp_TICK;
	
	void OnScheduledTick(float deltaTime)
	{

		if( GetGame().IsServer() )
		{
			alp_TICK+=deltaTime;
			if(alp_TICK > 1)
			{
				ForceSync();
				alp_TICK = 0;
			}
		}
	}	
	
	/*
	bool IsRegisteredToRadiation()
	{
		return alp_IsRegisterToRadiationStat;
	}	
	*/
	bool IsRegisteredToEnhanced()
	{
		return alp_IsRegisterToEnhancedStat;
	}
	
	void RegisterToStats(bool state)
	{

		alp_IsRegisterToEnhancedStat = state;
	}
	/*
	void RegisterToRadiation(bool state)
	{

		alp_IsRegisterToRadiationStat = state;
	}
	*/
	protected void RegisterElement( alpStatsBase element)
	{
		int id = element.GetType();
		alp_Elements[id] = element;
	}

	alpStatsBase GetElement(alpRPelements element_id)
	{
		if( element_id < 0 || element_id >= NUMBER_OF_ELEMENTS )
		{
			return null;
		}
		return alp_Elements[element_id];
	}
	
	protected void RegisterElementEnhanced( alpStatsBaseEnhanced element)
	{
		int id = element.GetType();
		alp_ElementsEnhanced[id] = element;
	}

	alpStatsBaseEnhanced GetElementEnhanced(alpRPelementsEnahnced element_id)
	{
		if( element_id < 0 || element_id >= NUMBER_OF_ELEMENTS_ENHANCED )
		{
			return null;
		}
		return alp_ElementsEnhanced[element_id];
	}	
			
	void OnRPC_RP_STATS(ParamsReadContext ctx)//on Client
	{	
		array<int> mask_array = new array<int>;
		ctx.Read(mask_array); 
		
		DeserializeStats(mask_array);

	}		
	void DeserializeStats(ref array<int> mask_array )
	{
		int maskArrayIndex = 0;
		int offset = 0;
		int mask = 0;
		
		for(int i = 0; i < NUMBER_OF_ELEMENTS;i++)
		{
			if( GetElement(i) )
			{
				//Log("entity> " + ToString(GetElement(i)) );
				if(offset + GetElement(i).GetNumberOfBits() > BIT_INT_SIZE)
				{
					maskArrayIndex++;
					offset = 0;
				}
				mask = mask_array.Get(maskArrayIndex);
				int value = BitToDec( mask, offset, GetElement(i).GetCompareMask() );
				offset = offset + GetElement(i).GetNumberOfBits();
				GetElement(i).SetValue( value );
				//HOTFIX 
				if ( i == alpRPelements.REPUTATION && alp_Player.GetIdentity() ) {
					alp_Player.GetIdentity().SetPlayerLevel( value );	
				}
			}
		}		
	}
	
	int BitToDec(int mask, int index, int compareMask)
	{
		int value = mask & (compareMask << index);
		value = value >> index;
		return value;
	}	
	
	void SendRPC_RP()
	{
		array<int> mask_array = new array<int>;
		SerializeStats(mask_array);
		if( !alp_LastSentStats || !AreArraysSame(alp_LastSentStats, mask_array)  )
		{
			ScriptRPC rpc = new ScriptRPC();
			rpc.Write(mask_array);
			rpc.Send(alp_Player, ALP_RPC_PLAYER_SYNC_BIT, true, alp_Player.GetIdentity());
			alp_LastSentStats = mask_array;
		}
	}

	bool AreArraysSame( notnull array<int> array_a, notnull array<int> array_b )
	{
		if( array_a.Count() != array_b.Count() ) return false;
		for(int i = 0; i  <array_a.Count(); i++)
		{
			if(	array_a.Get(i) != array_b.Get(i) )
			{
				return false;
			}
		}
		return true;
	}		
	
	void SerializeStats(ref array<int> mask_array)
	{
		
		int offset = 0;
		int mask = 0;
		
		for(int i = 0; i < NUMBER_OF_ELEMENTS; i++)
		{
			if(  GetElement(i) )
			{
				//GetElement(i).Update();
				
				if( (GetElement(i).GetNumberOfBits() + offset) > BIT_INT_SIZE )
				{
					mask_array.Insert(mask);
					offset = 0;
					mask = 0;
				}
				mask = mask | (GetElement(i).GetValue() << offset);
				offset = offset + GetElement(i).GetNumberOfBits();
			}
		}
		mask_array.Insert(mask);
		
	}	
	
	//stats enhanced
	
	void OnRPC_RP_STATS_ENHANCED(ParamsReadContext ctx)//on Client
	{	

		int type;
		float value;					
		ctx.Read(type); 			
		ctx.Read(value); 	
		if ( GetElementEnhanced(type ) )
		{
			GetElementEnhanced(type ).SetValue( value ) ;
						
		}	
	}	
	
	void SendRPC_RP_ENHANCED()
	{
		
		
		if (!IsRegisteredToEnhanced() && !GetPlayer().GetRP().HasDosimeter() )
			return;
		


		for(int i = 0; i < NUMBER_OF_ELEMENTS_ENHANCED;i++)
		{
			if( GetElementEnhanced(i) )
			{
				if ( ( GetElementEnhanced(i).IsTraderStats() & IsRegisteredToEnhanced() ) || ( GetElementEnhanced(i).IsPlayerStats() & IsRegisteredToEnhanced() ) || ( GetElementEnhanced(i).IsRadiationStats() ) )
				{

					float value;											
					if ( GetElementEnhanced(i).GetValue( value ) )
					{//was changed

						ScriptRPC rpc = new ScriptRPC();
						rpc.Write(i);
						rpc.Write(value);
						rpc.Send(alp_Player, ALP_RPC_PLAYER_SYNC_VALUE, false, alp_Player.GetIdentity());
					}
				}
			}
		}			

	}	
			
	void ForceSync()
	{
		SendRPC_RP();
		SendRPC_RP_ENHANCED();	
	}	

	
	void RegisterToEnhancedStatsSync(bool state)
	{	
		
		GetScriptRPC_RegisterEnhancedStats(state).Send(alp_Player, ALP_RPC_PLAYER, true, alp_Player.GetIdentity());	
	}
	
	protected ScriptRPC GetScriptRPC_RegisterEnhancedStats(bool state)
	{
		ScriptRPC rpc = new ScriptRPC();	
		rpc.Write( ALP_RPC_PLAYER_TYPE.SYNC_REGISTER_ENHANCEDSTATS );
		rpc.Write( state );
		return rpc;
	}	
		
}


