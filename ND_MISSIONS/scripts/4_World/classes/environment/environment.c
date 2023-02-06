modded class Environment
{
	//const float ALP_RAIN_LIMIT_LOW	= 0.05;


	
	bool IsRainingALP()
	{
		return m_Rain > RAIN_LIMIT_LOW && m_Player && !m_Player.IsInVehicle() && !m_Player.IsSoundInsideBuilding();
	}

};
