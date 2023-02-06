
modded class TransmitterBase 
{
	bool alp_Working;
	
	bool IsBaseRadio()
	{
		return false;
	}
	
	override void OnWorkStart()
	{
		super.OnWorkStart();
		
				
		alp_Working = true;
	}
	
	override void OnWorkStop( )
	{	

		super.OnWorkStop();
		
		alp_Working = false;
		


	}		
	
	
	bool IsWorking()
	{
		return alp_Working;
	}
	/*
	override void OnWorkStart()
	{
		super.OnWorkStart();
		
		PlayerBase player;		
		if ( Class.CastTo( player, GetHierarchyRootPlayer()) )
		{ 				
			player.GetRP().SetWalkieTalkie( this );						
		}					

	}
	
	override void OnWork( float consumed_energy )
	{	
		super.OnWork( consumed_energy );
	
		if ( GetGame().IsClient() )
		{
			PlayerBase player;		
			if ( Class.CastTo( player, GetHierarchyRootPlayer()) )
			{ 				
				player.GetRP().SetWalkieTalkie( this );						
			}					
		}

	}		
	*/
}


modded class BaseRadio
{
	override bool IsBaseRadio()
	{
		return true;
	}	
}