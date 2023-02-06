
class alpTaxesItem
{
	int alp_Price;
	int alp_Radius;
	int alp_Validity;
	Widget alp_Root;
	
	
	ButtonWidget alp_ActionBtn;
	
	void alpTaxesItem(int balance, int rank, int radius, int validity , int landTax, int estateTax = 0 )
	{
		alp_Radius = radius;
		alp_Validity = validity;
		
		alp_Root  = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/TaxItem.layout");	
		
		string iconReputation = "ND_MISSIONS/gui/images/Reputation/r" + rank.ToString() + ".paa";			
		ImageWidget.Cast( alp_Root.FindAnyWidget("TierImage") ).LoadImageFile(0,iconReputation);
		
		alp_ActionBtn = ButtonWidget.Cast( alp_Root.FindAnyWidget("ActionButton") );
		ImageWidget.Cast( alp_Root.FindAnyWidget("ActionIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/Images/Confirm.paa");
		ImageWidget.Cast( alp_Root.FindAnyWidget("ActionIcon") ).SetColor(COLOR_AVAILABLE_POSITIVE);
		
		TextWidget.Cast( alp_Root.FindAnyWidget("Radius") ).SetText( radius.ToString() );	
		TextWidget.Cast( alp_Root.FindAnyWidget("Validity") ).SetText( validity.ToString() );	
		TextWidget.Cast( alp_Root.FindAnyWidget("LandTax") ).SetText( alpUF.NumberToString( landTax,1) );	
		TextWidget.Cast( alp_Root.FindAnyWidget("PropertyTax") ).SetText( alpUF.NumberToString( estateTax,1) );
		
		alp_Price = landTax + estateTax;
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		int reputation = 0;
		
		if ( player )
		{
			reputation = Math.AbsInt( player.GetSyncData().GetElement( alpRPelements.REPUTATION).GetValue() );

		}
		
		
		if ( balance >= alp_Price && reputation >= rank )
		{
			ButtonWidget.Cast( alp_Root.FindAnyWidget("ActionButton") ).Show( true );	

		}
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
	int GetRadius()
	{
		return alp_Radius;
	}	
	int GetValidity()
	{
		return alp_Validity;
	}		
}

