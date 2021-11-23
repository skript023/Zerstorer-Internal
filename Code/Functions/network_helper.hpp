#pragma once
#include "../Common.hpp"

namespace big
{
	class network
	{
	public:

		static void crash_player(Ped target_ped);

		static void blind_cops(bool Activation);

		static void reveal_player(bool Activation);

		static void off_the_radar(bool Activation);

		static void blame_player(Ped blame);

		static void add_owned_explosion(Ped ped, NativeVector3 pos, int explosionType, float damageScale, bool isAudible, bool isInvinsible, float ShakeCam);

		static void set_session(int SessionId);

	};
}