// Script File
modded class Hud: Managed
{
	void SendMessageALP(int type, string text, vector pos = "0 0 0"){}
	
}


modded class PlayerIdentity : PlayerIdentityBase
{
	int m_PlayerUniqueID;
	
	int m_PlayerReputationLevel;
	
	void SetPlayerUniqueID(int id ){
		m_PlayerUniqueID = id;
	}
	int GetPlayerUniqueID(){
		return m_PlayerUniqueID;
	}
	void SetPlayerLevel(int id ){
		m_PlayerReputationLevel = id;
	}	
	int GetPlayerLevel(){
		return m_PlayerReputationLevel;
	}
}