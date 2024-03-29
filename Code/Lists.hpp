#pragma once
#include "UI/UIManager.hpp"

namespace big::Lists
{
	inline const char* HeaderTypesFrontend[]
	{
		"Static",
		"Gradient",
		"Custom"
	};

	inline UserInterface::HeaderType HeaderTypesBackend[]
	{
		UserInterface::HeaderType::Static,
		UserInterface::HeaderType::Gradient,
		UserInterface::HeaderType::Ytd
	};

	inline std::size_t HeaderTypesPosition = 1;

	inline const char* DemoList[10]
	{
		"One",
		"Two",
		"Three",
		"Four",
		"Five",
		"Six",
		"Seven",
		"Eight",
		"Nine",
		"Ten"
	};

	inline std::size_t DemoListPos = 0;

	inline const char* session_list[11]{
		"Join Public Session", "New Public Session", "Closed Crew Session", "Crew Session",
		"Closed Friend Session", "Find Friend Session","Solo Session", "Invite Only Session",
		"Join Crew Session", "Join SCTV", "Leave GTA Online"
	};

	inline std::size_t session_list_pos = 0;

	inline const char* casino_heist[]{ "Silent", "Bigcon", "Aggressive" };

	inline std::size_t casino_heist_pos = 0;

	inline const char* special_cargo_rare_items[] = { "Ornament Egg", "Gold Minigun", "Large Diamond", "Rare Hide", "Film Reel", "Pocket Watch" };

	inline std::size_t special_cargo_selected = 0;
}
