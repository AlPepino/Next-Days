// Script File


modded class alpNPC : PlayerBase
{


	
	
	bool CanMakeMedicalExamination()
	{
		if ( alp_StockID > 0 )
		{
			alpNPCtraderStock stock = alpTraderCoreBase.alp_TraderStockMapped.Get( alp_StockID );
			if ( stock )
			{
				bool setting = stock.EnabledInteractions;
				
				return setting & alpNPC_AVAILABLE_MENU.MEDICAL;			
			}
			return false;

		}
		return false;	
	}
	
	
	
	
	override bool CanSpeakWithMe(PlayerBase player)
	{
		
		int role = 0;

		if (player.GetSyncData().GetElement( alpRPelements.REPUTATION ).GetValue() > 0 )
		{
			if ( player.GetRP().IsHero()) 
				role = 1;
			else
				role = 2;
		}
							
		if  ( CheckCharacterRole(role) ) 
			return true;
		else 
			return false;	
		
	
	}
	
	

	bool CheckCharacterRole(int role)
	{
		if ( alp_StockID > 0 )
		{
			alpNPCtraderStock stock = alpTraderCoreBase.alp_TraderStockMapped.Get( alp_StockID );
			if ( stock )
			{
				int setting = stock.RequiredCharacterTraits;
				
				if ( setting == 0 || setting == role )
				{
					return true;
				}
				
				return false;		
			}
			return true;

		}
		return true;			
		
	}		

	

}
