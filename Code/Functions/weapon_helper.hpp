#pragma once
#include "../Common.hpp"

namespace big
{
	class weapon
	{
	public:
		static std::string get_weapon_name_from_hash(Hash weaponHash);
		static void ghost_gun(bool Activation);
		static void remove_object_gun(bool activation);
		static void rapid_fire(bool toggle);
		static void give_weapon(Ped target_ped);
		static void infinite_ammo(bool Activation);
	};
}