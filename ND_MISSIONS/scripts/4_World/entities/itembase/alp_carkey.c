class alp_CarKey_Base: Inventory_Base
{
	int				alp_KeyID;
	
	override void SetActions()
	{
		super.SetActions();
		
		
		AddAction(alpLockVehicle);
		AddAction(alpUnlockVehicle);
	}
	
	bool IsAdminKey()
	{
		return false;
	}
	
	
	int GetAlpKeyID()
	{
		return alp_KeyID;
	}
	
	void SetAlpKeyID(int keyid){
		alp_KeyID = keyid;
	}
}



class alp_AdminCarKey extends alp_CarKey_Base
{
	override bool IsAdminKey()
	{
		return true;
	}	
}


class alp_CarKey extends alp_CarKey_Base
{

	
	void alp_CarKey()
	{
		//SetEventMask(EntityEvent.INIT); // Enable + event
		
		RegisterNetSyncVariableInt("alp_KeyID");
		
		
	}

	override void EOnInit(IEntity other, int extra)
	{
		super.EOnInit(other, extra);
		
		GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( this.CreateKeyForVehicle, 100);
	}
	
	
	void CreateKeyForVehicle()
	{
		CarScript car;
		
		if ( alp_KeyID == 0 && Class.CastTo( car, GetHierarchyRoot() ) )
		{
			alp_KeyID = car.GetAlpCarID();
		}
		else
		{
			if ( alp_KeyID == 0 )
			{
				alp_KeyID = -1;	
			}
			
		}
		SetSynchDirty();
	}
	
	override string GetTooltip()
	{
		string tooltip = super.GetTooltip();
		int key = alp_KeyID;
		if ( key == -1 )
		{
			key = 0;
		}
		
		tooltip = tooltip + " ID: " + key.ToString();
		
		return tooltip;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(alpCreateDuplicate);
	}



	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );

        ctx.Write( alp_KeyID );

	}	
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( super.OnStoreLoad( ctx, version ) )
		{
			ctx.Read( alp_KeyID );
			return true;
		}
		else return false;
	}		
}

class alp_CarKeyBlue : alp_CarKey {}
class alp_CarKeyGreen : alp_CarKey {}
class alp_CarKeyYellow : alp_CarKey {}
class alp_CarKeyWhite : alp_CarKey {}
class alp_CarKeyPurple : alp_CarKey {}
class alp_CarKeyBrown : alp_CarKey {}