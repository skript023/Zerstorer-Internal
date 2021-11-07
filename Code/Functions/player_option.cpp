#include "player_option.hpp"
#include "game_helper.hpp"
#include "weapon_helper.hpp"

namespace big
{
	void player::set_player_invincible(Player player, bool activate)
	{
		if (auto ped = get_player(player))
		{
			if (activate)
				ped->enable_invincible();
			else
				ped->disable_invincible();
		}
	}

	void player::set_player_no_clip(bool toggle)
	{
		if (toggle)
		{
			int e = get_local_ped()->m_is_in_vehicle ? PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : PLAYER::PLAYER_PED_ID();

			NativeVector3 pos = ENTITY::GET_ENTITY_COORDS(e, false);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
			if (GetAsyncKeyState(systems::hotkey('S')))
			{
				float fivef = 0.5f;
				float heading = ENTITY::GET_ENTITY_HEADING(e);
				float xVec = fivef * sin(systems::degree(heading)) * -1.5f;
				float yVec = fivef * cos(systems::degree(heading));
				ENTITY::SET_ENTITY_HEADING(e, heading);

				pos.x -= xVec, pos.y -= yVec;
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
			}
			if (GetAsyncKeyState(systems::hotkey('W')))
			{
				float fivef = 0.5f;
				float heading = ENTITY::GET_ENTITY_HEADING(e);
				float xVec = fivef * sin(systems::degree(heading)) * -1.5f;
				float yVec = fivef * cos(systems::degree(heading));
				ENTITY::SET_ENTITY_HEADING(e, heading);

				pos.x += xVec, pos.y += yVec;
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
			}
			if (GetAsyncKeyState(systems::hotkey('A')))
			{
				float fivef = 0.5f;
				float heading = ENTITY::GET_ENTITY_HEADING(e);
				ENTITY::SET_ENTITY_HEADING(e, heading + 0.5f);
			}
			if (GetAsyncKeyState(systems::hotkey('D')))
			{
				float fivef = 0.5f;
				float heading = ENTITY::GET_ENTITY_HEADING(e);
				ENTITY::SET_ENTITY_HEADING(e, heading - 0.5f);
			}
			if (GetAsyncKeyState(VK_CONTROL))
			{
				float heading = ENTITY::GET_ENTITY_HEADING(e);
				ENTITY::SET_ENTITY_HEADING(e, heading);

				pos.z -= 0.5f;
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
			}
			if (GetAsyncKeyState(VK_SHIFT))
			{
				float heading = ENTITY::GET_ENTITY_HEADING(e);
				ENTITY::SET_ENTITY_HEADING(e, heading);

				pos.z += 0.5f;
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, pos.x, pos.y, pos.z, false, false, false);
			}
		}
	}

	void player::set_player_health(Player player, int HealthValue)
	{
		if (auto pointer = get_player(player))
		{
			pointer->m_health = systems::int_to_float(HealthValue);
		}
	}

	void player::set_player_armour(Player player, int ArmourValue)
	{
		if (auto pointer = get_player(player))
		{
			pointer->m_armor = systems::int_to_float(ArmourValue);
		}
	}

	void player::AutoHeal(bool Activation)
	{
		if (Activation)
		{
			int player_health = get_player_health(PLAYER::PLAYER_ID());
			int player_max_health = get_player_max_health(PLAYER::PLAYER_ID());
			int player_max_armor = PLAYER::GET_PLAYER_MAX_ARMOUR(PLAYER::PLAYER_ID());
			if (player_health >= 100 && player_health <= 200)
			{
				set_player_health(PLAYER::PLAYER_ID(), player_max_health);
				set_player_armour(PLAYER::PLAYER_ID(), player_max_armor);
				get_local_playerinfo()->m_damage_hp = 0.3f;
			}
			else
			{
				get_local_playerinfo()->m_damage_hp = 1.0f;
			}
		}
	}

    Ped player::get_player_ped(Player player)
    {
        if (auto ped = get_player(player))
        {
            return pointer_to_entity(ped);
        }
        return 0;
    }

    int player::get_player_max_health(Player player)
    {
        if (auto ped = get_player(player))
        {
            return systems::float_to_int(ped->m_max_health);
        }
        return 0;
    }

    int player::get_player_health(Player player)
    {
        if (auto ped = get_player(player))
        {
            return systems::float_to_int(ped->m_health);
        }
        return 0;
    }

    int player::get_player_armour(Player player)
    {
        if (auto ped = get_player(player))
        {
            return systems::float_to_int(ped->m_armor);
        }
        return 0;
    }

    int player::get_player_max_amour(Player player)
    {
        return PLAYER::GET_PLAYER_MAX_ARMOUR(player);
    }
    /*
    std::string player::get_player_ip(Player player)
    {
        uint32_t player_ip = 0;
        if (auto ped = get_player(player))
        {
            player_ip = ped->m_playerinfo->m_online_ip;
        }
        return fmt::format("{}.{}.{}.{}", (player_ip >> 24) & 0xff, (player_ip >> 16) & 0xff, (player_ip >> 8) & 0xff, player_ip & 0xff);
    }
    */
    uint64_t player::get_player_scid(Player player)
    {
        if (auto ped = get_player(player))
        {
            return ped->m_playerinfo->m_rockstar_id;
        }
        return 0;
    }

    int player::get_player_wanted_level(Player player)
    {
        if (auto ped = get_player(player))
        {
            return ped->m_playerinfo->m_wanted_level;
        }
        return 0;
    }

    bool player::get_player_invincible(Player player)
    {
        if (auto ped = get_player(player))
        {
            return ped->is_invincible();
        }
        return false;
    }

    bool player::get_player_waterproof(Player player)
    {
        if (auto ped = get_player(player))
        {
            return ped->is_water_proof();
        }
        return false;
    }

    bool player::get_player_vehicle_invincible(Entity entity)
    {
        if (CVehicle* e = entity_to_pointer<CVehicle*>(entity))
        {
            return e->is_invincible();
        }
        return false;
    }

    std::string player::get_player_weapon(Player player)
    {
        if (auto ped = get_player(player))
        {
            if (auto weapon = ped->m_weapon_mgr)
            {
                if (auto weapon_info = weapon->m_weapon_info)
                {
                    if (auto weapon_hash = weapon_info->m_weapon_hash)
                    {
                        return weapon::get_weapon_name_from_hash(weapon_hash);
                    }
                }
            }
        }
        return weapon::get_weapon_name_from_hash(0);
    }

    std::string player::get_player_vehicle_name(Player player)
    {
        if (auto ped = get_player(player))
        {
            if (ped->m_is_in_vehicle)
            {
                if (auto vehicle = ped->m_last_vehicle)
                {
                    if (auto vehicle_info = vehicle->m_model_info)
                    {
                        return vehicle_info->m_vehicle_name;
                    }
                }
            }
        }
        return "Not In Vehicle";
    }
    
    const char* player::get_player_name(Player player)
    {
        return g_GameFunctions->m_get_player_name(player);
    }
    
    NativeVector3 player::get_player_coords(Player player)
    {
        if (auto ped = get_player(player))
        {
            return systems::to_scr_vector(ped->m_navigation->m_position);
        }
        return NativeVector3(0.f, 0.f, 0.f);
    }

    bool player::get_player_infinite_clip(Player player)
    {
        if (auto ped = get_player(player))
        {
            return ped->m_weapon_inventory->is_infinite_clip();
        }
        return false;
    }

    bool player::get_player_infinite_ammo(Player player)
    {
        if (auto ped = get_player(player))
        {
            return ped->m_weapon_inventory->is_infinite_ammo();
        }
        return false;
    }

	void set_explosive_ammo_this_frame(Player player, bool activate)
	{
		if (activate)
		{
			if (auto ped = get_player(player))
			{
				ped->m_playerinfo->m_frame_flags |= (1 << 11);
			}
		}
	}
}