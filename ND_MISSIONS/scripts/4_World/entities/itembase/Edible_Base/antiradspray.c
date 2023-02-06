
class alp_DecontaminationSpray extends Edible_Base
{
	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		//can_this_be_combined = true;
	}
	
	override bool CanPutAsAttachment( EntityAI parent )
	{

		return false;
	}

	override bool CanDetachAttachment( EntityAI parent )
	{
		
		return false;
	}
	
	override float GetDisinfectQuantity(int system = 0, Param param1 = null)
	{
		return (GetQuantityMax() * 0.25);
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionDecontamineTarget);
		AddAction(ActionDecontamineSelf);;
	
		
		
	}
}