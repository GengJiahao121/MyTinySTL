#ifndef MYTINYSTL_VECTOR_TEST_H_
#define MYTINYSTL_VECTOR_TEST_H_

// vector test : 测试 vector 的接口与 push_back 的性能

#include <vector>

#include "../MyTinySTL/vector.h"
#include "test.h"

namespace mystl
{
namespace test
{
namespace vector_test
{
    void vector_test(){
        std::cout << "[===============================================================]\n";
        std::cout << "[----------------- Run container test : vector -----------------]\n";
        std::cout << "[-------------------------- API test ---------------------------]\n";

        mystl::vector<int> v1;
        mystl::vector<int> v2(v1);
        mystl::vector<int> v3 = v2;

        // 测试 push_back
        FUN_AFTER(v1, v1.push_back(20));
        FUN_AFTER(v1, v1.push_back(30));
        FUN_AFTER(v1, v1.push_back(40));
        /*
        std::cout << "push_back test : \n";
        v1.push_back(20);
        v1.push_back(30);
        v1.push_back(40);
        */
        

        // 测试print
        FUN_AFTER(v1, v1.printElements());
        /*
        std::cout << "print test : \n";
        v1.printElements();
        */
        

        // 测试insert
        FUN_AFTER(v1, v1.insert(0, 10));
        /*
        std::cout << "insert test : \n";
        v1.insert(0, 10);
        */
        

        // 测试size
        FUN_VALUE(v1.getSize());
        /*
        std::cout << "size test : \n";
        v1.getSize();
        */
        

        // 访问数组中的元素[]
        FUN_VALUE(v1[0]);
        FUN_VALUE(v1[1]);
        FUN_VALUE(v1[2]);
        /*
        std::cout << "operator[] test : \n";
        std::cout << v1[0] << " " << v1[1] << " " << v1[2] << std::endl;
        */
        

        // 测试pop_back
        FUN_AFTER(v1, v1.pop_back());
        /*
        std::cout << "pop_back test : \n";
        v1.pop_back();
        */

        // 清空数组
        FUN_AFTER(v1, v1.clear());
        /*
        std::cout << "clear test : \n";
        v1.clear();
        */

        
        // 迭代器begin()和end()
        // COUT宏定义已经测试过iterator了
        /*
        std::cout << "iterator test : \n";
            for (auto it = v1.begin(); it != v1.end(); ++it){
                std::cout << *it << " ";
            }
        */
        

        PASSED;

    #if PERFORMANCE_TEST_ON
        std::cout << "[--------------------- Performance Testing ---------------------]\n";
        std::cout << "|---------------------|-------------|-------------|-------------|\n";
        std::cout << "|      push_back      |";
    #if LARGER_TEST_DATA_ON
        CON_TEST_P1(vector<int>, push_back, rand(), SCALE_LL(LEN1), SCALE_LL(LEN2), SCALE_LL(LEN3));
    #else
        CON_TEST_P1(vector<int>, push_back, rand(), SCALE_L(LEN1), SCALE_L(LEN2), SCALE_L(LEN3));
    #endif
        std::cout << "\n";
        std::cout << "|---------------------|-------------|-------------|-------------|\n";
        PASSED;
    #endif
        std::cout << "[----------------- End container test : vector -----------------]\n";

    }

} // namespace vector_test
} // namespace test
} // namespace mystl


#endif // !MYTINYSTL_VECTOR_TEST_H_