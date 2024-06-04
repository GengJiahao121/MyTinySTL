#include <iostream>
#include <vector>



int main() {
    // 创建一个空的 vector
    std::vector<int> myVector;

    // 使用初始化列表创建 vector
    std::vector<int> myVector2 = {1, 2, 3, 4, 5};

    // 在尾部插入元素
    myVector.push_back(42);

    // 使用下标访问元素
    std::cout << "First element: " << myVector[0] << std::endl;

    // 打印 vector 的大小
    std::cout << "Size of myVector: " << myVector.size() << std::endl;

    return 0;
}