class alpSpreadRumoursFees 
{

	int NegativeGossipCost = 10000;
	int PositiveGossipCost = 10000;
	int NegativeGossipGain = 1000;
	int PositiveGossipGain = 1000;
}
class alpMedicalFees 
{
	bool EnabledBloodTest		= true;
	bool EnabledCloneDNA		= true;
	
	int Fee = 500;
	int Bleeding = 500;
	int BrainSick = 25000;
	int Commoncold = 5000;
	int Influenza = 10000;	
	int Cholera = 15000;
	int Salmonella = 10000;
	int WoundInfectionL1 = 5000;
	int WoundInfectionL2 = 10000;
	int FoodPoisoning = 5000;
	int ChemicalPoisoningL1 = 5000;
	int ChemicalPoisoningL2 = 10000;
	int ChemicalPoisoningL3 = 15000;		
	int BrokenArm = 10000;
	int BrokenLeg = 10000;
	int RadiationSick = 100000;
	int FrostbiteSick = 100000;
	
	int Decontamination = 2000;
	
	
	int SaveDNA = 1000;
	int RecoverDNA = 50000;	
}




class alpExpandedInteraction 
{
	bool EnableSales						= true;
	
	ref alpMedicalFees MedicalFees;
	
 	ref alpSpreadRumoursFees Rumours;


	void alpExpandedInteraction()
	{
		Rumours	= new alpSpreadRumoursFees();
		MedicalFees = new alpMedicalFees();
	}
	
	alpMedicalFees GetMedicalFees(float rate, float coef, float sale)
	{
		alpMedicalFees fees = new alpMedicalFees;
		
		if ( !EnableSales )
		{
			sale = 0;
		}

		if ( coef )			
		{
			
			fees.Fee = MedicalFees.Fee * rate * coef * (1 - sale );
			fees.Bleeding = MedicalFees.Bleeding * rate * coef * (1 - sale );
			fees.BrainSick = MedicalFees.BrainSick * rate * coef * (1 - sale );
			fees.Commoncold = MedicalFees.Commoncold * rate * coef * (1 - sale );
			fees.Influenza = MedicalFees.Influenza * rate * coef * (1 - sale );
			fees.Cholera = MedicalFees.Cholera * rate * coef * (1 - sale );
			fees.Salmonella = MedicalFees.Salmonella * rate * coef * (1 - sale );
			fees.WoundInfectionL1 = MedicalFees.WoundInfectionL1 * rate * coef * (1 - sale );
			fees.WoundInfectionL2 = MedicalFees.WoundInfectionL2 * rate * coef * (1 - sale );
			fees.FoodPoisoning = MedicalFees.FoodPoisoning * rate * coef * (1 - sale );
			fees.ChemicalPoisoningL1 = MedicalFees.ChemicalPoisoningL1 * rate * coef * (1 - sale );
			fees.ChemicalPoisoningL2 = MedicalFees.ChemicalPoisoningL2 * rate * coef * (1 - sale );
			fees.ChemicalPoisoningL3 = MedicalFees.ChemicalPoisoningL3 * rate * coef * (1 - sale );
			fees.BrokenArm = MedicalFees.BrokenArm * rate * coef * (1 - sale );
			fees.BrokenLeg = MedicalFees.BrokenLeg * rate * coef * (1 - sale );
			fees.RadiationSick = MedicalFees.RadiationSick * rate * coef * (1 - sale );
			fees.FrostbiteSick = MedicalFees.FrostbiteSick * rate * coef * (1 - sale );
			fees.Decontamination = MedicalFees.Decontamination * rate * coef * (1 - sale );
			fees.SaveDNA = MedicalFees.SaveDNA * rate * coef * (1 - sale );
			fees.RecoverDNA = MedicalFees.RecoverDNA * rate * coef * (1 - sale );
			
			
		}
				
		return fees;	
	}	
	
	alpSpreadRumoursFees GetRumoursFees(float rate, float coef, float sale)
	{
		alpSpreadRumoursFees fees = new alpSpreadRumoursFees;
		
		if ( !EnableSales )
		{
			sale = 0;
		}

		if ( coef )			
		{
			
			fees.NegativeGossipCost = Rumours.NegativeGossipCost * rate * coef * (1 - sale );
			fees.PositiveGossipCost = Rumours.PositiveGossipCost * rate * coef * (1 - sale );
	
			fees.NegativeGossipGain = Rumours.NegativeGossipGain / coef;
			fees.PositiveGossipGain = Rumours.PositiveGossipGain / coef;			
		}
				
		return fees;	
	}
}

