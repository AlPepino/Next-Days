class CfgPatches
{
	class ND_Clans_data_Sounds
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_Clans"
		};
	};
};
class CfgSoundShaders
{	
	class alp_LockingHouse_SoundShader
	{
		samples[]=
		{
			
			{
				"ND_Clans\data\Sounds\lock",
				1
			}
		};
		range=8;
		volume=10;
	};	
	class alp_UnLockingHouse_SoundShader
	{
		samples[]=
		{
			
			{
				"ND_Clans\data\Sounds\unlock",
				1
			}
		};
		range=8;
		volume=10;
	};			
};
class CfgSoundSets
{	
	class alp_LockingHouse_SoundSet
		{
		soundShaders[]=
		{
			"alp_LockingHouse_SoundShader",
		};
	};	
	class alp_UnLockingHouse_SoundSet
		{
		soundShaders[]=
		{
			"alp_UnLockingHouse_SoundShader",
		};
	};	
};