#pragma once

#include "insert_graft.hpp"

namespace bbtree::algorithm
{
	class left_insert_graft : public insert_graft
	{
	public:
		virtual ~left_insert_graft() override = default;

	private:
		virtual item_handle get_child(rb_item& parent) override;
	};
}