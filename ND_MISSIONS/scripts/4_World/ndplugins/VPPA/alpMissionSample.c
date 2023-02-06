// Script File

class alpMissionSample
{

	
	
	bool										active 					= true;
	
	float										chance					= 1.0;
	
	int 										nominal = 1;						//max count of this mission in map at once
	int 										lifeTime = 0;						//mission lifeTime
	int 										restock = 0;						//max events for all server LifeTime		

	int											missionSafeSpawnRadius	= 100;
	int 										distanceRadius			= 100;		
	
	int 										safeRadius				= 100;						//trigger for spawn dynamic AI
	int 										cleanRadius				= 150;
	
	bool										showInMap = true;						//show point in map

	string										mapTitle;						//map title
	

	ref array<ref array<float>> 				position				=	new array<ref array<float>>;

	ref array<ref alpMissionAddSpawn>			structures				= 	new array<ref alpMissionAddSpawn>;	
	ref array<ref alpMissionAddNPC>				NPC						= 	new array<ref alpMissionAddNPC>;	
	ref array<ref alpMissionAddCargo> 			loot					= 	new array<ref alpMissionAddCargo>;
	ref array<ref alpMissionAddVehicle> 		vehicles				= 	new array<ref alpMissionAddVehicle>;
}


class alpMissionAIsample
{

	string								className				= "ZmbM_PrisonerSkinny";
	string				 				type					= "static";
	ref array<int>						nominal					= {1,1};
	int									restock					= 0;
	
	vector								position;
	int									radius					= 0;
		
	int									spawnRadius				= 0;	
	ref array<ref alpLootCargo>			cargo 					= 	new array<ref alpLootCargo>;
	
	

}
