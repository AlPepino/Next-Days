enum alpPROTECTION
{
	BIOLOGICAL=1,//DEF_BIOLOGICAL
	CHEMICAL=2,//DEF_CHEMICAL,
	RADIATION,
}


modded class ItemBase
{
	protected bool 	alp_IsMissionObject = false;
	
	ref alpProtectionBonuses alp_ProtectionBonuses;
	

	
	void ItemBase()
	{
		RegisterNetSyncVariableInt(	"m_AttachedAgents"); //agent to client
		
	
	}	
	
	void ~ItemBase()
	{
		if ( GetGame() && GetGame().IsServer() ) {
			
			
			PlayerBase player = PlayerBase.Cast( GetHierarchyRootPlayer() );
			
			if ( player ) {
				int id = GetID();
				int flags = GetAgents();
				
				player.RemoveContaminedItem(id);
			}
				
		}	
	
	}	
	
	
#ifdef NAMALSK_SURVIVAL		
	override void SetWet(float value, bool allow_client = false)
	{
		if ( !IsServerCheck(allow_client) )
			return;

		float min = GetWetMin();
		float max = GetWetMax();

		if ( max > 1.9 ) {
			int liquid_type = GetLiquidType();	
			if ( liquid_type == LIQUID_VODKA || liquid_type == LIQUID_GASOLINE ) {
				max = 1.9;
			}				
		}
			
		float previousValue = m_VarWet;
		
		m_VarWet = Math.Clamp(value, min, max);
		
		//UpdateWeight();
		
		if ( previousValue != m_VarWet )
			SetVariableMask(VARIABLE_WET);
	}	
#endif

	
	string GetServerWorldID()
	{
		return GetNetworkIDString();
	}
	
	bool CanBeDiggedAlp()
	{
		return false;
	}

	override bool CanBeRepairedToPristine()
	{
		if ( GetND().GetRP().GetPlayerOptions().ItemsCanBeRepairedToPristine )
			return true;
		else
			return super.CanBeRepairedToPristine();
	}	
	
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );

		if (CanBeMissionObject() && !IsItemTent() )
		{
        	ctx.Write( alp_IsMissionObject );
		}
	}	

	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( super.OnStoreLoad( ctx, version ) )
		{
		
			if ( ! GetND().IsFirstRun() && CanBeMissionObject() && !IsItemTent() )
			{//new format
				ctx.Read( alp_IsMissionObject );	
				return true;
			}				
			
			
			return true;
		}
		else return false;
	}		
	
	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();	
		
		if ( ! GetND().IsFirstRun() && CanBeMissionObject() && IsMissionObject()  && GetHierarchyRootPlayer() == NULL)
		{	
			GetGame().ObjectDelete( this );
		}		
				
		if ( GetND().IsFirstRun() && ( !CanBeMissionObject() || IsItemTent() ) )
		{
			SetMissionObjectState( false );
			SetSynchDirty();
			
		}
				
	}	
	

	override void EEInventoryIn (Man newParentMan, EntityAI diz, EntityAI newParent)
	{
		super.EEInventoryIn(newParentMan, diz, newParent);
		
		if ( GetGame().IsServer() ) {

			PlayerBase player = PlayerBase.Cast( newParentMan );
			ItemBase itm = ItemBase.Cast(diz);
			if ( player &&  player.GetRP().IsRadiationHigh() &&  itm &&  !( itm.GetAgents() & alpeAgents.RADIATION ) )
			{//not attachet 
				itm.InsertAgent(alpeAgents.RADIATION,1);
				itm.SetSynchDirty();									
			}
			if ( player && itm && ( itm.GetAgents() & alpeAgents.RADIATION ) ) {
				//Print("Je kontaminovano "  + GetType() + " ID " + GetID() );
				player.AddContaminedItem(GetID());
			}	

		}
		
	
	}
	
	override void EEInventoryOut (Man oldParentMan, EntityAI diz, EntityAI newParent)
	{
		super.EEInventoryOut(oldParentMan, diz, newParent);
		
		if ( GetGame().IsServer() ) {
			ItemBase itm = ItemBase.Cast(diz);
			

			PlayerBase player = PlayerBase.Cast( oldParentMan );
			if ( player && itm && ( itm.GetAgents() & alpeAgents.RADIATION ) ) {
				player.RemoveContaminedItem(GetID());
			}				
		}

	}	


	override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner)
	{
		super.OnItemLocationChanged(old_owner, new_owner);
		
		if (alp_IsMissionObject) {
			SetMissionObjectState( false );		
		} else {
			if ( old_owner ) {
				PlayerBase pold = PlayerBase.Cast( old_owner.GetHierarchyRootPlayer() );
				if ( pold && GetND().GetMS().GetOptoinsTrader().DeleteDroppedItem && pold.GetRP().IsInTradeZone() && !new_owner ) {
					SetMissionObjectState( true );
					SetLifetime(3);										
				}			
			
			}

		}
			
	}
	
		
	bool IsMissionObject()
	{
		return alp_IsMissionObject;
	}

	bool CanBeMissionObject()
	{
		return true;
	}	
		
	void SetMissionObjectState(bool state)
	{

		alp_IsMissionObject	= state;
		SetSynchDirty();
	}
		
	override float GetProtectionLevel(int type, bool consider_filter = false, int system = 0)
	{	

		if ( consider_filter && GetInventory().GetAttachmentSlotsCount() != 0 )//is it an item with attachable filter ?
		{
			ItemBase filter = ItemBase.Cast(FindAttachmentBySlotName("GasMaskFilter"));
			if (filter )
			{
				return filter.GetProtectionLevel(type, true, system);//it's a valid filter, return the protection
			}
			else return 0;//otherwise return 0 when no filter attached
		}
								
									
		if  ( IsDamageDestroyed() ) 
		{
			return 0;
		}		

		if  ( consider_filter && HasQuantity() && GetQuantity() <= 0 ) 
		{
			return 0;
		}
		

		if  ( consider_filter && HasQuantity() && GetQuantity() > 0 ) 
		{
			if ( GetProtectionBonuses().GetFilterEfficiency() )			
				return GetProtectionBonuses().GetFilterEfficiency();
			else
				return 1;
		}	
				
		
		return GetProtectionBonuses().GetProtection( type );;
	}
	


	bool HasDosimeter()
	{
		string subclass_path = "CfgVehicles " + this.GetType() + " Protection hasdosimeter";
		return GetGame().ConfigGetInt(subclass_path);
	}
	
	alpProtectionBonuses GetProtectionBonuses()
	{
		if ( GetGame().IsClient() && !GetND().GetMS().IsInitCompleted() )
		{
			GetND().GetMS().AddSyncCallEventOnConnect( this , "SyncClientEventOnConnect" );
		}		
		
		if (!alp_ProtectionBonuses)
		{
			alp_ProtectionBonuses = alpProtectionBonuses(this);
		}
		return 	alp_ProtectionBonuses;
	}
	void SyncClientEventOnConnect()
	{
		alp_ProtectionBonuses = alpProtectionBonuses(this);
	}		
	
	ref alpTraderItemConfig alp_TraderItemConfig;
	
	alpTraderItemConfig GetTraderItemConfig()
	{
		//kontorla existence v input od uzivatele
		
		
		//default z configu
		if ( !alp_TraderItemConfig)
		{
			alp_TraderItemConfig = alpTraderCoreBase.GetTraderItemConfig( GetType() );
			
			if (!alp_TraderItemConfig )
			{
				alp_TraderItemConfig = new alpTraderItemConfig( GetType(), 0, 0,0 ,0, 0, 0, 0);
			}
			
			/*
			bool canBuy, canSell;
			int category, price, requiredReputation;
			float ratioSelling,ratioBuying;
			
			string subclass_path = "CfgVehicles " + GetType() + " TraderItem CategoryID";	
			category = GetGame().ConfigGetInt(subclass_path);
			
			subclass_path = "CfgVehicles " + GetType() + " TraderItem Price";	
			price = GetGame().ConfigGetInt(subclass_path);
			
			subclass_path = "CfgVehicles " + GetType() + " TraderItem CanBuy";	
			canBuy = GetGame().ConfigGetInt(subclass_path);
			
			subclass_path = "CfgVehicles " + GetType() + " TraderItem CanSell";	
			canSell = GetGame().ConfigGetInt(subclass_path);						
			
			subclass_path = "CfgVehicles " + GetType() + " TraderItem RequiredReputation";	
			requiredReputation = GetGame().ConfigGetInt(subclass_path);		
			
			subclass_path = "CfgVehicles " + GetType() + " TraderItem SellingBonusReputationRatio";	
			ratioSelling = GetGame().ConfigGetFloat(subclass_path);			
			
			subclass_path = "CfgVehicles " + GetType() + " TraderItem BuyingPenaltyReputationRatio";	
			ratioBuying = GetGame().ConfigGetFloat(subclass_path);		
			
			alp_TraderItemConfig = new alpTraderItemConfig( GetType(), category, price,canBuy ,canSell, requiredReputation, ratioSelling, ratioBuying);
			*/
		}
		
	
		return alp_TraderItemConfig;
	}



	int GetDefaultPrice(bool includeAtt = false, array<string> allowedAtt = null )
	{
		int price = 0;
		alpTraderItemConfig config = GetTraderItemConfig();		
		if ( !config || ( !config.CanBuy &&  !config.CanSell ) || (includeAtt && (!allowedAtt  || allowedAtt.Find(GetType()) < 0 ) ) )
		{

			return price;
		}

		if (IsMagazine())
		{

			price = GetAmmmoPrice( config.Price );	
			
		}
		else if ( IsWeapon() )//jeste povoleni?
		{
			if ( includeAtt && allowedAtt )
			{
				price =  config.Price + GetWeaponPrice( allowedAtt );
			}
			else
			{
				price =  config.Price;
			}
		}
		else if ( IsPeltBase() && !CanBeSplit() )	
		{		
			price = config.Price;
		}	
		else if ( HasFoodStage()  )
		{		
			price = (int) config.Price * GetFoodStageRatio() * ( GetQuantity() / GetQuantityMax() );
		}		
		else if ( GetLiquidType() && HasQuantity() )
		{		
			price = (int) config.Price + GetLiquidPrice();
		}
		else if ( IsInherited( Box_Base ) )
		{			
			price = GetBoxBasePrice();
		}	
		else if ( CanBeSplit() )
		{				
			price = config.Price * GetQuantity();
		}
		else if ( HasQuantity() )
		{			
			price = config.Price * GetQuantity() / GetQuantityMax();
		}						
		else
		{
		
			price = config.Price;

		}
		
		

		
		
		price = (int) price * GetHealthLevelALP();
	
		
		return price;
	}
	
	int GetWeaponPrice(  array<string> allowedAtt )
	{
		int price = 0;
		
		Weapon_Base wep = Weapon_Base.Cast( this );
		
		if ( wep )
		{
			autoptr array<EntityAI> itemsArray = new array<EntityAI>;
			ItemBase item;
			
			wep.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			
			for (int i = 0; i < itemsArray.Count(); i++)
			{				
				item = ItemBase.Cast(itemsArray.Get(i));
				
				if ( item && item != this && allowedAtt.Find( item.GetType() ) != -1 )
				{
					price += item.GetDefaultPrice();
				}
			}		
		}
		
		return price;
	}		
	
	int GetBoxBasePrice()
	{
		string path = "CfgVehicles " + GetType();
		string child_name = "";
		int count;
		array<string> resources = new array<string>;
			
		if( GetGame().ConfigIsExisting( path ) && GetGame().ConfigIsExisting( path + " Resources") )
		{
			path = path + " Resources";
			count = GetGame().ConfigGetChildrenCount ( path );
			for (int i = 0; i < count; i++)
			{
				GetGame().ConfigGetChildName ( path, i, child_name );
				
				if ( GetGame().ConfigGetInt( path + " " + child_name + " value" ) )
				{
					resources.Insert( child_name );
				}
			}			
			string itemType = resources.Get(0);
			int itemCount = GetGame().ConfigGetInt( path + " " + itemType + " value" );
		}
		
		alpTraderItemConfig config = alpTraderCoreBase.alp_AllItemsByName.Get( GetType() );
		
		int price = config.Price * itemCount;	
		
		return price;
	}

	float GetFoodStageRatio()
	{
		float ratio = 1;		
		Edible_Base food = Edible_Base.Cast(this);
		
		if ( food && food.HasFoodStage() )
		{
			int stage = food.GetFoodStageType();
			switch ( stage )
			{
				case FoodStageType.RAW:
					ratio = GetND().GetMS().GetOptoinsTrader().FoodRaw;
				break;
				case FoodStageType.BAKED:
					ratio = GetND().GetMS().GetOptoinsTrader().FoodBaked;
				break;
				case FoodStageType.BOILED:
					ratio = GetND().GetMS().GetOptoinsTrader().FoodBoiled;
				break;
				case FoodStageType.DRIED:
					ratio = GetND().GetMS().GetOptoinsTrader().FoodDried;
				break;
				case FoodStageType.BURNED:
					ratio = GetND().GetMS().GetOptoinsTrader().FoodBurned;
				break;
				case FoodStageType.ROTTEN:
					ratio = GetND().GetMS().GetOptoinsTrader().FoodRotten;
				break;																														
			}					
		}
				
		return ratio;
	}	
	
	int GetLiquidPrice()
	{
	 	int price = 0;
		int type = GetLiquidType();
		
		if ( type )
		{
			float quantity = GetQuantity();
			
			float value;
			
			if ( GetND().GetMS().GetOptoinsTrader().LiquidPricelist.Find( type, value ) )
			{
				price = (int) (value * quantity) ;							
			}		
		}
		return price;
	}	
	int GetAmmmoPrice(int magPrice)
	{
		int price = 0;
		if (IsMagazine())
		{
			
			alpTraderItemConfig config; // = alpTraderCoreBase.GetTraderItemConfig( GetType() );
			
			
			Magazine_Base mag = Magazine_Base.Cast(this);

			int ammo = mag.GetAmmoCount();
			
			if ( !mag.IsAmmoPile() )
			{				
				
				config = alpTraderCoreBase.GetTraderItemConfig( GetAmmoClassName() );						
			}
			else
			{
				config = GetTraderItemConfig();
				magPrice = 0;
			}
			
			if ( config )
			{				
				price = (int) magPrice + config.Price * ammo;
			}
			
		}			
		return price;
	}	
	
	string GetAmmoClassName()
	{
		string name;
		array<string> ammo_array = new array<string>;		
		ConfigGetTextArray ("ammoItems", ammo_array);
		if (ammo_array.Count() > 0)
		{
			//kontrola, zda predmet existuje
			for(int i = 0; i < ammo_array.Count();i++)
			{
				name = ammo_array.Get(i);

				if ( GetGame().IsKindOf( name, "Ammunition_Base" ) )
				{
					break;
				}								
			}						
		}
		return name;
	}	
	float GetHealthLevelALP()
	{
		float level = 1;
		
		switch (GetHealthLevel())
		{
			case 1:
			{
				level = 0.75;
				break;
			}
			case 2:
			{
				level = 0.50;
				break;
			}			
			case 3:
			{
				level = 0.25;
				break;
			}
			case 4:
			{
				level = 0;
				break;
			}			
		}
		return level;
	}
	float GetQuantityALP()
	{

		if (IsMagazine())
		{
			float ratio;
			Magazine_Base mag = Magazine_Base.Cast(this);

			if ( !mag.IsAmmoPile() )
			{
				ratio = mag.GetAmmoCount() / mag.GetAmmoMax();
				
				
				return ratio;
			}
			else
			{
				ratio = mag.GetAmmoCount() / mag.GetAmmoMax();
				return ratio;
			}
		}		
		
				
		if (HasQuantity())				
		{
			float quantity = GetQuantity() /GetQuantityMax();
			
			/*
			if (IsBottleBaseALP() && GetND().GetMS().GetOptoinsTrader().WaterHasNoValue &&   GetLiquidType() == LIQUID_WATER )
			{			
				quantity = 0;
			}
			*/
			return quantity;
		}
				
		return 1;
	}
	
	
	int GetAttachmentCountALP()
	{
		return GetInventory().AttachmentCount();
	}
	
	int GetCargoCountALP()
	{
		int cargo = 0;
		
		if ( HasAnyCargo() )
			cargo = GetInventory().GetCargo().GetItemCount();		
		
		return cargo;
	}
	
	
	string GetNameALP()
	{		
		string name = GetType()+ "_"  + GetAttachmentCountALP().ToString() + "_"  + GetCargoCountALP().ToString() + "_"  + GetQuantityALP().ToString() + "_" + GetHealthLevelALP().ToString() + "_" + GetLiquidType().ToString() + "_" + GetFoodStageRatio().ToString();
		return name;
	}		
	
}