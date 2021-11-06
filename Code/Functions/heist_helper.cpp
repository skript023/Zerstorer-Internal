#include "heist_helper.hpp"
#include "../ScriptLocal.hpp"
#include "memory_address.hpp"
#include "systems_helper.hpp"
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
}