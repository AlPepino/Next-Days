modded class Environment
{

	
	bool IsInShelter()
	{
		if ( m_Player && m_Player.IsSoundInsideBuilding() || m_IsUnderRoof)
			return true;
		else
			return false;
	}
};