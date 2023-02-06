enum alpRPelements
{
	STAMINA,
	RAD_RESIST,
	TOXIC_RESIST,
	REPUTATION,
	REPUTATION_ROLE,
	HUNTING,
	ISINTRADERZONE,
	ISALLOWDAMAGE,
	ISRAINED,
	DISEASES,	
	TDCY_TIREDNESS,
	COUNT
}

class alpStatsBase
{
	int 	alp_Value;

	
	int		alp_Range;
	
	int		alp_Type;
	
	int		NUM_OF_BITS;
	
	PlayerBase alp_Player;
	
	void alpStatsBase(PlayerBase player)
	{
		alp_Player = player;
		
	}
	
	void Update()
	{
		
	
	}
	
	
	int GetNumberOfBits()
	{
		return NUM_OF_BITS;
	}	
	
	void SetValue(int value)
	{
		alp_Value = value;
	}	
	
	int GetValue()
	{
		if (GetGame().IsServer() )
		{
			Update();
		}
		
		return alp_Value;
	}
	int GetRange()
	{
		return alp_Range;
	}
	
	
	int GetCompareMask()
	{
		int mask = Math.Pow(2, GetNumberOfBits() ) - 1;
		return mask;
	}	
	
	int GetType()
	{
		return alp_Type;
	}	
}


