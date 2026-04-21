modded class MissionGameplay
{
	override void RegisterZenClientOptions()
	{
		super.RegisterZenClientOptions();
		
		ZenOptions.AddBoolSetting("ZEN", "ZenMusicSetting", "#STR_ZenMusicSettingsCategory", true, "#STR_ZenMusicSettingsDescription", "#STR_ZenMusicSettingsNoCopyright");
	}
}