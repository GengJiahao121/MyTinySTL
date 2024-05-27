#include <iostream>
#include <set>

int main() {
    std::set<int> mySet;

    mySet.insert(42);
    mySet.insert(21);
    mySet.insert(63);
    mySet.insert(21);

    mySet.erase(63);

    auto it = mySet.find(42);
    if (it != mySet.end()) {
        // 元素存在
    }

    for (const int &element : mySet) {
        std::cout << element << std::endl;
    }

    std::cout << std::endl;
}