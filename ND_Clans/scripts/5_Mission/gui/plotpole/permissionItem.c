
class alpPermissionItem
{
	
	Widget alp_Root;

	CheckBoxWidget alp_ActionBtn;

	int alp_Type;
	
	void alpPermissionItem( int type, string action , bool state)
	{
		alp_Type = type;
		
		alp_Root  = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/permissionItem.layout");	
		
		TextWidget.Cast( alp_Root.FindAnyWidget("Text") ).SetText( action );	
		
		
		alp_ActionBtn = CheckBoxWidget.Cast( alp_Root.FindAnyWidget("CheckBox") );
		
		alp_ActionBtn.SetChecked( state );
		

	}

	Widget GetWidget()	
	{

		return alp_Root;
	}
	int GetType()	
	{

		return alp_Type;
	}	

	CheckBoxWidget GetActionBtn()	
	{
	
		return alp_ActionBtn;
	}


}

