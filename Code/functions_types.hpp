#pragma once
#include "Common.hpp"
#include "Classes/Class.hpp"

namespace big::functions
{
	using IsDlcPresent = bool(std::uint32_t hash);
	using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	using Fix_Vectors_T = void(*)(rage::scrNativeCallContext*);
	using GetEventData = bool(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
	using GetLabelText = const char* (void* unk, const char* label);
	using GetPlayerPed = CPed * (__fastcall*)(std::int32_t player);
	using get_player_name_t = const char* (__fastcall*)(std::int32_t player);
	using GetNetGamePlayer = CNetGamePlayer * (__fastcall*)(std::int32_t player);
	using ptr_to_handle_t = std::int32_t(__fastcall*)(PVOID pointer);
	using handle_to_ptr_t = uintptr_t * (__fastcall*)(std::int32_t entity);

	using received_event = bool(*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int64_t bit_buffer_size, rage::datBitBuffer* bit_buffer);
	using send_event_ack = void(*)(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, int event_index, int event_handled_bitset);

	using ReadDword = bool(*)(rage::datBitBuffer* ptr, uint32_t* integer, int bits);
	using read_bitbuf_array = bool(*)(rage::datBitBuffer* buffer, PVOID read, int bits, int);

	using get_network_object_t = rage::netObject*(*)(rage::CNetworkObjectMgr* mgr, int16_t id, bool is_true);
	using sync_can_apply_t = bool (*)(rage::netSyncTree* netSyncTree, rage::netObject* netObject);
	using clone_create_t = bool (*) (rage::CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp);

	using gta_thread_tick = __int64(*)(GtaThread* a1, unsigned int a2);
	using gta_thread_kill = __int64(*)(GtaThread* a1);

}