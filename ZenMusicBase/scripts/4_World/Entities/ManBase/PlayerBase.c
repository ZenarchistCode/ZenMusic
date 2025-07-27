modded class PlayerBase
{
	// Allows viewing inventory while inside cars - VicinityItemManager.c handles not being able to pick up items outside of the car
	override void OnCommandVehicleStart()
	{
		super.OnCommandVehicleStart();

		if (!GetInventory())
			return;

		if (GetZenMusicConfig().AllowCarInventory)
		{
			GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);
		}
	}
}