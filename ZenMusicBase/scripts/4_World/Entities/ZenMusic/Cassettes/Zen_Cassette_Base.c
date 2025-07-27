class Zen_Cassette_Base extends ItemBase
{
	bool m_IsZenRadioCassette;

	void Zen_Cassette_Base()
	{
		m_IsZenRadioCassette = false;

		RegisterNetSyncVariableBool("m_IsZenRadioCassette");
	}

	override void EEDelete(EntityAI parent)
	{
		UnlockFromParent();

		super.EEDelete(parent);
	}

	void SetZenRadioCassette(bool b)
	{
		m_IsZenRadioCassette = b;
		SetSynchDirty();

		if (m_IsZenRadioCassette)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(LockToParent, 100, false);
		}
	}

	bool IsZenRadioCassette()
	{
		return m_IsZenRadioCassette;
	}

	override bool DescriptionOverride(out string output)
	{
		if (!IsZenRadioCassette())
		{
			return false;
		}

		string cfgPath = "CfgVehicles " + GetType();
		GetGame().ConfigGetText(cfgPath + " descriptionShort", output);

		output = "87.8 Survivor FM Radio: " + output;
		return true;
	}

	static int GetZenMusicSongDuration(string type)
	{
		if (!GetGame())
			return -1;

		string cfgPath = "CfgVehicles " + type;

		if (!GetGame().ConfigIsExisting(cfgPath))
			return -1;

		if (GetZenMusicConfig().DebugSongDurationOverride > 0)
		{
			return GetZenMusicConfig().DebugSongDurationOverride;
		}

		return GetGame().ConfigGetInt(cfgPath + " playSeconds");
	}

	static string GetZenMusicSoundSet(string type)
	{
		if (type == "Zen_RadioIntermission")
			return "Zen_RadioIntermission_SoundSet";

		 return type + "_SoundSet";
	}

	static bool IsZenMusicCopyrighted(string type)
	{
		if (!GetGame())
			return false;

		string cfgPath = "CfgVehicles " + type;

		if (!GetGame().ConfigIsExisting(cfgPath))
			return false;

		return GetGame().ConfigGetInt(cfgPath + " copyrighted") == 1;
	}

	static bool IsZenMusicTape(string type)
	{
		if (!GetGame())
			return false;

		string cfgPath = "CfgVehicles " + type;

		if (!GetGame().ConfigIsExisting(cfgPath))
			return false;

		return GetGame().ConfigGetInt(cfgPath + " isMusic") == 1;
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		ctx.Write(m_IsZenRadioCassette);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_IsZenRadioCassette))
		{
			m_IsZenRadioCassette = false;
			return false;
		}

		return true;
	}

	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();

		if (m_IsZenRadioCassette)
		{
			UnlockFromParent();
			DeleteSafe();
		}
	}
}