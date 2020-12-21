#include "stdafx.hpp"
#include "right_insert_graft.hpp"

namespace bbtree::algorithm
{
	item_handle right_insert_graft::get_child(rb_item& parent)
	{
		return parent.right;
	}
}