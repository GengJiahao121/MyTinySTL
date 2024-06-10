#include "../MyTinySTL/deque.h"
#include <iostream>
#include <deque>
#include "test.h"
#include <typeinfo>

namespace mystl{

namespace test{

namespace deque_test{

void deque_test() {

    mystl::Deque<int> d1();

    /**
     * 存在前几个元素迭代器失效的问题！！！
    */

    // FUN_AFTER(d1, d1.push_back(1));
    // d1.printElements();
    // FUN_AFTER(d1, d1.push_back(2));
    // d1.printElements();
    // FUN_AFTER(d1, d1.push_back(3));
    // d1.printElements();
    // FUN_AFTER(d1, d1.push_back(4));
    // d1.printElements();

    // for (auto it = d1.begin(); it != d1.end(); ++it) {

    //     auto value = *it;
    //     std::cout << value << std::endl;
    // }


    // d1.printElements();
    // FUN_AFTER(d1, d1.push_back(3));
    // FUN_AFTER(d1, d1.push_front(3));
    // FUN_AFTER(d1, d1.push_front(4));
    // FUN_AFTER(d1, d1.push_front(5));

    // FUN_AFTER(d1, d1.pop_back());
    // FUN_AFTER(d1, d1.pop_front());

    // FUN_VALUE(d1[0]);
    // FUN_VALUE(d1[1]);
    // FUN_VALUE(d1[2]);

    // FUN_VALUE(d1.getSize());

    // FUN_AFTER(d1, d1.printElements());

    // 测试迭代器
    // mystl::Deque<int>::iterator it = d1.begin();
    // std::cout << it << std::endl;
    // FUN_VALUE(*it);
    // FUN_VALUE(*(it+=1));
    // it = it + 1;
    // FUN_VALUE(*it);

    // FUN_AFTER(d1, d1.clear());
        






}

}
}
}