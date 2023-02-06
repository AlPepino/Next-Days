

class alpEstatesItem
{
	int alp_Id;
	
	Widget alp_Root;
	
	int alp_PriceEstate;

	//int m_Action;
	ButtonWidget alp_ActionBtn;

	
	void alpEstatesItem(int balance, int validity, BuildingBase building, float exchange )
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		int pID = player.GetPlayerID();
		int pcID = player.GetClanID();
		
		alp_Id = building.GetWorldID();
		
		alp_Root  = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/EstateItem.layout");	
		
		TextWidget.Cast( alp_Root.FindAnyWidget("Estate") ).SetText( building.GetDisplayName() );	
		
		int olwOwner = 1;
		int boId = building.GetOwnerID();
		int bcId = building.GetClanID();
		if (  boId && ( boId != pID && bcId != pcID  ) ) {
			olwOwner = 2;
		}
		float volume = building.GetVolumeALP();
		
		alp_PriceEstate = (  volume * GetND().GetClans().GetBases().EstateValuePerCubicMeter + volume * GetND().GetClans().GetBases().BuildingTaxPerCubicMeterPerDay * validity ) * exchange;
		alp_PriceEstate*=olwOwner;
		
		TextWidget.Cast( alp_Root.FindAnyWidget("Price") ).SetText( alpUF.NumberToString(alp_PriceEstate,1) );
		
		int tax =  volume * GetND().GetClans().GetBases().BuildingTaxPerCubicMeterPerDay * exchange;
		
		TextWidget.Cast( alp_Root.FindAnyWidget("Tax") ).SetText( alpUF.NumberToString(tax,1) );
		
		
		int daysRemain = building.GetDaysRemain();
		
		if ( daysRemain < 0 ) 
			daysRemain = 0;
		
		TextWidget.Cast( alp_Root.FindAnyWidget("DaysRemain") ).SetText( alpUF.NumberToString(daysRemain,1) );
		

		alp_ActionBtn = ButtonWidget.Cast( alp_Root.FindAnyWidget("ActionButton") );
		ImageWidget.Cast( alp_Root.FindAnyWidget("ActionIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/Images/Confirm.paa");
		if (   ( boId != pID && bcId != pcID  ) && balance >= alp_PriceEstate )
		{//available buy lock COLOR_AVAILABLE_POSITIVE			
			alp_ActionBtn.Show( true );	
			
			ImageWidget.Cast( alp_Root.FindAnyWidget("ActionIcon") ).SetColor(COLOR_AVAILABLE_POSITIVE);
			
			//m_Action = 0;
		
		}
		if ( boId &&  ( boId == pID || bcId == pcID  ) ) {
		
			alp_ActionBtn.Show( true );	
			ImageWidget.Cast( alp_Root.FindAnyWidget("ActionIcon") ).SetColor(COLOR_AVAILABLE_NEGATIVE);
			//m_Action = 1;
		}	
		
		
		/*
		if ( building.GetOwnerID() > 0 )
		{
			ImageWidget.Cast( alp_Root.FindAnyWidget("IconSorted") ).Show( true );	
			
			COLOR_AVAILABLE_NEGATIVE
		}
		*/
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
	/*
	ImageWidget GetActionImage() {
		return 
	}
*/
	
	int GetEstatePrice()
	{
		return alp_PriceEstate;
	}

}

