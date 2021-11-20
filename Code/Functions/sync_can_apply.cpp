#include "../Hooking.hpp"
#include "../Classes/net_object_mgr.hpp"
#include "game_helper.hpp"


namespace big
{
	char sender_name[128];
	bool Hooks::clone_create(rage::CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t _object_type, int32_t _object_id, int32_t _object_flag, rage::datBitBuffer* buffer, int32_t timestamp)
	{
		strcpy(sender_name, src->get_name());

		return static_cast<decltype(&clone_create)>(g_Hooking->m_clone_create)(mgr, src, dst, _object_type, _object_id, _object_flag, buffer, timestamp);
	}

	bool Hooks::sync_can_apply(rage::netSyncTree* netSyncTree, rage::netObject* netObject)
	{
		auto ped_hash = netSyncTree->m_sync_tree_node->m_ped_model;
		char sender_info[128] = "Crash has been sent by ";
		strcat(sender_info, sender_name);
		
		if (g_protection->crash)
		{
			switch (ped_hash)
			{
			case RAGE_JOAAT("slod_human"):
			case RAGE_JOAAT("slod_large_quadped"):
			case RAGE_JOAAT("slod_small_quadped"):
				message::notification("~bold~~g~Zerstorer Menu", sender_info, "~bold~~g~Zerstorer Protection");
				return false;
			}
		}
		return static_cast<decltype(&sync_can_apply)>(g_Hooking->m_sync_can_apply)(netSyncTree, netObject);
	}
}