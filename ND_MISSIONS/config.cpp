class CfgPatches
{
	class ND_MISSIONS
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
		author="AlPepino";
		authorID="76561198077747785";
		name="ND_MISSIONS";
		url="";
	};
};

class CfgMods
{
	class ND_MISSIONS
	{
		type="mod";
		name="ND - Missions";
	    dependencies[] = {"Game", "World", "Mission"};
		inputs="ND_MISSIONS\scripts\inputs\nd_info_inputs.xml";
	    class defs	    
		{			
			class imageSets
			{
				files[]=
				{
					"ND_MISSIONS/gui/imagesets/nd_dayz_gui.imageset"
				};
			};			
			class gameScriptModule
            {
                value = "";
                files[] = 
				{	
					"BasicMapDefine/scripts/Common",
					"VPPAdminTools/Definitions",
					"DayZExpansion/Scripts/Common",
					"nst/namalsk/scripts/Common",
					"nst/ns_dayz/scripts/Common",					
					"ND_MISSIONS/scripts/3_Game"
				};
            };			
			class worldScriptModule
            {
                value = "";
                files[] = 
				{
					"BasicMapDefine/scripts/Common",
					"VPPAdminTools/Definitions",
					"DayZExpansion/Scripts/Common",
					"nst/namalsk/scripts/Common",
					"nst/ns_dayz/scripts/Common",			
					"ND_MISSIONS/scripts/4_World"
				};
            };
			class missionScriptModule
            {
                value = "";
                files[] = 
				{
					"BasicMapDefine/scripts/Common",
					"VPPAdminTools/Definitions",
					"DayZExpansion/Scripts/Common",
					"nst/namalsk/scripts/Common",
					"nst/ns_dayz/scripts/Common",			
					"ND_MISSIONS/scripts/5_Mission"
				};
            };
        };
    };
};
