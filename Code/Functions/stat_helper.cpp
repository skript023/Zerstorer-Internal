#include "stat_helper.hpp"
#include "systems_helper.hpp"

namespace big
{
    void stats::player_kill_death_ratio(float ratio)
    {
        int kill{};
        
        STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_KILLS_PLAYERS"), &kill, -1);
        
        auto total_kill = kill * ratio;
        auto total_death = total_kill / ratio;

        STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_KILLS_PLAYERS"), systems::float_to_int(total_kill), TRUE);
        STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_DEATHS_PLAYER"), systems::float_to_int(total_death), TRUE);
    }

	void stats::unlock_bunker_research(bool activate)
	{
		int character_slot = *script_global(1312763).as<int*>();
		for (int i = 15381; i <= 15499; i++)
		{
			STATS::STAT_SET_BOOL_MASKED(STATS::_GET_NGSTAT_BOOL_HASH((i - 15369), 0, 1, character_slot, "_DLCGUNPSTAT_BOOL"), activate, ((i - 15369) - STATS::_STAT_GET_PACKED_BOOL_MASK((i - 15369)) * 64), TRUE);
		}
	}

    int stats::packed_stat_mask(int iParam0)
    {
        int iVar0;

        iVar0 = 0;
        if (iParam0 >= 384 && iParam0 < 457)
        {
            iVar0 = ((iParam0 - 384) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 384)) * 8) * 8;
        }
        else if (iParam0 >= 457 && iParam0 < 513)
        {
            iVar0 = ((iParam0 - 457) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 457)) * 8) * 8;
        }
        else if (iParam0 >= 1281 && iParam0 < 1305)
        {
            iVar0 = ((iParam0 - 1281) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 1281)) * 8) * 8;
        }
        else if (iParam0 >= 1305 && iParam0 < 1361)
        {
            iVar0 = ((iParam0 - 1305) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 1305)) * 8) * 8;
        }
        else if (iParam0 >= 1361 && iParam0 < 1393)
        {
            iVar0 = ((iParam0 - 1361) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 1361)) * 8) * 8;
        }
        else if (iParam0 >= 1393 && iParam0 < 2919)
        {
            iVar0 = ((iParam0 - 1393) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 1393)) * 8) * 8;
        }
        else if (iParam0 >= 4143 && iParam0 < 4207)
        {
            iVar0 = ((iParam0 - 4143) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 4143)) * 8) * 8;
        }
        else if (iParam0 >= 3879 && iParam0 < 4143)
        {
            iVar0 = ((iParam0 - 3879) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 3879)) * 8) * 8;
        }
        else if (iParam0 >= 4399 && iParam0 < 6028)
        {
            iVar0 = ((iParam0 - 4399) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 4399)) * 8) * 8;
        }
        else if (iParam0 >= 6413 && iParam0 < 7262)
        {
            iVar0 = ((iParam0 - 6413) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 6413)) * 8) * 8;
        }
        else if (iParam0 >= 7262 && iParam0 < 7313)
        {
            iVar0 = ((iParam0 - 7262) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 7262)) * 8) * 8;
        }
        else if (iParam0 >= 7681 && iParam0 < 9361)
        {
            iVar0 = ((iParam0 - 7681) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 7681)) * 8) * 8;
        }
        else if (iParam0 >= 9553 && iParam0 < 15265)
        {
            iVar0 = ((iParam0 - 9553) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 9553)) * 8) * 8;
        }
        else if (iParam0 >= 15265 && iParam0 < 15369)
        {
            iVar0 = ((iParam0 - 15265) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 15265)) * 8) * 8;
        }
        else if (iParam0 >= 7313 && iParam0 < 7321)
        {
            iVar0 = ((iParam0 - 7313) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 7313)) * 8) * 8;
        }
        else if (iParam0 >= 7641 && iParam0 < 7681)
        {
            iVar0 = ((iParam0 - 7641) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 7641)) * 8) * 8;
        }
        else if (iParam0 >= 16010 && iParam0 < 18098)
        {
            iVar0 = ((iParam0 - 16010) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 16010)) * 8) * 8;
        }
        else if (iParam0 >= 18162 && iParam0 < 19018)
        {
            iVar0 = ((iParam0 - 18162) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 18162)) * 8) * 8;
        }
        else if (iParam0 >= 19018 && iParam0 < 22066)
        {
            iVar0 = ((iParam0 - 19018) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 19018)) * 8) * 8;
        }
        else if (iParam0 >= 22194 && iParam0 < 24962)
        {
            iVar0 = ((iParam0 - 22194) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 22194)) * 8) * 8;
        }
        else if (iParam0 >= 25538 && iParam0 < 26810)
        {
            iVar0 = ((iParam0 - 25538) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 25538)) * 8) * 8;
        }
        else if (iParam0 >= 27258 && iParam0 < 28098)
        {
            iVar0 = ((iParam0 - 27258) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 27258)) * 8) * 8;
        }
        else if (iParam0 >= 28483 && iParam0 < 30227)
        {
            iVar0 = ((iParam0 - 28483) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 28483)) * 8) * 8;
        }
        else if (iParam0 >= 30483 && iParam0 < 30515)
        {
            iVar0 = ((iParam0 - 30483) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 30483)) * 8) * 8;
        }
        else if (iParam0 >= 30707 && iParam0 < 31707)
        {
            iVar0 = ((iParam0 - 30707) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 30707)) * 8) * 8;
        }
        return iVar0;
    }

    int stats::packed_stat_name(int iParam0, int iParam1)
    {
        int iVar0;

        if (iParam1 == -1)
        {
            iParam1 = *script_global(1312763).as<int*>();
        }
        iVar0 = 0;
        if (iParam0 >= 384 && iParam0 < 457)
        {
            iVar0 = STATS::GET_PACKED_INT_STAT_KEY((iParam0 - 384), false, true, iParam1);
        }
        else if (iParam0 >= 457 && iParam0 < 513)
        {
            iVar0 = STATS::GET_PACKED_INT_STAT_KEY((iParam0 - 457), true, true, iParam1);
        }
        else if (iParam0 >= 1281 && iParam0 < 1305)
        {
            iVar0 = STATS::GET_PACKED_INT_STAT_KEY((iParam0 - 1281), false, false, 0);
        }
        else if (iParam0 >= 1305 && iParam0 < 1361)
        {
            iVar0 = STATS::GET_PACKED_INT_STAT_KEY((iParam0 - 1305), true, false, 0);
        }
        else if (iParam0 >= 1361 && iParam0 < 1393)
        {
            iVar0 = STATS::_GET_PACKED_TITLE_UPDATE_INT_STAT_KEY((iParam0 - 1361), false, false, 0);
        }
        else if (iParam0 >= 1393 && iParam0 < 2919)
        {
            iVar0 = STATS::_GET_PACKED_TITLE_UPDATE_INT_STAT_KEY((iParam0 - 1393), false, true, iParam1);
        }
        else if (iParam0 >= 4143 && iParam0 < 4207)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 4143), false, false, 0, "_NGPSTAT_INT");
        }
        else if (iParam0 >= 3879 && iParam0 < 4143)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 3879), false, true, iParam1, "_NGPSTAT_INT");
        }
        else if (iParam0 >= 4399 && iParam0 < 6028)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 4399), false, true, iParam1, "_LRPSTAT_INT");
        }
        else if (iParam0 >= 6413 && iParam0 < 7262)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 6413), false, true, iParam1, "_APAPSTAT_INT");
        }
        else if (iParam0 >= 7262 && iParam0 < 7313)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 7262), false, true, iParam1, "_LR2PSTAT_INT");
        }
        else if (iParam0 >= 7681 && iParam0 < 9361)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 7681), false, true, iParam1, "_BIKEPSTAT_INT");
        }
        else if (iParam0 >= 9553 && iParam0 < 15265)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 9553), false, true, iParam1, "_IMPEXPPSTAT_INT");
        }
        else if (iParam0 >= 15265 && iParam0 < 15369)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 15265), false, true, iParam1, "_GUNRPSTAT_INT");
        }
        else if (iParam0 >= 7313 && iParam0 < 7321)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 7313), false, false, 0, "_NGDLCPSTAT_INT");
        }
        else if (iParam0 >= 7641 && iParam0 < 7681)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 7641), false, true, iParam1, "_NGDLCPSTAT_INT");
        }
        else if (iParam0 >= 16010 && iParam0 < 18098)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 16010), false, true, iParam1, "_DLCSMUGCHARPSTAT_INT");
        }
        else if (iParam0 >= 18162 && iParam0 < 19018)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 18162), false, true, iParam1, "_GANGOPSPSTAT_INT");
        }
        else if (iParam0 >= 19018 && iParam0 < 22066)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 19018), false, true, iParam1, "_BUSINESSBATPSTAT_INT");
        }
        else if (iParam0 >= 22194 && iParam0 < 24962)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 22194), false, true, iParam1, "_ARENAWARSPSTAT_INT");
        }
        else if (iParam0 >= 25538 && iParam0 < 26810)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 25538), false, true, iParam1, "_CASINOPSTAT_INT");
        }
        else if (iParam0 >= 27258 && iParam0 < 28098)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 27258), false, true, iParam1, "_CASINOHSTPSTAT_INT");
        }
        else if (iParam0 >= 28483 && iParam0 < 30227)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 28483), false, true, iParam1, "_SU20PSTAT_INT");
        }
        else if (iParam0 >= 30483 && iParam0 < 30515)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 30483), false, true, iParam1, "_HISLANDPSTAT_INT");
        }
        else if (iParam0 >= 30707 && iParam0 < 31707)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 30707), false, true, iParam1, "_TUNERPSTAT_INT");
        }
        return iVar0;
    }

    std::string stats::packed_reversed(uint32_t hash)
    {
        auto X = std::to_string(*script_global(1312763).as<int*>());
        std::string result;
        for (int i = 0; i <= 5; i++)//708
        {
            auto index = std::to_string(i);

            if (joaat("MP" + X + "_TUNERPSTAT_INT" + index) == hash && i <= 124)
            {
                result = "MP" + X + "_TUNERPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_HISLANDPSTAT_INT" + index) == hash && i <= 3)
            {
                result = "MP" + X + "_HISLANDPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_SU20PSTAT_INT" + index) == hash && i <= 217)
            {
                result = "MP" + X + "_SU20PSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_CASINOPSTAT_INT" + index) == hash && i <= 158)
            {
                result = "MP" + X + "_CASINOPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_CASINOHSTPSTAT_INT" + index) == hash && i <= 104)
            {
                result = "MP" + X + "_CASINOHSTPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_ARENAWARSPSTAT_INT" + index) == hash && i <= 345)
            {
                result = "MP" + X + "_ARENAWARSPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_BUSINESSBATPSTAT_INT" + index) == hash && i <= 380)
            {
                result = "MP" + X + "_BUSINESSBATPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_GANGOPSPSTAT_INT" + index) == hash && i <= 106)
            {
                result = "MP" + X + "_GANGOPSPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_DLCSMUGCHARPSTAT_INT" + index) == hash && i <= 260)
            {
                result = "MP" + X + "_DLCSMUGCHARPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_GUNRPSTAT_INT" + index) == hash && i <= 12)
            {
                result = "MP" + X + "_GUNRPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_IMPEXPPSTAT_INT" + index) == hash && i <= 708)
            {
                result = "MP" + X + "_IMPEXPPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_BIKEPSTAT_INT" + index) == hash && i <= 210)
            {
                result = "MP" + X + "_BIKEPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_LR2PSTAT_INT" + index) == hash && i <= 6)
            {
                result = "MP" + X + "_LR2PSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_APAPSTAT_INT" + index) == hash && i <= 107)
            {
                result = "MP" + X + "_APAPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_LRPSTAT_INT" + index) == hash && i <= 203)
            {
                result = "MP" + X + "_LRPSTAT_INT" + index;
            }
            else if (joaat("MP_NGPSTAT_INT" + index) == hash && i <= 1)
            {
                result = "MP_NGPSTAT_INT" + index;
            }
            else if (joaat("MP_TUPSTAT_INT" + index) == hash && i <= 3)
            {
                result = "MP_TUPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_TUPSTAT_INT" + index) == hash && i <= 191)
            {
                result = "MP" + X + "_TUPSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_PSTAT_INT" + index) == hash && i <= 14)
            {
                result = "MP" + X + "_PSTAT_INT" + index;
            }
            else if (joaat("MP_PSTAT_INT" + index) == hash && i <= 2)
            {
                result = "MP_PSTAT_INT" + index;
            }
            else if (joaat("MP" + X + "_NGPSTAT_INT" + index) == hash && i <= 7)
            {
                result = "MP" + X + "_NGPSTAT_INT" + index;
            }
        }
        return result;
    }

    int stats::get_packed_int(int iParam0, int iParam1, int iParam2)
    {
        Any iVar0;
        int iVar1;
        int iVar2;

        if (iParam1 == -1)
        {
            iParam1 = *script_global(1312763).as<int*>();
        }
        iVar0 = 0;
        iVar1 = packed_stat_name(iParam0, iParam1);
        iVar2 = packed_stat_mask(iParam0);
        if (0 != iVar1)
        {
            if (!STATS::STAT_GET_MASKED_INT(iVar1, &iVar0, iVar2, 8, iParam2))
            {
                iVar0 = 0;
            }
        }
        return iVar0;
    }

    bool stats::set_packed_int(int iParam0, int iParam1, int iParam2, bool bParam3)
    {
        int iVar0;
        int iVar1;
        bool bVar2;

        if (iParam2 == -1)
        {
            iParam2 = *script_global(1312763).as<int*>();
        }
        if (iParam1 < 0)
        {
            iParam1 = 255;
        }
        iVar0 = 0;
        iVar1 = 0;
        if (iParam0 >= 384 && iParam0 < 457)
        {
            iVar0 = STATS::GET_PACKED_INT_STAT_KEY((iParam0 - 384), 0, 1, iParam2);
            iVar1 = ((iParam0 - 384) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 384)) * 8) * 8;
        }
        else if (iParam0 >= 457 && iParam0 < 513)
        {
            iVar0 = STATS::GET_PACKED_INT_STAT_KEY((iParam0 - 457), 1, 1, iParam2);
            iVar1 = ((iParam0 - 457) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 457)) * 8) * 8;
        }
        else if (iParam0 >= 1281 && iParam0 < 1305)
        {
            iVar0 = STATS::GET_PACKED_INT_STAT_KEY((iParam0 - 1281), 0, 0, 0);
            iVar1 = ((iParam0 - 1281) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 1281)) * 8) * 8;
        }
        else if (iParam0 >= 1305 && iParam0 < 1361)
        {
            iVar0 = STATS::GET_PACKED_INT_STAT_KEY((iParam0 - 1305), 1, 0, 0);
            iVar1 = ((iParam0 - 1305) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 1305)) * 8) * 8;
        }
        else if (iParam0 >= 1393 && iParam0 < 2919)
        {
            iVar0 = STATS::_GET_PACKED_TITLE_UPDATE_INT_STAT_KEY((iParam0 - 1393), 0, 1, iParam2);
            iVar1 = ((iParam0 - 1393) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 1393)) * 8) * 8;
        }
        else if (iParam0 >= 1361 && iParam0 < 1393)
        {
            iVar0 = STATS::_GET_PACKED_TITLE_UPDATE_INT_STAT_KEY((iParam0 - 1361), 0, 0, 0);
            iVar1 = ((iParam0 - 1361) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 1361)) * 8) * 8;
        }
        else if (iParam0 >= 3879 && iParam0 < 4143)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 3879), 0, 1, iParam2, "_NGPSTAT_INT");
            iVar1 = ((iParam0 - 3879) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 3879)) * 8) * 8;
        }
        else if (iParam0 >= 4143 && iParam0 < 4207)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 4143), 0, 0, 0, "_NGPSTAT_INT");
            iVar1 = ((iParam0 - 4143) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 4143)) * 8) * 8;
        }
        else if (iParam0 >= 4399 && iParam0 < 6028)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 4399), 0, 1, iParam2, "_LRPSTAT_INT");
            iVar1 = ((iParam0 - 4399) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 4399)) * 8) * 8;
        }
        else if (iParam0 >= 6413 && iParam0 < 7262)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 6413), 0, 1, iParam2, "_APAPSTAT_INT");
            iVar1 = ((iParam0 - 6413) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 6413)) * 8) * 8;
        }
        else if (iParam0 >= 7262 && iParam0 < 7313)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 7262), 0, 1, iParam2, "_LR2PSTAT_INT");
            iVar1 = ((iParam0 - 7262) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 7262)) * 8) * 8;
        }
        else if (iParam0 >= 7681 && iParam0 < 9361)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 7681), 0, 1, iParam2, "_BIKEPSTAT_INT");
            iVar1 = ((iParam0 - 7681) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 7681)) * 8) * 8;
        }
        else if (iParam0 >= 9553 && iParam0 < 15265)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 9553), 0, 1, iParam2, "_IMPEXPPSTAT_INT");
            iVar1 = ((iParam0 - 9553) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 9553)) * 8) * 8;
        }
        else if (iParam0 >= 15265 && iParam0 < 15369)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 15265), 0, 1, iParam2, "_GUNRPSTAT_INT");
            iVar1 = ((iParam0 - 15265) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 15265)) * 8) * 8;
        }
        else if (iParam0 >= 16010 && iParam0 < 18098)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 16010), 0, 1, iParam2, "_DLCSMUGCHARPSTAT_INT");
            iVar1 = ((iParam0 - 16010) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 16010)) * 8) * 8;
        }
        else if (iParam0 >= 18162 && iParam0 < 19018)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 18162), 0, 1, iParam2, "_GANGOPSPSTAT_INT");
            iVar1 = ((iParam0 - 18162) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 18162)) * 8) * 8;
        }
        else if (iParam0 >= 19018 && iParam0 < 22066)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 19018), 0, 1, iParam2, "_BUSINESSBATPSTAT_INT");
            iVar1 = ((iParam0 - 19018) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 19018)) * 8) * 8;
        }
        else if (iParam0 >= 22194 && iParam0 < 24962)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 22194), 0, 1, iParam2, "_ARENAWARSPSTAT_INT");
            iVar1 = ((iParam0 - 22194) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 22194)) * 8) * 8;
        }
        else if (iParam0 >= 25538 && iParam0 < 26810)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 25538), 0, 1, iParam2, "_CASINOPSTAT_INT");
            iVar1 = ((iParam0 - 25538) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 25538)) * 8) * 8;
        }
        else if (iParam0 >= 27258 && iParam0 < 28098)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 27258), 0, 1, iParam2, "_CASINOHSTPSTAT_INT");
            iVar1 = ((iParam0 - 27258) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 27258)) * 8) * 8;
        }
        else if (iParam0 >= 28483 && iParam0 < 30227)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 28483), 0, 1, iParam2, "_SU20PSTAT_INT");
            iVar1 = ((iParam0 - 28483) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 28483)) * 8) * 8;
        }
        else if (iParam0 >= 30483 && iParam0 < 30515)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 30483), 0, 1, iParam2, "_HISLANDPSTAT_INT");
            iVar1 = ((iParam0 - 30483) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 30483)) * 8) * 8;
        }
        else if (iParam0 >= 30707 && iParam0 < 31707)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 30707), 0, 1, iParam2, "_TUNERPSTAT_INT");
            iVar1 = ((iParam0 - 30707) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 30707)) * 8) * 8;
        }
        else if (iParam0 >= 7641 && iParam0 < 7681)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 7641), 0, 1, iParam2, "_NGDLCPSTAT_INT");
            iVar1 = ((iParam0 - 7641) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 7641)) * 8) * 8;
        }
        else if (iParam0 >= 7313 && iParam0 < 7321)
        {
            iVar0 = STATS::_GET_NGSTAT_INT_HASH((iParam0 - 7313), 0, 0, 0, "_NGDLCPSTAT_INT");
            iVar1 = ((iParam0 - 7313) - STATS::_STAT_GET_PACKED_INT_MASK((iParam0 - 7313)) * 8) * 8;
        }

        bVar2 = STATS::STAT_SET_MASKED_INT(iVar0, iParam1, iVar1, 8, bParam3);
        return bVar2;
    }

    bool stats::set_packed_bool(int iParam0, bool bParam1, int iParam2, int iParam3)
    {
        bool iVar0;
        int iVar1;
        int iVar2;
        int iVar3;
        int iVar4;
        int iVar5;
        int iVar6;
        int iVar7;
        int iVar8;
        int iVar9;
        int iVar10;
        int iVar11;
        int iVar12;
        int iVar13;
        int iVar14;
        int iVar15;
        int iVar16;
        int iVar17;
        int iVar18;
        int iVar19;
        int iVar20;
        int iVar21;
        int iVar22;
        int iVar23;
        int iVar24;
        int iVar25;
        int iVar26;

        if (iParam2 == -1)
        {
            iParam2 = *script_global(1312763).as<int*>();
        }
        iVar0 = 0;
        if (iParam0 >= 0 && iParam0 < 192)
        {
            iVar2 = STATS::GET_PACKED_BOOL_STAT_KEY((iParam0 - 0), 0, 1, iParam2);
            iVar1 = ((iParam0 - 0) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 0)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar2, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 192 && iParam0 < 384)
        {
            iVar3 = STATS::GET_PACKED_BOOL_STAT_KEY((iParam0 - 192), 1, 1, iParam2);
            iVar1 = ((iParam0 - 192) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 192)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar3, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 513 && iParam0 < 705)
        {
            iVar4 = STATS::GET_PACKED_BOOL_STAT_KEY((iParam0 - 513), 0, 0, 0);
            iVar1 = ((iParam0 - 513) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 513)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar4, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 705 && iParam0 < 1281)
        {
            iVar5 = STATS::GET_PACKED_BOOL_STAT_KEY((iParam0 - 705), 1, 0, 0);
            iVar1 = ((iParam0 - 705) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 705)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar5, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 3111 && iParam0 < 3879)
        {
            iVar6 = STATS::_GET_PACKED_TITLE_UPDATE_BOOL_STAT_KEY((iParam0 - 3111), 0, 1, iParam2);
            iVar1 = ((iParam0 - 3111) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 3111)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar6, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 2919 && iParam0 < 3111)
        {
            iVar7 = STATS::_GET_PACKED_TITLE_UPDATE_BOOL_STAT_KEY((iParam0 - 2919), 0, 0, 0);
            iVar1 = ((iParam0 - 2919) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 2919)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar7, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 4207 && iParam0 < 4335)
        {
            iVar8 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 4207), 0, 1, iParam2, "_NGPSTAT_BOOL");
            iVar1 = ((iParam0 - 4207) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 4207)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar8, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 4335 && iParam0 < 4399)
        {
            iVar9 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 4335), 0, 0, 0, "_NGPSTAT_BOOL");
            iVar1 = ((iParam0 - 4335) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 4335)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar9, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 6029 && iParam0 < 6413)
        {
            iVar10 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 6029), 0, 1, iParam2, "_NGTATPSTAT_BOOL");
            iVar1 = ((iParam0 - 6029) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 6029)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar10, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 7385 && iParam0 < 7641)
        {
            iVar11 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 7385), 0, 1, iParam2, "_NGDLCPSTAT_BOOL");
            iVar1 = ((iParam0 - 7385) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 7385)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar11, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 7321 && iParam0 < 7385)
        {
            iVar12 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 7321), 0, 0, 0, "_NGDLCPSTAT_BOOL");
            iVar1 = ((iParam0 - 7321) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 7321)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar12, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 9361 && iParam0 < 9553)
        {
            iVar13 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 9361), 0, 1, iParam2, "_DLCBIKEPSTAT_BOOL");
            iVar1 = ((iParam0 - 9361) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 9361)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar13, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 15369 && iParam0 < 15561)
        {
            iVar14 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 15369), 0, 1, iParam2, "_DLCGUNPSTAT_BOOL");
            iVar1 = ((iParam0 - 15369) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 15369)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar14, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 15562 && iParam0 < 15946)
        {
            iVar15 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 15562), 0, 1, iParam2, "_GUNTATPSTAT_BOOL");
            iVar1 = ((iParam0 - 15562) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 15562)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar15, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 15946 && iParam0 < 16010)
        {
            iVar16 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 15946), 0, 1, iParam2, "_DLCSMUGCHARPSTAT_BOOL");
            iVar1 = ((iParam0 - 15946) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 15946)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar16, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 18098 && iParam0 < 18162)
        {
            iVar17 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 18098), 0, 1, iParam2, "_GANGOPSPSTAT_BOOL");
            iVar1 = ((iParam0 - 18098) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 18098)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar17, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 22066 && iParam0 < 22194)
        {
            iVar18 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 22066), 0, 1, iParam2, "_BUSINESSBATPSTAT_BOOL");
            iVar1 = ((iParam0 - 22066) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 22066)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar18, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 24962 && iParam0 < 25538)
        {
            iVar19 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 24962), 0, 1, iParam2, "_ARENAWARSPSTAT_BOOL");
            iVar1 = ((iParam0 - 24962) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 24962)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar19, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 26810 && iParam0 < 27258)
        {
            iVar20 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 26810), 0, 1, iParam2, "_CASINOPSTAT_BOOL");
            iVar1 = ((iParam0 - 26810) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 26810)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar20, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 28098 && iParam0 < 28354)
        {
            iVar21 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 28098), 0, 1, iParam2, "_CASINOHSTPSTAT_BOOL");
            iVar1 = ((iParam0 - 28098) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 28098)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar21, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 28355 && iParam0 < 28483)
        {
            iVar22 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 28355), 0, 1, iParam2, "_HEIST3TATTOOSTAT_BOOL");
            iVar1 = ((iParam0 - 28355) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 28355)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar22, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 30227 && iParam0 < 30355)
        {
            iVar23 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 30227), 0, 1, iParam2, "_SU20PSTAT_BOOL");
            iVar1 = ((iParam0 - 30227) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 30227)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar23, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 30355 && iParam0 < 30483)
        {
            iVar24 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 30355), 0, 1, iParam2, "_SU20TATTOOSTAT_BOOL");
            iVar1 = ((iParam0 - 30355) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 30355)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar24, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 30515 && iParam0 < 30707)
        {
            iVar25 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 30515), 0, 1, iParam2, "_HISLANDPSTAT_BOOL");
            iVar1 = ((iParam0 - 30515) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 30515)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar25, bParam1, iVar1, iParam3);
        }
        else if (iParam0 >= 31707 && iParam0 < 32283)
        {
            iVar26 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 31707), 0, 1, iParam2, "_TUNERPSTAT_BOOL");
            iVar1 = ((iParam0 - 31707) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 31707)) * 64);
            iVar0 = STATS::STAT_SET_BOOL_MASKED(iVar26, bParam1, iVar1, iParam3);
        }
        return iVar0;
    }

    int stats::packed_bool_stat_mask(int iParam0)
    {
        int iVar0;

        iVar0 = 0;
        if (iParam0 >= 0 && iParam0 < 192)
        {
            iVar0 = ((iParam0 - 0) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 0)) * 64);
        }
        else if (iParam0 >= 192 && iParam0 < 384)
        {
            iVar0 = ((iParam0 - 192) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 192)) * 64);
        }
        else if (iParam0 >= 513 && iParam0 < 705)
        {
            iVar0 = ((iParam0 - 513) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 513)) * 64);
        }
        else if (iParam0 >= 705 && iParam0 < 1281)
        {
            iVar0 = ((iParam0 - 705) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 705)) * 64);
        }
        else if (iParam0 >= 2919 && iParam0 < 3111)
        {
            iVar0 = ((iParam0 - 2919) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 2919)) * 64);
        }
        else if (iParam0 >= 3111 && iParam0 < 3879)
        {
            iVar0 = ((iParam0 - 3111) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 3111)) * 64);
        }
        else if (iParam0 >= 4335 && iParam0 < 4399)
        {
            iVar0 = ((iParam0 - 4335) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 4335)) * 64);
        }
        else if (iParam0 >= 4207 && iParam0 < 4335)
        {
            iVar0 = ((iParam0 - 4207) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 4207)) * 64);
        }
        else if (iParam0 >= 6029 && iParam0 < 6413)
        {
            iVar0 = ((iParam0 - 6029) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 6029)) * 64);
        }
        else if (iParam0 >= 7385 && iParam0 < 7641)
        {
            iVar0 = ((iParam0 - 7385) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 7385)) * 64);
        }
        else if (iParam0 >= 7321 && iParam0 < 7385)
        {
            iVar0 = ((iParam0 - 7321) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 7321)) * 64);
        }
        else if (iParam0 >= 9361 && iParam0 < 9553)
        {
            iVar0 = ((iParam0 - 9361) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 9361)) * 64);
        }
        else if (iParam0 >= 15369 && iParam0 < 15561)
        {
            iVar0 = ((iParam0 - 15369) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 15369)) * 64);
        }
        else if (iParam0 >= 15562 && iParam0 < 15946)
        {
            iVar0 = ((iParam0 - 15562) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 15562)) * 64);
        }
        else if (iParam0 >= 15946 && iParam0 < 16010)
        {
            iVar0 = ((iParam0 - 15946) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 15946)) * 64);
        }
        else if (iParam0 >= 18098 && iParam0 < 18162)
        {
            iVar0 = ((iParam0 - 18098) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 18098)) * 64);
        }
        else if (iParam0 >= 22066 && iParam0 < 22194)
        {
            iVar0 = ((iParam0 - 22066) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 22066)) * 64);
        }
        else if (iParam0 >= 24962 && iParam0 < 25538)
        {
            iVar0 = ((iParam0 - 24962) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 24962)) * 64);
        }
        else if (iParam0 >= 26810 && iParam0 < 27258)
        {
            iVar0 = ((iParam0 - 26810) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 26810)) * 64);
        }
        else if (iParam0 >= 28098 && iParam0 < 28354)
        {
            iVar0 = ((iParam0 - 28098) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 28098)) * 64);
        }
        else if (iParam0 >= 28355 && iParam0 < 28483)
        {
            iVar0 = ((iParam0 - 28355) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 28355)) * 64);
        }
        else if (iParam0 >= 30227 && iParam0 < 30355)
        {
            iVar0 = ((iParam0 - 30227) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 30227)) * 64);
        }
        else if (iParam0 >= 30355 && iParam0 < 30483)
        {
            iVar0 = ((iParam0 - 30355) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 30355)) * 64);
        }
        else if (iParam0 >= 30515 && iParam0 < 30707)
        {
            iVar0 = ((iParam0 - 30515) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 30515)) * 64);
        }
        else if (iParam0 >= 31707 && iParam0 < 32283)
        {
            iVar0 = ((iParam0 - 31707) - STATS::_STAT_GET_PACKED_BOOL_MASK((iParam0 - 31707)) * 64);
        }
        return iVar0;
    }

    int stats::packed_bool_stat_name(int iParam0, int iParam1)
    {
        int iVar0;

        if (iParam1 == -1)
        {
            iParam1 = *script_global(1312763).as<int*>();
        }
        iVar0 = 0;
        if (iParam0 >= 0 && iParam0 < 192)
        {
            iVar0 = STATS::GET_PACKED_BOOL_STAT_KEY((iParam0 - 0), 0, 1, iParam1);
        }
        else if (iParam0 >= 192 && iParam0 < 384)
        {
            iVar0 = STATS::GET_PACKED_BOOL_STAT_KEY((iParam0 - 192), 1, 1, iParam1);
        }
        else if (iParam0 >= 513 && iParam0 < 705)
        {
            iVar0 = STATS::GET_PACKED_BOOL_STAT_KEY((iParam0 - 513), 0, 0, 0);
        }
        else if (iParam0 >= 705 && iParam0 < 1281)
        {
            iVar0 = STATS::GET_PACKED_BOOL_STAT_KEY((iParam0 - 705), 1, 0, 0);
        }
        else if (iParam0 >= 2919 && iParam0 < 3111)
        {
            iVar0 = STATS::_GET_PACKED_TITLE_UPDATE_BOOL_STAT_KEY((iParam0 - 2919), 0, 0, 0);
        }
        else if (iParam0 >= 3111 && iParam0 < 3879)
        {
            iVar0 = STATS::_GET_PACKED_TITLE_UPDATE_BOOL_STAT_KEY((iParam0 - 3111), 0, 1, iParam1);
        }
        else if (iParam0 >= 4335 && iParam0 < 4399)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 4335), 0, 0, 0, "_NGPSTAT_BOOL");
        }
        else if (iParam0 >= 4207 && iParam0 < 4335)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 4207), 0, 1, iParam1, "_NGPSTAT_BOOL");
        }
        else if (iParam0 >= 6029 && iParam0 < 6413)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 6029), 0, 1, iParam1, "_NGTATPSTAT_BOOL");
        }
        else if (iParam0 >= 7321 && iParam0 < 7385)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 7321), 0, 0, 0, "_NGDLCPSTAT_BOOL");
        }
        else if (iParam0 >= 7385 && iParam0 < 7641)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 7385), 0, 1, iParam1, "_NGDLCPSTAT_BOOL");
        }
        else if (iParam0 >= 9361 && iParam0 < 9553)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 9361), 0, 1, iParam1, "_DLCBIKEPSTAT_BOOL");
        }
        else if (iParam0 >= 15369 && iParam0 < 15561)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 15369), 0, 1, iParam1, "_DLCGUNPSTAT_BOOL");
        }
        else if (iParam0 >= 15562 && iParam0 < 15946)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 15562), 0, 1, iParam1, "_GUNTATPSTAT_BOOL");
        }
        else if (iParam0 >= 15946 && iParam0 < 16010)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 15946), 0, 1, iParam1, "_DLCSMUGCHARPSTAT_BOOL");
        }
        else if (iParam0 >= 18098 && iParam0 < 18162)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 18098), 0, 1, iParam1, "_GANGOPSPSTAT_BOOL");
        }
        else if (iParam0 >= 22066 && iParam0 < 22194)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 22066), 0, 1, iParam1, "_BUSINESSBATPSTAT_BOOL");
        }
        else if (iParam0 >= 24962 && iParam0 < 25538)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 24962), 0, 1, iParam1, "_ARENAWARSPSTAT_BOOL");
        }
        else if (iParam0 >= 26810 && iParam0 < 27258)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 26810), 0, 1, iParam1, "_CASINOPSTAT_BOOL");
        }
        else if (iParam0 >= 28098 && iParam0 < 28354)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 28098), 0, 1, iParam1, "_CASINOHSTPSTAT_BOOL");
        }
        else if (iParam0 >= 28355 && iParam0 < 28483)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 28355), 0, 1, iParam1, "_HEIST3TATTOOSTAT_BOOL");
        }
        else if (iParam0 >= 30227 && iParam0 < 30355)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 30227), 0, 1, iParam1, "_SU20PSTAT_BOOL");
        }
        else if (iParam0 >= 30355 && iParam0 < 30483)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 30355), 0, 1, iParam1, "_SU20TATTOOSTAT_BOOL");
        }
        else if (iParam0 >= 30515 && iParam0 < 30707)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 30515), 0, 1, iParam1, "_HISLANDPSTAT_BOOL");
        }
        else if (iParam0 >= 31707 && iParam0 < 32283)
        {
            iVar0 = STATS::_GET_NGSTAT_BOOL_HASH((iParam0 - 31707), 0, 1, iParam1, "_TUNERPSTAT_BOOL");
        }
        return iVar0;
    }

    bool stats::get_packed_bool(int iParam0, int iParam1, int iParam2)
    {
        bool bVar0;
        int iVar1;
        int iVar2;

        bVar0 = false;
        if (iParam1 == -1)
        {
            iParam1 = *script_global(1312763).as<int*>();
        }
        iVar1 = packed_bool_stat_name(iParam0, iParam1);
        iVar2 = packed_bool_stat_mask(iParam0);
        if (0 != iVar1)
        {
            bVar0 = STATS::STAT_GET_BOOL_MASKED(iVar1, iVar2, iParam2);
        }
        return bVar0;
    }
}