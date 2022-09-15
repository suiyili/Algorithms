#pragma once

#include "quick_sorter_i.hpp"
#include "single_item_sorter.hpp"
#include "double_items_sorter.hpp"
#include <memory>
#include <stdexcept>
#include <utility>

/*
1. iterate all util find one < last
2. swap and move splitter to include swapped element.
3. swap the judge with the border one.
4. start from both sides of the judge.
*/
namespace sort_algo::quicksort
{	
	template<typename ITER>
	class quick_sorter final : public quick_sorter_i<ITER>
	{
	public:
		static std::unique_ptr<quick_sorter_i<ITER>> create_sorter(ITER begin, ITER end);

		quick_sorter(ITER begin, ITER end);
		~quick_sorter() override = default;
		
		void sort(compare_func<ITER> comp) override;
	private:

		ITER partition(compare_func<ITER> comp)const;
		void recursive_sort(ITER split_pos, compare_func<ITER> comp)const;
		ITER begin_;
		ITER end_;
	};
	
	template<typename ITER>
	std::unique_ptr<quick_sorter_i<ITER>> quick_sorter<ITER>::create_sorter(ITER begin, ITER end)
	{
		auto diff = distance(begin, end);
		switch(diff)
		{
			case 0U:
				throw std::invalid_argument("no elements");
			case 1U:
				return std::make_unique<single_item_sorter<ITER>>(begin);
			case 2U:
				return std::make_unique<double_items_sorter<ITER>>(begin, next(begin));
			default:
				return std::make_unique<quick_sorter<ITER>>(begin, end);
		}
	}
	
	template<typename ITER>
	inline quick_sorter<ITER>::quick_sorter(ITER begin, ITER end)
	:begin_(begin), end_(end)
	{}
	
	template<typename ITER>
	inline void quick_sorter<ITER>::sort(compare_func<ITER> comp)
	{
		auto split_pos = partition(comp);
		recursive_sort(split_pos, comp);
	}
	
	template<typename ITER>
	inline ITER quick_sorter<ITER>::partition(compare_func<ITER> comp)const
	{
		auto splitter = begin_;
		auto last = prev(end_);
		for(auto i = begin_; i != last; ++i)
		{
			if(comp(*i, *last))
			{
				std::swap(*i, *splitter);
				++splitter;
			}
		}
		std::swap(*last, *splitter);
		return splitter;
	}
	
	template<typename ITER>
	inline void quick_sorter<ITER>::recursive_sort(ITER split_pos, compare_func<ITER> comp)const
	{
		if(begin_ != split_pos)
		{
			auto less_sorter = create_sorter(begin_, split_pos);
			less_sorter->sort(comp);
		}
		
		auto next_split = next(split_pos);
		if(next_split != end_)
		{
			auto great_sorter = create_sorter(next(split_pos), end_);
			great_sorter->sort(comp);
		}
	}
}