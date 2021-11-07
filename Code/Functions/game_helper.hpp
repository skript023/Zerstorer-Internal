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

			tick++;
		}
		static void when_game_closed()
		{
			if (!g_Running)
				message::notification("Zerstorer Gold Edition", "~bold~~g~Menu Unloaded", "~bold~~g~Zerstorer Unloader");
		}
    };

	inline static game_helper g_game_helper;
}
