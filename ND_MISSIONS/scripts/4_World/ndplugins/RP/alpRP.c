


class alpRP 
{
	PlayerBase					alp_Player;

	Transport					alp_Car;//synchr variables for trader
		
	ref alpProtection 			alp_Protection;
	ref alpTraderCart			alp_Cart;

	//TransmitterBase				alp_WalkieTalkie;
	
	ref map<int,float>			alp_Radiation;

	alp_geiger_counter			alp_GeigerCounter;	

	int 						alp_RewardForKill[2];//id currency/ ammount
	
	int alp_RadiationSickStage;
	
	protected bool alp_HasContaminedItems;
	protected bool alp_IsHighRadiation;
	
	
	protected bool alp_IsAllowedDamage	= true;
	protected bool alp_IsInTradeZone;
	
	protected bool alp_IsRained	= false;
	
	protected bool alp_IsDebtor;
	protected bool alp_EchoCooldown;
	const int alp_EchoPostpone = 5000;
	const int alp_EchoCDTime = 30000;
	
	void alpRP(PlayerBase player)
	{
		alp_Player = player;
		
		alp_Protection = new alpProtection(alp_Player);
		alp_Cart = new alpTraderCart( alp_Player);
		
		alp_Radiation = new map<int,float>;
		
		Init();
		
	}
	
	
	void MakeEchoWatnedPerson(ItemBase suppressor, int from)
	{
		
		if (!suppressor || suppressor.GetHealth01("","Health") < Math.RandomFloat01() )
		{
			SetEchoCooldown( true );
			
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SendEchoWantedPersonMessage,alp_EchoPostpone,false,from);
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetEchoCooldown,alp_EchoCDTime,false,false);		
		}
		

	}
	
	void SetDebtor( bool state )
	{
		alp_IsDebtor = state;
		
		if (state )
		{	
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SendPersonalAlertDebt,10000);	
			
			//set reaward	
			
			
		}		
		else
		{
			alp_RewardForKill = {0,0};
		}
	}
	
	
	void SetDebt(int currency, int debt)
	{
		int reward[2] = GetND().GetMS().GetOptoinsTrader().BankRewardForWantedPerson;
		int base = reward[0];
		int bonus = reward[1]; 
		float rate = alpBANK.GetCurrencyRate( currency );
		base = base * rate;
		if ( bonus )
		{

			rate = bonus / 100;
			bonus = rate * debt;		
			base += bonus;
		}
		
		alp_RewardForKill = {currency,base};
	}
	
	protected void SendPersonalAlertDebt()
	{
		GetND().GetNotf().SendPersonalMessage( "#alp_debtwarning", GetPlayer() );	
	}
	
	bool IsEchoCoolDown()
	{
		return alp_EchoCooldown;
	}
	
	protected void SetEchoCooldown(bool state)
	{
		alp_EchoCooldown = state;
	}
	
	protected void SendEchoWantedPersonMessage(int from)
	{
		string name = GetPlayer().GetIdentity().GetName();
		
		GetND().GetNotf().SendEchoAboutWantedPerson(ALPMSTYPE.MMPERSONAL, name, GetPlayer().GetPosition() , GetPlayer().GetPlayerHive().GetPlayerID(), from , alp_RewardForKill[0], alp_RewardForKill[1] );//ALPMSTYPE.MMPERSONAL
		
		
	}
	
	bool IsDebtor()
	{
		return alp_IsDebtor;
	}
	
	void SetCar(Transport car)
	{
		alp_Car = car;
	}
	
	Transport GetCar()
	{
		if ( alp_Car && !alp_Car.GetHierarchyRootPlayer() && alpUF.VectorDistance(alp_Car.GetPosition(), GetPlayer().GetPosition() ) < 50 )
		{
			return alp_Car;
		}
		return null;

	}	
	
	alpTraderCart GetCart()
	{
		return alp_Cart;
	}
	
	
	bool IsAllowedDamage()
	{
		return alp_IsAllowedDamage;
	}	
	bool IsInTradeZone()
	{
		return alp_IsInTradeZone;
	}		
	
		
	bool IsRained()
	{
		return alp_IsRained;
	}	
	void SetRainedState(bool state)
	{
		alp_IsRained = state;
	}	
	
			
	void SetAllowedDamage(bool state)
	{
		if (GetGame().IsServer())
		{
			GetPlayer().SetAllowDamage( state );
		}
		
		alp_IsAllowedDamage = state;
	}
	void SetInTradeZone(bool state)
	{
		alp_IsInTradeZone = state;
	}	
	
	PlayerBase GetPlayer()
	{
		return alp_Player;
	}
	
	void Init()
	{

	}
	
	alpProtection GetProtection()
	{
		return alp_Protection;
	}	

		
	//alpRADIO	
	int alp_RadioType;
	int GetWalkieTalkieType()
	{
		return alp_RadioType;
	}
	
	int HasWalkieTalkie()
	{	
		alp_RadioType = 0;
		
		//gps
		MapNavigationBehaviour	nav;
		nav = alp_Player.GetMapNavigationBehaviour();
		
		if (nav.GetNavigationType() & EMapNavigationType.GPS) {
			alp_RadioType = alp_RadioType | alpRADIO.HAS_GPS;	
		}
		if (nav.GetNavigationType() & EMapNavigationType.COMPASS) {
			alp_RadioType = alp_RadioType | alpRADIO.HAS_COMPASS;	
		}		
		
		if (!GetND().GetMS().GetOptions().RequiresWalkieTalkie )
		{
			alp_RadioType = alp_RadioType | alpRADIO.ALLOWED_BY_CONFIG_PERSONAL;		
			
			if ( !GetND().GetMS().GetOptions().BaseRadioUncoverAllMissions )
			{
				return alp_RadioType;
			}
		}
			
			
		autoptr array<EntityAI> itemsArray = new array<EntityAI>;
		TransmitterBase wt;		
		
		float frequency = GetND().GetMS().GetOptions().RequiredTunedFrequency;
		
		alp_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		for (int i = 0; i < itemsArray.Count(); i++)
		{	
			if ( itemsArray.Get(i).IsTransmitter() )
			{
				TransmitterBase radio = TransmitterBase.Cast( itemsArray.Get(i) );

				if ( radio.IsWorking() )
				{
					
					if ( radio.IsBaseRadio() )
					{
						if ( !frequency || ( frequency && frequency == radio.GetTunedFrequency() ) )						
						{
							alp_RadioType = alp_RadioType | alpRADIO.HAS_BASE_RADIO;
							break;					
						}
					}
					if ( !frequency || ( frequency && frequency == radio.GetTunedFrequency() ) )						
					{
						alp_RadioType = alp_RadioType | alpRADIO.HAS_WALKIE_TALKIE;				
					}					
					
				}

			}		
		}	
		return alp_RadioType;		

		
		
	}	
		/*
	bool HasWalkieTalkie()
	{	
		
		if (!GetND().GetMS().GetOptions().RequiresWalkieTalkie )
			return true;		

		
		autoptr array<EntityAI> itemsArray = new array<EntityAI>;
		TransmitterBase wt;		
		
		alp_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		for (int i = 0; i < itemsArray.Count(); i++)
		{	
			if ( itemsArray.Get(i).IsTransmitter() )
			{
				wt = TransmitterBase.Cast(itemsArray.Get(i));
				if ( wt.IsOn() )
				{
					return true;				
				}
			}		
		}	
		return false;		

		
		
	}	

	void SetWalkieTalkie(TransmitterBase wt)
	{
		alp_WalkieTalkie = wt;
	}	
	*/
	bool HasContaminedItems()
	{
		if (!GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems )
			return false;
		
		return alp_HasContaminedItems;
	}
	bool IsRadiationHigh()
	{
		return alp_IsHighRadiation;
	}		
	
	

	int GetRecievedRadiation()
	{
		return alp_Player.GetSingleAgentCount(alpeAgents.RADIATION);
	}
	
	
	void SetRadiation( int id, float radiation )
	{
		if ( alp_Player.IsSoundInsideBuilding() )
		{
			radiation	=  radiation - GetND().GetMS().GetOptionsRadiation().RadiationResistanceInBuilding;
			
			if ( radiation < 0 )
				radiation = 0;
		}		
		
		if ( radiation == 0 )
		{	

			alp_Radiation.Remove(id);	

			return;	
		}
		
		alp_Radiation.Set(id,radiation);		
	}

	float GetRadiation()
	{
		alp_IsHighRadiation = false;
		alp_HasContaminedItems = false;
		
		float radiation = 0;
		
		ItemBase itm;
		
		
		
		if ( GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems && alp_Player.HasContaminedItems() )
		{
			
	
			radiation = GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems + Math.RandomFloat(-0.05,-0.01) * GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems;
			alp_HasContaminedItems = true;
			//Print(" alp_Player.GetContaminedItemsCount() "  + alp_Player.GetContaminedItemsCount() + " radiation " + radiation);
			/*
			itm = alp_Player.GetItemInHands();
			if ( itm && ( itm.GetAgents() & alpeAgents.RADIATION ) )
			{		
				radiation = GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems + Math.RandomFloat(-0.05,-0.01) * GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems;	
				alp_HasContaminedItems = true;
			}
				
			if (!radiation)
			{
				for( int i = 0; i < alp_Player.GetInventory().AttachmentCount(); i++ )
				{				
					itm = ItemBase.Cast( alp_Player.GetInventory().GetAttachmentFromIndex( i ) );		
							
					if ( itm && ( itm.GetAgents() & alpeAgents.RADIATION ) )
					{						
						radiation = GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems + Math.RandomFloat(-0.05,-0.01) * GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems;
						alp_HasContaminedItems = true;
						break;	
					}		
				}
			}
			*/
		}
		
		if ( alp_Radiation.Count() > 0 )
		{
			array<float> values = alp_Radiation.GetValueArray();
		
			values.Sort(true); 
			
			if ( values.Get(0) > radiation )
			{
				if (alp_HasContaminedItems)
					alp_IsHighRadiation = true;
				
				radiation = values.Get(0);
			}
		}
		return radiation;	
	}	
	
	void ClearRadiation()
	{
		alp_Radiation.Clear();
	}	
	void SetLocalRadiation()
	{
		ClearRadiation();
		
		map<int, ref alpMission> missions  = GetND().GetMS().GetMissions();
		
		
		
		for (int i = 0; i < missions.Count() ; i++)
		{
			alpMission mission = missions.GetElement(i);		

			if (mission.IsActive() && mission.alp_Touched && ( mission.alp_Type == ALP_MISSIONTYPEID.radiation || mission.alp_Type == ALP_MISSIONTYPEID.radiationMission) )
			{//active rad mission
					
					
				float distance =  alpUF.VectorDistance ( mission.GetPosition() , alp_Player.GetPosition() );	
				
				if  ( distance <=  mission.alp_DamageRadius )
				{
					mission.SetPlayerInRadiation(alp_Player , distance );	
				}			
			}
			
		}
		
	}	
	
	bool HasDosimeter()
	{
		if ( GetProtection().HasDosimeter()  || HasActiveGeigerCounter() )	
			return true;	
		else 
			return false;		
	}		
	bool HasActiveGeigerCounter()
	{
		if (alp_GeigerCounter)
		{
			if ( alp_Player == PlayerBase.Cast(alp_GeigerCounter.GetHierarchyRootPlayer() ) && alp_GeigerCounter.m_Working )
				return true;
			else 
				return false;
		}
		else return false;
	}	
	
	void SetGeigerCounter(alp_geiger_counter gc)
	{
		alp_GeigerCounter = gc;
	}
		
	
	void Decontamination(bool all = false)
	{
		array<EntityAI> itemsArray = new array<EntityAI>;
		EntityAI item;
		alp_Player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);	
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			item = itemsArray.Get(i);
			if (item && item != alp_Player && ( item.GetAgents() & alpeAgents.RADIATION ) )
			{
				if ( GetND().GetMS().GetOptionsRadiation().EnableFoodDecontamination || ( !GetND().GetMS().GetOptionsRadiation().EnableFoodDecontamination && !item.IsFood()  ) )
				{
					alp_Player.RemoveContaminedItem(item.GetID());
					item.RemoveAgent( alpeAgents.RADIATION );
					item.SetSynchDirty();
				}
			}			
		}				
	}		
	void SetRecievedRadiation(float doses, bool isFood = false )
	{		
		alp_Player.InsertAgent(alpeAgents.RADIATION, doses );	
	}	

	int GetRadiationSickStage()
	{
		return alp_RadiationSickStage;
	}
	
	void SetRadiationSickStage(int level)
	{
		alp_RadiationSickStage = level;			
	}	
	
	void ImproveToxicNaturalResistance(float exp)
	{
	
	}
	
	
	void ImproveRadiationNaturalResistance(float exp)
	{
	
	}		
	void ChangeReputation( float inc )
	{

	}		
}


