
modded class alpMission 
{
	bool m_IsAiResctricted;

	void SetAiRestricted(bool state){
		m_IsAiResctricted = state;
	}
	
	
	override void LoadMission( alpMissionStore s ){
		super.LoadMission(s);
		if ( m_IsAiResctricted ) {
			alpPluginNDmissionsSystem.RegisterRestrictedMission(this);
		}
	}
	
	override alpMissionBase SpawnMission(vector pos = "0 0 0", vector angle = "0 0 0", int parentID = -1 ){
		alpMissionBase m = super.SpawnMission( pos, angle,parentID);
		if ( m ){
			if ( m_IsAiResctricted ) {
				alpPluginNDmissionsSystem.RegisterRestrictedMission(this);
			}			
			return m;
		}
		return null;
	}	
	
	override void DespawnMission(){		
		if ( m_IsAiResctricted ) {
			alpPluginNDmissionsSystem.UnRegisterRestrictedMission(this);
		}			
		super.DespawnMission();		
	}	
}