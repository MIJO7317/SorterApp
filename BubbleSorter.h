//BubbleSorter
#pragma once
#include "Sorter.h"

namespace Containers
{
	template<typename T>
	class BubbleSorter : public Sorter<T>
	{
	private:
		std::vector<std::pair<size_t, size_t>> swaps{};
		std::string name = "Bubble Sort";
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
		BubbleSorter<T>* Clone() const override;
	};

	template<typename T>
	void BubbleSorter<T>::Sort(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp)
	{
		size_t N = sequence.GetLength();
		do
		{
			size_t new_n = 0;
			for (size_t i = 1; i < N; i++)
				if (comp(sequence.Get(i), sequence.Get(i - 1)))
					sequence.Swap(i - 1, i),
					new_n = i;
			N = new_n;
		} while ( N > 1);
	}

	template<typename T>
	void BubbleSorter<T>::SortWithSwaps(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp)
	{
		this->swaps.clear();
		size_t N = sequence.GetLength();
		do
		{
			size_t new_n = 0;
			for (size_t i = 1; i < N; i++)
				if (comp(sequence.Get(i), sequence.Get(i - 1)))
					sequence.Swap(i - 1, i),
					this->swaps.emplace_back(i - 1, i),
					new_n = i;
			N = new_n;
		} while (N > 1);
	}

	template<typename T>
	void BubbleSorter<T>::SortWithExecution(Sequence<T>& sequence, bool& stop_execution, std::function<bool(const T&, const T&)> comp)
	{
		size_t N = sequence.GetLength();
		do
		{
			size_t new_n = 0;
			for (size_t i = 1; i < N; i++)
			{
				if (stop_execution)
					return;
				if (comp(sequence.Get(i), sequence.Get(i - 1)))
					sequence.Swap(i - 1, i),
					new_n = i;
			}
			N = new_n;
		} while (N > 1);
	}

	template<typename T>
	std::vector<std::pair<size_t, size_t>> BubbleSorter<T>::GetSwaps() const
	{
		return this->swaps;
	}

	template<typename T>
	std::string BubbleSorter<T>::Name() const
	{
		return this->name;
	}

	template<typename T>
	BubbleSorter<T>* BubbleSorter<T>::Clone() const
	{
		return new BubbleSorter<T>(*this);
	}
}