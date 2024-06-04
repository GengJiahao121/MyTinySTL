#ifndef MYTINYSTL_UNORDERED_SET_H
#define MYTINYSTL_UNORDERED_SET_H

#include "hashTable.h"
#include <cstddef>

namespace mystl{

template <typename Key>
class Unordered_set {
public:
    Unordered_set() : hashtable() {}

    ~Unordered_set() {}

    // noexcept 指明一个函数在执行时不会抛出异常
    bool empty() const noexcept { return hashtable.size() == 0; }

    size_t size() const noexcept { return hashtable.size(); }

    void clear() noexcept { hashtable.clear(); }

    void insert(const Key &key) { hashtable.insertKey(key); }

    void erase(const Key &key) { hashtable.erase(key); }

    bool find(const Key &key) {return hashtable.find(key) != nullptr; }

private:
    HashTable<Key, Key> hashtable; 
};

/*
int main() {

    // 创建一个整数类型的 Unordered_set 集合
    Unordered_set<int> intSet;

    // 插入一些数字
    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(3);

    // 检查集合是否为空
    std::cout << "集合是否为空? " << (intSet.empty() ? "是" : "否") << std::endl;

    // 检查集合的大小
    std::cout << "集合的大小: " << intSet.size() << std::endl;

    // 查找一个元素
    std::cout << "2 是否在集合中? " << (intSet.find(2) ? "是" : "否")
            << std::endl;

    // 删除一个元素
    intSet.erase(2);
    std::cout << "删除 2 后，2 是否还在集合中? " << (intSet.find(2) ? "是" : "否")
            << std::endl;

    // 清空集合
    intSet.clear();
    std::cout << "清空后集合是否为空? " << (intSet.empty() ? "是" : "否")
            << std::endl;

    // 创建一个字符串类型的 Unordered_set 集合
    Unordered_set<std::string> stringSet;

    // 插入一些字符串
    stringSet.insert("apple");
    stringSet.insert("banana");
    stringSet.insert("cherry");

    // 查找一个字符串
    std::cout << "'banana' 是否在集合中? "
            << (stringSet.find("banana") ? "是" : "否") << std::endl;

    // 删除一个字符串
    stringSet.erase("banana");
    std::cout << "删除 'banana' 后，'banana' 是否还在集合中? "
            << (stringSet.find("banana") ? "是" : "否") << std::endl;

    return 0;
}
*/

}

#endif // MYTINYSTL_UNORDERED_SET_H

/*
1. std::unordered_set 和 std::set 有什么区别？

答：主要区别在于内部数据结构和性能特性。std::set 基于红黑树实现，保持元素排序，而 std::unordered_set 基于哈希表，元素没有特定顺序。
因此，std::unordered_set 通常提供更快的插入、删除和查找操作，但不支持顺序访问和范围查询。

2. 如何处理 std::unordered_set 中的冲突？

答：std::unordered_set 通过链地址法处理哈希冲突。当两个元素的哈希值相同并映射到同一存储位置时，这些元素会被存储在同一存储桶中的链表里。
查找元素时，首先计算其哈希值，然后遍历对应存储桶中的链表。

3. 如何自定义 std::unordered_set 中元素的哈希函数和相等函数？

在声明 std::unordered_set 时，可以提供自定义的哈希函数和相等谓词类型作为模板参数。自定义哈希函数必须是一个接受单个参数（存储在容器中的元素类型）并返回其哈希值的函数。
自定义相等函数用于比较两个元素是否相等。

4. std::unordered_set 的迭代器是什么类型？它们是如何受到哈希表修改的影响？

std::unordered_set 提供了正向迭代器，包括常量和非常量版本。迭代器遍历哈希表的存储桶，然后遍历每个存储桶中的链表。
增加或删除元素可能会导致存储桶重新哈希，这可能会使现有迭代器失效。然而，删除迭代器当前指向的元素是安全的。

5. 如何优化 std::unordered_set 的性能？

优化 std::unordered_set 的性能通常涉及选择合适的哈希函数，以减少冲突并保持元素分布均匀。可以通过调用 rehash 方法来增加存储桶的数量，
或使用 reserve 方法来提前分配足够的存储空间，以减少重哈希操作的次数。

6. std::unordered_set 如何处理元素的删除？

删除操作首先找到要删除的元素的哈希值对应的存储桶，然后在该存储桶的链表中找到并删除该元素。
这个过程的平均时间复杂度是 O(1)
*/

