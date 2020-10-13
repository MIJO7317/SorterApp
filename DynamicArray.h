#pragma once
#include <optional>

namespace Containers
{
	constexpr size_t DEFAULT_BUFFER_SIZE = 32;
	//DynamicArray {a,b,c,d,e,f,g} approximate scheme:
	//[][][][][][][] [a][b][c][d][e][f][g] [][][][][][][][]
	//_l_additional__________count___________r_additional__ } - capacity
	//______=7________________=7__________________=8_______       =22

	template<typename T>
	class DynamicArray
	{
	public:
		//Конструкторы:
		DynamicArray(size_t size = 0);
		DynamicArray(size_t size, const T& default_element);
		DynamicArray(const T* const arr, size_t count, size_t start = 0);
		DynamicArray(const DynamicArray<T>& other);
		DynamicArray(DynamicArray<T>&& other);
		DynamicArray(std::initializer_list<T> init);
		//Доступ к элементам:
		std::optional<T>& At(size_t index);
		std::optional<T> At(size_t index) const;
		std::optional<T>& operator[](size_t index);
		const std::optional<T>& operator[](size_t index) const;
		std::optional<T>& Front();
		std::optional<T>& Back();
		std::optional<T> Front() const;
		std::optional<T> Back() const;
		std::optional<T>* Data();
		//Вместимость:
		DynamicArray<T>& Resize(size_t new_size);
		size_t Size() const;
		size_t Capacity() const;
		bool Empty() const;
		//Модификаторы:
		DynamicArray<T>& PushFront(const T& element);
		DynamicArray<T>& PushBack(const T& element);
		DynamicArray<T>& Insert(size_t index, const T& element, size_t count = 1);
		DynamicArray<T>& PopFront();
		DynamicArray<T>& PopBack();
		DynamicArray<T>& Erase(size_t index, size_t count = 1);
		DynamicArray<T>& Clear();
		DynamicArray<T>& operator=(const DynamicArray<T>& other);
		DynamicArray<T>& operator=(DynamicArray<T>&& other);
		//Деструктор:
		~DynamicArray() { delete[] this->data; }
	private:
		std::optional<T>* data;
		size_t l_additional;
		size_t r_additional;
		size_t count;
		size_t r_buffer;
		size_t l_buffer;
	};

	template<typename T>
	DynamicArray<T>::DynamicArray(size_t size)
	{
		this->l_buffer = this->r_buffer = DEFAULT_BUFFER_SIZE;
		this->l_additional = this->l_buffer;
		this->r_additional = this->r_buffer;
		this->count = size;
		try
		{
			this->data = new std::optional<T>[this->Capacity()];
		}
		catch (const std::bad_alloc& exc)
		{
			throw exc.what();
		}
	}

	template<typename T>
	DynamicArray<T>::DynamicArray(size_t size, const T& default_element) : DynamicArray(size)
	{
		for (size_t i = 0; i < this->count; i++)
			this->data[i + this->l_additional] = default_element;
	}

	template<typename T>
	DynamicArray<T>::DynamicArray(const T* const arr, size_t count, size_t start) : DynamicArray(count)
	{
		for (size_t i = 0; i < this->count; i++)
		{
			this->data[i + this->l_additional] = arr[i + start];
		}
	}

	template<typename T>
	DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) : DynamicArray(other.count)
	{
		for (size_t i = 0; i < this->count; i++)
		{
			this->data[i + this->l_additional] = other.data[i + other.l_additional];
		}
	}

	template<typename T>
	DynamicArray<T>::DynamicArray(DynamicArray<T>&& other)
	{
		this->data = other.data;
		other.data = nullptr;
		this->l_additional = other.l_additional;
		this->r_additional = other.r_additional;
		this->count = other.count;
		this->r_buffer = other.r_buffer;
		this->l_buffer = other.l_buffer;
	}

	template<typename T>
	DynamicArray<T>::DynamicArray(std::initializer_list<T> init) : DynamicArray(init.size())
	{
		for (size_t i = 0; i < init.size(); i++)
		{
			this->data[i + this->l_additional] = *(init.begin() + i);
		}
	}

	template<typename T>
	std::optional<T>& DynamicArray<T>::At(size_t index)
	{
		if (index >= this->count)
			throw std::exception("Out of range");
		return this->data[index + this->l_additional];
	}

	template<typename T>
	std::optional<T> DynamicArray<T>::At(size_t index) const
	{
		if (index >= this->count)
			throw std::exception("Out of range");
		return this->data[index + this->l_additional];
	}

	template<typename T>
	DynamicArray<T>& DynamicArray<T>::Resize(size_t new_size)
	{
		if (new_size > this->Capacity())
		{
			std::optional<T>* new_data;
			//Выделение памяти под новый массив
			try
			{
				new_data = new std::optional<T>[new_size + this->l_additional + this->r_additional];
			}
			catch (const std::bad_alloc& exc)
			{
				throw exc.what();
			}
			//Заполнение нового массива значениями из старого
			for (size_t i = 0; i < this->count; i++)
				new_data[i + this->l_additional] = this->data[i + this->l_additional];
			//Удаление старого массива
			delete[] this->data;
			//Присвоение нового массива старому
			this->data = new_data;
		}
		else
		{
			for (size_t i = new_size; i < this->count; i++)
				this->data[i + this->l_additional] = std::nullopt;
			this->r_additional += this->count - new_size;
		}
		this->count = new_size;
		return *this;
	}

	template<typename T>
	size_t DynamicArray<T>::Size() const
	{
		return this->count;
	}

	template<typename T>
	size_t DynamicArray<T>::Capacity() const
	{
		return this->count + this->l_additional + this->r_additional;
	}

	template<typename T>
	bool DynamicArray<T>::Empty() const
	{
		for (size_t i = 0; i < this->count; i++)
			if (this->data[i + this->l_additional] != std::nullopt)
				return false;
		return true;
	}

	template<typename T>
	DynamicArray<T>& DynamicArray<T>::PushFront(const T& element)
	{
		if (l_additional != 0)
		{
			this->data[--l_additional] = element;
		}
		else
		{
			std::optional<T>* new_data;
			//Удвоение буффера
			this->l_buffer *= 2;
			//Изменение вместимости
			this->l_additional = this->l_buffer;
			//Выделение памяти под новый массив
			try
			{
				new_data = new std::optional<T>[this->Capacity() + 1];
			}
			catch (const std::bad_alloc& exc)
			{
				throw exc.what();
			}
			//Заполнение первой ячейки нового массива
			new_data[this->l_additional] = element;
			//Заполнение нового массива значениями из старого
			for (size_t i = 0; i < this->count; i++)
				new_data[i + 1 + this->l_additional] = this->data[i];
			//Удаление старого массива
			delete[] this->data;
			//Присвоение нового массива старому
			this->data = new_data;
		}
		this->count++;
		return *this;
	}

	template<typename T>
	DynamicArray<T>& DynamicArray<T>::PushBack(const T& element)
	{
		if (r_additional != 0)
		{
			this->data[this->l_additional + this->count] = element;
			r_additional--;
		}
		else
		{
			std::optional<T>* new_data;
			//Удвоение буффера
			this->r_buffer *= 2;
			//Изменение вместимости
			this->r_additional = this->r_buffer;
			//Выделение памяти под новый массив
			try
			{
				new_data = new std::optional<T>[this->Capacity() + 1];
			}
			catch (const std::bad_alloc& exc)
			{
				throw exc.what();
			}
			//Заполнение нового массива значениями из старого
			for (size_t i = 0; i < this->count; i++)
				new_data[i + this->l_additional] = this->data[i + this->l_additional];
			//Заполнение последней ячейки нового массива
			new_data[this->l_additional + this->count] = element;
			//Удаление старого массива
			delete[] this->data;
			//Присвоение нового массива старому
			this->data = new_data;
		}
		this->count++;
		return *this;
	}

	template<typename T>
	DynamicArray<T>& DynamicArray<T>::Insert(size_t index, const T& element, size_t count)
	{
		if (index > this->count)
			throw std::exception("Invalid index");
		if (index == this->count)
			return this->PushBack(element);
		if (this->l_additional + this->r_additional >= count)
		{
			size_t r_shift = this->r_additional >= count ? count : this->r_additional;
			size_t l_shift = count - r_shift;
			for (int i = this->count - 1; i >= index; i--)
				std::swap(this->data[i + this->l_additional], this->data[i + this->l_additional + r_shift]);
			if (l_shift)
				for (size_t i = 0; i < index; i++)
					std::swap(this->data[i + this->l_additional], this->data[i + this->l_additional - l_shift]);
			this->l_additional -= l_shift;
			this->r_additional -= r_shift;
			for (size_t i = index; i < index + count; i++)
				this->data[i + this->l_additional] = element;
		}
		else
		{
			std::optional<T>* new_data;
			//Удвоение буффера
			this->r_buffer *= 2;
			this->l_buffer *= 2;
			//Выделение памяти под новый массив
			try
			{
				new_data = new std::optional<T>[this->count + count + this->l_buffer + this->r_buffer];
			}
			catch (const std::bad_alloc& exc)
			{
				throw exc.what();
			}
			//Заполнение нового массива значениями из старого
			for (size_t i = 0; i < index; i++)
				new_data[i + this->l_buffer] = this->data[i + this->l_additional];
			//Заполнение нового массива передаваемыми элементами
			for (size_t i = index; i < index + count; i++)
				new_data[i + this->l_buffer] = element;
			//Заполнение нового массива значениями из старого
			for (size_t i = index + count; i < this->count + count; i++)
				new_data[i + this->l_buffer] = this->data[i - count + this->l_additional];
			//Удаление старого массива
			delete[] this->data;
			//Присвоение нового массива старому
			this->data = new_data;
			//Изменение вместимости
			this->l_additional = this->l_buffer;
			this->r_additional = this->r_buffer;
		}
		this->count += count;
		return *this;
	}

	template<typename T>
	DynamicArray<T>& DynamicArray<T>::PopFront()
	{
		if (this->count-- == 0)
			throw std::exception("Array is empty");
		this->data[this->l_additional++] = std::nullopt;
		return *this;
	}

	template<typename T>
	DynamicArray<T>& DynamicArray<T>::PopBack()
	{
		if (this->count == 0)
			throw std::exception("Array is empty");
		this->data[this->l_additional + --this->count] = std::nullopt;
		this->r_additional++;
		return *this;
	}

	template<typename T>
	DynamicArray<T>& DynamicArray<T>::Erase(size_t index, size_t count)
	{
		if (index + count > this->count)
			throw std::exception("Out of range");
		for (size_t i = index; i < index + count; i++)
			this->data[i + this->l_additional] = std::nullopt;
		size_t r_shift = count / 2;
		size_t l_shift = count - r_shift;
		if (r_shift)
			for (size_t i = index + count; i < this->count; i++)
				std::swap(this->data[i + this->l_additional], this->data[i + this->l_additional - r_shift]);
		for (int i = index - 1; i >= 0; i--)
			std::swap(this->data[i + this->l_additional], this->data[i + this->l_additional + l_shift]);
		this->l_additional += l_shift;
		this->r_additional += r_shift;
		this->count -= l_shift + r_shift;
		return *this;
	}

	template<typename T>
	DynamicArray<T>& DynamicArray<T>::Clear()
	{
		for (size_t i = 0; i < this->count; i++)
			this->data[i + this->l_additional] = std::nullopt;
		size_t l_additional_add = this->count / 2;
		size_t r_additional_add = this->count - l_additional_add;
		this->l_additional += l_additional_add;
		this->r_additional += r_additional_add;
		this->count = 0;
		return *this;
	}

	template<typename T>
	DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other)
	{
		if (this == &other)
			return *this;
		if (this->Capacity() < other.count)
		{
			delete[] this->data;
			try
			{
				this->data = new std::optional<T>[other.count + this->r_additional + this->l_additional];
			}
			catch (const std::bad_alloc& exc)
			{
				throw exc.what();
			}
		}
		else
		{
			size_t l_additional_new = (this->Capacity() - other.count) / 2;
			size_t r_additional_new = this->Capacity() - other.count - l_additional_new;

			this->l_additional = l_additional_new;
			this->r_additional = r_additional_new;

			for (size_t i = 0; i < this->l_additional; i++)
				this->data[i] = std::nullopt;
			for (size_t i = this->l_additional + other.count; i < this->l_additional + this->r_additional + other.count; i++)
				this->data[i] = std::nullopt;
		}
		for (size_t i = 0; i < other.count; i++)
			this->data[i + this->l_additional] = other.data[i + other.l_additional];
		this->count = other.count;
		return *this;
	}

	template<typename T>
	DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other)
	{
		if (this == &other)
			return *this;
		delete[] this->data;
		this->data = other.data;
		other.data = nullptr;
		this->l_additional = other.l_additional;
		this->r_additional = other.r_additional;
		this->count = other.count;
		return *this;
	}

	template<typename T>
	std::optional<T>& DynamicArray<T>::operator[](size_t index)
	{
		if (index >= this->count)
			throw std::exception("Invalid index");
		return this->data[index + this->l_additional];
	}

	template<typename T>
	const std::optional<T>& DynamicArray<T>::operator[](size_t index) const
	{
		if (index >= this->count)
			throw std::exception("Invalid index");
		return this->data[index + this->l_additional];
	}

	template<typename T>
	std::optional<T>& DynamicArray<T>::Front()
	{
		if (this->count == 0)
			throw std::exception("Array is empty");
		return this->data[this->l_additional];
	}

	template<typename T>
	std::optional<T>& DynamicArray<T>::Back()
	{
		if (this->count == 0)
			throw std::exception("Array is empty");
		return this->data[this->l_additional + this->count - 1];
	}

	template<typename T>
	std::optional<T> DynamicArray<T>::Front() const
	{
		if (this->count == 0)
			throw std::exception("Array is empty");
		return this->data[this->l_additional];
	}

	template<typename T>
	std::optional<T> DynamicArray<T>::Back() const
	{
		if (this->count == 0)
			throw std::exception("Array is empty");
		return this->data[this->l_additional + this->count - 1];
	}

	template<typename T>
	std::optional<T>* DynamicArray<T>::Data()
	{
		if (this->count == 0)
			throw std::exception("Array is empty");
		return this->data + this->l_additional;
	}
}

