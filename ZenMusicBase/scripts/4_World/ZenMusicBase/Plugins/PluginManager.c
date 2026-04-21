modded class PluginManager
{
	override void Init()
	{
		super.Init();

		#ifdef SERVER
		if (GetZenMusicConfig().RadioAllowed && GetZenMusicConfig().RadioAllowed.Count() > 0)
		{
			RegisterPlugin("PluginZenMusicRadio", false, true);
		}
		#endif
	}
}