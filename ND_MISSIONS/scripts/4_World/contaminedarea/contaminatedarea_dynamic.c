modded class EffectArea : House
{
	void OnCreateALP()
	{}
}


// The dynamic Contaminated area, using it's own default settings
modded class ContaminatedArea_Dynamic : EffectArea
{
	/*
	const int 				AIRBORNE_EXPLOSION_DELAY 	= 5;
	const int 				AREA_SETUP_DELAY 			= 10;
	const float 			AIRBORNE_FX_OFFSET 			= 50;
	
	*/
	const float 			ARTILLERY_SHELL_SPEED		= 250;	
	
	override void EEInit()
	{
		
		super.EEInit();
		OnCreateALP();		
	}	
	
	ref array<vector> alp_ArtilleryPositions				= {"-500.00 165.00 5231.69",
		"-500.00 300.00 9934.41",
		"10406.86 192.00 15860.00",
		"4811.75 370.00 15860.00",
		"-500.00 453.00 15860.00"};	
		
	override void OnCreateALP()
	{

		
		
		// We get the PPE index for future usage and synchronization ( we must do it here for dynamic as it is not read through file )
		if ( GetGame().IsServer() && m_PPERequesterType )
			m_PPERequesterIdx = PPERequesterBank.GetRequester( m_PPERequesterType.ToType() ).GetRequesterIDX();
		
		SetSynchDirty();
		
		// If this is the first initialization, we delay it in order to play cool effects
		if ( m_DecayState == eAreaDecayStage.INIT ) // && GetGame().IsServer() )
		{
			vector areaPos = GetPosition();
			m_OffsetPos = areaPos;
			m_OffsetPos[1] = m_OffsetPos[1] + AIRBORNE_FX_OFFSET;
			
			// play artillery sound, sent to be played for everyone on server
			array<vector> artilleryPoints =  GetND().GetMS().GetOptions().ArtilleryPositions; //GetGame().GetMission().GetWorldData().GetArtyFiringPos();
			vector closestPoint = areaPos;
			int dist = 0;
			int temp;
			int index = 0;
			for ( int i = 0; i < artilleryPoints.Count(); i++ )
			{
				temp = vector.DistanceSq( artilleryPoints.Get( i ), areaPos );
				if ( temp < dist || dist == 0 )
				{
					dist = temp;
					index = i;
				}
			}
			
			closestPoint = artilleryPoints.Get( index );
			
			// We calculate the delay depending on distance from firing position to simulate shell travel time
			float delay = vector.Distance( closestPoint, areaPos );
			delay = delay / ARTILLERY_SHELL_SPEED;
			delay += AIRBORNE_EXPLOSION_DELAY; // We add the base, minimum time ( no area can start before this delay )
			
			Param3<vector, vector, float> pos; // The value to be sent through RPC
			array<ref Param> params; // The RPC params
			
			// We prepare to send the message
			pos = new Param3<vector, vector, float>( closestPoint, areaPos, delay );
			params = new array<ref Param>;
			
			// We send the message with this set of coords
			params.Insert( pos );
			GetGame().RPC( null, ERPCs.RPC_SOUND_ARTILLERY_SINGLE, params, true );
			
			m_FXTimer = new Timer( CALL_CATEGORY_GAMEPLAY );
			m_FXTimer.Run( delay, this, "PlayFX" );	
			
			delay += AREA_SETUP_DELAY; // We have an additional delay between shell detonation and finalization of area creation
			
			//Print("Delay " + delay);
			// setup zone
			m_StartupTimer = new Timer( CALL_CATEGORY_GAMEPLAY );
			m_StartupTimer.Run( delay, this, "InitZone" );
		}
	}
	
	override void SetupZoneData( EffectAreaParams params ) 
	{
		// A lot of branching, allowing to use default values on specified params
		if ( params.m_ParamName != "" )
			m_Name = params.m_ParamName;
		if ( params.m_ParamTriggerType != "" )
			m_TriggerType = params.m_ParamTriggerType;
		
		if ( params.m_ParamRadius > 0 )
			m_Radius = params.m_ParamRadius;
		if ( params.m_ParamPosHeight > -1 )
			m_PositiveHeight = params.m_ParamPosHeight;
		if ( params.m_ParamNegHeight > -1 )
			m_NegativeHeight = params.m_ParamNegHeight;
		
		m_InnerRings = params.m_ParamInnerRings;
		if ( params.m_ParamInnerSpace > -1 )
			m_InnerSpacing = params.m_ParamInnerSpace;
		
		m_OuterRingToggle = params.m_ParamOuterToggle;
		if ( params.m_ParamOuterSpace > -1 )
			m_OuterSpacing = params.m_ParamOuterSpace;
		m_OuterRingOffset = params.m_ParamOuterOffset;
		
		if ( params.m_ParamVertLayers > 0 )
			m_VerticalLayers = params.m_ParamVertLayers;
		if ( params.m_ParamVerticalOffset > 0 )
			m_VerticalOffset = params.m_ParamVerticalOffset;
		
		m_ParticleID = params.m_ParamPartId;
		m_AroundParticleID = params.m_ParamAroundPartId;
		m_TinyParticleID = params.m_ParamTinyPartId;
		
		if ( params.m_ParamPpeRequesterType != "" ){
			m_PPERequesterType = params.m_ParamPpeRequesterType;
			m_PPERequesterIdx = GetRequesterIndex(m_PPERequesterType);	
		}
			
		
		// We get the PPE index for future usage and synchronization
		
		
		// DEVELOPER NOTE :
		// If you cannot register a new requester, add your own indexation and lookup methods to get an index and synchronize it
		// EXAMPLE : m_PPERequesterIdx = MyLookupMethod()
		
		// We sync our data
		SetSynchDirty();
		
		// Now that everything is ready, we finalize setup
		//InitZone();
	}	

}