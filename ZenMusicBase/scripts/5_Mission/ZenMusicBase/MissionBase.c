modded class MissionBase
{
    void MissionBase()
    {
        if (!g_Game.IsDedicatedServer())
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
		for (i = 0; i < g_Game.ConfigGetChildrenCount("CfgVehicles"); i++)
		{
			g_Game.ConfigGetChildName("CfgVehicles", i, cfg_name);
			if (cfg_name.Contains("Zen_Cassette_") && !cfg_name.Contains("Base"))
            {
                if (g_Game.ConfigGetInt("CfgVehicles " + cfg_name + " allowRandomSpawn") != 0)
                {
                    Zen_Cassette_RandomTape.RANDOM_TAPES.Insert(cfg_name);
                }
                else 
                {
                    Print("[ZenMusic] Skipping random tape spawn (allowRandomSpawn=0): " + cfg_name);
                }
            }
		}

        Print("[ZenMusic] Loaded " + Zen_Cassette_RandomTape.RANDOM_TAPES.Count() + " random music tapes.");
    }
}