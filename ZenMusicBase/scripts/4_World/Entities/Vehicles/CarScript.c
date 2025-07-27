modded class CarScript
{
	//! MUSIC
	const static float ZEN_ZEN_SONG_UPDATE_TIMER_SECS = 1.0;

	// Server & client
	protected float m_ZenMusicVolumeClient = 0.5;
	protected float m_ZenMusicVolume = 0.5;
	protected bool m_ZenIsPlayingRadio = false;

	// Client
	protected ref EffectSound m_ZenSong;
	protected bool m_IsPlayingZenMusic = false;

	// Server
	int m_ZenMusicPlaySecs = -1;

	void CarScript()
	{
		RegisterNetSyncVariableFloat("m_ZenMusicVolume");
		RegisterNetSyncVariableInt("m_ZenMusicPlaySecs");
	}

	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();

		// Failsafe in case radio cassette gets stuck locked for some reason
		GetInventory().SetSlotLock(InventorySlots.GetSlotIdFromString("ZenCassette"), false);
	}

	void ~CarScript()
	{
		if (!GetGame())
			return;

		if (GetGame().IsDedicatedServer())
		{
			StopZenMusicSongServer(true);
		} else
		{
			StopZenMusicSongClient();
		}

		delete m_ZenSong;
	}

	//! MUSIC
	ItemBase GetZenMusicCassette()
    {
        return ItemBase.Cast(FindAttachmentBySlotName("ZenCassette"));
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
			StopZenMusicSongServer(true);
		}
	}

	bool HasValidZenMusicCassette()
	{
		if (!GetZenMusicCassette())
			return false;

		return GetZenMusicCassette() && !GetZenMusicCassette().IsRuined() && Zen_Cassette_Base.GetZenMusicSoundSet(GetZenMusicCassette().GetType()) != "" && Zen_Cassette_Base.GetZenMusicSongDuration(GetZenMusicCassette().GetType()) > 0;
	}

	void PlayZenMusicSongServer(int skipSecs = 0)
	{
		if (!HasValidZenMusicCassette())
		{
			if (!IsPlayingZenRadio())
			{
				PlayZenMusicSongServer_Radio();
			}
			
			return;
		}

		m_ZenMusicPlaySecs = skipSecs;

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateZenMusicSongDuration, 1000, false);
		SetSynchDirty();
	}

	void StopZenMusicSongServer(bool turnOffRadio = false)
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(UpdateZenMusicSongDuration);
		m_ZenMusicPlaySecs = -1;
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
					plugin.RemoveCar(this);
				}

				m_ZenIsPlayingRadio = false;
			}
		}
	}

	void PlayZenMusicSongServer_Radio()
	{
		m_ZenIsPlayingRadio = true;

		PluginZenMusicRadio plugin = PluginZenMusicRadio.Cast(GetPlugin(PluginZenMusicRadio));
		if (plugin)
		{
			plugin.AddCar(this);
		}
	}

	bool IsPlayingZenRadio()
	{
		return m_ZenIsPlayingRadio;
	}

	// Called every X seconds. No need for SynchDirty because that will be called when car is loaded on client anyway and this just tracks current song time
	void UpdateZenMusicSongDuration()
	{
		// If song has been stopped, don't update music play secs and stop here
		if (m_ZenMusicPlaySecs < 0 || m_ZenMusicPlaySecs > GetZenMusicSongDuration() + 10)
		{
			StopZenMusicSongServer();
			return;
		}

		// If battery is dead, stop music
		if (IsVitalCarBattery())
		{
			CarBattery carBattery = CarBattery.Cast(FindAttachmentBySlotName("CarBattery"));
			if (!carBattery || !carBattery.GetCompEM() || !carBattery.GetCompEM().GetEnergy() > 0 || carBattery.IsRuined())
			{
				StopZenMusicSongServer(true);
				return;
			}
		}
		else
		if (IsVitalTruckBattery())
		{
			TruckBattery truckBattery = TruckBattery.Cast(FindAttachmentBySlotName("TruckBattery"));
			if (!truckBattery || !truckBattery.GetCompEM() || !truckBattery.GetCompEM().GetEnergy() > 0 || truckBattery.IsRuined())
			{
				StopZenMusicSongServer(true);
				return;
			}
		}

		// All is well - continue to rock out with your small stones out.
		m_ZenMusicPlaySecs += ZEN_ZEN_SONG_UPDATE_TIMER_SECS;
		SetSynchDirty();

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateZenMusicSongDuration, ZEN_ZEN_SONG_UPDATE_TIMER_SECS * 1000, false);
	}

	void TurnZenMusicVolumeUp()
	{
		m_ZenMusicVolume = m_ZenMusicVolume + 0.25;
		if (m_ZenMusicVolume > 4.0)
			m_ZenMusicVolume = 4.0;

		SetSynchDirty();
	}

	void TurnZenMusicVolumeDown()
	{
		m_ZenMusicVolume = m_ZenMusicVolume - 0.25;
		if (m_ZenMusicVolume < 0)
			m_ZenMusicVolume = 0;

		SetSynchDirty();
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		CheckMusicSync();
	}

	protected void CheckMusicSync()
	{
		if (m_ZenMusicPlaySecs >= 0)
		{
			if (m_ZenMusicPlaySecs < GetZenMusicSongDuration() && (!m_ZenSong || !m_ZenSong.IsSoundPlaying()))
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
			m_ZenMusicVolumeClient = m_ZenMusicVolume;
			if (m_ZenSong)
			{
				if (m_ZenSong.Zen_GetAbstractWave().IsHeaderLoaded())
				{
					m_ZenSong.Zen_SetMaxVolume(m_ZenMusicVolumeClient);
					m_ZenSong.SetSoundVolume(m_ZenMusicVolumeClient);
				}
			}
		}
	}

	void PlayZenMusicSongClient()
	{
		if (!HasValidZenMusicCassette() || m_IsPlayingZenMusic)
		{
			return;
		}

		m_ZenSong = SEffectManager.CreateSound(Zen_Cassette_Base.GetZenMusicSoundSet(GetZenMusicCassette().GetType()), GetPosition(), 0, 0, false);
		
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
		#endif
		
		int playSecs = Zen_Cassette_Base.GetZenMusicSongDuration(GetZenMusicCassette().GetType());

		if (!m_ZenSong || !playSecs || playSecs <= 0)
			return;

		m_ZenSong.SetParent(this);
		m_ZenSong.SetLocalPosition(vector.Zero);
		m_ZenSong.SetSoundAutodestroy(true);
		m_ZenSong.Zen_SetMaxVolume(m_ZenMusicVolumeClient);
		m_ZenSong.SoundPlay();
		m_IsPlayingZenMusic = true;

		// If song has already been playing a while, skip ahead
		if (m_ZenMusicPlaySecs > 0 && m_ZenSong.Zen_GetAbstractWave())
		{
			float skip = (m_ZenMusicPlaySecs / playSecs);
			m_ZenSong.Zen_GetAbstractWave().SetStartOffset(skip);
		}
	}

	void StopZenMusicSongClient()
	{
		if (m_ZenSong)
		{
			m_ZenSong.SoundStop();
			m_IsPlayingZenMusic = false;
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		if (slot_name == "ZenCassette" || slot_name == "CarBattery" || slot_name == "TruckBattery")
		{
			if (GetGame().IsDedicatedServer())
			{
			
				StopZenMusicSongServer(slot_name != "ZenCassette");
			}
			else 
			{
				m_IsPlayingZenMusic = false;
			}
		}
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionZenToggleMusic);
		AddAction(ActionZenMusicVolUp);
		AddAction(ActionZenMusicVolDn);
	}

	override bool IgnoreOutOfReachCondition()
    {
		#ifdef ZENMODPACK
		if (!ZenModEnabled("ZenMusic"))
			return super.IgnoreOutOfReachCondition();
		#endif

		if (GetZenMusicConfig().AllowCarInventory)
		{
			// True = disables the distance checks for ALL car attachments. Only safe because I hide all other categories while inside vehicle.
			return ZenMusic_PlayerInCar();
		}

		return super.IgnoreOutOfReachCondition();
    }

	override bool CanDisplayCargo()
	{
		// If player inventory in cars is enabled, don't allow cargo displayed while inside car
		return super.CanDisplayCargo() && !ZenMusic_PlayerInCar();
	}

	override bool CanDisplayAttachmentCategory(string category_name)
	{
		#ifndef ZENMODPACK
		if (category_name == "ZenMusic")
		{
			if (ZenMusic_PlayerInCar())
			{
				return true;
			}
		}

		return super.CanDisplayAttachmentCategory(category_name) && !ZenMusic_PlayerInCar();
		#endif

		return super.CanDisplayAttachmentCategory(category_name);
	}

	static bool ZenMusic_PlayerInCar()
	{
		if (!GetGame() || !GetGame().IsClient())
			return false;

		PlayerBase clientPlayer = PlayerBase.Cast(GetGame().GetPlayer());
		if (clientPlayer)
		{
			return clientPlayer.IsInVehicle();
		}

		return false;
	}
}