
modded class Weapon_Base extends Weapon
{


	override void EEFired(int muzzleType, int mode, string ammoType)
	{	
		super.EEFired( muzzleType,  mode, ammoType);
		

		
		PlayerBase player = PlayerBase.Cast( GetHierarchyRootPlayer() );
		if( player && player.GetRP().IsDebtor() && !player.GetRP().IsEchoCoolDown() )
		{
			if( player.GetItemInHands() == this )
			{
				ItemBase suppressor = GetAttachedSuppressor();
			
				player.GetRP().MakeEchoWatnedPerson( suppressor , alpMOST_WANTED.BANK );
				
				
			}
		}


	}
	

};

