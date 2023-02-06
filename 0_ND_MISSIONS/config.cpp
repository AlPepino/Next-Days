class CfgPatches
{
	class 0_ND_MISSIONS
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};

class CfgMods
{
	class 0_ND_MISSIONS
	{
		type="mod";
		name="ND - Missions";
	    dependencies[] = {"GameLib","Game", "World", "Mission"};
	    class defs	    
		{	
			class gameLibScriptModule
			{
				value = "";
				files[] = {"0_ND_MISSIONS/scripts/Common"};
			};		
			class gameScriptModule
            {
                value = "";
				files[] = {"0_ND_MISSIONS/scripts/Common"};
            };			
			class worldScriptModule
            {
                value = "";
				files[] = {"0_ND_MISSIONS/scripts/Common"};
            };
			class missionScriptModule
            {
                value = "";
				files[] = {"0_ND_MISSIONS/scripts/Common"};
            };
        };
    };
};
