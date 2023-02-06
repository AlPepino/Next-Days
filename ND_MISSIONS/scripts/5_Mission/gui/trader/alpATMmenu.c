enum alpATM_STAGE
{
	LOGIN=0,
	CURRENCY,
	ACCOUNT,
}

class alpTransactionATM 
{
	int Stage;
	int Setting;	
	
	bool RequestUpdate;
	
	
	void SetStage(int stage, int setting = 0)
	{
		Stage = stage;
		Setting = setting;
	}
	
	int IsRequestedUpdate()
	{
		bool update = RequestUpdate;
		RequestUpdate = false;
		return update;
	}
	
	void SetRequestUpdate()
	{
		RequestUpdate = true;
	}
	
	int GetStage()
	{
		return Stage;
	}
	int GetType()
	{
		return Setting;
	}
}


class alpATMmenu extends UIScriptedMenu
{
	protected PlayerBase					alp_Player;
	protected alp_Debitcard					alp_PayCard;
	ref alpTransactionATM					alp_ATMstage;
	
	bool									alp_IsLogged;
	bool									alp_IsChangingPswd;
	bool 									alp_IsLoanPossible;

	
	int										alp_LogCounter;
	
	int 									alp_CurrencyType;
	
	float									alp_LoanInterest;
	int										alp_LoanTotal;
	int										alp_ExchangeCost;
	
	Widget									alp_LoginPanel;
	Widget									alp_CurrencyPanel;
	Widget									alp_AccountPanel;
	
	EditBoxWidget							alp_PIN;
	EditBoxWidget							alp_NEWPIN;
	EditBoxWidget							alp_NEWPIN2;
	
	XComboBoxWidget							alp_Currency;
	XComboBoxWidget							alp_CurrencyExchange;
	autoptr map<int,string>					alp_CurrencyMapped;
	
	int alp_AccountBalance;
	int alp_PlayerCash;
	int alp_AccountID;
	EditBoxWidget							alp_UserInput;
	
	TextListboxWidget						alp_CardsList;
	int 									alp_SelectedCard = -1;
	
	TextWidget								alp_LoginMessage;
	
	override Widget Init()
	{
		/*
		GetGame().GetMission().GetHud().ShowHudUI( false );
		GetGame().GetMission().GetHud().ShowQuickbarUI( false );
		GetGame().GetInput().ChangeGameFocus(1);
		*/
		
		alp_CurrencyMapped = new map<int,string>;
		
		Class.CastTo(alp_Player,GetGame().GetPlayer());
		alp_PayCard = alp_Debitcard.Cast( alp_Player.GetItemInHands() );
		
		alp_ATMstage = new alpTransactionATM();
		
		layoutRoot 	= GetGame().GetWorkspace().CreateWidgets("ND_MISSIONS/gui/layouts/ATM.layout");
			
		alp_LoginPanel = Widget.Cast( layoutRoot.FindAnyWidget( "Login") );		
		alp_CurrencyPanel = Widget.Cast( layoutRoot.FindAnyWidget( "Currency") );	
		alp_AccountPanel = Widget.Cast( layoutRoot.FindAnyWidget( "Account") );	
		
		alp_PIN = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "PIN_Input") );	
		alp_NEWPIN = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "NEWPIN_Input") );	
		alp_NEWPIN2 = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "NEWPIN2_Input") );	
	
		alp_Currency = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "CurrencyInput" ) );
		alp_CurrencyExchange = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "ExhangeCurrency" ) );
		
		alp_UserInput = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "INPUT_account") );	
		
		alp_CardsList = TextListboxWidget.Cast( layoutRoot.FindAnyWidget( "CardsList" ) );
			

		alp_LoginMessage = TextWidget.Cast( layoutRoot.FindAnyWidget( "Login_Message" ) );	
		alp_LoginMessage.SetText("");
							
		
		SetATMpanels(-1);
		
		//if not required payment card
		if ( GetND().GetMS().GetOptoinsTrader().ATM_NotRequiresPaymentCard )
		{//acces without card
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_0_login" ) ).Show( false );
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_3_Cards" ) ).Show( false );
			VerifyLogin();	
		}		
		
		
		
		
		return layoutRoot;
	}
	override void OnShow()
	{
		super.OnShow();

		SetFocus( layoutRoot );
		GetGame().GetInput().ChangeGameFocus(1);	
		PPEffects.SetBlurMenu( GetND().GetMS().GetOptoinsTrader().ATM_Menu_blur );
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
	void ~alpATMmenu()
	{
		/*
		GetGame().GetMission().GetHud().ShowHudUI( true );
		GetGame().GetMission().GetHud().ShowQuickbarUI( true );			
		GetGame().GetInput().ChangeGameFocus(-1);
		*/
		
		GetND().GetMS().GetTrader().SetValidTraderData( false );
	}	

	void VerifyLogin()
	{
		//if (!alp_IsChangingPswd)
		alpBankAccount account = alpBANK.GetClientAccount();
		
		if ( account )
		{
			alp_AccountID  = account.GetAccountID();
			
			if ( GetND().GetMS().GetOptoinsTrader().ATM_NotRequiresPaymentCard )
			{//acces without card
				alp_IsLogged = true;
				alp_ATMstage.SetStage( alpATM_STAGE.CURRENCY );
				
			}
			else
			{
				int card_id = alp_PayCard.GetCardID();
				int card_psw = alp_PayCard.GetCardPIN();
				
				if ( account.RegisteredCards.Find( card_id ) >= 0 )
				{
					int password = alp_PIN.GetText().ToInt();
	
					if (alp_IsLogged || password == card_psw )
					{//login success
						alp_LoginMessage.SetText("");
						alp_IsLogged = true;
						alp_ATMstage.SetStage( alpATM_STAGE.CURRENCY );
					}				
					else
					{
						alp_LoginMessage.SetText("#alp_atm_login_wrongpin");
						alp_LogCounter++;		
						
						if (alp_LogCounter>3)
						{
							GetND().GetMS().GetTrader().BlockCard( account.GetAccountID(), card_id, alp_Player );
							Close();	
						}			
					}								
					if ( alp_IsChangingPswd )
					{
						int pinnew = alp_NEWPIN.GetText().ToInt();
						int pinnew2 = alp_NEWPIN2.GetText().ToInt();
						
						if (pinnew == pinnew2 && pinnew >= 0 && pinnew <= 9999 )
						{//login success
	
							GetND().GetMS().GetTrader().GhangePassword( pinnew, alp_Player );
						}										
					}
					
				}
				else
				{
					//blocked
					Close();	
				}			
			}
			

			
			//set currency select menu
			map<int, ref alpCurrency> currencies = alpBANK.GetCurencies().GetCurrencies();	
			if ( 	currencies )
			{
				alp_Currency.ClearAll();
				alp_CurrencyExchange.ClearAll();
				for (int c = 0; c < currencies.Count();c++)
				{
					alp_Currency.AddItem("name");
					alpCurrency currency;
					currency = currencies.GetElement(c);
					alp_CurrencyMapped.Set( c ,currency.Name);
					alp_Currency.SetItem(c,currency.Name);
					alp_CurrencyExchange.AddItem("name");
					alp_CurrencyExchange.SetItem(c,currency.Name);
											
				}			
			}
		}
		else
		{
			Close();
		}

	
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
			
		if (GetND().GetMS().GetTrader().IsTraderSet())
		{
			int stage = alp_ATMstage.GetStage();
			switch (stage)
			{
				case alpATM_STAGE.LOGIN:
				{
					if (!alp_LoginPanel.IsVisible() || alp_ATMstage.IsRequestedUpdate() )
					{
						SetATMpanels( alpATM_STAGE.LOGIN );
						//setup btns
						ButtonWidget.Cast( layoutRoot.FindAnyWidgetById( 4 ) ).Show( alp_IsLogged );

						alp_NEWPIN.Show( alp_IsChangingPswd );
						alp_NEWPIN2.Show( alp_IsChangingPswd );
						TextWidget.Cast( layoutRoot.FindAnyWidget( "TitlePINNEW" ) ).Show( alp_IsChangingPswd );
						TextWidget.Cast( layoutRoot.FindAnyWidget( "TitlePINNEW2" ) ).Show( alp_IsChangingPswd );
					}
					break;
				}
				case alpATM_STAGE.CURRENCY:
				{
					if (!alp_CurrencyPanel.IsVisible()  || alp_ATMstage.IsRequestedUpdate()  )
					{
						SetATMpanels( alpATM_STAGE.CURRENCY );
					}				
					break;
				}
				case alpATM_STAGE.ACCOUNT:
				{
					if (!alp_AccountPanel.IsVisible()  || alp_ATMstage.IsRequestedUpdate() )
					{
						SetAccountPanel();
						SetAccountsPanels( alp_ATMstage.GetType() );
						SetATMpanels( alpATM_STAGE.ACCOUNT );
						
					}
					break;
				}						
			}		
		}
		else
		{
			SetATMpanels(-1);
			//alp_ATMstage.SetRequestUpdate();	 //for sure 
		}

	}
	
	void SetAccountPanel()
	{
		alpBankAccount account = alpBANK.GetClientAccount();
		if ( account )
		{
			TextWidget.Cast( layoutRoot.FindAnyWidget( "AccountTitle" )).SetText( account.Name );	
			
			
			alp_AccountBalance = account.GetBalance( alp_CurrencyType );
			
			int sumLoans = GetLoan(alp_CurrencyType );
			
			TextWidget.Cast( layoutRoot.FindAnyWidget( "AccountBalance" )).SetText( alpUF.NumberToString(alp_AccountBalance,1) + " " + alp_CurrencyMapped.GetElement(alp_CurrencyType) );	
			
			
			if ( sumLoans > 0)
			{
				RichTextWidget.Cast( layoutRoot.FindAnyWidget( "AccountLoans" )).SetText( alpUF.NumberToString(sumLoans,1) + " " + alp_CurrencyMapped.GetElement(alp_CurrencyType) + " (#alp_atm_loan_maturity " + GetLoanMaturity() + ")" );	
			}
			else
			{
				RichTextWidget.Cast( layoutRoot.FindAnyWidget( "AccountLoans" )).SetText( alpUF.NumberToString(sumLoans,1) + " " + alp_CurrencyMapped.GetElement(alp_CurrencyType) );	
			}
			
			
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_3_LoanTake" ) ).Enable(  sumLoans == 0 );
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_3_LoanTake" ) ).SetColor( GetBtnColor( sumLoans == 0 ) );
			
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_3_LoanPay" ) ).Enable(  sumLoans >0 );
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_3_LoanPay" ) ).SetColor(  GetBtnColor( sumLoans >0 ) );
					
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_3_Exchange" ) ).Enable(  alp_AccountBalance >0 );
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_3_Exchange" ) ).SetColor(  GetBtnColor( alp_AccountBalance >0 ) );

			float playerLimit = GetND().GetMS().GetOptoinsTrader().PlayerLoanLimit;
			float showExchange = !GetND().GetMS().GetOptoinsTrader().DisableExchange;
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_3_LoanTake" ) ).Show ( playerLimit );
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_3_LoanPay" ) ).Show ( playerLimit );
			ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BTN_3_Exchange" ) ).Show ( showExchange );
		}		
		
	}
	
	int GetBtnColor( bool state )
	{
		if ( state )
		{
			return ARGB(255,20,34,76);
		}
		else
		{
			return ARGB(255,53,64,97);
		}
	}
	
	
	string GetLoanMaturity()
	{
		string maturity;
		alpBankAccount account = alpBANK.GetClientAccount();
		if ( account )
		{
			if (account.Loans )
			{
				foreach( alpLoans loan : account.Loans)
				{
					if ( loan )
					{
						if ( loan.CurrencyID == alp_CurrencyType )
						{
							maturity = loan.Terminated[0].ToString() + "/" + loan.Terminated[1].ToString() + "/" + loan.Terminated[2].ToString();
						}					
					}
				}
			}	
		}	
		return maturity;
	}
	
	int GetLoan(int currency)
	{
		int sum = 0;
		alpBankAccount account = alpBANK.GetClientAccount();
		if ( account )
		{
			if (account.Loans)
			{
				foreach( alpLoans loan : account.Loans)
				{
					if ( loan )
					{
						if ( loan.CurrencyID == currency )
						{
							sum = sum + loan.Principal + loan.Interest;
						}					
					}
				}
			}	
		}		
		return sum;
	}
	
	void SetATMpanels(int stage)
	{
		alp_LoginPanel.Show(alpATM_STAGE.LOGIN == stage);
		alp_CurrencyPanel.Show(alpATM_STAGE.CURRENCY == stage);
		alp_AccountPanel.Show(alpATM_STAGE.ACCOUNT == stage);
		
		if ( !GetND().GetMS().GetOptoinsTrader().ATM_NotRequiresPaymentCard )
		{
			ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(1) ).Show( alpATM_STAGE.LOGIN <= stage);		
		}

		ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(20) ).Show( alpATM_STAGE.CURRENCY <= stage);
		ButtonWidget.Cast( layoutRoot.FindAnyWidgetById(30) ).Show( alpATM_STAGE.ACCOUNT <= stage);		
	}

	void SetAccountsPanels(int stage)
	{		
		Widget.Cast( layoutRoot.FindAnyWidget("AccountWindow0") ).Show( stage == 0 );
		Widget.Cast( layoutRoot.FindAnyWidget("AccountWindow1") ).Show( stage == 1 || stage == 2);
		Widget.Cast( layoutRoot.FindAnyWidget("AccountWindow2") ).Show( stage == 3 );
		Widget.Cast( layoutRoot.FindAnyWidget("AccountWindow3") ).Show( stage == 4 );
		Widget.Cast( layoutRoot.FindAnyWidget("AccountWindow4") ).Show( stage == 5 );
		Widget.Cast( layoutRoot.FindAnyWidget("AccountWindow5") ).Show( stage == 6 );
		
		ButtonWidget.Cast( layoutRoot.FindAnyWidget("BTN_3_confirm") ).Show( stage > 0 );
		ButtonWidget.Cast( layoutRoot.FindAnyWidget("BTN_3_back") ).Show( stage > 0 );
		EditBoxWidget.Cast( layoutRoot.FindAnyWidget("INPUT_account") ).Show( stage > 0 && stage != 6);
		
		int inputValue = EditBoxWidget.Cast( layoutRoot.FindAnyWidget("INPUT_account") ).GetText().ToInt();
		
		int depositLimit = alpBANK.GetDepositLimit(alp_Player);
						
		if (stage > 0)
		{
			alp_PlayerCash = alp_Player.GetRP().GetCart().GetMoney(alp_CurrencyType);						
		}
		TextWidget.Cast( layoutRoot.FindAnyWidget( "AccountCash" )).SetText( alpUF.NumberToString(alp_PlayerCash,1) + " " + alp_CurrencyMapped.GetElement(alp_CurrencyType) );
		TextWidget.Cast( layoutRoot.FindAnyWidget( "AccountCashTitle" )).Show( stage == 1 || stage == 2);
		TextWidget.Cast( layoutRoot.FindAnyWidget( "AccountCash" )).Show( stage == 1 || stage == 2);

		//withdraw
		if ( stage == 1 )
		{	
			ButtonWidget.Cast( layoutRoot.FindAnyWidget("BTN_3_confirm") ).Show( inputValue > 0 && inputValue <= alp_AccountBalance );	
		}
		//deposit
		if ( stage == 2 )
		{	
			ButtonWidget.Cast( layoutRoot.FindAnyWidget("BTN_3_confirm") ).Show( inputValue > 0 && inputValue <= alp_PlayerCash && depositLimit >= ( alp_AccountBalance + inputValue) );	
		}		
		//loans
		if ( stage == 3 )
		{
			float interest = alpBANK.GetLoanInterest( alp_Player ) * 100;
			TextWidget.Cast( layoutRoot.FindAnyWidget( "LoanTerms" )).SetText( interest.ToString() + " %" );
			TextWidget.Cast( layoutRoot.FindAnyWidget( "LoanTotal" )).SetText( "0" );
			TextWidget.Cast( layoutRoot.FindAnyWidget( "AccountLoanLimitTitle" )).SetText( "#alp_atm_loans_limit: " + alpUF.NumberToString(alpBANK.GetLoanLimit(alp_Player,alp_CurrencyType),1) + " " + alp_CurrencyMapped.GetElement(alp_CurrencyType) );
			if ( inputValue > 0 && inputValue <= alpBANK.GetLoanLimit(alp_Player,alp_CurrencyType) )
			{
				
				int selectedInterest = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "LoanLength" ) ).GetCurrentItem();
				
				if ( selectedInterest > 0 )
				{
					alp_LoanInterest = alpBANK.GetLoanInterest( alp_Player ) * Math.Pow( selectedInterest, -0.2);
					interest = alp_LoanInterest * 100;
					TextWidget.Cast( layoutRoot.FindAnyWidget( "LoanTerms" )).SetText( interest.ToString() + " % p.d." );
					alp_LoanTotal = inputValue * Math.Pow( (1 +  alp_LoanInterest), selectedInterest);
					TextWidget.Cast( layoutRoot.FindAnyWidget( "LoanTotal" )).SetText( alpUF.NumberToString(alp_LoanTotal,1) + " " + alp_CurrencyMapped.GetElement(alp_CurrencyType) );
					alp_IsLoanPossible = true;	
				}
				else
				{
					alp_IsLoanPossible = false;
				}			
			}
			else
			{
				alp_IsLoanPossible = false;
			}

			if ( GetLoan(alp_CurrencyType ) == 0 )
			{
				ButtonWidget.Cast( layoutRoot.FindAnyWidget("BTN_3_confirm") ).Show( alp_IsLoanPossible && depositLimit >= ( alp_AccountBalance + inputValue) );
			}
			else
			{
				ButtonWidget.Cast( layoutRoot.FindAnyWidget("BTN_3_confirm") ).Show( false );
			}
			
		}
		//pay loan
		if ( stage == 4 )
		{
			int loan = GetLoan(alp_CurrencyType );
			ButtonWidget.Cast( layoutRoot.FindAnyWidget("BTN_3_confirm") ).Show( inputValue > 0 && inputValue <= loan && inputValue <= alp_AccountBalance );
		}		
		//exchange
		if ( stage == 5 )
		{
			int selectedCurrency = alp_CurrencyExchange.GetCurrentItem();
			
			float rate = alpBANK.GetExchangeRate(alp_CurrencyType,selectedCurrency);
			
			TextWidget.Cast( layoutRoot.FindAnyWidget( "ExchangeAvailable" )).Show( selectedCurrency != alp_CurrencyType );
			EditBoxWidget.Cast( layoutRoot.FindAnyWidget("INPUT_account") ).Show( selectedCurrency != alp_CurrencyType );
			TextWidget.Cast( layoutRoot.FindAnyWidget( "ExchangeRate" )).Show( selectedCurrency != alp_CurrencyType );
			TextWidget.Cast( layoutRoot.FindAnyWidget( "ExchangeTotal" )).Show( selectedCurrency != alp_CurrencyType && inputValue > 0 );
			int exchangeLimit = alpBANK.GetExchangeLimit(selectedCurrency);
			TextWidget.Cast( layoutRoot.FindAnyWidget( "ExchangeAvailable" )).SetText( "#alp_atm_exchange_available: " + alpUF.NumberToString(exchangeLimit ,1) + " " + alp_CurrencyMapped.GetElement(selectedCurrency) );
			TextWidget.Cast( layoutRoot.FindAnyWidget( "ExchangeRate" )).SetText( rate.ToString() + " " + alp_CurrencyMapped.GetElement(alp_CurrencyType) + " / 1 " + alp_CurrencyMapped.GetElement(selectedCurrency) );
			
			//inputValue
			alp_ExchangeCost = Math.Ceil( inputValue *  rate );
			TextWidget.Cast( layoutRoot.FindAnyWidget( "ExchangeTotal" )).SetText(  alpUF.NumberToString( alp_ExchangeCost,1) + " " + alp_CurrencyMapped.GetElement(alp_CurrencyType) );
			
			ButtonWidget.Cast( layoutRoot.FindAnyWidget("BTN_3_confirm") ).Show( selectedCurrency != alp_CurrencyType && inputValue > 0 && inputValue <= exchangeLimit && alp_AccountBalance >= alp_ExchangeCost );	
			
		}	
		//cards
		if ( stage == 6 )
		{
			//alp_CardsList	
			alpBankAccount account = alpBANK.GetClientAccount();			
			alp_CardsList.ClearItems();
			if ( account )
			{
				if ( account.RegisteredCards )
				{
					int connected = -1;
					for (int i = 0; i < account.RegisteredCards.Count();i++)
					{
						int idCard = account.RegisteredCards.Get(i);
						
						if ( idCard == alp_PayCard.GetCardID())
						{
							connected = i;
						}
						alp_CardsList.AddItem(idCard.ToString(),null,0);
					}
					if ( connected >= 0 )
					{
						alp_CardsList.SetItem(connected,"#alp_atm_cards_connected",null,1);
					}
					if ( alp_SelectedCard >= 0)
					{
						alp_CardsList.SetItemColor(alp_SelectedCard,0,COLOR_GREEN);	
					}
										
				}

			}
			ButtonWidget.Cast( layoutRoot.FindAnyWidget("BTN_3_confirm") ).Show( alp_SelectedCard >= 0 );
		}			
	}
	
	override bool OnChange( Widget w, int x, int y, bool finished )
	{
		if( w == alp_UserInput )
		{
			VerifyUserInput( alp_UserInput );
			alp_ATMstage.SetRequestUpdate();			
			return true;
		}
		if( w == alp_PIN )
		{
			string pin = alp_PIN.GetText();
			
			if ( pin.Length() > 4 )
			{
				pin = pin.Substring(0,4);
				alp_PIN.SetText( pin );				
			}
			VerifyUserInput( alp_PIN );
			return true;
		}		
		if( w == alp_NEWPIN )
		{
			string newpin = alp_NEWPIN.GetText();

			if ( newpin.Length() > 4 )
			{
				newpin = newpin.Substring(0,4);
				alp_NEWPIN.SetText( newpin );				
			}
			VerifyUserInput( alp_NEWPIN );
			return true;
		}	
		if( w == alp_NEWPIN2 )
		{
			string newpin2 = alp_NEWPIN2.GetText();
			
			if ( newpin2.Length() > 4 )
			{
				newpin2 = newpin2.Substring(0,4);
				alp_NEWPIN2.SetText( newpin2 );				
			}
			VerifyUserInput( alp_NEWPIN2 );
			return true;
		}					
		return false;

	}
	
	
	void VerifyUserInput(EditBoxWidget editbox )
	{
		private array<string> allowed = {"0","1","2","3","4","5","6","7","8","9"};
		
		int len = editbox.GetText().Length();
		string textInput = editbox.GetText();
		string textOut;
		for (int i = 0; i < len; i++;)
		{
			if ( allowed.Find( textInput.Get(i) ) != -1 )
			{
				textOut += textInput.Get(i);							
			}	
		}
		
		editbox.SetText( textOut );
	}
	
		
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (!super.OnClick(w, x, y, button))
		{
			if ( alp_CardsList == w )
			{//card list
				alp_SelectedCard = alp_CardsList.GetSelectedRow();
				alp_ATMstage.SetRequestUpdate();
				return true;
			}		
			switch (w.GetUserID())
			{
				case 1://login menu
				{
					alp_ATMstage.SetStage( alpATM_STAGE.LOGIN );
					return true;
				}
				case 2://login menu, confirm
				{
					if ( !alp_IsLogged || alp_IsChangingPswd )
					{
						VerifyLogin();
					}
					else
					{
						alp_ATMstage.SetStage( alpATM_STAGE.CURRENCY );
					}
					return true;
				}			
				case 3://login menu, change psw
				{
					alp_IsChangingPswd = !alp_IsChangingPswd;
					alp_ATMstage.SetRequestUpdate();
					return true;
				}	
				case 4://login menu, logout
				{
					Close();
					return true;
				}							
				case 20://curreny menu
				{
					alp_ATMstage.SetStage( alpATM_STAGE.CURRENCY );
					return true;
				}	
				case 21://curreny menu
				{
					alp_CurrencyType = alp_Currency.GetCurrentItem();
					alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT ); 
					return true;
				}					
				case 30://account menu
				{
					alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT );
					return true;
				}	
				case 31://account menu, confirm
				{
					MakeUserTransaction();
					return true;
				}								
				case 32://account menu, back
				{
					alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT, 0 );
					alp_ATMstage.SetRequestUpdate();				
					return true;
				}							
				case 35://account menu,withdraw
				{					
					TextWidget.Cast( layoutRoot.FindAnyWidget( "AccountTransactionTitle" )).SetText( "#alp_atm_withdraw" );
					alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT, 1 );
					alp_ATMstage.SetRequestUpdate();
					return true;
				}								
				case 36://account menu, deposit
				{
					TextWidget.Cast( layoutRoot.FindAnyWidget( "AccountTransactionTitle" )).SetText( "#alp_atm_deposit" );
					alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT, 2 );
					alp_ATMstage.SetRequestUpdate();				
					return true;
				}					
				case 37://account menu, take loan
				{
					alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT, 3);
					alp_ATMstage.SetRequestUpdate();				
					return true;
				}					
				case 38://account menu, pay loan
				{
					alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT, 4 );
					alp_ATMstage.SetRequestUpdate();				
					return true;
				}					
				case 39://account menu, exchange
				{
					alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT, 5 );
					alp_ATMstage.SetRequestUpdate();				
					return true;
				}	
				case 40://account menu, cards
				{
					alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT, 6 );
					alp_ATMstage.SetRequestUpdate();				
					return true;
				}	
				case 70://account menu, loans, XComboBoxWidget
				{
					//alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT, 3 );
					alp_ATMstage.SetRequestUpdate();				
					return true;
				}	
				case 90://account menu, exchange, XComboBoxWidget
				{
					//alp_ATMstage.SetStage( alpATM_STAGE.ACCOUNT, 3 );
					alp_ATMstage.SetRequestUpdate();				
					return true;
				}																
			}
	
			return false;
		}
		return true;
	}
	


	void MakeUserTransaction()
	{
		int type = alp_ATMstage.GetType();
		
		
		int inputValue = alp_UserInput.GetText().ToInt();
		
		switch (type)
		{
			case 1://withdraw
			{
				
				GetND().GetMS().GetTrader().CashTranscation( alp_AccountID, alp_CurrencyType, -1 * inputValue, alp_Player );				
				
				break;
			}
			case 2://deposit
			{
				GetND().GetMS().GetTrader().CashTranscation( alp_AccountID, alp_CurrencyType,inputValue, alp_Player );		
				break;
			}		
			case 3://take loan
			{
				int length = XComboBoxWidget.Cast( layoutRoot.FindAnyWidget( "LoanLength" ) ).GetCurrentItem();
				int interest = alp_LoanTotal - inputValue;
				GetND().GetMS().GetTrader().TakeLoan( alp_AccountID, alp_CurrencyType,inputValue,interest,alp_LoanInterest,length, alp_Player );		
				break;
			}	
			case 4://repay loan
			{
				GetND().GetMS().GetTrader().PartialLoanRepayment( alp_AccountID, alp_CurrencyType,inputValue, alp_Player );		
				break;
			}	
			case 5://exchange
			{
				int selectedCurrency = alp_CurrencyExchange.GetCurrentItem();
				GetND().GetMS().GetTrader().Exchange( alp_AccountID, alp_CurrencyType, selectedCurrency, alp_ExchangeCost, inputValue, alp_Player );		
				break;
			}			
			case 6://block card
			{				
				alpBankAccount account = alpBANK.GetClientAccount();			
				GetND().GetMS().GetTrader().BlockCard( alp_AccountID, account.RegisteredCards.Get(alp_SelectedCard), alp_Player );
				alp_SelectedCard = -1;
				break;
			}				
										
		}
	
	}
}
