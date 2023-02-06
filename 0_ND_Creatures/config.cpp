class CfgPatches
{
	class 0_ND_Creatures
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};

class CfgMods
{
	class 0_ND_Creatures
	{
		type="mod";
		name="ND - Creatures";
	    dependencies[] = {"GameLib","Game", "World", "Mission"};
	    class defs	    
		{	
			class gameLibScriptModule
			{
				value = "";
				files[] = {"0_ND_Creatures/scripts/Common"};
			};		
			class gameScriptModule
            {
                value = "";
				files[] = {"0_ND_Creatures/scripts/Common"};
            };			
			class worldScriptModule
            {
                value = "";
				files[] = {"0_ND_Creatures/scripts/Common"};
            };
			class missionScriptModule
            {
                value = "";
				files[] = {"0_ND_Creatures/scripts/Common"};
            };
        };
    };
};
