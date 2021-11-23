#pragma once
#include "VMTHook.hpp"

namespace big
{
	struct Hooks
	{
		static bool IsDlcPresent(std::uint32_t hash);
		static const char* GetLabelText(void* unk, const char* label);
		static bool GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount);

		static bool received_event(rage::netEventMgr* event_manager, CNetGamePlayer* source_player, CNetGamePlayer* target_player, uint16_t event_id, int event_index, int event_handled_bitset, int64_t bit_buffer_size, rage::datBitBuffer* buffer);
		
		static bool send_net_info_to_lobby(rage::netPlayerData* local_player, __int64 a2, __int64 a3, DWORD* a4);

		static bool sync_can_apply(rage::netSyncTree* netSyncTree, rage::netObject* netObject);
		static bool clone_create(rage::CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t _object_type, int32_t _object_id, int32_t _object_flag, rage::datBitBuffer* buffer, int32_t timestamp);

		static rage::eThreadState gta_thread_tick(GtaThread* a1, unsigned int a2);
		static rage::eThreadState gta_thread_kill(GtaThread* thread);

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
		void* m_OriginalIsDlcPresent{};
		void* m_OriginalGetLabelText{};
		void* m_OriginalGetEventData{};

		void* m_received_event{};

		void* m_sync_can_apply{};
		void* m_clone_create{};

		void* m_send_net_info_to_lobby_hook{};

		void* m_gta_thread_tick{};
		void* m_gta_thread_kill{};
		
		void* m_OriginalWndProc{};
		VMTHook m_D3DHook;

	};

	inline std::unique_ptr<Hooking> g_Hooking;
}
