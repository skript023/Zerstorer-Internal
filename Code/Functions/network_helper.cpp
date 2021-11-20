#include "network_helper.hpp"
#include "game_helper.hpp"
#include "../ScriptCallback.hpp"

namespace big
{
    void network::blind_cops(bool Activation)
    {
        if (Activation)
        {
            *script_global(2544210).at(4623).as<int*>() = 1;
            *script_global(2544210).at(4625).as<int*>() = NETWORK::GET_NETWORK_TIME();
            *script_global(2544210).at(4622).as<int*>() = 5;
        }
        else
        {
            *script_global(2544210).at(4623).as<int*>() = 0;
            *script_global(2544210).at(4625).as<int*>() = 0;
            *script_global(2544210).at(4622).as<int*>() = 0;
        }
    }

    void network::reveal_player(bool Activation)
    {
        if (Activation)
        {
            *script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(212).as<int*>() = 1;
            *script_global(2441237).at(71).as<int*>() = NETWORK::GET_NETWORK_TIME();
        }
        else
        {
            *script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(212).as<int*>() = 0;
            *script_global(2441237).at(71).as<int*>() = NETWORK::GET_NETWORK_TIME();
        }
    }

    void network::off_the_radar(bool Activation)
    {
        if (Activation)
        {
            *script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(209).as<int*>() = 1;
            *script_global(2441237).at(70).as<int*>() = NETWORK::GET_NETWORK_TIME();
            *script_global(2544210).at(4628).as<int*>() = 3;
        }
        else
        {
            *script_global(2426865).at(PLAYER::PLAYER_ID(), 449).at(209).as<int*>() = 0;
            *script_global(2441237).at(70).as<int*>() = 0;
            *script_global(2544210).at(4628).as<int*>() = 0;
        }
    }

	void network::add_owned_explosion(Ped ped, NativeVector3 pos, int explosionType, float damageScale, bool isAudible, bool isInvinsible, float ShakeCam)
	{
		*(unsigned short*)g_GameVariables->m_add_owned_explosion_bypass_1 = 0xE990;
		*(unsigned short*)g_GameVariables->m_add_owned_explosion_bypass_2 = 0x9090;
		FIRE::ADD_OWNED_EXPLOSION(ped, pos.x, pos.y, pos.z, explosionType, damageScale, isAudible, isInvinsible, ShakeCam);
		*(unsigned short*)g_GameVariables->m_add_owned_explosion_bypass_1 = 0x850F;
		*(unsigned short*)g_GameVariables->m_add_owned_explosion_bypass_2 = 0x0E74;
	}

	void network::set_session(int SessionId)
	{
		if (SessionId == -1)
		{
			*script_global(g_global.session_change).at(2).as<int*>() = -1;
			*script_global(g_global.session_change).as<int*>() = 1;
			g_CallbackScript->AddCallback<DelayCallback>(200ms, []
			{
				*script_global(g_global.session_change).as<int*>() = 0;
				*script_global(g_global.sctv).as<bool*>() = false; 
			});
		}
		else if (SessionId == 13)
		{
			*script_global(g_global.session_id).as<int*>() = SessionId;
			*script_global(g_global.session_change).as<int*>() = 1;
			g_CallbackScript->AddCallback<DelayCallback>(200ms, []
			{
				*script_global(g_global.session_change).as<int*>() = 0;
				*script_global(g_global.sctv).as<bool*>() = true;
			});
		}
		else
		{
			*script_global(g_global.session_id).as<int*>() = SessionId;
			*script_global(g_global.session_change).as<int*>() = 1;
			g_CallbackScript->AddCallback<DelayCallback>(200ms, []
			{
				*script_global(g_global.session_change).as<int*>() = 0;
				*script_global(g_global.sctv).as<bool*>() = false;
			});
		}
	}
}