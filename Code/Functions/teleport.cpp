#include "teleport.hpp"
#include "game_helper.hpp"
#include "Blip.hpp"
#include "../ScriptCallback.hpp"
#include "../Classes/Enum.hpp"

namespace big
{
    NativeVector3 teleport::get_blip_coords(int icon_id, int icon_colour)
    {
        if (BlipList* blip_ptr = g_GameVariables->m_blip_ptr)
        {
            for (int i = 0; i <= 1492; i++)
            {
                auto blip_list = blip_ptr->m_blips[i].m_blip_entry;
                if (blip_list)
                {
                    int blip_id = blip_list->m_icon;
                    int blip_colour = blip_list->m_color;

                    if (icon_colour == 0)
                        if (blip_id == icon_id)
                            return systems::to_scr_vector(blip_list->blip_coords);

                    if ((blip_id == icon_id) && (blip_colour == icon_colour))
                        return systems::to_scr_vector(blip_list->blip_coords);
                }
            }
        }
        return NativeVector3(0.0f, 0.0f, 0.0f);
    }

    NativeVector3 teleport::get_mission_blip()
    {
        static NativeVector3 zero;
        NativeVector3 coords, oldCoords;
        auto e = PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : PLAYER::PLAYER_PED_ID();

        bool blipFound = false;
        if (!blipFound)
        {
            for (Blip i = HUD::GET_FIRST_BLIP_INFO_ID(Circle); HUD::DOES_BLIP_EXIST(i) != 0; i = HUD::GET_NEXT_BLIP_INFO_ID(Circle))
            {
                if (HUD::GET_BLIP_COLOUR(i) == YellowMission || HUD::GET_BLIP_COLOUR(i) == Mission || HUD::GET_BLIP_COLOUR(i) == YellowMission2 || HUD::GET_BLIP_COLOUR(i) == Blue)
                {
                    coords = HUD::GET_BLIP_COORDS(i);
                    blipFound = true;
                    oldCoords = ENTITY::GET_ENTITY_COORDS(e, FALSE);
                    break;
                }
            }
            if (blipFound)
            {
                return coords;
            }
        }
        else
        {
            coords = oldCoords;
            return coords;
        }
        return zero;
    }

    NativeVector3 teleport::get_ground_coords(NativeVector3 coords, int tries)
    {
        float groundZ;
        if (systems::is_float_equal(coords.z, 20.f))
        {
            for (int i = 0; i < tries; ++i)
            {
                if (i)
                {
                    for (float z = 1000.f; z >= 0.f; z -= 100.f)
                    {
                        STREAMING::REQUEST_COLLISION_AT_COORD(coords.x, coords.y, z);
                        SYSTEM::WAIT(0);
                    }
                }

                if (MISC::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, 1000.f, &groundZ, false, true))
                {
                    return NativeVector3(coords.x, coords.y, groundZ + 2.5f);
                }
                SYSTEM::WAIT(0);
            }
            return NativeVector3(coords.x, coords.y, -225.f);
        }
        return NativeVector3(coords.x, coords.y, coords.z + 2.5f);
    }
    
    void teleport::teleport_to_marker()
    {
        auto pos = *g_GameVariables->m_waypoint_coords;//blip::get_blip_coords(Waypoint, WaypointColor);
        auto e = PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : PLAYER::PLAYER_PED_ID();

        if (systems::is_float_equal(pos.x, 0.f) && systems::is_float_equal(pos.y, 0.f))
            return;
        
        g_CallbackScript->AddCallback<TeleportWaypoint>(e, pos.x, pos.y);
    }

    void teleport::teleport_to_objective()
    {
        NativeVector3 coords = get_mission_blip();

        if (systems::is_3d_vector_zero(coords))
            return;

        auto e = PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : PLAYER::PLAYER_PED_ID();

        g_CallbackScript->AddCallback<NetworkControlCallback>(e, [=] 
        {
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z, FALSE, FALSE, FALSE);
        });
    }
    
}