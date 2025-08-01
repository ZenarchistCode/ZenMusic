class ActionZenMusicVolDn : ActionInteractBase
{
	void ActionZenMusicVolDn()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_HEADLIGHT;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override typename GetInputType()
	{
		return ZenMusicVolumeDnInput;
	}

	override bool HasTarget()
	{
		return false;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		#ifdef ZENMODPACK
		if (!ZenModEnabled("ZenMusic"))
			return false;
		#endif

		HumanCommandVehicle vehCommand = player.GetCommand_Vehicle();

		if (vehCommand)
		{
			Transport trans = vehCommand.GetTransport();
			if (trans)
			{
				CarScript car;
				if (Class.CastTo(car, trans))
				{
					if (car.CrewMemberIndex(player) == DayZPlayerConstants.VEHICLESEAT_DRIVER || car.CrewMemberIndex(player) == DayZPlayerConstants.VEHICLESEAT_CODRIVER)
					{
						return true;
					}
					else
					{
						return true;
					}
				}
			}
		}

		return false;
	}

	override void OnExecuteServer(ActionData action_data)
	{
		HumanCommandVehicle vehCommand = action_data.m_Player.GetCommand_Vehicle();
		if (vehCommand)
		{
			Transport trans = vehCommand.GetTransport();
			if (trans)
			{
				CarScript car;
				if (Class.CastTo(car, trans))
				{
					car.TurnZenMusicVolumeDown();
				}
			}
		}
	}

	override bool CanBeUsedInVehicle()
	{
		return true;
	}
}