modded class ItemManager
{


	override void PrepareTooltip( EntityAI item, int x = 0, int y = 0 )
	{
		super.PrepareTooltip(item,x,y);
		

		if (item && item.IsItemBase() )
		{
			
			InspectMenuNew.UpdateItemLiquidTypeALP( m_TooltipWidget, ItemBase.Cast( item ) );
			
		}
	}

}
