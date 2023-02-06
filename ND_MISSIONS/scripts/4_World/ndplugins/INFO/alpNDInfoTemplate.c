
class alpISitem
{
	ref array<string>						Menu			= new array<string>;
	ref array<ref array<string>>			Text 			= new array<ref array<string>>;
}

class alpInfoSitesTemplate
{
	int										LanID 			= 0;
	int										MenuID 			= 0;
	//float									Version         = 0.1;
	ref array<string>						Language 		= new array<string>;
	ref array<string>						Button1 		= new array<string>;
	ref array<string>						Button2 		= new array<string>;
	ref array<string>						Button3 		= new array<string>;
	ref array<string>						Button4 		= new array<string>;
	ref array<string>						Button5 		= new array<string>;
	ref array<ref alpISitem>				Items			= new array<ref alpISitem>;

}


class alpInfoSitesTemplateInput
{
	//float									Version         = 0.1;
	ref array<string>						Language 		= new array<string>;
	ref array<string>						Button1 		= new array<string>;
	ref array<string>						Button2 		= new array<string>;
	ref array<string>						Button3 		= new array<string>;
	ref array<string>						Button4 		= new array<string>;
	ref array<string>						Button5 		= new array<string>;
	ref array<ref alpISitem>				Items			= new array<ref alpISitem>;

}