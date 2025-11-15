class CfgPatches
{
	class ZenMusicBase
	{
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class ZenMusicBase
	{
		dir = "ZenMusicBase";
		name = "Zen's Music";
		author = "Zenarchist";
		credits = "";
		version = "1.0";
		type = "mod";
		inputs = "ZenMusicBase/data/inputs.xml";
		dependencies[] = 
		{ 
			"Game", 
			"World", 
			"Mission" 
		};
		class defs
		{
			class imageSets
			{
				files[] =
				{
					"ZenMusicBase/data/gui/music/zen_music.imageset"
				};
			};
			class gameScriptModule
			{
				files[] = 
				{ 
					"ZenMusicBase/scripts/3_Game",
					"ZenMusicBase/scripts/Common"
				};
			};
			class worldScriptModule
			{
				files[] = 
				{ 
					"ZenMusicBase/scripts/4_World",
					"ZenMusicBase/scripts/Common"
				};
			};
			class missionScriptModule
			{
				files[] = 
				{ 
					"ZenMusicBase/scripts/5_mission",
					"ZenMusicBase/scripts/common"
				};
			};
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class CarScript;

	//! MUSIC
	class Zen_CassetteCase : Inventory_Base
	{
		scope = 2;
		displayName = "$STR_CfgVehicles_ZenCassetteCase0";
		descriptionShort = "$STR_CfgVehicles_ZenCassetteCase1";
		model = "\dz\gear\tools\cleaning_kit_wood.p3d";
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "ZenMusicBase\data\textures\music\case\cassette_case.paa" };
		animClass = "Knife";
		rotationFlags = 17;
		weight = 250;
		weightPerQuantityUnit = 0;
		itemSize[] = { 2,3 };
		itemsCargoSize[] = { 10,5 };
		fragility = 0.0099999998;
		allowOwnedCargoManipulation = 1; // No idea what this does, but if it's not set to 1, then items inside this inventory fall on the ground when you login with it nested in cargo
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] =
					{

						{
							1,

							{
								"DZ\gear\tools\data\cleaning_kit_wood.rvmat"
							}
						},

						{
							0.69999999,

							{
								"DZ\gear\tools\data\cleaning_kit_wood.rvmat"
							}
						},

						{
							0.5,

							{
								"DZ\gear\tools\data\cleaning_kit_wood_damage.rvmat"
							}
						},

						{
							0.30000001,

							{
								"DZ\gear\tools\data\cleaning_kit_wood_damage.rvmat"
							}
						},

						{
							0,

							{
								"DZ\gear\tools\data\cleaning_kit_wood_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class MeleeModes
		{
			class Default
			{
				ammo = "MeleeLightBlunt";
				range = 1;
			};
			class Heavy
			{
				ammo = "MeleeLightBlunt_Heavy";
				range = 1;
			};
			class Sprint
			{
				ammo = "MeleeLightBlunt_Heavy";
				range = 2.8;
			};
		};
		soundImpactType = "wood";
	};
    class Zen_BoomBox : Inventory_Base
    {
        scope = 2;
        displayName = "$STR_CfgVehicles_ZenBoombox0";
        descriptionShort = "$STR_CfgVehicles_ZenBoombox1";
        initVolume = 0.5;
		maxVolume = 2.0;
		noiseType = "Loud";
		attractsZombies = "true";
        model = "\ZenMusicBase\data\models\music\boombox\zen_boombox.p3d";
		itemBehaviour = 1;
        weight = 500;
        itemSize[] = {4,3};
        attachments[] =
        {
            "BatteryD",
            "ZenCassette"
        };
        repairableWithKits[] = { 7 };
        repairCosts[] = { 25 };
        class EnergyManager
        {
            hasIcon = 1;
            autoSwitchOff = 1;
            energyUsagePerSecond = 0.01;
            plugType = 1;
            attachmentAction = 1;
            wetnessExposure = 0.1;
        };
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] =
					{

						{
							1,

							{
								"ZenMusicBase\data\textures\music\boombox\boombox.rvmat"
							}
						},

						{
							0.69999999,

							{
								"ZenMusicBase\data\textures\music\boombox\boombox.rvmat"
							}
						},

						{
							0.5,

							{
								"ZenMusicBase\data\textures\music\boombox\boombox_damage.rvmat"
							}
						},

						{
							0.30000001,

							{
								"ZenMusicBase\data\textures\music\boombox\boombox_damage.rvmat"
							}
						},

						{
							0,

							{
								"ZenMusicBase\data\textures\music\boombox\boombox_destruct.rvmat"
							}
						}
					};
				};
			};
		};
    };
    class Zen_Walkman : Inventory_Base
    {
        scope = 2;
        displayName = "$STR_CfgVehicles_ZenWalkman0";
        descriptionShort = "$STR_CfgVehicles_ZenWalkman1";
        rotationFlags = 16;
		initVolume = 0.25;
		maxVolume = 0.25;
		noiseType = "Quiet";
		attractsZombies = "true";
        model = "\ZenMusicBase\data\models\music\walkman\zen_walkman.p3d";
        weight = 200;
        itemSize[] = { 1,2 };
        attachments[] =
        {
            "BatteryD",
            "ZenCassette"
        };
		inventorySlot[] =
		{
			"WalkieTalkie",
			"Chemlight"
		};
        repairableWithKits[] = { 7 };
        repairCosts[] = { 25 };
        class EnergyManager
        {
            hasIcon = 1;
            autoSwitchOff = 1;
            energyUsagePerSecond = 0.01;
            plugType = 1;
            attachmentAction = 1;
            wetnessExposure = 0.1;
        };
		class InventorySlotsOffsets
		{
			class WalkieTalkie
			{
				position[]={0,0,0};
				orientation[]={0,180,0};
			};
			class Chemlight
			{
				position[]={-0.01,0,0};
				orientation[]={-90,0,0};
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] =
					{

						{
							1,

							{
								"ZenMusicBase\data\textures\music\walkman\walkman.rvmat"
							}
						},

						{
							0.69999999,

							{
								"ZenMusicBase\data\textures\music\walkman\walkman.rvmat"
							}
						},

						{
							0.5,

							{
								"ZenMusicBase\data\textures\music\walkman\walkman_damage.rvmat"
							}
						},

						{
							0.30000001,

							{
								"ZenMusicBase\data\textures\music\walkman\walkman_damage.rvmat"
							}
						},

						{
							0,

							{
								"ZenMusicBase\data\textures\music\walkman\walkman_destruct.rvmat"
							}
						}
					};
				};
			};
		};
    };
    class Zen_Cassette_Base : Inventory_Base
    {
        displayName = "$STR_CfgVehicles_ZenCassette0";
        descriptionShort = "$STR_CfgVehicles_ZenCassette1";
        model = "\dz\gear\tools\cassette.p3d";
        absorbency = 0;
        rotationFlags = 16;
        weight = 25;
        itemSize[] = { 2,1 };
        fragility = 0.0099999998;
        varWetMax = 0.5;
		playSeconds = -1;
		copyrighted = 0;
		isMusic = 1;
		allowRandomSpawn = 1;
        inventorySlot[] =
        {
            "ZenCassette"
        };
		class CfgCassette
		{
			soundSet = "Your_Song_Soundset";
			playSeconds = 69; // play time in secs
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] =
					{

						{
							1,

							{
								"DZ\gear\tools\data\cassette.rvmat"
							}
						},

						{
							0.69999999,

							{
								"DZ\gear\tools\data\cassette.rvmat"
							}
						},

						{
							0.5,

							{
								"DZ\gear\tools\data\cassette_damage.rvmat"
							}
						},

						{
							0.30000001,

							{
								"DZ\gear\tools\data\cassette_damage.rvmat"
							}
						},

						{
							0,

							{
								"DZ\gear\tools\data\cassette_destruct.rvmat"
							}
						}
					};
				};
			};
		};
        class MeleeModes
        {
            class Default
            {
                ammo = "MeleeLightBlunt";
                range = 1;
            };
            class Heavy
            {
                ammo = "MeleeLightBlunt_Heavy";
                range = 1;
            };
            class Sprint
            {
                ammo = "MeleeLightBlunt_Heavy";
                range = 2.8;
            };
        };
    };
	class Zen_Cassette_RandomTape : Zen_Cassette_Base
	{
		scope = 2;
		displayName = "Random Tape";
		descriptionShort = "Will convert to random cassette for money";
	};
	class Zen_MusicNoise : Inventory_Base
	{
		// Zombie noises
		scope = 2;
		class Quiet
		{
			strength = 120;
			type = "sound";
		};
		class Loud
		{
			strength = 500;
			type = "sound";
		};
		class Louder
		{
			strength = 1000;
			type = "sound";
		};
	};

	// Vehicles
	class OffroadHatchback : CarScript
	{
		attachments[] +=
		{
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps
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
	class Offroad_02 : CarScript
	{
		attachments[] +=
		{
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps
		{
			class ZenMusic
			{
				name = "$STR_CfgVehicles_ZenCassette0";
				description = "$STR_CfgVehicles_ZenCassette0";
				icon = "Cassette";
				attachmentSlots[] =
				{
					"ZenCassette"
				};
			};
		};
	};
	class CivilianSedan : CarScript
	{
		attachments[] +=
		{
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps
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
	class Hatchback_02 : CarScript
	{
		attachments[] +=
		{
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps
		{
			class ZenMusic
			{
				name = "$STR_CfgVehicles_ZenCassette0";
				description = "$STR_CfgVehicles_ZenCassette0";
				icon = "Cassette";
				attachmentSlots[] =
				{
					"ZenCassette"
				};
			};
		};
	};
	class Sedan_02 : CarScript
	{
		attachments[] +=
		{
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps
		{
			class ZenMusic
			{
				name = "$STR_CfgVehicles_ZenCassette0";
				description = "$STR_CfgVehicles_ZenCassette0";
				icon = "Cassette";
				attachmentSlots[] =
				{
					"ZenCassette"
				};
			};
		};
	};
	class Truck_01_Base;
	class Truck_01_Covered: Truck_01_Base
	{
		attachments[] +=
		{
			"ZenCassette"
		};
		class GUIInventoryAttachmentsProps
		{
			class ZenMusic
			{
				name = "$STR_CfgVehicles_ZenCassette0";
				description = "$STR_CfgVehicles_ZenCassette0";
				icon = "Cassette";
				attachmentSlots[] =
				{
					"ZenCassette"
				};
			};
		};
	};

	// Static music boombox
	class Zen_BoomBox_Static : Inventory_Base
    {
		scope=1;
		storageCategory = 10;
        displayName = "$STR_CfgVehicles_ZenBoombox0";
        descriptionShort = "$STR_CfgVehicles_ZenBoombox1";
		initVolume = 0.5;
        maxVolume = 1.0;
		attractsZombies = "false";
        model = "\ZenMusicBase\data\models\music\boombox\zen_boombox.p3d";
		itemBehaviour = 1;
        weight = 99999;
        itemSize[] = {4,3};
        attachments[] =
        {
            "BatteryD",
            "ZenCassette"
        };
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 99999;
					healthLevels[] =
					{

						{
							1,

							{
								"ZenMusicBase\data\textures\music\boombox\boombox.rvmat"
							}
						},

						{
							0.69999999,

							{
								"ZenMusicBase\data\textures\music\boombox\boombox.rvmat"
							}
						},

						{
							0.5,

							{
								"ZenMusicBase\data\textures\music\boombox\boombox_damage.rvmat"
							}
						},

						{
							0.30000001,

							{
								"ZenMusicBase\data\textures\music\boombox\boombox_damage.rvmat"
							}
						},

						{
							0,

							{
								"ZenMusicBase\data\textures\music\boombox\boombox_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};

	// Static invisible music boombox
	class Zen_BoomBox_Invisible_Static : Zen_BoomBox_Static
    {
		scope=1;
		storageCategory = 10;
		initVolume = 0.4;
		maxVolume = 0.4;
		displayName = "";
		descriptionShort = "";
		model = "\dz\gear\consumables\Stone.p3d";
		hiddenSelections[] = { "zbytek" };
		hiddenSelectionsTextures[] = { "#(argb,8,8,3)color(1,1,1,0,CA)" };
	};

	// Radio boombox 
	class Zen_BoomBox_Static_Radio : Zen_BoomBox
    {
		scope = 1;
		initVolume = 0.5;
		maxVolume = 1.0;
	};

	// Radio intermissions
	class Zen_RadioIntermission : Zen_Cassette_Base
	{
		scope = 2;
		displayName = "87.8 Survivor FM";
		descriptionShort = "You're listening to 87.8 Survivor FM.";
		playSeconds = 5;
		allowRandomSpawn = 0;
	};
};

class CfgSlots
{
	//! MUSIC 
	class Slot_ZenCassette
    {
        name = "ZenCassette";
        displayName = "$STR_CfgVehicles_ZenCassette0";
		ghostIcon = "set:zen_music image:cassette_icon";
    };
};

class CfgSoundShaders
{
	//! MUSIC
	class Zen_Cassette_SoundShader_Base
    {
        samples[] = {};
        frequency = 1;
        range = 100;
        volume = 1;
    };

	class Zen_SoundShader_RadioIntermission : Zen_Cassette_SoundShader_Base 
	{
		samples[] = 
		{ 
			{
				"ZenMusicBase\data\sounds\radio\radio1",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio2",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio3",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio4",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio5",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio6",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio7",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio9",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio10",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio11",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio12",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio13",
				1
			},
			
			{
				"ZenMusicBase\data\sounds\radio\radio14",
				1
			}
		}; 
	};
};

class CfgSoundSets
{
	class Zen_RadioIntermission_SoundSet { soundShaders[] = { "Zen_SoundShader_RadioIntermission" }; volumeFactor = 0.5; };
};