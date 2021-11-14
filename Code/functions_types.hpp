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

	using ScriptedGameEvent = bool(*)(CScriptedGameEvent* NetEventStruct, CNetGamePlayer* sender);
	using IncrementEvent = bool(*)(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender, CNetGamePlayer* receiver);
	using ClearPedTask = bool(*)(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver);
	using CNetworkRequestEvent = bool(*)(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver);
	using CRemoveWeaponEvent = void(*)(int64_t thisptr, rage::datBitBuffer* buffer, CNetGamePlayer* sender, CNetGamePlayer* receiver);
	using CSendKickVoteEvent = void(*)(int64_t thisptr, rage::datBitBuffer* buffer, CNetGamePlayer* sender, CNetGamePlayer* receiver);

	using ReadDword = bool(*)(rage::datBitBuffer* ptr, uint32_t* integer, int bits);

}