
class alpBuildingLabels
{
	//static vector CameraPosition;
	
	static int LAST_COLOR;
	
	static float TerritoryRadius;
	
	static int COLOR_SELECTED = COLOR_GREEN;
	
	static int COLOR_DESELECTED = ARGB(255,255,255,255);
	
	static ref array<Widget> alp_Labels;
	static ref map<int,Widget> alp_LabelsSelecet;
	
	static ref array<Widget> alp_Borders;
	static ref array<vector> alp_BordersVectors;
	
	
	static ref array<vector> alp_Vectors;

	static void AddItem(int id, string label, vector pos, bool bought = false)
	{
		Widget root = 	GetLabelPanel();
		
		SetPosition(root, pos);
		SetLabel(root, id, label, bought);
		
		if (!alp_Labels)
		{
			alp_Labels = new array<Widget>;
			alp_Vectors = new array<vector>;
			
		}
		
		alp_Labels.Insert( root );
		alp_Vectors.Insert( pos );
	}
	
	static void ClearLabels()
	{
		int i;
		if 	( alp_Labels )
		{
			for( i = 0; i < alp_Labels.Count() ; i++)
			{
				alp_Labels.Get(i).Unlink();
			}
			
			alp_Labels.Clear();			
			alp_Vectors.Clear();	
			alp_LabelsSelecet.Clear();			
		}
		
		if 	( alp_Borders )
		{
			for(i = 0; i < alp_Borders.Count() ; i++)
			{
				alp_Borders.Get(i).Unlink();
			}
			
			alp_Borders.Clear();	
			alp_BordersVectors.Clear();						
		}		
		TerritoryRadius = 0;
	}
	
	static void ClearBorders()
	{
		int i;
		if 	( alp_Borders )
		{
			for(i = 0; i < alp_Borders.Count() ; i++)
			{
				alp_Borders.Get(i).Unlink();
			}
			
			alp_Borders.Clear();						
		}	
		
		alp_Borders = new array<Widget>;		
		alp_BordersVectors = new array<vector>;
	}
	
	
	static Widget GetLabelPanel()
	{
		Widget root = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/BuildingIcon.layout");

		
		return root;	
	}
	static Widget GetBorderSign()
	{
		Widget root = GetGame().GetWorkspace().CreateWidgets("ND_Clans/gui/layouts/TerritoryBorder.layout");

		
		return root;	
	}
	
	static void SetPosition(Widget w, vector pos)
	{
		vector screen_pos = GetGame().GetScreenPos( pos );

		float x,y;
		x = screen_pos[0];
		y = screen_pos[1];		
		w.SetPos(x,y);
	}
	
	static void SetLabel(Widget w, int id, string label, bool bought)
	{
		TextWidget text = TextWidget.Cast(  w.FindAnyWidget("Label") );
		
		text.SetText( label );
		
		if (bought)
		{	
			Widget.Cast( w.FindAnyWidget("Selected") ).SetColor( COLOR_AVAILABLE_POSITIVE );						
		}	
		else
		{
			Widget.Cast( w.FindAnyWidget("Selected") ).SetColor( COLOR_UNAVAILABLE );	
		}	
		
		if (!alp_LabelsSelecet)
			alp_LabelsSelecet = new map<int,Widget>;
		
		alp_LabelsSelecet.Set( id, Widget.Cast( w.FindAnyWidget("Selected") ));		
	}	
	
	
	static void SelectLabel(int id )
	{
		Widget label = alp_LabelsSelecet.Get(id);
		
		LAST_COLOR = label.GetColor();
		
		if (label)
		{
			label.SetColor( COLOR_RED );		
		}
	
	}
	static void UnSelectLabel(int id )
	{
		Widget label = alp_LabelsSelecet.Get(id);
		
		if (label)
		{
			label.SetColor( LAST_COLOR );		
		}
	
	}	
	
	
	static void Update()
	{
		int i;
		if 	( alp_Labels )
		{
			for(i = 0; i < alp_Labels.Count() ; i++)
			{
				
				SetPosition( alp_Labels.Get(i), alp_Vectors.Get(i));
			}

		}	
		if 	( alp_Borders )
		{
			for(i = 0; i < alp_Borders.Count() ; i++)
			{
				
				SetPosition( alp_Borders.Get(i), alp_BordersVectors.Get(i));
			}

		}		
			
	}
	
	static void SetBorders(float range)
	{
	
		
		
		TerritoryRadius = range;
		
		if ( TerritoryRadius > 0 )
		{
			
			
			PlayerBase player;
			Class.CastTo(player,GetGame().GetPlayer());		
			
	
	

			vector ppPos =  player.alp_PlotPoleManage.GetWorldPosition();
			ClearBorders();
			
			int countPoints = TerritoryRadius * 2 * Math.PI / 5;
			
			float angle 	= 360 / countPoints;
			float angle2 	= 0;
			for (int i = 0; i < countPoints;i++)
			{			
				angle2 = i*angle;				
				vector pos	= vector.Zero;				
				pos[0]= Math.NormalizeAngle(angle2);
				pos = pos.AnglesToVector();	
				pos[0] = pos[0]*TerritoryRadius;

				pos[2] = pos[2]*TerritoryRadius;	
				
				
				
				vector finalPos = ppPos - pos;	
				finalPos[1] = ppPos[1];
				
				Widget bodrder = GetBorderSign();
				
			
				
				//SetPosition(bodrder, finalPos);
				alp_BordersVectors.Insert( finalPos );
				alp_Borders.Insert( bodrder );
			}		
		}
	}
}

