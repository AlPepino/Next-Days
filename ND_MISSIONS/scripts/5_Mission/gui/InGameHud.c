
modded class IngameHud extends Hud
{
	//NOTIFICIATION
	ref alpMessagesCollector							alp_MessagesCollector;

	//RADIATION
	ref array<int> DOSESMAX = { ALP_RADPOISON.L1, ALP_RADPOISON.L2,ALP_RADPOISON.L3,ALP_RADPOISON.L4};
	ref array<int> COLORRAD = {FadeColors.WHITE, COLOR_YELLOW, ARGB(255,255,90,0), COLOR_RED };	
	
	float												alp_Tick;
	
	float												alp_LastRadiation;
	float												alp_LastRadiationDoses;
	float												alp_LastRadiationShield;
	
	bool												alp_HasDosimeter;
	bool												alp_HasGeiger;
	
	
	ref Widget											alp_GeigerPanel;
	ref Widget											alp_GeigerDisplay;
	ref TextWidget										alp_GeigerValue;
	ref ImageWidget 									alp_GeigerPointer;
	
	ref Widget											alp_ShieldPanel;
	ref TextWidget										alp_ShieldValue;	
	ref ImageWidget 									alp_RadiationShield;	
	
	ref Widget											alp_DosimeterPanel;	
	ref TextWidget										alp_DosesValue;	
	ref TextWidget										alp_DosesUnit;	
	ref ImageWidget 									alp_DosesIcon;
	
	ref Widget											alp_ShieldPanelChemical;
	ref TextWidget										alp_ShieldValueChemical;	
	ref ImageWidget 									alp_ChemicalShield;	





	override void Init( Widget hud_panel_widget )
 	{ 
		
  		super.Init(hud_panel_widget );
		//NOTIFICIATION
		InitNotification(hud_panel_widget);		

		//RADIATION
		WrapSpacerWidget leftHud = WrapSpacerWidget.Cast( hud_panel_widget.FindAnyWidget( "LeftHUDPanel" ) );
		
		Widget radPanel	= GetGame().GetWorkspace().CreateWidgets("ND_MISSIONS/gui/layouts/radiation.layout",leftHud);
		
		
		alp_GeigerPointer = ImageWidget.Cast( radPanel.FindAnyWidget("GeigerPointer") );
		alp_GeigerValue	= TextWidget.Cast(radPanel.FindAnyWidget("GeigerValue"));	
		alp_GeigerPanel = Widget.Cast(radPanel.FindAnyWidget("GeigerPanel"));
		alp_GeigerPanel.Show(false);
		
		alp_DosimeterPanel 	= Widget.Cast(radPanel.FindAnyWidget("DosesPanel"));
		alp_DosesIcon 		= ImageWidget.Cast( radPanel.FindAnyWidget("DosesIcon") );
		alp_DosesValue		= TextWidget.Cast(radPanel.FindAnyWidget("DosesValue"));
		alp_DosesUnit 		= TextWidget.Cast( radPanel.FindAnyWidget("DosesUnit") );
		
		
		alp_DosimeterPanel.Show( false );
		
		alp_ShieldPanel 	= Widget.Cast(radPanel.FindAnyWidget("ShieldPanel"));
		alp_RadiationShield = ImageWidget.Cast( radPanel.FindAnyWidget("RadiationShield") );
		alp_ShieldValue		= TextWidget.Cast(radPanel.FindAnyWidget("RadiationShieldValue"));
		alp_ShieldPanel.Show( false );
		
		alp_ShieldPanelChemical 	= Widget.Cast(radPanel.FindAnyWidget("ShieldPanelChemical"));
		alp_ChemicalShield = ImageWidget.Cast( radPanel.FindAnyWidget("ChemicalShieldIcon") );
		alp_ChemicalShield.LoadImageFile(0,"ND_MISSIONS/gui/Images/ToxicShield.paa");
		
		alp_ShieldValueChemical		= TextWidget.Cast(radPanel.FindAnyWidget("ChemicalShieldValue"));
		alp_ShieldPanelChemical.Show( false );				
 	}	
	
	//NOTF
	void InitNotification(Widget hud_panel_widget)
	{	
		alp_MessagesCollector = new alpMessagesCollector(hud_panel_widget);
		
	}
	
		
	override void Update( float timeslice )
	{
		super.Update( timeslice );

		//------------------------------------------------------------------------------------------------------ 				   		
		//Messages
		alp_MessagesCollector.Update( timeslice );
		//RADIATION
		alp_Tick += timeslice;		
		if ( alp_Tick > 0.2 )
		{		
			SetRadiationPanel();
			alp_Tick = 0;	
		}		
	}	
	
	

	//------------------------------------------------------------------------------------------------------ 				   		
	//Messages		
	override void SendMessageALP(int type, string text, vector pos = "0 0 0")
	{
		if ( GetND().GetNotf().GetOptions().EnableNotification )
		{
			alp_MessagesCollector.AddMessage( new alpMessage(type, text, pos) );		
		}

	}

	//------------------------------------------------------------------------------------------------------ 				   			
	//radiation

	void SetRadiationPanel()
	{
		
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		
		if (player)
		{
			
			float shieldRadiation = player.GetRP().GetProtection().GetTotalRadiationShield();
			
			if (shieldRadiation)
			{
				alp_ShieldValue.SetText( alpUF.NumberToString(shieldRadiation * 100 , 1));	
								
				alp_RadiationShield.SetColor( GetShieldColor( shieldRadiation ) );
				
				alp_ShieldPanel.Show( true );
			}
			else
			{
				alp_ShieldPanel.Show( false );
			}

			
			float shieldChemical = player.GetRP().GetProtection().GetTotalChemicalShield();
			
			if (shieldChemical)
			{
				alp_ShieldValueChemical.SetText( alpUF.NumberToString(shieldChemical * 100 , 1));	
				
				alp_ChemicalShield.SetColor( GetShieldColor( shieldChemical ) );
				
				
				alp_ShieldPanelChemical.Show( true );
			}
			else
			{
				alp_ShieldPanelChemical.Show( false );
			}
			
			
			if ( player.GetRP().HasActiveGeigerCounter() || player.GetRP().HasDosimeter() )
			{
				alp_DosimeterPanel.Show( true );
				
				int doses;				
				player.GetSyncData().GetElementEnhanced( alpRPelementsEnahnced.RADIATIONDOSES ).GetValue(doses);
				
				
				alp_DosesValue.SetText( alpUF.NumberToString(  doses ,1 ) );
				
				int index = GetDosimeterMaxValueIndex(doses);
				
				if (player.GetRP().HasActiveGeigerCounter())
				{
					//geiger					
					SetRadiationPointerALP( player.GetRP().GetRadiation() );															
					alp_GeigerValue.SetText( alpUF.NumberToString( player.GetRP().GetRadiation() ) );
					alp_GeigerPanel.Show(true);				
					
					//dosimeter
					
					alp_DosesIcon.LoadImageFile(0,"set:nd_dayz_gui image:dosimeter");
					alp_DosesValue.Show(true);
					alp_DosesUnit.Show(true);
					
					
					if ( index < 4 )
					{
						
						alp_DosesIcon.SetColor( COLORRAD.Get( index ) );
					}
					else 
					{
		
						alp_DosesIcon.SetColor( COLORRAD.Get( 3 ) );
					}
					
				}
				else
				{

					alp_DosesIcon.LoadImageFile(0,"set:nd_dayz_gui image:radiation");  //GetDosimeterColor
					alp_DosesIcon.SetColor( GetDosimeterColor(  doses ) );
					alp_DosesValue.Show(false);
					alp_DosesUnit.Show(false);									
					
					alp_GeigerPanel.Show(false);
				}
				
			}
			else
			{
				alp_DosimeterPanel.Show( false );
				alp_GeigerPanel.Show(false);
			}
		
		
		}
		
		
	}
		

	private void SetRadiationPointerALP(float radiation)
	{
		int maxValue = alpGeigerSound.GetMaxDialValue() + 1; //avoiding div 0
					
		float value = radiation;
		
		value = Math.Clamp(value,0,maxValue);
		
		value = value / maxValue;
		
		alp_GeigerPointer.SetRotation( 0, 0, value * 260 - 130, true );
		
		int typeValue = alpGeigerSound.GetSoundTypeValue( radiation );
		
		int color = alpGeigerSound.GetColorByType( typeValue );
		
		alp_GeigerPointer.SetColor( color );
	}
	
	
	private int GetShieldColor( float shield)
	{
		
		int shiedColor;

		
		if (shield==0)
		{
			return 0;
		} 
		
		if ( shield < 1 )
		{
			shield *= 100;
			shiedColor = ARGB(shield*2.5,255,255,255);	
			
		}
		else
		{
			shiedColor = COLOR_GREEN;	
		}		
		
		return shiedColor;	

		
	}


	private int GetDosimeterColor( float doses )
	{

		
		if ( doses < ALP_RADPOISON.L1 )
		{
			int a = (doses/ALP_RADPOISON.L1 ) * 100 * 2.5;	
	
			return ARGB(a,255,255,255);					
		}

		if ( doses < ALP_RADPOISON.L2 )
			return COLORRAD.Get( 1 );		
		if ( doses < ALP_RADPOISON.L3 )
			return COLORRAD.Get( 2 );	
		if ( doses < ALP_RADPOISON.L4 )
			return COLORRAD.Get( 3 );				
				
		return COLORRAD.Get( 4 );	
		
	}	
		
	private int GetDosimeterMaxValueIndex(float doses)
	{		
		if ( doses < ALP_RADPOISON.L1 )
			return 0;
		if ( doses < ALP_RADPOISON.L2 )
			return 1;		
		if ( doses < ALP_RADPOISON.L3 )
			return 2;
		if ( doses < ALP_RADPOISON.L4 )
			return 3;	
		
		return 4;			
	}	
	
}
