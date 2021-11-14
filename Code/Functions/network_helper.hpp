#pragma once
#include "../Common.hpp"

namespace big
{
	class network
	{
	public:

		static void add_owned_explosion(Ped ped, NativeVector3 pos, int explosionType, float damageScale, bool isAudible, bool isInvinsible, float ShakeCam);

		static void set_session(int SessionId);

	};
}