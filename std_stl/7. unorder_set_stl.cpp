#include <iostream>
#include <unordered_set>

int main(){

    std::unordered_set<int> mySet;

    // 插入元素
    mySet.insert(42);
    mySet.insert(21);
    mySet.insert(63);

    // 删除元素
    int searchElement = 21;
    auto it = mySet.find(searchElement);
    if (it != mySet.end()){
        std::cout << "Element " << searchElement << " found in the set " << std::endl;
    }
    else
    {
        std::cout << "Element " << searchElement << " not found in the set " << std::endl;
    }

    // 删除元素
    int deleteElement = 42;
    size_t numErased = mySet.erase(deleteElement);
    if (numErased > 0) {
        std::cout << "Element " << deleteElement << " deleted from the set." << std::endl;
    } else {
        std::cout << "Element " << deleteElement << " not found in the set. Nothing deleted." << std::endl;
    }

    // 打印集合大小
    std::cout << "Set size: " << mySet.size() << std::endl;

    // 遍历打印集合
    std::cout << "Set elements: ";
    for (const auto& element : mySet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;

}