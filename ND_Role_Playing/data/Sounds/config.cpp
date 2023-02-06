class CfgPatches
{
	class ND_Role_Playing_data_Sounds
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_Role_Playing"
		};
	};
};
class CfgSoundShaders
{
	class baseCharacter_SoundShader;
	class yawn_SoundShader: baseCharacter_SoundShader
	{
		samples[]=
		{
			
			{
				"ND_Role_Playing\data\Sounds\yawn",
				1
			}
		};
		volume=10;
	};	
	class alp_rofl_SoundShader: baseCharacter_SoundShader
	{
		samples[]=
		{
			
			{
				"ND_Role_Playing\data\Sounds\rofl",
				1
			}
		};
		range=50;
		volume=0.1;
	};	
};
class CfgSoundSets
{
	class baseCharacter_SoundSet;
	class yawn_SoundSet: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"yawn_SoundShader"
		};
	};	
	class alp_rofl_SoundSet: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"alp_rofl_SoundShader"
		};
	};
};