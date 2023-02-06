modded class CraftFireplace extends RecipeBase
{
	override void Init()
	{
		super.Init();
		//ingredient 1
		InsertIngredient(0,"alp_Money");//you can insert multiple ingredients this way
		//ingredient 2
		InsertIngredient(1,"alp_Money");//you can insert multiple ingredients this way	

		//ingredient 1
		InsertIngredient(0,"Lard");//you can insert multiple ingredients this way
		//ingredient 2
		InsertIngredient(1,"Lard");//you can insert multiple ingredients this way	
	}

	override void Do( ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight )//gets called upon recipe's completion
	{
		ItemBase result = ItemBase.Cast( results.Get( 0 ) );
		ItemBase ingredient1 = ingredients[0];
		ItemBase ingredient2 = ingredients[1];

		//clear inventory reservation
		if ( !GetGame().IsMultiplayer() )
		{
			InventoryLocation loc = new InventoryLocation;
			ingredient1.GetInventory().GetCurrentInventoryLocation( loc );
			player.GetInventory().ClearInventoryReservationEx( ingredient1, loc );
			ingredient2.GetInventory().GetCurrentInventoryLocation( loc );
			player.GetInventory().ClearInventoryReservationEx( ingredient2, loc );			
		}
		
		//Ingredient 1
		if ( ingredient1.GetQuantity() <= 0 || ingredient1.GetType() == "Lard" )
		{
			if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
			{
				
				if (ingredient1.GetType() == "Lard")
				{
					player.ServerTakeEntityToTargetAttachmentEx( result, ingredient1, InventorySlots.GetSlotIdFromString("LardALP")  );	
				}
				else
					player.ServerTakeEntityToTargetAttachment( result, ingredient1 ); // multiplayer server side
				
			}
			else
			{
				if (ingredient1.GetType() == "Lard")
				{
					player.LocalTakeEntityToTargetAttachmentEx( result, ingredient1, InventorySlots.GetSlotIdFromString("LardALP")  );	
				}
				else
					player.LocalTakeEntityToTargetAttachment( result, ingredient1 ); // single player or multiplayer client side
			}
		}
		else
		{
			string ingredient1_classname = ingredient1.GetType();
			ItemBase attachment1 = ItemBase.Cast( result.GetInventory().CreateAttachment( ingredient1_classname ) );
			MiscGameplayFunctions.TransferItemProperties( ingredient1, attachment1 );
			attachment1.SetQuantity( 1 );
			attachment1.SetCleanness(0);
			
			//set quantity to ingredient
			ingredient1.AddQuantity( -1 );
		}
		
		//Ingredient 2
		if ( ingredient2.GetQuantity() <= 0  || ingredient2.GetType() == "Lard" )
		{
			if ( GetGame().IsServer() && GetGame().IsMultiplayer() )
			{
				
				if (ingredient2.GetType() == "Lard")
				{
					player.ServerTakeEntityToTargetAttachmentEx( result, ingredient2, InventorySlots.GetSlotIdFromString("LardALP")  );	
				}
				else
					player.ServerTakeEntityToTargetAttachment( result, ingredient2 ); // multiplayer server side
			
				
			}
			else
			{

				if (ingredient2.GetType() == "Lard")
				{
					player.LocalTakeEntityToTargetAttachmentEx( result, ingredient2, InventorySlots.GetSlotIdFromString("LardALP")  );	
				}
				else
					player.LocalTakeEntityToTargetAttachment( result, ingredient2 ); // single player or multiplayer client side
				
			}
		}
		else
		{
			string ingredient2_classname = ingredient2.GetType();
			ItemBase attachment2 = ItemBase.Cast( result.GetInventory().CreateAttachment( ingredient2_classname ) );
			MiscGameplayFunctions.TransferItemProperties( ingredient2, attachment2 );
			attachment2.SetQuantity( 1 );
			attachment2.SetCleanness(0);
			//set quantity to ingredient
			ingredient2.AddQuantity( -1 );
		}
	}	
}
