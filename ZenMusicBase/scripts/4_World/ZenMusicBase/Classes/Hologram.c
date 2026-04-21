modded class Hologram
{
    override void SetProjectionPosition(vector position)
	{
		#ifndef ZenHologramControls // ZHC allows player to modify height themselves
		Zen_BoomBox boombox = Zen_BoomBox.Cast(m_Parent);
		if (boombox)
		{
			m_Projection.SetPosition(position + "0 0.15 0");
			
			if (IsFloating())
			{
				m_Projection.SetPosition(SetOnGround(position + "0 0.15 0"));
			}

			return;
		}
		#endif

		super.SetProjectionPosition( position );
	}
}