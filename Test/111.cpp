

#include <iostream>
#include "../MyTinySTL/list.h"
#include "test.h"

namespace mystl
{
namespace test
{
namespace list_test
{

int main(){

    mystl::list<int> mylist;

    mylist.push_back(1);
    mylist.push_back(2);
    mylist.push_back(3);

    for ( auto it : mylist ) {
        std::cout << it.data << " ";
    }

    std::cout << std::endl;
}

}}} // namespace mystl::test::list_test