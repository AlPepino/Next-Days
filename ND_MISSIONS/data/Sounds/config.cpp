class CfgPatches
{
	class ND_MISSIONS_data_Sounds
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"ND_MISSIONS"
		};
	};
};
class CfgSoundShaders
{
	class alp_Geiger_SoundShader_low
	{
		samples[]=
		{
			
			{
				"ND_MISSIONS\data\Sounds\Geiger_Counter_Sound_low",
				1
			}
		};
		range=15;
		volume=0.5;
	};
	class alp_Geiger_SoundShader_medium
	{
		samples[]=
		{
			
			{
				"ND_MISSIONS\data\Sounds\Geiger_Counter_Sound_medium",
				1
			}
		};
		range=15;
		volume=0.75;
	};	
	class alp_Geiger_SoundShader_high
	{
		samples[]=
		{
			
			{
				"ND_MISSIONS\data\Sounds\Geiger_Counter_Sound_high",
				1
			}
		};
		range=15;
		volume=1;
	};	
	class alp_Geiger_SoundShader_veryhigh
	{
		samples[]=
		{			
			{
				"ND_MISSIONS\data\Sounds\Geiger_Counter_Sound_high",
				1
			}
		};
		range=25;
		volume=2;
	};		
	class alp_Geiger_SoundShader_Switch
	{
		samples[]=
		{		
			{
				"ND_MISSIONS\data\Sounds\Geiger_Counter_Sound_Switch",
				1
			}
		};
		range=5;
		volume=0.5;
	};		
	class alp_DecontaminationShower_SoundShader_On
	{
		samples[]=
		{			
			{
				"ND_MISSIONS\data\Sounds\decontamination",
				1
			}
		};
		range=10;
		volume=2;
	};			
	class alp_Locking_SoundShader
	{
		samples[]=
		{
			
			{
				"ND_MISSIONS\data\Sounds\locking",
				1
			}
		};
		range=8;
		volume=10;
	};	
	class alp_CarAlarm_SoundShader
	{
		samples[]=
		{
			
			{
				"ND_MISSIONS\data\Sounds\CarAlarm",
				1
			}
		};
		range=1000;
		volume=0.5;
	};		
	class alp_LevelUp_SoundShader
	{
		samples[]=
		{
			
			{
				"ND_MISSIONS\data\Sounds\levelup",
				1
			}
		};
		range=2;
		volume=10;
	};	
	class alp_LevelDown_SoundShader
	{
		samples[]=
		{
			
			{
				"ND_MISSIONS\data\Sounds\leveldown",
				1
			}
		};
		range=2;
		volume=10;
	};	
	class alp_KeyboardEffect_SoundShader
	{
		samples[]=
		{
			
			{
				"ND_MISSIONS\data\Sounds\keyboard",
				1
			}
		};
		range=5;
		volume=10;
	};	
	class alp_WarningAlarmEffect_SoundShader
	{
		samples[]=
		{
			
			{
				"ND_MISSIONS\data\Sounds\warningalarm",
				1
			}
		};
		range=200;
		volume=0.5;
	};		
};
class CfgSoundSets
{
	class alp_Geiger_SoundSet_low
	{
		soundShaders[]=
		{
			"alp_Geiger_SoundShader_low",
		};
	};
	class alp_Geiger_SoundSet_medium
	{
		soundShaders[]=
		{
			"alp_Geiger_SoundShader_medium",
		};
	};
	class alp_Geiger_SoundSet_high
	{
		soundShaders[]=
		{
			"alp_Geiger_SoundShader_high",
		};
	};	
	class alp_Geiger_SoundSet_veryhigh
	{
		soundShaders[]=
		{
			"alp_Geiger_SoundShader_veryhigh",
		};
	};	
	class alp_Geiger_SoundSet_Switch
	{
		soundShaders[]=
		{
			"alp_Geiger_SoundShader_Switch",
		};
	};
	class alp_DecontaminationShower_SoundSet_On
	{
		soundShaders[]=
		{
			"alp_DecontaminationShower_SoundShader_On",
		};
	};		
	class alp_Locking_SoundSet
		{
		soundShaders[]=
		{
			"alp_Locking_SoundShader",
		};
	};	
	class alp_CarAlarm_SoundSet
		{
		soundShaders[]=
		{
			"alp_CarAlarm_SoundShader",
		};
	};	
	class alp_LevelUp_SoundSet
		{
		soundShaders[]=
		{
			"alp_LevelUp_SoundShader",
		};
	};	
	class alp_LevelDown_SoundSet
		{
		soundShaders[]=
		{
			"alp_LevelDown_SoundShader",
		};
	};	
	class alp_KeyboardEffect_SoundSet
		{
		soundShaders[]=
		{
			"alp_KeyboardEffect_SoundShader",
		};
	};		
	class alp_WarningAlarmEffect_SoundSet
		{
		soundShaders[]=
		{
			"alp_WarningAlarmEffect_SoundShader",
		};
	};	
};