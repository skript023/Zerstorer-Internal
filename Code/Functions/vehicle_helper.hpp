#pragma once
#include "../Common.hpp"
#include "../Natives.hpp"

namespace big
{
	class vehicle
	{
	public:

		static void infinite_boost(bool Activation);

		static void vehicle_godmode(bool Activation);

		static void remove_insurance();

		static void repair_vehicle(Ped player_ped);

		static void create_vehicle(const char* name, Entity entity);

	};
}