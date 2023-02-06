//sledovane budou NPC, control panels, structures, loot
class alpMissionElementStore_Base{
	string 	m_Type;
	int 	m_ID;
	int 	m_Index;//array index of template
	//string 	m_Name; nazev bude dynamicky?
	vector 	m_Position;
	vector 	m_YPR;
	int     m_Stance;
	
	void alpMissionElementStore_Base(string name, int id, int index, vector pos, vector ypr, int stance){
		m_Type = name;
		m_ID = id;
		m_Index = index;
		m_Position = pos;
		m_YPR = ypr;
		m_Stance = stance;	
	}

}

class alpMissionStore
{
	int m_Id;
	int m_ParendId;
	string m_Name;
	
	int m_Setting;

	int	m_SafeRadius;	
	int	m_CleanRadius;
	int	m_DamageRadius;
	
	vector	m_Position;
	vector	m_Angle;
	
	float	m_Radiation;	
	
	ref array<ref alpMissionElementStore_Base>	m_ControlPanels;
	ref array<ref alpMissionElementStore_Base> 	m_Loots;
	ref array<ref alpMissionElementStore_Base> 	m_Cars;
	
	ref array<ref alpMissionElementStore_Base>	m_Structures;
	
	ref array<ref alpMissionElementStore_Base>	m_NPC;  //UPRAVIT OBECNY MODEL SLEDOVANI NPC
	ref array<ref alpMissionElementStore_Base>	m_NPCdynamic;  //UPRAVIT OBECNY MODEL SLEDOVANI NPC
	
	ref array<ref alpMissionElementStore_Base>	m_ContaminedAreas;  
	ref array<ref alpMissionElementStore_Base>	m_ContaminedAreasDynamic;  
	
	void alpMissionStore() {
		m_ControlPanels	= new array<ref alpMissionElementStore_Base>;
		m_Loots = new array<ref alpMissionElementStore_Base>;
		m_Cars = new array<ref alpMissionElementStore_Base>;
		m_Structures = new array<ref alpMissionElementStore_Base>;
		m_NPC	= new array<ref alpMissionElementStore_Base>;
		m_NPCdynamic = new array<ref alpMissionElementStore_Base>;
		m_ContaminedAreas = new array<ref alpMissionElementStore_Base>;
		m_ContaminedAreasDynamic = new array<ref alpMissionElementStore_Base>;				
		
	}
	
	void InitMission(alpMissionBase mission){
		m_Id = mission.alp_Id;
		m_ParendId = mission.alp_ParendId;
		m_Name = mission.alp_Name;
		m_Setting = mission.alp_Setting;
		m_SafeRadius = mission.alp_SafeRadius;
		m_CleanRadius = mission.alp_CleanRadius;
		m_DamageRadius = mission.alp_DamageRadius;
		m_Position = mission.alp_Position;		
		m_Angle = mission.alp_Angle;
		m_Radiation = mission.alp_Radiation;
		
		Save();
	}
	void UpdateSetting(int setting){
		m_Setting = setting;
	}
	void Save(){
		if (IsPersistent() ){
			alpMHIVE.Save();
		}
	}
	bool IsPersistent() {
		return m_Setting & alpMISSION_SETTING.SAVE_STAGE;
	}
	
	void AddPanel(string name,int id, int index, vector pos, vector ypr, int stance = 0) {
		if (IsPersistent() ){
			alpMissionElementStore_Base element = new alpMissionElementStore_Base( name, id, index, pos, ypr,stance);
			m_ControlPanels.Insert(element);
			Save();				
		}
	}
	void AddLoot(string name,int id, int index, vector pos, vector ypr, int stance = 0) {
		if (IsPersistent() ){		
			alpMissionElementStore_Base element = new alpMissionElementStore_Base( name, id, index, pos, ypr,stance);
			m_Loots.Insert(element);
			Save();
		}			
	}	
	void AddCar(string name,int id, int index, vector pos, vector ypr, int stance = 0) {
		if (IsPersistent() ){		
			alpMissionElementStore_Base element = new alpMissionElementStore_Base(name,  id, index, pos, ypr,stance);
			m_Cars.Insert(element);
			Save();
		}			
	}	
	void AddStructure(string name,int id, int index, vector pos, vector ypr, int stance = 0) {
		alpMissionElementStore_Base element = new alpMissionElementStore_Base( name, id, index, pos, ypr,stance);
		m_Structures.Insert(element);
		alpMHIVE.Save(); //budovy vzdy ukladat, kvuli pozdejsimu odstraneni	
	}	
	void AddNpc(string name,int id, int index, vector pos, vector ypr, int stance = 0) {
		if (IsPersistent() ){		
			alpMissionElementStore_Base element = new alpMissionElementStore_Base( name, id, index, pos, ypr,stance);
			m_NPC.Insert(element);
			Save();		
		}			
	}	
	void AddNpcDynamic(string name,int id, int index, vector pos, vector ypr, int stance = 0) {
		if (IsPersistent() ){		
			alpMissionElementStore_Base element = new alpMissionElementStore_Base( name, id, index, pos, ypr,stance);
			m_NPCdynamic.Insert(element);
			Save();		
		}			
	}	
	void AddArea(string name,int id, int index, vector pos, vector ypr, int stance = 0) {
		if (IsPersistent() ){		
			alpMissionElementStore_Base element = new alpMissionElementStore_Base( name, id, index, pos, ypr,stance);
			m_ContaminedAreas.Insert(element);
			Save();	
		}			
	}	
	void AddAreaDynamic(string name,int id, int index, vector pos, vector ypr, int stance = 0) {
		if (IsPersistent() ){		
			alpMissionElementStore_Base element = new alpMissionElementStore_Base(name, id, index, pos, ypr,stance);
			m_ContaminedAreasDynamic.Insert(element);
			Save();	
		}			
	}	
	
	void RemoveLoot(int id) {
		if ( m_Loots ){
			int count = m_Loots.Count();
			for(int i = 0; i < count ; i++ ) {
				if ( m_Loots.Get(i).m_ID == id ) {
					m_Loots.Remove(i);
					break;
				}
			}
		}
		Save();
	}
	void RemoveCar(int id) {
		if ( m_Cars ){
			int count = m_Cars.Count();
			for(int i = 0; i < count ; i++ ) {
				if ( m_Cars.Get(i).m_ID == id ) {
					m_Cars.Remove(i);
					break;
				}
			}
		}
		Save();
	}
	void RemoveNPC(int id) {
		int count,i;		
		if ( m_NPC ){
			count = m_NPC.Count();
			for(i = 0; i < count ; i++ ) {
				if ( m_NPC.Get(i).m_ID == id ) {
					m_NPC.Remove(i);
					return;
				}
			}
		}
		if ( m_NPCdynamic ){
			count = m_NPCdynamic.Count();
			for(i = 0; i < count ; i++ ) {
				if ( m_NPCdynamic.Get(i).m_ID == id ) {
					m_NPCdynamic.Remove(i);
					return;
				}
			}
		}	
		Save();
	}	
		
}