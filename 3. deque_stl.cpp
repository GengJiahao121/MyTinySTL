#include <iostream>
#include <deque>

// std::deque 使用了分段数组的结构，每个分段都是一个固定大小的数组
/*
myDeque.push_front(1);
myDeque.push_back(2); 
myDeque.pop_front();
myDeque.pop_back();
*/
int main(){
    // 创建一个包含一些元素的deque
    std::deque<int> myDeque = {1, 2, 3, 4, 5};

    // 在常量时间内对元素进行随机访问
    std::cout << "Element at index 2: " << myDeque[2] << std::endl;
    std::cout << "Element at index 4: " << myDeque[4] << std::endl;

    return 0;
}