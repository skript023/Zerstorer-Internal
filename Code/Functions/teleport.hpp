#pragma once
#include "../Common.hpp"

namespace big
{
	class teleport
	{
	public:

		static NativeVector3 get_blip_coords(int icon_id, int icon_colour);

		static NativeVector3 get_mission_blip();

		static void teleport_to_marker();

		static void teleport_to_objective();

		static NativeVector3 get_ground_coords(NativeVector3 coords, int tries);

	};
}