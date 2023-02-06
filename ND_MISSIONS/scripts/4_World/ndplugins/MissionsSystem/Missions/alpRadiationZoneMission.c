//radiation mission
class alpRadiationZoneMission extends alpMission
{

	

//-------------------------------------------------------------------
//***************************//
//adjust default setting
//***************************//			
	override void OnInit()
	{
		//messages setting
		alp_SendInfoStart	= ALPMSTYPE.MMRADIATIONSTART;
		alp_SendInfoEnd		= ALPMSTYPE.MMRADIATIONEND;
		alp_AlertInfoIn		= ALPMSTYPE.SMRADIATIONIN;
		alp_AlertInfoOut	= ALPMSTYPE.SMRADIATIONOUT;
		alp_PagerInfoIn		= ALPMSTYPE.MMPERSONAL;
		alp_PagerInfoOut	= ALPMSTYPE.MMPERSONAL;		
	}

	
//-------------------------------------------------------------------
//***************************//
//Rewrite default methods
//***************************//		
	override protected bool SpawnLoot(bool missionSecured = false)
	{
		if (super.SpawnLoot(missionSecured))
		{
			SetRadioactiveBarrels();
			return true;
		}
		else return false;
	}
	
	override protected void InitMissionValues(int radius = 0, float radiation = 0)
	{	
		if ( !radius && !radiation ) {
			if ( GetTemplate().radiusOfRadiation.Count() == 2 && GetTemplate().strengthOfRadiation.Count() == 2){
				alp_DamageRadius	= Math.RandomIntInclusive(Math.AbsInt(GetTemplate().radiusOfRadiation.Get(0)),Math.AbsInt(GetTemplate().radiusOfRadiation.Get(1)));
				alp_Radiation		= Math.RandomFloatInclusive(Math.AbsFloat(GetTemplate().strengthOfRadiation.Get(0)),Math.AbsFloat(GetTemplate().strengthOfRadiation.Get(1)));
			}
			else {
				alp_DamageRadius 	= alp_SafeRadius;
				alp_Radiation		= 1;
			}				
 		} else {
			alp_DamageRadius = radius;
			alp_Radiation = radiation;
		}		
		
		
		if ( GetTemplate().radiationDynamic || GetTemplate().radiationSpawnedByContaminedArea )
		{
			RemoveSetting( alpMISSION_SETTING.RADIATION_ACTIVE );
		}
		else
		{
			SetSetting( alpMISSION_SETTING.RADIATION_ACTIVE );		
		}

	}		
	
	override protected void InteractionOnInsiders(Object obj,float distance) 
	{
		if (obj.IsMan() ) 
			SetPlayerInRadiation(PlayerBase.Cast(obj),distance);
	};
	
	override protected void OnLeave(Object obj )
	{
		super.OnLeave(obj);
		if (obj.IsMan()) 
			CleanPlayer(PlayerBase.Cast(obj));		
		
	};		
	
	override void OnLeavePlayer(PlayerBase player) 	
	{
		super.OnLeavePlayer(player);
		CleanPlayer(player);		
	}
	

	
	private void SetRadioactiveBarrels()
	{
		foreach(alpMissionElement e : alp_LootContainer)
		{
			if ( e.Get() && e.Get().GetType() == "alp_Barrel_Yellow" )			
			{
				alp_Barrel_Yellow barrel 	= alp_Barrel_Yellow.Cast( e.Get() );	  //added items
				//barrel.alp_SmokeType		= GetTemplate().visualEffect;
				barrel.Open();
				
				barrel.alp_MissionID = GetID(); 

				if (GetTemplate().enableDeactivation) barrel.alp_Lock(false);  
				else barrel.alp_Lock(true);						
			}
		}				
	}
	
	
	private void CleanPlayer(PlayerBase player)
	{
		if (player)
		{
			player.GetRP().SetRadiation( GetID() , 0 );		
		}		
	}	
	
	override void SetSettingOnEnter()
	{
		if ( GetTemplate().radiationDynamic && !GetTemplate().radiationSpawnedByContaminedArea )
		{
			int time = GetTemplate().radiationDynamic;
			time *= 1000;		
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.SetSetting,time,false, alpMISSION_SETTING.RADIATION_ACTIVE);
		}

	}	
}

		



