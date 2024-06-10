#include <iostream>
#include <string>
#include <unordered_map>

int main() {
    // 创建一个unordered_map，键类型为std::string，值类型为int
    std::unordered_map<std::string, int> wordCount;

    // 插入元素
    wordCount["apple"] = 1; // 方法1：使用下标运算符插入或修改元素
    wordCount.insert({"banana", 2}); // 方法2：使用insert函数插入元素
    wordCount.emplace("cherry", 3); // 方法3：使用emplace直接构造元素，效率更高

    // 检查元素是否存在
    if (wordCount.find("cherry") != wordCount.end()) {
        std::cout << "cherry found" << std::endl;
    }

    // 更新元素
    wordCount["apple"] = 5; // 更新apple的计数

    // 删除元素
    wordCount.erase("banana"); // 删除键为"banana"的元素

    // 遍历unordered_map
    for (const auto& pair : wordCount) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 获取unordered_map的大小
    std::cout << "Size of unordered_map: " << wordCount.size() << std::endl;

}