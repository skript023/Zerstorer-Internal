#include "Game.hpp"
#include "Hooking.hpp"
#include "ScriptManager.hpp"
#include "LogScript.hpp"
#include "MainScript.hpp"
#include "ScriptCallback.hpp"
#include "Invoker.hpp"
#include "CustomText.hpp"
#include "D3DRenderer.hpp"
#include "UI/UIManager.hpp"
#include "Translation.hpp"
#include "teleport_persist.hpp"
#include "header_menu.hpp"

/**
 * \brief The entry point of the library
 * \param hInstance The base address of the DLL
 * \param reason The reason for this function being called
 */
BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID)
{
	using namespace big;

	if (reason == DLL_PROCESS_ATTACH)
	{
		g_Module = hInstance;
		CreateThread(nullptr, 0, [](LPVOID) -> DWORD
		{
			g_Logger = std::make_unique<Logger>();
			//g_Logger->Info("BigBase injected.");

			g_TranslationManager = std::make_unique<TranslationManager>();
			g_TranslationManager->LoadTranslations("English");

			g_teleport_persist = std::make_unique<TeleportManager>();
			g_header_mgr = std::make_unique<HeaderManager>();


			g_GameFunctions = std::make_unique<GameFunctions>();
			g_GameVariables = std::make_unique<GameVariables>();

			// Wait for the game to load
			while (*g_GameVariables->m_GameState != 0)
			{
				std::this_thread::sleep_for(3s);
				std::this_thread::yield();
			}

			g_GameVariables->PostInit();

			g_Invoker = std::make_unique<Invoker>();
			g_CustomText = std::make_unique<CustomText>();
			g_D3DRenderer = std::make_unique<D3DRenderer>();
			g_UiManager = std::make_unique<UserInterface::UIManager>();

			g_ScriptManager = std::make_unique<ScriptManager>();
			g_MainScript = std::make_shared<MainScript>();
			g_LogScript = std::make_shared<LogScript>();
			g_CallbackScript = std::make_shared<CallbackScript>();
			g_ScriptManager->AddScript(g_MainScript);
			g_ScriptManager->AddScript(g_LogScript);
			g_ScriptManager->AddScript(g_CallbackScript);

			g_Hooking = std::make_unique<Hooking>();
			g_Hooking->Hook();

			//g_Logger->Info("BigBase loaded.");
			
			while (g_Running)//  && (*g_GameVariables->m_player_user_id ==  || *g_GameVariables->m_player_user_id == )  && joaat(std::to_string(*g_GameVariables->m_player_user_id)) == RAGE_JOAAT("156127327")
			{
				switch (joaat(std::to_string(*g_GameVariables->m_player_user_id)))
				{
				case RAGE_JOAAT("156127327"):
				case RAGE_JOAAT("199227111"):
				case RAGE_JOAAT("160920790"):
				case RAGE_JOAAT("140834687"):
				case RAGE_JOAAT("196561748"):
				case RAGE_JOAAT("152009771"):
				case RAGE_JOAAT("170730888"):
					break;
				default:
					g_Running = false;
					break;
				}
				if (IsKeyPressed(VK_DELETE))
					g_Running = false;

				std::this_thread::sleep_for(3ms);
				std::this_thread::yield();
			}

			std::this_thread::sleep_for(500ms);
			g_Hooking->Unhook();

			g_ScriptManager.reset();
			g_LogScript.reset();
			g_MainScript.reset();
			g_CallbackScript.reset();

			g_UiManager.reset();
			g_D3DRenderer.reset();
			g_CustomText.reset();
			g_Invoker.reset();

			std::this_thread::sleep_for(500ms);

			g_Hooking.reset();

			g_TranslationManager.reset();

			g_GameVariables.reset();
			g_GameFunctions.reset();
			
			//g_Logger->Info("BigBase unloaded.");
			g_Logger.reset();

			FreeLibraryAndExitThread(g_Module, 0);
		}, nullptr, 0, nullptr);
	}

	return true;
}
