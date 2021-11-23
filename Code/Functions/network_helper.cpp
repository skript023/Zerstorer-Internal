#include "network_helper.hpp"
#include "game_helper.hpp"
#include "../ScriptCallback.hpp"
#include "../Classes/Enum.hpp"
#include "player_option.hpp"

namespace big
{
    void network::crash_player(Ped target_ped)
    {
        Hash crash_hash = RAGE_JOAAT("slod_human");
        g_CallbackScript->AddCallback<ModelCallback>(crash_hash, [=] 
        {
            auto src = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), TRUE);
            auto dst = ENTITY::GET_ENTITY_COORDS(target_ped, TRUE);

            if (MISC::GET_DISTANCE_BETWEEN_COORDS(src.x, src.y, src.z, dst.x, dst.y, dst.z, false) > 300.0f)
            {
                if (STREAMING::IS_MODEL_IN_CDIMAGE(crash_hash))
                {
                    if (STREAMING::IS_MODEL_VALID(crash_hash))
                    {
                        *(unsigned short*)g_GameVariables->m_model_spawn_bypass = 0x9090;
                        Ped NewPed = PED::CREATE_PED(3, crash_hash, dst.x, dst.y, dst.z, 0, TRUE, TRUE);
                        *(unsigned short*)g_GameVariables->m_model_spawn_bypass = 0x0574;
                        // Segmentation Fault

                        if (*g_GameVariables->m_is_session_started)
                        {
                            ENTITY::_SET_ENTITY_SOMETHING(NewPed, TRUE); //True means it can be deleted by the engine when switching lobbies/missions/etc, false means the script is expected to clean it up.
                            auto networkId = NETWORK::PED_TO_NET(NewPed);
                            if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(NewPed))
                                NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
                        }
                        ENTITY::ATTACH_ENTITY_TO_ENTITY(NewPed, target_ped, SKEL_Spine0, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, FALSE, FALSE, TRUE, TRUE, 2, TRUE);

                        STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(crash_hash);
                    }
                }
            }
        });
    }

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

    void network::blame_player(Ped blame)
    {
        for (int i = 0; i <= 32; i++)
        {
            auto pos = ENTITY::GET_ENTITY_COORDS(player::get_player_ped(i), false);
            add_owned_explosion(blame, pos, EXPLOSION_TRAIN, 1000, TRUE, FALSE, 0.0f);
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