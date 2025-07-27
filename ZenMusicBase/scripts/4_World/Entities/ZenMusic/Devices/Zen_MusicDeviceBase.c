class Zen_MusicDeviceBase extends ItemBase
{
	const static float ZEN_SONG_UPDATE_TIMER_SECS = 1.0;

	 // Zombie sound variables
    private ref NoiseParams		m_ZenMusicNoisePar = NULL;
    private NoiseSystem			m_ZenMusicNoiseSystem = NULL;
    protected float				m_ZenMusicNoiseDuration = 1.0;
    protected int				m_ZenMusicMaxNoiseCount = 60;
    protected int				m_ZenMusicNoiseCount = 0;

	// Server & client
	protected bool				m_ZenMusicPausedServer;
	protected float				m_ZenMusicVolumeClient = 1.0;
	protected float				m_ZenMusicVolume = 1.0;
	protected int				m_ZenMusicPlaySecs = -1;

	// Client
	protected ref EffectSound	m_ZenSong;
	protected bool m_ZenIsPlayingRadio;

	// Server
	int							m_ZenMusicDuration = -1;

	void Zen_MusicDeviceBase()
	{
		if (m_ZenMusicVolume > GetInitZenMusicVolume())
		{
			m_ZenMusicVolumeClient = GetInitZenMusicVolume();
			m_ZenMusicVolume = GetInitZenMusicVolume();
		}

		#ifdef SERVER
		if (CanAlertZenZombies())
		{
			if (!m_ZenMusicNoiseSystem)
				m_ZenMusicNoiseSystem = GetGame().GetNoiseSystem();

			// Prepare zombie noise caller
			if (m_ZenMusicNoiseSystem && !m_ZenMusicNoisePar)
			{
				m_ZenMusicNoisePar = new NoiseParams();
				m_ZenMusicNoisePar.LoadFromPath("CfgVehicles Zen_MusicNoise " + ConfigGetString("noiseType"));
			}
		}
		#endif

		RegisterNetSyncVariableFloat("m_ZenMusicVolume");
		RegisterNetSyncVariableInt("m_ZenMusicPlaySecs");
	}

	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();

		// Failsafe in case radio cassette gets stuck locked for some reason
		GetInventory().SetSlotLock(InventorySlots.GetSlotIdFromString("ZenCassette"), false);
	}

	void ~Zen_MusicDeviceBase()
	{
		if (!GetGame())
			return;

		if (GetGame().IsDedicatedServer())
			StopZenMusicSongServer(true);

		if (m_ZenSong)
			m_ZenSong.Stop();
	}

	bool IsPlayingZenMusic()
    {
        return m_ZenMusicPlaySecs >= 0;
    }

	float GetZenMusicVolume()
	{
		if (GetGame().IsClient())
			return m_ZenMusicVolumeClient;

		return m_ZenMusicVolume;
	}

	float GetInitZenMusicVolume()
	{
		return ConfigGetFloat("initVolume");
	}

	float GetZenMusicMaxVolume()
	{
		return ConfigGetFloat("maxVolume");
	}

	ItemBase GetZenMusicCassette()
    {
        return ItemBase.Cast(FindAttachmentBySlotName("ZenCassette"));
    }

    ItemBase GetZenMusicBattery()
    {
        return ItemBase.Cast(FindAttachmentBySlotName("BatteryD"));
    }

	int GetZenMusicSongDuration()
	{
		if (GetZenMusicCassette() && !GetZenMusicCassette().IsRuined())
			return Zen_Cassette_Base.GetZenMusicSongDuration(GetZenMusicCassette().GetType());

		return -1;
	}

	void ToggleZenMusic()
	{
		if (m_ZenMusicPlaySecs == -1)
		{
			PlayZenMusicSongServer();
		} else
		{
			StopZenMusicSongServer();
		}
	}

	bool HasValidZenMusicCassette()
	{
		return GetZenMusicCassette() && !GetZenMusicCassette().IsRuined() && Zen_Cassette_Base.GetZenMusicSoundSet(GetZenMusicCassette().GetType()) != "" && Zen_Cassette_Base.GetZenMusicSongDuration(GetZenMusicCassette().GetType()) > 0;
	}

	bool CanAlertZenZombies()
	{
		return ConfigGetBool("attractsZombies");
	}

	void CallZenZombieDancers()
    {
		if (!CanAlertZenZombies())
			return;

        if (!m_ZenMusicNoisePar)
			return;

        if (!m_ZenMusicNoiseSystem)
			return;

        m_ZenMusicNoiseSystem.AddNoiseTarget(GetPosition(), m_ZenMusicNoiseDuration, m_ZenMusicNoisePar, GetZenMusicVolume());
    }

	void TurnZenMusicVolumeUpServer()
	{
		m_ZenMusicVolume = m_ZenMusicVolume + 0.1;
		if (m_ZenMusicVolume > 4.0)
			m_ZenMusicVolume = 4.0;

		SetSynchDirty();
	}

	void TurnZenMusicVolumeDownServer()
	{
		m_ZenMusicVolume = m_ZenMusicVolume - 0.1;
		if (m_ZenMusicVolume < 0)
			m_ZenMusicVolume = 0;

		SetSynchDirty();
	}

	int GetZenMusicSongPlaySecs()
	{
		return m_ZenMusicPlaySecs;
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		// Check music setting (for twitch streamers/youtubers etc)
		if (GetZenMusicCassette())
		{
			#ifdef ZENMODPACK
			// Don't allow copyrighted music
			if (GetZenModPackClientConfig().CassetteMusicSetting == 2)
			{
				if (Zen_Cassette_Base.IsZenMusicCopyrighted(GetZenMusicCassette().GetType()))
				{
					StopZenMusicSongClient();
					return;
				}
			}
			
			// Don't allow any music
			if (GetZenModPackClientConfig().CassetteMusicSetting == 3)
			{
				if (Zen_Cassette_Base.IsZenMusicTape(GetZenMusicCassette().GetType()))
				{
					StopZenMusicSongClient();
					return;
				}
			}
			#endif
		}

		if (m_ZenMusicPlaySecs >= 0)
		{
			if (m_ZenMusicPlaySecs < GetZenMusicSongDuration() && !m_ZenSong)
			{
				PlayZenMusicSongClient();
			}
		}
		else
		{
			StopZenMusicSongClient();
		}

		if (m_ZenMusicVolumeClient != m_ZenMusicVolume)
		{
			if (m_ZenSong)
			{
				if (m_ZenSong.Zen_GetAbstractWave().IsHeaderLoaded())
				{
					m_ZenMusicVolumeClient = m_ZenMusicVolume;
					m_ZenSong.Zen_SetMaxVolume(m_ZenMusicVolumeClient);
					m_ZenSong.SetSoundVolume(m_ZenMusicVolumeClient);
				}
			}
		}
	}

	void UpdateZenMusicSongDuration()
	{
		// If song has been stopped, don't update music play secs and stop here
		if (m_ZenMusicPlaySecs < 0 || m_ZenMusicPlaySecs >= m_ZenMusicDuration)
		{
			StopZenMusicSongServer();
			return;
		}

		// All is well - continue to rock out with your small stones out.
		m_ZenMusicPlaySecs += ZEN_SONG_UPDATE_TIMER_SECS;
		SetSynchDirty();

		CallZenZombieDancers();

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateZenMusicSongDuration, ZEN_SONG_UPDATE_TIMER_SECS * 1000.0, false);
	}

	bool PlayZenMusicSongServer(int skipSecs = 0)
	{
		if (IsZenMusicPausedServer())
			return false;

		if (!GetCompEM() || !GetCompEM().CanWork())
			return false;

		if (!HasValidZenMusicCassette())
		{
			if (!IsPlayingZenRadio())
			{
				return PlayZenMusicSongServer_Radio();
			}

			return false;
		}

		m_ZenMusicPlaySecs = skipSecs;
		m_ZenMusicDuration = Zen_Cassette_Base.GetZenMusicSongDuration(GetZenMusicCassette().GetType()) + 10; // Add 10 secs as a safe buffer for server/client sync

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateZenMusicSongDuration, 1000, false);
		SetSynchDirty();

		return true;
	}

	void StopZenMusicSongServer(bool turnOffRadio = false)
	{
		m_ZenMusicPlaySecs = -1;

		if (GetCompEM() && !m_ZenIsPlayingRadio)
			GetCompEM().SwitchOff();

		SetSynchDirty();

		if (m_ZenIsPlayingRadio)
		{
			if (GetZenMusicCassette())
			{
				GetZenMusicCassette().UnlockFromParent();
				GetZenMusicCassette().DeleteSafe();
			}

			if (turnOffRadio)
			{
				PluginZenMusicRadio plugin = PluginZenMusicRadio.Cast(GetPlugin(PluginZenMusicRadio));
				if (plugin)
				{
					plugin.RemoveDevice(this);
				}

				m_ZenIsPlayingRadio = false;
			}
		}
	}

	bool PlayZenMusicSongServer_Radio()
	{
		m_ZenIsPlayingRadio = true;

		PluginZenMusicRadio plugin = PluginZenMusicRadio.Cast(GetPlugin(PluginZenMusicRadio));
		if (plugin)
		{
			if (plugin.AddDevice(this))
			{
				return true;
			}
		}

		return false;
	}

	bool IsPlayingZenRadio()
	{
		return m_ZenIsPlayingRadio;
	}

	void PlayZenMusicSongClient()
	{
		if (!HasValidZenMusicCassette())
			return;

		int songLength = Zen_Cassette_Base.GetZenMusicSongDuration(GetZenMusicCassette().GetType());
		if (!songLength || songLength <= 0)
			return;

		m_ZenSong = SEffectManager.CreateSound(Zen_Cassette_Base.GetZenMusicSoundSet(GetZenMusicCassette().GetType()), GetPosition(), 0, 0, false);
		if (!m_ZenSong)
			return;

		m_ZenSong.SetParent(this);
		m_ZenSong.SetLocalPosition(vector.Zero);
		m_ZenSong.SetSoundAutodestroy(true);
		m_ZenSong.Zen_SetMaxVolume(m_ZenMusicVolumeClient);
		m_ZenSong.SoundPlay();

		// If song has already been playing a while, skip ahead
		if (m_ZenMusicPlaySecs > 0 && m_ZenSong.Zen_GetAbstractWave())
		{
			float skip = (m_ZenMusicPlaySecs / songLength);
			m_ZenSong.Zen_GetAbstractWave().SetStartOffset(skip);
		}
	}

	void StopZenMusicSongClient()
	{
		if (m_ZenSong)
			m_ZenSong.SoundStop();

		m_ZenSong = NULL;
	}

    override void OnWorkStart()
    {
        super.OnWorkStart();

		if (GetGame().IsDedicatedServer())
		{
			if (GetCompEM() && !PlayZenMusicSongServer())
				GetCompEM().SwitchOff();
		}
    }

    override void OnWorkStop()
    {
        super.OnWorkStop();

		#ifdef SERVER
        StopZenMusicSongServer(true);
		#endif
    }

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		#ifdef SERVER
		if (slot_name == "Battery9V" || slot_name == "ZenCassette")
			StopZenMusicSongServer();
		#endif
	}

	void PrepareForNewZenMusic(bool forceUnpause = false)
	{
	}

	void PauseZenMusicServer()
	{
	}

	bool IsZenMusicPausedServer()
	{
		return m_ZenMusicPausedServer;
	}

	override void SetActions()
    {
        super.SetActions();

        AddAction(ActionTurnOnWhileInHands);
        AddAction(ActionTurnOffWhileInHands);
        AddAction(ActionTurnOnWhileOnGround);
        AddAction(ActionTurnOffWhileOnGround);
    }
}