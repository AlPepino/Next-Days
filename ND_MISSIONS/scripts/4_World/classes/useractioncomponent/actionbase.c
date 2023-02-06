

modded class ActionBase : ActionBase_Basic
{	
	bool IsExceptionsALP(EntityAI mask)
	{
	
		string type = mask.GetType();
		
		
		
		int find = GetND().GetRP().GetPlayerOptions().ExceptionsInMask.Find( type );
		
		if ( find >= 0 )
			return true;
		else
			return false;

	}
};