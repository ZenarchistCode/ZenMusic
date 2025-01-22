modded class MissionBase
{
    void MissionBase()
    {
        GetRPCManager().AddRPC("ZenMod_RPC", "RPC_ReceiveZenMusicCfgClient", this, SingeplayerExecutionType.Client);
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