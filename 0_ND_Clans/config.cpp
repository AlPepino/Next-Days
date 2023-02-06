class CfgPatches
{
	class 0_ND_Clans
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};

class CfgMods
{
	class 0_ND_Clans
	{
		type="mod";
		name="ND - Clans";
	    dependencies[] = {"GameLib","Game", "World", "Mission"};
	    class defs	    
		{	
			class gameLibScriptModule
			{
				value = "";
				files[] = {"0_ND_Clans/scripts/Common"};
			};		
			class gameScriptModule
            {
                value = "";
				files[] = {"0_ND_Clans/scripts/Common"};
            };			
			class worldScriptModule
            {
                value = "";
				files[] = {"0_ND_Clans/scripts/Common"};
            };
			class missionScriptModule
            {
                value = "";
				files[] = {"0_ND_Clans/scripts/Common"};
            };
        };
    };
};
