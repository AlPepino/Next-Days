class CfgPatches
{
	class ND_Creatures
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_Role_Playing"		
		};
		author="AlPepino";
		authorID="76561198077747785";
		name="ND_Creatures";
		url="";
	};
};

class CfgMods
{
	class ND_Creatures
	{
		type="mod";
		name="ND - Clans";
	    dependencies[] = {"Game", "World"};
	    class defs	    
		{	
			class gameScriptModule
            {
                value = "";
                files[] = 
				{	
					"ND_Creatures/scripts/3_Game"
				};
            };		
			class worldScriptModule
            {
                value = "";
                files[] = 
				{
					"ND_Creatures/scripts/4_World"
				};
            };
        };
    };
};