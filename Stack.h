#pragma once
#include "LinkedList.h"

namespace Containers
{
	template<typename T>
	class Stack
	{
	public:
		//Конструкторы:
		Stack() {} //linked_list по умолчанию инициализируется пустым списком
		Stack(const Stack<T>& other) : list(other.list) {}
		Stack(Stack<T>&& other) : list(std::move(other.list)) {}
		//Методы:
		void Push(const T& value);
		void Push(T&& value);
		void Pop();
		T& Top();
		const T& Top() const;
		bool Empty() const;
		size_t Size() const;
		void Clear();
		//Операторы:
		Stack<T>& operator=(const Stack<T>& other);
		Stack<T>& operator=(Stack<T>&& other);
	private:
		LinkedList<T> list;
	};

	template<typename T>
	void Stack<T>::Push(const T& value)
	{
		this->list.PushFront(value);
	}

	template<typename T>
	void Stack<T>::Push(T&& value)
	{
		this->list.PushFront(std::move(value));
	}

	template<typename T>
	void Stack<T>::Pop()
	{
		this->list.PopFront();
	}

	template<typename T>
	T& Stack<T>::Top()
	{
		return this->list.Front();
	}

	template<typename T>
	const T& Stack<T>::Top() const
	{
		return this->list.Front();
	}

	template<typename T>
	bool Stack<T>::Empty() const
	{
		return this->list.Size() == 0;
	}

	template<typename T>
	size_t Stack<T>::Size() const
	{
		return this->list.Size();
	}

	template<typename T>
	void Stack<T>::Clear()
	{
		this->list.Clear();
	}

	template<typename T>
	Stack<T>& Stack<T>::operator=(const Stack<T>& other)
	{
		this->list = other;
		return *this;
	}

	template<typename T>
	Stack<T>& Stack<T>::operator=(Stack<T>&& other)
	{
		this->list = std::move(other);
		return *this;
	}
}