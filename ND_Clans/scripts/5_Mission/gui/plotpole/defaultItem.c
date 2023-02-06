
class alpDefaultItem
{
	int alp_Id;
	
	Widget alp_Root;
	
	int alp_Price;

	
	ButtonWidget alp_ActionBtn;

	
	void alpDefaultItem(int balance, int price, BuildingBase building )
	{
		alp_Id = building.GetWorldID();
		
		alp_Root  = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/defaultItem.layout");	
		
		TextWidget.Cast( alp_Root.FindAnyWidget("Estate") ).SetText( building.GetDisplayName() );	
		
		
		alp_Price = price;
		
		//if ( balance
		
		TextWidget.Cast( alp_Root.FindAnyWidget("Price") ).SetText( alpUF.NumberToString(price,1) );
		
		if ( balance >= price )
		{		
			alp_ActionBtn = ButtonWidget.Cast( alp_Root.FindAnyWidget("ActionButton") );
			alp_ActionBtn.Show( true );	
			ImageWidget.Cast( alp_Root.FindAnyWidget("ActionIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/Images/Confirm.paa");
			ImageWidget.Cast( alp_Root.FindAnyWidget("ActionIcon") ).SetColor(COLOR_AVAILABLE_POSITIVE);
		}

	}

	int GetWorldID()
	{
		return alp_Id;
	}
	
	Widget GetWidget()	
	{

		return alp_Root;
	}
	

	ButtonWidget GetActionBtn()	
	{
	
		return alp_ActionBtn;
	}

	
	int GetPrice()
	{
		return alp_Price;
	}

	
	void SetSortedIcon()
	{
		alp_ActionBtn.Show( false );	
		ImageWidget.Cast( alp_Root.FindAnyWidget("IconSorted") ).Show( true );	
	}
}

