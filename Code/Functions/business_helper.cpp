#include "business_helper.hpp"
#include "game_helper.hpp"
#include "../Util.hpp"

namespace big
{
    void business::special_cargo_crates(int crates)
    {
        if (auto crates_cargo = find_script_thread(RAGE_JOAAT("gb_contraband_buy")))
        {
            *script_local(crates_cargo, m_local.special_cargo_buying).at(1).as<int*>() = crates;
            *script_local(crates_cargo, m_local.special_cargo_buying).at(193).as<int*>() = crates;
            *script_local(crates_cargo, m_local.special_cargo_buying).at(6).as<int*>() = 9;
            *script_local(crates_cargo, m_local.special_cargo_buying).at(8).as<int*>() = 4;
            *script_local(crates_cargo, m_local.special_cargo_buying).at(9).as<int*>() = 9;
            *script_local(crates_cargo, m_local.special_cargo_buying).at(7).as<int*>() = 21;
        }
    }

    void business::special_cargo_selling_mission(int money)
    {
        if (auto special_cargo = find_script_thread(RAGE_JOAAT("gb_contraband_sell")))
        {
            int requirement = *script_local(special_cargo, m_local.special_cargo_sell).at(65).as<int*>();
            int cargo = *script_local(special_cargo, m_local.special_cargo_sell).at(55).as<int*>();//54 2 choice
            g_game_helper.tuneable = game_helper::func_799(cargo);
            g_game_helper.temp = *script_global(g_game_helper.tuneable).as<int*>();
            int result = money / cargo;
            if (result == 0) return;
            *script_global(g_game_helper.tuneable).as<int*>() = result;
            *script_local(special_cargo, m_local.special_cargo_sell).at(56).as<int*>() = requirement;
        }
    }

    void business::bunker_selling_mission(int money)
    {
        if (auto bunker_selling = find_script_thread(RAGE_JOAAT("gb_gunrunning")))
        {
            auto money_bunker = *g_GameVariables->m_money_in_bunker;
            if (money_bunker->money_in_bunker == 0) return;

            int kargo = *script_local(bunker_selling, m_local.bunker_sell).at(551).at(1).at(19).as<int*>();
            int data = money / money_bunker->money_in_bunker;
            *script_local(bunker_selling, m_local.bunker_sell).at(816).as<int*>() = kargo;
            *script_global(g_global.bunker_selling_mult_far).as<float*>() = systems::int_to_float(data);
            *script_global(g_global.bunker_selling_mult_near).as<float*>() = systems::int_to_float(data);

            int mission_time_remaining = *script_local(bunker_selling, m_local.bunker_sell_time_remaining).as<int*>();
            int mission_time_delivering = *script_local(bunker_selling, m_local.bunker_sell).at(579).as<int*>();
            int mission_time = mission_time_delivering - (mission_time_remaining - 1000);
            *script_local(bunker_selling, m_local.bunker_sell).at(579).as<int*>() = mission_time;
        }
    }

    void business::biker_selling_mission(int money)
    {
        if (auto mc_selling = find_script_thread(RAGE_JOAAT("gb_biker_contraband_sell")))
        {
            auto money_business = *g_GameVariables->m_money_in_bunker; int money_in_mc = money_business->money_in_bunker;

            if (money_in_mc == 0) return;
            float mc_multiplier = systems::int_to_float(money / money_in_mc);

            g_Logger->Info("Money : %f", mc_multiplier);

            *script_global(g_global.mc_sell_mult_far).as<float*>() = mc_multiplier;
            *script_global(g_global.mc_sell_mult_near).as<float*>() = mc_multiplier;
            int requirement = *script_local(mc_selling, m_local.mc_sell).at(143).as<int*>();
            *script_local(mc_selling, m_local.mc_sell).at(122).as<int*>() = requirement;

        }
    }

    void business::add_meth_supply(Player player, int supply)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 1:
            case 6:
            case 11:
            case 16:
                *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(2).as<int*>() = supply;
            }
        }
    }

    void business::add_weed_supply(Player player, int supply)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(2).as<int*>() = supply;
            }
        }
    }

    void business::add_cocain_supply(Player player, int supply)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(2).as<int*>() = supply;
            }
        }
    }

    void business::add_cash_supply(Player player, int supply)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(2).as<int*>() = supply;
            }
        }
    }

    void business::add_document_supply(Player player, int supply)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(2).as<int*>() = supply;
            }
        }
    }

    void business::add_bunker_supply(Player player, int supply)
    {
        if (*g_GameVariables->m_is_session_started)
        {
            *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(2).as<int*>() = supply;
        }
    }

    float business::get_meth_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 1:
            case 6:
            case 11:
            case 16:
                return systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(3).as<int*>());
            }
        }
        return 0.f;
    }

    float business::get_weed_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                return systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(3).as<int*>());
            }
        }
        return 0.f;
    }

    float business::get_cocain_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                return systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(3).as<int*>());
            }
        }
        return 0.f;
    }

    float business::get_cash_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                return systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(3).as<int*>());
            }
        }
        return 0.f;
    }

    float business::get_document_supply(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                return systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(3).as<int*>());
            }
        }
        return 0.f;
    }

    float business::get_bunker_supply(Player player)
    {
        if (*g_GameVariables->m_is_session_started)
        {
            return systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(2).as<int*>());
        }
        return 0.f;
    }

    float business::get_meth_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 1:
            case 6:
            case 11:
            case 16:
                float product = systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(1).as<int*>());
                return (product / 20.f) * 100.f;
            }
        }
        return 0.f;
    }

    float business::get_weed_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                float product = systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(1).as<int*>());
                return (product / 80.f) * 100.f;
            }
        }
        return 0.f;
    }

    float business::get_cocain_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                float product = systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(1).as<int*>());
                return (product / 10.f) * 100.f;
            }
        }
        return 0.f;
    }

    float business::get_cash_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                float product = systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(1).as<int*>());
                return (product / 40.f) * 100.f;
            }
        }
        return 0.f;
    }

    float business::get_document_stock(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                float product = systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).at(1).as<int*>());
                return (product / 60.f) * 100.f;
            }
        }
        return 0.f;
    }

    float business::get_bunker_stock(Player player)
    {
        if (*g_GameVariables->m_is_session_started)
        {
            return systems::int_to_float(*script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(1).as<int*>());
        }
        return 0.f;
    }

    float business::get_research_progress(Player player)
    {
        if (*g_GameVariables->m_is_session_started)
        {
            auto research_progress = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(12).as<int*>();
            auto research_percentages = (systems::int_to_float(research_progress) / 60.f) * 100.f;
            return research_percentages;
        }
        return 0.0f;
    }

    const char* business::get_meth_location(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 1:
                return "Paleto Bay";
            case 6:
                return "El Burro Heights";
            case 11:
                return "Grand Senora Desert";
            case 16:
                return "Terminal";
            }
        }
        return "No Data";
    }

    const char* business::get_weed_location(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 2:
                return "Mount Chiliad";
            case 7:
                return "Downtown Vinewood";
            case 12:
                return "San Chianski";
            case 17:
                return "Elysian Island";
            }
        }
        return "No Data";
    }

    const char* business::get_cocain_location(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 3:
                return "Paleto Bay";
            case 8:
                return "Morningwood";
            case 13:
                return "Alamo Sea";
            case 18:
                return "Elysian Island";
            }
        }
        return "No Data";
    }

    const char* business::get_cash_location(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 4:
                return "Paleto Bay";
            case 9:
                return "Vespucci Canals";
            case 14:
                return "Grand Senora Desert";
            case 19:
                return "Cypress Flats";
            }
        }
        return "No Data";
    }

    const char* business::get_document_location(Player player)
    {
        for (int i = 0; i <= 4; i++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(i, 12).as<int*>();
            switch (location)
            {
            case 5:
                return "Paleto Bay";
            case 10:
                return "Textile City";
            case 15:
                return "Grapeseed";
            case 20:
                return "Elysian Island";
            }
        }
        return "No Data";
    }

    const char* business::get_bunker_location(Player player)
    {
        auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).as<int*>();

        switch (location)
        {
        case 23:
            return "Route86";
        case 24:
            return "Farmhouse";
        case 25:
            return "Smoke Tree Road";
        case 26:
            return "Thomson Scrapyard";
        case 27:
            return "Grapeseed";
        case 28:
            return "Paleto Forest";
        case 29:
            return "Ranton Canyon";
        case 30:
            return "Lago Zancudo";
        case 31:
            return "Chumash";
        }
        return "No Data";
    }

    void business::trigger_meth_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 1:
            case 6:
            case 11:
            case 16:
                int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 20) message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Meth Production Function: Storage full with 20 Products!", "~bold~~g~Ellohim Business Manager");
                if (supply > 0)
                    *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Meth Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
                break;
            }
        }
    }

    void business::trigger_weed_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 2:
            case 7:
            case 12:
            case 17:
                int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 80) message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Weed Production Function: Storage full with 80 Products!", "~bold~~g~Ellohim Business Manager");
                if (supply > 0)
                    *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Weed Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
                break;
            }
        }
    }

    void business::trigger_cocain_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 3:
            case 8:
            case 13:
            case 18:
                int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 10) message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Cocaine Production Function: Storage full with 10 Products!", "~bold~~g~Ellohim Business Manager");
                if (supply > 0)
                    *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Cocaine Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
                break;
            }
        }
    }

    void business::trigger_cash_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 4:
            case 9:
            case 14:
            case 19:
                int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 40) message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Cash Production Function: Storage full with 40 Products!", "~bold~~g~Ellohim Business Manager");
                if (supply > 0)
                    *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Cash Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
                break;
            }
        }
    }

    void business::trigger_document_production(Player player)
    {
        for (int a = 0; a <= 4; a++)
        {
            auto location = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).as<int*>();
            switch (location)
            {
            case 5:
            case 10:
            case 15:
            case 20:
                int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(2).as<int*>();
                int product = *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(1).as<int*>();
                if (product == 60) message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Documents Production Function: Storage full with 60 Products!", "~bold~~g~Ellohim Business Manager");
                if (supply > 0)
                    *script_global(1590908).at(player, 874).at(267).at(185).at(a, 12).at(9).as<int*>() = 0;
                else
                    message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Documents Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
                break;
            }
        }
    }

    void business::trigger_bunker_production(Player player)
    {
        int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(2).as<int*>();
        int product = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(1).as<int*>();
        if (product == 100) message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Bunker Production Function: Full Stock!", "~bold~~g~Ellohim Business Manager");
        if (supply > 0)
            *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(9).as<int*>() = 0;
        else
            message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Bunker Production Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
    }

    void business::trigger_bunker_research(Player player)
    {
        int supply = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(2).as<int*>();
        int product = *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(1).as<int*>();
        if (product == 60) message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Bunker Research Function: Research Progress Done!", "~bold~~g~Ellohim Business Manager");
        if (supply > 0)
            *script_global(1590908).at(player, 874).at(267).at(185).at(5, 12).at(13).as<int*>() = 0;
        else
            message::notification("~bold~~g~Ellohim Private Menu", "~bold~~g~Trigger Bunker Research Function: Supplies are empty! Buy Supplies!", "~bold~~g~Ellohim Business Manager");
    }

    void business::trigger_nightclub_production()
    {
        for (int i = 0; i < 4; i++)
        {
            if (*script_global(g_global.nc_trigger_product).at(i, 2).at(1).as<int*>() == 1)
            {
                *script_global(g_global.nc_trigger_product).at(i, 2).as<int*>() = 0;//2515749
            }
        }
    }
}