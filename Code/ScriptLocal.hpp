#pragma once
#include "Game.hpp"

namespace big
{
	class script_local
	{
	public:
		explicit script_local(rage::scrThread* thread, std::size_t index):
			m_index(index), m_stack(thread->m_stack)
		{
		}
		explicit script_local(PVOID stack, std::size_t index):
			m_index(index), m_stack(stack)
		{
		}

		script_local at(std::ptrdiff_t index)
		{
			return script_local(m_stack, m_index + index);
		}

		script_local at(std::ptrdiff_t index, std::size_t size)
		{
			return script_local(m_stack, m_index + 1 + (index * size));
		}

		template <typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> as()
		{
			return static_cast<T>(get());
		}

		template <typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> as()
		{
			return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(get());
		}
	private:
		void* get()
		{
			return reinterpret_cast<uintptr_t*>((uintptr_t)m_stack + (m_index * sizeof(uintptr_t)));
		}
		std::size_t m_index;
		PVOID m_stack;
	};
}