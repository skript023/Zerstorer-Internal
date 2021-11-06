#pragma once
#include "Game.hpp"

namespace big
{
	class script_global
	{
	public:
		constexpr explicit script_global(std::size_t index):
			m_Index(index)
		{}

		constexpr script_global at(std::size_t index)
		{
			return script_global(m_Index + index);
		}

		constexpr script_global at(std::size_t index, std::size_t x)
		{
			return at(1 + (index * x));
		}

		template <typename T>
		std::enable_if_t<std::is_pointer<T>::value, T> as() const
		{
			return reinterpret_cast<T>(IndexToPtr(m_Index));
		}

		template <typename T>
		std::enable_if_t<std::is_lvalue_reference<T>::value, T> as() const
		{
			return *reinterpret_cast<std::add_pointer_t<std::remove_reference_t<T>>>(IndexToPtr(m_Index));
		}

		template <typename T>
		std::enable_if_t<std::is_same<T, std::uintptr_t>::value, T> as() const
		{
			return reinterpret_cast<std::uintptr_t>(as<void*>());
		}
	private:
		static void* IndexToPtr(std::size_t index)
		{
			return (g_GameVariables->m_GlobalBase[index >> 0x12 & 0x3F]) + (index & 0x3FFFF);
		}

		std::uintptr_t m_Index;
	};
}
