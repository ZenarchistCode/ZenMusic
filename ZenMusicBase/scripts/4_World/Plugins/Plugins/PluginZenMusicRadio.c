class PluginZenMusicRadio extends PluginBase
{
    protected float m_DeltaTime;

    protected int m_RadioSongIndex;
    protected int m_RadioIntermissionIndex;

    protected string m_CurrentTape;
    protected int m_CurrentTapeDuration;
    protected int m_CurrentTapePlaySecs;
    protected int m_SongsSinceIntermission;

    protected ref array<Zen_MusicDeviceBase> m_MusicDevices;
    protected ref array<CarScript> m_Cars;

	override void OnInit()
    {
        Print("[PluginZenMusicRadio] :: OnInit");

        m_DeltaTime = 0;
        m_RadioSongIndex = -1;
        m_RadioIntermissionIndex = -1;
        m_CurrentTapePlaySecs = 0;
        m_CurrentTapeDuration = 10;
        m_SongsSinceIntermission = 0;
        m_MusicDevices = new array<Zen_MusicDeviceBase>;
        m_Cars = new array<CarScript>;
        m_CurrentTape = "";
    }

    bool AddCar(notnull CarScript car)
    {
        bool carFound = false;
        foreach (string s : GetZenMusicConfig().RadioAllowed)
        {
            if (car.IsKindOf(s))
            {
                carFound = true;
                break;
            }
        }

        if (!carFound)
            return false;

        if (m_Cars.Find(car) != -1)
            return false;

        if (car.GetZenMusicCassette() != NULL)
            return false;

        Zen_Cassette_Base tape = Zen_Cassette_Base.Cast(car.GetInventory().CreateAttachment(m_CurrentTape));
        if (!tape)
        {
            Error("Failed to spawn tape: " + m_CurrentTape);
            return false;
        }

        tape.SetZenRadioCassette(true);
        car.PlayZenMusicSongServer(m_CurrentTapePlaySecs);
        m_Cars.Insert(car);
        return true;
    }

    void RemoveCar(notnull CarScript car)
    {
        m_Cars.RemoveItem(car);
    }

    bool AddDevice(notnull Zen_MusicDeviceBase musicDevice)
    {
        bool deviceFound = false;
        foreach (string s : GetZenMusicConfig().RadioAllowed)
        {
            if (musicDevice.IsKindOf(s))
            {
                deviceFound = true;
                break;
            }
        }

        if (!deviceFound)
            return false;

        if (m_MusicDevices.Find(musicDevice) != -1)
            return false;

        if (musicDevice.GetZenMusicCassette() != NULL)
            return false;

        Zen_Cassette_Base tape = Zen_Cassette_Base.Cast(musicDevice.GetInventory().CreateAttachment(m_CurrentTape));
        if (!tape)
        {
            Error("Failed to spawn tape: " + m_CurrentTape);
            return false;
        }

        tape.SetZenRadioCassette(true);
        musicDevice.PlayZenMusicSongServer(m_CurrentTapePlaySecs);

        m_MusicDevices.Insert(musicDevice);
        return true;
    }

    void RemoveDevice(notnull Zen_MusicDeviceBase musicDevice)
    {
        m_MusicDevices.RemoveItem(musicDevice);
    }

    override void OnDestroy()
    {
        if (m_MusicDevices)
            m_MusicDevices.Clear();

        if (m_Cars)
            m_Cars.Clear();
    }

    override void OnUpdate(float delta_time)
    {
        m_DeltaTime += delta_time;
        if (m_DeltaTime < 1)
            return;

        m_DeltaTime = 0;
        m_CurrentTapePlaySecs++;

        if (m_CurrentTapePlaySecs >= (m_CurrentTapeDuration + 7) || m_CurrentTape == "")
        {
            // 10 seconds after song ends, play next song.
            m_CurrentTape = PickNextSong();

            if (m_CurrentTape != "")
            {
                m_CurrentTapeDuration = Zen_Cassette_Base.GetZenMusicSongDuration(m_CurrentTape);
                m_CurrentTapePlaySecs = 0;
                SpawnAllCurrentTapes();
            }
        }
        else
        if (m_CurrentTapePlaySecs >= (m_CurrentTapeDuration + 5))
        {
            // 5 seconds after song/tape ends, delete it.
            DeleteAllCurrentTapes();
        }
    }

    void DeleteAllCurrentTapes()
    {
        int i;

        for (i = m_Cars.Count(); i >= 0; i--)
        {
            CarScript car = m_Cars.Get(i);
            if (!car)
            {
                m_Cars.Remove(i);
                continue;
            }

            if (car.IsPlayingZenRadio() && car.GetZenMusicCassette())
            {
                if (car.GetZenMusicCassette().IsZenRadioCassette())
                {
                    car.GetZenMusicCassette().UnlockFromParent();
                    car.GetZenMusicCassette().DeleteSafe();
                }
            }
        }

        for (i = m_MusicDevices.Count(); i >= 0; i--)
        {
            Zen_MusicDeviceBase device = m_MusicDevices.Get(i);
            if (!device)
            {
                m_MusicDevices.Remove(i);
                continue;
            }

            if (device.IsPlayingZenRadio() && device.GetZenMusicCassette())
            {
                if (device.GetZenMusicCassette().IsZenRadioCassette())
                {
                    device.GetZenMusicCassette().UnlockFromParent();
                    device.GetZenMusicCassette().DeleteSafe();
                }
            }
        }
    }

    void SpawnAllCurrentTapes()
    {
        int i;

        for (i = m_Cars.Count(); i >= 0; i--)
        {
            CarScript car = m_Cars.Get(i);
            if (!car)
            {
                m_Cars.Remove(i);
                continue;
            }

            if (car.IsPlayingZenRadio() && !car.GetZenMusicCassette())
            {
                Zen_Cassette_Base carTape = Zen_Cassette_Base.Cast(car.GetInventory().CreateAttachment(m_CurrentTape));
                if (!carTape)
                {
                    Error("Failed to spawn tape: " + m_CurrentTape);
                    return;
                }

                carTape.SetZenRadioCassette(true);
                car.PlayZenMusicSongServer(m_CurrentTapePlaySecs);
            }
        }

        for (i = m_MusicDevices.Count(); i >= 0; i--)
        {
            Zen_MusicDeviceBase device = m_MusicDevices.Get(i);
            if (!device)
            {
                m_MusicDevices.Remove(i);
                continue;
            }

            if (device.IsPlayingZenRadio() && !device.GetZenMusicCassette())
            {
                Zen_Cassette_Base deviceTape = Zen_Cassette_Base.Cast(device.GetInventory().CreateAttachment(m_CurrentTape));
                if (!deviceTape)
                {
                    Error("Failed to spawn tape: " + m_CurrentTape);
                    return;
                }

                deviceTape.SetZenRadioCassette(true);
                device.PlayZenMusicSongServer(m_CurrentTapePlaySecs);
            }
        }
    }

    string PickNextSong()
    {
        if (m_RadioSongIndex >= GetZenMusicConfig().RadioSongs.Count())
        {
            m_RadioSongIndex = 0;
            GetZenMusicConfig().ShuffleRadioArray();
        }

        if (m_RadioIntermissionIndex >= GetZenMusicConfig().RadioIntermissionSongs.Count())
        {
            m_RadioIntermissionIndex = 0;
            GetZenMusicConfig().ShuffleRadioIntermissionArray();
        }

        // Every 3 songs, play an intermission instead
        if (m_SongsSinceIntermission >= 3)
        {
            string intermission = GetZenMusicConfig().RadioIntermissionSongs.Get(m_RadioIntermissionIndex);
            m_RadioIntermissionIndex++;
            m_SongsSinceIntermission = 0;
            return intermission;
        }

        string song = GetZenMusicConfig().RadioSongs.Get(m_RadioSongIndex);
        m_RadioSongIndex++;
        m_SongsSinceIntermission++;
        return song;
    }
}