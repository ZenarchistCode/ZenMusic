class ZenMusicConfig
{
	// Config location
	private const static string zenModFolder = "$profile:\\Zenarchist\\";
	private const static string zenConfigName = "ZenMusicConfig.json";
	private const static string CURRENT_VERSION = "2";
	string CONFIG_VERSION = "";

	// Cassettes to play on static boombox
	bool AllowCarInventory;
	bool StaticBoomboxAutoPlay;
	ref array<string> StaticBoomboxSongs;
	int StaticBoomboxTurnsOffInvisibleRange;
	int StaticBoomboxTurnsOnInvisibleRange;
	bool StaticInvisibleBoomboxAutoPlay;
	ref array<string> StaticInvisibleBoomboxSongs;
	bool RadioBoomboxAutoPlay;
	ref array<string> RadioAllowed;
	ref array<string> RadioSongs;
	ref array<string> RadioIntermissionSongs;
	int DebugSongDurationOverride;


	void Load()
	{
		StaticBoomboxSongs = new array<string>;
		StaticInvisibleBoomboxSongs = new array<string>;
		RadioAllowed = new array<string>;
		RadioSongs = new array<string>;
		RadioIntermissionSongs = new array<string>;

		// Don't load JSON on server
		if (!GetGame().IsDedicatedServer())
			return;

		if (FileExist(zenModFolder + zenConfigName))
		{
			JsonFileLoader<ZenMusicConfig>.JsonLoadFile(zenModFolder + zenConfigName, this);

			if (CONFIG_VERSION != CURRENT_VERSION)
			{
				// Mismatch, back up old version
				JsonFileLoader<ZenMusicConfig>.JsonSaveFile(zenModFolder + zenConfigName + "_old", this);
			}
			else
			{
				// Config exists and version matches, shuffle array and stop here.
				ShuffleArrays();
				return;
			}
		}

		CONFIG_VERSION = CURRENT_VERSION;

		AllowCarInventory = true;

		RadioBoomboxAutoPlay = false;
		StaticBoomboxAutoPlay = false;
		StaticInvisibleBoomboxAutoPlay = false;
		StaticBoomboxTurnsOffInvisibleRange = 10;
		StaticBoomboxTurnsOnInvisibleRange = 10;

		StaticBoomboxSongs.Clear();
		StaticBoomboxSongs.Insert("Zen_Cassette_Classical1");
		StaticBoomboxSongs.Insert("Zen_Cassette_Classical2");
		StaticBoomboxSongs.Insert("Zen_Cassette_Classical3");
		StaticBoomboxSongs.Insert("Zen_Cassette_Classical4");
		StaticBoomboxSongs.Insert("Zen_Cassette_Classical5");
		StaticBoomboxSongs.Insert("Zen_Cassette_Classical6");
		StaticBoomboxSongs.Insert("Zen_Cassette_Classical7");
		StaticBoomboxSongs.Insert("Zen_Cassette_Classical8");
		StaticBoomboxSongs.Insert("Zen_Cassette_Classical9");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen1");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen2");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen3");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen4");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen5");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen6");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen7");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen8");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen9");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen10");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen11");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen12");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen13");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen14");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen15");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen16");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen17");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen18");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen19");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen20");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen21");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen22");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen23");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen24");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen25");
		StaticBoomboxSongs.Insert("Zen_Cassette_Zen26");

		StaticInvisibleBoomboxSongs.Clear();
		StaticInvisibleBoomboxSongs.Insert("Guitar_Songs_On_ExpansionAI_Etc");
		
		RadioAllowed.Clear();
		RadioAllowed.Insert("CarScript");
		RadioAllowed.Insert("Zen_BoomBox_Radio");

		RadioSongs.Clear();
		RadioSongs.Insert("Zen_Cassette_Classical1");
		RadioSongs.Insert("Zen_Cassette_Classical2");
		RadioSongs.Insert("Zen_Cassette_Classical3");
		RadioSongs.Insert("Zen_Cassette_Classical4");
		RadioSongs.Insert("Zen_Cassette_Classical5");
		RadioSongs.Insert("Zen_Cassette_Classical6");
		RadioSongs.Insert("Zen_Cassette_Classical7");
		RadioSongs.Insert("Zen_Cassette_Classical8");
		RadioSongs.Insert("Zen_Cassette_Classical9");
		RadioSongs.Insert("Zen_Cassette_Zen1");
		RadioSongs.Insert("Zen_Cassette_Zen2");
		RadioSongs.Insert("Zen_Cassette_Zen3");
		RadioSongs.Insert("Zen_Cassette_Zen4");
		RadioSongs.Insert("Zen_Cassette_Zen5");
		RadioSongs.Insert("Zen_Cassette_Zen6");
		RadioSongs.Insert("Zen_Cassette_Zen7");
		RadioSongs.Insert("Zen_Cassette_Zen8");
		RadioSongs.Insert("Zen_Cassette_Zen9");
		RadioSongs.Insert("Zen_Cassette_Zen10");
		RadioSongs.Insert("Zen_Cassette_Zen11");
		RadioSongs.Insert("Zen_Cassette_Zen12");
		RadioSongs.Insert("Zen_Cassette_Zen13");
		RadioSongs.Insert("Zen_Cassette_Zen14");
		RadioSongs.Insert("Zen_Cassette_Zen15");
		RadioSongs.Insert("Zen_Cassette_Zen16");
		RadioSongs.Insert("Zen_Cassette_Zen17");
		RadioSongs.Insert("Zen_Cassette_Zen18");
		RadioSongs.Insert("Zen_Cassette_Zen19");
		RadioSongs.Insert("Zen_Cassette_Zen20");
		RadioSongs.Insert("Zen_Cassette_Zen21");
		RadioSongs.Insert("Zen_Cassette_Zen22");
		RadioSongs.Insert("Zen_Cassette_Zen23");
		RadioSongs.Insert("Zen_Cassette_Zen24");
		RadioSongs.Insert("Zen_Cassette_Zen25");
		RadioSongs.Insert("Zen_Cassette_Zen26");

		RadioIntermissionSongs = new array<string>;
		RadioIntermissionSongs.Insert("Zen_RadioIntermission");

		DebugSongDurationOverride = 0;

		Save();
	}

	void Save()
	{
		if (!FileExist(zenModFolder))
		{
			MakeDirectory(zenModFolder);
		}

		JsonFileLoader<ZenMusicConfig>.JsonSaveFile(zenModFolder + zenConfigName, this);
	}

	void ShuffleArrays()
	{
		ShuffleStaticBoomboxArray();
		ShuffleStaticInvisibleBoomboxArray();

		ShuffleRadioArray();
		ShuffleRadioIntermissionArray();
	}

	void ShuffleStaticBoomboxArray()
	{
		int i;
		int randomIndexToSwap;
		string temp;

		for (i = 0; i < StaticBoomboxSongs.Count(); i++) 
		{
			randomIndexToSwap = Math.RandomIntInclusive(0, StaticBoomboxSongs.Count() - 1);
			temp = StaticBoomboxSongs[randomIndexToSwap];
			StaticBoomboxSongs[randomIndexToSwap] = StaticBoomboxSongs[i];
			StaticBoomboxSongs[i] = temp;
		}
	}

	void ShuffleStaticInvisibleBoomboxArray()
	{
		int i;
		int randomIndexToSwap;
		string temp;

		for (i = 0; i < StaticInvisibleBoomboxSongs.Count(); i++) 
		{
			randomIndexToSwap = Math.RandomIntInclusive(0, StaticInvisibleBoomboxSongs.Count() - 1);
			temp = StaticInvisibleBoomboxSongs[randomIndexToSwap];
			StaticInvisibleBoomboxSongs[randomIndexToSwap] = StaticInvisibleBoomboxSongs[i];
			StaticInvisibleBoomboxSongs[i] = temp;
		}
	}

	void ShuffleRadioArray()
	{
		int i;
		int randomIndexToSwap;
		string temp;

		for (i = 0; i < RadioSongs.Count(); i++) 
		{
			randomIndexToSwap = Math.RandomIntInclusive(0, RadioSongs.Count() - 1);
			temp = RadioSongs[randomIndexToSwap];
			RadioSongs[randomIndexToSwap] = RadioSongs[i];
			RadioSongs[i] = temp;
		}
	}

	void ShuffleRadioIntermissionArray()
	{
		int i;
		int randomIndexToSwap;
		string temp;

		for (i = 0; i < RadioIntermissionSongs.Count(); i++) 
		{
			randomIndexToSwap = Math.RandomIntInclusive(0, RadioIntermissionSongs.Count() - 1);
			temp = RadioIntermissionSongs[randomIndexToSwap];
			RadioIntermissionSongs[randomIndexToSwap] = RadioIntermissionSongs[i];
			RadioIntermissionSongs[i] = temp;
		}
	}
}

ref ZenMusicConfig m_ZenMusicConfig;

static ZenMusicConfig GetZenMusicConfig()
{
	if (!m_ZenMusicConfig)
	{
		m_ZenMusicConfig = new ZenMusicConfig;
		m_ZenMusicConfig.Load();
	}

	return m_ZenMusicConfig;
}