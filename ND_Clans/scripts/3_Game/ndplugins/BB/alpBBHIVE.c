class alpBBHIVE{
	  
	static string PATH = "$profile:Next-Days/DB/";  
	static string PATH_TOFILE = "$profile:Next-Days/DB/estates_";


	static int m_SaveRequestCounter;
	
	static bool m_WasInited;

	static protected ref map<string, ref alpEstateSetting> 	m_EstatesByID; 

	static protected void LoadHive(){		
		if (!FileExist(ALP_ROOTFOLDER)) MakeDirectory(ALP_ROOTFOLDER);
		if (!FileExist(PATH)) MakeDirectory(PATH);
		
		string path = PATH_TOFILE + "0.dat";		
		m_EstatesByID = new map<string, ref alpEstateSetting>;		
        if(FileExist(path)) {
			FileSerializer file = new FileSerializer();
			
			if (file.Open(path, FileMode.READ))
			{
				bool end;
				while(!end){
					alpEstateSetting estate;	
					file.Read(estate);
					if ( estate ) {
						string key = estate.ObjectID;
						m_EstatesByID.Set(key , estate);	
						//estate.PrintValues();
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
				for (int i = 0; i < m_EstatesByID.Count(); i++ ){
					if (m_EstatesByID.GetElement(i).OwnerID){
						file.Write(m_EstatesByID.GetElement(i));	//neulozim prazdne data
						//m_EstatesByID.GetElement(i).PrintValues();
					} 
				}
				file.Close();
			}			
			CopyFile(path,path_origo);									
		}
	}
	
	static void RegisterEstate( string id, alpEstateSetting estate ) {		
		m_EstatesByID.Set( id , estate ); 
	}
	
	static alpEstateSetting Get(string id , string type) {
		if ( !m_EstatesByID){
			LoadHive();
		}		
		alpEstateSetting estate;		
		if ( !m_EstatesByID.Find( id , estate ) ) {
			estate = new alpEstateSetting(id, type, 0,);
		}
		return estate;
	}
		
	static void Save() {
		
		if ( ! m_WasInited ) {
			m_WasInited = true;
			m_SaveRequestCounter++;
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(alpBBHIVE.SaveHive,60000,true);	
		} else {
			m_SaveRequestCounter++;		
		}
		
	}
}

