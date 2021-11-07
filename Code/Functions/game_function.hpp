#pragma once
#include "player_option.hpp"
#include "weapon_helper.hpp"
#include "game_event.hpp"
#include "heist_helper.hpp"
#include "systems_helper.hpp"
#include "vehicle_helper.hpp"
#include "business_helper.hpp"
#include "network_helper.hpp"
#include "game_variable.hpp"

static class selected_player
{
public:
	static inline std::uint32_t player{};
	static inline std::uint32_t ped{};
	static inline std::uint32_t vehicle_category{};
	static inline const char* vehicle{};
} g_selected;

static class features
{
public:
	static inline int64_t tick{};
	static inline bool godmode{};
	static inline bool vehicle_godmode{};
	static inline bool infinite_clip{};
	static inline bool infinite_ammo{};
	static inline bool auto_heal{};
	static inline bool no_ragdoll{};
	static inline bool seatbelt{};
	static inline bool never_wanted{};
	static inline bool spectating{};
	static inline bool no_collision{};
	static inline bool no_clip{};
	static inline bool no_idle_kick{};
} g_features;