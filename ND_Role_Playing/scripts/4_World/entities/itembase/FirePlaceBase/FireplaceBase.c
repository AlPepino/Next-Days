modded class FireplaceBase extends ItemBase
{
	
	typename ATTACHMENT_LARD_A_ALP			= Lard;

	
	override void EEInit()
	{
		super.EEInit();

		if ( m_FireConsumableTypes )
		{
			m_FireConsumableTypes.Insert( alp_Money10, 		new FireConsumableType( alp_Money10, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_Money20, 		new FireConsumableType( alp_Money20, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_Money50, 		new FireConsumableType( alp_Money50, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_Money100, 		new FireConsumableType( alp_Money100, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_Money500, 		new FireConsumableType( alp_Money500, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_Money1000, 		new FireConsumableType( alp_Money1000, 		5, 	true,	"Paper" ) );	
			
			m_FireConsumableTypes.Insert( alp_USD1, 		new FireConsumableType( alp_USD1, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_USD5, 		new FireConsumableType( alp_USD5, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_USD10, 		new FireConsumableType( alp_USD10, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_USD20, 		new FireConsumableType( alp_USD20, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_USD50, 		new FireConsumableType( alp_USD50, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_USD100, 		new FireConsumableType( alp_USD100, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_USD500, 		new FireConsumableType( alp_USD500, 		5, 	true,	"Paper" ) );	
			m_FireConsumableTypes.Insert( alp_USD1000, 		new FireConsumableType( alp_USD1000, 		5, 	true,	"Paper" ) );	
		
			m_FireConsumableTypes.Insert( ATTACHMENT_LARD_A_ALP, 		new FireConsumableType( ATTACHMENT_LARD_A_ALP, 		1, 	false,	"LardALP" ) );	
		}

	}	
	
	override void RefreshFireplaceVisuals()
	{	
		super.RefreshFireplaceVisuals();
		
		if ( IsHologram() )
		{
			return;
		}		
		
		if ( IsItemTypeAttached( ATTACHMENT_LARD_A_ALP )  )
		{
			SetAnimationPhase( ANIMATION_ASHES, 0 );
		}		
		
		
	}
	
	
	override protected bool IsFuel( ItemBase item )
	{
		bool isfuel = super.IsFuel(item);
		
		if (isfuel){
			if ( item.GetType() == "Lard" && item != FindAttachmentBySlotName("LardALP") ) {
				return false;
			}
			return true;
		} 
		return false;

	}
	
	
	
	
	override protected int GetFuelCount()
	{
		int attachments_count = GetInventory().AttachmentCount();
		int fire_consumables_count = m_FireConsumables.Count();
		int fuel_count = 0;
		
		for ( int i = 0; i < attachments_count; i++ )
		{
			ItemBase item = ItemBase.Cast( GetInventory().GetAttachmentFromIndex( i ) );
			
			if ( item.GetType() == "Lard" && item != FindAttachmentBySlotName("LardALP") )
				continue;
			
			for ( int j = 0; j < fire_consumables_count; j++ )
			{
				ref FireConsumableType fire_consumable_type = m_FireConsumableTypes.Get( item.Type() );

				if ( fire_consumable_type && !fire_consumable_type.IsKindling() )
				{
					fuel_count++;
					break;
				}
			}
		}
		
		return fuel_count;
	}	
	

	
	override bool CanReleaseAttachment( EntityAI attachment )
	{
		if( !super.CanReleaseAttachment( attachment ) )
			return false;
				
		if ( IsBurning() && attachment == FindAttachmentBySlotName("LardALP") )
		{
			return false;
		}
		else
		{
			return true;
		}
	}	
	
	
	override bool CanReceiveAttachment( EntityAI attachment, int slotId )
	{
		bool can = super.CanReceiveAttachment(attachment, slotId);		
		if ( !can ){
			return false;
		}		
		if ( can && IsBurning() ) {			
			if ( slotId == InventorySlots.GetSlotIdFromString("LardALP") && FindAttachmentBySlotName("LardALP") ) {
				return false;			
			}			
		}
		return true;

		
	}		
}

modded class Fireplace extends FireplaceBase
{
	override bool CanReceiveAttachment( EntityAI attachment, int slotId )
	{
		bool can = super.CanReceiveAttachment(attachment, slotId);		
		if ( can ) {
			return true;
		}
		
		if (attachment.GetType() == "Lard" && slotId == InventorySlots.GetSlotIdFromString("LardALP") ) {			
			if ( !IsBurning() || !FindAttachmentBySlotName("LardALP") ) {
				return true;
			}		
		}
		return false;

		
	}		
}