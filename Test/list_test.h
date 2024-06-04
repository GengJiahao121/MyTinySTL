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
    mystl::list<int> l2{ 1,2,3,4,5 };

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

    // 删除指定值的节点
    FUN_AFTER(l1, l1.remove(3));

    FUN_VALUE(l1.empty());

    FUN_VALUE(l1.getSize());

    FUN_VALUE(l2.getNode(2));

    for (auto it = l2.begin(); it != l2.end(); it++) {
        std::cout << it << ' '; 
    }

    FUN_AFTER(l2, l2.clear());

    FUN_VALUE(l2.getSize());









}

    
}
}
}


#endif // MyTinySTL_List_Test_H_