modded class Epinephrine
{
	override void OnApply(PlayerBase player)
	{
		super.OnApply(player);

		
		player.GetStatTiredness().Add( GetND().GetRP().GetFatigue().EpinephrineEnergyBoost );
		

	}
}
