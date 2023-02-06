
class alp_ATM extends BuildingSuper  //Land_Medical_Tent_Shower
{

		
	void alp_ATM()
	{
	
	}
	
	override bool IsBuilding()
	{
		return false;
	}
	

	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(alpActionATM);

	}
	



}