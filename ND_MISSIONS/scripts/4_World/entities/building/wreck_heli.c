modded class Wreck_UH1Y extends CrashBase
{
	protected bool alp_IsMissionObject = false;

	
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
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if ( IsMissionObject() )
		{	
			GetGame().ObjectDelete( this );
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
	
	void EEOnALPCreate()
	{
		EEOnCECreate();
	}	
}



modded class Wreck_Mi8 extends CrashBase
{
	protected bool alp_IsMissionObject = false;

	
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
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if ( IsMissionObject() )
		{	
			GetGame().ObjectDelete( this );
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
	
	void EEOnALPCreate()
	{
		EEOnCECreate();
	}
}




modded class Wreck_Mi8_Crashed extends CrashBase
{
	protected bool alp_IsMissionObject = false;

	
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
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		
		if ( IsMissionObject() )
		{	
			GetGame().ObjectDelete( this );
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
	
	void EEOnALPCreate()
	{
		EEOnCECreate();
	}
}
