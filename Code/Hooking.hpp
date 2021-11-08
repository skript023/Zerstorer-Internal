#pragma once
#include "VMTHook.hpp"

namespace big
{
	struct Hooks
	{
		static bool IsDlcPresent(std::uint32_t hash);
		static const char* GetLabelText(void* unk, const char* label);
		static bool GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);

		static bool ScriptGameEvent(CScriptedGameEvent* NetEventStruct, CNetGamePlayer* sender);
		static bool ClearPedTaskEvent(int64_t thisptr, CNetGamePlayer* sender, CNetGamePlayer* receiver);
		static bool IncrementStatEvent(CNetworkIncrementStatEvent* net_event_struct, CNetGamePlayer* sender, CNetGamePlayer* receiver);
		static void RemoveWeaponEvent(int64_t thisptr, rage::datBitBuffer* buffer, CNetGamePlayer* sender, CNetGamePlayer* receiver);
		static void KickVoteEvent(int64_t thisptr, rage::datBitBuffer* buffer, CNetGamePlayer* sender, CNetGamePlayer* receiver);

		static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		static constexpr auto PresentIndex = 8;
		static HRESULT Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags);

		static constexpr auto ResizeBuffersIndex = 13;
		static HRESULT ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);
	};

	class Hooking
	{
	public:
		explicit Hooking();
		~Hooking() noexcept;
		Hooking(Hooking const&) = delete;
		Hooking(Hooking&&) = delete;
		Hooking& operator=(Hooking const&) = delete;
		Hooking& operator=(Hooking&&) = delete;

		void Hook();
		void Unhook();

		friend struct Hooks;
	private:
		void* m_NtQueryVirtualMemory{};
		void* m_OriginalScriptEvent{};
		void* m_OriginalIsDlcPresent{};
		void* m_OriginalGetLabelText{};
		void* m_OriginalGetEventData{};
		void* m_increment_event{};
		void* m_clear_ped_task{};
		void* m_remove_weapon{};
		void* m_kick_vote{};

		
		void* m_OriginalWndProc{};
		VMTHook m_D3DHook;

	};

	inline std::unique_ptr<Hooking> g_Hooking;
}
