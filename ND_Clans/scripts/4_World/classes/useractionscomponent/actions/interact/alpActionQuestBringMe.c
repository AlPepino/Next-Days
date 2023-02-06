
// Script File
modded class alpActionQuestBringMe: ActionInteractBase
{

	
	override void ReputationReward(PlayerBase player, float exp)
	{
		if ( GetND().GetClans().GetOptions().SplitQuestReward )
		{
			int clanID = player.GetClanID();
			
			if ( clanID && player.GetRP().GetClan() )
			{
				autoptr array<Object> nearest_objects = new array<Object>;
				autoptr array<CargoBase> proxy_cargos = new array<CargoBase>;
					
				GetGame().GetObjectsAtPosition( player.GetPosition() , 20 , nearest_objects, proxy_cargos ); 	
					
				
				autoptr array<PlayerBase> players = new array<PlayerBase>;
				
				for (int i = 0; i < nearest_objects.Count();i++)
				{
					if ( nearest_objects.Get(i) && nearest_objects.Get(i).IsMan() )
					{
						PlayerBase man = PlayerBase.Cast( nearest_objects.Get(i) );
						
						if ( man && man != player && man.GetRP().GetClan() && man.GetClanID() == clanID )
						{
							players.Insert( man );
						}
					}
				}				
				exp = Math.Round (exp / (players.Count() + 1) );
				
				foreach (PlayerBase mate : players)
				{								
					mate.GetRP().ChangeReputation(  exp );				
				}
				
				
				
			}
			
		}

		super.ReputationReward(  player, exp );	
	
		
	}



}