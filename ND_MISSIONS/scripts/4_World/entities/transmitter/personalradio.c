
modded class PersonalRadio extends TransmitterBase
{
	bool alp_IsOn;
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		
		//store tuned frequency
		ctx.Write( IsOnALP() );
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
		


		if ( !ctx.Read( alp_IsOn ) )
		{
			SetWorkingStateALP(false);
		} 
		
		return true;
	}	

	override void AfterStoreLoad(){
		super.AfterStoreLoad();
		if ( IsOnALP() ){
			if ( HasEnergyManager() && !GetCompEM().IsWorking() && GetHierarchyRootPlayer() ) {
				GetCompEM().SwitchOn();
			} 
		}		 
	}
	
	void SetWorkingStateALP(bool state){
		alp_IsOn = state;
	}
	
	bool IsOnALP(){
		return alp_IsOn;
	}	
	

}
