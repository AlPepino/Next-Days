/*!
	Base script class for helicopters.
*/
modded class HelicopterScript extends HelicopterAuto
{
	protected bool alp_IsMissionObject = false;

	bool 						alp_Lock;
	int							alp_CarID;

	//bool						alp_AlarmSound;

	void HelicopterScript(){
		RegisterNetSyncVariableInt("alp_CarID");
		//RegisterNetSyncVariableBool("alp_AlarmSound");		
		
		if ( GetGame().IsServer() ) {
			alpPluginNDmissionsSystem.AddVehicleToStat( GetType() );	
		}
	}
	void ~HelicopterScript(){
		//alpPluginNDmissionsSystem.CarsCount = alpPluginNDmissionsSystem.CarsCount + 1;	
		
		if ( GetGame() && GetGame().IsMultiplayer() && GetGame().IsServer() ) {
			alpPluginNDmissionsSystem.RemoveVehicleFromStat( GetType()  );
			
		}
		
			
	}	
	int GetAlpCarID()
	{
		return alp_CarID;
	}
	void SetAlpCarID(int carid)
	{
		alp_CarID = carid;
	}	
	
	override void EEInit()
	{
		super.EEInit();
		
		
		if ( GetGame().IsServer() )
		{
			if ( alp_CarID == 0 ) 
				SetCarID();

		}		
	}	
	protected void SetCarID()
	{
		alp_CarID = Math.RandomIntInclusive( 1, int.MAX - 1 );
		SetSynchDirty();
	}	
	
	string GetServerWorldID()
	{
		return GetNetworkIDString();
	}
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );

		Param2 <bool,int> data = new Param2<bool,int>(alp_Lock,alp_CarID);
		ctx.Write( data );
		ctx.Write( alp_IsMissionObject );

	}	
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		bool result = super.OnStoreLoad( ctx, version );
		
		if (! GetND().IsFirstRun() )
		{
			Param2 <bool,int> data = new Param2<bool,int>(0,0);
			if ( !ctx.Read( data ) ){
				result = false;;	
			}
			
			alp_Lock 				= data.param1;
			alp_CarID 				= data.param2;

			/*
			SetVehicleLockState( alp_Lock );
			if ( alp_CarID == 0 )
			{
				SetCarID();	
				SetSynchDirty();
			}							
			*/
							
			if ( !ctx.Read( alp_IsMissionObject ) ){
				result = false;;	
			}
		}		
		
		return result;
	}	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if (! GetND().IsFirstRun() && IsMissionObject() )
		{	
			GetGame().ObjectDelete( this );
		}				
	}	
	
	protected void SetVehicleLockState( bool state)
	{
		alp_Lock = state;
		
		if (state)	
		{
			GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
			
			if ( state && GetND().GetRP().GetVehicleOptions().IndestructibleLockedVehicle  )
			{
				LockVehicleAttachmentsALP( false );
				SetAllowDamage( false );
			}
							
		}
		SetSynchDirty();
	}		
	void LockVehicleALP( bool state)
	{
		alp_Lock = state;
		
		if (state)	
		{
			GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
			
			if ( state && GetND().GetRP().GetVehicleOptions().IndestructibleLockedVehicle  )
			{
				LockVehicleAttachmentsALP( false );
				SetAllowDamage( false );
			}				
		}
		else
		{
			GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
			
			if (GetND().GetRP().GetVehicleOptions().IndestructibleLockedVehicle  )
			{
				LockVehicleAttachmentsALP( true );
				SetAllowDamage( true );
			}			
		}
	
	}
	void LockVehicleAttachmentsALP(bool state)
	{
		int attachments_count = GetInventory().AttachmentCount();

		
		for ( int i = 0; i < attachments_count; i++ )
		{
			ItemBase item = ItemBase.Cast( GetInventory().GetAttachmentFromIndex( i ) );
			
			if ( item )
			{
				item.SetAllowDamage( state );	
			}
		}
		
	}	


	bool IsMissionObject()
	{
		return alp_IsMissionObject;
	}
	
	void SetMissionObjectState(bool state)
	{
		alp_IsMissionObject	= state;
	}

	ref alpTraderItemConfig alp_TraderItemConfig;
	
	alpTraderItemConfig GetTraderItemConfig()
	{
		//kontorla existence v input od uzivatele
		
		
		//default z configu
		if ( !alp_TraderItemConfig)
		{
			alp_TraderItemConfig = alpTraderCoreBase.GetTraderItemConfig( GetType() );
			
			if (!alp_TraderItemConfig )
			{
				alp_TraderItemConfig = new alpTraderItemConfig( GetType(), 0, 0,0 ,0, 0, 0, 0);
			}

		}
		
	
		return alp_TraderItemConfig;
	}	
	/*
	void PlayAlarmSound()
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{		
			EffectSound sound =	SEffectManager.PlaySound("alp_CarAlarm_SoundSet", GetPosition() );
			sound.SetSoundAutodestroy( true );
			alp_AlarmSound = false;
		}
	}

	override float OnSound( CarSoundCtrl ctrl, float oldValue )
	{
		float value = super.OnSound( ctrl, oldValue);
		
		if ( GetGame().IsServer() )
		{
			if ( alp_AlarmSound )
				alp_AlarmSound = false;
		}

		return value;
	}	
	*/
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		/*		
		if (alp_AlarmSound )
			PlayAlarmSound();
		*/
	}
	/*
	void ActivateAlarmSystem()
	{
		alp_AlarmSound = true;	
	}
	void DisableAlarmSystem()
	{
		alp_AlarmSound = false;	
	}	
*/

	override void OnEngineStart()	
	{
		super.OnEngineStart();
		SetMissionObjectState( false );	
		
		PlayerBase player = PlayerBase.Cast(CrewMember(0));		
		if (player)
		{
			player.GetRP().SetCar ( this );
		}	


		//unlock car
		if (alp_Lock)
		{
			LockVehicleALP( false );			
		}
	
	}

	int GetAttachmentCountALP()
	{
		//return GetInventory().AttachmentCount();
		EntityAI attachment;
		int attcount = GetInventory().AttachmentCount();
		int count = 0;
		for (int att = 0; att < attcount; att++)
		{	
			attachment = GetInventory().GetAttachmentFromIndex(att);
			if ( attachment.IsItemBase() && attachment.HasAnyCargo())
			{
				count++;
			}
		}							
		return count;
	}
	
	string GetNameALP()
	{		
		string name = GetType() + "_"  + GetQuantityALP().ToString() + "_" + GetHealthLevelALP().ToString() + "_" + GetAttachmentCountALP().ToString() + "_" + GetCargoCountALP().ToString();
		return name;
	}
	int GetCargoCountALP()
	{
		int cargo = 0;
		
		if ( HasAnyCargo() )
			cargo = GetInventory().GetCargo().GetItemCount();		
		
		return cargo;
	}
	
	float GetQuantityALP()
	{
		return 1;
	}	
	
		
		
	float GetHealthLevelALP()
	{
		float level = 1;
		
		switch (GetHealthLevel())
		{
			case 1:
			{
				level = 0.75;
				break;
			}
			case 2:
			{
				level = 0.50;
				break;
			}			
			case 3:
			{
				level = 0.25;
				break;
			}
			case 4:
			{
				level = 0;
				break;
			}			
		}
		return level;
	}		
	
	
	int GetDefaultPrice()
	{
		int price = 0;
		alpTraderItemConfig config = GetTraderItemConfig();		
		if ( !config || ( !config.CanBuy &&  !config.CanSell ) )
		{
			return price;
		}
		
		
		
		price = (int) config.Price * GetHealthLevelALP();
		
		
		return price;
	}
	void MissionLockVehicleALP( bool state)
	{
		alp_Lock = state;
		
		if (state)	
		{
			GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
			
			LockVehicleAttachmentsALP( false );
			SetAllowDamage( false );				
		}
		else
		{
			GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
			
			LockVehicleAttachmentsALP( true );
			SetAllowDamage( true );		
		}
	
	}	
}
