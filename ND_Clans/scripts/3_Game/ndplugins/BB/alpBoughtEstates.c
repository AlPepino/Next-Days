class alpEstateSetting
{
	string	ObjectID;//house id	
	string	ObjectName;//house id	
	int 	OwnerID;//owner
	int 	ClanID;//owner
	int		KeyID;	 //key
	int    	Setting;//setting
	
	int 	RoomMates[32];
	int 	ClaimedBeds;
	int		ValidThru;
	int 	Permission;

	void alpEstateSetting(string houseid, string type,  int ownerid)
	{
		ObjectID = houseid;
		ObjectName = type;
		OwnerID = ownerid;

	}
	
	bool ReleaseOldBed( int index, int playerID)
	{
		int b = Math.Pow( 2 ,index );
		if ( RoomMates[index] == playerID )
		{
			ClaimedBeds = ~b & ClaimedBeds;
			RoomMates[index] = 0;		
			return true;
		}
		return false;
	}	
	void Clear(){
		OwnerID = 0;
		ClanID = 0;
		KeyID = 0;
		Setting = 0;
		ClaimedBeds = 0;
		ValidThru = 0;		
		Permission = 0;	
	}
	void PrintValues(){
		Print("ObjectID " + ObjectID + " ObjectName " + ObjectName + " OwnerID " + OwnerID + " ClanID " + ClanID + " ClaimedBeds " + ClaimedBeds );
	}
}



