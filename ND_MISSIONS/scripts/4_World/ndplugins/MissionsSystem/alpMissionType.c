
class alpMissionType 
{
	ref map<string,int>	alp_MissionType;
	
	void alpMissionType()
	{
		alp_MissionType = new map<string,int>;
		Init();
	}
	void ~alpMissionType()
	{
		delete alp_MissionType;
	}
	
	
	void Init()
	{
		alp_MissionType.Set("noradiationMission", ALP_MISSIONTYPEID.noradiationMission );		
		alp_MissionType.Set("mission", ALP_MISSIONTYPEID.noradiationMission );		
		
		alp_MissionType.Set("noradiation", ALP_MISSIONTYPEID.noradiation );		
		alp_MissionType.Set("static", ALP_MISSIONTYPEID.noradiation );			

		
		alp_MissionType.Set("carAccident", ALP_MISSIONTYPEID.carAccident );				
		
		alp_MissionType.Set("radiation", ALP_MISSIONTYPEID.radiation );
		alp_MissionType.Set("radiationMission", ALP_MISSIONTYPEID.radiationMission );	
		
		alp_MissionType.Set("trader", ALP_MISSIONTYPEID.trader );	
		alp_MissionType.Set("fuelstation", ALP_MISSIONTYPEID.fuelstation );
		alp_MissionType.Set("savesurvivors", ALP_MISSIONTYPEID.savesurvivors );
		alp_MissionType.Set("savemerchants", ALP_MISSIONTYPEID.savemerchants );
		alp_MissionType.Set("conquerdefend", ALP_MISSIONTYPEID.conquerdefend );
	}
	
	static int GetMissionID(string name)
	{
		alpMissionType mt = new alpMissionType();
		
		int missionID = -1;
		
		mt.alp_MissionType.Find( name, missionID );
		
		return missionID;
	}

}