
modded class TentBase extends ItemBase
{
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );

        ctx.Write( alp_IsMissionObject );

	}	

	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( super.OnStoreLoad( ctx, version ) )
		{
			ctx.Read( alp_IsMissionObject );
						
			return true;
		}
		else return false;
	}
};
