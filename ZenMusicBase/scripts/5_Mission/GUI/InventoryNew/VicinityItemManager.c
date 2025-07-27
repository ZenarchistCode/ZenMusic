// This is for stopping the player from picking up items outside a car while inside if opening inventory is allowed.
// Only takes effect if inventory is allowed while in the car via JSON config.
modded class VicinityItemManager
{
	override bool ExcludeFromContainer_Phase1(Object actor_in_radius)
	{
		#ifdef ZENMODPACK
		if (!ZenModEnabled("ZenMusic"))
		{
			return super.ExcludeFromContainer_Phase1(actor_in_radius);
		}
		#endif

		#ifndef ZENMODPACK
		if (ZenMusic_PlayerInCar())
			return true;
		#endif
			
		return super.ExcludeFromContainer_Phase1(actor_in_radius);
	}

	override bool ExcludeFromContainer_Phase2(Object object_in_radius)
	{
		#ifdef ZENMODPACK
		if (!ZenModEnabled("ZenMusic"))
		{
			return super.ExcludeFromContainer_Phase1(object_in_radius);
		}
		#endif

		#ifndef ZENMODPACK
		if (ZenMusic_PlayerInCar())
			return true;
		#endif

		return super.ExcludeFromContainer_Phase2(object_in_radius);
	}

	override bool ExcludeFromContainer_Phase3(Object object_in_cone)
	{
		#ifdef ZENMODPACK
		if (!ZenModEnabled("ZenMusic"))
		{
			return super.ExcludeFromContainer_Phase3(object_in_cone);
		}
		#endif

		#ifndef ZENMODPACK
		if (ZenMusic_PlayerInCar() && object_in_cone != NULL && !object_in_cone.IsKindOf("CarScript"))
			return true;
		#endif

		return super.ExcludeFromContainer_Phase3(object_in_cone);
	}

	bool ZenMusic_PlayerInCar()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player && player.IsInVehicle())
			return true;

		return false;
	}
}