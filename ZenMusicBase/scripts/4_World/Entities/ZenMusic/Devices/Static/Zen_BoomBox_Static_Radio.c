class Zen_BoomBox_Static_Radio extends Zen_BoomBox
{
	override void EEInit()
	{
		super.EEInit();

		if (!GetGame().IsDedicatedServer())
			return;

		SetAllowDamage(false);
		SetTakeable(false);

		if (!GetZenMusicBattery())
		{
			ItemBase battery = ItemBase.Cast(GetInventory().CreateAttachment("Battery9V"));
			if (battery)
			{
				battery.LockToParent();
			}
		}

		Print("[ZenMusic] Spawned " + GetType() + ". IsPaused=" + m_ZenMusicPausedServer);

		if (GetZenMusicConfig().RadioBoomboxAutoPlay)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(PlayZenMusicSongServer, 1500.0, false, false);
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

	override void OnWorkStart()
	{
		super.OnWorkStart();

		if (!GetGame().IsDedicatedServer())
		{
			return;
		}

		ToggleInvisibleZenRadio(false);
	}

	override void OnWorkStop()
	{
		super.OnWorkStop();

		if (!GetGame().IsDedicatedServer())
		{
			return;
		}

		ToggleInvisibleZenRadio(true);
	}

	void ToggleInvisibleZenRadio(bool turnOn)
	{
		array<Object> nearbyObjects = new array<Object>;
		GetGame().GetObjectsAtPosition3D(GetPosition(), GetZenMusicConfig().StaticBoomboxTurnsOffInvisibleRange, nearbyObjects, NULL);

		foreach (Object obj : nearbyObjects)
		{
			if (obj.IsInherited(Zen_BoomBox_Invisible_Static))
			{
				Zen_BoomBox_Invisible_Static staticInvisBoombox = Zen_BoomBox_Invisible_Static.Cast(obj);
				if (staticInvisBoombox)
				{
					if (turnOn)
					{
						staticInvisBoombox.PrepareForNewZenMusic(true);
					}
					else 
					{
						staticInvisBoombox.PauseZenMusicServer();
					}
					
					break;
				}
			}
		}
	}
}