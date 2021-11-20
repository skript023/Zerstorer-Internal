#include "vehicle_helper.hpp"
#include "../ScriptCallback.hpp"
#include "game_helper.hpp"
#include "vehicle_value.h"


namespace big
{
    void vehicle::set_flag(int Flag, uint32_t flagBit)
    {
        if (get_local_ped()->m_is_in_vehicle)
        {
            switch (Flag)
            {
            case 1:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_1;
                uint32_t bit_set = Memory::set_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_1 = bit_set;
                break;
            }
            case 2:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_2;
                uint32_t bit_set = Memory::set_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_2 = bit_set;
                break;
            }
            case 3:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_3;
                uint32_t bit_set = Memory::set_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_3 = bit_set;
                break;
            }
            case 4:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_4;
                uint32_t bit_set = Memory::set_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_4 = bit_set;
                break;
            }
            case 5:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_5;
                uint32_t bit_set = Memory::set_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_5 = bit_set;
                break;
            }
            case 6:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_6;
                uint32_t bit_set = Memory::set_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_6 = bit_set;
                break;
            }
            case 7:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_7;
                uint32_t bit_set = Memory::set_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_7 = bit_set;
                break;
            }
            }
        }
    }

    void vehicle::clear_flag(int Flag, uint32_t flagBit)
    {
        if (get_local_ped()->m_is_in_vehicle)
        {
            switch (Flag)
            {
            case 1:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_1;
                uint32_t bit_set = Memory::clear_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_1 = bit_set;
                break;
            }
            case 2:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_2;
                uint32_t bit_set = Memory::clear_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_2 = bit_set;
                break;
            }
            case 3:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_3;
                uint32_t bit_set = Memory::clear_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_3 = bit_set;
                break;
            }
            case 4:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_4;
                uint32_t bit_set = Memory::clear_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_4 = bit_set;
                break;
            }
            case 5:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_5;
                uint32_t bit_set = Memory::clear_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_5 = bit_set;
                break;
            }
            case 6:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_6;
                uint32_t bit_set = Memory::clear_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_6 = bit_set;
                break;
            }
            case 7:
            {
                auto set_bit = get_local_ped()->m_last_vehicle->m_model_info->m_flag_7;
                uint32_t bit_set = Memory::clear_bit(set_bit, flagBit);
                get_local_ped()->m_last_vehicle->m_model_info->m_flag_7 = bit_set;
                break;
            }
            }
        }
    }

    Vehicle vehicle::get_personal_vehicle(Player player)
    {
        if (joaat(SCRIPT::GET_THIS_SCRIPT_NAME()) == RAGE_JOAAT("freemode"))
        {
            if (NETWORK::NETWORK_DOES_NETWORK_ID_EXIST(*script_global(2426865).at(player, 449).at(38).as<int*>()) && NETWORK::NETWORK_DOES_ENTITY_EXIST_WITH_NETWORK_ID(*script_global(2426865).at(player, 449).at(38).as<int*>()))
            {
                return NETWORK::NET_TO_VEH(*script_global(2426865).at(player, 449).at(38).as<int*>());
            }
        }
        return *script_global(2544210).at(298).as<int*>();
    }

    void vehicle::infinite_boost(bool Activation)
    {
        if (Activation)
        {

            if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
            {
                auto VehicleHash = get_local_ped()->m_last_vehicle->m_model_info->m_model_hash;
                auto Flag = get_local_ped()->m_last_vehicle->m_model_info->m_flag_4; //*(uint32_t*)((DWORD64)VehicleInfo + 0x588);
                auto BoostLevel = get_local_vehicle()->m_vehicle_boost;//Memory::get_value<float>(g_ptr.WorldPTR, { 0x8, 0xD30, 0x320 });//*(float*)((DWORD64)VehiclePTR + 0x320);

                if (VehicleHash == RAGE_JOAAT("Oppressor2") && BoostLevel < 0.99f && GetKeyState(0x58) & 0x8000)
                {
                    get_local_vehicle()->m_vehicle_boost = 1.00f;
                }
                else if (VehicleHash == RAGE_JOAAT("Scramjet") && BoostLevel < 2.24f && GetKeyState(0x58) & 0x8000)
                {
                    get_local_vehicle()->m_vehicle_boost = 2.25f;
                }
                else if (VehicleHash == RAGE_JOAAT("Toreador") && BoostLevel < 0.99f && GetKeyState(0x45) & 0x8000)
                {
                    get_local_vehicle()->m_vehicle_boost = 1.00f;
                }
                else if (VehicleHash == RAGE_JOAAT("Voltic2") || VehicleHash == RAGE_JOAAT("Oppressor") || VehicleHash == RAGE_JOAAT("Vigilante") && GetKeyState(0x45) && BoostLevel < 1.24f)
                {
                    get_local_vehicle()->m_vehicle_boost = 1.25f;
                }
                else if (Flag == 1107558400 || Memory::is_bit_set(Flag, 30) && BoostLevel < 1.24f && GetKeyState(0x45) & 0x8000)
                {
                    get_local_vehicle()->m_vehicle_boost = 1.25f;
                }
                else
                {
                    return;
                }
            }
        }
    }

    void vehicle::vehicle_godmode(bool Activation)
    {
        if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE))
        {
            auto VehId = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
            if (Activation)
            {
                ENTITY::SET_ENTITY_INVINCIBLE(VehId, TRUE);
                VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(VehId, FALSE);
                ENTITY::SET_ENTITY_PROOFS(VehId, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
                VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(VehId, FALSE);
                VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(VehId, FALSE);
                if (VEHICLE::_IS_VEHICLE_DAMAGED(VehId))
                {
                    VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(VehId);
                    GRAPHICS::REMOVE_DECALS_FROM_VEHICLE(VehId);
                    if (!VEHICLE::IS_VEHICLE_WINDOW_INTACT(VehId, 6))
                        VEHICLE::FIX_VEHICLE_WINDOW(VehId, 6);
                    if (!VEHICLE::IS_VEHICLE_WINDOW_INTACT(VehId, 7))
                        VEHICLE::FIX_VEHICLE_WINDOW(VehId, 7);
                }
            }
            else
            {
                ENTITY::SET_ENTITY_INVINCIBLE(VehId, FALSE);
                VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(VehId, TRUE);
                ENTITY::SET_ENTITY_PROOFS(VehId, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
                VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(VehId, TRUE);
                VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(VehId, TRUE);
            }
        }
    }

    void vehicle::remove_insurance()
    {
        int _maxslots = 0, _index = 0, _hash = 0, _flags = 0;
        _maxslots = *script_global(1323703).as<int*>();//1323678
        for (int i = 0; i < _maxslots; i++)
        {
            _index = 1323703 + 1 + (i * 142);
            _hash = *script_global(_index).at(66).as<int*>();
            if (_hash != 0)
            {
                _flags = *script_global(_index).at(103).as<int*>();
                if (_flags != 0)
                {
                    _flags = Memory::clear_bit(_flags, 1); // Vehicle destroyed : "Your Personal Vehicle has been destroyed. You can call Mors Mutual Insurance to make a claim"
                    _flags = Memory::clear_bit(_flags, 7); // Insurance Claim open or in process
                    _flags = Memory::clear_bit(_flags, 16); // Vehicle outside the Garage and no Insurance or a Insurance Claim(is open or in process)
                    *script_global(_index).at(103).as<int*>() = _flags;
                }
            }
        }
    }

    void vehicle::repair_vehicle(Ped player_ped)
    {
        Vehicle VehicleId = PED::GET_VEHICLE_PED_IS_IN(player_ped, FALSE);

        g_CallbackScript->AddCallback<NetworkControlCallback>((VehicleId), [=]
        {
            VEHICLE::SET_VEHICLE_FIXED(VehicleId);
            VEHICLE::SET_VEHICLE_ENGINE_HEALTH(VehicleId, 1000.0f);
            VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(VehicleId, 1000.0f);
            VEHICLE::SET_VEHICLE_DIRT_LEVEL(VehicleId, 0.0f);
            if (!VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(VehicleId))
            {
                VEHICLE::SET_VEHICLE_ENGINE_ON(VehicleId, TRUE, TRUE, FALSE);
            }
        });
    }

    void vehicle::create_vehicle(const char* name, Entity entity)
    {
        Hash hash_vehicle = joaat(name);
        g_CallbackScript->AddCallback<ModelCallback>((hash_vehicle), [=]
        {
            if (!*g_GameVariables->m_is_session_started) *script_global(4270934).as<bool*>() = true;
            auto pos = ENTITY::GET_ENTITY_COORDS(entity, TRUE);
            auto forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
            auto heading = ENTITY::GET_ENTITY_HEADING(entity);

            pos.x += 10.0f * forward.x;
            pos.y += 10.0f * forward.y;
            //MISC::GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, pos.z, &pos.z, TRUE, FALSE);

            *(unsigned short*)g_GameVariables->m_model_spawn_bypass = 0x9090;
            auto vehicle = VEHICLE::CREATE_VEHICLE(hash_vehicle, pos.x, pos.y, pos.z + 0.5f, heading + 90.0f, TRUE, TRUE, FALSE);
            *(unsigned short*)g_GameVariables->m_model_spawn_bypass = 0x0574;

            if (*g_GameVariables->m_is_session_started)
            {
                DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
                ENTITY::_SET_ENTITY_SOMETHING(vehicle, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
                auto networkId = NETWORK::VEH_TO_NET(vehicle);
                if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
                    NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
                VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
            }

            VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle, 1.f);
            VEHICLE::_SET_VEHICLE_CAN_BE_LOCKED_ON(vehicle, FALSE, FALSE);
            VEHICLE::_SET_VEHICLE_MAX_SPEED(vehicle, 1.39f * VEHICLE::GET_VEHICLE_ESTIMATED_MAX_SPEED(vehicle));
            VEHICLE::MODIFY_VEHICLE_TOP_SPEED(vehicle, 1.39f);
            VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, "Janda");

            if (g_game_helper.auto_getin)
            {
                PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
            }

            if (g_game_helper.full_upgrade)
            {
                VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_XENONHEADLIGHTS, TRUE);
                VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TURBO, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 0, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 1, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 2, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, 3, TRUE);
                VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, NEON_COLOR_RED);
                VEHICLE::_SET_VEHICLE_XENON_LIGHTS_COLOR(vehicle, 8);
                VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);

                for (int i = 0; i < 50; i++)
                {
                    VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, TRUE);
                }
                VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, 9);
                VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_FRONTWHEEL, 52, TRUE);
            }

            if (VEHICLE::IS_THIS_MODEL_A_PLANE(hash_vehicle))
            {
                VEHICLE::SET_PLANE_TURBULENCE_MULTIPLIER(vehicle, 0.0f);
            }
            STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash_vehicle);
            if (g_game_helper.auto_getin)
            {
                STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
                GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
                GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY("scr_clown_appears", PLAYER::PLAYER_PED_ID(), 0.0f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.6f, false, false, false);
            }
        });
    }
}