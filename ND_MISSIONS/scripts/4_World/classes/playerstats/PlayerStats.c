  

enum EPlayerStats_ALP
{
	
	SKILL_SPECIALTY_SOFT,
	SKILL_SPECIALTY_HARD,

	SKILL_STAMINA,
	SKILL_STAMINAPROGRESS,
		
	SKILL_RADIATIONIMMUNITY,
	SKILL_RADIATIONPROGRESS,

	SKILL_TOXICIMMUNITY,
	SKILL_TOXICIMMUNITYPROGRESS,

	SKILL_HUNTING,
	SKILL_HUNTINGPROGRESS,

	SKILL_REPUTATION,
	SKILL_REPUTATIONPROGRESS,
	COUNTPLAYERS,
	COUNTZOMBIES,
	COUNTANIMALS,
	COUNTSKINNED,
	CURRENT_SCORE,
	TIREDNESS,
};


class PlayerStatsND extends PlayerStatsPCO_Base
{
	override void Init()
	{
		//RegisterStat(EPlayerStats_ALP.HASONCONNECTDATA, new PlayerStat<int>(0, int.MAX , 0, "HasOnConnectData", EPSstatsFlags.EMPTY));
		
		RegisterStat(EPlayerStats_ALP.SKILL_SPECIALTY_SOFT, new PlayerStat<float>(-1, 0, 0, "SpecialtySoft", EPSstatsFlags.EMPTY));
		RegisterStat(EPlayerStats_ALP.SKILL_SPECIALTY_HARD, new PlayerStat<float>(0, 1, 0, "SpecialtyHard", EPSstatsFlags.EMPTY));		

		RegisterStat(EPlayerStats_ALP.SKILL_STAMINA, new PlayerStat<int>(0,64,0,"LevelStamina",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.SKILL_STAMINAPROGRESS, new PlayerStat<float>(0,999999999,0,"LevelStaminaProgress",EPSstatsFlags.EMPTY) );
		
		RegisterStat(EPlayerStats_ALP.SKILL_RADIATIONIMMUNITY, new PlayerStat<int>(0,64,0,"LevelImmunity",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.SKILL_RADIATIONPROGRESS, new PlayerStat<float>(0,999999999,0,"LevelImmunityProgress",EPSstatsFlags.EMPTY) );
		
		RegisterStat(EPlayerStats_ALP.SKILL_TOXICIMMUNITY, new PlayerStat<int>(0,64,0,"ToxicImmunity",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.SKILL_TOXICIMMUNITYPROGRESS, new PlayerStat<float>(0,999999999,0,"ToxicImmunityProgress",EPSstatsFlags.EMPTY) );	
		
		RegisterStat(EPlayerStats_ALP.SKILL_HUNTING, new PlayerStat<int>(0,64,0,"LevelHunting",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.SKILL_HUNTINGPROGRESS, new PlayerStat<float>(0,999999999,0,"LevelHuntingProgress",EPSstatsFlags.EMPTY) );

		RegisterStat(EPlayerStats_ALP.SKILL_REPUTATION, new PlayerStat<int>(-64,64,0,"LevelReputation",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.SKILL_REPUTATIONPROGRESS, new PlayerStat<float>(-999999999,999999999,0,"LevelReputationProgress",EPSstatsFlags.EMPTY) );
		
		RegisterStat(EPlayerStats_ALP.COUNTPLAYERS, new PlayerStat<int>(0,999999999,0,"CountPlayers",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.COUNTZOMBIES, new PlayerStat<int>(0,999999999,0,"CountZombies",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.COUNTANIMALS, new PlayerStat<int>(0,999999999,0,"CountAnimals",EPSstatsFlags.EMPTY) );
		RegisterStat(EPlayerStats_ALP.COUNTSKINNED, new PlayerStat<int>(0,999999999,0,"CountSkinned",EPSstatsFlags.EMPTY) );
		
		RegisterStat(EPlayerStats_ALP.TIREDNESS, new PlayerStat<float>(0, 100, 100, "Tiredness", EPSstatsFlags.EMPTY));
		
		RegisterStat(EPlayerStats_ALP.CURRENT_SCORE, new PlayerStat<float>(-999999999,999999999,0,"CurrentScore",EPSstatsFlags.EMPTY) );
	}	
};

class PlayerStatsALP
{
	
	ref PlayerStatsPCO_Base			m_PCO_base = new PlayerStatsND();

	Man m_Player;

	void PlayerStatsALP(Man player)
	{
		Init(player);
	}

	void Init(Man player)
	{
		m_Player 		= player;
	}

	PlayerStatsPCO_Base GetPCO()
	{
		return m_PCO_base;
	}
	
	void ~PlayerStatsALP()
	{
		
	}
	
	
	PlayerStatBase GetStatObject(int id)
	{
		PlayerStatsPCO_Base pco = GetPCO();
		if ( pco )
		{
			return pco.GetStatObject(id);
		}
		else
		{
			return null;
		}
	}
	


	
	void SaveStats( ParamsWriteContext ctx )
	{

		PlayerStatsPCO_Base pco = GetPCO();
		
		if ( pco )
		{
			pco.OnStoreSave(ctx);

		}
		else
		{
			return;
		}
	}

	bool LoadStats( ParamsReadContext ctx, int version )
	{
		PlayerStatsPCO_Base pco = GetPCO();
		if (pco && pco.OnStoreLoad(ctx))
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}


}