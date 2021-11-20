#include "features.hpp"
#include "../ScriptGlobal.hpp"
#include "game_function.hpp"
#include "game_helper.hpp"

namespace big::features
{
	void run_on_tick()
	{
		player::AutoHeal(g_features->auto_heal);
		player::set_player_invincible(PLAYER::PLAYER_ID(), g_features->godmode);
		player::set_player_no_clip(g_features->no_clip);
		player::set_player_no_collision(g_features->no_collision);
		player::no_idle_kick(g_features->no_idle_kick);

		player::set_explosive_ammo_this_frame(PLAYER::PLAYER_ID(), g_features->explosive_ammo);
		player::set_explosive_melee_this_frame(PLAYER::PLAYER_ID(), g_features->explosive_fist);
		player::set_fire_ammo_this_frame(PLAYER::PLAYER_ID(), g_features->fire_ammo);
		player::set_super_jump_this_frame(PLAYER::PLAYER_ID(), g_features->super_jump);

		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), g_features->infinite_clip);
		weapon::infinite_ammo(g_features->infinite_ammo);
		weapon::rapid_fire(g_features->rapid_fire);
		weapon::remove_object_gun(g_features->delete_gun);

		vehicle::vehicle_godmode(g_features->vehicle_godmode);
		vehicle::infinite_boost(g_features->infinite_boost);

		network::blind_cops(g_features->blind_cops);
		network::off_the_radar(g_features->off_the_radar);
		network::reveal_player(g_features->reveal_player);

		game_helper::game_frame();
	}
}