#pragma once
#include "../Common.hpp"

namespace big
{
	class casino_heist
	{
	public:
		static void all_heist_take(int Take);
		static void remove_crew_heist(bool Activation);
		static void auto_heist_cut(bool Activate);
		static void heist_crew_cut_zero(bool Activation);
	};
}