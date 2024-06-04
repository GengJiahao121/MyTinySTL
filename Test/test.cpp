#include <stdlib.h>

#include "vector_test.h"
#include "list_test.h"

int main(){
    using namespace mystl::test;

    std::cout.sync_with_stdio(false);

    vector_test::vector_test();

    list_test::list_test();
}

