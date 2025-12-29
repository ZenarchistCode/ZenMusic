/*
	(c) 2025 | ZenExpansionVehiclesMusic | Zenarchist
*/

class CfgPatches
{
	class ZenExpansionVehiclesMusic
	{
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Vehicles_Wheeled",
			"ZenMusicBase",
			"DayZExpansion_Vehicles_Ground_LandRover",
			"DayZExpansion_Vehicles_Ground_UAZ",
			"DayZExpansion_Vehicles_Ground_Ikarus"
		};
	};
};

class CfgMods
{
	class ZenExpansionVehiclesMusic
	{
		author = "Zenarchist";
		type = "mod";
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = 
				{ 
					"ZenExpansionVehiclesMusic/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value = "";
				files[] = 
				{ 
					"ZenExpansionVehiclesMusic/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] = 
				{ 
					"ZenExpansionVehiclesMusic/scripts/5_Mission"
				};
			};
		};
	};
};

class CfgVehicles
{
	class CarScript;
	
	class GUIInventoryAttachmentsProps;
	class Engine;
	class Body;
	class Chassis;
	class AnimationSources;
	
	class Expansion_Landrover_Base: CarScript
	{
		attachments[] +=
		{
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class ZenMusic
			{
				name = "$STR_CfgVehicles_ZenCassette0";
				description = "$STR_CfgVehicles_ZenCassette0";
				icon = "set:zen_music image:cassette_icon";
				attachmentSlots[] =
				{
					"ZenCassette"
				};
			};
		};
	};
	class ExpansionUAZBase: CarScript 
	{
		attachments[] +=
		{
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class ZenMusic
			{
				name = "$STR_CfgVehicles_ZenCassette0";
				description = "$STR_CfgVehicles_ZenCassette0";
				icon = "set:zen_music image:cassette_icon";
				attachmentSlots[] =
				{
					"ZenCassette"
				};
			};
		};
	};
	class ExpansionUAZ: ExpansionUAZBase
	{
		attachments[]+=
		{
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class ZenMusic
			{
				name = "$STR_CfgVehicles_ZenCassette0";
				description = "$STR_CfgVehicles_ZenCassette0";
				icon = "set:zen_music image:cassette_icon";
				attachmentSlots[] =
				{
					"ZenCassette"
				};
			};
		};
	};
	class ExpansionUAZRoofless : ExpansionUAZ
	{
		attachments[]=
		{
			"CarBattery",
			"CarRadiator",
			"SparkPlug",
			"Reflector_1_1",
			"Reflector_2_1",
			"uazwheel_1_1",
			"uazwheel_1_2",
			"uazwheel_2_1",
			"uazwheel_2_2",
			"uazdriverdoor",
			"uazcodriverdoor",
			"uazcargo1door",
			"uazcargo2door",
			"uazhooddoor",
			"CamoNet",
			"KeyChain",
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class ZenMusic
			{
				name = "$STR_CfgVehicles_ZenCassette0";
				description = "$STR_CfgVehicles_ZenCassette0";
				icon = "set:zen_music image:cassette_icon";
				attachmentSlots[] =
				{
					"ZenCassette"
				};
			};
		};
	};
	class ExpansionUAZCargoRoofless: ExpansionUAZ
	{
		attachments[]=
		{
			"CarBattery",
			"CarRadiator",
			"SparkPlug",
			"Reflector_1_1",
			"Reflector_2_1",
			"uazwheel_1_1",
			"uazwheel_1_2",
			"uazwheel_2_1",
			"uazwheel_2_2",
			"uazdriverdoor",
			"uazcodriverdoor",
			"uazcargo1door",
			"uazcargo2door",
			"uazhooddoor",
			"CamoNet",
			"KeyChain",
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class ZenMusic
			{
				name = "$STR_CfgVehicles_ZenCassette0";
				description = "$STR_CfgVehicles_ZenCassette0";
				icon = "set:zen_music image:cassette_icon";
				attachmentSlots[] =
				{
					"ZenCassette"
				};
			};
		};
	};
	class ExpansionBus: CarScript
	{
		attachments[]+=
		{
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps: GUIInventoryAttachmentsProps
		{
			class ZenMusic
			{
				name = "$STR_CfgVehicles_ZenCassette0";
				description = "$STR_CfgVehicles_ZenCassette0";
				icon = "set:zen_music image:cassette_icon";
				attachmentSlots[] =
				{
					"ZenCassette"
				};
			};
		};
	};
};