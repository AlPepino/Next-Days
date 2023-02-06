

#ifdef VPPADMINTOOLS

class VPPAKeyWordALP
{

	static string alp_ExportFolder = ALP_ROOTFOLDER + "Exports/";

	static string alp_NPC 	= "vbldr_legs_dz";

	static string alp_AI 	= "vbldr_legs_m";

	static string alp_LOOT = "vbldr_barrel_holes";
	static string alp_LOOT2 = "StaticObj_Misc_WoodenCrate";
	

	static string alp_VEHICLE = "Land_Wreck_Volha_Blue";	
	
	static string alp_CONSOLE = "alp_ServerConsole";	
	
	static string alp_VEHICLE_SPAWN = "Land_Wreck_Lada_Green";	
}




modded class BuildingSet
{




	
	override void ExportBuildings()
	{
		super.ExportBuildings();
		
		
		//check if exist folder
		if (!FileExist(VPPAKeyWordALP.alp_ExportFolder)) 
			MakeDirectory(VPPAKeyWordALP.alp_ExportFolder);	
		
		
		alpMissionTemplate ms = new alpMissionTemplate;
		
		
		ms.mapTitle = m_Name;
		ms.active = 1;
		ms.nominal = 1;
		ms.lifeTime = 3600;
		ms.restock = 1;
		ms.safeRadius = 100;
		ms.cleanRadius = 200;
		ms.chance = 1;
		ms.showInMap = 1;
		ms.sendInfo = 1;
		//ms.structures
		
		vector 	zeroPosition;

		float  	mYaw;
		float 	mPitch;
		float	mRoll;		
		
		foreach(SpawnedBuilding building: m_Buildings)
		{
			
			
			alpMissionAddSpawn structure = new alpMissionAddSpawn;	
				
			structure.className 		= building.GetTypeName();
			structure.noPlaceOnSurface	= true;

			vector orientation 			= building.GetOrientation();
									
			if (!zeroPosition)
			{
								
				zeroPosition 		= building.GetPosition();

				
				array<float> mPos = {zeroPosition[0],zeroPosition[1],zeroPosition[2],0};
				ms.position.Insert( mPos ); 
				
				structure.position = "0 0 0";
								
				structure.yaw 		= orientation[0];
				structure.pitch 	= orientation[1];
				structure.roll 		= orientation[2];	
				
				
			}
			else
			{
	
				structure.position = vector.Direction(zeroPosition ,  building.GetPosition() );
				//structure.position = vector.Direction(  building.GetPosition(), zeroPosition );
				
				
			
				structure.yaw 		= orientation[0];
				structure.pitch 	= orientation[1];
				structure.roll 		= orientation[2];				
			}
			
			//override default structure setting
			bool exception = false;			
			switch ( structure.className)
			{
				case VPPAKeyWordALP.alp_NPC:
				{
					alpMissionAddNPC npc = new alpMissionAddNPC;
					
					npc.position 	= structure.position;
										
					npc.yaw 		= structure.yaw;
					npc.pitch 		= structure.pitch;
					npc.roll 		= structure.roll;		
					
					ms.NPC.Insert( npc );
								
					exception = true;
					break;
				}
				case VPPAKeyWordALP.alp_AI:
				{
				    CreateMissionAI_alp( structure.position );
					exception = true;
					break;
				}			
				case VPPAKeyWordALP.alp_LOOT2:
				case VPPAKeyWordALP.alp_LOOT:
				{
					alpMissionAddCargo loot = new alpMissionAddCargo;
					loot.chance		= 1;
					loot.className 	= "SeaChest";
					
					loot.position 	= structure.position;
					
					loot.yaw 		= structure.yaw;
					loot.pitch 		= structure.pitch;
					loot.roll 		= structure.roll;							
					ms.loot.Insert( loot );
					exception = true;
					break;
				}	
				case VPPAKeyWordALP.alp_VEHICLE:
				{
					alpMissionAddVehicle vehicle = new alpMissionAddVehicle;
					vehicle.chance		= 1;
					vehicle.title = "MissionCars_1";

					vehicle.position 	= structure.position;
					
					vehicle.yaw 		= structure.yaw;
					vehicle.pitch 		= structure.pitch;
					vehicle.roll 		= structure.roll;						
					ms.vehicles.Insert( vehicle );					
					exception = true;
					break;
				}	
				case VPPAKeyWordALP.alp_CONSOLE:
				{
					alpMissionAddControlPanel console = new alpMissionAddControlPanel;

					console.className 	= "alp_ServerConsole";
					console.position 	= structure.position;
					
					console.yaw 		= structure.yaw;
					console.pitch 		= structure.pitch;
					console.roll 		= structure.roll;						
					ms.controlPanels.Insert( console );					
					exception = true;
					break;
				}	
				case VPPAKeyWordALP.alp_VEHICLE_SPAWN:
				{
					alpMissionAddSpawn spawn = new alpMissionAddSpawn;
					
					spawn.position 	= structure.position;
					
					spawn.yaw 		= structure.yaw;
					spawn.pitch 		= structure.pitch;
					spawn.roll 		= structure.roll;						
					ms.spawnPlaceForVehicles.Insert( spawn );					
					exception = true;
					break;
				}									
			} 
									
			if (!exception)
			{
				ms.structures.Insert( structure );	
			}
		}
		
		JsonFileLoader<ref alpMissionTemplate>.JsonSaveFile(VPPAKeyWordALP.alp_ExportFolder + m_Name + ".json",  ms);
	}
	
	
	void CreateMissionAI_alp(vector pos)
	{
		array<ref alpMissionAIsample> missionAI;
		
		if (!FileExist(VPPAKeyWordALP.alp_ExportFolder + m_Name + "_AI.json"))
		{
			JsonFileLoader<array<ref alpMissionAIsample>>.JsonSaveFile(VPPAKeyWordALP.alp_ExportFolder + m_Name + "_AI.json",  missionAI);	
		} 

		JsonFileLoader<array<ref alpMissionAIsample>>.JsonLoadFile(VPPAKeyWordALP.alp_ExportFolder + m_Name + "_AI.json",  missionAI);	
		
		
		alpMissionAIsample newAI = new alpMissionAIsample;		
		newAI.position = pos;
		
		missionAI.Insert( newAI );
		
		JsonFileLoader<array<ref alpMissionAIsample>>.JsonSaveFile(VPPAKeyWordALP.alp_ExportFolder + m_Name + "_AI.json",  missionAI);	

	};
	
}

#endif
