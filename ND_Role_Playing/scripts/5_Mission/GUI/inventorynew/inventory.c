
modded class Inventory: LayoutHolder
{

	override void UpdateSpecialtyMeter()
	{
		if ( GetND().GetRP().GetPerksOptions().EnablePerkCustomDayzSkills )
		{
			m_SpecializationPanel.Show(false);
		}
		else
		{
			super.UpdateSpecialtyMeter();
		}		

	}
	
}
