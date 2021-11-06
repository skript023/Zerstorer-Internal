#include "systems_helper.hpp"

namespace big
{
    int systems::hotkey(char ch)
    {
        return ch;
    }
    bool systems::is_2d_vector_equal(NativeVector3 a, NativeVector3 b, float epsilon)
    {
        return (fabs(a.x - b.x) <= epsilon * std::max(fabs(a.x), fabs(b.x))) && (fabs(a.y - b.y) <= epsilon * std::max(fabs(a.y), fabs(b.y)));
    }

    bool systems::is_3d_vector_equal(NativeVector3 a, NativeVector3 b, float epsilon)
    {
        return (fabs(a.x - b.x) <= epsilon * std::max(fabs(a.x), fabs(b.x))) && (fabs(a.y - b.y) <= epsilon * std::max(fabs(a.y), fabs(b.y))) && (fabs(a.z - b.z) <= epsilon * std::max(fabs(a.z), fabs(b.z)));
    }

    bool systems::is_3d_vector_zero(Vector3 a, float epsilon)
    {
        return (fabs(a.x - 0.0f) <= epsilon * std::max(fabs(a.x), fabs(0.0f))) && (fabs(a.y - 0.0f) <= epsilon * std::max(fabs(a.y), fabs(0.0f))) && (fabs(a.z - 0.0f) <= epsilon * std::max(fabs(a.z), fabs(0.0f)));
    }

    bool systems::is_float_equal(float a, float b, float epsilon)
    {
        return (fabs(a - b) <= epsilon * std::max(fabs(a), fabs(b)));
    }
    Player systems::get_player_id_from_name(const char* player_name)
    {
        if (*g_GameVariables->m_is_session_started)
        {
            for (int i = 0; i <= 32; ++i)
            {
                if (strcmp(g_GameFunctions->m_get_player_name(i), player_name) == 0)
                {
                    return i;
                }
            }
        }
        return -1;
    }

    NativeVector3 systems::to_scr_vector(Vector3 vector)
    {
        return NativeVector3(vector.x, vector.y, vector.z);
    }

    Vector3 systems::to_rage_vector(NativeVector3 vector)
    {
        Vector3 coordinates = { vector.x, vector.y, vector.z };
        return coordinates;
    }

    int systems::float_to_int(const float& num) 
    {
        //check if float fits into integer
        if (std::numeric_limits<int>::digits < std::numeric_limits<float>::digits)
        {
            // check if float is smaller than max int
            if ((num < static_cast<float>(std::numeric_limits<int>::max())) && (num > static_cast<float>(std::numeric_limits<int>::min())))
            {
                return static_cast<int>(num); //safe to cast
            }
            else 
            {
                //NaN is not defined for int return the largest int value
                return std::numeric_limits<int>::max();
            }
        }
        else 
        {
            //It is safe to cast
            return static_cast<int>(num);
        }
    }

    float systems::int_to_float(int x)
    {
        if (std::abs(long(static_cast<float>(x))) <= std::abs(long(x)))
            return static_cast<float>(x);
        return std::nextafter(static_cast<float>(x), 0.f);
    }

    float systems::round(float var)
    {
        return floorf(var * 100) / 100;
    }

    float systems::degree(float degs)
    {
        return degs * 3.141592653589793f / 180.f;
    }

    bool systems::is_script_active(uint32_t Hash)
    {
        return find_script_thread(Hash) != nullptr;
    }
    

}