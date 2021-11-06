#pragma once
#include "../Common.hpp"
#include "../Natives.hpp"

namespace Big
{
	class systems
	{
	public:
		static double milisecond_to_day(int64_t Milisecond);
		static bool is_number_8_bit(uint8_t number);
		static bool is_number_16_bit(uint16_t number);
		static bool is_number_32_bit(uint32_t number);
		static bool is_number_64_bit(uint64_t number);
		static bool is_script_active(uint32_t Hash);
		static int hotkey(char ch);
		static float degree(float degs);
		static std::string character_filter(const char* str);
		static bool is_2d_vector_equal(NativeVector3 a, NativeVector3 b, float epsilon = FLT_EPSILON);
		static bool is_3d_vector_equal(NativeVector3 a, NativeVector3 b, float epsilon = FLT_EPSILON);
		static bool is_3d_vector_zero(Vector3 a, float epsilon = FLT_EPSILON);
		static bool is_not_number(const char* str);
		static bool has_special_character(const char* str);
		static bool is_float_equal(float a, float b, float epsilon = FLT_EPSILON);
		static void set_weather_type(const char* WeatherType);
		static Player get_player_id_from_name(const char* player_name);
		static NativeVector3 to_scr_vector(Vector3 vector);
		static Vector3 to_rage_vector(NativeVector3 vector);
		static int float_to_int(const float& num);
		static float int_to_float(int x);
		static float round(float var);
	};
}