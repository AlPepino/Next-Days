// Script File

//template for recieved messages
class alpMessage 
{
	float 	Time;
	string 	Message 	= "";
	int 	Type 		= 0;
	int  	Length;
	vector 	Position;
	
	void alpMessage(int type,string message, vector pos)
	{
		Time = GetND().GetNotf().GetOptions().MessageDisplayedMinimalFor;
		
		Position = pos;
		
		Message = message;
		Type	= type;
		
		//every 10 char + 1s
		Length 	= Message.Length();
		float c;
		c		=  Length / 10;		
		Time 	+= c * GetND().GetNotf().GetOptions().MessageProlong;		
	}
}

class alpMessagesCollector 
{
	int													alp_MessageCounter;
		
	WrapSpacerWidget									alp_Collector;
	
	ref array< ref alpMessage> 							alp_Messages;
	
	//PlayerBase											alp_Player;
	Widget 												alp_Parent;
	
	void alpMessagesCollector(Widget parent )
	{
		alp_MessageCounter = 0;
		
		alp_Parent 	= parent;
		
		alp_Messages	= new array< ref alpMessage>;
	
		

	}
	
	
	void InitMessageCollector()
	{
		if ( !alp_Collector )
		{
			int align = GetND().GetNotf().GetOptions().NotificationAlign;
			Widget messageWindow;
			//Print(" NOTOFIKACE " +  align );
			switch ( align )
			{
				case 1:
					messageWindow = GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/nd_notf_center.layout" ); 
					break;
				case 2:
					messageWindow = GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/nd_notf_right.layout" ); 
					break;			
				default:
					messageWindow = GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/nd_notf.layout" ); 						
					
			}			
			alp_Collector = WrapSpacerWidget.Cast(messageWindow.FindAnyWidget("ServerMessagesWindow"));
			
			alp_Parent.GetParent().AddChild(alp_Collector);
		}
		
	
	}
	
	
	void AddMessage( alpMessage message )
	{
		alp_Messages.Insert( message );
	}
	
	
	void Update(float timeslice)
	{
		if ( alp_Messages.Count() > 0 && GetCountShownMessages() < GetND().GetNotf().GetOptions().ShownMessagesAtOnce )
		{
			InitMessageCollector();
			ShowMessage();
		}
	}
	
	int GetCountShownMessages()
	{	
	
		return alp_MessageCounter;
	}
	
	void ShowMessage()
	{
		int count = GetND().GetNotf().GetOptions().ShownMessagesAtOnce - GetCountShownMessages();
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		for (int i = 0 ; i < count; i++)
		{
			if ( alp_Messages && alp_Messages.Count() > 0 )
			{
				alpMessage message = alp_Messages.Get(0);

				if ( message.Type > ALPMSTYPE.SMEND )
				{
					int nav = player.GetRP().HasWalkieTalkie();
					if (player && player.GetRP() && ( nav & alpRADIO.ALLOWED_BY_CONFIG_PERSONAL || nav & alpRADIO.ALLOWED_BY_CONFIG_FIELD || nav & alpRADIO.HAS_WALKIE_TALKIE || nav & alpRADIO.HAS_BASE_RADIO)  )
					{						
						EffectSound sound;
						player.PlaySoundSet( sound , "turnOnRadioNoise_SoundSet", 0, 0 );
						alp_Collector.AddChild( GetMessagePanel(message) );	
					}
				
				}
				else
				{
					alp_Collector.AddChild( GetMessagePanel(message) );
				}
				
				
				alp_Messages.Remove( 0 );
				
				alp_MessageCounter++;
			}
			else
			{
				break;
			}
		}
	
	}
	
	WrapSpacerWidget GetMessagePanel(alpMessage message)
	{
		Widget messageWindow = GetGame().GetWorkspace().CreateWidgets( "ND_MISSIONS/gui/layouts/nd_notf_message.layout" );
	
		WrapSpacerWidget messagepanel			= WrapSpacerWidget.Cast(messageWindow.FindAnyWidget("ServerMessagesPanel"));	
		
		RichTextWidget text =  RichTextWidget.Cast( messagepanel.FindAnyWidget("ServerMessages"));
		text.SetText( GetText(message) );		
		
		ImageWidget icon = ImageWidget.Cast( messagepanel.FindAnyWidget("ServerMessagesIcon"));
		icon.LoadImageFile( 0,ALPMSICON.Get( message.Type ) ); 
		icon.SetColor( ALPMSCOLOR.Get( message.Type ));	
		
		//promotions
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		EffectSound sound;				
		if ( message.Type == ALPMSTYPE.SMLEVELUP )
		{
			player.PlaySoundSet( sound , "alp_LevelUp_SoundSet", 0, 0 );
		}
		if ( message.Type == ALPMSTYPE.SMLEVELDOWN )
		{
			player.PlaySoundSet( sound , "alp_LevelDown_SoundSet", 0, 0 );
		}
		
								
		int time = message.Time * 1000;
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.Hide,time,false,messagepanel);
		
		return messagepanel;
	}

	
	void Hide(WrapSpacerWidget panel)
	{
		panel.Unlink();
		alp_MessageCounter--;
	}
	
	string GetText(alpMessage message)
	{
		string text = message.Message;

		text.Replace("#pos", GetND().GetNotf().GetLocationsLabels().GetLocation( message.Position ) );

		
		return text;	
	}
}

