#pragma once
#include "../Common.hpp"
#include "../Natives.hpp"

namespace Big
{
	class player
	{
	public:
		static void set_player_invincible(Player player, bool activate);
		static bool get_player_infinite_ammo(Player player);
		static bool get_player_infinite_clip(Player player);
		static void set_player_no_clip(bool toggle);
		static void set_player_health(Player player, int HealthValue);
		static void set_player_armour(Player player, int ArmourValue);
		static void AutoHeal(bool Activation);

		static int get_player_health(Player player);
		static int get_player_max_health(Player player);
		static int get_player_armour(Player player);
		static int get_player_max_amour(Player player);

		static uint64_t get_player_scid(Player player);
		static std::string get_player_weapon(Player player);
		static std::string get_player_vehicle_name(Player player);
		static int get_player_wanted_level(Player player);
		bool get_player_invincible(Player player);
		static const char* get_player_name(Player player);
		static NativeVector3 get_player_coords(Player player);
		static bool get_player_vehicle_invincible(Entity entity);
		static bool get_player_waterproof(Player player);

		static Ped get_player_ped(Player player);
	};
}