// Script File


modded class IngameHud extends Hud
{

	
	//------------------------------------------------------------------------------------------------------ 				
   	//clan;
	float												alp_TimeUpdateIcon;

	int alp_NICK_DISTANCE;

//-------------------------------------------------------------------------------------------------------------- 	
//***************************//
//Override default HUD function
//***************************//		

		
	override void Update( float timeslice )
	{
		super.Update( timeslice );


		

		//clan members icon
		
		alp_TimeUpdateIcon += timeslice;
		if (alp_TimeUpdateIcon > 0.05 )
		{
			ShowMembersIcon();
			alp_TimeUpdateIcon = 0;
		}
	
	}	
	
	

	
//-------------------------------------------------------------------------------------------------------------- 	
//***************************//
//Clan 
//***************************//	
			
	
	ref map<int,ref alpMemberIcon> 	alp_MemberIcons		= new map<int,ref alpMemberIcon>;
	
	//------------------------------------------------------------------------------------------------------ 				   		
	//clan
	void HideAllIcons()
	{
		foreach( alpMemberIcon icon : alp_MemberIcons)
		{
			icon.Show( false, 0,0, 0);
		}
	}
	
	
	void ShowMembersIcon()
	{
		HideAllIcons();
		
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		
		if ( player && player.GetRP().GetClientData().ShowPlayersIcontem )
		{
			alpClanData clan = player.GetRP().GetClan();
			
			bool inTraderZone = player.GetSyncData().GetElement( alpRPelements.ISINTRADERZONE ).GetValue();
			
			if ( clan || inTraderZone )
			{
				float view = GetND().GetClans().GetOptions().ShowIconDistance;
	
				alp_NICK_DISTANCE = GetND().GetClans().GetOptions().ShowNickDistance;
				
				if ( player.IsInOptics() ) 
				{
					
	
					EntityAI entityInHands = player.GetItemInHands();
					
					ItemOptics optic;
					
					if ( entityInHands	&& entityInHands.IsInherited(ItemOptics) )
					{
						optic = ItemOptics.Cast(player.GetItemInHands());
					}
					else if ( entityInHands	&& entityInHands.IsInherited(Weapon) )
					{
						optic = ItemOptics.Cast( Weapon.Cast( entityInHands ).GetAttachedOptics() );
					}
	
					if ( optic )
					{
						float viewInOptic = optic.GetZeroingDistanceZoomMax();						
						view = Math.Max( viewInOptic , view );
						float nickDistanceInOptic = view / 2;
						
						alp_NICK_DISTANCE = Math.Max( nickDistanceInOptic, alp_NICK_DISTANCE);
						
					}					
					
				}
				
				foreach( Man man : ClientData.m_PlayerBaseList )
				{
					PlayerBase member;
					if (Class.CastTo(member,man) && member.IsPlayer() && member.IsAlive() && member.GetIdentity() && !member.IsInVehicle()  && member != player ) //not controlled player
					{	
						//vector mypos = GetGame().GetCurrentCameraPosition();					
						vector mypos = player.GetPosition();
						vector pos   = member.GetPosition();
						float dist = vector.Distance( mypos, pos );
						
				
						int memberID = member.GetPlayerID();	
												
						if ( clan && clan.IsMember(memberID) )
						{					
							
							if ( dist <= view)
							{	
								SetPlayerIconALP(member, dist, view );
							}					
						}
						else
						{
						
							if ( inTraderZone && GetND().GetClans().GetOptions().ShowIconsInTradeZone )
							{
								
								
								if ( dist < 20 )
								{						
									SetPlayerIconALP(member, dist, 20 , true );							
							
								}
		
							}
						}
					}
				}	
							
		
			
			}
	
		}
		

	}


	protected void SetPlayerIconALP(PlayerBase player, float dist, float view, bool nofade = false )
	{
		int playerID = player.GetPlayerID();
		string name  = player.GetIdentity().GetName();
		
		float colorCoef;
		int colorA;

		
		bool head = dist < alp_NICK_DISTANCE;
		vector partPos;
		int indexPart
		if ( head )
		{
			indexPart = player.GetBoneIndexByName( "Head" );
			partPos = player.GetBonePositionWS( indexPart );		
		}
		else
		{
			indexPart = player.GetBoneIndexByName( "Spine3" );
			partPos = player.GetBonePositionWS( indexPart );		
		}
						

		vector screnPos = GetScreenPosALP( partPos );
		if (screnPos != vector.Zero )
		{
			int a = GetND().GetClans().GetOptions().ClanMemberIconColor[0];
			int r = GetND().GetClans().GetOptions().ClanMemberIconColor[1];
			int g = GetND().GetClans().GetOptions().ClanMemberIconColor[2];
			int b = GetND().GetClans().GetOptions().ClanMemberIconColor[3];
			
			if ( !nofade )
			{
				colorCoef = 1 - dist / ( view + 0.01 );
				
				//Print("KOEF " + colorCoef );
				
				colorCoef = Math.Clamp( colorCoef, 0 , 1 );

				
				a = colorCoef * ( a * 0.7) + 0.3 *  a;		

			}
			
			colorA = ARGB( a , r, g, b );
			
			
			//bod or nick
			//bool nick = dist < alp_NICK_DISTANCE;
			
			alpMemberIcon icon;						
			
			float offset = 0;
			
			if ( head )
			{
			 offset = 30;
			}
		
			
			if ( alp_MemberIcons.Find( playerID, icon ) )
			{

				icon.Show( true , (screnPos[0] - offset),  screnPos[1] , colorA, head);
			}
			else
			{
				icon = new alpMemberIcon( name, colorA );
				icon.Show( true , (screnPos[0] - offset ),  screnPos[1] , colorA, head);//25
				alp_MemberIcons.Set( playerID, icon );								
				
			}
													
		}	
		
	}
	
		
	protected vector GetScreenPosALP(vector pWorldPos)
	{
		//int parent_width, parent_height;
		vector screenPosAbs, screen_pos;
		
		//! get relative pos for screen from world pos vector
		screen_pos = GetGame().GetScreenPosRelative( pWorldPos  + "0 0.3 0");
		
		if( screen_pos[0] >= 1 || screen_pos[0] == 0 || screen_pos[1] >= 1 || screen_pos[1] == 0 || screen_pos[2] < 0) return vector.Zero;
		
 		screenPosAbs = GetGame().GetScreenPos( pWorldPos  + "0 0.3 0");
		
		return screenPosAbs;
	}	
	
	
}


class alpMemberIcon
{
	Widget 					alp_Icon;
	TextWidget				alp_PlayerNameText;
	Widget					alp_PlayerBod;
	string					alp_PlayerName;	
	int 					alp_Color;
	
	void alpMemberIcon(string name, int color )
	{

		alp_Icon = GetGame().GetWorkspace().CreateWidgets( "ND_Clans/gui/layouts/PlayerIcon.layout" );			
		
		Class.CastTo(alp_PlayerNameText, alp_Icon.FindAnyWidget("PlayerName"));
		
		Class.CastTo(alp_PlayerBod, alp_Icon.FindAnyWidget("PlayerBod"));
		
		
		if (name.Length() > 6 ) 
		{
			name = name.Substring(0,5) + ".";
		}			
		alp_PlayerName = name;
		alp_Color = color;
		
		alp_PlayerNameText.SetText( name );
		alp_PlayerNameText.SetColor(color);
				
		alp_PlayerBod.SetColor(color);
	}
	void ~alpMemberIcon()
	{
		if ( alp_Icon )
		{
			alp_Icon.Unlink();
		}	
	}
		
	
	
	void Show(bool state, float x, float y , int color, bool nick = true)
	{
		alp_Icon.SetPos(x,y);
		alp_Icon.Show(state );
		
		
		alp_PlayerNameText.Show(nick );
		alp_PlayerBod.Show(!nick );
		
		alp_PlayerNameText.SetColor(color);
		alp_PlayerBod.SetColor(color);
		
	}

}
