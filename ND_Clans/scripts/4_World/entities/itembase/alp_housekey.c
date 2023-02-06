
class alp_HouseKey_Base: Inventory_Base
{

	int 			alp_HouseKeyID = -1;
	
	int 			alp_KeyID = -1;
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(alpActionLockDoors);
		AddAction(alpActionUnlockDoors);
	}
	
	bool IsAdminKey()
	{
		return false;
	}
	
	
	void SetHouseID(int id)
	{
		alp_HouseKeyID = id;
	}	
	int GetHouseID()
	{
		return alp_HouseKeyID;
	}	

	void SetKeyID(int id)
	{
		alp_KeyID = id;
	}
	int GetKeyID()
	{
		return alp_KeyID;
	}	
		
}



class alp_AdminHouseKey extends alp_HouseKey_Base
{
	override bool IsAdminKey()
	{
		return true;
	}	
}


class alp_HouseKey extends alp_HouseKey_Base
{



	void alp_HouseKey()
	{

		RegisterNetSyncVariableInt("alp_HouseKeyID");
		RegisterNetSyncVariableInt("alp_KeyID");
	}
	
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );

        ctx.Write( alp_HouseKeyID );
		 ctx.Write( alp_KeyID );
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( super.OnStoreLoad( ctx, version ) )
		{
			ctx.Read( alp_HouseKeyID );
			ctx.Read( alp_KeyID );

			return true;
		}
		else return false;
	}	
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if (alp_HouseKeyID > 0 )
		{
			SetSynchDirty();
		}
	}
			

	override string GetTooltip()
	{
		string tooltip = super.GetTooltip();
	
		string keyID = "#pp_masterkey";
		
		if ( alp_KeyID >= 0 )
		{
			keyID =  "#pp_doorID: " + alp_KeyID.ToString();
		}
		
		
		tooltip = tooltip + " - #pp_houseID: " + alp_HouseKeyID.ToString() + ", " + keyID;
		
		return tooltip;
	}
	

}