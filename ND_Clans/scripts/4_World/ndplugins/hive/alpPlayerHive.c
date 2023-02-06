
modded class alpPlayerHive 
{

	void SetClaimedBed(int pp, string house, int index)
	{
		
		int ppID = GetStore().Base_Owner;
		string hID = GetStore().Base_House;
		int old_index = GetStore().Base_Bed;
		
		if ( ppID )
		{//delete old record
			int pID = GetPlayer().GetPlayerID();		
			alpClansPlugin.ReleaseBed( ppID, hID, old_index, pID );
		}				
		GetStore().Base_Owner = pp;
		GetStore().Base_House = house;
		GetStore().Base_Bed = index;
		Save();
	
	}
	void ReleaseClaimedBed(int pp, string house, int index)
	{
		
		int ppID = GetStore().Base_Owner;
		string hID = GetStore().Base_House;
		int old_index = GetStore().Base_Bed;
		
		if ( ppID == pp && hID == house && index == old_index )
		{//delete old record
			GetStore().Base_Owner = 0;
			GetStore().Base_House = "";
			GetStore().Base_Bed = 0;
			
			Save();
		}				
	}	

	vector GetBedLocation()
	{
		vector pos = "0 0 0";
		
		int ownerID = GetStore().Base_Owner;
		string houseID = GetStore().Base_House;
		int bedID = GetStore().Base_Bed;	
		int pID = GetPlayer().GetPlayerID();
		int clanID = GetStore().ClanID;		
		if ( ownerID )
		{	
			pos = alpClansPlugin.GetBedLocation( ownerID, houseID, bedID, pID, clanID );
			
			if (pos == "0 0 0")
			{//delete spawn
				GetStore().Base_Owner = 0;
				GetStore().Base_House = "";
				GetStore().Base_Bed = 0;
				
				Save();			
			}
		}
	
		return pos;
	}
	
	override void OnConnect()
	{
		super.OnConnect();
	
		if (GetGame().IsServer() )
		{
			vector pos = "0 0 0";
			bool enhancedSpawn = GetND().GetClans().GetSpawn().EnableEnhancedSpawnSettings;			
			bool equipmentChanged = false;
			
			int reputationLevel = GetPlayer().GetStatPerkReputation().Get();
			autoptr array<string> messages = new array<string>;
			
			if ( IsActiveDeathEvent()  )  //second condition to solve disconnect while being unconscious
			{

				//equipment
				if ( enhancedSpawn )
				{
					equipmentChanged = true;
					if ( GetStore().IsNewborn )
					{
						GetStore().IsNewborn = false;
						
						alpSpawnSetNewborn spawnsetnewborn = GetND().GetClans().GetSpawnManagement().GetNewbornSet();					
						if (spawnsetnewborn)
						{							
							EquipPlayer( spawnsetnewborn.Equipments , spawnsetnewborn.lootMaxCount);
							
							foreach(string m : spawnsetnewborn.Messages)
							{
								messages.Insert(m);	
							}
							
							if ( spawnsetnewborn.Water )
							{
								GetPlayer().GetStatWater().Set( spawnsetnewborn.Water );
							}
							if ( spawnsetnewborn.Energy )
							{
								GetPlayer().GetStatEnergy().Set( spawnsetnewborn.Energy );
							}							
						}						
					}
					else
					{//equipment according to reputation
						alpSpawnSetPlayer spawnset = GetND().GetClans().GetSpawnManagement().GetSpawnSet(reputationLevel);
						
						if (spawnset)
						{	
							EquipPlayer( spawnset.Equipments , spawnset.lootMaxCount );
							
							foreach(string m2 : spawnset.Messages)
							{
								messages.Insert(m2);	
							}	
							
							if ( spawnset.Water )
							{
								GetPlayer().GetStatWater().Set( spawnset.Water );
							}
							if ( spawnset.Energy )
							{
								GetPlayer().GetStatEnergy().Set( spawnset.Energy );
							}														
						}
					}
				}

				//spawn in base
				if ( GetND().GetClans().GetSpawn().EnableSpawnInBase )
				{
					pos = GetBedLocation();
					
					if ( pos != "0 0 0")
					{
						int pID = GetPlayer().GetPlayerID();
						if ( GetND().GetClans().CanSpawnInBase( pID ) )
						{
							pos = pos + "0 0.5 0"; 
							
							GetPlayer().SetPosition( pos );						
						}

					}				
				}
				

				
				
				DeactiveEvent( ALP_SPAWN_EVENT.DEATH );
			}
			else
			{
				if ( GetPlayer().IsPlayerSpawn() && enhancedSpawn &&  GetStore().IsNewborn )
				{//first spawn after WIPE
					GetStore().IsNewborn = false;
					equipmentChanged = true;
					
					alpSpawnSetNewborn spawnsetnewborn2 = GetND().GetClans().GetSpawnManagement().GetNewbornSet();					
					if (spawnsetnewborn2)
					{						
						EquipPlayer( spawnsetnewborn2.Equipments , spawnsetnewborn2.lootMaxCount);
						
						foreach(string m3 : spawnsetnewborn2.Messages)
						{
							messages.Insert(m3);	
						}	
						if ( spawnsetnewborn2.Water )
						{
							GetPlayer().GetStatWater().Set( spawnsetnewborn2.Water );
						}
						if ( spawnsetnewborn2.Energy )
						{
							GetPlayer().GetStatEnergy().Set( spawnsetnewborn2.Energy );
						}													
					}					
				}
			}
						
			if ( pos != "0 0 0" || equipmentChanged )
			{
				int timeOffset = 500;
				int messageStart = 6000;
				int timeMessage;
				int count = 0;
				if ( messages )
				{//private messages
					foreach(string mes : messages)
					{
						
						timeMessage = messageStart + timeOffset * count;
						GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater( this.SendSpawnMessage, timeMessage,false, mes);
						count++;
					}				
				}
				
				GetPlayer().SetSynchDirty();
			}			
		}			
		
			
	}

	
	void SendSpawnMessage(string message)
	{
		GetND().GetNotf().SendPersonalMessage( message, GetPlayer() );	
	}	
	
	override void SaveCommonStats()
	{
		super.SaveCommonStats();

		//save death event
		GetStore().Event =  GetStore().Event | ALP_SPAWN_EVENT.DEATH;
		
	}	
	
	bool IsActiveDeathEvent()
	{
		return GetStore().Event & ALP_SPAWN_EVENT.DEATH;
	}
	
	
	bool IsActiveEvent(int type)
	{
		return GetStore().Event & type;
	}
	
	void DeactiveEvent(int type)
	{
		if ( IsActiveEvent( type ) )
		{
			GetStore().Event = ~type & GetStore().Event;
		}
		
	}
	
	override void OnFirstConnect()
	{
		super.OnFirstConnect();
		
		alp_StoreValues.IsNewborn = true;		
	}
	
	
	void EquipPlayer(array<ref alpLootCargo> equipments, int maxCount = 0 )
	{
		if ( equipments )
		{
			GetPlayer().ClearInventory();
			int count = 0;
			foreach (alpLootCargo cargoMan : equipments)
			{
				alpLoot lootMan =  GetND().GetMS().alp_LootMap.Get(cargoMan.title);
					
				if (lootMan) 
				{
					alpMission.SpawnCargo( GetPlayer(),lootMan,cargoMan.chance);
				}
				else
				{
					alpMission.SpawnEntityInCargo(GetPlayer(), cargoMan.title, cargoMan.chance );
				}								
				count++; 												
				if ( maxCount && count >= maxCount ){
					break;
				}					
			}			
		}
		
		
	}
}
