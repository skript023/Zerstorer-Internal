#include "network_helper.hpp"

namespace big
{
	void network::set_session(int SessionId)
	{
			{
		if (SessionId == -1)
		{
			*script_global(g_global.session_change).at(2).as<int*>() = -1;
			*script_global(g_global.session_change).as<int*>() = 1;
			std::this_thread::sleep_for(200ms);
			*script_global(g_global.session_change).as<int*>() = 0;
			*script_global(g_global.sctv).as<bool*>() = false;
		}
		else if (SessionId == 13)
		{
			*script_global(g_global.session_id).as<int*>() = SessionId;
			*script_global(g_global.session_change).as<int*>() = 1;
			std::this_thread::sleep_for(200ms);
			*script_global(g_global.session_change).as<int*>() = 0;
			*script_global(g_global.sctv).as<bool*>() = true;
		}
		else
		{
			*script_global(g_global.session_id).as<int*>() = SessionId;
			*script_global(g_global.session_change).as<int*>() = 1;
			std::this_thread::sleep_for(200ms);
			*script_global(g_global.session_change).as<int*>() = 0;
			*script_global(g_global.sctv).as<bool*>() = false;
		}
	}
}