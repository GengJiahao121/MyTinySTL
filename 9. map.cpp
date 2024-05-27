#include "5. RedBlackTree.cpp"

#include <iostream>
#include <utility>

template <typename Key, typename Value>
class Map{
public:
    Map() : rbTree() {}
    ~Map() {}

public:
    void insert(const Key &key, const Value &value) { rbTree.insert(key, value); }

    void erase(const Key &key) { rbTree.remove(key); }

    size_t size() { return rbTree.getSize(); }

    bool empty() const { return rbTree.empty(); }

    bool contains(const Key &key) { return rbTree.at(key) != nullptr; }

    Value &at(const Key &key) {
        Value *foundVal = rbTree.at(key);
        if (foundVal) {
            return *foundVal;
        } else {
            throw std::out_of_range("Key not found");
        }
    }

    Value &operator[](const Key &key) {
        Value *foundVal = rbTree.at(key);
        if (foundVal) {
        // 如果键存在，返回关联的值
            return *foundVal; // 或者，返回与找到的键关联的值
        } else {
            // 如果键不存在，插入新键值对，并返回新插入的值的引用
            Value defaultValue;
            rbTree.insert(key, defaultValue);
            return *rbTree.at(key);
        }
    }

private:
    RedBlackTree<Key, Value> rbTree;
};

// main函数
int main() {
    Map<int, std::string> map;

    // 插入键值对
    map.insert(1, "Apple");
    map.insert(2, "Banana");
    map.insert(3, "Cherry");

    // 打印大小
    std::cout << "当前Map的大小: " << map.size() << std::endl;

    // 访问元素
    try {
        std::cout << "键1对应的值: " << map.at(1) << std::endl;
        std::cout << "键2对应的值: " << map.at(2) << std::endl;
    } catch (const std::out_of_range &e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }

    // 检查是否包含某个键
    int keyToCheck = 3;
    std::cout << "Map是否包含键" << keyToCheck << ": "
            << (map.contains(keyToCheck) ? "是" : "否") << std::endl;

    // 使用[]运算符访问或创建元素
    std::cout << "键4对应的值（在此之前不存在，将被创建）: " << map[4]
            << std::endl;

    // 删除元素
    int keyToDelete = 2;
    std::cout << "删除键" << keyToDelete << std::endl;
    map.erase(keyToDelete);

    // 再次打印大小
    std::cout << "删除键" << keyToDelete << "后，当前Map的大小: " << map.size()
            << std::endl;

    // 使用[]运算符为元素赋值
    map[4] = "Pear";
    std::cout << "键4对应的值: " << map[4] << '\n';
    return 0;
}

/*
1. std::map和std::unordered_map有什么区别？

内部实现：std::map内部基于红黑树实现，因此它的元素是自动排序的。而std::unordered_map基于哈希表实现，元素是无序的。
性能：对于std::map，查找、插入和删除操作的时间复杂度通常是O(log n)。对于std::unordered_map，这些操作的平均时间复杂度是O(1)，但最坏情况下是O(n)。
内存消耗：由于哈希表的开销，std::unordered_map可能会比std::map消耗更多内存。
元素排序：std::map中的元素按照键自动排序，而std::unordered_map中的元素没有特定的顺序。

2. 如何在std::map中查找一个键并安全地访问它的值？

使用find方法来查找键，它返回一个迭代器。如果找到了键，迭代器将指向相应的元素；如果没有找到，则迭代器等于end()迭代器。
在解引用迭代器之前，应该检查它是否不等于end()，以确保访问是安全的。

3. std::map的迭代器失效的情况有哪些？

删除当前迭代器指向的元素会使该迭代器失效，但其他迭代器仍然有效。
插入操作不会使现有迭代器失效。
std::map的迭代器是双向迭代器，对树的结构修改（如插入或删除）不会影响其他迭代器，除了指向被删除元素的迭代器。

4. 如果std::map的键类型是自定义类型，需要怎么做？

如果键类型是自定义类型，则需要定义比较函数或重载<运算符，以便std::map能够对键进行排序。
可以通过在自定义类型中重载<运算符或提供自定义比较函数作为std::map的第三个模板参数来实现。

```
struct MyKey {
    int key;
    bool operator<(const MyKey& other) const {
        return key < other.key;
    }
};
std::map<MyKey, int> myMap;
```

或者
```
struct MyCompare {
    bool operator()(const MyKey& lhs, const MyKey& rhs) const {
        return lhs.key < rhs.key;
    }
};
std::map<MyKey, int, MyCompare> myMap;
```

5. 解释std::map::emplace和std::map::insert的区别。

emplace方法会在map中直接构造元素，避免了额外的复制或移动操作。它接受构造元素所需的参数，并且尝试在容器中构造元素。

insert方法用于将已经构造好的元素插入到map中。如果提供了键值对，insert可能会导致一次或两次额外的复制或移动构造，首先是创建临时键值对对象，然后是将其插入到容器中。

emplace更高效，因为它直接在容器内部构造元素，减少了不必要的复制或移动操作。然而，选择使用emplace还是insert取决于具体情况，有时为了代码的清晰可读，使用insert可能更合适。
*/