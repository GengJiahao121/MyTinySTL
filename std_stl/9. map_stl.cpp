#include <iostream>
#include <map>

int main() {
    std::map<int, int> myMap;

    myMap.insert({1, 100});

    myMap[2] = 200; // 使用下标操作符直接插入或修改

    myMap.insert({3, 300}); // 使用初始化列表插入

    // 访问元素
    std::cout << "Element with key 2: " << myMap[2] << std::endl;

    // 迭代遍历
    std::cout << "Iterating over elements:" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << pair.first << " => " << pair.second << std::endl;
    }

    // 查找元素
    auto search = myMap.find(2); // 查找键为2的元素
    if (search != myMap.end()) {
        std::cout << "Found element with key 2: " << search->second << std::endl;
    } else {
        std::cout << "Element with key 2 not found." << std::endl;
    }

    // 删除元素
    myMap.erase(2); // 删除键为2的元素
    std::cout << "Element with key 2 erased." << std::endl;

    // 再次遍历，查看删除效果
    std::cout << "Iterating over elements after deletion:" << std::endl;
    for (const auto& pair : myMap) {
        std::cout << pair.first << " => " << pair.second << std::endl;
    }

    return 0;
}