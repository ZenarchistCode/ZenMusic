class Zen_BoomBox_Static extends Zen_MusicDeviceBase
{
	private bool m_ZenSongIsPlaying;
	private int m_ZenCassetteSpawnFails;
	private int m_ZenSongIndex;

	// THIS IS ALL SERVER-SIDE: SPAWNS A CASSETTE AND TELLS CLIENTS TO SYNC TO SONG
	override void EEInit()
	{
		super.EEInit();

		SetAllowDamage(false);
		SetTakeable(false);

		if (GetType() == "Zen_BoomBox_Static")
		{
			m_ZenMusicPausedServer = !GetZenMusicConfig().StaticBoomboxAutoPlay;
		} else
		if (GetType() == "Zen_BoomBox_Invisible_Static")
		{
			m_ZenMusicPausedServer = !GetZenMusicConfig().StaticInvisibleBoomboxAutoPlay;
		}

		m_ZenSongIndex = 0;
		m_ZenCassetteSpawnFails = 0;

		Print("[ZenMusic] Spawned " + GetType() + ". IsPaused=" + m_ZenMusicPausedServer);

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(PrepareForNewZenMusic, 1500.0, false, false);
	}

	void ~Zen_BoomBox_Static()
	{
		if (!GetGame())
			return;

		if (GetGame().IsDedicatedServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(UpdateZenMusicSongDuration);
		}
	}

	override void PrepareForNewZenMusic(bool forceUnpause = false)
	{
		if (forceUnpause)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(UpdateZenMusicSongDuration);
			m_ZenMusicPausedServer = false;
		}

		if (m_ZenMusicPausedServer)
			return;

		if (GetZenMusicCassette())
		{
			GetZenMusicCassette().UnlockFromParent();
			GetZenMusicCassette().DeleteSafe();
		}

		if (!GetZenMusicBattery())
		{
			ItemBase battery = ItemBase.Cast(GetInventory().CreateAttachment("Battery9V"));
			if (battery)
				battery.LockToParent();
		}

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(SpawnRandomZenMusicCassette, 1000.0, false);
	}

	override void UpdateZenMusicSongDuration()
	{
		if (m_ZenMusicPausedServer)
			return;

		// If song has been stopped, don't update music play secs and stop here
		if (m_ZenMusicPlaySecs < 0 || m_ZenMusicPlaySecs > GetZenMusicSongDuration() + 10)
		{
			StopZenMusicSongServer();
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(PrepareForNewZenMusic, 1500, false, false);
			return;
		}

		// All is well - continue to rock out with your small stones out.
		m_ZenMusicPlaySecs += ZEN_SONG_UPDATE_TIMER_SECS;
		SetSynchDirty();

		CallZenZombieDancers();

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateZenMusicSongDuration, ZEN_SONG_UPDATE_TIMER_SECS * 1000, false);
	}

	void SpawnRandomZenMusicCassette()
	{
		if (m_ZenCassetteSpawnFails >= 10)
			return;

		string tape;
		if (GetType() == "Zen_BoomBox_Static")
		{
			tape = GetZenMusicConfig().StaticBoomboxSongs.Get(m_ZenSongIndex);
			m_ZenSongIndex++;
			if (m_ZenSongIndex >= GetZenMusicConfig().StaticBoomboxSongs.Count())
			{
				GetZenMusicConfig().ShuffleStaticBoomboxArray();
				m_ZenSongIndex = 0;
			}
		} else
		if (GetType() == "Zen_BoomBox_Invisible_Static")
		{
			tape = GetZenMusicConfig().StaticInvisibleBoomboxSongs.Get(m_ZenSongIndex);
			m_ZenSongIndex++;
			if (m_ZenSongIndex >= GetZenMusicConfig().StaticInvisibleBoomboxSongs.Count())
			{
				GetZenMusicConfig().ShuffleStaticInvisibleBoomboxArray();
				m_ZenSongIndex = 0;
			}
		}

		if (tape == "")
		{
			Print("[ZenMusic] " + GetType() + " ERROR: Tape could not be loaded!");
			return;
		}

		GetInventory().CreateAttachment(tape);

		if (GetZenMusicCassette())
		{
			GetZenMusicCassette().LockToParent();
			PlayZenMusicSongServer();
		}
		else
		{
			Error("[ZenMusic] COULD NOT SPAWN STATIC MUSIC CASSETTE: " + tape);
			SpawnRandomZenMusicCassette();
			m_ZenCassetteSpawnFails++;
		}
	}

	override bool CanPutInCargo(EntityAI parent)
	{
		return false;
	}

	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}

	// No need for CompEM() on static boombox
	override bool PlayZenMusicSongServer(int skipSecs = 0)
	{
		if (!HasValidZenMusicCassette())
		{
			Error("[ZenMusic] Cassette malfunctioned for tape: " + GetZenMusicCassette().GetType() + " (HasValidZenMusicCassette = false)");
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(PrepareForNewZenMusic, 1500, false);
			m_ZenCassetteSpawnFails++;
			return false;
		}

		m_ZenMusicPlaySecs = skipSecs;
		m_ZenMusicPausedServer = false;
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(UpdateZenMusicSongDuration, 1000, false);
		SetSynchDirty();

		return true;
	}

	override void StopZenMusicSongServer(bool turnOffRadio = false)
	{
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(UpdateZenMusicSongDuration);
		m_ZenMusicPlaySecs = -1;
		SetSynchDirty();
	}

	override void PauseZenMusicServer()
	{
		m_ZenMusicPausedServer = true;
		StopZenMusicSongServer();
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionZenStaticBoomboxTurnOn);
		AddAction(ActionZenStaticBoomboxTurnOff);
		AddAction(ActionZenBoomboxVolDown);
		AddAction(ActionZenBoomboxVolUp);
		AddAction(ActionZenStaticBoomboxNextSong);
	}
}