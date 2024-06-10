#ifndef MYTINYSTL_MULTISET_H_
#define MYTINYSTL_MULTISET_H_

#include "RedBlackTree.h"
#include <cstddef>
#include <stdexcept>

template <typename Key>
class MultiSet {
public:
    MultiSet() : sz(0), rbTree() {};
    ~MultiSet() {};

    void insert(const Key &key) {
        auto count = rbTree.at(key);
        if (count != nullptr){
            (*count)++;
            this->sz++;
            return;
        }
        rbTree.insert(key, 1);
        this->sz++;
    }

    void erase(const Key &key) {
        auto count = rbTree.at(key);
        if (count == nullptr) {
            return;
        }
        (*count)--;
        this->sz--;
        if (*count == 0) {
            rbTree.remove(key);
        }
    }

    // 返回容器中元素的数量
    size_t size() const { return this->sz; }

    // 判断容器是否为空
    bool empty() const { return this->sz == 0; }

    // 返回在 multiset 中等于给定值的元素的数量
    size_t count(const Key &key) {
        auto num = rbTree.at(key);
        if (num != nullptr) {
            return *num;
        }

        return 0;
    }

    void clear() {
        this->sz = 0;
        rbTree.clear();
    }



private:
    RedBlackTree<Key, size_t> rbTree;
    size_t sz;

};

/*
int main() {
    MultiSet<int> mySet; // Create an Unordered_set for integers

    // Insert some elements
    mySet.insert(1);
    mySet.insert(2);
    mySet.insert(3);

    // Check if elements are in the set
    std::cout << "Does the set contain 1? " << (mySet.count(1) > 0 ? "Yes" : "No")
            << std::endl;
    std::cout << "Does the set contain 4? " << (mySet.count(4) > 0 ? "Yes" : "No")
            << std::endl;

    // Print the size of the set
    std::cout << "The set size is: " << mySet.size() << std::endl;

    // Remove an element
    mySet.erase(2);
    std::cout << "After erasing 2, does the set contain 2? "
            << (mySet.count(2) > 0 ? "Yes" : "No") << std::endl;
    std::cout << "The set size is now: " << mySet.size() << std::endl;

    // Clear the set
    mySet.clear();
    std::cout << "After clearing, is the set empty? "
            << (mySet.empty() ? "Yes" : "No") << std::endl;

    return 0;
}
*/

#endif // MYTINYSTL_MULTISET_H_

/*
1. 解释multiset和Set的区别是什么？ multiset和Set都是关联容器，它们可以存储元素，并能够快速检索。
它们之间的主要区别在于multiset允许存储重复的元素，而Set不允许重复元素。这意味着在multiset中，可以有多个相同的键值，每个键值都会被计数；而在Set中，同一个键值只能出现一次。

2. 在multiset中如何统计一个元素的出现次数？ 
在multiset中，可以通过count成员函数来统计某个元素的出现次数。以下是如何使用count函数的示例代码：
```
multiset<int> mymultiset;
// ... (代码中添加一些元素到mymultiset中) ...
int count = mymultiset.count(5); // 统计元素5出现的次数
```

3. 如何在multiset中插入和删除元素？ 
可以使用insert成员函数来向multiset中插入元素。
删除元素时，可以使用erase函数来删除一定数量的特定元素。以下示例展示了插入和删除操作：

4. 如何遍历multiset中的所有元素？ 
由于multiset可能包含重复元素，遍历时可能需要处理每个元素出现的次数。可以使用迭代器来遍历multiset中的元素，如下所示
```
for (auto it = myMultiSet.begin(); it != myMultiSet.end(); ++it) {
    count = it->value;
    while (count) {
        // 打印 key和value
        count--;
    }
}
```

5. multiset通常使用什么内部数据结构？ 

multiset通常使用平衡二叉树作为其内部数据结构，最常见的实现是红黑树。
红黑树是一种自平衡的二叉搜索树，它可以在对数时间内完成插入、删除和查找操作，保证了multiset的高效性能。

6. 如何清空multiset中的所有元素？

若要清空multiset中的所有元素，可以使用clear成员函数。
这会移除multiset中的所有元素，并将其大小重置为0。

7. 如果要实现一个multiset，关键的操作有哪些？ 
实现一个multiset时，关键的操作包括元素的插入、搜索、删除和迭代遍历。
这些操作都需要高效地处理重复值，并维护内部数据结构的平衡状态。此外，还需要提供一种方法来统计单个键的出现次数，以及清空容器的功能。

8. 使用multiset有什么优点？ 
使用multiset的优点包括能够快速插入、查找和删除元素，特别是当需要处理大量可能重复的数据时。multiset自动排序元素，提供了一种自然的方式来维护集合中元素的次序。
此外，multiset还提供了一些容器操作的便捷性，如统计某个元素的数量、检查集合是否为空等。
*/