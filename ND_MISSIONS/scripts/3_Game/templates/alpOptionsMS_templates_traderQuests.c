class alpRegisteredQuest
{
	int NPC;
	int Quest;
	int CurrencyID;
	float PosX;
	float PosY;
	void alpRegisteredQuest( int npc, int quest , vector pos, int currencyID )
	{
		NPC = npc;
		Quest = quest;
		PosX = pos[0];
		PosY = pos[2];
		CurrencyID = currencyID;
	}
	
	vector GetPosition()
	{
		return Vector(PosX,0,PosY);
	}
}


class alpTraderQuest
{
	ref array<int> AssociatedTraders = new array<int>;
	string AssociatedMission;
	//bool DespawnAssocitedMission = true;
	string StartMessage;
	string EndMessage;
	int RepeatStartMessageEvery;
	string MapTitle;  //odstranit, misto toho bude Bring me 
	float Chance;
	int Nominal;
	int LifeTime;
	int LastRun;
	int CoolDown;		
	bool HideWantedItems = true;;
	
	
	string WantedItem;
	string WantedItemAllowedType;
	int WantedRequiredCount = 1;
	string RewardItem;
	int RewardGivenCount = 1;
	float RewardPrice = 1;
	float RewardReputation = 0;
	int RequiredLevel = 0;
	int StoreAt = 0;
	
	
	void alpTraderQuest(int example = 0 )
	{
	
		switch (example)
		{
			case 1:
				//Title = "Bring #item to #pos for reward #reward ";
				WantedItem = "SVD";			
				break;				
		}		
	}
	//
	

}

