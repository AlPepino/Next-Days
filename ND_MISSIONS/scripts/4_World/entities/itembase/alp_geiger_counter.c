// Script File
enum alpGEIGERSOUNTYPE
{
	NONE = 0,
	LOW,
	MEDIUM,
	HIGH,
	VERYHIGH,
	COUNT,
}


class alpGeigerSound
{
	static string GetSoundSetByType( alpGEIGERSOUNTYPE ide )
	{
		string soundset = "alp_Geiger_SoundSet_low";

		switch (ide)
		{
			case alpGEIGERSOUNTYPE.LOW:
				soundset = "alp_Geiger_SoundSet_low";
				break;
			case alpGEIGERSOUNTYPE.MEDIUM:
				soundset = "alp_Geiger_SoundSet_medium";
				break;		
			case alpGEIGERSOUNTYPE.HIGH:
				soundset = "alp_Geiger_SoundSet_high";
				break;
			case alpGEIGERSOUNTYPE.VERYHIGH:
				soundset = "alp_Geiger_SoundSet_veryhigh";
				break;			
		}
		return soundset;
	} 
	
	static int GetSoundTypeValue( float radiation )
	{
		if ( radiation == 0 )
			return alpGEIGERSOUNTYPE.NONE;
		
		if ( radiation <= GetND().GetMS().GetOptionsRadiation().GeigerSoundEffect_Radiation_Low )
			return alpGEIGERSOUNTYPE.LOW;

		if ( radiation <= GetND().GetMS().GetOptionsRadiation().GeigerSoundEffect_Radiation_Medium )
			return alpGEIGERSOUNTYPE.MEDIUM;				

		if ( radiation <= GetND().GetMS().GetOptionsRadiation().GeigerSoundEffect_Radiation_High )
			return alpGEIGERSOUNTYPE.HIGH;	
								
		return alpGEIGERSOUNTYPE.VERYHIGH;
	}
	
	static int GetColorByType( alpGEIGERSOUNTYPE ide )
	{
		int color = COLOR_GREEN;

		switch (ide)
		{
			case alpGEIGERSOUNTYPE.LOW:
				color = FadeColors.WHITE;
				break;
			case alpGEIGERSOUNTYPE.MEDIUM:
				color = COLOR_YELLOW;
				break;		
			case alpGEIGERSOUNTYPE.HIGH:
				color = COLOR_RED;
				break;
			case alpGEIGERSOUNTYPE.VERYHIGH:
				color = COLOR_RED;
				break;				
		}
		return color;
	
	}
	
	static int GetMaxDialValue()
	{
		int value = GetND().GetMS().GetOptionsRadiation().GeigerSoundEffect_Radiation_High;
		
		value *= 1.25;
		
		return value;
	}
}


class alp_geiger_counter extends ItemBase
{
	float						alp_Radiation;
	
	
	int							alp_SoundLoopType;
	int							alp_SoundLoopTypeLast = alpGEIGERSOUNTYPE.NONE;
	
	static const string			START_SOUND 				= "alp_Geiger_SoundSet_Switch";
	
	static const string			STOP_SOUND 					= "alp_Geiger_SoundSet_Switch";
	static const string 		BATTERY_ATTACH_SOUND 		= "alp_Geiger_SoundSet_Switch";
	static const string 		BATTERY_DETACH_SOUND 		= "alp_Geiger_SoundSet_Switch";
	
	
	
	
	protected EffectSound 		m_EngineLoop;
	protected EffectSound 		m_EngineStart;
	protected EffectSound 		m_EngineStop;

	
	ItemBase					m_Battery; // Attached battery9v

	bool						m_Working;

	ref Timer 					m_SoundLoopStartTimer;
	
	
	void alp_geiger_counter()
	{	
		RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
		
		RegisterNetSyncVariableInt("alp_SoundLoopType",0,alpGEIGERSOUNTYPE.COUNT);
	}
	

	override void OnInitEnergy()
	{
		super.OnInitEnergy();

	}
	override void OnWorkStart()
	{

			PlayerBase player;		
			if ( Class.CastTo( player, GetHierarchyRootPlayer()) )
			{
				
				player.GetRP().SetGeigerCounter( this );	
			
				if ( GetGame().IsServer() )
				{
					alp_SoundLoopType = alpGeigerSound.GetSoundTypeValue(  player.GetRP().GetRadiation() );  	

				}		
			}
		
		if ( GetGame().IsClient()  ||  !GetGame().IsMultiplayer() )
		{
			PlaySoundSet( m_EngineStart, START_SOUND, 0, 0 );
			
			
			if (!m_SoundLoopStartTimer) 
				m_SoundLoopStartTimer = new Timer( CALL_CATEGORY_GAMEPLAY );			
			
			CheckRadiationZone();	
			m_SoundLoopStartTimer.Run(1, this, "CheckRadiationZone", NULL, true);	
									
			
		}
		
		m_Working = true;
	}
	
	private void CheckRadiationZone()
	{

		if ( alp_SoundLoopType > alpGEIGERSOUNTYPE.NONE )
		{

			
			if ( alp_SoundLoopTypeLast != alp_SoundLoopType )
			{
				alp_SoundLoopTypeLast = alp_SoundLoopType;
				
				string soundset = alpGeigerSound.GetSoundSetByType( alp_SoundLoopType );
				
				if (m_EngineLoop && m_EngineLoop.IsSoundPlaying() )	
				{
					m_EngineLoop.SoundStop();		
					m_EngineLoop = NULL;
				}
							
				PlaySoundSet( m_EngineLoop, soundset , 0,0, true);		 
			
				
			}
		}
		else
		{	
				
			if (m_EngineLoop && m_EngineLoop.IsSoundPlaying() )	
			{
				m_EngineLoop.SoundStop();		
				alp_SoundLoopTypeLast = alpGEIGERSOUNTYPE.NONE; 
			}
		}
		

	}
	
	
	override void OnWork( float consumed_energy )
	{	
		PlayerBase player;		
		if ( Class.CastTo( player, GetHierarchyRootPlayer()) )
		{
			//if ( GetGame().IsClient() )
			//{
				player.GetRP().SetGeigerCounter( this );		
			//}
			
			if ( GetGame().IsServer() )
			{
				
				alp_SoundLoopType = alpGeigerSound.GetSoundTypeValue(  player.GetRP().GetRadiation() );  
				
				if ( alp_SoundLoopTypeLast != alp_SoundLoopType )
				{
					alp_SoundLoopTypeLast = alp_SoundLoopType;
					SetSynchDirty();
				}
			}			
		}	
		
		
	
	}	
	
	override void OnWorkStop()
	{
		super.OnWorkStop();
		if ( GetGame().IsClient()  ||  !GetGame().IsMultiplayer() )
		{
			m_SoundLoopStartTimer.Stop();	
				
			if (m_EngineLoop)
			{
				alp_SoundLoopTypeLast = alpGEIGERSOUNTYPE.NONE; 
				
				if (m_EngineLoop.IsSoundPlaying()) 
					m_EngineLoop.SoundStop();
			}
			PlaySoundSet( m_EngineStop, STOP_SOUND, 0, 0 );
			

		}
		if ( GetGame().IsServer() )
		{
			alp_SoundLoopType = alpGEIGERSOUNTYPE.NONE;  		
		}		
		
		m_Working = false;
	}

	override void EEItemAttached ( EntityAI item, string slot_name )
	{
		super.EEItemAttached ( item, slot_name );
		
		ItemBase item_IB = ItemBase.Cast( item );
		
		if ( item_IB.IsKindOf("Battery9V") )
		{
			m_Battery = item_IB;
			if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
			{
				
				SEffectManager.PlaySound(BATTERY_ATTACH_SOUND, GetPosition() );
			}
		}
	}
	
	
	override void EEItemDetached ( EntityAI item, string slot_name )
	{
		super.EEItemDetached ( item, slot_name );
		
		ItemBase item_IB = ItemBase.Cast( item );
		
		if ( item_IB.IsKindOf("Battery9V") )
		{
			m_Battery = NULL;
			
			if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
			{
				SEffectManager.PlaySound(BATTERY_DETACH_SOUND, GetPosition() );
			}
		}
	}	

	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
	}
}
