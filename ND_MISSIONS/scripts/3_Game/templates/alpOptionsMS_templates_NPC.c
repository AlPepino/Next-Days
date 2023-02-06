//NPC template
//----------------------------------------------------------------------------------------------




class alpNPCtraderStock 
{
	int 							RequiredCharacterTraits;  //RequiredRole
	int 							EnabledInteractions = 3;//settingNPC
		
	int 							CurrencyID;	
	
	int								Cash = 500000;	
	
	int								CashAddingPerRestock = 100000;//adding per spawn;		
	
	//int								CashNominal = 1000000;//trader cash	
	int								CashMinimal= 1000000;//trader cash	
	int								CashOptimal = 5000000;//cashAffectsPrices
	//int								CashMaximal = 10000000;
	float							CashAffectsPrices = 0.25; //0.25 	
					
	//float							PricelistGlobalRatio = 1;	

		
	float							PricelistRatioHero = 1;
	float							PricelistRatioBandit = 1;	
	int 							CentralStock = 0;
	bool							NoReputationRequirementsWhileBuying = 0;
	ref map<string,int>				Stock;	
	

}



class alpMissionAddNPC 
{
	string 							className;
	float							chance;
	int								IsDead;
	vector 							position;
	float  							yaw;
	float							pitch;
	float							roll;
	int								stance;	

	ref array<string>				attachments;
	int	lootMaxCount =  0;			
	ref array<ref alpLootCargo>		cargo;	


	int 							AllowedQuestsAtOnce;//0-means nothing
	int 							EnabledInteractions;	
	ref array<string>				AvailableGoodsByTag;	//works at first run	
	int 							CurrencyID;
	int 							CentralStockID;
	int 							StockID;

	string 							managedMission;	
	string 							missionWhileCountdowningON;
	string 							missionWhileCountdowningOFf;		
	int 							missionTriggerSetting;
	int                             missionSwitchCooldown;
	string 							missionActionMessageON;	
	string 							missionActionMessageOFF;

	int 							missionActionGameplayCountdownedON;
	int 							missionActionGameplayCountdownedOFF;	
	string 							countdownMessageON;	
	string 							countdownMessageOFF;	
	string 							giveItemWhenActivate;
		
	//string 							

	
}	

