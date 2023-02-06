
modded class DisinfectItem extends RecipeBase
{	


	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		ItemBase ingredient1, ingredient2;
		Class.CastTo(ingredient1, ingredients[0]);
		

		ingredient1.AddQuantity(-ingredient1.GetDisinfectQuantity());

		Class.CastTo(ingredient2, ingredients[1]);
		ingredient2.RemoveAllAgentsExcept(eAgents.BRAIN | eAgents.SALMONELLA | eAgents.CHOLERA | alpeAgents.RADIATION);
		ingredient2.SetCleanness(1);
	}
};
