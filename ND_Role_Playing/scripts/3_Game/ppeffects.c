modded class PPEffects
{

	
	static void EnableClosedEyesALP()
	{
		SetColorValue(m_BurlapBlindness, 0, 0, 0, 1, 1.0);
		UpdateColor();
		g_Game.SetEVValue(-5);
	}

	static void DisableClosedEyesALP()
	{		
		SetColorValue(m_BurlapBlindness, 0, 0, 0, 0, 0.0);
		UpdateColor();
		g_Game.SetEVValue(0);
	}

};