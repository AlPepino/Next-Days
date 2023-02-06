
modded class ActionSkinning: ActionContinuousBase
{	

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if ( super.ActionCondition( player, target, item )  )
		{
			
			if (! GetND().GetRP().GetPerksOptions().EnablePerkHunting )
				return true;
						
			if ( GetND().GetRP().GetPerkHunting().RequiredLevelToSkin >  player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue() )
				return false;
			else
				return true;
		}		
		return false; 
	
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		if (! GetND().GetRP().GetPerksOptions().EnablePerkHunting )
		{		
			super.OnFinishProgressServer(action_data );
		}
		else
		{
			int level = action_data.m_Player.GetSyncData().GetElement( alpRPelements.HUNTING ).GetValue(); 
			int levelCup = GetND().GetRP().GetPerkHuntingLevelCup();
			
			float petlDamageMdf = 1;
			
			if ( GetND().GetRP().GetPerkHunting().AffectPeltQualityByLevel && levelCup )
			{
				petlDamageMdf = level / levelCup;			
			}
			
			
			float hunting = GetND().GetRP().GetPerkHuntingMdf( level );
			
			
			Object targetObject = action_data.m_Target.GetObject();
			
			// Prepare to read config variables
			string item_to_spawn;
			string cfg_skinning_organ_class;
			
			// Mark the body as skinned to forbid another skinning action on it
			EntityAI body;
			Class.CastTo(body,  targetObject );
			vector body_pos = body.GetPosition();
			body.SetAsSkinned();
			
			if (body.IsInherited(PlayerBase))
			{
				// This section drops all clothes (and attachments) from the dead player before deleting their body
				PlayerBase body_PB = PlayerBase.Cast(body);
				
				if (body_PB.IsRestrained() && body_PB.GetHumanInventory().GetEntityInHands())
				{
					MiscGameplayFunctions.TransformRestrainItem(body_PB.GetHumanInventory().GetEntityInHands(), null, action_data.m_Player, body_PB);
					/*
					EntityAI item_in_hands = action_data.m_MainItem;
					body_PB.SetRestrained(false);
					string new_item_name = MiscGameplayFunctions.ObtainRestrainItemTargetClassname(item_in_hands);			
					MiscGameplayFunctions.TurnItemInHandsIntoItemEx(body_PB, new UnrestrainSelfPlayer(item_in_hands, new_item_name));
					*/
				}
				//Remove splint if target is wearing one
				if (body_PB.IsWearingSplint())
				{
					EntityAI entity = action_data.m_Player.SpawnEntityOnGroundOnCursorDir("Splint", 0.5);
					EntityAI attachment;
					ItemBase new_item = ItemBase.Cast(entity);
					Class.CastTo(attachment, body_PB.GetItemOnSlot("Splint_Right"));
					if ( attachment && attachment.GetType() == "Splint_Applied" )
					{
						if (new_item)
						{
							MiscGameplayFunctions.TransferItemProperties(attachment,new_item);
							
							if (GetGame().IsServer())
							{
								//Lower health level of splint after use
								if (new_item.GetHealthLevel() < 4)
								{
									int newDmgLevel = new_item.GetHealthLevel() + 1;
									
									float max = new_item.GetMaxHealth("","");
									
									switch ( newDmgLevel )
									{
										case GameConstants.STATE_BADLY_DAMAGED:
											new_item.SetHealth( "", "", max * GameConstants.DAMAGE_BADLY_DAMAGED_VALUE );
											break;
					
										case GameConstants.STATE_DAMAGED:
											new_item.SetHealth( "", "", max * GameConstants.DAMAGE_DAMAGED_VALUE );
											break;
					
										case GameConstants.STATE_WORN:
											new_item.SetHealth( "", "", max * GameConstants.DAMAGE_WORN_VALUE );
											break;
										
										case GameConstants.STATE_RUINED:
											new_item.SetHealth( "", "", max * GameConstants.DAMAGE_RUINED_VALUE );
											break;
										
										default:
											break;
									}
								}
							}
						}
						attachment.Delete();
					}
				}
				
				/*
				DropEquipAndDestroyRootLambda lambda(body_PB, "", action_data.m_Player);
				action_data.m_Player.ServerReplaceItemWithNew(lambda);
				*/
				int deadBodyLifetime;
				if ( GetCEApi() )
				{
					deadBodyLifetime = GetCEApi().GetCEGlobalInt( "CleanupLifetimeDeadPlayer" );
					if ( deadBodyLifetime <= 0 )
					{
						deadBodyLifetime = 3600;
					}
				}
				array<EntityAI> children = new array<EntityAI>;
				body_PB.GetInventory().EnumerateInventory(InventoryTraversalType.LEVELORDER, children);
				int count = children.Count();
				for (int i = 0; i < count; ++i)
				{
					EntityAI child = children.Get(i);
					if ( child )
					{
						body_PB.GetInventory().DropEntity(InventoryMode.SERVER, body_PB, child);
						child.SetLifetime( deadBodyLifetime );
					}
				}
			}
			
			GetGame().ObjectDelete(body); // Temporal deletion of the body
	
			// clutter cutter removed due to issues with audio it causes when players steps on it.
			//Object cutter = GetGame().CreateObject( "ClutterCutter2x2", body_pos, false ); // clutter cutter to free space on ground for organs.
			
			// Get config path to the animal
			string cfg_animal_class_path = "cfgVehicles " + body.GetType() + " " + "Skinning ";
			
			// Getting item type from the config
			int child_count = g_Game.ConfigGetChildrenCount( cfg_animal_class_path );
			
			// Parsing of the 'Skinning' class in the config of the dead body
			for ( int i1 = 0; i1 < child_count; i1++ )
			{
				// To make configuration as convenient as possible, all classes are parsed and parameters are read
				g_Game.ConfigGetChildName(cfg_animal_class_path, i1, cfg_skinning_organ_class); // out cfg_skinning_organ_class
				cfg_skinning_organ_class = cfg_animal_class_path + cfg_skinning_organ_class + " ";
				g_Game.ConfigGetText(cfg_skinning_organ_class + "item", item_to_spawn); // out item_to_spawn
				
				if ( item_to_spawn != "" ) // Makes sure to ignore incompatible parameters in the Skinning class of the agent
				{
					// Spawning items in action_data.m_Player's inventory
					int item_count = 0; 
					
					
					bool is_pelt = false;
					
					if (cfg_skinning_organ_class.IndexOf("ObtainedPelt") != -1 )
					{

						is_pelt = true;												
						
						if ( level >= GetND().GetRP().GetPerkHunting().RequiredLevelToGetPelt )
						{
							item_count = 1;
						
						}
											
					}
					else
					{
						item_count = g_Game.ConfigGetInt( cfg_skinning_organ_class + "count" ) * hunting; //alpepino
					
					}
					
					
					
	
					array<string> itemZones = new array<string>;
					array<float> itemCount = new array<float>;
					float zoneDmg = 0;
	
					GetGame().ConfigGetTextArray( cfg_skinning_organ_class + "itemZones", itemZones);
					GetGame().ConfigGetFloatArray( cfg_skinning_organ_class + "countByZone", itemCount);
	
					if ( itemCount.Count() > 0 )
					{
						item_count = 0;
						for ( int z = 0; z < itemZones.Count(); z++ )
						{
							zoneDmg = targetObject.GetHealth01(itemZones[z], "Health") * hunting;
							zoneDmg *= itemCount[z]; //just re-using variable
							item_count += Math.Floor( zoneDmg ) ;
						}
					}
	
					for ( int i2 = 0; i2 < item_count; i2++ )
					{
						ItemBase spawn_result = CreateOrgan( action_data.m_Player, body_pos, item_to_spawn, cfg_skinning_organ_class, action_data.m_MainItem );
	
						//Damage pelts based on the average values on itemZones
						//It only works if the "quantityCoef" in the config is more than 0 
						float qtCoeff = GetGame().ConfigGetFloat( cfg_skinning_organ_class + "quantityCoef");
						if(qtCoeff > 0)
						{

							
							//Print("ano tady jsem " + item_to_spawn );
							float avgDmgZones = 0;
							for(int c2 = 0; c2 < itemZones.Count(); c2++ )
							{
								avgDmgZones += targetObject.GetHealth01(itemZones[c2], "Health");
							}
							if ( itemZones.Count() > 0 )
							{
								avgDmgZones = ( avgDmgZones/( itemZones.Count()  ) * hunting; // Evaluate the average Health	
							}
							else
							{
								avgDmgZones =  avgDmgZones * hunting; // Evaluate the average Health	
							}
							
							
							avgDmgZones = Math.Clamp(avgDmgZones ,avgDmgZones , 1);
							//Print("avgDmgZones " + avgDmgZones );

							
							if ( is_pelt && spawn_result && spawn_result.HasQuantity() )
							{	
												
								spawn_result.SetQuantity(1);
							}
									
							if(spawn_result )
							{
								if ( is_pelt )
								{
									avgDmgZones *= petlDamageMdf;
									avgDmgZones = Math.Clamp(avgDmgZones ,avgDmgZones , 1);
								}
								spawn_result.SetHealth01("","", avgDmgZones);		
			
							}
												
						}
						else
						{
							//Print("VOLANO JE 2");
							if ( spawn_result )
							{

								float relativeHealth = spawn_result.GetHealth01("","");
								//Print("relativeHealth " + relativeHealth );
								relativeHealth *= hunting;
								
								relativeHealth = Math.Clamp(relativeHealth,0,1);
								//Print("relativeHealth 2 " + relativeHealth );
								
								
								if ( is_pelt && spawn_result.HasQuantity() )
								{																
									spawn_result.SetQuantity(1);
								}	
								
								
								spawn_result.SetHealth01("","", relativeHealth);								
							}
						}	
					
					
					
						// handle fat/guts from human bodies
						if ( ( item_to_spawn == "Lard" ) || ( item_to_spawn == "Guts" ) )
						{
							if ( body.IsKindOf( "SurvivorBase" ) )
							{
								spawn_result.InsertAgent(eAgents.BRAIN, 1);
							}
						}
					}
					
					/*action_data.m_MainItem.DecreaseHealth("","",UADamageApplied.SKINNING); // wear out tool			
					Print(action_data.m_MainItem.GetHealth01());*/
				}
			}	
			
			MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, UADamageApplied.SKINNING / hunting );
			
			PluginLifespan module_lifespan = PluginLifespan.Cast( GetPlugin( PluginLifespan ) );
			module_lifespan.UpdateBloodyHandsVisibility( action_data.m_Player, true );
			
			action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );			
		}
		
		PlayerSkinnedEntityALP( action_data );
	}	


	
	protected void PlayerSkinnedEntityALP( ActionData action_data )
	{
		
		PlayerBase player;
		Object targetObject = action_data.m_Target.GetObject();
		
		if (Class.CastTo(player,targetObject))
		{
			if (action_data.m_Player.GetRP().IsHero() )
			{
				action_data.m_Player.GetRP().ChangeReputation(   GetND().GetRP().GetReputationBonusSkinPlayer(ALP_RP_HERO) );				
			}	
			else 
			{	
				action_data.m_Player.GetRP().ChangeReputation(   GetND().GetRP().GetReputationBonusSkinPlayer(ALP_RP_BANDIT) );
			}
			action_data.m_Player.GetStatCountSkinned().Add(1);						
		}
		else
		{
			if ( GetND().GetRP().GetPerksOptions().EnablePerkHunting )
			{
				AnimalBase animal;
				
				if ( Class.CastTo( animal,	targetObject ) )
				{
					
					action_data.m_Player.GetRP().ChangeHunting(  GetND().GetRP().GetPerkHunting().SkinAnimal );							
				}				
			}
		}
	
	}	
	
	

};
