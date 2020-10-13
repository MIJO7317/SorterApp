//ShellSorter
#pragma once
#include "Sorter.h"

namespace Containers
{
	template<typename T>
	class ShellSorter : public Sorter<T>
	{
	private:
		std::vector<std::pair<size_t, size_t>> swaps{};
		std::string name = "Shell Sort"; 
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
		ShellSorter<T>* Clone() const override;
	};

	template<typename T>
	void ShellSorter<T>::Sort(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp)
	{
		for (size_t step = sequence.GetLength() / 2; step != 0; step /= 2)
			for (size_t i = step; i < sequence.GetLength(); i++)
				for (int j = i - step; (j >= 0) && comp(sequence.Get(j + step), sequence.Get(j)); j -= step)
					sequence.Swap(j, j + step);
	}

	template<typename T>
	void ShellSorter<T>::SortWithSwaps(Sequence<T>& sequence, std::function<bool(const T&, const T&)> comp)
	{
		this->swaps.clear();
		for (size_t step = sequence.GetLength() / 2; step != 0; step /= 2)
			for (size_t i = step; i < sequence.GetLength(); i++)
				for (int j = i - step; (j >= 0) && comp(sequence.Get(j + step), sequence.Get(j)); j -= step)
					sequence.Swap(j, j + step), this->swaps.emplace_back(j, j + step);
	}

	template<typename T>
	void ShellSorter<T>::SortWithExecution(Sequence<T>& sequence, bool& stop_execution, std::function<bool(const T&, const T&)> comp)
	{
		for (size_t step = sequence.GetLength() / 2; step != 0; step /= 2)
			for (size_t i = step; i < sequence.GetLength(); i++)
				for (int j = i - step; (j >= 0) && comp(sequence.Get(j + step), sequence.Get(j)); j -= step)
				{
					if (stop_execution)
						return;
					sequence.Swap(j, j + step);
				}
	}

	template<typename T>
	std::vector<std::pair<size_t, size_t>> ShellSorter<T>::GetSwaps() const
	{
		return this->swaps;
	}

	template<typename T>
	std::string ShellSorter<T>::Name() const
	{
		return this->name;
	}

	template<typename T>
	ShellSorter<T>* ShellSorter<T>::Clone() const
	{
		return new ShellSorter<T>(*this);
	}
}