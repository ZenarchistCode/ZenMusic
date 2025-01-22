modded class CarScript
{
	const static float SONG_UPDATE_TIMER_SECS = 1.0;

	// Server & client
	protected float m_MusicVolumeClient = 1.0;
	protected float m_MusicVolume = 1.0;

	// Client
	protected ref EffectSound m_Song;
	protected bool m_IsPlayingSong = false;

	// Server
	int m_MusicPlaySecs = -1;

	void CarScript()
	{
		RegisterNetSyncVariableFloat("m_MusicVolume");
		RegisterNetSyncVariableInt("m_MusicPlaySecs");
	}

	void ~CarScript()
	{
		if (!GetGame())
			return;

		if (GetGame().IsDedicatedServer())
			StopSongServer();
		else
			StopSongClient();

		delete m_Song;
	}

	ItemBase GetCassette()
    {
        return ItemBase.Cast(FindAttachmentBySlotName("ZenCassette"));
    }

	int GetSongDuration()
	{
		if (GetCassette() && !GetCassette().IsRuined())
			return Zen_Cassette_Base.GetSongDuration(GetCassette().GetType());

		return -1;
	}

	void ToggleMusic()
	{
		if (m_MusicPlaySecs == -1)
			PlaySongServer();
		else
			StopSongServer();
	}

	bool HasValidCassette()
	{
		if (!GetCassette())
			return false;

		return GetCassette() && !GetCassette().IsRuined() && Zen_Cassette_Base.GetSongSoundSet(GetCassette().GetType()) != "" && Zen_Cassette_Base.GetSongDuration(GetCassette().GetType()) > 0;
	}

	void PlaySongServer()
	{
		if (!HasValidCassette())
			return;

		m_MusicPlaySecs = 0;
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateSongDuration, 1000, false);
		SetSynchDirty();
	}

	void StopSongServer()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(UpdateSongDuration);
		m_MusicPlaySecs = -1;
		SetSynchDirty();
	}

	// Called every X seconds. No need for SynchDirty because that will be called when car is loaded on client anyway and this just tracks current song time
	void UpdateSongDuration()
	{
		// If song has been stopped, don't update music play secs and stop here
		if (m_MusicPlaySecs < 0 || m_MusicPlaySecs > GetSongDuration() + 10)
		{
			StopSongServer();
			return;
		}

		// If battery is dead, stop music
		if (IsVitalCarBattery())
		{
			CarBattery carBattery = CarBattery.Cast(FindAttachmentBySlotName("CarBattery"));
			if (!carBattery || !carBattery.GetCompEM() || !carBattery.GetCompEM().GetEnergy() > 0 || carBattery.IsRuined())
			{
				StopSongServer();
				return;
			}
		}
		else
		if (IsVitalTruckBattery())
		{
			TruckBattery truckBattery = TruckBattery.Cast(FindAttachmentBySlotName("TruckBattery"));
			if (!truckBattery || !truckBattery.GetCompEM() || !truckBattery.GetCompEM().GetEnergy() > 0 || truckBattery.IsRuined())
			{
				StopSongServer();
				return;
			}
		}

		// All is well - continue to rock out with your small stones out.
		m_MusicPlaySecs += SONG_UPDATE_TIMER_SECS;
		SetSynchDirty();

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateSongDuration, SONG_UPDATE_TIMER_SECS * 1000, false);
	}

	void TurnVolumeUp()
	{
		m_MusicVolume = m_MusicVolume + 0.25;
		if (m_MusicVolume > 4.0)
			m_MusicVolume = 4.0;

		SetSynchDirty();
	}

	void TurnVolumeDown()
	{
		m_MusicVolume = m_MusicVolume - 0.25;
		if (m_MusicVolume < 0)
			m_MusicVolume = 0;

		SetSynchDirty();
	}

	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		CheckMusicSync();
	}

	protected void CheckMusicSync()
	{
		if (m_MusicPlaySecs >= 0)
		{
			if (m_MusicPlaySecs < GetSongDuration() && (!m_Song || !m_Song.IsSoundPlaying()))
			{
				PlaySongClient();
			}
		}
		else
		{
			StopSongClient();
		}

		if (m_MusicVolumeClient != m_MusicVolume)
		{
			m_MusicVolumeClient = m_MusicVolume;
			if (m_Song)
			{
				if (m_Song.Zen_GetAbstractWave().IsHeaderLoaded())
				{
					m_Song.Zen_SetMaxVolume(m_MusicVolumeClient);
					m_Song.SetSoundVolume(m_MusicVolumeClient);
				}
			}
		}
	}

	void PlaySongClient()
	{
		if (!HasValidCassette() || m_IsPlayingSong)
			return;

		m_Song = SEffectManager.CreateSound(Zen_Cassette_Base.GetSongSoundSet(GetCassette().GetType()), GetPosition(), 0, 0, false);
		int playSecs = Zen_Cassette_Base.GetSongDuration(GetCassette().GetType());

		if (!m_Song || !playSecs || playSecs <= 0)
			return;

		m_Song.SetParent(this);
		m_Song.SetLocalPosition(vector.Zero);
		m_Song.SetSoundAutodestroy(true);
		m_Song.Zen_SetMaxVolume(m_MusicVolumeClient);
		m_Song.SoundPlay();
		m_IsPlayingSong = true;

		// If song has already been playing a while, skip ahead to current playtime
		if (m_MusicPlaySecs > 0 && m_Song.Zen_GetAbstractWave())
		{
			float skip = (m_MusicPlaySecs / playSecs);
			m_Song.Zen_GetAbstractWave().SetStartOffset(skip);
		}
	}

	void StopSongClient()
	{
		if (m_Song)
		{
			m_Song.SoundStop();
			m_IsPlayingSong = false;
		}
	}

	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		if (slot_name == "CarBattery" || slot_name == "TruckBattery" || slot_name == "ZenCassette")
		{
			StopSongServer();
		}
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionToggleMusic);
		AddAction(ActionMusicVolUp);
		AddAction(ActionMusicVolDn);
	}

	override bool CanDisplayAttachmentSlot(string slot_name)
	{
		//! MUSIC
		if (slot_name == "ZenCassette")
			return true;

		return super.CanDisplayAttachmentSlot(slot_name);
	}

	override bool CanDisplayCargo()
	{
		if (GetZenMusicConfig().AllowCarInventory)
		{
			if (GetGame().GetPlayer()) // Override since I've enabled the player inventory to be seen in cars
			{
				PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
				if (player && player.IsInVehicle())
				{
					return false;
				}
			}
		}

		return super.CanDisplayCargo();
	}

	override bool CanDisplayAttachmentCategory(string category_name)
	{
		category_name.ToLower();

		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player)
			return false;

		bool inCar = player.IsInVehicle();

		if (GetZenMusicConfig().AllowCarInventory && inCar)
		{
			if (category_name == "zenmusiccarradio")
				return true;
		}

		return super.CanDisplayAttachmentCategory(category_name) && !inCar;
	}
}
