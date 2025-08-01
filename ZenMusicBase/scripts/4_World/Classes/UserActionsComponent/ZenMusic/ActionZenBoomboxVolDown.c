class ActionZenBoomboxVolDown : ActionInteractBase
{
	#ifdef ZENMODPACK
	override int Zen_GetDisplayPriority()
	{
		return 1;
	}
	#endif

	void ActionZenBoomboxVolDown()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_Text = "#STR_ZenMusic_VolumeDown";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target || !target.GetObject())
			return false;

		Object target_object = target.GetObject();

		Zen_MusicDeviceBase ntarget = Zen_MusicDeviceBase.Cast(target_object);
		if (ntarget && ntarget.IsPlayingZenMusic())
			return ntarget.GetZenMusicVolume() != 0;

		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		Object target_object = action_data.m_Target.GetObject();

		Zen_MusicDeviceBase ntarget = Zen_MusicDeviceBase.Cast(target_object);
		if (ntarget)
			ntarget.TurnZenMusicVolumeDownServer();
	}
}