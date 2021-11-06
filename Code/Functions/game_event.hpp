#pragma once
#include "../Common.hpp"
#include "../Natives.hpp"

namespace big
{
	class remote_event
	{
	public:
		static void take_all_cayo(int take);
		static void take_all_casino(int take);
		static void take_casino_partial(int take);
		//static void get_name_from_event_hash(int32_t hash);
		static void off_the_radar(Player player, bool toggle);
		static void bribe_authority(Player player, bool toggle);
		static void bail_player(Player player);
		//static void revenge_kick(bool Activation);
		static void teleport_player_to_cayo(Player player);
		static void force_invite_apartment(Player player);
		static void ceo_kick(Player player);
		static void ceo_ban(Player player);
		static void rotate_cam(Player player);
		static void vehicle_kick(Player player);
		static void clear_wanted(Player player);
		static void kick_player(Player player);
		static void transaction_fail(Player player);
		static void send_to_mission(Player player);
		static void give_fake_money(Player player, int TotalMoney);
		static void remove_fake_money(Player player, int TotalMoney);
		static void steal_fake_money(Player player, int TotalMoney);
		//static void give_wanted_level(Player player);
	};
}