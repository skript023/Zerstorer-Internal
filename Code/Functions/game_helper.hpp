#pragma once
#include "../Common.hpp"
#include "../Natives.hpp"
#include "memory_address.hpp"
#include "systems_helper.hpp"
#include "../ScriptLocal.hpp"

namespace big
{
	class message
	{
	public:
		static void notification(const char* sender, const char* Message, const char* MessageTag)
        {
			HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(Message);
			HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", FALSE, 0, sender, MessageTag);
			HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, true);
        }
	};

	class game_protection
	{
	public:
		static inline bool redirect_report = true;
		static inline bool block_apartment = true;
		static inline bool block_cayo = true;
		static inline bool block_ceo_kick = true;
		static inline bool block_ceo_ban = true;
		static inline bool block_vehicle_kick = true;
		static inline bool block_rotate_cam = true;
		static inline bool block_transaction_error = true;
		static inline bool block_send_mission = true;
		static inline bool block_kick = true;
		static inline bool block_spam = true;
		static inline bool clear_ped_task = true;
		static inline bool block_report = true;
		static inline bool block_remove_weapon = true;
		static inline bool block_kick_vote = true;
		static inline bool block_request_control = true;
		static inline bool block_explosion_event = true;
		static inline bool block_ptfx_event = true;
		static inline bool crash = true;
	};

    class game_helper
    {
	public:
		static inline int64_t tick{};
		static inline int64_t tick_2{};

		static inline int tuneable{0};
		static inline int temp{0};

		static inline bool auto_getin{};
		static inline bool full_upgrade{true};
		static inline bool first_load{ true };

		static inline Vehicle player_vehicle{};
		static inline std::vector<std::string> slot_display_names{};
		static inline std::map<int, int> owned_mods{};
		static inline std::map<int, std::vector<std::string>> mod_display_names{};
		static inline int selected_slot = -1;
		static inline int selected_xenon = 0;
		static inline bool can_tires_burst{}, tiresmoke{}, turbo{}, xenon{};
		static inline int primary_color{}, secondary_color{}, pearlescent{}, wheel_color{}, interior_color{}, dashboard_color{};

        static inline const std::map<int, const char*> horn_map = {
        {-1, "CMOD_HRN_0"}, {0, "CMOD_HRN_TRK"}, {1, "CMOD_HRN_COP"}, {2, "CMOD_HRN_CLO"}, {3, "CMOD_HRN_MUS1"}, {4, "CMOD_HRN_MUS2"}, {5, "CMOD_HRN_MUS3"}, {6, "CMOD_HRN_MUS4"}, {7, "CMOD_HRN_MUS5"}, {8, "CMOD_HRN_SAD"}, {9, "HORN_CLAS1"}, {10, "HORN_CLAS2"}, {11, "HORN_CLAS3"}, {12, "HORN_CLAS4"}, {13, "HORN_CLAS5"}, {14, "HORN_CLAS6"}, {15, "HORN_CLAS7"}, {16, "HORN_CNOTE_C0"}, {17, "HORN_CNOTE_D0"}, {18, "HORN_CNOTE_E0"}, {19, "HORN_CNOTE_F0"}, {20, "HORN_CNOTE_G0"}, {21, "HORN_CNOTE_A0"}, {22, "HORN_CNOTE_B0"}, {23, "HORN_CNOTE_C1"}, {24, "HORN_HIPS1"}, {25, "HORN_HIPS2"}, {26, "HORN_HIPS3"}, {27, "HORN_HIPS4"}, {28, "HORN_INDI_1"}, {29, "HORN_INDI_2"}, {30, "HORN_INDI_3"}, {31, "HORN_INDI_4"}, {32, "HORN_LUXE2"}, {33, "HORN_LUXE1"}, {34, "HORN_LUXE3"}, /*{35, "HORN_LUXE2"},
            {36, "HORN_LUXE1"}, {37, "HORN_LUXE3"},*/
        {38, "HORN_HWEEN1"},
        /*{39, "HORN_HWEEN1"},*/ {40, "HORN_HWEEN2"},
        /*{41, "HORN_HWEEN2"},*/ {42, "HORN_LOWRDER1"},
        /*{43, "HORN_LOWRDER1"},*/ {44, "HORN_LOWRDER2"}, /*{45, "HORN_LOWRDER2"},*/
        {46, "HORN_XM15_1"},
        {47, "HORN_XM15_2"},
        {48, "HORN_XM15_3"} };
        static inline const char* xenonColourCaptions[]{
            "Stock",
            "White",
            "Blue",
            "Electric Blue",
            "Mint Green",
            "Lime Green",
            "Yellow",
            "Golden Shower",
            "Orange",
            "Red",
            "Pony Pink",
            "Hot Pink",
            "Purple",
            "Blacklight",
        }; //14 items
    public:
        static void game_frame()
		{
			if (tick == 200)
			{
				if (*script_global(g_global.session_change).as<int*>() == 1)
					*script_global(g_global.session_change).as<int*>() = 0;
				tick = 0;
			}

			if (tick_2 == 1000)
			{
				if (!systems::is_float_equal(*script_global(g_global.mc_sell_mult_far).as<float*>(), 1.5f) && !systems::is_float_equal(*script_global(g_global.mc_sell_mult_near).as<float*>(), 1.0f))
				{
					*script_global(g_global.mc_sell_mult_far).as<float*>() = 1.5f;
					*script_global(g_global.mc_sell_mult_near).as<float*>() = 1.0f;
				}

				if (!systems::is_float_equal(*script_global(g_global.bunker_selling_mult_far).as<float*>(), 1.5f) && !systems::is_float_equal(*script_global(g_global.bunker_selling_mult_near).as<float*>(), 1.0f))
				{
					*script_global(g_global.bunker_selling_mult_far).as<float*>() = 1.5f;
					*script_global(g_global.bunker_selling_mult_near).as<float*>() = 1.0f;
				}

				if (!systems::is_script_active(RAGE_JOAAT("gb_contraband_sell")))
				{
					if (tuneable != 0)
						*script_global(tuneable).as<int*>() = temp;
				}

				tick_2 = 0;
			}

			if (first_load)
			{
				HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~bold~~y~Zerstorer ~g~Menu Connected With The Game~w~");
				HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", FALSE, 0, "~bold~~y~Zerstorer", "~y~~a~Premium Mod Menu");
				HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, true);
			}

			tick++; tick_2++; first_load = false;
		}
		static void when_game_closed()
		{
			if (!g_Running)
				message::notification("Zerstorer Gold Edition", "~bold~~g~Menu Unloaded", "~bold~~g~Zerstorer Unloader");
		}
		static const char* get_mod_slot_name(int mod_slot, Vehicle vehicle);
		static const char* get_mod_name(int mod, int mod_slot, int mod_count, Vehicle vehicle);
		static void get_vehicle_mod();
		static int func_799(int iParam0)
		{
			if (iParam0 >= *script_global(262145).at(15507).as<int*>())
			{
				return (262145 + 15528);
			}
			else if (iParam0 >= *script_global(262145).at(15506).as<int*>())
			{
				return (262145 + 15527);
			}
			else if (iParam0 >= *script_global(262145).at(15505).as<int*>())
			{
				return (262145 + 15526);
			}
			else if (iParam0 >= *script_global(262145).at(15504).as<int*>())
			{
				return (262145 + 15525);
			}
			else if (iParam0 >= *script_global(262145).at(15503).as<int*>())
			{
				return (262145 + 15524);
			}
			else if (iParam0 >= *script_global(262145).at(15502).as<int*>())
			{
				return (262145 + 15523);
			}
			else if (iParam0 >= *script_global(262145).at(15501).as<int*>())
			{
				return (262145 + 15522);
			}
			else if (iParam0 >= *script_global(262145).at(15500).as<int*>())
			{
				return (262145 + 15521);
			}
			else if (iParam0 >= *script_global(262145).at(15499).as<int*>())
			{
				return (262145 + 15520);
			}
			else if (iParam0 >= *script_global(262145).at(15498).as<int*>())
			{
				return (262145 + 15519);
			}
			else if (iParam0 >= *script_global(262145).at(15497).as<int*>())
			{
				return (262145 + 15518);
			}
			else if (iParam0 >= *script_global(262145).at(15496).as<int*>())
			{
				return (262145 + 15517);
			}
			else if (iParam0 >= *script_global(262145).at(15495).as<int*>())
			{
				return (262145 + 15516);
			}
			else if (iParam0 >= *script_global(262145).at(15494).as<int*>())
			{
				return (262145 + 15515);
			}
			else if (iParam0 >= *script_global(262145).at(15493).as<int*>())
			{
				return (262145 + 15514);
			}
			else if (iParam0 >= *script_global(262145).at(15492).as<int*>())
			{
				return (262145 + 15513);
			}
			else if (iParam0 >= *script_global(262145).at(15491).as<int*>())
			{
				return (262145 + 15512);
			}
			else if (iParam0 >= *script_global(262145).at(15490).as<int*>())
			{
				return (262145 + 15511);
			}
			else if (iParam0 >= *script_global(262145).at(15489).as<int*>())
			{
				return (262145 + 15510);
			}
			else if (iParam0 >= *script_global(262145).at(15488).as<int*>())
			{
				return (262145 + 15509);
			}
			return (262145 + 15508);
		}
    };

	inline static game_helper g_game_helper;
	inline static game_protection g_protection;
}
