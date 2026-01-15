#pragma once

#include <IGenerator.h>
#include <ExceptionsAll.h>
#include <SmartPtr.h>

using namespace gens;

namespace containers {
    template <class T>
    class LinkedList : public Generamble<T>{
        struct Node {
            T item;
            Node* next;
            explicit Node(const T& item, Node* next = nullptr): item(item), next(next) {}
        };
        Node* head;
        Node* tail;
        size_t size;

        class LinkedListGenerator : public gens::IGenerator<T> {
            LinkedList<T>& data;
            Node* current;
            size_t pos = 0;

        public:
            explicit LinkedListGenerator(LinkedList<T>& data)
                : data(data), current(data.head) {}

            gens::IGenerator<T>& Next() override {
                if (this->HasNext()) {
                    current = current->next;
                    pos++;
                    return *this;
                }
                throw Exceptions::IndexOutOfRange();
            }

            const T& GetCurrent() const override {
                if (pos >= data.size || current == nullptr)
                    throw Exceptions::IndexOutOfRange();
                return current->item;
            }

            [[nodiscard]] bool HasNext() const override {
                return pos < data.size && current != nullptr;
            }
        };
        using Generator = LinkedList<T>::LinkedListGenerator;

    public:
        LinkedList(): head(nullptr), tail(nullptr), size(0) {}

        LinkedList(T* items, size_t count): head(nullptr), tail(nullptr), size(0) {
            for (size_t i = 0; i < count; i++) {
                Append(items[i]);
            }
        }

        LinkedList(const LinkedList<T>& list): head(nullptr), tail(nullptr), size(0) {
            Node* current = list.head;
            while (current != nullptr) {
                Append(current->item);
                current = current->next;
            }
        }

        ~LinkedList() override {
            Clear();
        }

        void Clear() {
            Node* current = head;
            while (current != nullptr) {
                Node* next = current->next;
                delete current;
                current = next;
            }

            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        T& Append(const T& item) {
            Node* newNode = new Node(item);
            if (size == 0) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode  ;
            }
            size++;
            return newNode->item;
        }

        void Prepend(const T& item) {
            Node* newNode = new Node(item);
            if (size == 0) {
                head = newNode;
                tail = newNode;
            } else {
                newNode->next = head;
                head = newNode;
            }
            size++;
        }

        T GetFirst() {
            if (size == 0) {
                throw Exceptions::ContainerIsEmpty();
            }

            return head->item;
        }

        T GetLast() {
            if (size == 0) {
                throw Exceptions::ContainerIsEmpty();
            }

            return tail->item;
        }

        [[nodiscard]] size_t GetLength() const {
            return size;
        }

        T Get(size_t index) {
            if (index >= size) {
                throw Exceptions::InvalidIndex();
            }

            Node* current = head;
            for (size_t i = 0; i < index; i++) {
                current = current->next;
            }

            return current->item;
        }

        LinkedList<T>* GetSubList(size_t startIndex, size_t endIndex) {
            if (startIndex >= size || endIndex >= size) {
                throw Exceptions::InvalidIndex();
            }

            if (startIndex > endIndex) {
                throw Exceptions::IndexOutOfRange();
            }

            auto* subList = new LinkedList<T>();
            Node* current = head;
            for (size_t i = 0; i <= endIndex; i++) {
                if (i >= startIndex) {
                    subList->Append(current->item);
                }
                current = current->next;
            }

            return subList;
        }

        void InsertAt(const T& item, size_t index) {
            if (index > size) {
                throw Exceptions::InvalidIndex();
            }

            if (index == 0) {
                Prepend(item);
                return;
            }

            if (index == size) {
                Append(item);
                return;
            }

            Node* prev = head;
            for (size_t i = 0; i < index - 1; i++) {
                prev = prev->next;
            }

            Node* newNode = new Node(item, prev->next);
            prev->next = newNode;
            size++;
        }

        void RemoveAt(size_t index) {
            if (index >= size) {
                throw Exceptions::InvalidIndex();
            }

            if (index == 0) {
                Node* toDelete = head;
                head = head->next;
                delete toDelete;

                if (size == 1) {
                    tail = nullptr;
                }
            } else {
                Node* prev = head;
                for (size_t i = 0; i < index - 1; i++) {
                    prev = prev->next;
                }

                Node* toDelete = prev->next;
                prev->next = toDelete->next;

                if (index == size - 1) {
                    tail = prev;
                }

                delete toDelete;
            }

            size--;
        }

        void Concat(const LinkedList<T>& other) {
            Node* current = other.head;
            while (current != nullptr) {
                Append(current->item);
                current = current->next;
            }
        }

        T& operator[](size_t index) {
            if (index >= size) throw Exceptions::InvalidIndex();
            Node* current = head;
            for (size_t i = 0; i < index; i++) {
                current = current->next;
            }
            return current->item;
        }

        const T& operator[](size_t index) const {  // const-версия
            if (index >= size) throw Exceptions::InvalidIndex();
            Node* current = head;
            for (size_t i = 0; i < index; i++) {
                current = current->next;
            }
            return current->item;
        }

        GeneratorT<T> GetGenerator() override
        {
            return smartptr::MakeUnique<Generator>(*this);
        }

        GeneratorT<T> GetGenerator() const {
            return smartptr::MakeUnique<Generator>(
                const_cast<LinkedList<T>&>(*this)
            );
        }

    };
}


