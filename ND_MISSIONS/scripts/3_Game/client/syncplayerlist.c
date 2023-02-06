modded class SyncPlayerList
{
	

	override void CreatePlayerList()
	{
		if (GetGame().IsServer())
		{
			m_PlayerList = new array<ref SyncPlayer>;

			array<Man> players = new array<Man>;
			GetGame().GetWorld().GetPlayerList(players);

			for (int i = 0; i < players.Count(); ++i)
			{
				Man player = players[i];
				PlayerIdentity p_identity = player.GetIdentity();

				if (p_identity)
				{
					SyncPlayer sync_player = new SyncPlayer;
					sync_player.m_UID = p_identity.GetPlainId();
					sync_player.m_PlayerName = p_identity.GetName();
					sync_player.m_PlayerUniqueID = p_identity.GetPlayerUniqueID();
					m_PlayerList.Insert(sync_player);
				}
				else
				{
					DebugPrint.LogErrorAndTrace("No Identity in Server Player List");
				}
			}
		}
	}

}