class CfgPatches
{
	class 0_ND_Role_Playing
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};

class CfgMods
{
	class 0_ND_Role_Playing
	{
		type="mod";
		name="ND - Role-Playing";
	    dependencies[] = {"GameLib","Game", "World", "Mission"};
	    class defs	    
		{	
			class gameLibScriptModule
			{
				value = "";
				files[] = {"0_ND_Role_Playing/scripts/Common"};
			};		
			class gameScriptModule
            {
                value = "";
				files[] = {"0_ND_Role_Playing/scripts/Common"};
            };			
			class worldScriptModule
            {
                value = "";
				files[] = {"0_ND_Role_Playing/scripts/Common"};
            };
			class missionScriptModule
            {
                value = "";
				files[] = {"0_ND_Role_Playing/scripts/Common"};
            };
        };
    };
};
