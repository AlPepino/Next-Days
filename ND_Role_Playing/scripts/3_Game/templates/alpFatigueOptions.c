
class alpFatigueOptions 
{
	float FatigueBasal									= 0.0025; //energy loss per second while idle (max energy is 100)
	float FatigueWalk									= 0.005; //energy loss per second while walking (max energy is 100)
	float FatigueJog									= 0.008; //energy loss per second while jogging (max energy is 100)
	float FatigueSprint									= 0.016; //energy loss per second while sprintingn (max energy is 100)
	float FatigueRadiationMultiplier					= 1.2;  //multiplies energy loss while you staying in radiation zone
	float FatigueRadiationSickMultiplier				= 2;  //multiplies energy loss while you getting radiation disease
	float FatigueSickMultiplier							= 1.5;  //multiplies energy loss while you getting common diseases
	float FatigueHeatMultiplier							= 2;  //multiplies energy loss while you have bad heat confort
	float Resting										= 2; //energy increase per second while resting 
	float RestingPenaltyHeat							= 0.5; //when you do not have heat comfort;
	float RestingPenaltyShelter							= 0.5; //when you are not in building or near sleeping bag;
	bool ClosedEyesWhileSleeping						= true;// 0/1
	float EpinephrineEnergyBoost						= 10; //max energy is 100
	ref array<string> SleepingBag						= {};
	ref array<ref alpFoodBonuses> FoodBonuses;
	ref array<ref alpLiquidBonuses> LiquidBonuses;
	
	void alpFatigueOptions()
	{
		FoodBonuses = new array<ref alpFoodBonuses>;
		
		FoodBonuses.Insert( new alpFoodBonuses( "SodaCan_Cola", 0.02, 0, 0,0 ) );
		FoodBonuses.Insert( new alpFoodBonuses( "SodaCan_Pipsi", 0.02, 0, 0,0 ) );
		FoodBonuses.Insert( new alpFoodBonuses( "SodaCan_Kvass", -0.01, 0.1, -0.1,0 ) );	
		
		
		LiquidBonuses = new array<ref alpLiquidBonuses>;
		
		LiquidBonuses.Insert( new alpLiquidBonuses( 2048, -0.05, 0.6, -0.6,-0.2 ) ); //vodka
		LiquidBonuses.Insert( new alpLiquidBonuses( 4096, -0.01, 0.1, -0.1,0 ) ); //bear

	}	
	
	alpFoodBonuses GetFoodBonus(string name)
	{
		alpFoodBonuses	food;
	
		if (FoodBonuses)
		{
			for (int i = 0; i < FoodBonuses.Count();i++)
			{
				if ( name == FoodBonuses.Get(i).Item )
				{
					food = FoodBonuses.Get(i);
					break;
				}
			}
		}
		
		
		return food;
	}
	
	alpLiquidBonuses GetLiquidBonus(int name)
	{
		alpLiquidBonuses lid;
	
		if (LiquidBonuses)
		{
			for (int i = 0; i < LiquidBonuses.Count();i++)
			{
				if ( name == LiquidBonuses.Get(i).LiquidID )
				{
					lid = LiquidBonuses.Get(i);
					break;
				}
			}
		}
		
		
		return lid;
	}	
}

class alpFoodBonuses 
{
	string Item;
	float Energy;
	float Alcohol;
	float Radiation;
	float Toxicity;
	
	void alpFoodBonuses(string n, float en, float ac, float rr, float tt)
	{
		Item 			= n;
		Energy			= en;
		Alcohol			= ac;
		Radiation		= rr;
		Toxicity		= tt;
	}
}

class alpLiquidBonuses 
{
	int LiquidID;
	float Energy;
	float Alcohol;
	float Radiation;
	float Toxicity;
	
	void alpLiquidBonuses(int liqID, float en, float ac, float rr, float tt)
	{
		LiquidID 		= liqID;
		Energy			= en;
		Alcohol			= ac;
		Radiation		= rr;
		Toxicity		= tt;
	}
}