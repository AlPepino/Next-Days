
	
class alpMHIVE{
	  
	static string PATH = "$profile:Next-Days/DB/";  
	static string PATH_TOFILE = "$profile:Next-Days/DB/missions_";

	static protected ref map<int, ref alpMissionStore> 	m_Missions; 
	
	static int m_SaveRequestCounter;	

	static protected void LoadHive(){		
		if (!FileExist(ALP_ROOTFOLDER)) MakeDirectory(ALP_ROOTFOLDER);
		if (!FileExist(PATH)) MakeDirectory(PATH);
		
		string path = PATH_TOFILE + "0.dat";		
		m_Missions = new map<int, ref alpMissionStore>;	
        if(FileExist(path)) {
			FileSerializer file = new FileSerializer();
			
			if (file.Open(path, FileMode.READ))
			{
				bool end;
				while(!end){
					alpMissionStore mission;	
					file.Read(mission);
					if ( mission ) {

						int key = mission.m_Id;
						m_Missions.Set(key , mission);	
					} else {
						end = true;
					}
				}					
			    file.Close();
			}
        }		
	}
	
	static protected void SaveHive(){

		if ( m_SaveRequestCounter > 0 ) {
			m_SaveRequestCounter = 0;
			string path_origo = PATH_TOFILE + "0.dat";				
			string path = PATH_TOFILE + "1.dat";	
			FileSerializer file = new FileSerializer();
			if (file.Open( path, FileMode.WRITE) )
			{
				for (int i = 0; i < m_Missions.Count(); i++ ){
					file.Write(m_Missions.GetElement(i));				
				}
				file.Close();
			}			
			CopyFile(path,path_origo);	
		}								
	}
	
	static void InitHive() {
		LoadHive();		
		//delete all structures			
		foreach( alpMissionStore stored : m_Missions ){
			for(int i = 0; i < stored.m_Structures.Count();i++){
				alpMissionElementStore_Base s = stored.m_Structures.Get(i);				
				autoptr array<Object> nearest_objects = new array<Object>;
				autoptr array<CargoBase> proxy_cargos = new array<CargoBase>;
					
				GetGame().GetObjectsAtPosition3D( s.m_Position , 5 , nearest_objects, proxy_cargos ); 						
				for (int x = 0; x < nearest_objects.Count();x++){
					Object obj = nearest_objects.Get(x);				
					if ( obj && obj.GetType() == s.m_Type ) {
						GetGame().ObjectDelete( obj );
					}
				}
			}
		}
		//save loop
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(alpMHIVE.SaveHive,5000,true);	
	}
	
	static alpMissionStore RegisterMission( alpMissionBase mission ) {		
		int id = mission.GetID();
		alpMissionStore store = new alpMissionStore();		
		m_Missions.Set( id , store ); 
		Save();
		return store;
	}
	
	static void UnRegisterMission(int id) {
		m_Missions.Remove(id);
		Save();
	}

	static alpMissionStore Get(int id, string name ) {	
		alpMissionStore mission;			
		if ( m_Missions.Find( id , mission )  ) {
			if ( mission.m_Name == name && ( mission.m_Setting & alpMISSION_SETTING.SAVE_STAGE ) && !(mission.m_Setting & alpMISSION_SETTING.MISSION_IDLE) &&  !( mission.m_Setting & alpMISSION_SETTING.MISSION_SECURED ||  mission.m_Setting & alpMISSION_SETTING.MISSION_EXPIRED || mission.m_Setting & alpMISSION_SETTING.MISSION_FAILED ) ) {			
				return mission;
			} 
		}
		return null;
	}

		
	static void Save() {
		m_SaveRequestCounter++;						
	}
}

