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

    FUN_AFTER(l1, l1.push_back(1));
    FUN_AFTER(l1, l1.push_back(2));
    FUN_AFTER(l1, l1.push_back(3));
    FUN_AFTER(l1, l1.push_back(4));
    FUN_AFTER(l1, l1.push_back(5));












}

    
}
}
}


#endif // MyTinySTL_List_Test_H_