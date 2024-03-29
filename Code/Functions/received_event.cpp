#include "../Hooking.hpp"
#include "../Classes/net_game_event.hpp"
#include "../Classes/Enum.hpp"
#include "../Natives.hpp"
#include "game_helper.hpp"
#include "game_event.hpp"
#include "hook_helper.hpp"
#include "../Classes/net_object_mgr.hpp"

namespace big
{
	bool Hooks::received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int64_t bit_buffer_size, rage::datBitBuffer* buffer)
	{
		if (event_id > 90u) return false;

		const char* event_name = *(char**)((DWORD64)event_manager + 8i64 * event_id + 243376);
		if (event_name == nullptr || source_player == nullptr || source_player->player_id < 0 || source_player->player_id >= 32)
		{
			g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
			return false;
		}

		switch (event_id)
		{
		case SCRIPTED_GAME_EVENT:
		{
			auto game_event = CScriptedGameEvent();
			buffer->ReadDword(&game_event.m_args_size, 32);
			if (game_event.m_args_size <= 0x1AF)
				buffer->ReadArray(&game_event.m_args, 8 * game_event.m_args_size);
			if (hook_helper::validate_game_event(&game_event, source_player, target_player))
			{
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return false;
			}
			buffer->Seek(0);
			break;
		}
		case NETWORK_INCREMENT_STAT_EVENT:
		{
			auto event_obj = CNetworkIncrementStatEvent();
			buffer->ReadDword(&event_obj.m_stat, 32);
			buffer->ReadDword(&event_obj.m_ammount, 32);
			if (hook_helper::report_status(&event_obj, source_player, target_player))
			{
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return false;
			}

			buffer->Seek(0);
			break;
		}
		case NETWORK_CLEAR_PED_TASKS_EVENT:
		{
			if (source_player->player_id < 32)
			{
				uint16_t network_id{};
				buffer->ReadWord(&network_id, 0xD);
				char sender_info[100];
				strcpy(sender_info, "~bold~~g~Blocked Clear Ped Task From ");
				strcat(sender_info, source_player->get_name());
				if (!CUTSCENE::IS_CUTSCENE_PLAYING() && (!(NETWORK::NETWORK_IS_ACTIVITY_SESSION() && get_local_vehicle()->m_model_info->m_model_hash == RAGE_JOAAT("VEHICLE_PBUS"))))
				{
					if (g_protection->clear_ped_task)
					{
						message::notification("Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");
						g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);

						return false;
					}
				}
				buffer->Seek(0);
			}

			break;
		}
		case REMOVE_WEAPON_EVENT:
		{
			uint16_t network_id{};
			buffer->ReadWord(&network_id, 0xD);
			char sender_info[100];
			strcpy(sender_info, "~bold~~g~Blocked Remove Weapon From ");
			strcat(sender_info, source_player->get_name());
			if (g_protection->block_remove_weapon)
			{
				message::notification("Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return false;
			}
			buffer->Seek(0);
			break;
		}
		// Don't block this event, we still want to report this player
		// because if we still report others, our account seems less fishy
		case REPORT_CASH_SPAWN_EVENT:
		{
			uint32_t money;

			buffer->Seek(64);
			buffer->ReadDword(&money, 32);
			buffer->Seek(0);

			if (money >= 2000)
			{
				char msg[64];
				strcpy(msg, "~bold~~g~<C>");
				strcat(msg, source_player->get_name());
				strcat(msg, "</C> is spawning cash.");
				message::notification("Zerstorer Menu", msg, "~bold~~g~Zerstorer Menu Protection");
			}

			break;
		}
		// player sending this event is a modder
		case NETWORK_CHECK_CODE_CRCS_EVENT:
		case REPORT_MYSELF_EVENT:
		{
			char msg[64];
			strcpy(msg, "~bold~~g~Detected <C>");
			strcat(msg, source_player->get_name());
			strcat(msg, "</C> as cheater.");
			message::notification("Zerstorer Menu", msg, "~bold~~g~Zerstorer Menu Protection");

			break;
		}
		case REQUEST_CONTROL_EVENT:
		{
			if (g_protection->block_request_control)
			{
				uint16_t network_id{};
				buffer->ReadWord(&network_id, 0xD);
				char sender_info[100];
				strcpy(sender_info, "~bold~~g~Blocked Request Control From ");
				strcat(sender_info, source_player->get_name());
				if (get_local_ped()->m_is_in_vehicle && get_local_ped()->m_last_vehicle->m_passanger == 1)
				{
					message::notification("Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");

					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return false;
				}
				buffer->Seek(0);
			}
			break;
		}
		case KICK_VOTES_EVENT:
		{
			uint32_t bitset{};
			buffer->ReadDword(&bitset, MAX_PLAYERS);
			char sender_info[128] = "~bold~~g~You Got Voted Kick By ";
			strcat(sender_info, source_player->get_name());
			if (g_protection->block_kick_vote && bitset & (1 << target_player->player_id))
			{
				message::notification("Zerstorer Menu", sender_info, "~bold~~g~Ellohim Protection");
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return false;
			}
			buffer->Seek(0);
			break;
		}
		case EXPLOSION_EVENT:
		{
			char sender_info[128] = "~bold~~g~You Got Explosion Event By ";
			strcat(sender_info, source_player->get_name());
			uint16_t explosion_owner{};
			uint32_t explosion_flags{};
			int32_t explosion_type{};
			buffer->Seek(29);
			buffer->ReadWord(&explosion_owner, 13);
			buffer->Seek(55);
			buffer->ReadInt32(&explosion_type, 8);
			buffer->Seek(149);
			buffer->ReadDword(&explosion_flags, 32);
			auto ped_owner_id = -1;
			if (auto net_obj = g_GameFunctions->m_get_network_object(*g_GameVariables->m_network_object_manager, explosion_owner, FALSE))
				ped_owner_id = net_obj->owner_id;
			if ((explosion_flags & 11) && source_player->player_id != ped_owner_id && ped_owner_id != -1)
			{
				if (g_protection->block_explosion_event)
				{
					message::notification("Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");
					g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
					return false;
				}
			}
			buffer->Seek(0);
			break;
		}
		case NETWORK_PTFX_EVENT:
		{
			uint16_t network_id{};
			buffer->ReadWord(&network_id, 0xD);
			char sender_info[100];
			strcpy(sender_info, "~bold~~g~Blocked PTFX Task From ");
			strcat(sender_info, source_player->get_name());
			if (g_protection->block_ptfx_event)
			{
				message::notification("Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");
				g_GameFunctions->m_send_event_ack(event_manager, source_player, target_player, event_index, event_handled_bitset);
				return false;
			}
			buffer->Seek(0);
			break;
		}
		}
		return static_cast<decltype(&received_event)>(g_Hooking->m_received_event)(event_manager, source_player, target_player, event_id, event_index, event_handled_bitset, bit_buffer_size, buffer);
	}
}