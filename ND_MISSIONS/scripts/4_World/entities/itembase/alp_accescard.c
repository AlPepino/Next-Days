
class alp_AccessCard_Base extends ItemBase
{
	int GetKeyID(){
		int value = 0;
		string subclass_path = "CfgVehicles " + GetType() + " keyid";
		value = GetGame().ConfigGetInt(subclass_path);		
		return value;
	}
	
	
	

}
class alp_AccessCardRed extends alp_AccessCard_Base {}
class alp_AccessCardBlue extends alp_AccessCard_Base {}
class alp_AccessCardGreen extends alp_AccessCard_Base {}
class alp_AccessCardYellow extends alp_AccessCard_Base {}