#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include "../include/list.h"
#include "../include/memory_resource.h"

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

TEST(Memory_resource, AllocateDeallocate) { 
    MemoryResource<1024> resource;

    EXPECT_EQ(resource.allocated_block_count(), 0);

    void* ptr1 = resource.do_allocate(128, 16);
    EXPECT_EQ(resource.allocated_block_count(), 1);

    void* ptr2 = resource.do_allocate(64, 8);
    EXPECT_EQ(resource.allocated_block_count(), 2);

    ASSERT_NE(nullptr, ptr1);
    ASSERT_NE(nullptr, ptr2);
    
    resource.deallocate(ptr1, 128, 16);
    EXPECT_EQ(resource.allocated_block_count(), 1);

    resource.deallocate(ptr2, 64, 8);
    EXPECT_EQ(resource.allocated_block_count(), 0);
}

TEST(Memory_resource, BadAllocate){
    MemoryResource<1024> resource;
    bool isBad = false;
    try {
        resource.do_allocate(1024 * 1024 * 1024, 1);
    } catch (const std::bad_alloc&) {
        isBad = true;
    }
    EXPECT_TRUE(isBad);
}

TEST(Memory_resource, IsEqual) {
    MemoryResource<1024> res_1;
    MemoryResource<1024> res_2;
    EXPECT_TRUE(res_1.do_is_equal(res_1));
    EXPECT_FALSE(res_1.do_is_equal(res_2));
}

TEST(Linked_List, PushAndRemove) { 
    MemoryResource<1024> resource;
    std::pmr::polymorphic_allocator<int> alloc_int(&resource);
    
    LinkedList<int, decltype(alloc_int)> list(alloc_int);

    list.push_front(15); 
    EXPECT_EQ(list.get_size(), 1);

    list.push_front(5); 
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.front(), 5);

    list.push_after(10, 0);
    EXPECT_EQ(list.get_size(), 3);

    list.push_back(20);
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list.back(), 20);

    list.remove_front();
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list.front(), 10);

    list.remove_after(0);
    EXPECT_EQ(list.get_size(), 2);

    list.remove_back();
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.front(), 10);
    EXPECT_EQ(list.back(), 10);
}

TEST(Linked_List, Iterators) { 
    MemoryResource<1024> resource;
    
    std::pmr::polymorphic_allocator<int> alloc_int(&resource);
    LinkedList<int, decltype(alloc_int)> list(alloc_int);
 
    list.push_front(3); 
    list.push_front(1); 
    list.push_after(2, 0); 

    auto it = list.begin(); 
    bool isTrue = true; 
    isTrue = isTrue && *it == 1; 
    ++it; 
    isTrue = isTrue && *it == 2; 
    ++it; 
    isTrue = isTrue && *it == 3; 
    ++it; 

    bool result = isTrue && it == list.end(); 
    EXPECT_TRUE(isTrue); 
} 
 
TEST(Linked_List, EmptyAndEqual) { 
    MemoryResource<1024> resource;
    std::pmr::polymorphic_allocator<int> alloc_int(&resource);
    
    LinkedList<int, decltype(alloc_int)> list_1(alloc_int);
    EXPECT_TRUE(list_1.empty());

    list_1.push_front(3); 
    EXPECT_FALSE(list_1.empty());
 
    LinkedList<int, decltype(alloc_int)> list_2(alloc_int);

    list_1.push_front(2); 
    list_1.push_front(1);
    list_1.push_front(0);

    list_2.push_back(0); 
    list_2.push_back(1); 
    list_2.push_back(2);
    list_2.push_back(3);
 
    EXPECT_TRUE(list_1 == list_2); 
    
    list_2.push_back(4); 
    EXPECT_FALSE(list_1 == list_2);  
} 

TEST(Complex_List, PushAndRemove) { 
    MemoryResource<1024> resource;
    std::pmr::polymorphic_allocator<ComplexType> alloc_complex(&resource);

    LinkedList<ComplexType, decltype(alloc_complex)> list(alloc_complex);

    list.push_front(ComplexType{3, "ООП"}); 
    EXPECT_EQ(list.get_size(), 1);

    list.push_front(ComplexType{1, "Физика"}); 
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_EQ(list.front(), (ComplexType {1, "Физика"}));

    list.push_after(ComplexType{2, "Операционные системы"}, 0);
    EXPECT_EQ(list.get_size(), 3);

    list.push_back(ComplexType{4, "Психология"});
    EXPECT_EQ(list.get_size(), 4);
    EXPECT_EQ(list.back(), (ComplexType {4, "Психология"}));

    list.remove_front();
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_EQ(list.front(), (ComplexType {2, "Операционные системы"}));

    list.remove_after(0);
    EXPECT_EQ(list.get_size(), 2);

    list.remove_back();
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_EQ(list.front(), (ComplexType {2, "Операционные системы"}));
    EXPECT_EQ(list.back(), (ComplexType {2, "Операционные системы"}));
}

TEST(Complex_List, Iterators) { 
    MemoryResource<1024> resource;
    std::pmr::polymorphic_allocator<ComplexType> alloc_complex(&resource);

    LinkedList<ComplexType, decltype(alloc_complex)> list(alloc_complex);

    list.push_front(ComplexType{3, "Операционные системы"}); 
    list.push_front(ComplexType{1, "ООП"}); 
    list.push_after(ComplexType{2, "Дифуры"}, 0); 
 
    auto it = list.begin(); 
 
    bool isTrue = true; 
    isTrue = isTrue && *it == ComplexType {1, "ООП"}; 
    ++it; 
    isTrue = isTrue && *it == ComplexType {2, "Дифуры"}; 
    ++it; 
    isTrue = isTrue && *it == ComplexType {3, "Операционные системы"};
    ++it; 
    
    bool result = isTrue && it == list.end(); 
    EXPECT_TRUE(isTrue); 
} 
 
TEST(Complex_List, EmptyAndEqual) { 
    MemoryResource<1024> resource;
    std::pmr::polymorphic_allocator<ComplexType> alloc_complex(&resource);

    LinkedList<ComplexType, decltype(alloc_complex)> list_1(alloc_complex);
    EXPECT_TRUE(list_1.empty());

    list_1.push_front(ComplexType{3, "Функ. лог. прог."}); 
    EXPECT_FALSE(list_1.empty());
 
    LinkedList<ComplexType, decltype(alloc_complex)> list_2(alloc_complex);

    list_1.push_front(ComplexType{2, "Мат. анализ"}); 
    list_1.push_front(ComplexType{1, "ОС"});
    list_1.push_front(ComplexType{0, "ООП"});

    list_2.push_back(ComplexType{0, "ООП"}); 
    list_2.push_back(ComplexType{1, "ОС"}); 
    list_2.push_back(ComplexType{2, "Мат. анализ"});
    list_2.push_back(ComplexType{3, "Функ. лог. прог."});
 
    EXPECT_TRUE(list_1 == list_2); 
    
    list_2.push_back(ComplexType{4, "Философия"}); 
    EXPECT_FALSE(list_1 == list_2);  
} 

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}