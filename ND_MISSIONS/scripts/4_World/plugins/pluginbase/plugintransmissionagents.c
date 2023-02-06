
modded class PluginTransmissionAgents extends PluginBase
{

	void PluginTransmissionAgents()
	{
		//add new agents here
		RegisterAgent(new alpRadiationAgent);

	}
	
	
	override static float GetProtectionLevelEx(int type, int slot, Man player, bool consider_filter = true, int system = 0)
	{
		float protection = 0;
		
		PlayerBase p = PlayerBase.Cast( p );
		
		if ( p && p.GetRP())
		{
			if ( consider_filter )
			{
				protection = p.GetRP().GetProtection().GetProtectionRespiratory( type );
			}
			else
			{
				protection = p.GetRP().GetProtection().GetProtection(type,slot);
			}
		
		}
		
		return protection;
	}

};