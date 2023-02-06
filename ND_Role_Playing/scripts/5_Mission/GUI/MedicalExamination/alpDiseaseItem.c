enum alpDISEASEITEMTYPE
{
	HEADER,
	ITEM
}

class alpDiseaseItem
{
	WrapSpacerWidget alp_Parent;
	ref Widget alp_Main;
	ImageWidget alp_Icon;	

	TextWidget alp_NameText;
	
	TextWidget alp_ExamineText;
	
	TextWidget alp_PriceText;
	
	ButtonWidget alp_Heal;
	
	Widget alp_HeaderPanel;

	
	float alp_Price;
	
	bool alp_State;
	
	Widget alp_Root;
	
	bool alp_CanBeCured;
	
	void alpDiseaseItem(int type, string img, WrapSpacerWidget w, string name, bool state, float price, bool canBeCured = true)
	{

		alp_Parent = w;
		alp_CanBeCured = canBeCured;
		
		alp_Root = GetGame().GetWorkspace().CreateWidgets( "ND_Role_Playing/gui/layouts/Disease.layout" ,w);	
		
		
		alp_Main = Widget.Cast( alp_Root.FindAnyWidget("Disease_panel") );
		alp_Icon = ImageWidget.Cast( alp_Root.FindAnyWidget("Disease_icon") );
		alp_NameText = TextWidget.Cast( alp_Root.FindAnyWidget("Disease_text") );		
		alp_ExamineText = TextWidget.Cast( alp_Root.FindAnyWidget("Examination_text") );
		alp_PriceText = TextWidget.Cast( alp_Root.FindAnyWidget("Price_text") );		
		alp_Heal = ButtonWidget.Cast( alp_Root.FindAnyWidget("ButtonPlus") );
		alp_HeaderPanel = Widget.Cast( alp_Root.FindAnyWidget("HeadTitlePanel") );
		
		
		if (type == alpDISEASEITEMTYPE.ITEM)
		{
		
			
			
			alp_Icon.LoadImageFile(0,img);
			
			

			alp_NameText.SetText( name );
			
			alp_Heal = ButtonWidget.Cast( alp_Root.FindAnyWidget("ButtonPlus") );
			
			SetPrice( price );
			
			SetState(state);			
		
		}
		
		if (type == alpDISEASEITEMTYPE.HEADER)
		{
					
			alp_Icon.Show(false);
			
			alp_NameText.Show(false);
			
			alp_HeaderPanel.Show(true);

			
			
			
			//SetPrice( price );
			
			//SetState(state);			
		
		}		
		
		

		
		
		
		
	}
	Widget GetRoot()
	{
		return alp_Root;
	}		
	
	Widget GetWidget()
	{
		return alp_Main;
	}	

	void SetPrice(float value)
	{
		alp_Price = value;
		
		if ( alp_Price == 0 )
		{
			alp_PriceText.Show(false);
		}
		else
		{
			alp_PriceText.Show(true);
			alp_PriceText.SetText( alpUF.NumberToString(alp_Price,1)  );
		}
		
	}	
	
	float GetFee()
	{
		return alp_Price;
	}
	
	void SetState(bool state)
	{
		alp_State = state;
		
		if (state)
		{
			alp_ExamineText.SetText("#me_disease_pozitive");
			alp_ExamineText.SetColor( COLOR_RED );
			if (alp_CanBeCured)
			{
				alp_Heal.Show(true);
			}
			else
			{
				alp_Heal.Show(false);
			}
		}
		else
		{
		
			alp_ExamineText.SetText("#me_disease_negative");
			alp_ExamineText.SetColor( ARGB(255,255,255,255) );
			alp_Heal.Show(false);
		}
		
		
	}		
	
	
		
	void SetValue(float value)
	{
		//alp_Value = value;
		
		//alp_Bar.SetCurrent( value );
	}
	

	ButtonWidget GetButton()
	{
		return 	alp_Heal;
	}

	
}