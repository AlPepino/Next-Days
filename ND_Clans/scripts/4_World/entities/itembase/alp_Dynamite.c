class alp_Dynamite extends alp_Dynamite_Base
{
	void alp_Dynamite()
	{
		SetAmmoType("alp_DynamiteExplosion");
		SetFuseDelay(15);
		SetParticleExplosion(ParticleList.EXPLOSION_LANDMINE);  //M67
	}

	void ~alp_Dynamite() {}
}


class alp_Dynamite_Base extends InventoryItemSuper
{
	protected const float DEFAULT_FUSE_DELAY 	= 10;
	protected const string DEFAULT_AMMO_TYPE 	= "Explosion_NonLethal";


	protected ref Timer		m_FuseTimer;
	protected ref Timer		m_DeleteTimer;
	protected float			m_FuseDelay;
	protected float 		m_RemainingFuseTime;
	
	protected bool			m_Pinned;
	protected bool			m_Pinnable;
	protected bool			m_Explodable;
	
	protected EGrenadeType	m_GrenadeType;

	protected string		m_AmmoType;
	
	//! particle
	protected Particle 		m_ParticleExplosion;
	protected int			m_ParticleExplosionId;
	protected vector		m_ParticlePosition;
	
	protected Particle 		m_ParticleIgnited;
	protected vector		m_ParticlePositionKnot;
	
	//! light	
	GrenadeLight			m_Light;

	void Pin()
	{
		if ( !m_Pinned && m_Pinnable )
		{
			OnPin();
		}
	}
	
	void Unpin()
	{
		if ( m_Pinned )
		{
			OnUnpin();
		}
	}		
	
	override void OnActivatedByTripWire()
	{
		Unpin();
	}
	
	bool IsPinned()
	{
		return m_Pinned;
	}
	
	bool IsPinnable()
	{
		//Grenade cannot be pinned once the fuse has started
		if( m_FuseTimer.IsRunning() )
		{
			return false;	
		}
		
		return m_Pinnable;
	}
	
	override bool IsExplosive()
	{
		return true;
	}

	void ActivateImmediate()
	{
		OnActivateImmediate();
	}
	

	
	void SetPinnable(bool state)
	{
		m_Pinnable = state;
	}
	
	void SetFuseDelay(float delay)
	{
		m_FuseDelay = delay;
	}

	void SetAmmoType(string ammo)
	{
		m_AmmoType = ammo;
	}
	
	void SetGrenadeType(EGrenadeType type)
	{
		m_GrenadeType = type;
	}
	
	void SetParticleExplosion(int particle)
	{
		m_ParticleExplosionId = particle;
	}

	//! set position for smoke particle - needs to be in Local Space
	void SetParticlePosition(vector local_pos)
	{
		m_ParticlePosition = local_pos;

		if ( GetHierarchyParent() )
		{
			m_ParticlePosition = GetHierarchyParent().WorldToModel(GetPosition());
		}
	}
	
	void SetParticlePositionKnot(vector local_pos)
	{
		m_ParticlePositionKnot = local_pos;

		if ( GetHierarchyParent() )
		{
			m_ParticlePosition = GetHierarchyParent().WorldToModel(GetPosition());
		}
	}	
	
	EGrenadeType GetGrenadeType()
	{
		return m_GrenadeType;
	}
	
	void Activate()
	{
		if( !m_FuseTimer.IsRunning() )
		{
			//! run only the remaining part (already unpinned and pinned)
			if( m_RemainingFuseTime > 0 )
			{
				//Print("Grenade activated num of seconds to explosion: " + m_RemainingFuseTime);
				m_FuseTimer.Run(m_RemainingFuseTime, this, "OnActivateFinished");
			}
			else
			{
				//Print("Grenade activated num of seconds to explosion: " + m_FuseDelay);
				m_FuseTimer.Run(m_FuseDelay, this, "OnActivateFinished");
			}

		}
	}
	
	protected void Deactivate()
	{
		if( m_FuseTimer.IsRunning() )
		{
			m_RemainingFuseTime = m_FuseTimer.GetRemaining();
			m_FuseTimer.Stop();
			OnDeactivate();
		}
	}
	
	protected void ExplodeGrenade(EGrenadeType grenade_type)
	{
		switch ( grenade_type )
		{
			case EGrenadeType.FRAGMENTATION:
				Explode(DT_EXPLOSION, m_AmmoType);
			break;
			case EGrenadeType.CHEMICAL:
			break;
			case EGrenadeType.ILLUMINATING:
				Explode(DT_EXPLOSION, m_AmmoType);
			break;
			case EGrenadeType.NON_LETHAL:
			break;
		}
		
		OnExplode();
	}

	protected void OnPin()
	{
		m_Pinned = true;
		if ( GetGame().IsServer() )
		{
			SetSynchDirty();
		}
		Deactivate();
	}

	protected void OnUnpin()
	{
		m_Pinned = false;
		if ( GetGame().IsServer() )
		{
			SetSynchDirty();
		}
		OnActivateStarted();
	}

	protected void OnActivateStarted() {}
	protected void OnActivateFinished()
	{
		if ( GetGame().IsServer() )
		{
			SetHealth("", "", 0.0); // causes explosion when grenade is destroyed
			SetTakeable(false);
		}
	}
	
	protected void OnActivateImmediate()
	{
		if ( GetGame().IsServer() )
		{
			SetHealth("", "", 0.0); // causes explosion when grenade is destroyed
			SetTakeable(false);
		}
	}
	
	protected void OnDeactivate() {}
	protected void OnExplode()
	{
		if ( GetGame().IsServer() )
		{
			SetHealth("", "", 0.0);
			m_DeleteTimer.Run(10, this, "DeleteSave");
		}
	}
	
	protected void CreateLight()
	{
		m_Light = GrenadeLight.Cast( ScriptedLightBase.CreateLight( GrenadeLight, GetPosition()) );
	}
	
	protected void DestroyParticle(Particle p)
	{
		if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() )
		{
			if (p != null)
			{
				p.Stop();
			}
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		if ( GetGame().SaveVersion() >= 107 )
		{
			ctx.Write( m_Pinned );
		}
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if ( !super.OnStoreLoad(ctx, version) )
			return false;
		
		bool pinned;
		if ( version >= 107 )
		{
			if ( !ctx.Read(pinned) )
			{
				return false;
			}
			
			m_Pinned = pinned;
		}

		return true;
	}

	override void OnExplosionEffects(Object source, Object directHit, int componentIndex, string surface, vector pos, vector surfNormal, float energyFactor, float explosionFactor, bool isWater, string ammoType)
	{
		super.OnExplosionEffects(source, directHit, componentIndex, surface, pos, surfNormal, energyFactor, explosionFactor, isWater, ammoType);

		if ( m_ParticleExplosionId > ParticleList.INVALID )
		{
			EntityAI parent = this;
			if ( GetHierarchyParent() )
			{
				parent = GetHierarchyParent();
			}

			DestroyParticle(m_ParticleIgnited);
			
			m_ParticleExplosion = ParticleManager.GetInstance().PlayOnObject(m_ParticleExplosionId, parent, m_ParticlePosition, Vector(0, 0, 0), true);
		}

		CreateLight();
	}

	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		
		if ( !IsPinned() && !m_ParticleIgnited)
		{
			//ROADFLARE_BURNING_INIT  ROADFLARE_BURNING_ENDING //FLAREPROJ_FIRE  ROADFLARE_BURNING_SMOKE
			m_ParticleIgnited = ParticleManager.GetInstance().PlayOnObject( ParticleList.ALP_SPARKS , this, m_ParticlePositionKnot, Vector(0, 0, 0), true);
		}
		
	}	
	
	
	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		
		DestroyParticle(m_ParticleExplosion);
	}
	
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);

		//! should be called only here to avoid multiple explosion calculations, call SetHealth("","",0.0) instead
	 	ExplodeGrenade(m_GrenadeType);

	}

	override bool CanExplodeInFire()
	{
		return true;
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionAttach);
		AddAction(ActionDetach);
		//AddAction(ActionUnpin);
		//AddAction(ActionPin);
		
		//AddAction(ActionTogglePlaceObject);
		//AddAction(ActionDeployObject);		
	}
	/*
	override void EEItemLocationChanged(notnull InventoryLocation oldLoc, notnull InventoryLocation newLoc)
	{
		super.EEItemLocationChanged(oldLoc, newLoc);

		//! activate grenade when it leaves player hands (safety handle released)
		if(newLoc.GetType() != InventoryLocationType.HANDS && !IsPinned())
		{
			Activate();
		}
	}
	
	override void OnWasAttached(EntityAI parent, int slot_id)
	{
		super.OnWasAttached(parent, slot_id);
		
		if( parent.IsInherited(TrapBase) )
		{
			Deactivate();
		}
	}
	*/
	void alp_Dynamite_Base()
	{
		m_Pinned = true;
		m_FuseTimer = new Timer;
		m_DeleteTimer = new Timer;
		m_RemainingFuseTime = -1;
		m_ParticleExplosion = null;

		SetPinnable(true);
		SetFuseDelay(DEFAULT_FUSE_DELAY);
		SetAmmoType(DEFAULT_AMMO_TYPE);
		SetGrenadeType(EGrenadeType.FRAGMENTATION);
		
		SetParticleExplosion(ParticleList.INVALID); //! no effect
		SetParticlePosition(WorldToModel(GetPosition()));
		
		vector posKnot = GetSelectionPositionMS("knot") + "0 0.13 0";
		SetParticlePositionKnot(posKnot);
		
		
		RegisterNetSyncVariableBool("m_Pinned");
	}
	
	void ~alp_Dynamite_Base() {}
}