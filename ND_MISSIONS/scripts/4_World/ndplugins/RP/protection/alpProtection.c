// Script File




class alpProtection 
{
	PlayerBase alp_Player;
	
	ref map<int, ref alpProtectionBonuses> alp_WearingAttachment;
	
#ifdef NAMALSK_SURVIVAL	
	static const int alp_InventorySlots[7] = {InventorySlots.GetSlotIdFromString("Headgear") ,InventorySlots.GetSlotIdFromString("Mask") ,InventorySlots.GetSlotIdFromString("Gloves"),InventorySlots.GetSlotIdFromString("Body"),InventorySlots.GetSlotIdFromString("Feet"),InventorySlots.GetSlotIdFromString("Legs"),InventorySlots.GetSlotIdFromString("LEHS")};
#else
	static const int alp_InventorySlots[6] = {InventorySlots.GetSlotIdFromString("Headgear") ,InventorySlots.GetSlotIdFromString("Mask") ,InventorySlots.GetSlotIdFromString("Gloves"),InventorySlots.GetSlotIdFromString("Body"),InventorySlots.GetSlotIdFromString("Feet"),InventorySlots.GetSlotIdFromString("Legs")};	
#endif		
	
	

	ref map<string,int> alp_InventoryMap;
	
	int alp_HasDosimeter = 0;
	
	
		
	void alpProtection(PlayerBase player)
	{
		alp_Player = player;
		
		alp_WearingAttachment = new map<int, ref alpProtectionBonuses>;
		
		alp_InventoryMap = new map<string,int>;
		
		foreach(int loc : alp_InventorySlots)
		{
			alp_InventoryMap.Set( InventorySlots.GetSlotName(loc), loc );
			
		}		
		
		
	}
	
	bool HasDosimeter()
	{
		return alp_HasDosimeter;
	}
	
	
	void ItemAttached(EntityAI item, string slot_name)
	{
		
		int slot_id;
		
		if (alp_InventoryMap.Find( slot_name, slot_id ) )
		{
			ItemBase itm = ItemBase.Cast( alp_Player.GetInventory().FindAttachment( slot_id ) );  //alpProtectionBonuses tohle budu ukladat
			
			if (itm)
			{
				alpProtectionBonuses protection = itm.GetProtectionBonuses();
				
				alp_WearingAttachment.Set( slot_id , protection );		
				
				if ( protection.HasDosimeter() )
				{
					alp_HasDosimeter++;
				}
			}
		
		}
			
	}
	
	void ItemDetached(EntityAI item, string slot_name)
	{
		int slot_id;
		
		if (alp_InventoryMap.Find( slot_name, slot_id ) && alp_WearingAttachment.Get(slot_id) )
		{
			if ( alp_WearingAttachment.Get(slot_id).HasDosimeter() )
			{
				alp_HasDosimeter--;
			}			
			
			alp_WearingAttachment.Remove( slot_id );
		}	
	}	
	


	float GetProtection(int type, int loc, bool noResistance = false)
	{
		
		float attProtection = 0;
		
		if ( loc == InventorySlots.GetSlotIdFromString("Headgear") || loc == InventorySlots.GetSlotIdFromString("Mask") )
		{
			alpProtectionBonuses protectionHead = alp_WearingAttachment.Get( InventorySlots.GetSlotIdFromString("Headgear") );
			alpProtectionBonuses protectionMask = alp_WearingAttachment.Get( InventorySlots.GetSlotIdFromString("Mask") );
						
			float attProtectionHead,attProtectionMask;
			
			if ( protectionHead )
			{
				attProtectionHead = protectionHead.GetProtection(type);
			}	
			if ( protectionMask )
			{
				attProtectionMask = protectionMask.GetProtection(type);
			}			
			
			attProtection = Math.Clamp( (attProtectionHead + attProtectionMask),0,1);
		}
		else
		{
			
			
			if ( IsMaskFullBodyProtection() )
			{
				
				attProtection = GetProtection( type, InventorySlots.GetSlotIdFromString("Headgear") );
			}
			else
			{
				alpProtectionBonuses protection = alp_WearingAttachment.Get(loc);
#ifdef NAMALSK_SURVIVAL	
				if ( !protection ) {
					protection = alp_WearingAttachment.Get(InventorySlots.GetSlotIdFromString("LEHS"));	
				}	
#endif										
				
				if ( protection )
				{
					attProtection = protection.GetProtection(type);
									
					
				}	
			
			}
						
		}
			
		

		float naturalResist = 0;
		
		if ( !noResistance )
		{
			naturalResist = GetNaturalResistance(type);
		}
		
		return Math.Max(attProtection,naturalResist);
	}

	float GetProtectionRespiratory(int type)
	{
		alpProtectionBonuses protection = alp_WearingAttachment.Get(InventorySlots.GetSlotIdFromString("Mask"));
			
				
		float attProtection = 0;
		
		if ( protection && protection.GetItem() )
		{
			
			attProtection = protection.GetItem().GetProtectionLevel(type, true );
								
		} 

#ifdef NAMALSK_SURVIVAL			
		if ( !attProtection ) {
			protection = alp_WearingAttachment.Get(InventorySlots.GetSlotIdFromString("Headgear"));	
			
			if ( protection ) {
				dzn_lehs_helmet helmet = dzn_lehs_helmet.Cast( protection.GetItem() );
			
				if ( helmet )
				{
					if ( helmet.IsPressurized() )
						attProtection = 1.0;
					else
						attProtection = 0.0;
				}					
			}
		}		
#endif				
		
		
						
		
		float naturalResist = GetNaturalResistance(type);
		
		return Math.Max(attProtection,naturalResist);
	}
	
	
	
	float GetNaturalResistance(int type)
	{
		switch (type)
		{

			case alpPROTECTION.BIOLOGICAL:
				return GetNaturalResistanceAgainstBiologic();
			case alpPROTECTION.CHEMICAL:
				return GetNaturalResistanceAgainstChemical();
			case alpPROTECTION.RADIATION:
				return GetNaturalResistanceAgainstRadiation();
		}		
		return 0;
	}
	
	float GetTotalRadiationShield()
	{
		//head
		float respiratory;
		if (  GetND().GetMS().GetOptionsRadiation().NotRequiredFilterForRadiation )
		{
			respiratory	= 1;
		}
		else
		{
			respiratory = GetProtectionRespiratory( alpPROTECTION.RADIATION );
		}

		
		
		
		float head = GetProtection( alpPROTECTION.RADIATION, InventorySlots.GetSlotIdFromString("Headgear") );
		
		//top
		float body = GetProtection( alpPROTECTION.RADIATION, InventorySlots.GetSlotIdFromString("Body") );
		float hands = GetProtection( alpPROTECTION.RADIATION, InventorySlots.GetSlotIdFromString("Gloves") );
		
		//bottom
		float legs = GetProtection( alpPROTECTION.RADIATION, InventorySlots.GetSlotIdFromString("Legs") );
		float feet = GetProtection( alpPROTECTION.RADIATION, InventorySlots.GetSlotIdFromString("Feet") );		
		
		
		float protection;
		
		if (IsMaskFullBodyProtection())
		{
			if (  GetND().GetMS().GetOptionsRadiation().NotRequiredFilterForRadiation )
			{			
				protection =  head;
			}
			else
			{
				protection = respiratory * 0.3 +  head * 0.7;
			}			
		}
		else
		{
			if (  GetND().GetMS().GetOptionsRadiation().NotRequiredFilterForRadiation )
			{							
				protection =  head * 0.5 + body * 0.3 + hands * 0.05 + legs * 0.1 + feet * 0.05;
			}
			else
			{
				protection = respiratory * 0.3 +  head * 0.2 + body * 0.3 + hands * 0.05 + legs * 0.1 + feet * 0.05;
			}				
			
		}
		
		
		protection = Math.Clamp(protection,0,1);
		
		return protection;
	
	}

	
	float GetTotalChemicalShield()
	{
		float suit;
					
		
		//head
		float respiratory = GetProtectionRespiratory( alpPROTECTION.CHEMICAL );
		
		float head = GetProtection( alpPROTECTION.CHEMICAL, InventorySlots.GetSlotIdFromString("Headgear") );
		
		//top
		float body = GetProtection( alpPROTECTION.CHEMICAL, InventorySlots.GetSlotIdFromString("Body") );
		float hands = GetProtection( alpPROTECTION.CHEMICAL, InventorySlots.GetSlotIdFromString("Gloves") );
		
		//bottom
		float legs = GetProtection( alpPROTECTION.CHEMICAL, InventorySlots.GetSlotIdFromString("Legs") );
		float feet = GetProtection( alpPROTECTION.CHEMICAL, InventorySlots.GetSlotIdFromString("Feet") );		
		
		float protection;
		
		if (IsMaskFullBodyProtection())
		{
			protection = respiratory * 0.3 +  head * 0.7;
		}
		else
		{
			protection = respiratory * 0.3 +  head * 0.2 + body * 0.3 + hands * 0.05 + legs * 0.1 + feet * 0.05;
		}
		
		protection = Math.Clamp(protection,0,1);
		
		return protection;
	
	}	
	
	
	float GetNaturalResistanceAgainstRadiation()
	{		
		return 0;
	}
	float GetNaturalResistanceAgainstChemical()
	{		
		return 0;
	}	
	float GetNaturalResistanceAgainstBiologic()
	{		
		return 0;
	}		
	
	
	bool IsMaskFullBodyProtection()
	{
		return GetND().GetMS().GetOptionsRadiation().HeadgearsDetermineBodyProtection;
	}
}




