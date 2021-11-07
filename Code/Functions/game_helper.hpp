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

    class game_helper
    {
	public:
		static inline int64_t tick{};
		static inline bool auto_getin{};
		static inline bool full_upgrade{};
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
			if (tick == 200 && *script_global(g_global.session_change).as<int*>() == 1)
			{
				*script_global(g_global.session_change).as<int*>() = 0;
				tick = 0;
			}

			if (tick >= 200)
				tick = 0;

			if (first_load)
			{
				HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("~bold~~y~Zerstorer ~g~Menu Connected With The Game~w~");
				HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", FALSE, 0, "~bold~~y~Zerstorer", "~y~~a~Premium Mod Menu");
				HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, true);
				first_load = false;
			}

			tick++;
		}
		static void when_game_closed()
		{
			if (!g_Running)
				message::notification("Zerstorer Gold Edition", "~bold~~g~Menu Unloaded", "~bold~~g~Zerstorer Unloader");
		}
		static const char* get_mod_slot_name(int mod_slot, Vehicle vehicle);
		static const char* get_mod_name(int mod, int mod_slot, int mod_count, Vehicle vehicle);
		static void get_vehicle_mod();
    };

	inline static game_helper g_game_helper;
}
