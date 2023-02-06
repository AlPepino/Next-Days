// Script File
/*
enum alpRADIATION_ITEM
{
	
}
*/

class alpRadiationMdfr: ModifierBase
{
	
	//static int alp_RADIATION_TO_ITEM = 10;
	
	int alp_WATER_DRAIN_CONST;
	int alp_RADIATION_CAP;
	float alp_ARMOR_RATIO;

	
	override void Init()
	{
		
		m_TrackActivatedTime			= false;
		m_ID 							= rModifiers.MDF_ALPRADIATION;
		m_TickIntervalInactive 			= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 			= DEFAULT_TICK_TIME_ACTIVE; //DEFAULT_TICK_TIME_ACTIVE;
		
		if ( GetND() && GetND().GetMS().GetOptionsRadiation() )
		{
			
			alp_WATER_DRAIN_CONST			= GetND().GetMS().GetOptionsRadiation().WaterDrainInRadiationPerSec;
			alp_RADIATION_CAP				= GetND().GetMS().GetOptionsRadiation().RadiationCapForCalc;
			alp_ARMOR_RATIO					= GetND().GetMS().GetOptionsRadiation().ArmorRatioNBCforWaterDrain;			
			
		}
		
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		
		return true;

	}

	override void OnActivate(PlayerBase player)
	{
		
	}
	
	override void OnReconnect(PlayerBase player)
	{
		
	}

	override void OnDeactivate(PlayerBase player)
	{
	
	}

	override bool DeactivateCondition(PlayerBase player)
	{
 		return false;
	}

	override void OnTick(PlayerBase player, float deltaT)
	{	
		float radH = player.GetRP().GetRadiation();
		
		float radiation = radH / 60 / 60;	
		
		float shield =  player.GetRP().GetProtection().GetTotalRadiationShield();
		
		//make thirsty
		if ( alp_WATER_DRAIN_CONST > 0 && radiation > 0)
		{

					
			float radiationStrength = Math.Clamp(radH,0, alp_RADIATION_CAP); 
			
			float waterDrain = ( radH / alp_RADIATION_CAP ) * alp_WATER_DRAIN_CONST;
			
			waterDrain = ( waterDrain - waterDrain * alp_ARMOR_RATIO * shield ) * deltaT;
			
			player.GetStatWater().Add( -waterDrain );
			
		}		
		
		if ( radiation && shield < 1 )
		{
			float doses = ( radiation * ( 1 - shield )  * 1000 ) * deltaT;

			
			player.GetRP().SetRecievedRadiation( doses );
			
		
		}
		
		//damage attchments
		
		if (  GetND().GetMS().GetOptionsRadiation().RadiationLimitDegradingAttachments ||   GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems )
		{
			//Print("RadH " + radH);
			
			float damage = radH - GetND().GetMS().GetOptionsRadiation().RadiationLimitDegradingAttachments;
			
			if ( damage > 0 )
			{
				damage = Math.Pow( damage, GetND().GetMS().GetOptionsRadiation().DamageToAttachmentsExponent );
				
				damage *= GetND().GetMS().GetOptionsRadiation().DamageToAttachmentsCoef * deltaT;				
			}
			else
			{
				damage = 0;
			}
			

			
			
			ItemBase itm;
			
			//in hands
			/*
			itm = player.GetItemInHands();
			if ( itm && ( radH > GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems && !( itm.GetAgents() & alpeAgents.RADIATION )  ) )
			{	
				player.AddContaminedItem(itm.GetID());
				itm.InsertAgent(alpeAgents.RADIATION,1);
				itm.SetSynchDirty();
			}
			*/
			//attachments
			for( int i = 0; i < player.GetInventory().AttachmentCount(); i++ )
			{
				
				itm = ItemBase.Cast( player.GetInventory().GetAttachmentFromIndex( i ) );		
				
				if ( itm )
				{
					float health = itm.GetHealth("","");
					
					if ( GetND().GetMS().GetOptionsRadiation().RadiationLimitDegradingAttachments && health > 20 && radH > GetND().GetMS().GetOptionsRadiation().RadiationLimitDegradingAttachments )			
					{
						health -= damage;
					
						health = Math.Clamp( health, 20, health );
					
						itm.SetHealth("","", health );
					}
					
					if ( GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems && radH > GetND().GetMS().GetOptionsRadiation().RadiationLimitToContamineItems && !( itm.GetAgents() & alpeAgents.RADIATION )  )
					{
						//Print("Je kontaminovano "  + itm.GetType() + " ID " + itm.GetID() );
						player.AddContaminedItem(itm.GetID());
						
						itm.InsertAgent(alpeAgents.RADIATION,1);
						itm.SetSynchDirty();
					}	
				}
			}			
			
			

		}
		
		
	}
	

	

};