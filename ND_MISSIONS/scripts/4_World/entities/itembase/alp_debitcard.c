
class alp_Debitcard extends ItemBase
{
	int alp_BANK_GUID;
	int alp_CARD_ID;
	int alp_CARD_PIN;

	
	void alp_Debitcard()
	{	
		RegisterNetSyncVariableInt("alp_CARD_PIN");		
		RegisterNetSyncVariableInt("alp_CARD_ID");	
		
	}	

	void SetBankID(int id)
	{
		alp_CARD_PIN = 1234;
		alp_BANK_GUID	= id;
		SetSynchDirty();
	}
	int GetBankID()
	{
		return alp_BANK_GUID;
	}	
	int GetCardID()
	{
		if (!alp_CARD_ID)
			alp_CARD_ID = Math.RandomInt(1, int.MAX - 1);
				
		return alp_CARD_ID;
	}
	int GetCardPIN()
	{
		return alp_CARD_PIN;
	}
	void SetCardPIN(int pin)
	{
		alp_CARD_PIN = pin;
		SetSynchDirty();
	}	

	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		
        ctx.Write( alp_CARD_ID );
		ctx.Write( alp_BANK_GUID );
		ctx.Write( alp_CARD_PIN );

	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( super.OnStoreLoad( ctx, version ) )
		{
		
			ctx.Read( alp_CARD_ID );
			ctx.Read( alp_BANK_GUID );
			ctx.Read( alp_CARD_PIN );
			
			return true;
		}
		else return false;
	}	

	
}
