#include "../Hooking.hpp"
#include "game_helper.hpp"
#include "game_function.hpp"
#include "../Classes/Player.hpp"
#include "player_option.hpp"

namespace big
{
	bool Hooks::send_net_info_to_lobby(rage::netPlayerData* local_player, __int64 a2, __int64 a3, DWORD* a4)
	{
		auto name = std::string(local_player->m_name);
		std::string name_real = g_GameVariables->m_real_name;
		auto scid_real = *g_GameVariables->m_player_user_id;

		if (scid_real == local_player->m_rockstar_id)
		{
			std::string spoof_name(g_features->spoofer_name);
			uint64_t spoof_scid = atoi(g_features->spoofer_rid);
			bool name_diff = !spoof_name.empty() && spoof_name != name;
			bool scid_diff = spoof_scid != 0 && spoof_scid != local_player->m_rockstar_id;

			if (name_diff)
				player::change_name(spoof_name, local_player);//player::local_name((char*)spoof_name.c_str());
			if (scid_diff)
				local_player->m_rockstar_id = spoof_scid; 

			if (!name_diff)
				message::notification("~bold~~g~Ellohim Private Menu", "Your Name Spoofed", "~bold~~g~Ellohim Spoofer");
			if (!scid_diff)
				message::notification("~bold~~g~Ellohim Private Menu", "Your RID Spoofed", "~bold~~g~Ellohim Spoofer");

			auto retnvalue = static_cast<decltype(&send_net_info_to_lobby)>(g_Hooking->m_send_net_info_to_lobby_hook)(local_player, a2, a3, a4);
			if (scid_diff)
				local_player->m_rockstar_id = scid_real;
			return retnvalue;
		}
		return static_cast<decltype(&send_net_info_to_lobby)>(big::g_Hooking->m_send_net_info_to_lobby_hook)(local_player, a2, a3, a4);
	}
}