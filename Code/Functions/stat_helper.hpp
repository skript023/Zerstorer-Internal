#pragma once
#include "../Common.hpp"
#include "../Natives.hpp"

namespace big
{
	class stats
	{
	public:
		static void player_kill_death_ratio(float ratio);
		static void unlock_bunker_research(bool activate);
		static int packed_stat_mask(int iParam0);
		static int packed_stat_name(int iParam0, int iParam1);
		static std::string packed_reversed(uint32_t hash);
		static int get_packed_int(int iParam0, int iParam1, int iParam2);
		static bool set_packed_int(int iParam0, int iParam1, int iParam2, bool bParam3);
		static bool set_packed_bool(int iParam0, bool bParam1, int iParam2, int iParam3);
		static int packed_bool_stat_mask(int iParam0);
		static int packed_bool_stat_name(int iParam0, int iParam1);
		static bool get_packed_bool(int iParam0, int iParam1, int iParam2);
	};
}