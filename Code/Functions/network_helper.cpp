#include "network_helper.hpp"
#include "game_helper.hpp"

namespace big
{
	void network::set_session(int SessionId)
	{
		int i = 0;
		if (SessionId == -1)
		{
			*script_global(g_global.session_change).at(2).as<int*>() = -1;
			*script_global(g_global.session_change).as<int*>() = 1;
			*script_global(g_global.sctv).as<bool*>() = false;
		}
		else if (SessionId == 13)
		{
			*script_global(g_global.session_id).as<int*>() = SessionId;
			*script_global(g_global.session_change).as<int*>() = 1;
			*script_global(g_global.sctv).as<bool*>() = true;
		}
		else
		{
			*script_global(g_global.session_id).as<int*>() = SessionId;
			*script_global(g_global.session_change).as<int*>() = 1;
			*script_global(g_global.sctv).as<bool*>() = false;
		}
	}
}