class CfgPatches
{
	class ND_Role_Playing
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS"		
		};
		author="AlPepino";
		authorID="76561198077747785";
		name="ND_Role_Playing";
		url="";
	};
};

class CfgMods
{
	class ND_Role_Playing
	{
		type="mod";
		name="ND - Clans";
	    dependencies[] = {"Game", "World", "Mission"};
	    class defs	    
		{					
			class gameScriptModule
            {
                value = "";
                files[] = 
				{	
					"ND_Role_Playing/scripts/3_Game"
				};
            };			
			class worldScriptModule
            {
                value = "";
                files[] = 
				{
					"ND_Role_Playing/scripts/4_World"
				};
            };
			class missionScriptModule
            {
                value = "";
                files[] = 
				{
					"ND_Role_Playing/scripts/5_Mission"
				};
            };
        };
    };
};
