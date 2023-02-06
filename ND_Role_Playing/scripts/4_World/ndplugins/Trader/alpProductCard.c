
modded class alpProductCard 
{


	override float GetPlayerCoef(alpNPCtraderStock trader)
	{

		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		float hero = trader.PricelistRatioHero;
		float bandit = trader.PricelistRatioBandit;		
		auto stock = GetND().GetMS().GetTrader().GetCurrentTrader();
		if ( stock && !stock.RequiredCharacterTraits ) {
			if ( GetND().GetMS().GetTrader().IsBuyMenu() ){
				if ( player.GetRP().IsHero() ){
					return hero;		
				} else {
					return bandit;
				}					
			} else {
				return Math.Min(hero,bandit);
			}							
		} else {
			if ( player.GetRP().IsHero() ){
				return hero;		
			} else {
				return bandit;
			}			
		}

	}

	//TO DO: reputation skill
	override bool HasReputation()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		int level = player.GetSyncData().GetElement( alpRPelements.REPUTATION ).GetValue();
		
		int required = GetRequiredReputation();
		
		auto stock = GetND().GetMS().GetTrader().GetCurrentTrader();
				
		if (level >= required || (GetND().GetMS().GetTrader().IsSellMenu() && stock.NoReputationRequirementsWhileBuying ))
		{			
			return true;
		}
		else
		{
			return false;
		}
		
	}
	
	override float GetSales()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		int level = player.GetSyncData().GetElement( alpRPelements.REPUTATION ).GetValue();

		float sale = 	GetND().GetRP().GetReputationMdf( level );	
		return sale;
	}

}