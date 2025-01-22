modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		GetZenMusicConfig();
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);

		SendZenMusicConfig(player, identity);
	}

	void SendZenMusicConfig(PlayerBase player, PlayerIdentity identity)
	{
		GetRPCManager().SendRPC("ZenMod_RPC", "RPC_ReceiveZenMusicCfgClient", new Param1<bool>(GetZenMusicConfig().AllowCarInventory), true, player.GetIdentity());
	}
}