//InsertionSorter
#pragma once
#include "Sorter.h"

namespace Containers
{
	template<typename T>
	class InsertionSorter : public Sorter<T>
	{
	private:
		std::vector<std::pair<size_t, size_t>> swaps{};
		std::string name = "Insertion Sort";
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
		InsertionSorter<T>* Clone() const override;
	};

	template<typename T>
	void InsertionSorter<T>::Sort(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp)
	{
		for (size_t i = 1; i < sequence.GetLength(); i++)
			for (int j = i - 1; (j >= 0) && comp(sequence.Get(j + 1), sequence.Get(j)); j--)
				sequence.Swap(j, j + 1);
	}

	template<typename T>
	void InsertionSorter<T>::SortWithSwaps(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp)
	{
		this->swaps.clear();
		for (size_t i = 1; i < sequence.GetLength(); i++)
			for (int j = i - 1; (j >= 0) && comp(sequence.Get(j + 1), sequence.Get(j)); j--)
				sequence.Swap(j, j + 1), this->swaps.emplace_back(j, j + 1);
	}

	template<typename T>
	void InsertionSorter<T>::SortWithExecution(Sequence<T>& sequence, bool& stop_execution, std::function<bool(const T&, const T&)> comp)
	{
		for (size_t i = 1; i < sequence.GetLength(); i++)
			for (int j = i - 1; (j >= 0) && comp(sequence.Get(j + 1), sequence.Get(j)); j--)
			{
				if (stop_execution)
					return;
				sequence.Swap(j, j + 1);
			}
	}

	template<typename T>
	std::vector<std::pair<size_t, size_t>> InsertionSorter<T>::GetSwaps() const
	{
		return this->swaps;
	}

	template<typename T>
	std::string InsertionSorter<T>::Name() const
	{
		return this->name;
	}

	template<typename T>
	InsertionSorter<T>* InsertionSorter<T>::Clone() const
	{
		return new InsertionSorter<T>(*this);
	}
}
