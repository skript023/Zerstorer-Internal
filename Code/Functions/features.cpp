#include "features.hpp"
#include "../ScriptGlobal.hpp"
#include "game_function.hpp"

namespace big::features
{
	void run_on_tick()
	{
		player::AutoHeal(g_features.auto_heal);
		player::set_player_invincible(PLAYER::PLAYER_ID(), g_features.godmode);
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(PLAYER::PLAYER_PED_ID(), g_features.infinite_clip);
		weapon::infinite_ammo(g_features.infinite_ammo);
	}
}