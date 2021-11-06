#pragma once
#include "player_option.hpp"
#include "weapon_helper.hpp"
#include "game_event.hpp"
#include "heist_helper.hpp"
#include "systems_helper.hpp"

static class selected_player
{
public:
	static inline std::int32_t player{};
	static inline std::int32_t ped{};
} g_selected;

static class features
{
public:
	static inline bool godmode{};
	static inline bool infinite_clip{};
	static inline bool infinite_ammo{};
	static inline bool auto_heal{};
	static inline bool no_ragdoll{};
	static inline bool seatbelt{};
	static inline bool never_wanted{};
} g_features;