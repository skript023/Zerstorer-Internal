#pragma once
#include "../Common.hpp"

namespace big
{
	class business
	{
	public:

		static void add_meth_supply(Player player, int supply);

		static void add_weed_supply(Player player, int supply);

		static void add_cocain_supply(Player player, int supply);

		static void add_cash_supply(Player player, int supply);

		static void add_document_supply(Player player, int supply);

		static void add_bunker_supply(Player player, int supply);

		static float get_meth_supply(Player player);

		static float get_weed_supply(Player player);

		static float get_cocain_supply(Player player);

		static float get_cash_supply(Player player);

		static float get_document_supply(Player player);

		static float get_bunker_supply(Player player);

		static float get_meth_stock(Player player);

		static float get_weed_stock(Player player);

		static float get_cocain_stock(Player player);

		static float get_cash_stock(Player player);

		static float get_document_stock(Player player);

		static float get_bunker_stock(Player player);

		static float get_research_progress(Player player);

		static const char* get_meth_location(Player player);

		static const char* get_weed_location(Player player);

		static const char* get_cocain_location(Player player);

		static const char* get_cash_location(Player player);

		static const char* get_document_location(Player player);

		static const char* get_bunker_location(Player player);

		static void trigger_meth_production(Player player);

		static void trigger_weed_production(Player player);

		static void trigger_cocain_production(Player player);

		static void trigger_cash_production(Player player);

		static void trigger_document_production(Player player);

		static void trigger_bunker_production(Player player);

		static void trigger_bunker_research(Player player);

	};
}