#include "Hooking.hpp"
#include "Classes/net_game_event.hpp"
#include "Game.hpp"
#include "ScriptManager.hpp"
#include "CustomText.hpp"
#include "Util.hpp"
#include "D3DRenderer.hpp"
#include "UI/UIManager.hpp"
#include "Functions/game_event.hpp"
#include <MinHook/MinHook.h>
#include "Classes/Enum.hpp"
#include "Functions/game_helper.hpp"
#include "Functions/game_function.hpp"

#ifdef BIGBASE_DEBUG
#  pragma comment(lib, "MinHook-Debug.lib")
#else
#  pragma comment(lib, "MinHook-Release.lib")
#endif

namespace big
{
	namespace
	{
		std::uint32_t g_HookFrameCount{};
	}

	bool Hooks::ScriptGameEvent(CScriptedGameEvent* NetEventStruct, CNetGamePlayer* sender)
	{
		auto args = NetEventStruct->m_args;//reinterpret_cast<std::int64_t*>(NetEventStruct + 0x70);
		auto sender_name = sender->get_name();//*reinterpret_cast<std::int8_t*>(CNetGamePlayer + 0x2D);
		auto ip_address = sender->get_net_data()->m_relay_ip;//uint8_t out[4]; //*(uint32_t*)&out = ip_address;
		int args_size = _ARRAYSIZE(args);//sizeof(*args) / sizeof(args[0]); //NetEventStruct->m_args_size;

		auto sender_id = sender->player_id;//systems::get_player_id_from_name(sender_name);//CNetGamePlayer->player_id
		auto PlayerRID = sender->get_net_data()->m_rockstar_id;//player::GetPlayerRid((Player)args[1]);//CNetGamePlayer->player_info->m_rockstar_id;
		const auto EventHash = (int)args[0]; //because the event hash is the first arguement
		char sender_info[100];

		switch (EventHash)
		{
		case TELEPORT_APARTMENT: //Invite
			if (true)
			{
				strcpy(sender_info, "~g~Blocked Invite Event From ");
				strcat(sender_info, sender_name);

				return true; //lets return true if we return false we are really only moving the event to the buffer
			}
			break;
		case TELEPORT_CAYO: //send cayo
			if (true)
			{
				strcpy(sender_info, "~g~Blocked Teleport Cayo Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Ellohim Private Menu", sender_info, "~bold~~g~Ellohim Menu Protection");
				
				return true;
			}
			break;
		case CEO_KICK: //CEO Kick
			if (true)
			{
				strcpy(sender_info, "~g~Blocked CEO Kick Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Ellohim Private Menu", sender_info, "~bold~~g~Ellohim Menu Protection");
				
				return true;
			}
			break;
		case CEO_BAN: //CEO Ban
			if (true)
			{
				strcpy(sender_info, "~g~Blocked CEO Ban Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Ellohim Private Menu", sender_info, "~bold~~g~Ellohim Menu Protection");
				
				return true;
			}
			break;
		case ROTATE_CAM: //Rotete Cam
			if (true)
			{
				/*
				HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME("Blocked Rotete Cam");
				HUD::END_TEXT_COMMAND_THEFEED_POST_MESSAGETEXT("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", FALSE, 0, sender_name, "~g~Ellohim Menu Protection");
				HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(true, true);
				*/
				return true;
			}
			break;
		case VEHICLE_KICK: //Vehicle Kick
			if (true)
			{
				strcpy(sender_info, "~g~Blocked Vehicle Kick Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Ellohim Private Menu", sender_info, "~bold~~g~Ellohim Menu Protection");
				
				return true;
			}
			break;
		case TRANSACTION_ERROR:
			if (true)
			{
				strcpy(sender_info, "~g~Blocked Transaction Error Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Ellohim Private Menu", sender_info, "~bold~~g~Ellohim Menu Protection");
				
				return true;
			}
			break;
		case SEND_TO_MISSION_1:
		case SEND_TO_MISSION_2:
			if (true)
			{
				strcpy(sender_info, "~g~Blocked Force Mission Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Ellohim Private Menu", sender_info, "~bold~~g~Ellohim Menu Protection");
				
				return true;
			}
			break;
		case PHONE_INVITE:
			if (true)
			{
				strcpy(sender_info, "~g~Blocked Phone Spam Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Ellohim Private Menu", sender_info, "~bold~~g~Ellohim Menu Protection");
				
				return true;
			}
			break;
		case 515799090:
		case 1767220965:
		case 1305720168:
		case -275229102:
		case -654645351:
		case 1848973789:
		case -194543830:
		case -2063448951:
		case 797978700:
		case -176858990:
		case 1731962870:
		case 1152266822:
		case 257478565:
		case 23010443:
		case 496476216:
		case 1455421717:
		case -419415284:
		case 1358851648:
		case -525866785:
		case -1277389265:
		case -892744477:
		case 600486780:
			if (true)
			{
				return true;
			}
			break;
		case 1463355688: //Kick
		case 575344561: //Kick Host
		case -1382676328: //Kick Host
		case 1256866538: //Kick Sp
		case -1753084819: //Kick SP
		case 1119864805: //Kick
		case -1833002148: //Kick
		case -1587276086: //Kick
		case 1954846099: //Kick 1964309656
		case 1659915470://
		case -2017818728: // Kick Host
		case 27785517: // Kick Host
		case 641157117:
		case -347755611: // Kick Host
		case -137439024: // Kick Host
		case 161038699: // Kick Host
		case -1813981910:
		case 2092565704:
		case 202252150:
		case -1503282114:
		case 243981125:
		case -1836118977:
		case -169685950:
		case -2071141142:
		case -149227625:
		case 1433396036:
		case 1608876738:
		case 458875017:
		case 987018372:
		case 813647057:
		case 696123127:
			if (true)
			{
				strcpy(sender_info, "~g~Blocked Kick Event From ");
				strcat(sender_info, sender_name);
				message::notification("~bold~~g~Ellohim Private Menu", sender_info, "~bold~~g~Ellohim Menu Protection");
				
				return true;
			}
			break;
		}

		return static_cast<decltype(&ScriptGameEvent)>(g_Hooking->m_OriginalScriptEvent)(NetEventStruct, sender);
	}

	bool Hooks::IsDlcPresent(std::uint32_t hash)
	{
		if (g_Running && g_HookFrameCount != *g_GameVariables->m_FrameCount)
		{
			g_HookFrameCount = *g_GameVariables->m_FrameCount;
			g_ScriptManager->OnGameTick();
		}

		return static_cast<decltype(&IsDlcPresent)>(g_Hooking->m_OriginalIsDlcPresent)(hash);
	}

	const char* Hooks::GetLabelText(void* unk, const char* label)
	{
		if (g_Running)
			if (auto text = g_CustomText->GetText(joaat(label)))
				return text;

		return static_cast<decltype(&GetLabelText)>(g_Hooking->m_OriginalGetLabelText)(unk, label);
	}

	bool Hooks::GetEventData(std::int32_t eventGroup, std::int32_t eventIndex, std::int64_t* args, std::uint32_t argCount)
	{
		auto result = static_cast<decltype(&GetEventData)>(g_Hooking->m_OriginalGetEventData)(eventGroup, eventIndex, args, argCount);
		
		if (result && g_LogScriptEvents)
		{
			g_Logger->Info("Script event group: %i", eventGroup);
			g_Logger->Info("Script event index: %i", eventIndex);
			g_Logger->Info("Script event argcount: %i", argCount);
			for (std::uint32_t i = 0; i < argCount; ++i)
				g_Logger->Info("Script event args[%u] : %" PRIi64, i, args[i]);
		}

		return result;
	}

	LRESULT Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		g_D3DRenderer->WndProc(hWnd, msg, wParam, lParam);
		return static_cast<decltype(&WndProc)>(g_Hooking->m_OriginalWndProc)(hWnd, msg, wParam, lParam);
	}

	HRESULT Hooks::Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags)
	{
		if (g_Running)
		{
			g_D3DRenderer->BeginFrame();
			g_ScriptManager->OnD3DTick();
			g_D3DRenderer->EndFrame();
		}

		return g_Hooking->m_D3DHook.GetOriginal<decltype(&Present)>(PresentIndex)(dis, syncInterval, flags);
	}

	HRESULT Hooks::ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
	{
		if (g_Running)
		{
			g_D3DRenderer->PreResize();
			auto hr = g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
			if (SUCCEEDED(hr))
			{
				g_D3DRenderer->PostResize();
			}

			return hr;
		}

		return g_Hooking->m_D3DHook.GetOriginal<decltype(&ResizeBuffers)>(ResizeBuffersIndex)(dis, bufferCount, width, height, newFormat, swapChainFlags);
	}

	Hooking::Hooking():
		m_D3DHook(g_GameVariables->m_Swapchain, 18)
	{

		MH_Initialize();
		MH_CreateHook(g_GameFunctions->m_IsDlcPresent, &Hooks::IsDlcPresent, &m_OriginalIsDlcPresent);
		MH_CreateHook(g_GameFunctions->m_GetLabelText, &Hooks::GetLabelText, &m_OriginalGetLabelText);
		MH_CreateHook(g_GameFunctions->m_GetEventData, &Hooks::GetEventData, &m_OriginalGetEventData);
		MH_CreateHook(g_GameFunctions->m_WndProc, &Hooks::WndProc, &m_OriginalWndProc);

		m_D3DHook.Hook(&Hooks::Present, Hooks::PresentIndex);
		m_D3DHook.Hook(&Hooks::ResizeBuffers, Hooks::ResizeBuffersIndex);
	}

	Hooking::~Hooking() noexcept
	{
		MH_RemoveHook(g_GameFunctions->m_WndProc);
		MH_RemoveHook(g_GameFunctions->m_GetEventData);
		MH_RemoveHook(g_GameFunctions->m_GetLabelText);
		MH_RemoveHook(g_GameFunctions->m_IsDlcPresent);
		MH_Uninitialize();
	}

	void Hooking::Hook()
	{
		m_D3DHook.Enable();
		MH_EnableHook(MH_ALL_HOOKS);
	}

	void Hooking::Unhook()
	{
		m_D3DHook.Disable();
		MH_DisableHook(MH_ALL_HOOKS);
	}
}
