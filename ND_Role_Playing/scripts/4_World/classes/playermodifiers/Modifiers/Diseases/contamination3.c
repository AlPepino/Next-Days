modded class ContaminationStage3Mdfr: ModifierBase
{
	override void OnActivate(PlayerBase player)
	{
		super.OnActivate(player);
		
		
		player.GetRP().SetDisease(alpDiseases.POISONING_CHEMICAL_3);

	}
	

	
	override void OnDeactivate(PlayerBase player)
	{
		super.OnDeactivate(player);
		
		player.GetRP().UnsetDisease(alpDiseases.POISONING_CHEMICAL_3);
	}
	
	override protected void OnTick(PlayerBase player, float deltaT)
	{
		
		float protection = player.GetRP().GetProtection().GetNaturalResistanceAgainstChemical();
		
		if ( protection )
		{
			
			if(GetAttachedTime() > 4 && (!player.GetSymptomManager().GetCurrentPrimaryActiveSymptom() || (player.GetSymptomManager().GetCurrentPrimaryActiveSymptom() &&  player.GetSymptomManager().GetCurrentPrimaryActiveSymptom().GetType() != SymptomIDs.SYMPTOM_VOMIT)) )
			{
				if ( Math.RandomFloat01()> protection )
				{
					float shock = -100 * (1 - protection);
					player.AddHealth("","Shock", shock );
				}
				
				
				SetAttachedTime(0);
			}
			
			if (player.IsUnconscious())
			{
				if ( Math.RandomFloat01()> protection )
				{
					player.AddHealth("","",DAMAGE_PER_SEC * deltaT * (1 - protection) );
				}
			}		
		}
		else super.OnTick(player, deltaT);
		


	}	
};