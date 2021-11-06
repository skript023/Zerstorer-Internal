#pragma once
#include "../Common.hpp"

namespace Big
{
	class weapon
	{
	public:
		static std::string get_weapon_name_from_hash(Hash weaponHash);
		static void infinite_ammo(bool Activation);
	};
}