#include "vehicle_helper.hpp"
#include "../ScriptCallback.hpp"
#include "game_helper.hpp"


namespace big
{
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
                else if (Flag == 1107558400 || Memory::Is_Bit_Set(Flag, 30) && BoostLevel < 1.24f && GetKeyState(0x45) & 0x8000)
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
                    _flags = Memory::Clear_Bit(_flags, 1); // Vehicle destroyed : "Your Personal Vehicle has been destroyed. You can call Mors Mutual Insurance to make a claim"
                    _flags = Memory::Clear_Bit(_flags, 7); // Insurance Claim open or in process
                    _flags = Memory::Clear_Bit(_flags, 16); // Vehicle outside the Garage and no Insurance or a Insurance Claim(is open or in process)
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
}