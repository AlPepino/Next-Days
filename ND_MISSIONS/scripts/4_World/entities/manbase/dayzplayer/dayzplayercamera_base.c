modded class DayZPlayerCameraBase extends DayZPlayerCamera
{
	int last_Radiation;
	
		
	int GetRaditaionLevel()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player)
		{	
			int radiation =   alpGeigerSound.GetSoundTypeValue( player.GetRP().GetRadiation() );
			
			return radiation;
			
		}
		return alpGEIGERSOUNTYPE.NONE;	
	}
	
	
	
	int ALP_GOOGLES = 1;
	int ALP_OPTICS = 2;
	int ALP_OPTICS_DAY = 3;
	
	bool IsNVvision(int type)
	{
		int nv;
		if ( type == NVTypes.NV_GOGGLES  )
		{
			nv = GetNV_ID( ALP_GOOGLES );
			PPERequesterBank.GetRequester(PPERequesterBank.REQ_CAMERANV).Start( new Param1<int>(nv) );
			GetGame().GetMission().GetEffectWidgets().AddActiveEffects({EffectWidgetsTypes.NVG_OCCLUDER});
			GetGame().GetMission().GetEffectWidgets().RemoveActiveEffects({EffectWidgetsTypes.PUMPKIN_OCCLUDER});				
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdateCameraNVALP,1000,false,PlayerBase.Cast(m_pPlayer) );
			return true;
		}
		
		if ( type == NVTypes.NV_OPTICS_KAZUAR_NIGHT || type == NVTypes.NV_OPTICS_STARLIGHT_NIGHT  || type == NVTypes.NV_OPTICS_ON  )
		{
			nv = GetNV_ID( ALP_OPTICS );
			PPERequesterBank.GetRequester(PPERequesterBank.REQ_CAMERANV).Start( new Param1<int>(nv) );
			GetGame().GetMission().GetEffectWidgets().RemoveActiveEffects({EffectWidgetsTypes.NVG_OCCLUDER});
			GetGame().GetMission().GetEffectWidgets().RemoveActiveEffects({EffectWidgetsTypes.PUMPKIN_OCCLUDER});			
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdateCameraNVALP,1000,false,PlayerBase.Cast(m_pPlayer) );
			return true;	
		}		
		
		if ( type == NVTypes.NV_OPTICS_KAZUAR_DAY || type == NVTypes.NV_OPTICS_STARLIGHT_DAY  )
		{
			nv = GetNV_ID( ALP_OPTICS_DAY );
			PPERequesterBank.GetRequester(PPERequesterBank.REQ_CAMERANV).Start( new Param1<int>(nv) );
			GetGame().GetMission().GetEffectWidgets().RemoveActiveEffects({EffectWidgetsTypes.NVG_OCCLUDER});
			GetGame().GetMission().GetEffectWidgets().RemoveActiveEffects({EffectWidgetsTypes.PUMPKIN_OCCLUDER});			
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdateCameraNVALP,1000,false,PlayerBase.Cast(m_pPlayer) );	
			return true;			
		}		
		
		return false;
	}
	
	
	override void SetNVPostprocess(int NVtype)
	{

		if ( !GetND().GetMS().GetOptionsRadiation().RadiationAffectsNVG || !IsNVvision(NVtype) )
		{
			super.SetNVPostprocess( NVtype );
			return;
		}		

		
		if (PlayerBaseClient.Cast(m_pPlayer))
		{
			PlayerBaseClient.Cast(m_pPlayer).SwitchPersonalLight(NVtype < 1); //TODO 
		}
	}
	

	
	int GetNV_ID(int type)
	{
		
		if (type == ALP_OPTICS)
		{
			switch (last_Radiation)
			{
				case alpGEIGERSOUNTYPE.NONE:
					return PPERequester_CameraNV.NV_DEFAULT_OPTICS;				
				case alpGEIGERSOUNTYPE.LOW:
					return PPERequester_CameraNV.NV_DEFAULT_OPTICS_RAD_LOW;
				case alpGEIGERSOUNTYPE.MEDIUM:
					return PPERequester_CameraNV.NV_DEFAULT_OPTICS_RAD_MEDIUM;
				case alpGEIGERSOUNTYPE.HIGH:
					return PPERequester_CameraNV.NV_DEFAULT_OPTICS_RAD_HIGH;
				case alpGEIGERSOUNTYPE.VERYHIGH:
					return PPERequester_CameraNV.NV_DEFAULT_OPTICS_RAD_VERYHIGH;
			}					
		}
		else if (type == ALP_GOOGLES)
		{
			switch (last_Radiation)
			{
				case alpGEIGERSOUNTYPE.NONE:
					return PPERequester_CameraNV.NV_DEFAULT_GLASSES;						
				case alpGEIGERSOUNTYPE.LOW:
					return PPERequester_CameraNV.NV_DEFAULT_GLASSES_RAD_LOW;
				case alpGEIGERSOUNTYPE.MEDIUM:
					return PPERequester_CameraNV.NV_DEFAULT_GLASSES_RAD_MEDIUM;
				case alpGEIGERSOUNTYPE.HIGH:
					return PPERequester_CameraNV.NV_DEFAULT_GLASSES_RAD_HIGH;
				case alpGEIGERSOUNTYPE.VERYHIGH:
					return PPERequester_CameraNV.NV_DEFAULT_GLASSES_RAD_VERYHIGH;
			}					
		}
		else
		{
			switch (last_Radiation)
			{
				case alpGEIGERSOUNTYPE.NONE:
					return PPERequester_CameraNV.NV_DAYTIME_OPTICS;					
				case alpGEIGERSOUNTYPE.LOW:
					return PPERequester_CameraNV.NV_DAYTIME_RAD_LOW;
				case alpGEIGERSOUNTYPE.MEDIUM:
					return PPERequester_CameraNV.NV_DAYTIME_RAD_MEDIUM;
				case alpGEIGERSOUNTYPE.HIGH:
					return PPERequester_CameraNV.NV_DAYTIME_RAD_HIGH;
				case alpGEIGERSOUNTYPE.VERYHIGH:
					return PPERequester_CameraNV.NV_DAYTIME_RAD_VERYHIGH;
			}			
		
		}
		return type;
	}
		

	void UpdateCameraNVALP(PlayerBase player)
	{
		
		if ( !player )
			return;
		
		if ( player.IsNVGWorking() && IsCameraNV() )
		{
			int level = GetRaditaionLevel(); 
			
			if (level != last_Radiation)
			{	
				last_Radiation = level;					
				SetNVPostprocess( GetCameraNVType() );								
			}			
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.UpdateCameraNVALP,1000,false,PlayerBase.Cast(m_pPlayer) );
		}		
		
	}	

		
}

