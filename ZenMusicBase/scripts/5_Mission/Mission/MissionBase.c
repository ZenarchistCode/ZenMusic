modded class MissionBase
{
    void MissionBase()
    {
        GetRPCManager().AddRPC("ZenMod_RPC", "RPC_ReceiveZenMusicCfgClient", this, SingeplayerExecutionType.Client);

        if (!GetGame().IsDedicatedServer())
            return;

        int i;
        string cfg_name = "";

        if (!Zen_Cassette_RandomTape.RANDOM_TAPES)
        {
            Zen_Cassette_RandomTape.RANDOM_TAPES = new array<string>;
        }
        else 
        {
            Zen_Cassette_RandomTape.RANDOM_TAPES.Clear();
        }


		// Load how many cassette tapes exist for RandomCassette spawner
		for (i = 0; i < GetGame().ConfigGetChildrenCount("CfgVehicles"); i++)
		{
			GetGame().ConfigGetChildName("CfgVehicles", i, cfg_name);
			if (cfg_name.Contains("Zen_Cassette_") && !cfg_name.Contains("Base"))
            {
                if (GetGame().ConfigGetInt("CfgVehicles " + cfg_name + " allowRandomSpawn") != 0)
                {
                    Zen_Cassette_RandomTape.RANDOM_TAPES.Insert(cfg_name);
                    Print("[ZenMusic] Loaded random tape spawn: " + cfg_name);
                }
            }
		}

        Print("[ZenMusic] Loaded " + Zen_Cassette_RandomTape.RANDOM_TAPES.Count() + " random music tapes.");
    }

	// Server -> tell player if they can access inventory while in car
	void RPC_ReceiveZenMusicCfgClient(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        Param1<bool> data;
        if (!ctx.Read(data))
        {
            Error("[ZenMusic] Error sync'ing server-side data to client - RPC_ReceiveZenMusicCfgClient");
            return;
        }

		GetZenMusicConfig().AllowCarInventory = data.param1;
    }
}