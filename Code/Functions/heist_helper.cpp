#include "heist_helper.hpp"
#include "../ScriptLocal.hpp"
#include "game_helper.hpp"
#include "game_event.hpp"


namespace big
{
    void casino_heist::all_heist_take(int Take)
    {
        if (auto casino = find_script_thread(RAGE_JOAAT("fm_mission_controller")))
        {
            *script_local(casino, m_local.take_casino).as<int*>() = Take;
        }
        if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller_2020")))
        {
            remote_event::take_all_cayo(Take);
        }
    }

    void casino_heist::remove_crew_heist(bool Activation)
    {
        if (Activation)
        {
            if (systems::is_script_active(RAGE_JOAAT("fm_mission_controller")))
            {
                *script_global(g_global.casino_stat).at(PLAYER::PLAYER_ID(), 68).at(18).at(14).as<int*>() = 6;
                *script_global(g_global.casino_stat).at(PLAYER::PLAYER_ID(), 68).at(18).at(12).as<int*>() = 6;
                *script_global(g_global.casino_stat).at(PLAYER::PLAYER_ID(), 68).at(18).at(10).as<int*>() = 6;
            }
        }
    }

    void casino_heist::auto_heist_cut(bool Activate)
    {
        if (Activate)
        {
            if (systems::is_script_active(RAGE_JOAAT("gb_casino_heist_planning")))
            {
                if (*script_global(g_global.casino_cut_1).as<int*>() >= 15 && *script_global(g_global.casino_cut_1).as<int*>() < 85)
                {
                    *script_global(g_global.casino_cut_1).as<int*>() = 85;
                }
                else if (*script_global(g_global.casino_cut_2).as<int*>() >= 15 && *script_global(g_global.casino_cut_2).as<int*>() < 85)
                {
                    *script_global(g_global.casino_cut_2).as<int*>() = 85;
                }
                else if (*script_global(g_global.casino_cut_3).as<int*>() >= 15 && *script_global(g_global.casino_cut_3).as<int*>() < 85)
                {
                    *script_global(g_global.casino_cut_3).as<int*>() = 85;
                }
                else if (*script_global(g_global.casino_cut_4).as<int*>() >= 15 && *script_global(g_global.casino_cut_4).as<int*>() < 85)
                {
                    *script_global(g_global.casino_cut_4).as<int*>() = 85;
                }
            }

            if (systems::is_script_active(RAGE_JOAAT("gb_gang_ops_planning")))
            {
                if (*script_global(g_global.doomsday_cut_1).as<int*>() >= 15 && *script_global(g_global.doomsday_cut_1).as<int*>() < 85)
                {
                    *script_global(g_global.doomsday_cut_1).as<int*>() = 85;
                }
                else if (*script_global(g_global.doomsday_cut_2).as<int*>() >= 15 && *script_global(g_global.doomsday_cut_2).as<int*>() < 85)
                {
                    *script_global(g_global.doomsday_cut_2).as<int*>() = 85;
                }
                else if (*script_global(g_global.doomsday_cut_3).as<int*>() >= 15 && *script_global(g_global.doomsday_cut_3).as<int*>() < 85)
                {
                    *script_global(g_global.doomsday_cut_3).as<int*>() = 85;
                }
                else if (*script_global(g_global.doomsday_cut_4).as<int*>() >= 15 && *script_global(g_global.doomsday_cut_4).as<int*>() < 85)
                {
                    *script_global(g_global.doomsday_cut_4).as<int*>() = 85;
                }
            }

            if (systems::is_script_active(RAGE_JOAAT("fmmc_launcher")))
            {
                if (*script_global(g_global.apartmen_cut_1).as<int*>() >= 15 && *script_global(g_global.apartmen_cut_1).as<int*>() < 85)
                {
                    *script_global(g_global.apartmen_cut_1).as<int*>() = 85;
                }
                else if (*script_global(g_global.apartmen_cut_2).as<int*>() >= 15 && *script_global(g_global.apartmen_cut_2).as<int*>() < 85)
                {
                    *script_global(g_global.apartmen_cut_2).as<int*>() = 85;
                }
                else if (*script_global(g_global.apartmen_cut_3).as<int*>() >= 15 && *script_global(g_global.apartmen_cut_3).as<int*>() < 85)
                {
                    *script_global(1666211).at(3008).at(3).as<int*>() = 85;
                }
                else if (*script_global(g_global.apartmen_cut_4).as<int*>() >= 15 && *script_global(g_global.apartmen_cut_4).as<int*>() < 85)
                {
                    *script_global(g_global.apartmen_cut_4).as<int*>() = 85;
                }
            }

            if (systems::is_script_active(RAGE_JOAAT("heist_island_planning")))
            {
                if (*script_global(g_global.cayo_cut_1).as<int*>() >= 15 && *script_global(g_global.cayo_cut_1).as<int*>() < 85)
                {
                    *script_global(g_global.cayo_cut_1).as<int*>() = 85;
                }
                else if (*script_global(g_global.cayo_cut_2).as<int*>() >= 15 && *script_global(g_global.cayo_cut_2).as<int*>() < 85)
                {
                    *script_global(g_global.cayo_cut_2).as<int*>() = 85;
                }
                else if (*script_global(g_global.cayo_cut_3).as<int*>() >= 15 && *script_global(g_global.cayo_cut_3).as<int*>() < 85)
                {
                    *script_global(g_global.cayo_cut_3).as<int*>() = 85;
                }
                else if (*script_global(g_global.cayo_cut_4).as<int*>() >= 15 && *script_global(g_global.cayo_cut_4).as<int*>() < 85)
                {
                    *script_global(g_global.cayo_cut_4).as<int*>() = 85;
                }
            }
            *script_global(g_global.real_player_cut).as<int*>() = 85;
        }
    }

    void casino_heist::heist_crew_cut_zero(bool Activation)
    {
        if (Activation)
        {
            *script_global(g_global.ch_gunman.karl_cut).as<int*>() = 0;
            *script_global(g_global.ch_gunman.gustavo_cut).as<int*>() = 0;
            *script_global(g_global.ch_gunman.charlie_cut).as<int*>() = 0;
            *script_global(g_global.ch_gunman.chester_cut).as<int*>() = 0;
            *script_global(g_global.ch_gunman.packie_cut).as<int*>() = 0;
            *script_global(g_global.ch_hacker.rickie_cut).as<int*>() = 0;
            *script_global(g_global.ch_hacker.christian_cut).as<int*>() = 0;
            *script_global(g_global.ch_hacker.yohan_cut).as<int*>() = 0;
            *script_global(g_global.ch_hacker.avi_cut).as<int*>() = 0;
            *script_global(g_global.ch_hacker.paige_cut).as<int*>() = 0;
            *script_global(g_global.ch_driver.karim_cut).as<int*>() = 0;
            *script_global(g_global.ch_driver.taliana_cut).as<int*>() = 0;
            *script_global(g_global.ch_driver.eddie_cut).as<int*>() = 0;
            *script_global(g_global.ch_driver.zach_cut).as<int*>() = 0;
            *script_global(g_global.ch_driver.chester_cut).as<int*>() = 0;
            *script_global(g_global.real_player_cut).as<int*>() = 85;
        }
        else
        {
            *script_global(g_global.ch_gunman.karl_cut).as<int*>() = 5;
            *script_global(g_global.ch_gunman.gustavo_cut).as<int*>() = 9;
            *script_global(g_global.ch_gunman.charlie_cut).as<int*>() = 7;
            *script_global(g_global.ch_gunman.chester_cut).as<int*>() = 10;
            *script_global(g_global.ch_gunman.packie_cut).as<int*>() = 8;
            *script_global(g_global.ch_hacker.rickie_cut).as<int*>() = 3;
            *script_global(g_global.ch_hacker.christian_cut).as<int*>() = 7;
            *script_global(g_global.ch_hacker.yohan_cut).as<int*>() = 5;
            *script_global(g_global.ch_hacker.avi_cut).as<int*>() = 10;
            *script_global(g_global.ch_hacker.paige_cut).as<int*>() = 9;
            *script_global(g_global.ch_driver.karim_cut).as<int*>() = 5;
            *script_global(g_global.ch_driver.taliana_cut).as<int*>() = 7;
            *script_global(g_global.ch_driver.eddie_cut).as<int*>() = 9;
            *script_global(g_global.ch_driver.zach_cut).as<int*>() = 6;
            *script_global(g_global.ch_driver.chester_cut).as<int*>() = 10;
        }
    }





}