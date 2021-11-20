#include "game_helper.hpp"
#include "vehicle_value.h"

namespace big
{
    script_local game_helper::mission_lives()
    {
        if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller")))
        {
            if (auto fm_mission_controller = find_script_thread(RAGE_JOAAT("fm_mission_controller")))
            {
                return script_local(fm_mission_controller, m_local.tc_live);
            }
        }
        else if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020")))
        {
            if (auto mission_controller_2020 = find_script_thread(RAGE_JOAAT("fm_mission_controller_2020")))
            {
                return script_local(mission_controller_2020, m_local.tc_live_c);
            }
        }
        //return script_local(find_script_thread(RAGE_JOAAT("main_persistent")), 0);
    }

    const char* game_helper::get_mod_slot_name(int mod_slot, Vehicle vehicle)
    {
        Hash model = ENTITY::GET_ENTITY_MODEL(vehicle);
        switch (mod_slot)
        {
        case MOD_HOOD:
            return HUD::_GET_LABEL_TEXT("CMOD_MOD_HOD");
        case MOD_ARMOR:
            return HUD::_GET_LABEL_TEXT("CMOD_MOD_ARM");
        case MOD_BRAKES:
            return HUD::_GET_LABEL_TEXT("CMOD_MOD_BRA");
        case MOD_ENGINE:
            return HUD::_GET_LABEL_TEXT("CMOD_MOD_ENG");
        case MOD_SUSPENSION:
            return HUD::_GET_LABEL_TEXT("CMOD_MOD_SUS");
        case MOD_TRANSMISSION:
            return HUD::_GET_LABEL_TEXT("CMOD_MOD_TRN");
        case MOD_HORNS:
            return HUD::_GET_LABEL_TEXT("CMOD_MOD_HRN");
        case MOD_FRONTWHEEL:
            if (!VEHICLE::IS_THIS_MODEL_A_BIKE(model) && VEHICLE::IS_THIS_MODEL_A_BICYCLE(model))
                return HUD::_GET_LABEL_TEXT("CMOD_MOD_WHEM");
            else
                return HUD::_GET_LABEL_TEXT("CMOD_WHE0_0");
        case MOD_REARWHEEL:
            return HUD::_GET_LABEL_TEXT("CMOD_WHE0_1");
            //Bennys
        case MOD_PLATEHOLDER:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S0");
        case MOD_VANITYPLATES:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S1");
        case MOD_TRIMDESIGN:
            if (model == VEHICLE_SULTANRS)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S2b");
            else
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S2");
        case MOD_ORNAMENTS:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S3");
        case MOD_DASHBOARD:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S4");
        case MOD_DIALDESIGN:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S5");
        case MOD_DOORSPEAKERS:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S6");
        case MOD_SEATS:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S7");
        case MOD_STEERINGWHEELS:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S8");
        case MOD_COLUMNSHIFTERLEVERS:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S9");
        case MOD_PLAQUES:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S10");
        case MOD_SPEAKERS:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S11");
        case MOD_TRUNK:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S12");
        case MOD_HYDRAULICS:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S13");
        case MOD_ENGINEBLOCK:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S14");
        case MOD_AIRFILTER:
            if (model == VEHICLE_SULTANRS)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S15b");
            else
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S15");
        case MOD_STRUTS:
            if (model == VEHICLE_SULTANRS || model == VEHICLE_BANSHEE2)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S16b");
            else
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S16");
        case MOD_ARCHCOVER:
            if (model == VEHICLE_SULTANRS)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S17b");
            else
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S17");
        case MOD_AERIALS:
            if (model == VEHICLE_SULTANRS)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S18b");
            else if (model == VEHICLE_BTYPE3)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S18c");
            else
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S18");
        case MOD_TRIM:
            if (model == VEHICLE_SULTANRS)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S19b");
            else if (model == VEHICLE_BTYPE3)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S19c");
            else if (model == VEHICLE_VIRGO2)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S19d");
            else
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S19");
        case MOD_TANK:
            if (model == VEHICLE_SLAMVAN3)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S27");
            else
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S20");
        case MOD_WINDOWS:
            if (model == VEHICLE_BTYPE3)
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S21b");
            else
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S21");
        case MOD_DOORS:
            if (model == VEHICLE_SLAMVAN3)
                return HUD::_GET_LABEL_TEXT("SLVAN3_RDOOR");
            else
                return HUD::_GET_LABEL_TEXT("CMM_MOD_S22");
        case MOD_LIVERY:
            return HUD::_GET_LABEL_TEXT("CMM_MOD_S23");
        default:
            auto name = VEHICLE::GET_MOD_SLOT_NAME(vehicle, mod_slot);
            if (name == nullptr)
                return "";
            if (strstr(name, "_"))
                return HUD::_GET_LABEL_TEXT(name);
            return name;
        }
    }
    const char* game_helper::get_mod_name(int mod, int mod_slot, int mod_count, Vehicle vehicle)
    {
        std::string chrome;
        if (mod_count == 0)
            return "";
        if (mod < -1 || mod >= mod_count)
            return "";
        if (mod_slot == MOD_HORNS)
        {
            if (horn_map.find(mod) != horn_map.end())
            {
                return HUD::_GET_LABEL_TEXT(horn_map.find(mod)->second);
            }
            return "";
        }
        Hash model = ENTITY::GET_ENTITY_MODEL(vehicle);
        if (mod_slot == MOD_FRONTWHEEL || mod_slot == MOD_REARWHEEL)
        {
            if (mod == -1)
            {
                if (!VEHICLE::IS_THIS_MODEL_A_BIKE(model) && VEHICLE::IS_THIS_MODEL_A_BICYCLE(model))
                    return HUD::_GET_LABEL_TEXT("CMOD_WHE_0");
                else
                    return HUD::_GET_LABEL_TEXT("CMOD_WHE_B_0");
            }
            if (mod >= mod_count / 2)
            {
                //return fmt::format("{} {}", HUD::_GET_LABEL_TEXT("CHROME"), HUD::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod))).c_str(); //Bug with FMT library? Returns Chrome Chrome...
                chrome = HUD::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod));
                return chrome.c_str();
            }
            else
            {
                return HUD::_GET_LABEL_TEXT(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod));
            }
        }
        std::string armor;
        std::string brakes;
        std::string engine;
        std::string suspension;
        std::string transmission;

        switch (mod_slot)
        {
        case MOD_ARMOR:
            armor = "CMOD_ARM_" + std::to_string(mod + 1);
            return HUD::_GET_LABEL_TEXT(armor.c_str());
        case MOD_BRAKES:
            brakes = "CMOD_BRA_" + std::to_string(mod + 1);
            return HUD::_GET_LABEL_TEXT(brakes.c_str());
        case MOD_ENGINE:
            if (mod == -1)
                return HUD::_GET_LABEL_TEXT("CMOD_ARM_0");
            engine = "CMOD_ENG_" + std::to_string(mod + 1);
            return HUD::_GET_LABEL_TEXT(engine.c_str());
        case MOD_SUSPENSION:
            suspension = "CMOD_SUS_" + std::to_string(mod + 1);
            return HUD::_GET_LABEL_TEXT(suspension.c_str());
        case MOD_TRANSMISSION:
            transmission = "CMOD_GBX_" + std::to_string(mod + 1);
            return HUD::_GET_LABEL_TEXT(transmission.c_str());
        }
        if (mod > -1)
        {
            if (mod_slot == MOD_SIDESKIRT && VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SIDESKIRT) < 2)
            {
                return HUD::_GET_LABEL_TEXT("CMOD_SKI_1");
            }
            auto label = VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod);
            if (label == nullptr || strlen(label) == 0)
                return "MISSING_LABEL";
            return HUD::_GET_LABEL_TEXT(label);
        }
        else
        {
            switch (mod_slot)
            {
            case MOD_AIRFILTER:
                break;
            case MOD_STRUTS:
                switch (model)
                {
                case VEHICLE_BANSHEE:
                case VEHICLE_BANSHEE2:
                case VEHICLE_SULTANRS:
                    return HUD::_GET_LABEL_TEXT("CMOD_COL5_41");
                }
                break;
            }
            return HUD::_GET_LABEL_TEXT("CMOD_DEF_0");
        }
    }
    void game_helper::get_vehicle_mod()
    {
        if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE))
        {
            if (player_vehicle != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE))
            {
                if (!HUD::HAS_THIS_ADDITIONAL_TEXT_LOADED("MOD_MNU", 10))
                {
                    HUD::CLEAR_ADDITIONAL_TEXT(10, TRUE);
                    HUD::REQUEST_ADDITIONAL_TEXT("MOD_MNU", 10);
                    std::this_thread::yield();
                }

                player_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
                can_tires_burst = !VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(player_vehicle);
                tiresmoke = VEHICLE::IS_TOGGLE_MOD_ON(player_vehicle, MOD_TIRESMOKE);
                turbo = VEHICLE::IS_TOGGLE_MOD_ON(player_vehicle, MOD_TURBO);
                xenon = VEHICLE::IS_TOGGLE_MOD_ON(player_vehicle, MOD_XENONHEADLIGHTS);
                VEHICLE::GET_VEHICLE_COLOURS(player_vehicle, &primary_color, &secondary_color);
                VEHICLE::GET_VEHICLE_EXTRA_COLOURS(player_vehicle, &pearlescent, &wheel_color);
                VEHICLE::_GET_VEHICLE_INTERIOR_COLOR(player_vehicle, &interior_color);
                VEHICLE::_GET_VEHICLE_DASHBOARD_COLOR(player_vehicle, &dashboard_color);
                std::vector<std::string> dsp_names{};
                for (int slot = MOD_SPOILERS; slot <= MOD_LIVERY; slot++)
                {
                    int count = VEHICLE::GET_NUM_VEHICLE_MODS(player_vehicle, slot);
                    if (count > 0)
                    {
                        owned_mods[slot] = (VEHICLE::GET_VEHICLE_MOD(player_vehicle, selected_slot) + 1);
                        dsp_names.push_back(get_mod_slot_name(slot, player_vehicle));
                        std::vector<std::string> names;
                        for (int mod = -1; mod < count; mod++)
                            names.push_back(get_mod_name(mod, slot, count, player_vehicle));
                        mod_display_names[slot] = names;
                    }
                    else
                    {
                        dsp_names.push_back("");
                    }
                }
                slot_display_names = dsp_names;
            }
        }
        else if (!slot_display_names.empty())
        {
            player_vehicle = NULL;
            mod_display_names.clear();
            slot_display_names.clear();
        }
    }
}