#include <iostream>
#include <set>

int main() {
    // 创建一个空的multiset
    std::multiset<int> myMultiset;

    // 插入元素
    myMultiset.insert(42);
    myMultiset.insert(30);
    myMultiset.insert(56);
    myMultiset.insert(30); // 允许重复元素

    // 遍历输出
    std::cout << "Elements in the multiset: ";
    for (const auto& elem : myMultiset) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 删除元素
    myMultiset.erase(30); // 删除所有值为30的元素

    // 再次遍历输出
    std::cout << "Elements after erasing 30: ";
    for (const auto& elem : myMultiset) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 查找元素
    auto it = myMultiset.find(56);
    if (it != myMultiset.end()) {
        std::cout << "Element 56 found in the multiset." << std::endl;
    } else {
        std::cout << "Element 56 not found in the multiset." << std::endl;
    }

    // 获取元素数量
    std::size_t count = myMultiset.size();
    std::cout << "Number of elements in the multiset: " << count << std::endl;

    // 判断是否为空
    if (myMultiset.empty()) {
        std::cout << "The multiset is empty." << std::endl;
    } else {
        std::cout << "The multiset is not empty." << std::endl;
    }

    return 0;
}