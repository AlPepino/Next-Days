modded class DayZGame extends CGame
{

	// ------------------------------------------------------------
	override string CreateDefaultPlayer()
	{	

		string child_name = super.CreateDefaultPlayer();
		
		if (child_name.Contains("alp_")) child_name.Replace("alp_","");
		
		if (child_name.Contains("Bot")) child_name.Replace("Bot","Survivor");
		
		return child_name;
	}
	
	// ------------------------------------------------------------
	override string CreateRandomPlayer()
	{

		string child_name = super.CreateRandomPlayer();
		
		if (child_name.Contains("alp_")) child_name.Replace("alp_","");
		
		if (child_name.Contains("Bot")) child_name.Replace("Bot","Survivor");
		
		return child_name;		
	}
	
	// ------------------------------------------------------------
	override TStringArray ListAvailableCharacters()
	{

		array<string> char_class_names = super.ListAvailableCharacters();
		array<string> new_char_class_names = new array<string>;
		
		for (int i = 0;i < char_class_names.Count();i++){
			string name = char_class_names.Get(i);
			if (!name.Contains("alp_")) new_char_class_names.Insert(name);			
		}
				
				
		return new_char_class_names;
	}
	
};

