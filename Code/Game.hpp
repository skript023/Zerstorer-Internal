#pragma once
#include "Classes/Class.hpp"
#include "functions_types.hpp"

namespace big
{
	class GameVariables
	{
	public:
		explicit GameVariables();
		~GameVariables() noexcept = default;
		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;

		void PostInit();

		std::uint32_t* m_GameState;
		std::uint32_t* m_FrameCount;
		bool* m_is_session_started{};
		HWND m_GameWindow;
		IDXGISwapChain* m_Swapchain;
		rage::scrNativeRegistration** m_NativeRegistrations;
		std::uint64_t** m_GlobalBase;
		char* m_GameBuild;
		PVOID m_model_spawn_bypass;
		PVOID m_return_address;
		CPedFactory** m_ped_factory;
		int64_t **m_script_threads;
	};

	class GameFunctions
	{
	public:
		explicit GameFunctions();
		~GameFunctions() noexcept = default;
		GameFunctions(GameFunctions const&) = delete;
		GameFunctions(GameFunctions&&) = delete;
		GameFunctions& operator=(GameFunctions const&) = delete;
		GameFunctions& operator=(GameFunctions&&) = delete;

		
		functions::IsDlcPresent* m_IsDlcPresent;
		functions::WndProc* m_WndProc;
		functions::Fix_Vectors_T m_Fix_Vectors{};
		functions::GetEventData* m_GetEventData;
		functions::GetLabelText* m_GetLabelText;
		functions::GetPlayerPed m_player_pointer;
		functions::get_player_name_t m_get_player_name;
		functions::GetNetGamePlayer get_net_player;
		functions::ptr_to_handle_t m_ptr_to_handle;
		functions::handle_to_ptr_t m_handle_to_ptr;
		functions::ScriptedGameEvent m_script_event;
		functions::IncrementEvent m_increment_event;
		functions::ClearPedTask m_clear_ped_event;
		functions::CRemoveWeaponEvent m_remove_weapon;
		functions::CSendKickVoteEvent m_kick_vote;
		functions::ReadDword m_read_bitbuf_dword;
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;
}
