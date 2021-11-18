#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Lists.hpp"
#include "Natives.hpp"
#include "Timer.hpp"
#include "Translation.hpp"
#include "CustomText.hpp"
#include "UI/UIManager.hpp"
#include "UI/BoolOption.hpp"
#include "UI/ChooseOption.hpp"
#include "UI/NumberOption.hpp"
#include "UI/RegularOption.hpp"
#include "UI/SubOption.hpp"
#include "UI/RegularSubmenu.hpp"
#include "UI/PlayerSubmenu.hpp"
#include "Functions/game_function.hpp"
#include "Functions/features.hpp"
#include "Functions/memory_address.hpp"
#include "ScriptLocal.hpp"
#include "Functions/game_helper.hpp"
#include "Functions/vehicle_value.h"

namespace big
{
	enum Submenu : std::uint32_t
	{
		SubmenuHome,
		SubmenuSettings,
		SubmenuSettingsHeader,
		SubmenuSettingsHeaderStaticBackground,
		SubmenuSettingsHeaderGradientBackground,
		SubmenuSettingsHeaderText,
		SubmenuSettingsSubmenuBar,
		SubmenuSettingsOption,
		SubmenuSettingsFooter,
		SubmenuSettingsDescription,
		SubmenuSettingsInput,
		SubmenuSettingsLanguage,
		SubmenuSelectedPlayer,
		SubmenuPlayerList,
		SubmenuTest,
		SubmenuHeist,
		SubmenuCasino,
		SubmenuCayo,
		SubmenuVehicle,
		SubmenuBusiness,
		SubmenuOnline,
		SubmenuVehicleCategory,
		SubmenuVehicleList,
		SubmenuLSCustoms,
		SubmenuModList,
		SubmenuProtection,
		SubmenuTeleport,
		SubmenuWeapon,
		SubmenuSession,
		SubmenuMC,
		SubmenuBunker,
		SubmenuSpecialCargo,
		SubmenuNightclub
	};

	bool MainScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType MainScript::GetType()
	{
		return ScriptType::Game;
	}

	void MainScript::Initialize()
	{
		m_Initialized = true;
		using namespace UserInterface;

		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_JOINING"), "You're Using " BIGBASE_NAME " - Gold Edition");
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_TRANSP"), "You're Using " BIGBASE_NAME " - Gold Edition");

		g_UiManager->AddSubmenu<RegularSubmenu>("Home", SubmenuHome, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Self", nullptr, SubmenuTest);
			sub->AddOption<SubOption>("Teleport", nullptr, SubmenuTeleport);
			sub->AddOption<SubOption>("Vehicle", nullptr, SubmenuVehicle);
			sub->AddOption<SubOption>("Online", nullptr, SubmenuOnline);
			sub->AddOption<SubOption>("Players", nullptr, SubmenuPlayerList);
			sub->AddOption<SubOption>("Protection", nullptr, SubmenuProtection);
			sub->AddOption<SubOption>("Settings", nullptr, SubmenuSettings);
			
			//sub->AddOption<BoolOption<bool>>("Log Script Events", nullptr, &g_LogScriptEvents, BoolDisplay::OnOff);
			sub->AddOption<RegularOption>("Unload", "Unload the menu.", []
			{
				g_Running = false;
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Teleport Option", SubmenuTeleport, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Teleport Waypoint", nullptr, []
			{
				teleport::teleport_to_marker();
			}); 
			sub->AddOption<RegularOption>("Teleport Objective", nullptr, []
			{
				teleport::teleport_to_objective();
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Protection Option", SubmenuProtection, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Force Invite Apartment", nullptr, &g_protection.block_apartment, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Force Teleport Cayo", nullptr, &g_protection.block_cayo, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("CEO Kick", nullptr, &g_protection.block_ceo_kick, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("CEO Ban", nullptr, &g_protection.block_ceo_ban, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Vehicle Kick", nullptr, &g_protection.block_vehicle_kick, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Rotate Cam", nullptr, &g_protection.block_rotate_cam, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Sound Spam", nullptr, &g_protection.block_spam, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Transaction Error", nullptr, &g_protection.block_transaction_error, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Force Send Mission", nullptr, &g_protection.block_send_mission, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Kick", nullptr, &g_protection.block_kick, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Block Freeze", nullptr, &g_protection.clear_ped_task, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Report Block", nullptr, &g_protection.block_report, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Remove Weapon", nullptr, &g_protection.block_remove_weapon, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Kick Vote", nullptr, &g_protection.block_kick_vote, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Request Control", nullptr, &g_protection.block_request_control, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Explosion Event", nullptr, &g_protection.block_explosion_event, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("PTFX Event", nullptr, &g_protection.block_ptfx_event, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Invalid Model", nullptr, &g_protection.crash, BoolDisplay::YesNo);

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Online Option", SubmenuOnline, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Session Option", nullptr, SubmenuSession);
			sub->AddOption<SubOption>("Heist", nullptr, SubmenuHeist);
			sub->AddOption<SubOption>("Business", nullptr, SubmenuBusiness);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Session Option", SubmenuSession, [](RegularSubmenu* sub)
		{
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Session", nullptr, &Lists::session_list, &Lists::session_list_pos, false, []
				{
					switch (Lists::session_list_pos)
					{
					case 0:
						network::set_session(0);
						break;
					case 1:
						network::set_session(1);
						break;
					case 2:
						network::set_session(2);
						break;
					case 3:
						network::set_session(3);
						break;
					case 4:
						network::set_session(6);
						break;
					case 5:
						network::set_session(9);
						break;
					case 6:
						network::set_session(10);
						break;
					case 7:
						network::set_session(11);
						break;
					case 8:
						network::set_session(12);
						break;
					case 9:
						network::set_session(13);
						break;
					case 10:
						network::set_session(-1);
						break;
					}
				});
			sub->AddOption<RegularOption>("Choose Character", nullptr, []
				{
					*script_global(g_global.session_unk_1).as<int*>() = 0;
					*script_global(g_global.session_change).at(2).as<int*>() = 0;
					*script_global(g_global.session_change).as<int*>() = 65;
					*script_global(g_global.session_unk_2).as<int*>() = 1;
					*script_global(g_global.session_unk_3).as<int*>() = 4;
				});
			sub->AddOption<RegularOption>("Creator Mode", nullptr, []
				{
					*script_global(g_global.session_unk_1).as<int*>() = 2;
					*script_global(g_global.session_change).at(2).as<int*>() = 2;
					*script_global(g_global.session_change).as<int*>() = 1;
				});
			sub->AddOption<RegularOption>("Disconnect", nullptr, []
				{
					NETWORK::NETWORK_BAIL(49, 0, 0);
				});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Option", SubmenuVehicle, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Godmode", nullptr, &g_features.vehicle_godmode, BoolDisplay::OnOff);
			sub->AddOption<RegularOption>("Repair Vehicle", nullptr, []
			{
				vehicle::repair_vehicle(PLAYER::PLAYER_PED_ID());
			});
			sub->AddOption<RegularOption>("Get Personal Vehicle", nullptr, []
			{
				auto vehicle = vehicle::get_personal_vehicle(PLAYER::PLAYER_ID());
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
			});
			sub->AddOption<RegularOption>("Remove Insurance", nullptr, []
			{
				vehicle::remove_insurance();
			});
			sub->AddOption<SubOption>("Vehicle Spawn", nullptr, SubmenuVehicleCategory);
			sub->AddOption<SubOption>("LS Customs", "Must Be In Vehicle", SubmenuLSCustoms);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Los Santos Customs", SubmenuLSCustoms, [](RegularSubmenu* sub)
		{
			game_helper::get_vehicle_mod();
			if (!g_game_helper.slot_display_names.empty())
			{
				sub->AddOption<RegularOption>("Full Upgrade", nullptr, []
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE))
					{
						Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
						VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_XENONHEADLIGHTS, TRUE);
						VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TURBO, TRUE);
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 0, TRUE);
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 1, TRUE);
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 2, TRUE);
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 3, TRUE);
						VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, NEON_COLOR_RED);
						VEHICLE::_SET_VEHICLE_XENON_LIGHTS_COLOR(vehicle, 8);
						VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);

						for (int i = 0; i < 50; i++)
						{
							VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, TRUE);
						}
						VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, 9);
						VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_FRONTWHEEL, 52, TRUE);
					}
				});
				sub->AddOption<BoolOption<bool>>("Bulletproof Tires", nullptr, &g_game_helper.can_tires_burst, BoolDisplay::OnOff, false, []
				{
					VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(g_game_helper.player_vehicle, !g_game_helper.can_tires_burst);
				});
				sub->AddOption<BoolOption<bool>>("Tiresmoke", nullptr, &g_game_helper.tiresmoke, BoolDisplay::OnOff, false, []
				{
					VEHICLE::TOGGLE_VEHICLE_MOD(g_game_helper.player_vehicle, MOD_TIRESMOKE, g_game_helper.tiresmoke);
				});
				sub->AddOption<BoolOption<bool>>("Turbo", nullptr, &g_game_helper.turbo, BoolDisplay::OnOff, false, []
				{
					VEHICLE::TOGGLE_VEHICLE_MOD(g_game_helper.player_vehicle, MOD_TURBO, g_game_helper.turbo);
				});
				sub->AddOption<BoolOption<bool>>("Xenon Light", nullptr, &g_game_helper.xenon, BoolDisplay::OnOff, false, []
				{
					VEHICLE::TOGGLE_VEHICLE_MOD(g_game_helper.player_vehicle, MOD_XENONHEADLIGHTS, g_game_helper.xenon);
				});
				sub->AddOption<ChooseOption<const char*, std::int32_t>>("Xenon Light Colour", nullptr, &g_game_helper.xenonColourCaptions, &g_game_helper.selected_xenon, false, []
				{
					VEHICLE::_SET_VEHICLE_XENON_LIGHTS_COLOR(g_game_helper.player_vehicle, g_game_helper.selected_xenon - 1);
				});
				for (int slot = MOD_SPOILERS; slot <= MOD_LIVERY; slot++)
				{
					if (g_game_helper.slot_display_names[slot].empty())
						continue;
					sub->AddOption<SubOption>(g_game_helper.slot_display_names[slot].c_str(), nullptr, SubmenuModList, [=]
					{
						g_game_helper.selected_slot = slot;
					});
						
				}
			}
		});
		
		g_UiManager->AddSubmenu<RegularSubmenu>("Modification", SubmenuModList, [](RegularSubmenu* sub)
		{
				if (g_game_helper.selected_slot != -1)
				{
					for (int i = 0; i < g_game_helper.mod_display_names[g_game_helper.selected_slot].size(); i++)
					{
						if (g_game_helper.mod_display_names[g_game_helper.selected_slot][i].empty())
							continue;

						sub->AddOption<RegularOption>(g_game_helper.mod_display_names[g_game_helper.selected_slot][i].c_str(), nullptr, [=]
						{
							g_CallbackScript->AddCallback<NetworkControlCallback>((PLAYER::PLAYER_PED_ID()), [=]
							{
								g_game_helper.owned_mods[g_game_helper.selected_slot] = i;
								VEHICLE::SET_VEHICLE_MOD(g_game_helper.player_vehicle, g_game_helper.selected_slot, i - 1, false);
							});
						});
					}
				}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Vehicle Spawn", SubmenuVehicleCategory, [](RegularSubmenu* sub)
		{
			for (auto i = 0; i <= _ARRAYSIZE(game_variable::VehicleCategory); ++i)
			{
				sub->AddOption<SubOption>(game_variable::VehicleCategory[i], nullptr, SubmenuVehicleList, [=]
				{
					g_selected.vehicle_category = i;
				});
			}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("List Of Vehicle", SubmenuVehicleList, [](RegularSubmenu* sub)
		{
				sub->AddOption<BoolOption<bool>>("Auto Get-in", nullptr, &g_game_helper.auto_getin, BoolDisplay::OnOff);
				sub->AddOption<BoolOption<bool>>("Full Upgrade", nullptr, &g_game_helper.full_upgrade, BoolDisplay::OnOff);
				switch (g_selected.vehicle_category)
				{
				case 0:
					for (auto selected_vehicle : game_variable::Super)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 1:
					for (auto selected_vehicle : game_variable::Sport)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 2:
					for (auto selected_vehicle : game_variable::SportClassic)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 3:
					for (auto selected_vehicle : game_variable::SummerUpdate)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 4:
					for (auto selected_vehicle : game_variable::Sedan)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 5:
					for (auto selected_vehicle : game_variable::Service)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 6:
					for (auto selected_vehicle : game_variable::SUV)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 7:
					for (auto selected_vehicle : game_variable::Plane)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 8:
					for (auto selected_vehicle : game_variable::Helicopter)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 9:
					for (auto selected_vehicle : game_variable::OffRoad)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 10:
					for (auto selected_vehicle : game_variable::Muscle)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 11:
					for (auto selected_vehicle : game_variable::Motorcycle)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 12:
					for (auto selected_vehicle : game_variable::Military)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 13:
					for (auto selected_vehicle : game_variable::Trailer)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 14:
					for (auto selected_vehicle : game_variable::Train)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 15:
					for (auto selected_vehicle : game_variable::Utility)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 16:
					for (auto selected_vehicle : game_variable::Van)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 17:
					for (auto selected_vehicle : game_variable::ArenaWar)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 18:
					for (auto selected_vehicle : game_variable::Casino1)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 19:
					for (auto selected_vehicle : game_variable::Casino2)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 20:
					for (auto selected_vehicle : game_variable::Emergency)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 21:
					for (auto selected_vehicle : game_variable::Industrial)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 22:
					for (auto selected_vehicle : game_variable::Coupes)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 23:
					for (auto selected_vehicle : game_variable::Compact)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 24:
					for (auto selected_vehicle : game_variable::Boat)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 25:
					for (auto selected_vehicle : game_variable::Bikes)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 26:
					for (auto selected_vehicle : game_variable::Commericals)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 27:
					for (auto selected_vehicle : game_variable::CayoPerico)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				case 28:
					for (auto selected_vehicle : game_variable::tuner_update)
					{
						sub->AddOption<RegularOption>(selected_vehicle, nullptr, [=]
						{
							vehicle::create_vehicle(selected_vehicle, PLAYER::PLAYER_PED_ID());
						});
					}
					break;
				}
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Business Option", SubmenuBusiness, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Set As Public", nullptr, &g_features.vehicle_godmode, BoolDisplay::OnOff);
			sub->AddOption<SubOption>("MC Business", nullptr, SubmenuMC);
			sub->AddOption<SubOption>("Bunker Business", nullptr, SubmenuBunker);
			sub->AddOption<SubOption>("Special Cargo Business", nullptr, SubmenuSpecialCargo);
			sub->AddOption<SubOption>("Nightclub Business", nullptr, SubmenuNightclub);

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Nightclub Business", SubmenuNightclub, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Trigger Nightclub Production", nullptr, []
			{
				business::trigger_nightclub_production();
			});

			sub->AddOption<RegularOption>("Trigger Nightclub Production", nullptr, []
			{
				const auto mpx = std::to_string(*script_global(1312763).as<int*>());
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLUB_POPULARITY"), 1000, TRUE);
			});

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Special Cargo Business", SubmenuSpecialCargo, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<int32_t>>("Special Cargo Money", "Money Option", &g_features.cargo_money, 0, 6000000, 100000, 3, false, "", "", []
			{
				business::special_cargo_selling_mission(g_features.cargo_money);
			});

			sub->AddOption<NumberOption<int32_t>>("Special Cargo Crates", "Money Option", &g_features.cargo_crates, 0, 111, 1, 3, false, "", "", []
			{
				business::special_cargo_crates(g_features.cargo_crates);
			});

			sub->AddOption<BoolOption<bool>>("Remove Sell Cooldown", nullptr, &g_features.sell_cargo_cooldown, BoolDisplay::OnOff, false, []
			{
				if (g_features.sell_cargo_cooldown)
					*script_global(g_global.special_cargo_selling_cooldown).as<int*>() = 0;
				else
					*script_global(g_global.special_cargo_selling_cooldown).as<int*>() = 1800000;
			});

			sub->AddOption<BoolOption<bool>>("Remove Buy Cooldown", nullptr, &g_features.buy_cargo_cooldown, BoolDisplay::OnOff, false, []
			{
				if (g_features.buy_cargo_cooldown)
					*script_global(g_global.special_cargo_buying_cooldown).as<int*>() = 0;
				else
					*script_global(g_global.special_cargo_buying_cooldown).as<int*>() = 300000;
			});

			sub->AddOption<BoolOption<bool>>("Extend Selling Timer", nullptr, &g_features.cargo_selling_time, BoolDisplay::OnOff, false, []
			{
				if (g_features.cargo_selling_time)
					*script_global(g_global.special_cargo_selling_time).as<int*>() = 18000000;
				else
					*script_global(g_global.special_cargo_selling_time).as<int*>() = 1800000;
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Bunker Business", SubmenuBunker, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<int32_t>>("Bunker Money", "Money Option", &g_features.bunker_business_money, 0, 5000000, 100000, 3, false, "", "", []
			{
				business::bunker_selling_mission(g_features.bunker_business_money);
			});

			sub->AddOption<RegularOption>("Trigger Bunker Production", nullptr, []
			{
				business::trigger_bunker_production(PLAYER::PLAYER_ID());
			});

			sub->AddOption<RegularOption>("Trigger Bunker Research", nullptr, []
			{
				business::trigger_bunker_research(PLAYER::PLAYER_ID());
			});

			sub->AddOption<BoolOption<bool>>("Remove Supply Delay", nullptr, &g_features.bunker_supply_bool, BoolDisplay::OnOff, false, []
			{
				if (g_features.bunker_supply_bool)
					*script_global(g_global.bunker_supplies_delay).as<int*>() = 0;
				else
					*script_global(g_global.bunker_supplies_delay).as<int*>() = 600;
			});

			sub->AddOption<BoolOption<bool>>("Extend Selling TImer", nullptr, &g_features.bunker_supply_bool, BoolDisplay::OnOff, false, []
			{
				if (g_features.bunker_timer_bool)
				{
					*script_global(g_global.bunker_selling_time_1).as<int*>() = 18000000;
					*script_global(g_global.bunker_selling_time_2).as<int*>() = 9000000;
					*script_global(g_global.bunker_selling_time_3).as<int*>() = 9000000;
					*script_global(g_global.bunker_selling_time_4).as<int*>() = 9000000;
					*script_global(g_global.bunker_selling_time_5).as<int*>() = 9000000;
					*script_global(g_global.bunker_selling_time_6).as<int*>() = 9000000;
				}
				else
				{
					*script_global(g_global.bunker_selling_time_1).as<int*>() = 1800000;
					*script_global(g_global.bunker_selling_time_2).as<int*>() = 900000;
					*script_global(g_global.bunker_selling_time_3).as<int*>() = 900000;
					*script_global(g_global.bunker_selling_time_4).as<int*>() = 900000;
					*script_global(g_global.bunker_selling_time_5).as<int*>() = 900000;
					*script_global(g_global.bunker_selling_time_6).as<int*>() = 900000;
				}
			});

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("MC Business", SubmenuMC, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<int32_t>>("MC Business Money", "Money Option", &g_features.mc_business_money, 0, 2500000, 100000, 3, false, "", "", []
			{
				business::biker_selling_mission(g_features.mc_business_money);
			});

			sub->AddOption<RegularOption>("Trigger Meth Production", nullptr, []
			{
				business::trigger_meth_production(PLAYER::PLAYER_ID());
			});

			sub->AddOption<RegularOption>("Trigger Weed Production", nullptr, []
			{
				business::trigger_weed_production(PLAYER::PLAYER_ID());
			});

			sub->AddOption<RegularOption>("Trigger Cocain Production", nullptr, []
			{
				business::trigger_cocain_production(PLAYER::PLAYER_ID());
			});

			sub->AddOption<RegularOption>("Trigger Cash Production", nullptr, []
			{
				business::trigger_cash_production(PLAYER::PLAYER_ID());
			});

			sub->AddOption<RegularOption>("Trigger Document Production", nullptr, []
			{
				business::trigger_document_production(PLAYER::PLAYER_ID());
			});

			sub->AddOption<BoolOption<bool>>("Remove Supply Delay", nullptr, &g_features.mc_supply_bool, BoolDisplay::OnOff, false, []
			{
				if (g_features.mc_supply_bool)
					*script_global(g_global.mc_supplies_delay).as<int*>() = 0;
				else
					*script_global(g_global.mc_supplies_delay).as<int*>() = 600;
			});

			sub->AddOption<BoolOption<bool>>("Extend Selling Timer", nullptr, &g_features.mc_timer_bool, BoolDisplay::OnOff, false, []
			{
				if (g_features.mc_timer_bool)
				{
					*script_global(g_global.mc_selling_time_1).as<int*>() = 18000000;
					*script_global(g_global.mc_selling_time_2).as<int*>() = 18000000;
					*script_global(g_global.mc_selling_time_3).as<int*>() = 18000000;
					*script_global(g_global.mc_selling_time_4).as<int*>() = 18000000;
					*script_global(g_global.mc_selling_time_5).as<int*>() = 18000000;
					*script_global(g_global.mc_selling_time_6).as<int*>() = 18000000;
					*script_global(g_global.mc_selling_time_7).as<int*>() = 18000000;
					*script_global(g_global.mc_selling_time_8).as<int*>() = 18000000;
					*script_global(g_global.mc_selling_time_9).as<int*>() = 18000000;
					*script_global(g_global.mc_selling_time_10).as<int*>() = 18000000;
				}
				else
				{
					*script_global(g_global.mc_selling_time_1).as<int*>() = 1800000;
					*script_global(g_global.mc_selling_time_2).as<int*>() = 1800000;
					*script_global(g_global.mc_selling_time_3).as<int*>() = 1800000;
					*script_global(g_global.mc_selling_time_4).as<int*>() = 1800000;
					*script_global(g_global.mc_selling_time_5).as<int*>() = 1800000;
					*script_global(g_global.mc_selling_time_6).as<int*>() = 1800000;
					*script_global(g_global.mc_selling_time_7).as<int*>() = 1800000;
					*script_global(g_global.mc_selling_time_8).as<int*>() = 1800000;
					*script_global(g_global.mc_selling_time_9).as<int*>() = 1800000;
					*script_global(g_global.mc_selling_time_10).as<int*>() = 1800000;
				}
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Self Option", SubmenuTest, [](RegularSubmenu* sub)
		{
			/*
			sub->AddOption<RegularOption>("Spawn T20", "A regular option.", []
			{
				constexpr Hash vehiclehash = RAGE_JOAAT("T20");
				g_CallbackScript->AddCallback<ModelCallback>((vehiclehash), [=]
				{
					auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
					*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x9090;
					Vehicle vehicle = VEHICLE::CREATE_VEHICLE(vehiclehash, pos.x, pos.y, pos.z, 0.f, TRUE, FALSE, FALSE);
					*(unsigned short*)g_GameVariables->m_ModelSpawnBypass = 0x0574; // By writing the "old" bypass to the function, running CREATE_VEHICLE, then restoring it, the anti-cheat does not have enough time to catch the function in a dirty state.

					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehiclehash);
					if (NETWORK::NETWORK_IS_SESSION_STARTED())
					{
						DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
						ENTITY::_SET_ENTITY_SOMETHING(vehicle, TRUE); // True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
						auto networkId = NETWORK::VEH_TO_NET(vehicle);
						if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
							NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
						VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
					}
				});
			});
			*/
			sub->AddOption<SubOption>("Weapon Option", nullptr, SubmenuWeapon);
			sub->AddOption<BoolOption<bool>>("Godmode", nullptr, &g_features.godmode, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("No Idle Kick", nullptr, &g_features.no_idle_kick, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Auto Heal", nullptr, &g_features.auto_heal, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Never Wanted", nullptr, &g_features.never_wanted, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Seatbelt", nullptr, &g_features.seatbelt, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Pass Through Wall", nullptr, &g_features.no_collision, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("No Clip", nullptr, &g_features.no_clip, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Super Jump", nullptr, &g_features.super_jump, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Explosive Fist", nullptr, &g_features.explosive_fist, BoolDisplay::OnOff);
			
			sub->AddOption<NumberOption<std::int32_t>>("Wanted Level", nullptr, &get_local_ped()->m_playerinfo->m_wanted_level, 0, 5);
			sub->AddOption<NumberOption<float>>("Run Speed", nullptr, &get_local_playerinfo()->m_run_speed, 0.f, 10.f, 0.1f, 1);
			sub->AddOption<NumberOption<float>>("Swim Speed", nullptr, &get_local_playerinfo()->m_swim_speed, 0.f, 10.f, 0.1f, 1);
			sub->AddOption<NumberOption<float>>("Sneak Speed", nullptr, &get_local_playerinfo()->m_sneak_speed, 0.f, 10.f, 0.1f, 1);

			static std::vector<std::uint64_t> vector{ 1, 2, 3 };
			static size_t vectorPos{};

			sub->AddOption<ChooseOption<const char*, std::size_t>>("Array", nullptr, &Lists::DemoList, &Lists::DemoListPos);
			sub->AddOption<ChooseOption<std::uint64_t, std::size_t>>("Vector", nullptr, &vector, &vectorPos);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Weapon Option", SubmenuWeapon, [](RegularSubmenu* sub) 
		{
			sub->AddOption<RegularOption>("Give Weapon", nullptr, []
			{
				int MaxAmmo;
				for (auto WeaponList : game_variable::AllWeaponHashes)
				{
					if (!WEAPON::HAS_PED_GOT_WEAPON(PLAYER::PLAYER_PED_ID(), joaat(WeaponList), FALSE))
					{
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), joaat(WeaponList), (WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), joaat(WeaponList), &MaxAmmo) == TRUE) ? MaxAmmo : 9999, FALSE);
						for (auto ComponentHashes : game_variable::AllComponentHashes)
						{
							WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), RAGE_JOAAT("WEAPON_MILITARYRIFLE"), 3);
							WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), RAGE_JOAAT("WEAPON_MINIGUN"), 3);
							WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::PLAYER_PED_ID(), RAGE_JOAAT("WEAPON_GRENADELAUNCHER"), 3);
							WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::PLAYER_PED_ID(), joaat(WeaponList), joaat(ComponentHashes));
						}
					}
				}
			});
			sub->AddOption<BoolOption<bool>>("Infinite Ammo", nullptr, &g_features.infinite_ammo, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Infinite Clip", nullptr, &g_features.infinite_clip, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Explosive Ammo", nullptr, &g_features.explosive_ammo, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Fire Ammo", nullptr, &g_features.fire_ammo, BoolDisplay::OnOff);
		});
		
		g_UiManager->AddSubmenu<RegularSubmenu>("Heist Option", SubmenuHeist, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Casino Heist", nullptr, SubmenuCasino);

			sub->AddOption<SubOption>("Cayo Perico Heist", nullptr, SubmenuCayo);

			sub->AddOption<RegularOption>("Doomsday Act III Hack", "Instantly Hack Clifford", [=]
				{
					if (auto doomsday = find_script_thread(RAGE_JOAAT("fm_mission_controller")))
					{
						*script_local(doomsday, m_local.doomsday_act_3_hack).as<int*>() = 0;
					}
				});

			sub->AddOption<RegularOption>("Motherboard Hacking", "Instant Fleeca Motherboard Hacking", [=]
				{
					if (auto fleeca_bank = find_script_thread(RAGE_JOAAT("fm_mission_controller")))
					{
						*script_local(fleeca_bank, m_local.board_hacking_x).as<float*>() = 0.7f;
						*script_local(fleeca_bank, m_local.board_hacking_y).as<float*>() = 0.3f;
						*script_local(fleeca_bank, m_local.board_hacking_requirement).as<int*>() = 1;
					}
				});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Casino Heist", SubmenuCasino, [](RegularSubmenu* sub)
		{
			static int32_t casino_take{ 0 };
			sub->AddOption<NumberOption<int32_t>>("Heist Take", "Casino Heist Take", &casino_take, 0, INT32_MAX, 10000000, 3, true, "", "", []
			{
				casino_heist::all_heist_take(casino_take);
			});

			sub->AddOption<NumberOption<std::int32_t>>("Casino Cut Player 1", nullptr, script_global(g_global.casino_cut_1).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Casino Cut Player 2", nullptr, script_global(g_global.casino_cut_2).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Casino Cut Player 3", nullptr, script_global(g_global.casino_cut_3).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Casino Cut Player 4", nullptr, script_global(g_global.casino_cut_4).as<int*>(), 0, 100, 5);

			sub->AddOption<ChooseOption<const char*, std::size_t>>("Skip Heist Prep", "Skip Heist Preparation Mission", &Lists::casino_heist, &Lists::casino_heist_pos, false,[]
			{
				const auto mpx = std::to_string(*script_global(1312763).as<int*>());
				switch (Lists::casino_heist_pos)
				{
				case 0:
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_APPROACH"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_LAST_APPROACH"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_HARD_APPROACH"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_TARGET"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_DISRUPTSHIP"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_KEYLEVELS"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_CREWWEAP"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_CREWDRIVER"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_CREWHACKER"), 4, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_VEHS"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_WEAPS"), 0, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_BITSET1"), 159, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_BITSET0"), 392982, TRUE);
					break;
				case 1:
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_APPROACH"), 1, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_LAST_APPROACH"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_HARD_APPROACH"), 1, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_TARGET"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_DISRUPTSHIP"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_KEYLEVELS"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_CREWWEAP"), 5, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_CREWDRIVER"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_CREWHACKER"), 4, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_VEHS"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_WEAPS"), 1, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_BITSET1"), 127, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_BITSET0"), 62, TRUE);
					break;
				case 2:
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_APPROACH"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_LAST_APPROACH"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_HARD_APPROACH"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_TARGET"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_DISRUPTSHIP"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_KEYLEVELS"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_CREWWEAP"), 5, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_CREWDRIVER"), 2, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_CREWHACKER"), 4, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_VEHS"), 3, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_WEAPS"), 1, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_BITSET1"), 799, TRUE);
					STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_BITSET0"), 3670038, TRUE);
					break;
				}
			});
			
			sub->AddOption<RegularOption>("Instant Drill", "Instantly Drill Vault Door", [=]
			{
				if (auto vault_door = find_script_thread(RAGE_JOAAT("fm_mission_controller")))
				{
					auto total = *script_local(vault_door, m_local.vault_door_total).as<int*>();
					*script_local(vault_door, m_local.vault_door).as<int*>() = total;
				}
			});

			sub->AddOption<RegularOption>("Finger Print Hack", "Instantly Finished Finger Print Hack", [=]
			{
				if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller")))
				{
					if (auto casino = find_script_thread(RAGE_JOAAT("fm_mission_controller")))
					{
						*script_local(casino, m_local.finger_print).as<int*>() += 1;
						*script_local(casino, m_local.door_hack).as<int*>() += 1;
					}
				}
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Cayo Perico heist", SubmenuCayo, [](RegularSubmenu* sub)
		{
			static int32_t cayo_perico{ 0 };
			sub->AddOption<NumberOption<int32_t>>("Heist Take", "Cayo Perico Heist Take", &cayo_perico, 0, INT32_MAX, 10000000, 3, true, "", "", []
			{
				casino_heist::all_heist_take(cayo_perico);
			});

			sub->AddOption<NumberOption<std::int32_t>>("Cayo Perico Cut Player 1", nullptr, script_global(g_global.cayo_cut_1).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Cayo Perico Cut Player 2", nullptr, script_global(g_global.cayo_cut_2).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Cayo Perico Cut Player 3", nullptr, script_global(g_global.cayo_cut_3).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Cayo Perico Cut Player 4", nullptr, script_global(g_global.cayo_cut_4).as<int*>(), 0, 100, 5);

			sub->AddOption<RegularOption>("Cayo Perico Heist", "Skip Heist Preparation Mission", [=]
			{
				const auto mpx = std::to_string(*script_global(1312763).as<int*>());
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_CASH_I"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_CASH_I_SCOPED"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_CASH_C"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_CASH_C_SCOPED"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_WEED_I"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_WEED_I_SCOPED"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_WEED_C"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_WEED_C_SCOPED"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_COKE_I"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_COKE_I_SCOPED"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_COKE_C"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_COKE_C_SCOPED"), 0, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_GOLD_I_SCOPED"), 16777215, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_GOLD_I"), 16777215, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_GOLD_C_SCOPED"), 255, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_GOLD_C"), 255, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_PAINT_SCOPED"), 255, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4LOOT_PAINT"), 255, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_BS_ENTR"), 63, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_BS_ABIL"), 63, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_WEP_DISRP"), 3, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_HEL_DISRP"), 3, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_ARM_DISRP"), 3, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_BOLTCUT"), 4641, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_GRAPPEL"), 33024, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_UNIFORM"), 16770, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_TROJAN"), 1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_APPROACH"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_VOLTAGE"), 3, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_BS_GEN"), 131071, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_WEAPONS"), 2, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4CNF_TARGET"), 5, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4_PROGRESS"), 130415, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4_MISSIONS"), 65535, TRUE);
				if (auto heist_island_planning = find_script_thread(RAGE_JOAAT("heist_island_planning")))
				{
					*script_local(heist_island_planning, m_local.submarine_computer).as<int*>() = 2;
				}
			});

			sub->AddOption<RegularOption>("Clone Finger Print Hack", "Instant Finger Print Hack", [=] 
			{
				if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020")))
				{
					if (auto cayo = find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
					{
						*script_local(cayo, m_local.finger_clone).as<int*>() += 1;
					}
				}
			});

			sub->AddOption<RegularOption>("Voltage Hack", "Instantly Finished Voltage Hack", [=]
			{
				if (auto cayo = find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
				{
					*script_local(cayo, m_local.voltage_hack_target).as<int*>() = *script_local(cayo, m_local.voltage_hack_current).as<int*>();
				}
			});

			sub->AddOption<RegularOption>("Safe Crack", "Instantly Finished Safe Crack", [=]
			{
				if (auto cayo = find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
				{
					for (int i = 0; i <= 2; i++)
					{
						*script_local(cayo, 28268).at(1).at(i, 2).as<float*>() = systems::int_to_float(*script_local(cayo, 28268).at(1).at(i, 2).at(1).as<int*>());
					}
				}
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Settings", SubmenuSettings, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Header", nullptr, SubmenuSettingsHeader);
			sub->AddOption<SubOption>("Infobar", nullptr, SubmenuSettingsSubmenuBar);
			sub->AddOption<SubOption>("Options", nullptr, SubmenuSettingsOption);
			sub->AddOption<SubOption>("Footer", nullptr, SubmenuSettingsFooter);
			sub->AddOption<SubOption>("Description", nullptr, SubmenuSettingsDescription);
			sub->AddOption<SubOption>("Input", nullptr, SubmenuSettingsInput);
			sub->AddOption<SubOption>("Language", nullptr, SubmenuSettingsLanguage);
			sub->AddOption<NumberOption<float>>("X Position", nullptr, &g_UiManager->m_PosX, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Y Position", nullptr, &g_UiManager->m_PosY, 0.f, 1.f, 0.01f, 2);
			sub->AddOption<NumberOption<float>>("Width", nullptr, &g_UiManager->m_Width, 0.01f, 1.f, 0.01f, 2);
			sub->AddOption<BoolOption<bool>>("Sounds", nullptr, &g_UiManager->m_Sounds, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<std::atomic_bool>>("Log Window", nullptr, &g_Settings.m_LogWindow, BoolDisplay::OnOff);
			sub->AddOption<RegularOption>(std::move(RegularOption("Version").SetRightText(g_GameVariables->m_GameBuild)));
			sub->AddOption<RegularOption>("Quit Game", "Quit Game.", []
			{
				exit(0);
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Language", SubmenuSettingsLanguage, [](RegularSubmenu* sub)
		{
			namespace fs = std::filesystem;
			fs::directory_iterator dirIt{ g_TranslationManager->GetTranslationDirectory() };
			for (auto&& dirEntry : dirIt)
			{
				if (dirEntry.is_regular_file())
				{
					auto path = dirEntry.path();
					if (path.has_filename())
					{
						sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
						{
							g_TranslationManager->LoadTranslations(path.stem().u8string().c_str());
						});
					}
				}
			}

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Infobar", SubmenuSettingsSubmenuBar, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_SubmenuBarHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_UiManager->m_SubmenuBarTextSize, 0.01f, 1.f, 0.01f, 2);

			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_SubmenuBarBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text R", nullptr, &g_UiManager->m_SubmenuBarTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text G", nullptr, &g_UiManager->m_SubmenuBarTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text B", nullptr, &g_UiManager->m_SubmenuBarTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Text A", nullptr, &g_UiManager->m_SubmenuBarTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Options", SubmenuSettingsOption, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_OptionHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", nullptr, &g_UiManager->m_OptionTextSize, 0.01f, 1.f, 0.01f, 2);

			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background R", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background G", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background B", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Background A", nullptr, &g_UiManager->m_OptionSelectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background R", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background G", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background B", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Background A", nullptr, &g_UiManager->m_OptionUnselectedBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));

			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text R", nullptr, &g_UiManager->m_OptionSelectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text G", nullptr, &g_UiManager->m_OptionSelectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text B", nullptr, &g_UiManager->m_OptionSelectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Selected Text A", nullptr, &g_UiManager->m_OptionSelectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text R", nullptr, &g_UiManager->m_OptionUnselectedTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text G", nullptr, &g_UiManager->m_OptionUnselectedTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text B", nullptr, &g_UiManager->m_OptionUnselectedTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Unselected Text A", nullptr, &g_UiManager->m_OptionUnselectedTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Footer", SubmenuSettingsFooter, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_FooterHeight, 0.01f, 0.1f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Sprite Size", nullptr, &g_UiManager->m_FooterSpriteSize, 0.01f, 1.f, 0.001f, 3);

			sub->AddOption<NumberOption<std::uint8_t>>("Background R", nullptr, &g_UiManager->m_FooterBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background G", nullptr, &g_UiManager->m_FooterBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background B", nullptr, &g_UiManager->m_FooterBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Background A", nullptr, &g_UiManager->m_FooterBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite R", nullptr, &g_UiManager->m_FooterSpriteColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite G", nullptr, &g_UiManager->m_FooterSpriteColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite B", nullptr, &g_UiManager->m_FooterSpriteColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("Sprite A", nullptr, &g_UiManager->m_FooterSpriteColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header", SubmenuSettingsHeader, [](RegularSubmenu* sub)
		{
			sub->AddOption<ChooseOption<const char*, std::size_t>>("Type", nullptr, &Lists::HeaderTypesFrontend, &Lists::HeaderTypesPosition, true, []
			{
				g_UiManager->m_HeaderType = Lists::HeaderTypesBackend[Lists::HeaderTypesPosition];
			});

			switch (g_UiManager->m_HeaderType)
			{
			case HeaderType::Static:
				sub->AddOption<SubOption>("Background", nullptr, SubmenuSettingsHeaderStaticBackground);
				break;
			case HeaderType::Gradient:
				sub->AddOption<SubOption>("Gradient", nullptr, SubmenuSettingsHeaderGradientBackground);
				break;
			}

			sub->AddOption<SubOption>("Text", nullptr, SubmenuSettingsHeaderText);
			sub->AddOption<NumberOption<float>>("Height", nullptr, &g_UiManager->m_HeaderHeight, 0.01f, 0.2f, 0.001f, 3);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Background", SubmenuSettingsHeaderStaticBackground, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_UiManager->m_HeaderBackgroundColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_UiManager->m_HeaderBackgroundColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_UiManager->m_HeaderBackgroundColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_UiManager->m_HeaderBackgroundColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Gradient", SubmenuSettingsHeaderGradientBackground, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Transparent", nullptr, &g_UiManager->m_HeaderGradientTransparent, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Flip", nullptr, &g_UiManager->m_HeaderGradientFlip, BoolDisplay::YesNo);

			sub->AddOption<NumberOption<std::uint8_t>>("R1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A1", nullptr, &g_UiManager->m_HeaderGradientColorLeft.a, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("R2", nullptr, &g_UiManager->m_HeaderGradientColorRight.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G2", nullptr, &g_UiManager->m_HeaderGradientColorRight.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B2", nullptr, &g_UiManager->m_HeaderGradientColorRight.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A2", nullptr, &g_UiManager->m_HeaderGradientColorRight.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Header Text", SubmenuSettingsHeaderText, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Enable", nullptr, &g_UiManager->m_HeaderText, BoolDisplay::OnOff);
			sub->AddOption<NumberOption<float>>("Size", nullptr, &g_UiManager->m_HeaderTextSize, 0.1f, 2.f, 0.01f, 2);
			sub->AddOption<NumberOption<std::uint8_t>>("R", nullptr, &g_UiManager->m_HeaderTextColor.r, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("G", nullptr, &g_UiManager->m_HeaderTextColor.g, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("B", nullptr, &g_UiManager->m_HeaderTextColor.b, '\0', static_cast<std::uint8_t>(255));
			sub->AddOption<NumberOption<std::uint8_t>>("A", nullptr, &g_UiManager->m_HeaderTextColor.a, '\0', static_cast<std::uint8_t>(255));
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Description", SubmenuSettingsDescription, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<float>>("Padding", "Padding before the description rect.", &g_UiManager->m_DescriptionHeightPadding, 0.01f, 1.f, 0.001f,
 3);
			sub->AddOption<NumberOption<float>>("Height", "Size of the description rect.", &g_UiManager->m_DescriptionHeight, 0.01f, 1.f, 0.001f, 3);
			sub->AddOption<NumberOption<float>>("Text Size", "Size of the description text.", &g_UiManager->m_DescriptionTextSize, 0.1f, 2.f, 0.01f, 2);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Input", SubmenuSettingsInput, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<std::int32_t>>("Open Delay", nullptr, &g_UiManager->m_OpenDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Back Delay", nullptr, &g_UiManager->m_BackDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Enter Delay", nullptr, &g_UiManager->m_EnterDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Vertical Delay", nullptr, &g_UiManager->m_VerticalDelay, 10, 1000, 10, 0);
			sub->AddOption<NumberOption<std::int32_t>>("Horizontal Delay", nullptr, &g_UiManager->m_HorizontalDelay, 10, 1000, 10, 0);
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Players", SubmenuPlayerList, [](RegularSubmenu* sub)
		{
			for (std::uint32_t i = 0; i < 32; ++i)
			{
				if (auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i))
				{
					sub->AddOption<SubOption>(PLAYER::GET_PLAYER_NAME(i), nullptr, SubmenuSelectedPlayer, [=]
					{
						g_selected.player = i;
						g_selected.ped = player::get_player_ped(i);
					});
				}
			}
		});

		g_UiManager->AddSubmenu<PlayerSubmenu>(&g_selected.player, SubmenuSelectedPlayer, [](PlayerSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Network Error", "Network Error", [=]
			{
				remote_event::bail_player(g_selected.player);
			});
			sub->AddOption<RegularOption>("Kick", nullptr, [=]
			{
				remote_event::kick_player(g_selected.player);
			});
			sub->AddOption<RegularOption>("CEO Ban", nullptr, [=]
			{
				remote_event::ceo_ban(g_selected.player);
			});
			sub->AddOption<RegularOption>("CEO Kick", nullptr, [=]
			{
				remote_event::ceo_kick(g_selected.player);
			});
			sub->AddOption<RegularOption>("Teleport Cayo", nullptr, [=]
			{
				remote_event::teleport_player_to_cayo(g_selected.player);
			});
			sub->AddOption<RegularOption>("Force Apartment", nullptr, [=]
			{
				remote_event::force_invite_apartment(g_selected.player);
			});
			sub->AddOption<RegularOption>("Send Mission", nullptr, [=]
			{
				remote_event::send_to_mission(g_selected.player);
			});
			sub->AddOption<RegularOption>("Vehicle Kick", nullptr, [=]
			{
				remote_event::vehicle_kick(g_selected.player);
			});
			sub->AddOption<BoolOption<bool>>("Spectate", nullptr, &g_features.spectating, BoolDisplay::OnOff, false, [=]
			{
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(g_features.spectating, g_selected.ped);
			});
		});
	}

	void MainScript::Destroy()
	{
		g_UiManager.reset();
	}

	void MainScript::Tick()
	{
		g_UiManager->OnTick();
		features::run_on_tick();
	}
}
