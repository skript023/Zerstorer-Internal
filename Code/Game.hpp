#pragma once
#include "Classes/Class.hpp"
#include "functions_types.hpp"
#include "Types.hpp"

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
		PVOID m_add_owned_explosion_bypass_1;
		PVOID m_add_owned_explosion_bypass_2;
		Vector2 *m_waypoint_coords;
		uint64_t* m_player_user_id;
		BusinessMoney** m_money_in_bunker;
		char* m_real_name;
		char* m_player_name_esp;
		char* m_player_name_display;

		int *m_total_friend;
		PVOID m_return_address;
		CPedFactory** m_ped_factory;
		BlipList* m_blip_ptr;
		FriendList** m_friend_list;
		CReplayInterface** m_replay_interface;
		rage::CNetworkObjectMgr** m_network_object_manager;

		LocalScript** m_script_threads;
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

		functions::ReadDword m_read_bitbuf_dword;
		functions::read_bitbuf_array m_read_bitbuf_array;
		functions::received_event m_received_event;
		functions::send_event_ack m_send_event_ack;

		functions::get_network_object_t m_get_network_object;
		functions::sync_can_apply_t m_sync_can_apply;
		functions::clone_create_t m_clone_create;

		functions::gta_thread_tick m_gta_thread_tick;
		functions::gta_thread_kill m_gta_thread_kill;
		functions::send_net_info_to_lobby m_send_net_info_to_lobby;
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;
}
