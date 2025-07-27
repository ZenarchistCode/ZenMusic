class ActionZenStaticBoomboxTurnOn : ActionInteractBase
{
	void ActionZenStaticBoomboxTurnOn()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "#switch_on";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target || !target.GetObject())
			return false;

		Object target_object = target.GetObject();

		Zen_MusicDeviceBase ntarget = Zen_MusicDeviceBase.Cast(target_object);
		return ntarget && !ntarget.IsPlayingZenMusic();
	}

	override void OnExecuteServer(ActionData action_data)
	{
		Object target_object = action_data.m_Target.GetObject();

		// Prep static boombox to play a random cassette
		Zen_MusicDeviceBase ntarget = Zen_MusicDeviceBase.Cast(target_object);
		if (!ntarget)
			return;

		ntarget.PrepareForNewZenMusic(true);

		// Scan for any invisible music (eg. guitar player) and stop their music
		array<Object> nearbyObjects = new array<Object>;
		GetGame().GetObjectsAtPosition3D(ntarget.GetPosition(), GetZenMusicConfig().StaticBoomboxTurnsOffInvisibleRange, nearbyObjects, NULL);

		foreach (Object obj : nearbyObjects)
		{
			if (obj.IsInherited(Zen_BoomBox_Invisible_Static))
			{
				Zen_BoomBox_Invisible_Static staticInvisBoombox = Zen_BoomBox_Invisible_Static.Cast(obj);
				if (staticInvisBoombox)
				{
					staticInvisBoombox.PauseZenMusicServer();
					break;
				}
			}
		}
	}
}