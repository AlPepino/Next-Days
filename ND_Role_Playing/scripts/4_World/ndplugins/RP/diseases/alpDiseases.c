


class alpDisease
{
	PlayerBase alp_Player;
	protected int alp_ID;
	protected bool alp_Enable;
	protected bool alp_CanBeCured;
	
	protected string alp_Name;
	
	protected string alp_Icon;
	
	void alpDisease(PlayerBase player, int id, string name, bool show, bool state, string icon)
	{
		alp_Player = player;
		alp_ID = id;
		alp_Name = name;
		alp_Enable = show;
		alp_CanBeCured = state;	
		alp_Icon = icon;
		
	}
	

	
	int GetID()
	{
		return alp_ID;
	}
	
	void CureDisease()
	{
	
	}
	
	bool IsInfected()
	{
		return alp_Player.GetRP().IsInfected(alp_ID);
	}
	
	bool IsEnable()
	{
		return alp_Enable;
	}
	bool CanBeCured()
	{
		return alp_CanBeCured;
	}	
	
	float GetFee()
	{
		return 0;
	}
	
	
	float GetPrice()
	{
		
		float price = GetFee();
	
		return price;
	}
	
	string GetName()
	{
		return alp_Name;
	}
	
	string GetIcon()
	{
		return alp_Icon;
	}
}



class alpFever extends alpDisease
{

	override void CureDisease()
	{
	
	}
}




