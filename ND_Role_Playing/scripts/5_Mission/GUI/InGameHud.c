
modded class IngameHud extends Hud
{


	override void Init( Widget hud_panel_widget )
 	{ 
		
  		super.Init(hud_panel_widget );
		//if ( GetNextDays().GetOptions() && GetNextDays().GetOptions().GetRP().EnableFatigue  )
		//{		
			
			Widget notPanel = Widget.Cast( hud_panel_widget.FindAnyWidget("NotifiersPanel") );
			notPanel.Unlink();
			Widget newNot 	= GetGame().GetWorkspace().CreateWidgets("ND_Role_Playing/gui/layouts/fatigue.layout",hud_panel_widget);
			
			m_Notifiers						= hud_panel_widget.FindAnyWidget("NotifiersPanel");		
			m_BloodType						= TextWidget.Cast( hud_panel_widget.FindAnyWidget("BloodType") );
			m_BloodPosType					= TextWidget.Cast( hud_panel_widget.FindAnyWidget("BloodPosType") );		
			
			m_HeatBufferPlus = ImageWidget.Cast( m_HudPanelWidget.FindAnyWidget( "HeatBuffer" ) );
			if ( m_HeatBufferPlus )
				m_HeatBufferPlus.Show( false );
	
	
			//move divider
			float x1,y1;	
			Widget badgeSpacer = Widget.Cast( hud_panel_widget.FindAnyWidget("BadgesSpacer") );
			badgeSpacer.GetPos(x1,y1);
			x1+=35;
			badgeSpacer.SetPos(x1,y1);
			
			//move badges
			m_Badges.GetPos(x1,y1);	
			x1+=35;//43
			m_Badges.SetPos(x1,y1);		
			
			int i = 0;
			int key = 0;
					
			//------------------------------------------------------------------------------------------------------ 				
	
			//state notifiers	
				
			m_StatesWidgetNames.Clear();
			m_StatesWidgets.Clear();
			m_StatesWidgetNames.Set( NTFKEY_THIRSTY, "Thirsty" );
			m_StatesWidgetNames.Set( NTFKEY_HUNGRY, "Hungry" );
			m_StatesWidgetNames.Set( NTFKEY_SICK, "Health" );
			m_StatesWidgetNames.Set( NTFKEY_BLEEDISH, "Blood" );
			m_StatesWidgetNames.Set( NTFKEY_FEVERISH, "Temperature" );		
			
			//added
			m_StatesWidgetNames.Set( NTFKEY_ALPTIREDNESS, "Tiredness" );		
			//added end
			
			for ( i = 0; i < m_StatesWidgetNames.Count(); i++ )
				{
					string widget_name = m_StatesWidgetNames.GetElement(i);
					key = m_StatesWidgetNames.GetKey(i);
					ImageWidget w;
					Class.CastTo(w,  m_Notifiers.FindAnyWidget( String( "Icon" + widget_name ) ) );
				
					
				
					if (w)
					{
					
						m_StatesWidgets.Set( key, w );
						w.Show( true );
						for ( int y = 0; y < 5; y++ )
						{
							if ( key == NTFKEY_ALPTIREDNESS )
								w.LoadImageFile( y, "set:nd_dayz_gui image:icon" + widget_name + y );
							else
								w.LoadImageFile( y, "set:dayz_gui image:icon" + widget_name + y );
						}
						// clear all arrows
						for ( int x = 1; x < 4; x++ )
						{
							Class.CastTo(w,  m_Notifiers.FindAnyWidget( String( widget_name + "ArrowUp" + x.ToString() ) ) );
							w.Show( false );
							Class.CastTo(w,  m_Notifiers.FindAnyWidget( String( widget_name + "ArrowDown" + x.ToString() ) ) );
							w.Show( false );
						}
					}
					
				}
			
		
		//}
 	}	

}

