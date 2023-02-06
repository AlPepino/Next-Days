


class alpSpreadRumoursMenu extends UIScriptedMenu
{

	
	const int alp_UPDATE = 1;
	float alp_Update;
	
	protected PlayerBase					alp_Player;
	
	Widget 									alp_WindowGossip;
	
	TextWidget								alp_SaveGossipNegativeCost;
	TextWidget								alp_SaveGossipNegativeGain;
	TextWidget								alp_SaveGossipPositiveCost;
	TextWidget								alp_SaveGossipPositiveGain;
	
	
	ButtonWidget							alp_GossipNegativeBtn;
	ButtonWidget							alp_GossipPositiveBtn;
	
	autoptr map<int,string>						alp_CurrencyMapped;
	
	//balance	
	TextWidget								alp_BalanceText;
	float 									alp_Balance;

	
	Widget									alp_BodyWindowGossip;
	
	int 									alp_MyCash;
	ref alpSpreadRumoursFees 				alp_Fees;
	
	override Widget Init()
	{

		
		Class.CastTo(alp_Player,GetGame().GetPlayer());
		
		layoutRoot 	= GetGame().GetWorkspace().CreateWidgets("ND_Role_Playing/gui/layouts/SpreadRumour.layout");
		
		
		
		alp_BodyWindowGossip = Widget.Cast( layoutRoot.FindAnyWidget("BodyWindowGossip") );
		alp_SaveGossipNegativeCost = TextWidget.Cast( layoutRoot.FindAnyWidget( "GossipNegativeCost") );
		alp_SaveGossipNegativeGain = TextWidget.Cast( layoutRoot.FindAnyWidget( "GossipNegative") );
		alp_SaveGossipPositiveCost = TextWidget.Cast( layoutRoot.FindAnyWidget( "GossipPositiveCost") );
		alp_SaveGossipPositiveGain = TextWidget.Cast( layoutRoot.FindAnyWidget( "GossipPositive") );
		
		alp_GossipNegativeBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonWidgetNegative") );
		alp_GossipPositiveBtn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "ButtonWidgetPositive") );				
		

		ImageWidget.Cast( layoutRoot.FindAnyWidget("PositiveIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/smTrader.paa");		
		ImageWidget.Cast( layoutRoot.FindAnyWidget("NegativeIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/smTrader.paa");	
			
		
		ImageWidget.Cast( layoutRoot.FindAnyWidget("BalanceIcon") ).LoadImageFile(0,"ND_MISSIONS/gui/images/Cash.paa");		
		alp_BalanceText = TextWidget.Cast( layoutRoot.FindAnyWidget( "BalanceText") );
	
		
		//map currency
		alp_CurrencyMapped = new map<int,string>;
		map<int, ref alpCurrency> currencies = alpBANK.GetCurencies().GetCurrencies();	
		if ( 	currencies )
		{
			for (int c = 0; c < currencies.Count();c++)
			{
				alpCurrency currency = currencies.GetElement(c);
				alp_CurrencyMapped.Set(c,currency.Name);
			}			
		}	
		
		
		alp_BodyWindowGossip.Show( false );
		
		return layoutRoot;
	}
	
	void ~alpSpreadRumoursMenu()
	{
		alp_Player.GetSyncData().RegisterToEnhancedStatsSync(false);
		GetND().GetMS().GetTrader().SetValidTraderData( false );				
	}	
	

	
		
	override void OnShow()
	{
		super.OnShow();
		SetFocus( layoutRoot );
		GetGame().GetInput().ChangeGameFocus(1);	
		PPEffects.SetBlurMenu( GetND().GetMS().GetOptoinsTrader().NPC_Menu_blur );
		MissionGameplay.Cast( GetGame().GetMission() ).PlayerControlDisable(INPUT_EXCLUDE_ALL);
		GetGame().GetMission().GetHud().ShowHudUI( false );
		GetGame().GetMission().GetHud().ShowQuickbarUI( false );	
		
	}	
	override void OnHide()
	{
		super.OnHide();
		SetFocus( null );
		PPEffects.SetBlurMenu( 0 );
		GetGame().GetInput().ChangeGameFocus(-1);
		MissionGameplay.Cast( GetGame().GetMission() ).PlayerControlEnable(true);	
		GetGame().GetMission().GetHud().ShowHudUI( true );
		GetGame().GetMission().GetHud().ShowQuickbarUI( true );	
	}	

	bool alp_WindowInit = true;
	bool alp_WindowMain;
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if ( GetND().GetMS().GetTrader().IsTraderSet() && alp_WindowInit )
		{
			//TO DO: postpone + plus info about transaction
			alp_WindowInit = false;
			alp_WindowMain = true;
			alp_BodyWindowGossip.Show( true );
						
			InitWindow();

		}
		if ( !GetND().GetMS().GetTrader().IsTraderSet() && alp_WindowMain )
		{
			alp_WindowInit = true;
			alp_WindowMain = false;
			alp_BodyWindowGossip.Show( false );
		}
		alp_Update += timeslice;
		
		if (alp_WindowMain && alp_Update >= alp_UPDATE)
		{
			alp_Update = 0;
			
			RefreshBalance();
			RefreshBribes();
		}	

	}	

	void InitWindow()
	{
		RefreshBalance();	
		InitBribes();
		RefreshBribes();
	}
	
	void RefreshBalance()
	{	
		
		alp_MyCash = alp_Player.GetRP().GetCart().GetTotalBalance();

		alp_BalanceText.SetText( alpUF.NumberToString( alp_MyCash, 1 ) + " " + alp_CurrencyMapped.GetElement( alp_Player.GetRP().GetCart().GetCurrencyID() ) );	
	}	
	
	void InitBribes()
	{
		alpNPCtraderStock trader = GetND().GetMS().GetTrader().GetCurrentTrader();
		float currencyRate,coef;
		
		int level = alp_Player.GetSyncData().GetElement( alpRPelements.REPUTATION ).GetValue();
		float sale = 	GetND().GetRP().GetReputationMdf( level );			
		
		if ( trader )
		{
			currencyRate = alpBANK.GetCurrencyRate( trader.CurrencyID );	
		
			
			if (alp_Player.GetRP().IsHero())
			{
				coef = trader.PricelistRatioHero;	
			}
			else
			{
				coef = trader.PricelistRatioBandit;	
			}
			
			alp_Fees = GetND().GetRP().GetInteractions().GetRumoursFees( currencyRate, coef, sale );
		}
		
	}		
	
	void RefreshBribes()
	{	
		if ( alp_Fees )
		{
		
			alp_SaveGossipNegativeCost.SetText( "- " + alpUF.NumberToString( alp_Fees.NegativeGossipCost , 1 ) + " " + alp_CurrencyMapped.GetElement( alp_Player.GetRP().GetCart().GetCurrencyID() ) );	
			alp_SaveGossipNegativeGain.SetText( alpUF.NumberToString( alp_Fees.NegativeGossipGain , 1 ) );
			alp_SaveGossipNegativeGain.SetColor(COLOR_RED);
			
			alp_SaveGossipPositiveCost.SetText( "- " + alpUF.NumberToString( alp_Fees.PositiveGossipCost , 1 ) + " " + alp_CurrencyMapped.GetElement( alp_Player.GetRP().GetCart().GetCurrencyID() ) );
			alp_SaveGossipPositiveGain.SetText( alpUF.NumberToString( alp_Fees.PositiveGossipGain , 1 ) );
			alp_SaveGossipPositiveGain.SetColor(COLOR_GREEN);		
		
			alp_GossipNegativeBtn.Enable(  alp_MyCash >= alp_Fees.NegativeGossipCost );
			alp_GossipPositiveBtn.Enable( alp_MyCash >= alp_Fees.PositiveGossipCost );	
					
		}

	}		
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (super.OnClick(w, x, y, button)){
			return true;
		}
		else 
		{					
			switch (w.GetUserID())
			{		
				//main menu
				case 1:
					Close();
					return true;
				case 11:
					//alp_WindowGossip.Show(true);
					return true;											
			}
	
			return OnClickALP(w);
		}
	}	
	
	bool OnClickALP(Widget w)
	{
	
		if (CheckGossip_Buttons(w))
			return true;					
						
		return false;
	}		
	
	bool CheckGossip_Buttons(Widget w)
	{
		float exp;
		if (w == alp_GossipPositiveBtn)
		{
			exp = alp_Fees.PositiveGossipGain;
			
			GetND().GetMS().GetTrader().SpreadRumoursRPC( exp, alp_Fees.PositiveGossipCost , alp_Player );
					
			return true;
		}
		if (w == alp_GossipNegativeBtn)
		{
			exp = alp_Fees.NegativeGossipGain * -1;
			GetND().GetMS().GetTrader().SpreadRumoursRPC( exp, alp_Fees.NegativeGossipCost , alp_Player );
			return true;
		}		
		return false;
	}		

}
