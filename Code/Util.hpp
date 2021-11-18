#pragma once
#include "Game.hpp"
#include "Classes/Classes.hpp"
#include "Classes/script_thread.hpp"

namespace big
{
	/**
	 * \brief Checks if a key is pressed
	 * \param key A virtual key code
	 * \return bool
	 */
	inline bool IsKeyPressed(std::uint16_t key)
	{
		if (GetForegroundWindow() == g_GameVariables->m_GameWindow)
		{
			if (GetAsyncKeyState(key) & 0x8000)
			{
				return true;
			}
		}

		return false;
	}

	/**
	 * \brief A stream buffer that uses a char[] buffer
	 */
	class MemoryStreamBuf : public std::streambuf
	{
	public:
		MemoryStreamBuf(char* array, std::size_t size)
		{
			std::fill_n(array, size, '\0');
			std::streambuf::setp(array, array + size - 1);
		}

		template <std::size_t size>
		MemoryStreamBuf(char(&array)[size]) :
			MemoryStreamBuf(&array[0], size)
		{
		}
	};

	/**
	 * \brief An input/output stream that uses a char[] buffer
	 */
	class MemoryStringStream : virtual MemoryStreamBuf, public std::iostream
	{
	public:
		MemoryStringStream(char* array, std::size_t size) :
			MemoryStreamBuf(array, size),
			std::iostream(static_cast<MemoryStreamBuf*>(this))
		{
		}

		template <std::size_t size>
		MemoryStringStream(char(&array)[size]) :
			MemoryStreamBuf(array),
			std::iostream(static_cast<MemoryStreamBuf*>(this))
		{
		}
	};

	/**
	 * \brief A MemoryStringStream with a built in buffer
	 */
	template <std::size_t N>
	class MemoryStringStreamWithBuffer : public MemoryStringStream
	{
	public:
		MemoryStringStreamWithBuffer():
			MemoryStringStream(m_Buffer)
		{}
	private:
		char m_Buffer[N];
	};

	inline constexpr char ToLower(const char c)
	{
		return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
	}

	/**
	 * \brief Calculates JOAAT hash of string at compile time
	 */
	template <std::size_t CharCount>
	struct ConstexprJooat
	{
		char data[CharCount];

		template <std::size_t... Indices>
		constexpr ConstexprJooat(const char* str, std::index_sequence<Indices...>) :
			data{ (str[Indices])... }
		{
		}

		constexpr std::uint32_t GetHash()
		{
			std::uint32_t hash = 0;

			for (std::size_t i = 0; i < CharCount; ++i)
			{
				hash += ToLower(data[i]);
				hash += (hash << 10);
				hash ^= (hash >> 6);
			}

			hash += (hash << 3);
			hash ^= (hash >> 11);
			hash += (hash << 15);

			return hash;
		}
	};
	
	inline CPed* get_local_ped()
	{
		if (auto ped_factory = *g_GameVariables->m_ped_factory)
		{
			return ped_factory->m_local_ped;
		}
		return nullptr;
	}
	
	inline CPlayerInfo* get_local_playerinfo()
	{
		if (auto ped_factory = *g_GameVariables->m_ped_factory)
		{
			if (auto ped = ped_factory->m_local_ped)
			{
				return ped->m_playerinfo;
			}
		}
		return nullptr;
	}

	inline CVehicle* get_local_vehicle()
	{
		if (auto ped_factory = *g_GameVariables->m_ped_factory)
		{
			if (auto ped = ped_factory->m_local_ped)
			{
				return ped->m_last_vehicle;
			}
		}
		return nullptr;
	}
	
	inline CPed* get_player(Player player)
	{
		return g_GameFunctions->m_player_pointer(player);
	}
	
	inline CNetGamePlayer* get_net_player(Player player)
	{
		return g_GameFunctions->get_net_player(player);
	}
	
	template <typename pointer>
	inline pointer entity_to_pointer(Entity entity)
	{
		return reinterpret_cast<pointer>(g_GameFunctions->m_handle_to_ptr(entity));
	}

	inline Entity pointer_to_entity(PVOID pointer)
	{
		return g_GameFunctions->m_ptr_to_handle(pointer);
	}

	inline GtaThread* find_script_thread(uint32_t hash)
	{
		auto local_script = *g_GameVariables->m_script_threads;
		for (int i = 0; i < 53; i++)
		{
			auto thread = local_script->m_thread_list[i];
			if (thread && thread->m_context.m_thread_id && thread->m_handler && thread->m_script_hash == hash)
			{
				return thread;
			}
		}
		return nullptr;
	}
	
	/**
	 * \brief Hashes a string with the Jenkins-one-at-a-time hash function
	 * \param str The string to be hashed
	 * \return Hash of str
	 */
	inline constexpr std::uint32_t joaat(const char* str)
	{
		std::uint32_t hash = 0;
		while (*str)
		{
			hash += ToLower(*str++);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}

	inline constexpr std::uint32_t joaat(std::string_view str)
	{
		std::uint32_t hash = 0;

		for (char c : str)
		{
			hash += ToLower(c);
			hash += (hash << 10);
			hash ^= (hash >> 6);
		}

		hash += (hash << 3);
		hash ^= (hash >> 11);
		hash += (hash << 15);

		return hash;
	}

#	define CONSTEXPR_JOAAT_IMPL(x) (::big::ConstexprJooat<sizeof(x) - 1>((x), std::make_index_sequence<sizeof(x) - 1>()).GetHash())
#	define CONSTEXPR_JOAAT(x) (std::integral_constant<std::uint32_t, CONSTEXPR_JOAAT_IMPL(x)>::value)
#	define RAGE_JOAAT(x) (std::integral_constant<std::uint32_t, CONSTEXPR_JOAAT_IMPL(x)>::value)
}

namespace big::Memory
{
	inline uintptr_t get_multilayer_pointer(uintptr_t base_address, std::vector<DWORD> offsets)
	{
		uintptr_t ptr = *(uintptr_t*)(base_address);
		if (!ptr) {

			return NULL;
		}
		auto level = offsets.size();

		for (auto i = 0; i < level; i++)
		{
			if (i == level - 1)
			{
				ptr += offsets[i];
				if (!ptr) return NULL;
				return ptr;
			}
			else
			{
				ptr = *(uint64_t*)(ptr + offsets[i]);
				if (!ptr) return NULL;
			}
		}

		return ptr;
	}

	template <typename T>
	inline T get_value(uintptr_t BaseAddress, std::vector<DWORD> offsets)
	{

		uintptr_t Addr = get_multilayer_pointer(BaseAddress, offsets);
		if (Addr == NULL) {
			return NULL;
		}

		return *((T*)Addr);
	}

	template <typename T>
	inline void set_value(uintptr_t BaseAddress, std::vector<DWORD> offsets, T value)
	{
		uintptr_t Addr = get_multilayer_pointer(BaseAddress, offsets);
		if (Addr == NULL) {
			return;
		}

		*reinterpret_cast<T*>(Addr) = value;
	}

	inline bool is_bit_set(int _value, int _bit)
	{
		if ((_value >> _bit) & 1LL) return true;
		return false;
	}

	inline int set_bit(int _value, int _bit)
	{
		return _value |= 1LL << _bit;
	}

	inline int clear_bit(int _value, int _bit)
	{
		return _value &= ~(1LL << _bit);
	}
}