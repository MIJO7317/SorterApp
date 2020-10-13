//QuickSorter
#pragma once
#include "Sorter.h"
#include "Stack.h"

namespace Containers
{
	template<typename T>
	class QuickSorter : public Sorter<T>
	{
	private:
		std::vector<std::pair<size_t, size_t>> swaps{};
		std::string name = "Quick Sort";
	public:
		void Sort(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp =
			[](const T& element_1, const T& element_2)
			{
				return element_1 < element_2;
			}) override;
		void SortWithSwaps(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp =
			[](const T& element_1, const T& element_2)
			{
				return element_1 < element_2;
			}) override;
		void SortWithExecution(Sequence<T>& sequence, bool& stop_execution,
			std::function<bool(const T&, const T&)> comp =
			[](const T& element_1, const T& element_2)
			{
				return element_1 < element_2;
			}) override;
		std::vector<std::pair<size_t, size_t>> GetSwaps() const override;
		std::string Name() const override;
		QuickSorter<T>* Clone() const override;
	};

	template<typename T>
	void QuickSorter<T>::Sort(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp)
	{
		if (sequence.GetLength() < 2)
			return;
		T pivot;
		int left, right, i;
		Stack<size_t> stack;
		stack.Push(sequence.GetLength() - 1);
		stack.Push(0);
		do { //while (!stack.Empty())
			left = stack.Top();
			stack.Pop();
			right = stack.Top();
			stack.Pop();
			if (right < left)
				continue;
			pivot = sequence.Get(right);
			i = left - 1;
			for (int j = left; j < right; j++)
			{
				if (comp(sequence.Get(j), pivot))
					i++, sequence.Swap(i, j);
			}
			sequence.Swap(i + 1, right);
			stack.Push(i);
			stack.Push(left);
			stack.Push(right);
			stack.Push(i + 2);
		} while (!stack.Empty());
	}

	template<typename T>
	void QuickSorter<T>::SortWithSwaps(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp)
	{
		this->swaps.clear();
		if (sequence.GetLength() < 2)
			return;
		T pivot;
		int left, right, i;
		Stack<size_t> stack;
		stack.Push(sequence.GetLength() - 1);
		stack.Push(0);
		do { //while (!stack.Empty())
			left = stack.Top();
			stack.Pop();
			right = stack.Top();
			stack.Pop();
			if (right < left)
				continue;
			pivot = sequence.Get(right);
			i = left-1;
			for (int j = left; j < right; j++)
			{
				if (comp(sequence.Get(j), pivot))
					i++, sequence.Swap(i, j), this->swaps.emplace_back(i, j);
			}
			sequence.Swap(i + 1, right);
			this->swaps.emplace_back(i + 1, right);
			stack.Push(i);
			stack.Push(left);
			stack.Push(right);
			stack.Push(i+2);
		} while (!stack.Empty());
	}

	template<typename T>
	void QuickSorter<T>::SortWithExecution(Sequence<T>& sequence, bool& stop_execution, std::function<bool(const T&, const T&)> comp)
	{
		if (sequence.GetLength() < 2)
			return;
		T pivot;
		int left, right, i;
		Stack<size_t> stack;
		stack.Push(sequence.GetLength() - 1);
		stack.Push(0);
		do { //while (!stack.Empty())
			left = stack.Top();
			stack.Pop();
			right = stack.Top();
			stack.Pop();
			if (right < left)
				continue;
			pivot = sequence.Get(right);
			i = left - 1;
			for (int j = left; j < right; j++)
			{
				if (stop_execution)
					return;
				if (comp(sequence.Get(j), pivot))
					i++, sequence.Swap(i, j);
			}
			sequence.Swap(i + 1, right);
			stack.Push(i);
			stack.Push(left);
			stack.Push(right);
			stack.Push(i + 2);
		} while (!stack.Empty());
	}

	template<typename T>
	std::vector<std::pair<size_t, size_t>> QuickSorter<T>::GetSwaps() const
	{
		return this->swaps;
	}

	template<typename T>
	std::string QuickSorter<T>::Name() const
	{
		return this->name;
	}

	template<typename T>
	QuickSorter<T>* QuickSorter<T>::Clone() const
	{
		return new QuickSorter<T>(*this);
	}
}