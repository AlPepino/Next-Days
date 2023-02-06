
#ifdef NAMALSK_SURVIVAL
			


modded class Inventory
{
	protected Widget m_ColdResistPanel;


	
	

	void Inventory( LayoutHolder parent )
	{
		m_ColdResistPanel = GetMainWidget().FindAnyWidget("ColdResistancePanelPanel");
		

	}

	
	
	override void OnShow()
	{
		super.OnShow();

		m_ColdResistPanel.Show( false );
		
		

	}

}

#endif		