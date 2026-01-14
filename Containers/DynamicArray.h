#pragma once

#include <SmartPtr.h>
#include <ExceptionsAll.h>
#include <IGenerator.h>
#include <algorithm>

// using namespace gens;

namespace containers
{

    using gens::Generamble, gens::IGenerator, gens::GeneratorT;

    template <class T>
    class DynamicArray : public Generamble<T>
    {
        T *data;
        size_t size;
        size_t capacity;

        class DynamicArrayGenerator : public IGenerator<T>
        {
            DynamicArray<T> &data;
            size_t pos = 0;

        public:
            DynamicArrayGenerator(DynamicArray<T> &data) : data(data) {}

            IGenerator<T> &Next() override
            {
                if (this->HasNext())
                {
                    pos++;
                    return *this;
                }
                throw Exceptions::IndexOutOfRange();
            }

            const T &GetCurrent() const override
            {
                if (pos >= data.GetLength())
                    throw Exceptions ::IndexOutOfRange();
                return data.data[pos];
            }

            [[nodiscard]] bool HasNext() const override
            {
                return pos < data.GetLength();
            };
        };
        using Generator = DynamicArray<T>::DynamicArrayGenerator;

    public:
        DynamicArray() : size(0), capacity(10)
        {
            data = new T[capacity];
        }

        DynamicArray(T *items, size_t size) : size(size), capacity(size)
        {
            data = new T[capacity];
            for (size_t i = 0; i < size; i++)
            {
                data[i] = items[i];
            }
        }

        DynamicArray(std::initializer_list<T> list) : size(list.size()), capacity(list.size()),
                                                      data(static_cast<T *>(::operator new(sizeof(T) * list.size())))
        {
            std::copy(list.begin(), list.end(), data);
        }

        explicit DynamicArray(size_t size) : size(0), capacity(size)
        {
            data = new T[capacity];
        }

        DynamicArray(const DynamicArray<T> &other)
        {
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];

            for (size_t i = 0; i < size; i++)
            {
                data[i] = other.data[i];
            }
        }

        ~DynamicArray() override { delete[] data; }

        void Append(const T &item)
        {
            if (size == capacity)
            {
                Resize(capacity * 2);
            }
            data[size] = item;
            size++;
        }

        T Get(const size_t index) const
        {
            if (index >= size)
            {
                throw Exceptions ::InvalidIndex();
            }
            return data[index];
        }

        [[nodiscard]] size_t GetLength() const { return size; }

        void Set(const size_t index, const T &value)
        {
            if (index >= size)
            {
                throw Exceptions ::InvalidIndex();
            }
            data[index] = value;
        }

        void Resize(size_t newSize)
        {
            if (newSize < size)
            {
                throw Exceptions ::InvalidNewSize();
            }
            T *newData = new T[newSize];
            for (size_t i = 0; i < size; i++)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newSize;
        }

        DynamicArray &operator=(const DynamicArray<T> &other)
        {
            if (this != &other)
            {
                delete[] data;
                size = other.size;
                capacity = other.capacity;
                data = new T[capacity];
                for (size_t i = 0; i < size; i++)
                {
                    data[i] = other.data[i];
                }
            }
            return *this;
        }

        T &operator[](size_t index)
        {
            if (index >= size)
                throw Exceptions ::InvalidIndex();
            return data[index];
        }

        GeneratorT<T> GetGenerator() override
        {
            return smartptr::MakeUnique<Generator>(*this);
        }

    };

} // namespace containers
