#include "stdafx.hpp"
#include "left_insert_graft.hpp"

namespace bbtree::algorithm
{
	item_handle left_insert_graft::get_child(rb_item& parent)
	{
		return parent.left;
	}
}