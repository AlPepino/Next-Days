

modded class Cooking
{


	
	//Returns 1 if the item changed its cooking stage, 0 if not
	override int CookWithEquipment(ItemBase cooking_equipment, float cooking_time_coef = 1)
	{
		bool is_empty;
		
		//check cooking conditions
		if (cooking_equipment == null)
		{
			return 0;
		}
		
		//manage items in cooking equipment
		Param2<bool, bool> stateFlags = new Param2<bool, bool>(false, false); // 1st - done; 2nd - burned
		Param2<CookingMethodType, float> cookingMethodWithTime = GetCookingMethodWithTimeOverride(cooking_equipment);
		
		CargoBase cargo = cooking_equipment.GetInventory().GetCargo();
		if (cargo)
		{
			is_empty = cargo.GetItemCount() == 0;
			
			//process items
			for (int i = 0; i < cargo.GetItemCount(); i++)
			{
				ProcessItemToCook(ItemBase.Cast(cargo.GetItem(i)), cooking_equipment, cookingMethodWithTime, stateFlags);
			}
		}
		else
		{
			ProcessItemToCook(cooking_equipment, cooking_equipment, cookingMethodWithTime, stateFlags);
		}
		
		//manage cooking equipment
		Bottle_Base bottle_base = Bottle_Base.Cast(cooking_equipment);
		if ( bottle_base )
		{
			float cooking_equipment_temp = cooking_equipment.GetTemperature();
			bool is_water_boiling;
			
			//handle water boiling
			if (cooking_equipment_temp >= LIQUID_BOILING_POINT)
			{
				//remove agents
				cooking_equipment.RemoveAllAgentsExcept( alpeAgents.RADIATION);
				
				if (cooking_equipment.GetQuantity() > 0)
				{
					is_water_boiling = true;
					
					//vaporize liquid
					cooking_equipment.AddQuantity(-LIQUID_VAPOR_QUANTITY);
				};
			}
			
			//handle audio visuals
			bottle_base.RefreshAudioVisualsOnClient(cookingMethodWithTime.param1, stateFlags.param1, is_empty, stateFlags.param2);
		}

		FryingPan frying_pan = FryingPan.Cast(cooking_equipment);
		if (frying_pan && !bottle_base)
		{
			//handle audio visuals
			frying_pan.RefreshAudioVisualsOnClient(cookingMethodWithTime.param1, stateFlags.param1, is_empty, stateFlags.param2);
		}
		
		return 1;
	}
	
	//Returns 1 if the item changed its cooking stage, 0 if not
	override protected int UpdateCookingState(Edible_Base item_to_cook, CookingMethodType cooking_method, ItemBase cooking_equipment, float cooking_time_coef)
	{
		//food properties
		float food_temperature = item_to_cook.GetTemperature();
		
		//{min_temperature, time_to_cook, max_temperature (optional)}
		//get next stage name - if next stage is not defined, next stage name will be empty "" and no cooking properties (food_min_temp, food_time_to_cook, food_max_temp) will be set
		FoodStageType new_stage_type = item_to_cook.GetNextFoodStageType(cooking_method);

		float food_min_temp 	= 0;
		float food_time_to_cook = 0;
		float food_max_temp		= -1;
		
		//Set next stage cooking properties if next stage possible
		if (item_to_cook.CanChangeToNewStage(cooking_method)) // new_stage_type != NONE
		{
			array<float> next_stage_cooking_properties = new array<float>();
			next_stage_cooking_properties = FoodStage.GetAllCookingPropertiesForStage(new_stage_type, null, item_to_cook.GetType());
			
			food_min_temp = next_stage_cooking_properties.Get(eCookingPropertyIndices.MIN_TEMP);
			food_time_to_cook = next_stage_cooking_properties.Get(eCookingPropertyIndices.COOK_TIME);
			// The last element is optional and might not exist
			if (next_stage_cooking_properties.Count() > 2)
			{
				food_max_temp = next_stage_cooking_properties.Get(eCookingPropertyIndices.MAX_TEMP);
			}
		}
		
		//add temperature
		AddTemperatureToItem(item_to_cook, cooking_equipment, food_min_temp);
		
		//add cooking time if the food can be cooked by this method
		if (food_min_temp > 0 && food_temperature >= food_min_temp)
		{
			float new_cooking_time = item_to_cook.GetCookingTime() + COOKING_FOOD_TIME_INC_VALUE * cooking_time_coef;
			item_to_cook.SetCookingTime(new_cooking_time);
			
			//progress to next stage
			if (item_to_cook.GetCookingTime() >= food_time_to_cook)
			{
				//if max temp is defined check next food stage
				if (food_max_temp >= 0)
				{
					if (food_temperature > food_max_temp && item_to_cook.GetFoodStageType() != FoodStageType.BURNED)
					{
						new_stage_type = FoodStageType.BURNED;
					}
				}
				
				//! Change food stage
				item_to_cook.ChangeFoodStage(new_stage_type);
				//! Remove all modifiers
				item_to_cook.RemoveAllAgentsExcept(eAgents.BRAIN | alpeAgents.RADIATION);
				
				if (cooking_equipment)
				{
					if (cooking_method == CookingMethodType.BAKING)
					{
						ItemBase lard = GetItemTypeFromCargo(COOKING_INGREDIENT_LARD, cooking_equipment);
						if (lard)
						{
							//decrease lard quantity
							float lardQuantity = lard.GetQuantity() - COOKING_LARD_DECREASE_COEF;
							lardQuantity = Math.Clamp(lardQuantity, 0, lard.GetQuantityMax());
							lard.SetQuantity(lardQuantity);
							
							//! baking with lard
							DecreaseCookedItemQuantity(item_to_cook, COOKING_FOOD_QUANTITY_DECREASE_AMOUNT_LARD);
						}

						//! any foodstage without lard
						DecreaseCookedItemQuantity(item_to_cook, COOKING_FOOD_QUANTITY_DECREASE_AMOUNT_NONE);
					}
				}
				else
				{
					//! any foodstage without lard 
					DecreaseCookedItemQuantity(item_to_cook, COOKING_FOOD_QUANTITY_DECREASE_AMOUNT_NONE);
				}
				
				//reset cooking time
				item_to_cook.SetCookingTime(0);

				return 1;
			}
		}
		
		return 0;
	}
	
	//Returns 1 if the item changed its cooking stage, 0 if not
	override protected int UpdateCookingStateOnStick( Edible_Base item_to_cook, float cook_time_inc )
	{
		//food properties
		float food_temperature = item_to_cook.GetTemperature();
		
		//{min_temperature, time_to_cook, max_temperature (optional)}
		//get next stage name - if next stage is not defined, next stage name will be empty "" and no cooking properties (food_min_temp, food_time_to_cook, food_max_temp) will be set
		FoodStageType new_stage_type = item_to_cook.GetNextFoodStageType( CookingMethodType.BAKING );
		float food_min_temp = 0;
		float food_time_to_cook = 0;
		float food_max_temp = -1;
		bool is_done = false;	// baked
		bool is_burned = false;	// burned

		//Set next stage cooking properties if next stage possible
		if ( item_to_cook.CanChangeToNewStage( CookingMethodType.BAKING ) )
		{
			array<float> next_stage_cooking_properties = new array<float>;
			next_stage_cooking_properties = FoodStage.GetAllCookingPropertiesForStage( new_stage_type, null, item_to_cook.GetType() );
			
			food_min_temp = next_stage_cooking_properties.Get( eCookingPropertyIndices.MIN_TEMP );
			food_time_to_cook = next_stage_cooking_properties.Get( eCookingPropertyIndices.COOK_TIME );
			// The last element is optional and might not exist
			if ( next_stage_cooking_properties.Count() > 2 )
				food_max_temp = next_stage_cooking_properties.Get( eCookingPropertyIndices.MAX_TEMP );
		}
		
		
		// refresh audio
		if (item_to_cook.GetInventory().IsAttachment())
		{
			item_to_cook.MakeSoundsOnClient(true);
			//add temperature
			AddTemperatureToItem(item_to_cook, null, food_min_temp);
		}
		
		//add cooking time if the food can be cooked by this method
		if ( food_min_temp > 0 && food_temperature >= food_min_temp )
		{
			float new_cooking_time = item_to_cook.GetCookingTime() + cook_time_inc;
			item_to_cook.SetCookingTime( new_cooking_time );
			
			//progress to next stage
			if ( item_to_cook.GetCookingTime() >= food_time_to_cook )
			{
				//if max temp is defined check next food stage
				if ( food_max_temp >= 0 )
				{
					if ( food_temperature > food_max_temp && item_to_cook.GetFoodStageType() != FoodStageType.BURNED )
					{
						new_stage_type = FoodStageType.BURNED;
					}
				}
				
				//change food stage
				item_to_cook.ChangeFoodStage( new_stage_type );
				//Temp
				//Remove all modifiers
				item_to_cook.RemoveAllAgentsExcept(eAgents.BRAIN | alpeAgents.RADIATION);

				//reset cooking time
				item_to_cook.SetCookingTime( 0 );
				return 1;
			}
		}
		
		return 0;
	}
	
	override  void SmokeItem( Edible_Base item_to_cook, float cook_time_inc )
	{
		if ( item_to_cook )
		{
			if ( ( item_to_cook.GetFoodStageType() == FoodStageType.RAW ) || ( item_to_cook.GetFoodStageType() == FoodStageType.BAKED ) || ( item_to_cook.GetFoodStageType() == FoodStageType.BOILED ) )
			{
				float new_cooking_time = item_to_cook.GetCookingTime() + ( cook_time_inc );
				item_to_cook.SetCookingTime( new_cooking_time );

				if ( item_to_cook.GetCookingTime() >= FoodStage.GetCookingPropertyFromIndex( eCookingPropertyIndices.COOK_TIME, FoodStageType.DRIED, null, item_to_cook.GetType()) )
				{
					item_to_cook.ChangeFoodStage( FoodStageType.DRIED );
					item_to_cook.RemoveAllAgentsExcept(eAgents.BRAIN | alpeAgents.RADIATION );
				}
			}
			else
			{
				item_to_cook.SetCookingTime( 0 );
			}
		}
	}
	



	


}
