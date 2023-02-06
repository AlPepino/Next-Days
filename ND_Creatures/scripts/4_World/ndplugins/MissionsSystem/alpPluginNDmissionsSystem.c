
modded class alpPluginNDmissionsSystem extends alpPlugin
{
	
	
	static ref map<int,ref alpMission>					m_AiCannotSpawnInMissions = new map<int,ref alpMission>;
	
	static int m_IsLocal = 0;
	static int m_IsGlobal = 0;
	
	

	void ~alpPluginNDmissionsSystem(){
		delete m_AiCannotSpawnInMissions;			
	}		
	/*
	override void Init() {
		super.Init();
		if (GetGame().IsServer() &&  GetGame().IsMultiplayer() ){
			m_IsLocal = 0;
			m_IsGlobal = 0;
			m_AiCannotSpawnInMissions = new map<int,ref alpMission>;
		}		
	}
	*/
	
	override void AddMissionByName(string name, alpMission mission)
	{
		super.AddMissionByName(name,mission);
		array<string> registered = GetND().GetCreatures().GetOptions().CannotSpawnInMissions;
		if ( mission && registered && registered.Find( name ) != -1 ) {
			mission.SetAiRestricted(true);
		} 
	}	
	
	static void RegisterRestrictedMission(alpMission m){
		int id = m.GetID();
		int radius = m.alp_DamageRadius;		
		
		if ( radius >= 20000 ) {
			
			m_IsGlobal+=1;
		} else {
			m_IsLocal+=1;
			m_AiCannotSpawnInMissions.Set(id,m);			
		}
	
	}
	static void UnRegisterRestrictedMission(alpMission m){
		
		int id = m.GetID();
		int radius = m.alp_DamageRadius;		
		if ( radius >= 15000 ) {
			m_IsGlobal-=1;
		} else {
			m_IsLocal-=1;
			m_AiCannotSpawnInMissions.Remove(id);			
		}	
	
	}	

	static bool CansSpawnAI(DayZCreatureAI ai){
		
		if ( ai.ResistContaminatedEffect() ) {					
			return true;
		}

		if (m_IsGlobal ){
			return false;
		}
	
		if ( m_IsLocal   ) {
			foreach(alpMission m : m_AiCannotSpawnInMissions ) {
				int radius = m.alp_DamageRadius;
				if ( alpUF.VectorDistance( m.GetPosition(),ai.GetPosition()) <= radius ) {
					return false;
				}			
			}			
		}
	
				
		return true;
	}

}

