class Zen_BoomBox extends Zen_MusicDeviceBase
{
	override bool CanPutInCargo(EntityAI parent)
	{
		return !IsPlayingZenMusic();
	}

	// Force boomboxes to re-spawn every 4 hours when they are created by the Central Loot Economy (once touched by players, regular types.xml lifetime applies)
	override void EEOnCECreate()
	{
		super.EEOnCECreate();

		SetLifetime(14400);
	}

	override bool IsRefresherSignalingViable()
	{
		return !IsRuined();
	}

	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
		AddAction(ActionZenBoomboxVolDown);
		AddAction(ActionZenBoomboxVolUp);
	}
}
