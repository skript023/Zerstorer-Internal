#include "Game.hpp"
#include "Invoker.hpp"

namespace big
{
	GameVariables::GameVariables():
		m_GameState(Signature("48 85 C9 74 4B 83 3D").Scan().Add(7).Rip().As<decltype(m_GameState)>()),
		m_FrameCount(Signature("F3 0F 10 0D ? ? ? ? 44 89 6B 08").Scan().Add(4).Rip().Sub(8).As<decltype(m_GameState)>()),
		m_GameWindow(FindWindowA("grcWindow", "Grand Theft Auto V")),
		m_Swapchain(Signature("48 8B 0D ? ? ? ? 48 8D 55 A0 48 8B 01").Scan().Add(3).Rip().As<decltype(m_Swapchain)&>()),
		m_NativeRegistrations(Signature("48 83 EC 20 48 8D 0D ? ? ? ? E8 ? ? ? ? 0F B7 15 ? ? ? ? 33 FF").Scan().Add(7).Rip().As<decltype(m_NativeRegistrations)>()),
		m_GlobalBase(Signature("4C 8D 4D 08 48 8D 15 ? ? ? ? 4C 8B C0").Scan().Add(7).Rip().As<decltype(m_GlobalBase)>()),
		m_ModelSpawnBypass(Signature("48 8B C8 FF 52 30 84 C0 74 05 48").Scan().Add(8).As<decltype(m_ModelSpawnBypass)>()),
		m_ped_factory(Signature("48 8B 05 ? ? ? ? 48 8B 48 08 48 85 C9 74 52 8B 81").Scan().Add(3).Rip().As<decltype(m_ped_factory)>()),
		m_return_address(Signature("FF E3").Scan().As<decltype(m_return_address)>()),
		m_is_session_started(Signature("40 38 35 ? ? ? ? 75 0E 4C 8B C3 49 8B D7 49 8B CE").Scan().Add(3).Rip().As<decltype(m_is_session_started)>()),
		m_script_threads(Signature("48 8B 05 ? ? ? ? 8B CF 48 8B 0C C8 39 59 68").Scan().Add(3).Rip().As<decltype(m_script_threads)>())
	{
		auto sig = Signature("48 83 EC 60 48 8D 0D ? ? ? ? E8").Scan().Sub(17);
		m_GameBuild = sig.Add(265 + 3).Rip().As<decltype(m_GameBuild)>();
	}

	void GameVariables::PostInit()
	{
	}

	GameFunctions::GameFunctions():
		m_IsDlcPresent(Signature("84 C0 74 0D 8D 53 0C").Scan().Sub(63).As<decltype(m_IsDlcPresent)>()),
		m_WndProc(Signature("48 8B 0D ? ? ? ? 48 8D 55 EF FF 15").Scan().Sub(853).As<decltype(m_WndProc)>()),
		m_Fix_Vectors(Signature("83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA").Scan().As<decltype(m_Fix_Vectors)>()),
		m_GetEventData(Signature("48 85 C0 74 14 4C 8B 10").Scan().Sub(28).As<decltype(m_GetEventData)>()),
		m_GetLabelText(Signature("75 ? E8 ? ? ? ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9").Scan().Sub(19).As<decltype(m_GetLabelText)>()),
		m_player_pointer(Signature("40 53 48 83 EC 20 33 DB 38 1D ? ? ? ? 74 1C 83 F9 1F 77 26").Scan().As<decltype(m_player_pointer)>()),
		m_get_player_name(Signature("40 53 48 83 EC 20 80 3D ? ? ? ? ? 8B D9 74 22").Scan().As<decltype(m_get_player_name)>()),
		m_handle_to_ptr(Signature("75 0D 41 8B 41").Scan().Sub(27).As<decltype(m_handle_to_ptr)>()),
		m_ptr_to_handle(Signature("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC 20 8B 15 ? ? ? ? 48 8B F9 48 83 C1 10 33 DB").Scan().As<decltype(m_ptr_to_handle)>())
	{
	}
}
