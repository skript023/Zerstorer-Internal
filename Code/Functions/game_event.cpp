#include "game_event.hpp"
#include "game_variable.hpp"
#include "../Classes/Enum.hpp"
#include "game_helper.hpp"

namespace big
{
    void remote_event::take_all_cayo(int take)
    {
        int64_t cayo_take[] = { TAKE_CAYO, PLAYER::PLAYER_ID(), take, 1 };
        for (int i = 0; i <= NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS(); i++)
        {
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, cayo_take, 4, 1 << i);
            std::this_thread::yield();
        }
    }

    void remote_event::take_all_casino(int take)
    {
        *script_global(4456448).at(85976).as<int*>() = 32;
        *script_global(g_global.casino_take_indicator).as<int*>() = 1;
        *script_global(g_global.pasific_standard).as<int*>() = take;
        std::this_thread::sleep_for(1500ms);
        int64_t casino_take[] = { TAKE_PASIFIC, PLAYER::PLAYER_ID(), *script_global(g_global.pasific_standard).as<int*>(), 1, 1, 0, 0, 0 };
        for (int i = 0; i <= NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS(); i++)
        {
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, casino_take, 8, 1 << i);
            std::this_thread::yield();
        }
        std::this_thread::sleep_for(2000ms);
        *script_global(g_global.pasific_standard).as<int*>() = 1000000;
    }

    void remote_event::take_casino_partial(int take)
    {
        *script_global(g_global.artwork).as<int*>() = (take * 100) / 18;
        std::this_thread::sleep_for(1500ms);
        int64_t casino_take[] = { TAKE_CASINO, PLAYER::PLAYER_ID(), 5, 1 };
        for (int i = 0; i <= NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS(); i++)
        {
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, casino_take, 4, 1 << i);
            std::this_thread::yield();
        }
        *script_global(g_global.artwork).as<int*>() = 2350000;
    }
    /*
    void remote_event::give_wanted_level(Player player)
    {
        Vector3 coordinate = { 0.0f, 0.0f, 0.0f };
        controller::CreatePed(RAGE_JOAAT("s_m_y_swat_01"), coordinate, 3, TRUE);
        *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0xE990;
        *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x9090;
        FIRE::ADD_OWNED_EXPLOSION(player, coordinate.x, coordinate.y, coordinate.z, EXPLOSION_TRAIN, 1000.0f, TRUE, FALSE, 2.0f);
        *(PWORD)g_pointers->m_add_owned_explosion_bypass_1 = 0x850F;
        *(PWORD)g_pointers->m_add_owned_explosion_bypass_2 = 0x0E74;
    }
    */
    void remote_event::steal_fake_money(Player player, int TotalMoney)
    {
        int64_t steal_money[4] = { FAKE_MONEY, PLAYER::PLAYER_ID(), FAKE_STEAL, TotalMoney };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, steal_money, 9, 1 << player);
    }

    void remote_event::remove_fake_money(Player player, int TotalMoney)
    {
        int64_t remove_money[4] = { FAKE_MONEY, PLAYER::PLAYER_ID(), FAKE_REMOVE, TotalMoney };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, remove_money, 9, 1 << player);
    }

    void remote_event::give_fake_money(Player player, int TotalMoney)
    {
        int64_t banked_money[4] = { FAKE_MONEY, PLAYER::PLAYER_ID(), FAKE_BANKED, TotalMoney };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, banked_money, 9, 1 << player);
    }

    void remote_event::send_to_mission(Player player)
    {
        int64_t send_to_mission_1[9] = { SEND_TO_MISSION_1, PLAYER::PLAYER_ID(), 0, 0, 0, -1, 1, 1, 0 };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, send_to_mission_1, 9, 1 << player);

        int64_t send_to_mission_2[9] = { SEND_TO_MISSION_2, PLAYER::PLAYER_ID(), 0, 0, 0, -1, 1, 1, 0 };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, send_to_mission_2, 9, 1 << player);
    }

    void remote_event::transaction_fail(Player player)
    {
        int64_t trans_fail[8] = { TRANSACTION_ERROR, PLAYER::PLAYER_ID(), 10000, 0, 0, *script_global(1630816).at(player,597).at(508).as<int64_t*>(), *script_global(1658176).at(9).as<int64_t*>(), *script_global(1658176).at(9).as<int64_t*>() };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, trans_fail, 8, 1 << player);
    }

    void remote_event::kick_player(Player player)
    {
        for (int64_t KickEvent : var::KickHash)
        {
            int64_t kick[2] = { KickEvent, PLAYER::PLAYER_ID() };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, kick, 2, 1 << player);
        }
    }

    void remote_event::clear_wanted(Player player)
    {
        int64_t clear_wanted[3] = { CLEAR_WANTED, PLAYER::PLAYER_ID(), *script_global(1630816).at(player, 597).at(508).as<int*>() };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, clear_wanted, 3, 1 << player);
    }

    void remote_event::vehicle_kick(Player player)
    {
        int64_t vehicle_kick[2] = { VEHICLE_KICK, PLAYER::PLAYER_ID() };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, vehicle_kick, 2, 1 << player);
    }

    void remote_event::rotate_cam(Player player)
    {
        int64_t rotate_cam[3] = { ROTATE_CAM, PLAYER::PLAYER_ID(), -1952943290 };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, rotate_cam, 3, 1 << player);
    }

    void remote_event::ceo_ban(Player player)
    {
        int64_t ceo_ban[4] = { CEO_BAN , PLAYER::PLAYER_ID(), 1, 5 };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, ceo_ban, 4, 1 << player);
    }

    void remote_event::ceo_kick(Player player)
    {
        int64_t ceo_kick[4] = { CEO_KICK , PLAYER::PLAYER_ID(), 1, 5 };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, ceo_kick, 4, 1 << player);
    }

    void remote_event::force_invite_apartment(Player player)
    {
        int64_t invite_apartment[9] = { TELEPORT_APARTMENT, PLAYER::PLAYER_ID(), 1, -1, 1, 12728, 0, 1, 0 };//uint64_t args[9] = { 1097312011 , player, 1, -1, 1, 12728, 0, 1, 0 };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, invite_apartment, 9, 1 << player);//uint64_t soundspam[4] = { 1097312011, player, 0, 0 }; sound spam
    }

    void remote_event::teleport_player_to_cayo(Player player)
    {
        int64_t send_to_cayo[2] = { TELEPORT_CAYO , PLAYER::PLAYER_ID() };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, send_to_cayo, 2, 1 << player);
    }
    /*
    void remote_event::revenge_kick(bool Activation)
    {
        if (Activation)
        {
            rage::CPedInterface* ped_interface = g_pointers->m_replay_interface->m_ped_interface;
            for (int i = 0; i < ped_interface->m_max_peds; i++)
            {
                auto* ped_ptr = ped_interface->get_ped(i);
                if (ped_ptr == nullptr)
                    continue;

                Ped ped = g_pointers->m_ptr_to_handle(ped_ptr);
                if (ped == 0)
                    break;

                Player player = NETWORK::NETWORK_GET_PLAYER_INDEX_FROM_PED(ped);
                if (PED::IS_PED_A_PLAYER(ped))
                {
                    if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(g_local.InVehicle ? PLAYER::PLAYER_ID()Vehicle : g_local.ped, ped, TRUE) && WEAPON::HAS_ENTITY_BEEN_DAMAGED_BY_WEAPON(g_local.InVehicle ? PLAYER::PLAYER_ID()Vehicle : g_local.ped, 0, 2))
                    {
                        int64_t bail_event[3] = { 2092565704, PLAYER::PLAYER_ID(), *script_global(1630816).at(player, 597).at(508).as<int64_t*>() };
                        SCRIPT::TRIGGER_SCRIPT_EVENT(1, bail_event, 3, 1 << player);
                        controller::ShowMessage(fmt::format("~g~Hash Sent Kick To {}", PLAYER::GET_PLAYER_NAME(player)).c_str(), false);
                    }
                }
            }
        }
    }

    void remote_event::get_name_from_event_hash(int32_t hash)
    {

    }
    */
    
    void remote_event::bail_player(Player player)
    {
        int64_t bail_event[3] = { 2092565704, PLAYER::PLAYER_ID(), *script_global(1630816).at(player, 597).at(508).as<int64_t*>() };
        SCRIPT::TRIGGER_SCRIPT_EVENT(1, bail_event, 3, 1 << player);
    }
    /*
    bool script_helper::is_script_active(Hash ScriptHash)
    {
        return rage_helper::find_script_thread(ScriptHash) != nullptr;
    }
    */
    void remote_event::off_the_radar(Player player, bool toggle)
    {
        if (toggle)
        {
            int64_t args[7] = { -397188359, PLAYER::PLAYER_ID(), *script_global(2441237).at(70).as<int*>(), NETWORK::GET_NETWORK_TIME(), 1, 1, *script_global(1630816).at(player, 597).at(508).as<int*>() };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 7, 1 << player);
            *script_global(2426865).at(player, 449).at(209).as<bool*>() = toggle;
        }
    }

    void remote_event::bribe_authority(Player player, bool toggle)
    {
        if (toggle)
        {
            int64_t args[7] = { -151720011, PLAYER::PLAYER_ID(), 0, *script_global(2544210).at(4625).as<int*>(), NETWORK::GET_NETWORK_TIME(), 1, *script_global(1630816).at(player, 597).at(508).as<int*>() };
            SCRIPT::TRIGGER_SCRIPT_EVENT(1, args, 7, 1 << player);
            *script_global(2544210).at(4623).as<bool*>() = toggle;
        }
    }
}