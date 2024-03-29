#include "../Hooking.hpp"
#include "../Classes/script_thread.hpp"

namespace big
{
	using namespace rage;

	static char struct_backup[sizeof(GtaThread)];
	static char stack_buffer[0xFFFF];
	static bool freemode_terminated = false;

	eThreadState Hooks::gta_thread_tick(GtaThread* thread, unsigned int a2)
	{
		eThreadState state = thread->m_context.m_state;

		if (thread->m_script_hash == RAGE_JOAAT("freemode") && state == eThreadState::running && !freemode_terminated)
		{
			memcpy(struct_backup, (void*)thread, sizeof(GtaThread));
			if (thread->m_stack)
				memcpy(stack_buffer, thread->m_stack, thread->m_context.m_stack_size);
		}

		eThreadState result = static_cast<decltype(&gta_thread_tick)>(g_Hooking->m_gta_thread_tick)(thread, a2);

		if (thread->m_script_hash == RAGE_JOAAT("freemode"))
		{
			if (result == eThreadState::killed && state == eThreadState::running && !freemode_terminated)
			{
				g_Logger->Info("Freemode script crashed, attempting recovery...");

				result = eThreadState::running;

				memcpy(thread, struct_backup, sizeof(GtaThread));
				if (thread->m_stack)
					memcpy(thread->m_stack, stack_buffer, thread->m_context.m_stack_size);
			}

			if (freemode_terminated) freemode_terminated = !(result == eThreadState::running);
		}

		return result;
	}

	eThreadState Hooks::gta_thread_kill(GtaThread* thread)
	{
		eThreadState result = static_cast<decltype(&gta_thread_kill)>(g_Hooking->m_gta_thread_kill)(thread);

		if (thread->m_script_hash == RAGE_JOAAT("freemode"))
			freemode_terminated = !(result == eThreadState::running);

		return result;
	}
}