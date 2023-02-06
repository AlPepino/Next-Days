class alpServerMessageTemplate 
{
	int 				Type;					//0-1 server message, 2 personal message sending player OnConnect event
	string				Message;				//message
	ref array<int>		Time = new array<int>;	//HH:MM:SS
	int					Loop		= 0;		//count of loop, -1 = infinity, 0 = just once, x = x+1 loops
	int					LoopTime	= 0;		//time beetween loops
	
	
	void alpServerMessageTemplate(int type, string text, ref array<int> time, int loop, int looptime)
	{
		Type=type;
		Message=text;
		Time=time;
		Loop=loop;
		LoopTime=looptime;
	}
}

