#pragma once
#include <cstdint>
#include "Player.hpp"

namespace Big
{
	#pragma pack(push, 1)
	class CPed : public fwEntity
	{
	public:
		uint32_t m_hostility; //0x018C
		char pad_0190[240]; //0x0190
		float m_health; //0x0280
		char pad_0284[28]; //0x0284
		float m_max_health; //0x02A0
		char pad_02A4[2700]; //0x02A4
		class CVehicle* m_last_vehicle; //0x0D30
		char pad_0D38[282]; //0x0D38
		bool m_is_in_vehicle; //0x0E52
		char pad_0E53[613]; //0x0E53
		uint8_t m_ragdoll; //0x10B8
		char pad_10B9[3]; //0x10B9
		int8_t m_decal_index; //0x10BC
		int8_t m_decal_info; //0x10BD
		char pad_10BE[10]; //0x10BE
		class CPlayerInfo* m_playerinfo; //0x10C8
		class CPedInventory* m_weapon_inventory; //0x10D0
		class CPedWeaponManager* m_weapon_mgr; //0x10D8
		char pad_10E0[812]; //0x10E0
		uint8_t seatbelt; //0x140C
		char pad_140D[211]; //0x140D
		float m_armor; //0x14E0
	};	//Size: 0x14E4
	static_assert(sizeof(CPed) == 0x14E4, "CPed is not properly sized");
	#pragma pack(pop)
	class CPedFactory
	{
	public:
		virtual ~CPedFactory() = default;
		class CPed* m_local_ped;
	};
}