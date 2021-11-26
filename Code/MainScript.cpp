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

#pragma warning(disable:4477)
#pragma warning(disable:4244)

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
		SubmenuNightclub,
		SubmenuSaveTeleport,
		SubmenuRecovery,
		SubmenuStats,
		SubmenuScriptEvent,
		SubmenuTrollOption,
		SubmenuNetworkEvent,
		SubmenuDoomsday,
		SubmenuApartment,
		SubmenuSpoofer

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
		uint32_t textureID;
		char buffers[128];
		std::sprintf(buffers, "%s\\" BIGBASE_NAME "\\Headers\\zerstorer.ytd", std::getenv("appdata"));
		g_Logger->Info("Location : %s", buffers);
		g_GameFunctions->m_file_register(&textureID, buffers, true, "zerstorer.ytd", false);

		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_JOINING"), "You're Using " BIGBASE_NAME " - Gold Edition");
		g_CustomText->AddText(CONSTEXPR_JOAAT("HUD_TRANSP"), "You're Using " BIGBASE_NAME " - Gold Edition");

		g_UiManager->AddSubmenu<RegularSubmenu>("Home", SubmenuHome, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Player", nullptr, SubmenuTest);
			sub->AddOption<SubOption>("Weapon Option", nullptr, SubmenuWeapon);
			sub->AddOption<SubOption>("Teleport", nullptr, SubmenuTeleport);
			sub->AddOption<SubOption>("Vehicle", nullptr, SubmenuVehicle);
			sub->AddOption<SubOption>("Online", nullptr, SubmenuOnline);
			sub->AddOption<SubOption>("Recovery Service", nullptr, SubmenuRecovery);
			sub->AddOption<SubOption>("Online Players", nullptr, SubmenuPlayerList);
			sub->AddOption<SubOption>("Protection", nullptr, SubmenuProtection);
			sub->AddOption<SubOption>("Settings", nullptr, SubmenuSettings);
			sub->AddOption<RegularOption>("Force Cloud Save", "Unload the menu.", []
			{
					STATS::STAT_SAVE(0, 0, 3, 0);
					message::notification(BIGBASE_NAME " Gold Edition", "~bold~~g~Character Saved!", "~bold~~g~" BIGBASE_NAME " Cloud Save");
			});
			//sub->AddOption<BoolOption<bool>>("Log Script Events", nullptr, &g_LogScriptEvents, BoolDisplay::OnOff);
			sub->AddOption<RegularOption>("Unload", "Unload the menu.", []
			{
				g_Running = false;
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Recovery Option", SubmenuRecovery, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Player Stats", nullptr, SubmenuStats);

			sub->AddOption<RegularOption>("Unlock Achievement", nullptr, []
			{
				for (int i = 1; i <= 77; i++)
				{
					PLAYER::GIVE_ACHIEVEMENT_TO_PLAYER(i);
					message::notification(BIGBASE_NAME " Gold Edition","~g~All Achievements Unlocked!", "~bold~~g~" BIGBASE_NAME " Recovery");
				}
			});

			sub->AddOption<RegularOption>("Unlock Casino Shop Stuff", nullptr, []
			{
				int character = *script_global(1312763).as<int*>();
				const auto mpx = std::to_string(*script_global(1312763).as<int*>());
				for (int i = 30227; i <= 30355; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 30227), 0, 1, character, "_SU20PSTAT_BOOL"),
						true, ((i - 30227) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 30227)) * 64), 1);
				}
				for (int i = 30355; i <= 30483; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 30355), 0, 1, character, "_SU20TATTOOSTAT_BOOL"),
						true, ((i - 30355) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 30355)) * 64), 1);
				}
				for (int i = 15369; i <= 15561; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 15369), 0, 1, character, "_DLCGUNPSTAT_BOOL"),
						true, ((i - 15369) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 15369)) * 64), 1);
				}
				for (int i = 15562; i <= 15946; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 15562), 0, 1, character, "_GUNTATPSTAT_BOOL"),
						true, ((i - 15562) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 15562)) * 64), 1);
				}
				for (int i = 15946; i <= 16010; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 15946), 0, 1, character, "_DLCSMUGCHARPSTAT_BOOL"),
						true, ((i - 15946) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 15946)) * 64), 1);
				}
				for (int i = 26810; i <= 27258; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 26810), 0, 1, character, "_CASINOPSTAT_BOOL"),
						true, ((i - 26810) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 26810)) * 64), 1);
				}
				for (int i = 28098; i <= 28354; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 28098), 0, 1, character, "_CASINOHSTPSTAT_BOOL"),
						true, ((i - 28098) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 28098)) * 64), 1);
				}
				for (int i = 28355; i <= 28483; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 28355), 0, 1, character, "_HEIST3TATTOOSTAT_BOOL"),
						true, ((i - 28355) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 28355)) * 64), 1);
				}
				for (int i = 22066; i <= 22194; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 22066), 0, 1, character, "_BUSINESSBATPSTAT_BOOL"),
						true, ((i - 22066) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 22066)) * 64), 1);
				}
				for (int i = 30515; i <= 30707; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 30515), 0, 1, character, "_HISLANDPSTAT_BOOL"),
						true, ((i - 30515) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 30515)) * 64), 1);
				}
				for (int i = 31707; i <= 32283; i++)
				{
					STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 31707), FALSE, TRUE, character, "_TUNERPSTAT_BOOL"), FALSE, ((i - 31707) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 31707)) * 64), TRUE);
				}
				STATS::STAT_SET_INT(joaat("MPPLY_H3_COOLDOWN"), 0, true);
				/* LSC selling vehicles */
				STATS::STAT_SET_INT(joaat("MPPLY_VEHICLE_SELL_TIME"), 0, true);
				STATS::STAT_SET_INT(joaat("MPPLY_NUM_CARS_SOLD_TODAY"), 0, true);
				/* Mental state */
				STATS::STAT_SET_FLOAT(joaat("MPPLY_PLAYER_MENTAL_STATE"), 0.f, true);
				/* Apartament Heists */
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_COMPLET_HEIST_1STPER"), true, true);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_COMPLET_HEIST_MEM"), true, true);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_FLEECA_FIN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_PRISON_FIN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_HUMANE_FIN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_SERIESA_FIN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_PACIFIC_FIN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_HST_ORDER"), true, true);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_HST_SAME_TEAM"), true, true);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_HST_ULT_CHAL"), true, true);
				STATS::STAT_SET_INT(joaat("MPPLY_HEIST_ACH_TRACKER"), -1, true);
				/* Pilot school */
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_0"), 1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_1"), 1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_2"), 1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_3"), 1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_4"), 1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_5"), 1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_6"), 1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_7"), 1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_8"), 1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_9"), 1, true);
				
				/* Mental state */
				STATS::STAT_SET_FLOAT(joaat("MP" + mpx + "_PLAYER_MENTAL_STATE"), 0.f, true);
				/* Benny's */
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_FLOW_CS_DRV_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_FLOW_CS_TRA_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_FLOW_CS_FUN_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_FLOW_CS_PHO_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_FLOW_CS_FIN_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_BEN_INTRO_CS_SEEN"), true, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LOWRIDER_FLOW_COMPLETE"), 3, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LOW_FLOW_CURRENT_PROG"), 9, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LOW_FLOW_CURRENT_CALL"), 9, true);
				/* Apartament Heists */
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HEIST_1_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_VEHICLE_1_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_VEHICLE_2_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HEIST_COMPLETION"), -1, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ACTIVATE_2_PERSON_KEY"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ALL_ROLES_HEIST"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_PLANNING_DONE_PRINT"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_PLANNING_DONE_HELP_0"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_PLANNING_DONE_HELP_1"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_PRE_PLAN_DONE_HELP_0"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_CUTS_DONE_FINALE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_CUTS_DONE_ORNATE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_CUTS_DONE_BIOLAB"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_CUTS_DONE_PRISON"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_CUTS_DONE_NARCOTIC"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_CUTS_DONE_TUTORIAL"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_AWARD_DONE_PREP"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HEIST_AWARD_BOUGHT_IN"), true, true);
				/* Agatha Baker */
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_VCM_FLOW_CS_RSC_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_VCM_FLOW_CS_BWL_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_VCM_FLOW_CS_MTG_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_VCM_FLOW_CS_OIL_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_VCM_FLOW_CS_DEF_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_VCM_FLOW_CS_FIN_SEEN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CAS_VEHICLE_REWARD"), false, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_VCM_FLOW_PROGRESS"), 1839072, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_VCM_STORY_PROGRESS"), 0, true);
				/* Facility heists */
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_GANGOPS_HEIST_STATUS"), 9999, true);
				/* Skip cutscenes */
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_INTRO_CUT_DONE"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_CUT_DONE"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_CUT_DONE_2"), -1, true);
				/* Pilot school */
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_0"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_1"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_2"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_3"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_4"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_5"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_6"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_7"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_8"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_9"), true, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PILOT_SCHOOL_MEDAL_0"), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PILOT_SCHOOL_MEDAL_1"), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PILOT_SCHOOL_MEDAL_2"), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PILOT_SCHOOL_MEDAL_3"), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PILOT_SCHOOL_MEDAL_4"), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PILOT_SCHOOL_MEDAL_5"), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PILOT_SCHOOL_MEDAL_6"), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PILOT_SCHOOL_MEDAL_7"), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PILOT_SCHOOL_MEDAL_8"), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PILOT_SCHOOL_MEDAL_9"), 1, true);
				/* Unlock shotaro */
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRDEADLINE"), 5, true);
				/* Shooting range */
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_1"), 690, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_2"), 1860, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_3"), 2690, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_4"), 2660, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_5"), 2650, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_6"), 450, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_WEAPON_BIT_SET"), -1, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_SR_TIER_1_REWARD"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_SR_TIER_3_REWARD"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_SR_INCREASE_THROW_CAP"), true, true);
				/* LSC */
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_GTA_RACE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_RACE_MODDED_CAR"), true, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_1_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_2_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_3_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_4_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_5_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_6_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_7_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_RACES_FASTEST_LAP"), 82, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_TURBO_STARTS_IN_RACE"), 63, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_7_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_USJS_FOUND"), 50, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_USJS_COMPLETED"), 50, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_SLIPSTREAMS_IN_RACE"), 127, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FINISH_HEISTS"), 50, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FINISH_HEIST_SETUP_JOB"), 50, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMRALLYWONDRIVE "), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMRALLYWONNAV"), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMWINAIRRACE "), 1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FMWINSEARACE"), 1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES0"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES1"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES2"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES3"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES4"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES5"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES6"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES7"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES8"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES9"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES10"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES11"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES12"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES13"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES14"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES15"), -1, true);
				STATS::STAT_SET_INT(joaat("MPPLY_XMASLIVERIES16"), -1, true);
				/* Arcade */
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_BOARD_DIALOGUE0"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_BOARD_DIALOGUE1"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_BOARD_DIALOGUE2"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_VEHICLESUSED"), -1, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SCOPEOUT"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CREWEDUP"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MOVINGON"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PROMOCAMP"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GUNMAN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SMASHNGRAB"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_INPLAINSI"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_UNDETECTED"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ALLROUND"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELITETHEIF"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PRO"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SUPPORTACT"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SHAFTED"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_COLLECTOR"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_DEADEYE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PISTOLSATDAWN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_TRAFFICAVOI"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CANTCATCHBRA"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_WIZHARD"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_APEESCAPE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MONKEYKIND"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_AQUAAPE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_NEMESIS"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_TRUELOVE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FRIENDZONED"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_KINGOFQUB3D"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_QUBISM"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_QUIBITS"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GODOFQUB3D"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GOFOR11TH"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELEVENELEVEN"), true, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PREPARATION"), 40, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ASLEEPONJOB"), 20, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DAICASHCRAB"), 100000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_BIGBRO"), 40, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SHARPSHOOTER"), 40, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_RACECHAMP"), 40, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_BATSWORD"), 1000000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_COINPURSE"), 950000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ASTROCHIMP"), 3000000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_MASTERFUL"), 40000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_COINPURSE"), 950000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CH_ARC_CAB_CLAW_TROPHY"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CH_ARC_CAB_LOVE_TROPHY"), -1, true);

				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_LOSTANDFOUND"), 500000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SUNSET"), 1800000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TREASURE_HUNTER"), 1000000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WRECK_DIVING"), 1000000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_KEINEMUSIK"), 1800000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PALMS_TRAX"), 1800000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_MOODYMANN"), 1800000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FILL_YOUR_BAGS"), 10000000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WELL_PREPARED"), 50, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4_PLAYTHROUGH_STATUS"), -1, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_INTELGATHER"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_COMPOUNDINFILT"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_LOOT_FINDER"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MAX_DISRUPT"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_THE_ISLAND_HEIST"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GOING_ALONE"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_TEAM_WORK"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MIXING_UP"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PRO_THIEF"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CAT_BURGLAR"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ONE_OF_THEM"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GOLDEN_GUN"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELITE_THIEF"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PROFESSIONAL"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_HELPING_OUT"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_COURIER"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PARTY_VIBES"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_HELPING_HAND"), TRUE, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELEVENELEVEN"), TRUE, true);

				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WEAP_UNLOCKED"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WEAP_UNLOCKED2"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WEAP_ADDON_1_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WEAP_ADDON_2_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WEAP_ADDON_3_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WEAP_ADDON_4_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_UNLOCKED"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_UNLOCKED2"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_UNLOCKED3"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_1_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_2_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_3_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_4_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_5_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_6_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_7_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_8_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_9_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_10_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_11_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_12_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_13_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_14_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_15_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_16_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_17_UNLCK"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_18_UNLCK"), -1, true);

				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_STAM"), 100, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_STRN"), 100, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_FLY"), 100, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_STL"), 100, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_LUNG"), 100, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_DRIV"), 100, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_SHO"), 100, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_HEALTH_1_UNLCK"), 0xFFFFFFFF, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_HEALTH_2_UNLCK"), 0xFFFFFFFF, true);

				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_BOARD_DIALOGUE0"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_BOARD_DIALOGUE1"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_BOARD_DIALOGUE2"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_VEHICLESUSED"), -1, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SCOPEOUT"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CREWEDUP"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MOVINGON"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PROMOCAMP"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GUNMAN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SMASHNGRAB"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_INPLAINSI"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_UNDETECTED"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ALLROUND"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELITETHEIF"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PRO"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SUPPORTACT"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SHAFTED"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_COLLECTOR"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_DEADEYE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PISTOLSATDAWN"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_TRAFFICAVOI"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CANTCATCHBRA"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_WIZHARD"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_APEESCAPE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MONKEYKIND"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_AQUAAPE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_NEMESIS"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_TRUELOVE"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FRIENDZONED"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_KINGOFQUB3D"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_QUBISM"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_QUIBITS"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GODOFQUB3D"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GOFOR11TH"), true, true);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELEVENELEVEN"), true, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PREPARATION"), 40, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ASLEEPONJOB"), 20, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DAICASHCRAB"), 100000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_BIGBRO"), 40, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SHARPSHOOTER"), 40, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_RACECHAMP"), 40, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_BATSWORD"), 1000000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_COINPURSE"), 950000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ASTROCHIMP"), 3000000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_MASTERFUL"), 40000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_COINPURSE"), 950000, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CH_ARC_CAB_CLAW_TROPHY"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CH_ARC_CAB_LOVE_TROPHY"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_COMPLETEDPOSIX"), 0, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CAS_HEIST_FLOW"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_ACCESSPOINTS"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3OPT_POI"), -1, true);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_CAR_CLUB_MEM"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SPRINTRACER"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_STREETRACER"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PURSUITRACER"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TEST_CAR"), 1800000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_CAR_EXPORT"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_GROUNDWORK"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ROBBERY_CONTRACT"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FACES_OF_DEATH"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_AUTO_SHOP"), 100, TRUE);
				stats::set_packed_int(7315, 6, -1, TRUE);
				stats::set_packed_int(18981, 4, -1, TRUE);
				stats::set_packed_int(18988, 24, -1, TRUE);
				stats::set_packed_int(22032, 100, -1, TRUE);
				stats::set_packed_int(22050, 100, -1, TRUE);
				stats::set_packed_int(22051, 100, -1, TRUE);
				stats::set_packed_int(22052, 100, -1, TRUE);
				stats::set_packed_int(22053, 100, -1, TRUE);
				stats::set_packed_int(22054, 100, -1, TRUE);
				stats::set_packed_int(22055, 100, -1, TRUE);
				stats::set_packed_int(22056, 100, -1, TRUE);
				stats::set_packed_int(22057, 100, -1, TRUE);
				stats::set_packed_int(22058, 100, -1, TRUE);
				stats::set_packed_int(22063, 20, -1, TRUE);
				Any date[]{ 2014, 0, 9, 0, 17, 0, 20, 0, 30, 0, 1, 0, 1 };
				STATS::STAT_SET_DATE(joaat("MP" + mpx + "_CHAR_DATE_CREATED"), &date[0], 7, TRUE);
				STATS::STAT_SET_DATE(joaat("MP" + mpx + "_CHAR_DATE_RANKUP"), &date[0], 7, TRUE);
				STATS::STAT_SET_DATE(joaat("MPPLY_STARTED_MP"), &date[0], 7, TRUE);
				STATS::STAT_SET_DATE(joaat("MPPLY_NON_CHEATER_CASH"), &date[0], 7, TRUE);
				STATS::STAT_SET_DATE(joaat("MP" + mpx + "_CHAR_LAST_PLAY_TIME"), &date[0], 7, TRUE);
				STATS::STAT_INCREMENT(joaat("MPPLY_TOTAL_TIME_IN_LOBBY"), systems::int_to_float(INT_MAX));
				STATS::STAT_INCREMENT(joaat("MP" + mpx + "_CLOUD_TIME_CHAR_CREATED"), systems::int_to_float(1379449800));
				STATS::STAT_INCREMENT(joaat("MP" + mpx + "_PS_TIME_CHAR_CREATED"), systems::int_to_float(1379449800));
				STATS::STAT_INCREMENT(joaat("MPPLY_TOTAL_TIME_SPENT_FREEMODE"), systems::int_to_float(INT_MAX));
				STATS::STAT_INCREMENT(joaat("LEADERBOARD_PLAYING_TIME"), systems::int_to_float(INT_MAX)); // found in mpstatssetup.
				STATS::STAT_INCREMENT(joaat("MP" + mpx + "_TOTAL_PLAYING_TIME"), systems::int_to_float(INT_MAX));
				STATS::STAT_INCREMENT(joaat("MP_PLAYING_TIME_NEW"), systems::int_to_float(INT_MAX)); // found in mpstatssetup.
				STATS::STAT_INCREMENT(joaat("MP_PLAYING_TIME"), systems::int_to_float(INT_MAX)); // found in mpstatssetupui.
				STATS::STAT_INCREMENT(joaat("MP" + mpx + "_LONGEST_PLAYING_TIME"), systems::int_to_float(INT_MAX));
				STATS::STAT_SAVE(0, 0, 3, 0);
			});

			sub->AddOption<RegularOption>("Unlock All Bool Stat", nullptr, []
			{
				const auto mpx = std::to_string(*script_global(1312763).as<int*>());
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_RACE_MODDED_CAR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_DRIVE_RALLY"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_GTA_RACE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_BOAT_RACE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_FOOT_RACE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_TEAM_DM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_VEHICLE_DM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_MISSION_CONTACT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_A_PLAYLIST"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_POINT_TO_POINT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_ONE_ON_ONE_DM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PLAY_ONE_ON_ONE_RACE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_SURV_A_BOUNTY"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_SET_WANTED_LVL_ON_PLAY"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_GANG_BACKUP_GANGS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_GANG_BACKUP_LOST"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_GANG_BACKUP_VAGOS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_CALL_MERCENARIES"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_PHONE_MECH_DROP_CAR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_GONE_OFF_RADAR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_FILL_TITAN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_MOD_CAR_USING_APP"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_BUY_APPARTMENT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_BUY_INSURANCE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_BUY_GARAGE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_ENTER_FRIENDS_HOUSE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_CALL_STRIPPER_HOUSE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_CALL_FRIEND"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_SEND_FRIEND_REQUEST"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_CL_W_WANTED_PLAYER_TV"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_0"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_1"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_2"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_3"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_4"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_5"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_6"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_7"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_8"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_PILOT_ASPASSEDLESSON_9"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FIRST_TIME1"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FIRST_TIME2"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FIRST_TIME3"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FIRST_TIME4"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FIRST_TIME5"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FIRST_TIME6"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ALL_IN_ORDER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SUPPORTING_ROLE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ACTIVATE_2_PERSON_KEY"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ALL_ROLES_HEIST"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_LEADER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SURVIVALIST"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SCOPEOUT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CREWEDUP"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MOVINGON"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PROMOCAMP "), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GUNMAN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SMASHNGRAB"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_INPLAINSI "), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_UNDETECTED"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ALLROUND"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELITETHEIF"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PRO"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SUPPORTACT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SHAFTED"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_COLLECTOR "), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_DEADEYE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PISTOLSATDAWN "), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_TRAFFICAVOI"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CANTCATCHBRA"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_WIZHARD"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_APEESCAPE "), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MONKEYKIND"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_AQUAAPE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_KEEPFAITH "), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_TRUELOVE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_NEMESIS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FRIENDZONED"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_ALLINORDER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_SUPPORT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_LOYALTY2"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_CRIMMASMD2"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_LOYALTY3"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_CRIMMASMD3"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_LOYALTY"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_CRIMMASMD"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_BUY_EVERY_GUN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_DAILYOBJMONTHBONUS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_DAILYOBJWEEKBONUS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_DRIVELESTERCAR5MINS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FINISH_HEIST_NO_DAMAGE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FM25DIFFERENTDM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FM25DIFFERENTRACES"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FM25DIFITEMSCLOTHES"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMFURTHESTWHEELIE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FM6DARTCHKOUT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FM_GOLF_HOLE_IN_1"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FM_SHOOTRANG_GRAN_WON"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FM_TENNIS_5_SET_WINS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMATTGANGHQ"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMFULLYMODDEDCAR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMKILL3ANDWINGTARACE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMKILLSTREAKSDM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMMOSTKILLSGANGHIDE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMMOSTKILLSSURVIVE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMPICKUPDLCCRATE1ST"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMRACEWORLDRECHOLDER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMTATTOOALLBODYPARTS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMWINALLRACEMODES"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMWINCUSTOMRACE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FMWINEVERYGAMEMODE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SPLIT_HEIST_TAKE_EVENLY"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_STORE_20_CAR_IN_GARAGES"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_MELEECHLENGECOMPLETED"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_HEADSHOTCHLENGECOMPLETED"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_SR_TIER_1_REWARD"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_SR_TIER_3_REWARD"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_SR_INCREASE_THROW_CAP"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_COMPLET_HEIST_MEM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_COMPLET_HEIST_1STPER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_FLEECA_FIN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_HST_ORDER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_HST_SAME_TEAM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_HST_ULT_CHAL"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_HUMANE_FIN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_PACIFIC_FIN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_PRISON_FIN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_SERIESA_FIN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_IAA"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_SUBMARINE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MPPLY_AWD_GANGOPS_MISSILE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CLUB_COORD"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CLUB_HOTSPOT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CLUB_CLUBBER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_BEGINNER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FIELD_FILLER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ARMCHAIR_RACER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_LEARNER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SUNDAY_DRIVER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_THE_ROOKIE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_BUMP_AND_RUN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GEAR_HEAD"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_DOOR_SLAMMER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_HOT_LAP"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ARENA_AMATEUR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PAINT_TRADER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_SHUNTER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_JOCK"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_WARRIOR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_T_BONE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MAYHEM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_WRECKER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CRASH_COURSE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ARENA_LEGEND"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PEGASUS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CONTACT_SPORT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_UNSTOPPABLE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_FLOW_CS_DRV_SEEN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_FLOW_CS_TRA_SEEN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_FLOW_CS_FUN_SEEN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_FLOW_CS_PHO_SEEN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_FLOW_CS_FIN_SEEN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_LOW_BEN_INTRO_CS_SEEN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_FURIA"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_MINITANK"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_YOSEMITE2"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_ZHABA"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_IMORGEN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_SULTAN2"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_VAGRANT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_VSTR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_STRYDER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_SUGOI"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_KANJO"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_FORMULA"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_FORMULA2"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_HELP_JB7002"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_UNLOCK_RACE_HIPSTER_TSHIRT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_UNLOCK_DM_HIPSTER_TSHIRT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_UNLOCK_HIPSTER_TSHIRT_DOG"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_UNLOCK_HIPSTER_TSHIRT_VINYL"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_UNLOCK_HIPSTER_TSHIRT_MESS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_KINGOFQUB3D"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_QUBISM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_QUIBITS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GODOFQUB3D"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GOFOR11TH"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELEVENELEVEN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_QUIBITS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_QUIBITS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_INTELGATHER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_COMPOUNDINFILT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_LOOT_FINDER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MAX_DISRUPT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_THE_ISLAND_HEIST"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GOING_ALONE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_TEAM_WORK"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MIXING_UP"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PRO_THIEF"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CAT_BURGLAR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ONE_OF_THEM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GOLDEN_GUN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELITE_THIEF"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PROFESSIONAL"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_HELPING_OUT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_COURIER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PARTY_VIBES"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_HELPING_HAND"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELEVENELEVEN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_COMPLETE_H4_F_USING_VETIR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_COMPLETE_H4_F_USING_LONGFIN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_COMPLETE_H4_F_USING_ANNIH"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_COMPLETE_H4_F_USING_ALKONOS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_COMPLETE_H4_F_USING_PATROLB"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_INTELGATHER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_COMPOUNDINFILT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_LOOT_FINDER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MAX_DISRUPT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_THE_ISLAND_HEIST"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GOING_ALONE"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_TEAM_WORK"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MIXING_UP"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PRO_THIEF"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CAT_BURGLAR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ONE_OF_THEM"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_GOLDEN_GUN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELITE_THIEF"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PROFESSIONAL"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_HELPING_OUT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_COURIER"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PARTY_VIBES"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_HELPING_HAND"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_ELEVENELEVEN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_COMPLETE_H4_F_USING_VETIR"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_COMPLETE_H4_F_USING_LONGFIN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_COMPLETE_H4_F_USING_ANNIH"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_COMPLETE_H4_F_USING_ALKONOS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_COMPLETE_H4_F_USING_PATROLB"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_CAR_CLUB"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_PRO_CAR_EXPORT"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_UNION_DEPOSITORY"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MILITARY_CONVOY"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FLEECA_BANK"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_FREIGHT_TRAIN"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_BOLINGBROKE_ASS"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_IAA_RAID"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_METH_JOB"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_BUNKER_RAID"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_STRAIGHT_TO_VIDEO"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_MONKEY_C_MONKEY_DO"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_TRAINED_TO_KILL"), TRUE, TRUE);
				STATS::STAT_SET_BOOL(joaat("MP" + mpx + "_AWD_DIRECTOR"), TRUE, TRUE);
			});

			sub->AddOption<RegularOption>("Unlock All Int Stat", nullptr, []
			{
				const auto mpx = std::to_string(*script_global(1312763).as<int*>());
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_LOSTANDFOUND"), 500000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SUNSET"), 1800000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TREASURE_HUNTER"), 1000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WRECK_DIVING"), 1000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_KEINEMUSIK"), 1800000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PALMS_TRAX"), 1800000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_MOODYMANN"), 1800000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FILL_YOUR_BAGS"), 200000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WELL_PREPARED"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4_PLAYTHROUGH_STATUS"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_LOSTANDFOUND"), 500000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SUNSET"), 1800000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TREASURE_HUNTER"), 1000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WRECK_DIVING"), 1000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_KEINEMUSIK"), 1800000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PALMS_TRAX"), 1800000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_MOODYMANN"), 1800000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FILL_YOUR_BAGS"), 200000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WELL_PREPARED"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H4_PLAYTHROUGH_STATUS"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_MK2_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_MK2_DEATHS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_MK2_SHOTS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_MK2_HITS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_MK2_HEADSHOTS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_MK2_HELDTIME"), 5963259, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_MK2_DB_HELDTIME"), 5963259, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_MK2_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ODD_JOBS"), 52, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PREPARATION"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ASLEEPONJOB"), 20, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DAICASHCRAB"), 100000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_BIGBRO"), 40, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SHARPSHOOTER"), 40, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_RACECHAMP"), 40, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_BATSWORD"), 1000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_COINPURSE"), 950000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ASTROCHIMP"), 3000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_MASTERFUL"), 40000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DM_CURRENT_KILLS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DM_CURRENT_ASSISTS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DM_CURRENT_DEATHS"), 600, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DM_HIGHEST_KILLSTREAK"), 900, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HIGHEST_SKITTLES"), 900, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_NEAR_MISS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LAP_DANCED_BOUGHT"), 100, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_NUM_CAPTURES_CREATED"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CARS_EXPLODED"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CARS_COPS_EXPLODED"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BIKES_EXPLODED"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BOATS_EXPLODED"), 168, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HELIS_EXPLODED"), 98, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PLANES_EXPLODED"), 138, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_QUADBIKE_EXPLODED"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BICYCLE_EXPLODED"), 48, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SUBMARINE_EXPLODED"), 28, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DEATHS"), 4998, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DIED_IN_DROWNING"), 833, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DIED_IN_DROWNINGINVEHICLE"), 833, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DIED_IN_EXPLOSION"), 833, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DIED_IN_FALL"), 833, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DIED_IN_FIRE"), 833, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DIED_IN_ROAD"), 833, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NO_PHOTOS_TAKEN"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PROSTITUTES_FREQUENTED"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BOUNTSONU"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BOUNTPLACED"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PASS_DB_KILLS"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PASS_DB_PLAYER_KILLS"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PASS_DB_SHOTS"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PASS_DB_HITS"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PASS_DB_HITS_PEDS_VEHICLES"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PASS_DB_HEADSHOTS"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIRES_POPPED_BY_GUNSHOT"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_CRASHES_CARS"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_CRASHES_BIKES"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BAILED_FROM_VEHICLE"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_CRASHES_QUADBIKES"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_COP_VEHICLE"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_CARS"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_BIKES"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_BOATS"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_HELIS"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_PLANES"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_QUADBIKES"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_BICYCLES"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FAVOUTFITBIKETIMECURRENT"), 884483972, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FAVOUTFITBIKETIME1ALLTIME"), 884483972, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FAVOUTFITBIKETYPECURRENT"), 884483972, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FAVOUTFITBIKETYPEALLTIME"), 884483972, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MC_CONTRIBUTION_POINTS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MEMBERSMARKEDFORDEATH"), 268, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MCKILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MCDEATHS"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_RIVALPRESIDENTKILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_RIVALCEOANDVIPKILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MELEEKILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLUBHOUSECONTRACTSCOMPLETE"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLUBHOUSECONTRACTEARNINGS"), 32698547, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLUBCHALLENGESCOMPLETED"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MEMBERCHALLENGESCOMPLETED"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LONGEST_PLAYING_TIME"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_DRIVING_CAR"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_DRIVING_PLANE"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_DRIVING_HELI"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_DRIVING_QUADBIKE"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_DRIVING_BIKE"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_DRIVING_BICYCLE"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_DRIVING_BOAT"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_DRIVING_SUBMARINE"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_SWIMMING"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_WALKING"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_UNDERWATER"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_IN_WATER"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_IN_COVER"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_DRIVING_PASSENGER"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TOTAL_TIME_SPENT_ON_PHONE"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_AS_A_PASSENGER"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_AS_A_DRIVER"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_SPENT_FLYING"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_IN_CAR"), 1047483647, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_TIME_MISSION_CREATO"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TOTAL_TIME_UNDERWATER"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TOTAL_TIME_CINEMA"), 1047483647, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_TIME_LOAD_SCREEN"), 1047483647, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_TIME_IN_LOBBY"), 1047483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HITS"), 100000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_DEATHS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_SHOTS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_HITS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_HEADSHOTS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_HELDTIME"), 5963259, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_DB_HELDTIME"), 5963259, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MKRIFLE_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BETAMOUNT"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_GHKILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HORDELVL"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HORDKILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_UNIQUECRATES"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BJWINS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HORDEWINS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MCMWINS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_GANGHIDWINS"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_FM_MISSION_LIKES"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS"), 800, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HITS_PEDS_VEHICLES"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SHOTS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HEADSHOTS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_ARMED"), 650, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SUCCESSFUL_COUNTERS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_PLAYERS"), 3593, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DEATHS_PLAYER"), 1002, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_STEALTH"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_INNOCENTS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_ENEMY_GANG_MEMBERS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_FRIENDLY_GANG_MEMBERS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_BY_OTHERS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HITS"), 600, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BIGGEST_VICTIM_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARCHENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRARMWREST"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRBASEJUMP"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRDARTS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRDM"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRGANGHIDE"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRGOLF"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRHORDE"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRMISSION"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRSHOOTRNG"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRTENNIS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TOTAL_TIME_CINEMA"), 2147483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NO_TIMES_CINEMA"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_PLAYER_MENTAL_STATE"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_AS_A_PASSENGER"), 2147483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_AS_A_DRIVER"), 2147483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_SPENT_FLYING"), 2147483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TIME_IN_CAR"), 2147483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_UNDERTA"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_COMPLET"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_UNDERTA"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_COMPLET"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_UNDERTABC"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_COMPLETBC"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S1_0"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S2_0"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S3_0"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS0"), 10000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_BUY_UNDERTA1"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_BUY_COMPLET1"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_SELL_UNDERTA1"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_SELL_COMPLET1"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SEL_UNDERTABC1"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SEL_COMPLETBC1"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S1_1"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S2_1"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S3_1"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS1"), 10000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_BUY_UNDERTA2"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_BUY_COMPLET2"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_SELL_UNDERTA2"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_SELL_COMPLET2"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SEL_UNDERTABC2"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SEL_COMPLETBC2"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S1_2"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S2_2"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S3_2"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS2"), 10000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_BUY_UNDERTA3"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_BUY_COMPLET3"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_SELL_UNDERTA3"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_SELL_COMPLET3"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SEL_UNDERTABC3"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SEL_COMPLETBC3"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S1_3"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S2_3"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S3_3"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS3"), 10000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_BUY_UNDERTA4"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_BUY_COMPLET4"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_SELL_UNDERTA4"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_SELL_COMPLET4"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SEL_UNDERTABC4"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SEL_COMPLETBC4"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S1_4"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S2_4"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BKR_PROD_STOP_COUT_S3_4"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS4"), 10000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_BUY_UNDERTA5"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_BUY_COMPLET5"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SEL_UNDERTABC5"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SEL_COMPLETBC5"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_SELL_UNDERTA5"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_BIKER_SELL_COMPLET5"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BUNKER_UNITS_MANUFAC"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS5"), 10000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_ABILITY_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_ABILITY_2_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_ABILITY_3_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_ABILITY_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_ABILITY_2_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_ABILITY_3_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_BUY_UNDETAK"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_BUY_COMPLET"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_SEL_UNDETAK"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_SEL_COMPLET"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_EARNINGS"), 29654123, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_EARN_BONUS"), 15987456, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_RIVAL_HANGAR_CRATES_STOLEN"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_IE_STEAL_STARTED"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_IE_EXPORT_STARTED"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_IE_EXPORT_COMPLETED"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_IE_MISSION_EARNINGS"), 59654897, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AT_FLOW_IMPEXP_NUM"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLUB_POPULARITY"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NIGHTCLUB_VIP_APPEAR"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NIGHTCLUB_JOBS_DONE"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NIGHTCLUB_EARNINGS"), 39856412, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HUB_SALES_COMPLETED"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HUB_EARNINGS"), 29865423, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DANCE_COMBO_DURATION_MINS"), 86400000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NIGHTCLUB_PLAYER_APPEAR"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_HUB_GOODS_SOLD"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_HUB_GOODS_MADE"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_10"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_11"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_12"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_8"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_CLOTHES_GV_BS_9"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADMIN_WEAPON_GV_BS_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AIR_LAUNCHES_OVER_40M"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_5STAR_WANTED_AVOIDANCE"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_CAR_BOMBS_ENEMY_KILLS"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_CARS_EXPORTED"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_CONTROL_CROWDS"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DAILYOBJCOMPLETED"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DO_HEIST_AS_MEMBER"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DO_HEIST_AS_THE_LEADER"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DROPOFF_CAP_PACKAGES"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FINISH_HEIST_SETUP_JOB"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FINISH_HEISTS"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_DM_3KILLSAMEGUY"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_DM_KILLSTREAK"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_DM_STOLENKILL"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_DM_TOTALKILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_DM_WINS"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_GOLF_HOLE_IN_1"), 300, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_GOLF_BIRDIES"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_GOLF_WON"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_GTA_RACES_WON"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_RACE_LAST_FIRST"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_RACES_FASTEST_LAP"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_SHOOTRANG_CT_WON"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_SHOOTRANG_RT_WON"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_SHOOTRANG_TG_WON"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_TDM_MVP"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_TDM_WINS"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_TENNIS_ACE"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FM_TENNIS_WON"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMBASEJMP"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMBBETWIN"), 50000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMCRATEDROPS"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMDRIVEWITHOUTCRASH"), 30, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMHORDWAVESSURVIVE"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMKILLBOUNTY"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMRALLYWONDRIVE"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMRALLYWONNAV"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMREVENGEKILLSDM"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMSHOOTDOWNCOPHELI"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMWINAIRRACE"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMWINRACETOPOINTS"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FMWINSEARACE"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_HOLD_UP_SHOPS"), 20, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_KILL_CARRIER_CAPTURE"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_KILL_PSYCHOPATHS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_KILL_TEAM_YOURSELF_LTS"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_LAPDANCES"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_LESTERDELIVERVEHICLES"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_MENTALSTATE_TO_NORMAL"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_NIGHTVISION_KILLS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_NO_HAIRCUTS"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ODISTRACTCOPSNOEATH"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ONLY_PLAYER_ALIVE_LTS"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PARACHUTE_JUMPS_20M"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PARACHUTE_JUMPS_50M"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PASSENGERTIME"), 4, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PICKUP_CAP_PACKAGES"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_RACES_WON"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SECURITY_CARS_ROBBED"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TAKEDOWNSMUGPLANE"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TIME_IN_HELICOPTER"), 4, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TRADE_IN_YOUR_PROPERTY"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_VEHICLES_JACKEDR"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WIN_AT_DARTS"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WIN_CAPTURE_DONT_DYING"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WIN_CAPTURES"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WIN_GOLD_MEDAL_HEISTS"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WIN_LAST_TEAM_STANDINGS"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_BOTTLE_IN_POSSESSION"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_2_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_3_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_4_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_5_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_6_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CARMOD_7_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_VEHICLE_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_VEHICLE_2_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_2_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_3_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_4_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_5_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_6_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_7_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_8_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_9_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_10_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_11_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_12_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_13_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_14_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_15_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_16_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_17_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_ADDON_18_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_UNLOCKED"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_UNLOCKED2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_WEAP_UNLOCKED3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_10_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_11_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_12_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_1_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_2_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_3_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_4_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_5_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_6_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_7_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_8_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_9_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_10_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_11_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_12_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_13_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_14_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_15_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_16_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_17_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_18_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_19_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_20_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_21_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_22_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_23_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_24_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_25_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_26_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_27_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_28_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_29_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_30_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_31_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_32_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_33_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_34_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_35_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_36_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_37_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_38_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_39_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_40_FM_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE10"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE11"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE12"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE8"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_KIT_FM_PURCHASE9"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WANTED_LEVEL_TIME5STAR"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WEAP_FM_PURCHASE"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WEAP_FM_PURCHASE2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_BERD"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_BERD_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_BERD_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_BERD_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_BERD_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_BERD_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_BERD_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_DECL"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_FEET"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_FEET_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_FEET_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_FEET_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_FEET_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_FEET_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_FEET_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_FEET_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_JBIB"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_JBIB_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_JBIB_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_JBIB_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_JBIB_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_JBIB_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_JBIB_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_JBIB_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_LEGS"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_LEGS_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_LEGS_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_LEGS_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_LEGS_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_LEGS_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_LEGS_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_LEGS_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_OUTFIT"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS_10"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS_8"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_PROPS_9"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_SPECIAL"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_SPECIAL2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_SPECIAL2_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_SPECIAL_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_SPECIAL_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_SPECIAL_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_SPECIAL_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_SPECIAL_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_SPECIAL_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_SPECIAL_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_TEETH"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_TEETH_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_TEETH_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_ACQUIRED_TORSO"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_BERD"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_BERD_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_BERD_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_BERD_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_BERD_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_BERD_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_BERD_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_BERD_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_DECL"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_FEET"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_FEET_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_FEET_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_FEET_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_FEET_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_FEET_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_FEET_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_FEET_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_HAIR"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_HAIR_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_HAIR_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_HAIR_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_HAIR_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_HAIR_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_HAIR_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_HAIR_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_JBIB"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_JBIB_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_JBIB_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_JBIB_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_JBIB_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_JBIB_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_JBIB_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_JBIB_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_LEGS"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_LEGS_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_LEGS_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_LEGS_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_LEGS_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_LEGS_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_LEGS_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_LEGS_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_OUTFIT"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS_10"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS_8"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_PROPS_9"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_SPECIAL"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_SPECIAL2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_SPECIAL2_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_SPECIAL_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_SPECIAL_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_SPECIAL_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_SPECIAL_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_SPECIAL_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_SPECIAL_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_SPECIAL_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_TEETH"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_TEETH_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_TEETH_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CLTHS_AVAILABLE_TORSO"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_0"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_10"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_11"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_12"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_13"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_14"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_15"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_16"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_17"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_18"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_19"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_20"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_21"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_22"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_23"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_24"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_25"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_26"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_27"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_28"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_29"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_30"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_31"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_32"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_33"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_34"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_35"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_36"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_37"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_38"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_39"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_40},"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_8"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DLC_APPAREL_ACQUIRED_9"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_GRENADE_ENEMY_KILLS"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MICROSMG_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SMG_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ASLTSMG_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ASLTRIFLE_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRBNRIFLE_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ADVRIFLE_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MG_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CMBTMG_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ASLTMG_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_RPG_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_PLAYERS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LONGEST_WHEELIE_DIST"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MOST_ARM_WRESTLING_WINS"), 25, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NO_CARS_REPAIR"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_VEHICLES_SPRAYED"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_NEAR_MISS_NOCRASH"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_USJS_FOUND"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_USJS_FOUND_MASK"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_USJS_COMPLETED"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_USJS_TOTAL_COMPLETED"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_USJS_COMPLETED_MASK"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MOST_FLIPS_IN_ONE_JUMP"), 5, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MOST_SPINS_IN_ONE_JUMP"), 5, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_SLIPSTREAMS_IN_RACE"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_TURBO_STARTS_IN_RACE"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PASS_DB_PLAYER_KILLS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PISTOL_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_PLAYER_HEADSHOTS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_RACES_WON"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SAWNOFF_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_DRIV"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_FLY"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_LUNG"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_MECH"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_SHO"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_STAM"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_STL"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SCRIPT_INCREASE_STRN"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_STKYBMB_ENEMY_KILLS"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_UNARMED_ENEMY_KILLS"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_USJS_COMPLETED"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_WEAP_FM_ADDON_PURCH"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_WEAP_FM_ADDON_PURCH2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_WEAP_FM_ADDON_PURCH3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_WEAP_FM_ADDON_PURCH4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_WEAP_FM_ADDON_PURCH5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CRDEADLINE"), 5, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_ABILITY_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_ABILITY_2_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_ABILITY_3_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_ABILITY_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_ABILITY_2_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_ABILITY_3_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BUY_COMPLETE"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BUY_UNDERTAKEN"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_SELL_COMPLETE"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_SELL_UNDERTAKEN"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_CONTRA_EARNINGS"), 20000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_COMPLET"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_UNDERTA"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_COMPLET"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_UNDERTA"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_COMPLET1"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_UNDERTA1"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_COMPLET1"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_UNDERTA1"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_COMPLET2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_UNDERTA2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_COMPLET2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_UNDERTA2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_COMPLET3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_UNDERTA3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_COMPLET3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_UNDERTA3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_COMPLET4"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_UNDERTA4"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_COMPLET4"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_UNDERTA4"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_COMPLET5"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_BUY_UNDERTA5"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_COMPLET5"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BIKER_SELL_UNDERTA5"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS0"), 20000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS1"), 20000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS2"), 20000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS3"), 20000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS4"), 20000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LIFETIME_BKR_SELL_EARNINGS5"), 20000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_IE_EXPORT_COMPLETED"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_IE_MISSION_EARNINGS"), 20000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_SEL_UNDETAK"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_SEL_COMPLET"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_EARNINGS"), 20000000, TRUE);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_0"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_8"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MPPLY_PILOT_SCHOOL_MEDAL_9"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_1"), 690, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_2"), 1860, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_3"), 2690, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_4"), 2660, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_5"), 2650, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_HIGHSCORE_6"), 450, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_TARGETS_HIT"), 269, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SR_WEAPON_BIT_SET"), -1, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_HEIST_ACH_TRACKER"), -1, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GANGOPS_ALLINORDER"), 100, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GANGOPS_LOYALTY"), 100, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GANGOPS_CRIMMASMD"), 100, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GANGOPS_LOYALTY2"), 100, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GANGOPS_LOYALTY3"), 100, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GANGOPS_CRIMMASMD2"), 100, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GANGOPS_CRIMMASMD3"), 100, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GANGOPS_SUPPORT"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_GANGOPS_HEIST_STATUS"), 9999, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NO_BOUGHT_YUM_SNACKS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DANCE_TO_SOLOMUN"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DANCE_TO_TALEOFUS"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DANCE_TO_DIXON"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_DANCE_TO_BLKMAD"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_CLUB_DRUNK"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NIGHTCLUB_PLAYER_APPEAR"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMUNIQUEPLYSINCLUB"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DANCETODIFFDJS"), 4, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DANCEPERFECTOWNCLUB"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NIGHTCLUB_HOTSPOT_TIME_MS"), 3600000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WATCH_YOUR_STEP"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TOWER_OFFENSE"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_READY_FOR_WAR"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_THROUGH_A_LENS"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SPINNER"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_YOUMEANBOOBYTRAPS"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_MASTER_BANDITO"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SITTING_DUCK"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_CROWDPARTICIPATION"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_KILL_OR_BE_KILLED"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_MASSIVE_SHUNT"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_YOURE_OUTTA_HERE"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_WEVE_GOT_ONE"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ARENA_WAGEWORKER"), 20000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TIME_SERVED"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TOP_SCORE"), 500000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_CAREER_WINNER"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARENAWARS_SKILL_LEVEL"), 20, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARENAWARS_AP_TIER"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARENAWARS_AP_LIFETIME"), 47551850, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_THEME_SCIFI"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_THEME_APOC"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_THEME_CONS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_PASS_THE_BOMB"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_DETONATION"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_ARCADE_RACE"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_CTF"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_TAG_TEAM"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_DESTR_DERBY"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_CARNAGE"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_MONSTER_JAM"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_W_GAMES_MASTERS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_L_PASS_THE_BOMB"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_L_DETONATION"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_L_ARCADE_RACE"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_L_CTF"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_L_TAG_TEAM"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_L_DESTR_DERBY"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_L_CARNAGE"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_L_MONSTER_JAM"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_L_GAMES_MASTERS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_OF_CHAMP_BOUGHT"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_SPECTATOR_KILLS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_LIFETIME_KILLS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_LIFETIME_DEATHS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARENAWARS_CARRER_WINS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARENAWARS_CARRER_WINT"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARENAWARS_MATCHES_PLYD"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARENAWARS_MATCHES_PLYDT"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_SPEC_BOX_TIME_MS"), 86400000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_SPECTATOR_DRONE"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_SPECTATOR_CAMS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_SMOKE"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_DRINK"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_MONSTER3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_MONSTER4"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_MONSTER5"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_CERBERUS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_CERBERUS2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_CERBERUS3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_BRUISER"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_BRUISER2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_BRUISER3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_SLAMVAN4"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_SLAMVAN5"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_SLAMVAN6"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_BRUTUS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_BRUTUS2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_BRUTUS3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_SCARAB"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_SCARAB2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_SCARAB3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_DOMINATOR4"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_DOMINATOR5"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_DOMINATOR6"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_IMPALER2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_IMPALER3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_IMPALER4"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_ISSI4"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_ISSI5"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_ISSI6"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_IMPERATOR"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_IMPERATOR2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_IMPERATOR3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_ZR380"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_ZR3802"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_ZR3803"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_DEATHBIKE"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_DEATHBIKE2"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_VEH_DEATHBIKE3"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NO_BOUGHT_HEALTH_SNACKS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NO_BOUGHT_EPIC_SNACKS"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_OF_ORANGE_BOUGHT"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MP_CHAR_ARMOUR_1_COUNT"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MP_CHAR_ARMOUR_2_COUNT"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MP_CHAR_ARMOUR_3_COUNT"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MP_CHAR_ARMOUR_4_COUNT"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MP_CHAR_ARMOUR_5_COUNT"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_OF_BOURGE_BOUGHT"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CIGARETTES_BOUGHT"), 1000, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_AWD_FM_CR_DM_MADE"), 600, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_AWD_FM_CR_PLAYED_BY_PEEP"), 1168, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_AWD_FM_CR_RACES_MADE"), 1000, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_AWD_FM_CR_MISSION_SCORE"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_ACT_PHN"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_ACT_PH2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_ACT_PH3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_ACT_PH4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_ACT_PH5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_VEH_TX1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_ACT_PH6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_ACT_PH7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_ACT_PH8"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_FM_ACT_PH9"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LOWRIDER_FLOW_COMPLETE"), 3, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LOW_FLOW_CURRENT_PROG"), 9, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LOW_FLOW_CURRENT_CALL"), 9, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_MORGUE"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_DELUXO"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_SERVERFARM"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_IAABASE_FIN"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_STEALOSPREY"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_FOUNDRY"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_RIOTVAN"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_SUBMARINECAR"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_SUBMARINE_FIN"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_PREDATOR"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_BMLAUNCHER"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_BCCUSTOM"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_STEALTHTANKS"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_SPYPLANE"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_FINALE"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_FINALE_P2"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGOP_FINALE_P3"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_SNIPERRFL_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HVYSNIPER_ENEMY_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_TIME_SPENT_DEATHMAT"), 2147483647, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_TIME_SPENT_RACES"), 2147483647, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_RACES_WON"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_RACES_LOST"), 250, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_CUSTOM_RACES_WON"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_DEATHMATCH_LOST"), 250, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_DEATHMATCH_WON"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_TDEATHMATCH_LOST"), 250, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TOTAL_TDEATHMATCH_WON"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_SHOOTINGRANGE_WINS"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_SHOOTINGRANGE_LOSSES"), 250, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TENNIS_MATCHES_WON"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_TENNIS_MATCHES_LOST"), 250, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GOLF_WINS"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_GOLF_LOSSES"), 250, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_DARTS_TOTAL_WINS"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_DARTS_TOTAL_MATCHES"), 750, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_SHOOTINGRANGE_TOTAL_MATCH"), 800, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_BJ_WINS"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_BJ_LOST"), 250, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_RACE_2_POINT_WINS"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_RACE_2_POINT_LOST"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_WEAPON_ARMOR"), 136985, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_VEH_MAINTENANCE"), 33698562, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_STYLE_ENT"), 5698456, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_PROPERTY_UTIL"), 19874563, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_JOB_ACTIVITY"), 1569856, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_BETTING"), 986542, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_CONTACT_SERVICE"), 15698745, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_DROPPED_STOLEN"), 12356, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_SHARED"), 986543, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_JOBSHARED"), 459856, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_HEALTHCARE"), 1569875, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_EXEC_PA"), 1698564, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_SPENT_BUY_CONTRABAND"), 12398654, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_EARN_JOBS"), 786000000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_EARN_SELLING_VEH"), 12356897, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_EARN_BETTING"), 1265798, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_EARN_GOOD_SPORT"), 156987, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_EARN_PICKED_UP"), 125987, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_EARN_SHARED"), 598756, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_EARN_JOBSHARED"), 365798, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MONEY_EARN_ROCKSTAR_AWARD"), 25654789, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_KILLS_PLAYERS"), 3593, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_DEATHS_PLAYER"), 1002, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_COP"), 4500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_SWAT"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WANTED_LEVEL_TIME"), 5000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_COP_VEHICLE"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_CARS"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_BIKES"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_BOATS"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_HELIS"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_PLANES"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_QUADBIKES"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_STOLEN_BICYCLES"), 200, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_STARS_ATTAINED"), 5000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_STARS_EVADED"), 4000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TOTAL_CHASE_TIME"), 1547483647, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_VEHEXPORTED"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TOTAL_NO_SHOPS_HELD_UP"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_ENEMY_GANG_MEMBERS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_KILLS_FRIENDLY_GANG_MEMBERS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGATTACK_CITY"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGATTACK_COUNTRY"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGATTACK_LOST"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CR_GANGATTACK_VAGOS"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_MISSIONS_CREATED"), 500, TRUE);
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_LTS_CREATED"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HORDKILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_GHKILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NO_NON_CONTRACT_RACE_WIN"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DB_SHOTTIME"), 596, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DB_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DB_PLAYER_KILLS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DB_SHOTS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DB_HITS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DB_HITS_PEDS_VEHICLES"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_DB_HEADSHOTS"), 500, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_RANKAP_UNLK_0"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_RANKAP_UNLK_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_RANKAP_UNLK_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_RANKAP_UNLK_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_CREWUNLOCK_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HEIST_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_PACKAGE_1_COLLECT"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_PACKAGE_2_COLLECT"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_PACKAGE_3_COLLECT"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_PACKAGE_5_COLLECT"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_PACKAGE_6_COLLECT"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_PACKAGE_7_COLLECT"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_PACKAGE_8_COLLECT"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_NO_FM_PACKAGES_COL"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_BS_TRINKET_SAVED"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_ARN_BS_TRINKET_TICKERS"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_BOARD_DIALOGUE0"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_BOARD_DIALOGUE1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_BOARD_DIALOGUE2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_H3_VEHICLESUSED"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_GANGOPS_FLOW_BITSET_MISS0"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_BUY_UNDETAK"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_LFETIME_HANGAR_BUY_COMPLET"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AT_FLOW_VEHICLE_BS"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_WVM_FLOW_VEHICLE_BS"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_0"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_8"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_9"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_10"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_11"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_TATTOO_FM_UNLOCKS_12"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_2_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_3_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_4_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_5_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_6_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_7_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_8_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_9_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_10_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_CLOTHES_11_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_CREWUNLOCK_1_FM_EQUIP"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_CREWUNLOCK_2_FM_EQUIP"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_CREWUNLOCK_3_FM_EQUIP"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_CREWUNLOCK_4_FM_EQUIP"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK1"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK3"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK4"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK5"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK6"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK7"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK8"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK9"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK10"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK11"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_HAIR_UNLCK12"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_HEALTH_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_HEALTH_2_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_FM_HAIRCUT_1_UNLCK"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WEAP_UNLOCKED"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CHAR_WEAP_UNLOCKED2"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HEIST_COMPLETION"), 26, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HEIST_TOTAL_TIME"), 86400000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_HEISTS_ORGANISED"), 50, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CH_ARC_CAB_CLAW_TROPHY"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CH_ARC_CAB_LOVE_TROPHY"), -1, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_CAR_CLUB_MEM"), 1000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_SPRINTRACER"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_STREETRACER"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_PURSUITRACER"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_TEST_CAR"), 1800000, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_CAR_EXPORT"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_GROUNDWORK"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_ROBBERY_CONTRACT"), 100, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_FACES_OF_DEATH"), 250, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_AWD_AUTO_SHOP"), 100, TRUE);
			});

			sub->AddOption<RegularOption>("Unlock Casino Shop Stuff", nullptr, []
			{
				for (int i = 26782; i <= 27356; i++)
				{
					*script_global(262145).at(i).as<int*>() = TRUE;
				}
				message::notification(BIGBASE_NAME" Gold Edition", "~g~Shop Unlocked!", "~bold~~g~" BIGBASE_NAME " Recovery");
			});


		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Player Stats", SubmenuStats, [](RegularSubmenu* sub)
		{
			static int kill{};
			STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_KILLS_PLAYERS"), &kill, -1);
			sub->AddOption<NumberOption<int32_t>>("Player Kills", nullptr, &kill, 0, 1000, 1, 3, true, "", "", []
			{
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_KILLS_PLAYERS"), kill, TRUE);
			});

			static int death{};
			STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_DEATHS_PLAYER"), &death, -1);
			sub->AddOption<NumberOption<int32_t>>("Player Death", nullptr, &death, 0, 1000, 1, 3, true, "", "", []
			{
				STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_DEATHS_PLAYER"), death, TRUE);
			});

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Teleport Option", SubmenuTeleport, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Add Teleport", "Add some to use them!", []
			{
				MISC::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", "Teleport Name", "", "", "", 25);

				g_CallbackScript->AddCallback<KeyBoardCallBack>("Teleport Name", 25, [] {
					std::string text = MISC::GET_ONSCREEN_KEYBOARD_RESULT();
					auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
					g_teleport_persist->AddTeleport(text, pos);
				});
			});
			sub->AddOption<SubOption>("Saved Teleport", nullptr, SubmenuSaveTeleport);
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
			sub->AddOption<BoolOption<bool>>("Force Invite Apartment", nullptr, &g_protection->block_apartment, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Force Teleport Cayo", nullptr, &g_protection->block_cayo, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("CEO Kick", nullptr, &g_protection->block_ceo_kick, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("CEO Ban", nullptr, &g_protection->block_ceo_ban, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Vehicle Kick", nullptr, &g_protection->block_vehicle_kick, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Rotate Cam", nullptr, &g_protection->block_rotate_cam, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Sound Spam", nullptr, &g_protection->block_spam, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Transaction Error", nullptr, &g_protection->block_transaction_error, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Force Send Mission", nullptr, &g_protection->block_send_mission, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Kick", nullptr, &g_protection->block_kick, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Block Freeze", nullptr, &g_protection->clear_ped_task, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Report Block", nullptr, &g_protection->block_report, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Remove Weapon", nullptr, &g_protection->block_remove_weapon, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Kick Vote", nullptr, &g_protection->block_kick_vote, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Request Control", nullptr, &g_protection->block_request_control, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Explosion Event", nullptr, &g_protection->block_explosion_event, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("PTFX Event", nullptr, &g_protection->block_ptfx_event, BoolDisplay::YesNo);
			sub->AddOption<BoolOption<bool>>("Invalid Model", nullptr, &g_protection->crash, BoolDisplay::YesNo);

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Online Option", SubmenuOnline, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Session Option", nullptr, SubmenuSession);
			sub->AddOption<SubOption>("Heist", nullptr, SubmenuHeist);
			sub->AddOption<SubOption>("Business", nullptr, SubmenuBusiness);
			sub->AddOption<SubOption>("Spoofer", nullptr, SubmenuSpoofer);

			sub->AddOption<RegularOption>("Max Snack & Armour", nullptr, []
			{
				const auto mpx = std::to_string(*script_global(1312763).as<int*>());
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NO_BOUGHT_YUM_SNACKS"), 30, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NO_BOUGHT_HEALTH_SNACKS"), 15, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NO_BOUGHT_EPIC_SNACKS"), 5, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_OF_ORANGE_BOUGHT"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_NUMBER_OF_BOURGE_BOUGHT"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_CIGARETTES_BOUGHT"), 20, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MP_CHAR_ARMOUR_1_COUNT"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MP_CHAR_ARMOUR_2_COUNT"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MP_CHAR_ARMOUR_3_COUNT"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MP_CHAR_ARMOUR_4_COUNT"), 10, TRUE);
				STATS::STAT_SET_INT(joaat("MP" + mpx + "_MP_CHAR_ARMOUR_5_COUNT"), 10, TRUE);
			});

			sub->AddOption<BoolOption<bool>>("Off The Radar", nullptr, &g_features->off_the_radar, BoolDisplay::YesNo);

			sub->AddOption<BoolOption<bool>>("Reveal Player", nullptr, &g_features->reveal_player, BoolDisplay::YesNo);

			sub->AddOption<BoolOption<bool>>("Blind Cops", nullptr, &g_features->blind_cops, BoolDisplay::YesNo);

			sub->AddOption<NumberOption<std::int32_t>>("Mission Lives", nullptr, &g_features->player_lives, 0, 10000, 1, 3, true, "", "", [] 
			{
				game_helper::mission_lives(g_features->player_lives);
			});

			sub->AddOption<RegularOption>("Call Terrorbyte", nullptr, []
			{
				*script_global(g_global.terorbyte).as<bool*>() = true;
			});

			sub->AddOption<RegularOption>("Call Kosatka", nullptr, []
			{
				*script_global(g_global.kosatka).as<bool*>() = true;
			});

			sub->AddOption<RegularOption>("Call Avenger", nullptr, []
			{
				*script_global(g_global.avanger).as<bool*>() = true;
			});

			sub->AddOption<RegularOption>("Call Mobile Operation Center", nullptr, []
			{
				*script_global(g_global.moc).as<bool*>() = true;
			});

			sub->AddOption<RegularOption>("Dinghy", nullptr, []
			{
				*script_global(g_global.dinghy).as<bool*>() = true;
			});

			sub->AddOption<RegularOption>("Drone", nullptr, []
			{
				int flags = *script_global(g_global.drone).as<int*>();
				flags = Memory::set_bit(flags, 2);
				flags = Memory::set_bit(flags, 22);
				flags = Memory::set_bit(flags, 23);
				flags = Memory::set_bit(flags, 24);
				*script_global(g_global.drone).as<int*>() = flags;
				
				g_CallbackScript->AddCallback<DelayCallback>(100ms, []
				{
					int flags = *script_global(g_global.drone).as<int*>();
					flags = Memory::clear_bit(flags, 2);
					flags = Memory::clear_bit(flags, 22);
					flags = Memory::clear_bit(flags, 23);
					*script_global(g_global.drone).as<int*>() = flags;
				});
			});

			sub->AddOption<RegularOption>("Minitank", nullptr, []
			{
				*script_global(g_global.mini_tank).as<int*>() = 1;
				g_CallbackScript->AddCallback<DelayCallback>(1000ms, []
				{
					*script_global(g_global.mini_tank).as<int*>() = 0;
				});
			});

			sub->AddOption<RegularOption>("RC Bandito", nullptr, []
			{
				*script_global(g_global.rc_bandito).as<int*>() = 1;
				g_CallbackScript->AddCallback<DelayCallback>(1000ms, []
				{
					*script_global(g_global.rc_bandito).as<int*>() = 0;
				});
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Spoofer Option", SubmenuSpoofer, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Name Spoofer", "Change Name Here!", []
			{
				MISC::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", "Your Name", "", "", "", 25);

				g_CallbackScript->AddCallback<KeyBoardCallBack>("Your Name", 25, [] {
					strcpy(g_features->spoofer_name, MISC::GET_ONSCREEN_KEYBOARD_RESULT());
					strcpy(get_local_playerinfo()->m_name, MISC::GET_ONSCREEN_KEYBOARD_RESULT());
					strcpy(g_GameVariables->m_player_name_display, MISC::GET_ONSCREEN_KEYBOARD_RESULT());
					strcpy(g_GameVariables->m_player_name_esp, MISC::GET_ONSCREEN_KEYBOARD_RESULT());
				});
			});

			sub->AddOption<RegularOption>("RID Spoofer", "RID Here!", []
			{
				MISC::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", "Your RID", "", "", "", 25);

				g_CallbackScript->AddCallback<KeyBoardCallBack>("Your RID", 25, [] {
					strcpy(g_features->spoofer_rid, MISC::GET_ONSCREEN_KEYBOARD_RESULT());
				});
			});
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
			sub->AddOption<BoolOption<bool>>("Godmode", nullptr, &g_features->vehicle_godmode, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Seatbelt", nullptr, &g_features->seatbelt, BoolDisplay::OnOff);
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
			sub->AddOption<SubOption>("Vehicle Handling", "Must Be In Vehicle", SubmenuLSCustoms);
			sub->AddOption<BoolOption<bool>>("Infinite Boost", nullptr, &g_features->infinite_boost, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Boost Flag", nullptr, &g_features->boost_flag, BoolDisplay::OnOff, false, []
				{
					if (g_features->boost_flag)
					{
						vehicle::set_flag(4, 30);
					}
					else
					{
						vehicle::clear_flag(4, 30);
					}
				});
			sub->AddOption<BoolOption<bool>>("Jump Flag", nullptr, &g_features->jump_flag, BoolDisplay::OnOff, false, []
				{
					if (g_features->jump_flag)
					{
						vehicle::set_flag(4, 29);
					}
					else
					{
						vehicle::clear_flag(4, 29);
					}
				});
			sub->AddOption<BoolOption<bool>>("Parachute Flag", nullptr, &g_features->parachute_flag, BoolDisplay::OnOff, false, []
			{
				if (g_features->parachute_flag)
				{
					vehicle::set_flag(5, 0);
				}
				else
				{
					vehicle::clear_flag(5, 0);
				}
			});
			sub->AddOption<BoolOption<bool>>("Oppressor Flag", nullptr, &g_features->oppressor_flag, BoolDisplay::OnOff, false, []
			{
				if (g_features->oppressor_flag)
				{
					vehicle::set_flag(4, 1);
				}
				else
				{
					vehicle::clear_flag(4, 1);
				}
			});
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
			sub->AddOption<BoolOption<bool>>("Set As Public", nullptr, &g_features->vehicle_godmode, BoolDisplay::OnOff);
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

			static int32_t popularity{ business::get_nightclub_popularity() };

			sub->AddOption<NumberOption<int32_t>>("Nightclub Popularity", nullptr, &popularity, 0, 1000, 1, 3, true, "", "", []
			{
				business::set_nightclub_popularity(popularity);
			});

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Special Cargo Business", SubmenuSpecialCargo, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<int32_t>>("Special Cargo Money", "Money Option", &g_features->cargo_money, 0, 6000000, 100000, 3, false, "", "", []
			{
				business::special_cargo_selling_mission(g_features->cargo_money);
			});

			sub->AddOption<NumberOption<int32_t>>("Special Cargo Crates", "Money Option", &g_features->cargo_crates, 0, 111, 1, 3, false, "", "", []
			{
				business::special_cargo_crates(g_features->cargo_crates);
			});

			sub->AddOption<BoolOption<bool>>("Remove Sell Cooldown", nullptr, &g_features->sell_cargo_cooldown, BoolDisplay::OnOff, false, []
			{
				if (g_features->sell_cargo_cooldown)
					*script_global(g_global.special_cargo_selling_cooldown).as<int*>() = 0;
				else
					*script_global(g_global.special_cargo_selling_cooldown).as<int*>() = 1800000;
			});

			sub->AddOption<BoolOption<bool>>("Remove Buy Cooldown", nullptr, &g_features->buy_cargo_cooldown, BoolDisplay::OnOff, false, []
			{
				if (g_features->buy_cargo_cooldown)
					*script_global(g_global.special_cargo_buying_cooldown).as<int*>() = 0;
				else
					*script_global(g_global.special_cargo_buying_cooldown).as<int*>() = 300000;
			});

			sub->AddOption<BoolOption<bool>>("Extend Selling Timer", nullptr, &g_features->cargo_selling_time, BoolDisplay::OnOff, false, []
			{
				if (g_features->cargo_selling_time)
					*script_global(g_global.special_cargo_selling_time).as<int*>() = 18000000;
				else
					*script_global(g_global.special_cargo_selling_time).as<int*>() = 1800000;
			});

			sub->AddOption<BoolOption<bool>>("Enable Rare Items", nullptr, script_global(g_global.rare_item).as<bool*>(), BoolDisplay::OnOff);

			sub->AddOption<ChooseOption<const char*, std::size_t>>("Session", nullptr, &Lists::special_cargo_rare_items, &Lists::special_cargo_selected, true, []
			{
				switch (Lists::special_cargo_selected)
				{
				case 0:
					*script_global(g_global.special_crates).as<int*>() = 2;
					break;
				case 1:
					*script_global(g_global.special_crates).as<int*>() = 4;
					break;
				case 2:
					*script_global(g_global.special_crates).as<int*>() = 6;
					break;
				case 3:
					*script_global(g_global.special_crates).as<int*>() = 7;
					break;
				case 4:
					*script_global(g_global.special_crates).as<int*>() = 8;
					break;
				case 5:
					*script_global(g_global.special_crates).as<int*>() = 9;
					break;
				}
			});

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Bunker Business", SubmenuBunker, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<int32_t>>("Bunker Money", "Money Option", &g_features->bunker_business_money, 0, 5000000, 100000, 3, false, "", "", []
			{
				business::bunker_selling_mission(g_features->bunker_business_money);
			});

			sub->AddOption<RegularOption>("Trigger Bunker Production", nullptr, []
			{
				business::trigger_bunker_production(PLAYER::PLAYER_ID());
			});

			sub->AddOption<RegularOption>("Trigger Bunker Research", nullptr, []
			{
				business::trigger_bunker_research(PLAYER::PLAYER_ID());
			});

			sub->AddOption<BoolOption<bool>>("Unlock Bunker Research", nullptr, &g_features->research, BoolDisplay::OnOff, false, []
			{
					stats::unlock_bunker_research(g_features->research);
			});

			sub->AddOption<BoolOption<bool>>("Remove Supply Delay", nullptr, &g_features->bunker_supply_bool, BoolDisplay::OnOff, false, []
			{
				if (g_features->bunker_supply_bool)
					*script_global(g_global.bunker_supplies_delay).as<int*>() = 0;
				else
					*script_global(g_global.bunker_supplies_delay).as<int*>() = 600;
			});

			sub->AddOption<BoolOption<bool>>("Extend Selling TImer", nullptr, &g_features->bunker_timer_bool, BoolDisplay::OnOff, false, []
			{
				if (g_features->bunker_timer_bool)
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
			sub->AddOption<NumberOption<int32_t>>("MC Business Money", "Money Option", &g_features->mc_business_money, 0, 2500000, 100000, 3, false, "", "", []
			{
				business::biker_selling_mission(g_features->mc_business_money);
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

			sub->AddOption<BoolOption<bool>>("Remove Supply Delay", nullptr, &g_features->mc_supply_bool, BoolDisplay::OnOff, false, []
			{
				if (g_features->mc_supply_bool)
					*script_global(g_global.mc_supplies_delay).as<int*>() = 0;
				else
					*script_global(g_global.mc_supplies_delay).as<int*>() = 600;
			});

			sub->AddOption<BoolOption<bool>>("Extend Selling Timer", nullptr, &g_features->mc_timer_bool, BoolDisplay::OnOff, false, []
			{
				if (g_features->mc_timer_bool)
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

		g_UiManager->AddSubmenu<RegularSubmenu>("Player Option", SubmenuTest, [](RegularSubmenu* sub)
		{
			sub->AddOption<BoolOption<bool>>("Godmode", nullptr, &g_features->godmode, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("No Ragdoll", nullptr, &g_features->no_ragdoll, BoolDisplay::OnOff, false, []
			{
				if (g_features->no_ragdoll && get_local_ped()->m_ragdoll > 0x0F)
				{
					get_local_ped()->m_ragdoll = 0x01;
				}
				else if (!g_features->no_ragdoll && get_local_ped()->m_ragdoll <= 0x0F)
				{
					get_local_ped()->m_ragdoll = 0x20;
				}
			});

			sub->AddOption<BoolOption<bool>>("No Idle Kick", nullptr, &g_features->no_idle_kick, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Auto Heal", nullptr, &g_features->auto_heal, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Never Wanted", nullptr, &g_features->never_wanted, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("No Ragdoll", nullptr, &g_features->no_ragdoll, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Pass Through Wall", nullptr, &g_features->no_collision, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("No Clip", nullptr, &g_features->no_clip, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Super Jump", nullptr, &g_features->super_jump, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Explosive Fist", nullptr, &g_features->explosive_fist, BoolDisplay::OnOff);
			
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
				weapon::give_weapon(PLAYER::PLAYER_PED_ID());
			});
			sub->AddOption<RegularOption>("Give Max Ammo", nullptr, []
			{
				for (auto Weapon : game_variable::AllWeaponHashes)
				{
					int max_ammo;
					if (WEAPON::IS_WEAPON_VALID(joaat(Weapon)))
					{
						int max_clip = WEAPON::GET_MAX_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), joaat(Weapon), FALSE);
						WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), joaat(Weapon), &max_ammo);
						WEAPON::SET_AMMO_IN_CLIP(PLAYER::PLAYER_PED_ID(), joaat(Weapon), max_clip);
						WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), joaat(Weapon), max_ammo, FALSE);
					}
				}
			});

			sub->AddOption<BoolOption<bool>>("Infinite Ammo", nullptr, &g_features->infinite_ammo, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Infinite Clip", nullptr, &g_features->infinite_clip, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Explosive Ammo", nullptr, &g_features->explosive_ammo, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Fire Ammo", nullptr, &g_features->fire_ammo, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Rapid Fire", nullptr, &g_features->rapid_fire, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Delete Gun", nullptr, &g_features->delete_gun, BoolDisplay::OnOff);
			sub->AddOption<BoolOption<bool>>("Ghost Gun", nullptr, &g_features->ghost_gun, BoolDisplay::OnOff);

		});
		
		g_UiManager->AddSubmenu<RegularSubmenu>("Heist Option", SubmenuHeist, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Casino Heist", nullptr, SubmenuCasino);

			sub->AddOption<SubOption>("Cayo Perico Heist", nullptr, SubmenuCayo);

			sub->AddOption<SubOption>("Doomsday Heist", nullptr, SubmenuDoomsday);

			sub->AddOption<SubOption>("Apartment Heist", nullptr, SubmenuApartment);

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

		g_UiManager->AddSubmenu<RegularSubmenu>("Doomsday Heist", SubmenuDoomsday, [](RegularSubmenu* sub)
		{
			sub->AddOption<NumberOption<std::int32_t>>("Doomsday Cut Player 1", nullptr, script_global(g_global.doomsday_cut_1).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Doomsday Cut Player 2", nullptr, script_global(g_global.doomsday_cut_2).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Doomsday Cut Player 3", nullptr, script_global(g_global.doomsday_cut_3).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Doomsday Cut Player 4", nullptr, script_global(g_global.doomsday_cut_4).as<int*>(), 0, 100, 5);


		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Apartment Heist", SubmenuApartment, [](RegularSubmenu* sub)
		{
			static int32_t pasific_standard{ 0 };
			sub->AddOption<NumberOption<int32_t>>("Pasific Standard Take", "Pasific Standard Take", &pasific_standard, 0, 10000000, 10000, 3, true, "", "", []
			{
				casino_heist::all_heist_take(pasific_standard);
			});
			sub->AddOption<NumberOption<std::int32_t>>("Apartment Cut Player 1", nullptr, script_global(g_global.apartmen_cut_1).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Apartment Cut Player 2", nullptr, script_global(g_global.apartmen_cut_2).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Apartment Cut Player 3", nullptr, script_global(g_global.apartmen_cut_3).as<int*>(), 0, 100, 5);
			sub->AddOption<NumberOption<std::int32_t>>("Apartment Cut Player 4", nullptr, script_global(g_global.apartmen_cut_4).as<int*>(), 0, 100, 5);



		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Casino Heist", SubmenuCasino, [](RegularSubmenu* sub)
		{
			static int32_t casino_take{ 0 };
			sub->AddOption<NumberOption<int32_t>>("Heist Take", "Casino Heist Take", &casino_take, 0, 10000000, 10000, 3, true, "", "", []
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
				case 1:
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
			sub->AddOption<NumberOption<int32_t>>("Heist Take", "Cayo Perico Heist Take", &cayo_perico, 0, 10000000, 50000, 3, true, "", "", []
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
			case HeaderType::Ytd:
				sub->AddOption<SubOption>("Ytd", nullptr, SubmenuSettingsHeaderStaticBackground);
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
			sub->AddOption<SubOption>("Troll Option", nullptr, SubmenuTrollOption);

			sub->AddOption<RegularOption>("Crash Player", "Crashing Player Game", []
			{
				network::crash_player(g_selected.ped);
			});
			
			sub->AddOption<BoolOption<bool>>("Spectate", nullptr, &g_features->spectating, BoolDisplay::OnOff, false, [=]
			{
				NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(g_features->spectating, g_selected.ped);
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Troll Option", SubmenuTrollOption, [](RegularSubmenu* sub)
		{
			sub->AddOption<SubOption>("Script Event", nullptr, SubmenuScriptEvent);

			sub->AddOption<SubOption>("Network Event", nullptr, SubmenuNetworkEvent);

			sub->AddOption<SubOption>("Other", nullptr, SubmenuScriptEvent);

		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Network Event", SubmenuNetworkEvent, [](RegularSubmenu* sub)
		{
			sub->AddOption<RegularOption>("Give Weapon", "Give Weapon To Selected Player", [=]
			{
				weapon::give_weapon(g_selected.ped);
			});

			sub->AddOption<RegularOption>("Blame", "Send Explosion To All Player", [=]
			{
				network::blame_player(g_selected.ped);
			});
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Script Event", SubmenuScriptEvent, [](RegularSubmenu* sub)
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
		});

		g_UiManager->AddSubmenu<RegularSubmenu>("Teleport Locations", SubmenuSaveTeleport, [](RegularSubmenu* sub)
			{
				namespace fs = std::filesystem;
				fs::directory_iterator dirIt{ g_teleport_persist->GetTeleportDirectory() };
				for (auto&& dirEntry : dirIt)
				{
					if (dirEntry.is_regular_file())
					{
						auto path = dirEntry.path();
						if (path.has_filename() && !fs::is_empty(path))
						{
							sub->AddOption<RegularOption>(path.stem().u8string().c_str(), nullptr, [=]
								{
									fs::path m_FilePath;
									char prefix[64] = {};
									std::snprintf(prefix, sizeof(prefix) - 1, "%s%s", path.stem().u8string(), ".big");

									m_FilePath.append(std::getenv("appdata"));
									m_FilePath.append(BIGBASE_NAME);
									m_FilePath.append("Teleports\\");

									m_FilePath.append(prefix);

									std::ifstream ifs(m_FilePath);

									std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
									std::stringstream ss(content);
									std::vector<float> result;

									while (ss.good())
									{
										std::string substr;
										std::getline(ss, substr, ',');
										result.push_back(::atof(substr.c_str()));
									}
									if (PED::IS_PED_IN_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), true))
									{
										Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(veh, result[0], result[1], result[2], false, false, false);
									}
									else {
										ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(), result[0], result[1], result[2], false, false, false);
									}
								});
						}
						else
						{
							sub->AddOption<RegularOption>("No Teleports Found", "Add some to use them!", []
							{
								MISC::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", "Teleport Name", "", "", "", 25);

								g_CallbackScript->AddCallback<KeyBoardCallBack>("Teleport Name", 25, [] {
									std::string text = MISC::GET_ONSCREEN_KEYBOARD_RESULT();
									auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
									g_teleport_persist->AddTeleport(text, pos);
								});
							});
						}
					}
				}

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
