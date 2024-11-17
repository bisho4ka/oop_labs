#include <iostream>
#include <string>
#include <memory_resource>
#include "include/list.h"
#include "include/memory_resource.h"

struct ComplexType {
    int num;
    std::string lesson;

    ComplexType(int num, std::string lesson) : num(num), lesson(std::move(lesson)) {}
    
    friend std::ostream& operator<<(std::ostream& os, const ComplexType& block) {
        return os << block.num << ". " << block.lesson << std::endl;
    }

    bool operator==(const ComplexType& other) const {
        return num == other.num && lesson == other.lesson;
    }
};

int main() {
    MemoryResource<1024> resource;
    std::pmr::polymorphic_allocator<int> alloc_int(&resource);
    std::pmr::polymorphic_allocator<ComplexType> alloc_complex(&resource);

    LinkedList<int, decltype(alloc_int)> list(alloc_int);

    list.push_front(5);
    list.push_front(2);
    list.push_front(1);

    std::cout << "Первый элемент: " << list.front() << std::endl;
    std::cout << "Последний элемент: " << list.back() << std::endl;
    
    list.push_after(4, 1);
    list.push_after(3, 1);

    list.push_back(6);
    list.push_back(7);

    std::cout << "Однонаправленный список:" << std::endl;
    list.print();

    list.remove_front();
    list.remove_back();

    list.remove_after(0);

    std::cout << "Однонаправленный список после удаления:" << std::endl;
    list.print();



    LinkedList<ComplexType, decltype(alloc_complex)> list_complex(alloc_complex);
    list_complex.push_front({3, "Психология"});
    list_complex.push_front({1, "Физкультура"});

    list_complex.push_after({2, "ООП"}, 0);
    list_complex.push_after({3, "Операционные системы"}, 1);

    list_complex.push_back({4, "Математический анализ"});
    list_complex.push_back({5, "Физика"});

    std::cout << "Однонаправленный список:" << std::endl;
    std::cout << " ";
    list_complex.print();

    list_complex.remove_front();
    list_complex.remove_back();

    list_complex.remove_after(0);

    std::cout << "Однонаправленный список после удаления:" << std::endl;
    std::cout << " ";
    list_complex.print();

    return 0;
}