#pragma once
#include "Sequence.h"
#include <functional>
#include<vector>
#include<utility>

namespace Containers
{
	template<typename T>
	class Sorter
	{
	public:
		virtual void Sort(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp =
			[](const T& element_1, const T& element_2)
			{
				return element_1 < element_2;
			}) = 0;
		virtual void SortWithSwaps(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp =
			[](const T& element_1, const T& element_2)
			{
				return element_1 < element_2;
			}) = 0;
		virtual void SortWithExecution(Sequence<T>& sequence, bool& stop_execution,
			std::function<bool(const T&, const T&)> comp =
			[](const T& element_1, const T& element_2)
			{
				return element_1 < element_2;
			}) = 0;
		virtual std::vector<std::pair<size_t, size_t>> GetSwaps() const = 0;
		virtual std::string Name() const = 0;
		virtual Sorter<T>* Clone() const = 0;
		virtual ~Sorter() {}
	};
}

#include "InsertionSorter.h"
#include "ShellSorter.h"
#include "QuickSorter.h"
#include "BubbleSorter.h"