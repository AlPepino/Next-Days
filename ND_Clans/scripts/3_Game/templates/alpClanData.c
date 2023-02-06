
class alpClanData 
{
	int ClanID;
	string Name;
	ref array<int>					MembersOnline	= new array<int>; //GUID
	ref map<int,string>				Members 		= new map<int,string>; //GUID - Name	
	
	void alpClanData(int clanID, string clanName, string playerName )
	{
		ClanID = clanID;
		Name = clanName;
		
		Members.Set( clanID, playerName );
		MembersOnline.Insert( clanID );
		
		if ( GetGame().IsServer() )
		{
		
			string path = ALP_CLANS_FOLDER + ClanID.ToString() + ".json";
			
			if (FileExist(path) ) 
				DeleteFile(path);	
			
		
			Save();			
		}
	
	}
	
	void SetMemberOnline(int id)
	{
		if ( MembersOnline.Find(id) < 0 )
		{
			MembersOnline.Insert( id );
		}
	}
	bool RemoveMemberOnline(int id)
	{
		MembersOnline.RemoveItem( id );
		
		if ( MembersOnline.Count() > 0 )
		{
			return false;
		}
		else
		{
			return true;
		}
	}	
	bool IsMemberOnline(int playerID)
	{

		if ( MembersOnline.Find( playerID) >= 0 )
			return true;
		return false;
	}
	
	
	void RemoveMember(int playerID)
	{
		MembersOnline.RemoveItem(playerID);
		Members.Remove( playerID );
		
		Save();
	}
	
	void AddMember(int playerID, string name )
	{
		SetMemberOnline( playerID );
		Members.Set( playerID, name );
		
		Save();
	}
	
	
	bool IsMember(int playerID)
	{
		string name;
		if ( Members.Find( playerID, name) )
		{
			return true;
		}
		return false;
	}
		
	int GetCountOnline()
	{
		return MembersOnline.Count();	
	}

	
	void Save()
	{
		string path = ALP_CLANS_FOLDER + ClanID.ToString() + ".json";
		JsonFileLoader< alpClanData>.JsonSaveFile(path,  this );
	
	}	
	
	void Delete()
	{
		string path = ALP_CLANS_FOLDER + ClanID.ToString() + ".json";
			
		if (FileExist(path) ) 
			DeleteFile(path);	
							
	}
	
	static alpClanData GetClan(int clanId, int playerID , string name)
	{
		alpClanData clan;
		
		string path = ALP_CLANS_FOLDER + clanId.ToString() + ".json";
		
		JsonFileLoader< alpClanData>.JsonLoadFile(path,  clan );
		
		if ( clan )
		{
			string savedName;
			if ( clan.Members.Find( playerID, savedName ) )
			{
				if ( name != savedName )
				{
					clan.Members.Set( playerID, name );
					clan.Save();				
				}
			}
			else
			{
				return null;
			}
		}
		return clan;
	}
}
