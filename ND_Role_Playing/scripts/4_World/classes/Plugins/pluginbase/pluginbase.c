// Script File
modded class PluginPlayerStatus extends PluginBase
{
	/*
	ref multiMap<int, string> 	m_NotifiersLabel;
	ref multiMap<int, int>		m_NotifiersIndexColor;

	private ref multiMap<int, string>	m_NotifiersIcons;

	*/
	
	void PluginPlayerStatus()
	{
		/*
		m_NotifiersLabel = new multiMap<int, string>; // [key] label
		m_NotifiersIndexColor = new multiMap<int, int>; // [key] index, color

		m_NotifiersIcons = new multiMap<int, string>; // [key] iconName
		
		m_NotifiersIcons.Insert( NTFKEY_HUNGRY, "iconHunger" );
		m_NotifiersIcons.Insert( NTFKEY_THIRSTY, "iconThirsty" );
		m_NotifiersIcons.Insert( NTFKEY_SICK, "iconHealth" );
		m_NotifiersIcons.Insert( NTFKEY_BACTERIA, "iconBacteria" );
		m_NotifiersIcons.Insert( NTFKEY_BLEEDISH, "iconBlood" );
		m_NotifiersIcons.Insert( NTFKEY_FEVERISH, "iconTemperature" );
		m_NotifiersIcons.Insert( NTFKEY_FRACTURE, "iconFracture" );
		*/
		
		m_NotifiersIcons.Insert( NTFKEY_ALPTIREDNESS, "iconTiredness" );
	}
	
	
	override void DisplayTendency( int key, int tendency, int status = 1 )
	{
		super.DisplayTendency( key, tendency, status  );
			
		
		if ( key == NTFKEY_ALPTIREDNESS )
		{
			PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
			
			if (player.GetRP())
				player.GetRP().SetFatigueStatus( status );
		}
	}

}
