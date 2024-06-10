#ifndef MyTinySTL_List_Test_H_
#define MyTinySTL_List_Test_H_

// list test : 测试 list 的接口与 insert, sort 的性能

#include <list>

#include "../MyTinySTL/list.h"
#include "test.h"

namespace mystl
{
namespace test
{
namespace list_test
{

void list_test(){

    std::cout << "[===============================================================]" << std::endl;
    std::cout << "[------------------ Run container test : list ------------------]" << std::endl;
    std::cout << "[-------------------------- API test ---------------------------]" << std::endl;

    mystl::list<int> l1;
    mystl::list<int> l2{ 5, 9, 6, 4, 1 };

    FUN_AFTER(l2, l2.insert(l2.end(), 1));
    
    // FUN_AFTER(l2, l2.sort());
    
    FUN_AFTER(l2, nullptr);

    FUN_AFTER(l1, l1.push_back(1));
    FUN_AFTER(l1, l1.push_back(2));
    FUN_AFTER(l1, l1.push_back(3));
    FUN_AFTER(l1, l1.push_back(4));
    FUN_AFTER(l1, l1.push_back(5));

    FUN_AFTER(l1, l1.pop_front());
    FUN_AFTER(l1, l1.pop_front());
    FUN_AFTER(l1, l1.pop_back());
    FUN_AFTER(l1, l1.pop_back());

    FUN_AFTER(l1, l1.insert(l1.begin(), 1));

    // 删除指定值的节点
    FUN_AFTER(l1, l1.remove(3));
    FUN_VALUE(l1.empty());
    FUN_VALUE(l1.getSize());
    FUN_VALUE(l2.getNode(2));
    FUN_AFTER(l2, l2.clear());
    FUN_VALUE(l2.getSize());
    
#if PERFORMANCE_TEST_ON
    std::cout << "[--------------------- Performance Testing ---------------------]" << std::endl;
    std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
    std::cout << "|       insert        |";
#if LARGER_TEST_DATA_ON
    CON_TEST_P2(list<int>, insert, end, rand(), SCALE_L(LEN1), SCALE_L(LEN2), SCALE_L(LEN3));
#else
    CON_TEST_P2(list<int>, insert, end, rand(), SCALE_M(LEN1), SCALE_M(LEN2), SCALE_M(LEN3));
#endif
    std::cout << std::endl;
    std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
    // std::cout << "|         sort        |";
// #if LARGER_TEST_DATA_ON
//     LIST_SORT_TEST(SCALE_M(LEN1), SCALE_M(LEN2), SCALE_M(LEN3));
// #else
//     LIST_SORT_TEST(SCALE_S(LEN1), SCALE_S(LEN2), SCALE_S(LEN3));
// #endif
//   std::cout << std::endl;
//   std::cout << "|---------------------|-------------|-------------|-------------|" << std::endl;
//   PASSED;
// #endif
  std::cout << "[------------------ End container test : list ------------------]" << std::endl;
#endif



} 
}
}
}

#endif // !MyTinySTL_List_Test_H_