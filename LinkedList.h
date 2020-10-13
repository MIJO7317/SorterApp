#pragma once
#include <iterator>
#include <utility>

namespace Containers
{
	template<typename T>
	class LinkedList
	{
	private:
		struct Node
		{
			T data;
			Node* next;
			Node* prev;
		};

		Node* head; //Первый элемент списка
		Node* tail; //Элемент следующий за последним элементом списка
		size_t size;

	public:
		//Класс итератора:
		template<class Iter>
		class LinkedListIterator : public std::iterator<std::bidirectional_iterator_tag, Iter>
		{
			friend class LinkedList;
			Iter* ptr; //Указатель на Node
		private:
			//Приватный конструктор (для LinkedList):
			LinkedListIterator(Iter* ptr) : ptr(ptr) {}
		public:
			//Копирующий конструктор:
			LinkedListIterator(const LinkedListIterator& it) : ptr(it.ptr) {}
			//Операторы:
			LinkedListIterator<Iter>& operator=(const LinkedListIterator& other);
			bool operator==(const LinkedListIterator& other) const;
			bool operator!=(const LinkedListIterator& other) const;
			T& operator*();
			LinkedListIterator<Iter>& operator++();//Префикс
			LinkedListIterator<Iter>& operator--();//Префикс
			LinkedListIterator<Iter> operator++(int);//Постфикс
			LinkedListIterator<Iter> operator--(int);//Постфикс
		};
		//Для работы итератора со стандартными алгоритмами:
		using iterator = LinkedListIterator<Node>;
		//Конструкторы:
		LinkedList();
		LinkedList(size_t count, const T& value);
		LinkedList(const LinkedList& other);
		LinkedList(LinkedList&& other);
		LinkedList(std::initializer_list<T> init);
		//Доступ к элементам:
		T& Front();
		T& Back();
		const T& Front() const;
		const T& Back() const;
		//Вместимость:
		size_t Size() const;
		//Модификаторы:
		void Clear();
		iterator Insert(iterator pos, const T& value);
		iterator Insert(iterator pos, T&& value);
		iterator Erase(iterator pos);
		void PushBack(const T& value);
		void PushFront(const T& value);
		void PushBack(T&& value);
		void PushFront(T&& value);
		void PopBack();
		void PopFront();
		LinkedList<T>& operator=(const LinkedList<T>& other);
		LinkedList<T>& operator=(LinkedList<T>&& other);
		LinkedList<T>& operator=(std::initializer_list<T> init);
		//Итераторы:
		iterator begin();
		iterator end();
		//Деструктор:
		~LinkedList();
	};

	//Методы итератора:

	template<typename T>
	template<class Iter>
	LinkedList<T>::LinkedListIterator<Iter>& LinkedList<T>::LinkedListIterator<Iter>::operator=(const LinkedListIterator& other)
	{
		if (this != &other)
			this->ptr = other.ptr;
		return *this;
	}

	template<typename T>
	template<class Iter>
	bool LinkedList<T>::LinkedListIterator<Iter>::operator==(const LinkedListIterator& other) const
	{
		return this->ptr == other.ptr;
	}

	template<typename T>
	template<class Iter>
	bool LinkedList<T>::LinkedListIterator<Iter>::operator!=(const LinkedListIterator& other) const
	{
		return this->ptr != other.ptr;
	}

	template<typename T>
	template<class Iter>
	T& LinkedList<T>::LinkedListIterator<Iter>::operator*()
	{
		if (this->ptr->next == nullptr)
			throw std::exception("Can't dereference out of range LinkedList iterator");
		return this->ptr->data;
	}

	template<typename T>
	template<class Iter>
	LinkedList<T>::LinkedListIterator<Iter>& LinkedList<T>::LinkedListIterator<Iter>::operator++()
	{
		if (this->ptr->next == nullptr)
			throw std::exception("Can't increment LinkedList iterator past end");
		this->ptr = this->ptr->next;
		return *this;
	}

	template<typename T>
	template<class Iter>
	LinkedList<T>::LinkedListIterator<Iter>& LinkedList<T>::LinkedListIterator<Iter>::operator--()
	{
		if (this->ptr->prev == nullptr)
			throw std::exception("Can't decrement LinkedList iterator before begin");
		this->ptr = this->ptr->prev;
		return *this;
	}

	template<typename T>
	template<class Iter>
	LinkedList<T>::LinkedListIterator<Iter> LinkedList<T>::LinkedListIterator<Iter>::operator++(int)
	{
		LinkedListIterator<Iter> temp{ *this };
		++(*this);
		return temp;
	}

	template<typename T>
	template<class Iter>
	LinkedList<T>::LinkedListIterator<Iter> LinkedList<T>::LinkedListIterator<Iter>::operator--(int)
	{
		LinkedListIterator<Iter> temp{ *this };
		--(*this);
		return temp;
	}

	//Методы LinkedList

	template<typename T>
	LinkedList<T>::LinkedList() : size(0)
	{
		this->head = this->tail = new Node;
		this->tail->next = nullptr;
		this->head->prev = nullptr;
	}

	template<typename T>
	LinkedList<T>::LinkedList(size_t count, const T& value) : LinkedList()
	{
		for (size_t i = 0; i < count; i++)
			this->PushBack(value);
	}

	template<typename T>
	LinkedList<T>::LinkedList(const LinkedList& other) : LinkedList()
	{
		for (auto el : const_cast<LinkedList&>(other))//Нет const_iterator
			this->PushBack(el);
	}

	template<typename T>
	LinkedList<T>::LinkedList(LinkedList&& other)
	{
		this->size = other.size;
		this->head = other.head;
		this->tail = other.tail;
		other.size = 0;
		other.tail = nullptr;
		other.head = nullptr;
	}

	template<typename T>
	LinkedList<T>::LinkedList(std::initializer_list<T> init) : LinkedList()
	{
		for (auto el : init)
			this->PushBack(el);
	}

	template<typename T>
	T& LinkedList<T>::Front()
	{
		return *this->begin();
	}

	template<typename T>
	T& LinkedList<T>::Back()
	{
		if (std::prev(this->end()) == nullptr)
			throw std::exception("Back called on empty LinkedList");
		return *std::prev(this->end());
	}

	template<typename T>
	const T& LinkedList<T>::Front() const
	{
		return *const_cast<LinkedList*>(this)->begin();//Нет const_iterator
	}

	template<typename T>
	const T& LinkedList<T>::Back() const
	{
		if (std::prev(const_cast<LinkedList*>(this)->end()) == nullptr)//Нет const_iterator
			throw std::exception("Back called on empty LinkedList");
		return *std::prev(const_cast<LinkedList*>(this)->end());
	}

	template<typename T>
	size_t LinkedList<T>::Size() const
	{
		return this->size;
	}

	template<typename T>
	void LinkedList<T>::Clear()
	{
		size_t list_size = this->size;
		for (size_t i = 0; i < list_size; i++)
			this->Erase(this->begin());
		this->size = 0;
	}

	template<typename T>
	typename LinkedList<T>::iterator LinkedList<T>::Insert(iterator pos, const T& value)
	{
		this->size++;
		Node* new_node = new Node;
		new_node->data = value;
		new_node->prev = pos.ptr->prev;
		new_node->next = pos.ptr;
		pos.ptr->prev = new_node;
		if (new_node->prev == nullptr)
			this->head = new_node;
		else
			new_node->prev->next = new_node;
		return iterator(new_node);
	}

	template<typename T>
	typename LinkedList<T>::iterator LinkedList<T>::Insert(iterator pos, T&& value)
	{
		this->size++;
		Node* new_node = new Node;
		new_node->data = std::move(value);
		new_node->prev = pos.ptr->prev;
		new_node->next = pos.ptr;
		pos.ptr->prev = new_node;
		if (new_node->prev == nullptr)
			this->head = new_node;
		else
			new_node->prev->next = new_node;
		return iterator(new_node);
	}

	template<typename T>
	typename LinkedList<T>::iterator LinkedList<T>::Erase(iterator pos)
	{
		if (pos == this->end())
			throw std::exception("Can't delete iterator end of the LinkedList");
		pos.ptr->next->prev = pos.ptr->prev;
		if (pos.ptr->prev == nullptr)
			this->head = pos.ptr->next;
		else
			pos.ptr->prev->next = pos.ptr->next;
		Node* ptr_next = pos.ptr->next;
		delete pos.ptr;
		this->size--;
		return iterator(ptr_next);
	}

	template<typename T>
	void LinkedList<T>::PushBack(const T& value)
	{
		this->Insert(this->end(), value);
	}

	template<typename T>
	void LinkedList<T>::PushFront(const T& value)
	{
		this->Insert(this->begin(), value);
	}

	template<typename T>
	void LinkedList<T>::PushBack(T&& value)
	{
		this->Insert(this->end(), std::move(value));
	}

	template<typename T>
	void LinkedList<T>::PushFront(T&& value)
	{
		this->Insert(this->begin(), std::move(value));
	}

	template<typename T>
	void LinkedList<T>::PopBack()
	{
		if (std::prev(this->end()) == nullptr)
			throw std::exception("PopBack called on empty list");
		this->Erase(std::prev(this->end()));
	}

	template<typename T>
	void LinkedList<T>::PopFront()
	{
		this->Erase(this->begin());
	}

	template<typename T>
	LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other)
	{
		if (this == &other)
			return *this;
		this->Clear();
		for (auto el : const_cast<LinkedList&>(other))//Нет const_iterator
			this->PushBack(el);
		return *this;
	}

	template<typename T>
	LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other)
	{
		if (this == &other)
			return *this;
		this->Clear();
		Node* delete_tail = this->tail;
		this->size = other.size;
		this->head = other.head;
		this->tail = other.tail;
		other.size = 0;
		other.head = delete_tail;
		other.tail = delete_tail;
		return *this;
	}

	template<typename T>
	LinkedList<T>& LinkedList<T>::operator=(std::initializer_list<T> init)
	{
		this->Clear();
		for (auto el : init)
			this->PushBack(el);
		return *this;
	}

	template<typename T>
	typename LinkedList<T>::iterator LinkedList<T>::begin()
	{
		return iterator(head);
	}

	template<typename T>
	typename LinkedList<T>::iterator LinkedList<T>::end()
	{
		return iterator(tail);
	}

	template<typename T>
	LinkedList<T>::~LinkedList()
	{
		this->Clear();
		delete this->tail;
	}
}