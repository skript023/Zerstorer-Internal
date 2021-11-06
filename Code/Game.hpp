#pragma once

namespace rage
{
	struct scrNativeRegistration;
}

namespace Big
{
	class CPedFactory;
	class CPed;
	class CNetGamePlayer;
}

namespace Big
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
		PVOID m_ModelSpawnBypass;
		PVOID m_return_address;
		CPedFactory** m_ped_factory;
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

		using IsDlcPresent = bool(std::uint32_t hash);
		IsDlcPresent* m_IsDlcPresent;

		using WndProc = LRESULT(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		WndProc* m_WndProc;

		using GetEventData = bool(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);
		GetEventData* m_GetEventData;

		using GetLabelText = const char*(void* unk, const char* label);
		GetLabelText* m_GetLabelText;

		using GetPlayerPed = CPed*(__fastcall*)(std::int32_t player);
		GetPlayerPed m_player_pointer;

		using get_player_name_t = const char* (__fastcall*)(std::int32_t player);
		get_player_name_t m_get_player_name;

		using GetNetGamePlayer = CNetGamePlayer*(__fastcall*)(std::int32_t player);
		GetNetGamePlayer get_net_player;

		using ptr_to_handle_t = std::int32_t(__fastcall*)(PVOID pointer);
		ptr_to_handle_t m_ptr_to_handle;

		using handle_to_ptr_t = uintptr_t*(__fastcall*)(std::int32_t entity);
		handle_to_ptr_t m_handle_to_ptr;
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;
}
