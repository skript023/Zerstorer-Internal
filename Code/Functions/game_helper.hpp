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
}