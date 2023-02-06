//Alpepino usefull function
//-------------------------

modded class alpUF
{
	//tirednes fce
	
	static float GetTirednessMetabolicSpeed(int movement_speed)
	{
		float speed;
		//PrintString(movement_speed.ToString());
		switch (movement_speed)
		{
			case 1:
			{
				speed = GetND().GetRP().GetFatigue().FatigueWalk;
				break;
			}
			case 2:
			{
				speed = GetND().GetRP().GetFatigue().FatigueJog;
				break;
			}
			case 3:
			{
				speed = GetND().GetRP().GetFatigue().FatigueSprint;
				break;
			}
			default:
			{
				speed = 0;
				break;
			}
		}
		speed += GetND().GetRP().GetFatigue().FatigueBasal;
		return speed;	
	
	}
};
//end Alpepino usefull function
//-------------------------