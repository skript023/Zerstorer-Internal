#pragma once
#include "../Classes/net_game_event.hpp"
#include "../Util.hpp"
#include "game_event.hpp"
#include "game_helper.hpp"

#pragma warning (disable:4189)

namespace big::hook_helper
{
	inline bool report_status(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		auto hash = net_event_struct->m_stat;
		auto amount = net_event_struct->m_ammount;
		const char* sender_name = sender->get_name();
		auto sender_id = sender->player_id;
		char sender_info[120] = "~g~Blocked Report From ";
		
		if (g_protection->block_report)
		{
			switch (hash)
			{
			case RAGE_JOAAT("MPPLY_GRIEFING"): //MPPLY_GRIEFING
			case RAGE_JOAAT("MPPLY_VC_ANNOYINGME"): //MPPLY_VC_ANNOYINGME
			case RAGE_JOAAT("MPPLY_VC_HATE"): //MPPLY_VC_HATE
			case RAGE_JOAAT("MPPLY_TC_ANNOYINGME"): //MPPLY_TC_ANNOYINGME
			case RAGE_JOAAT("MPPLY_TC_HATE"): //MPPLY_TC_HATE
			case RAGE_JOAAT("MPPLY_OFFENSIVE_LANGUAGE"): //MPPLY_OFFENSIVE_LANGUAGE
			case RAGE_JOAAT("MPPLY_OFFENSIVE_TAGPLATE"): //MPPLY_OFFENSIVE_TAGPLATE
			case RAGE_JOAAT("MPPLY_OFFENSIVE_UGC"): //MPPLY_OFFENSIVE_UGC
			case RAGE_JOAAT("MPPLY_BAD_CREW_NAME"): //MPPLY_BAD_CREW_NAME
			case RAGE_JOAAT("MPPLY_BAD_CREW_MOTTO"): //MPPLY_BAD_CREW_MOTTO
			case RAGE_JOAAT("MPPLY_BAD_CREW_STATUS"): //MPPLY_BAD_CREW_STATUS
			case RAGE_JOAAT("MPPLY_BAD_CREW_EMBLEM"): //MPPLY_BAD_CREW_EMBLEM
			case RAGE_JOAAT("MPPLY_GAME_EXPLOITS"): //MPPLY_GAME_EXPLOITS
			case RAGE_JOAAT("MPPLY_EXPLOITS"): //MPPLY_EXPLOITS
			case RAGE_JOAAT("MPPLY_FRIENDLY"):
			case RAGE_JOAAT("MPPLY_HELPFUL"):

				strcat(sender_info, sender_name);

				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Ellohim Menu Received Event");
				if (g_protection->redirect_report)
				{
					char redirect_message[120] = "~g~redirected to ";
					strcat(redirect_message, sender_name);
					message::notification("Event Redirect", redirect_message, "~bold~~g~Ellohim Menu Redirect");
					remote_event::bail_player(sender_id);
				}
				return true;
			}
		}
		return false;
	}

	inline bool validate_game_event(CScriptedGameEvent* net_event_struct, CNetGamePlayer* sender, CNetGamePlayer* receiver)
	{
		auto args = net_event_struct->m_args;
		auto sender_name = sender->get_name();
		auto ip_address = sender->get_net_data()->m_relay_ip;
		int args_size = net_event_struct->m_args_size;

		auto sender_id = sender->player_id;
		auto PlayerRID = sender->get_net_data()->m_rockstar_id;
		const auto EventHash = (int)args[0];
		char sender_info[100];
		switch (EventHash)
		{
		case TELEPORT_APARTMENT: //Invite
			if (g_protection->block_apartment)
			{
				strcpy(sender_info, "~g~Blocked Invite Event From ");
				strcat(sender_info, sender_name);

				return true; //lets return true if we return false we are really only moving the event to the buffer
			}
			break;
		case TELEPORT_CAYO: //send cayo
			if (g_protection->block_cayo)
			{
				strcpy(sender_info, "~g~Blocked Teleport Cayo Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");

				return true;
			}
			break;
		case CEO_KICK: //CEO Kick
			if (g_protection->block_ceo_kick)
			{
				strcpy(sender_info, "~g~Blocked CEO Kick Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");

				return true;
			}
			break;
		case CEO_BAN: //CEO Ban
			if (g_protection->block_ceo_ban)
			{
				strcpy(sender_info, "~g~Blocked CEO Ban Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");

				return true;
			}
			break;
		case ROTATE_CAM: //Rotete Cam
			if (g_protection->block_rotate_cam)
			{
				/*
				HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Blocked Rotete Cam");
				HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", FALSE, 0, sender_name, "~g~Zerstorer Menu Protection");
				HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, true);
				*/
				return true;
			}
			break;
		case VEHICLE_KICK: //Vehicle Kick
			if (g_protection->block_vehicle_kick)
			{
				strcpy(sender_info, "~g~Blocked Vehicle Kick Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");

				return true;
			}
			break;
		case TRANSACTION_ERROR:
			if (g_protection->block_transaction_error)
			{
				strcpy(sender_info, "~g~Blocked Transaction Error Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");

				return true;
			}
			break;
		case SEND_TO_MISSION_1:
		case SEND_TO_MISSION_2:
			if (g_protection->block_send_mission)
			{
				strcpy(sender_info, "~g~Blocked Force Mission Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");

				return true;
			}
			break;
		case PHONE_INVITE:
			if (g_protection->block_spam)
			{
				strcpy(sender_info, "~g~Blocked Phone Spam Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");

				return true;
			}
			break;
		case 2092565704:
			if (g_protection->block_kick)
			{
				strcpy(sender_info, "~g~Blocked Network Error From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");

			}
			break;
		case 515799090:
		case 1767220965:
		case 1305720168:
		case -275229102:
		case -654645351:
		case 1848973789:
		case -194543830:
		case -2063448951:
		case 797978700:
		case -176858990:
		case 1731962870:
		case 1152266822:
		case 257478565:
		case 23010443:
		case 496476216:
		case 1455421717:
		case -419415284:
		case 1358851648:
		case -525866785:
		case -1277389265:
		case -892744477:
		case 600486780:
			if (g_protection->block_kick)
			{
				return true;
			}
			break;
		case 1463355688: //Kick
		case 575344561: //Kick Host
		case -1382676328: //Kick Host
		case 1256866538: //Kick Sp
		case -1753084819: //Kick SP
		case 1119864805: //Kick
		case -1833002148: //Kick
		case -1587276086: //Kick
		case 1954846099: //Kick 1964309656
		case 1659915470://
		case -2017818728: // Kick Host
		case 27785517: // Kick Host
		case 641157117:
		case -347755611: // Kick Host
		case -137439024: // Kick Host
		case 161038699: // Kick Host
		case -1813981910:
		case 202252150:
		case -1503282114:
		case 243981125:
		case -1836118977:
		case -169685950:
		case -2071141142:
		case -149227625:
		case 1433396036:
		case 1608876738:
		case 458875017:
		case 987018372:
		case 813647057:
		case 696123127:
			if (g_protection->block_kick)
			{
				strcpy(sender_info, "~g~Blocked Kick Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Menu Protection");

			}
			break;
		}

		return false;
	}
}