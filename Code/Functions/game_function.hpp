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
#include "teleport.hpp"
#include "stat_helper.hpp"
#include "../teleport_persist.hpp"

namespace big
{
	static class selected_player
	{
	public:
		static inline std::uint32_t player{};
		static inline std::uint32_t ped{};
		static inline std::uint32_t vehicle_category{};
		static inline const char* vehicle{};
	} g_selected;

	class contents
	{
	public:
		static inline int64_t tick{};
		static inline bool godmode{};
		static inline bool vehicle_godmode{ true };
		static inline bool infinite_clip{};
		static inline bool infinite_ammo{ true };
		static inline bool auto_heal{ true };
		static inline bool no_ragdoll{};
		static inline bool seatbelt{true};
		static inline bool never_wanted{};
		static inline bool spectating{};
		static inline bool no_collision{};
		static inline bool no_clip{};
		static inline bool no_idle_kick{ true };

		static inline char spoofer_name[20];
		static inline char spoofer_rid[100];
		static inline float player_kill_death_ratio{};
		static inline int player_level{};
		static inline int total_evc{};
		static inline int total_svc{};
		static inline int money_earn_jobs{};



		static inline bool super_jump{};
		static inline bool explosive_ammo{};
		static inline bool explosive_fist{};
		static inline bool fire_ammo{};

		static inline bool rapid_fire{};
		static inline bool delete_gun{};
		static inline bool ghost_gun{};


		static inline bool off_the_radar{};
		static inline bool reveal_player{};
		static inline bool blind_cops{};


		static inline int mc_business_money{};
		static inline bool mc_supply_bool{};
		static inline bool mc_timer_bool{};

		static inline int bunker_business_money{};
		static inline bool bunker_supply_bool{};
		static inline bool bunker_timer_bool{};
		static inline bool research{};


		static inline bool sell_cargo_cooldown{};
		static inline bool buy_cargo_cooldown{};
		static inline bool cargo_selling_time{};
		static inline int cargo_money{};
		static inline int cargo_crates{};

		//Vehicle
		static inline bool boost_flag{};
		static inline bool jump_flag{};
		static inline bool parachute_flag{};
		static inline bool oppressor_flag{};
		static inline bool infinite_boost{};

		static inline int player_lives{};
	};

	inline static contents* g_features{};
}