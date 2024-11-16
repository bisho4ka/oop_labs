#pragma once
#include <iostream>
#include <memory>
#include <memory_resource>
#include <exception>

template <typename T, typename Allocator = std::pmr::polymorphic_allocator<T>>
class LinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;

        Node(const Allocator& alloc, const T& value) : data(value), next(nullptr) {}
        Node(const Allocator& alloc, T&& value) : data(std::move(value)), next(nullptr) {}
    };

    size_t size;
    Allocator allocator;
    std::unique_ptr<Node> head;
    
public:
    LinkedList(const Allocator& alloc = Allocator()) : head(nullptr), allocator(alloc), size(0) {}

    ~LinkedList() = default;

    Node* find_node(size_t index) {
        if (index >= size)
            throw std::out_of_range("Неподходящий индекс");
        Node* current = head.get();

        for (size_t i = 0; i < index; i++) 
            current = current->next.get();
        return current; 
    }

    bool operator==(const LinkedList& other) const {
        if (size != other.size) 
            return false;
        Node* current1 = head.get();
        Node* current2 = other.head.get();

        while (current1 && current2) {
            if (current1->data != current2->data) 
                return false;
            current1 = current1->next.get();
            current2 = current2->next.get();
        }
        return true;
    }

    bool operator!=(const LinkedList& other) const {
        return !(*this == other);
    }

    void push_front(const T& value) {
        auto new_node = std::make_unique<Node>(allocator, value);
        new_node->next = std::move(head);
        head = std::move(new_node);
        size++;
    }

    void remove_front() {
        if (!head) 
            throw std::out_of_range("Список пуст");
        head = std::move(head->next);
        size--;
    }

    void push_after(const T& value, size_t index) {
        if (index >= size) 
            throw std::invalid_argument("Добавить узел невозможно");
        Node* prev_node = find_node(index); // Используем вспомогательную функцию
        auto new_node = std::make_unique<Node>(allocator, value);
        new_node->next = std::move(prev_node->next);
        prev_node->next = std::move(new_node);
        size++;
    }

    void remove_after(size_t index) {
        if (index >= size - 1) 
            throw std::invalid_argument("Удалить узел невозможно");
        Node* prev_node = find_node(index);
        if (!prev_node || !prev_node->next) 
            throw std::invalid_argument("Удалить узел невозможно");
        prev_node->next = std::move(prev_node->next->next);
        size--;
    }

    void push_back(const T& value) {
        if (head == nullptr) {
            push_front(value);
            return;
        }
        Node* current = head.get();
        while (current->next) 
            current = current->next.get();
        auto new_node = std::make_unique<Node>(allocator, value);
        current->next = std::move(new_node);
        size++;
    }

    void remove_back() {
        if (!head)
            throw std::out_of_range("Список пуст");
        Node* current = head.get();
        while (current->next->next != nullptr)
            current = current->next.get();
        current->next.reset();
        size--;
    }

    T front() const {
        if (!head) 
            throw std::out_of_range("Список пуст");
        return head->data;
    }

    T back() const {
        if (!head) 
            throw std::out_of_range("Список пуст");
        Node* current = head.get();
        while (current->next != nullptr)
            current = current->next.get();
        return current->data;
    }

    bool empty() const noexcept {
        return size == 0;
    }

    size_t get_size() const noexcept {
        return size;
    }

    void clear() {
        head.reset();
        size = 0;
    }

    void print() const {
        Node* current = head.get();
        while (current) {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }

    class Iterator;

    Iterator begin() { 
        return Iterator(head.get()); 
    }

    Iterator end() { 
        return Iterator(nullptr); 
    }

};

template<typename T, typename Allocator>
class LinkedList <T, Allocator>::Iterator {
private:
    Node* current;
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    Iterator(Node* node) : current(node) {}

    reference operator*() { 
        return current->data; 
    }

    pointer operator->() {
        return &current->data;
    }

    Iterator& operator++() {
        if (current) 
            current = current->next.get();
        return *this;
    }

    Iterator operator++(int) {
        Iterator it = *this;
        (*this)++;
        return it;
    }

    bool operator==(const Iterator& other) const { 
        return current == other.current; 
    }

    bool operator!=(const Iterator& other) const { 
        return current != other.current; 
    }
};