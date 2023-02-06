enum alpMOST_WANTED
{
	BANK,
	PLAYER,
}

class alpMostWanted 
{
	int alp_From;
	int alp_PlayerID;
	int alp_Currency;
	int alp_Reward;
	string alp_Name;
	string alp_Title;
	vector alp_RealVector;
	vector alp_AdjustedVector;
	string alp_Icon;
	
	int alp_TimeStamp;
	
	void alpMostWanted(int from, int playerid,int currency, int reward, string name, string title, vector position,vector position2, string icon = "")
	{
		alp_From = from;
		alp_PlayerID = playerid;
		alp_Currency = currency;
		alp_Reward = reward;
		alp_Name = name;
	 	alp_Title = title;
	 	alp_RealVector = position;
	 	alp_AdjustedVector = position2;
	 	alp_Icon = icon;
		
		alp_TimeStamp = g_Game.GetTime();
	}
	
	int GetTime()
	{
		return alp_TimeStamp;
	}
	
	vector GetPostition()
	{	
		return alp_AdjustedVector;
	}
	vector GetRealPostition()
	{	
		return alp_RealVector;
	}	
	string GetTitle()
	{
		return alp_Title;
	}
	string GetName()
	{
		if ( alp_Reward )
		{
			string name;
			
			name = 	alp_Name + " (" + NumberToString( alp_Reward, 1 ) + ")";
			return name;
		}
		else
		{		
			return alp_Name;
		}
		
		
	}	
	string GetIcon()
	{
		return alp_Icon;
	}	
	
	string NumberToString(float value, int k = 1000)
	{
		int 			v 		= value* k ;		
		string 			text 	= v.ToString();
		int 			len 	= text.Length();
		string 			output  = "";
		int				s=0;
		len -=1;
		for (int i=len; i>=0;i--){
			
			if (s==3 || s==6 || s==9){
				output = text.Get(i) + " " + output;
			}
			else output = text.Get(i) + output;
			s++;
		}
		return output;
	}		
}