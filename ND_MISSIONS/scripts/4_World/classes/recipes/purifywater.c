
modded class PurifyWater extends RecipeBase
{	


	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		ItemBase ingredient2 = ingredients[1];
		ingredient2.RemoveAllAgentsExcept( alpeAgents.RADIATION );
		
	}
};
