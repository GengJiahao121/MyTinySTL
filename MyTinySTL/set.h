#ifndef MYTINYSTL_SET_H
#define MYTINYSTL_SET_H

#include "RedBlackTree.h"

namespace mystl
{

template <typename Key>
class Set {
public:
    Set() : rbTree() {

    }

    ~Set() {}

    void insert(const Key &key) {rbTree.insert(key, key);}

    void erase(const Key &key) {rbTree.remove(key);}

    size_t size() { return rbTree.getSize(); }

    bool empty() { return rbTree.empty(); }

    bool contains(const Key &key) { return rbTree.at(key) != nullptr; }

private:
    RedBlackTree<Key, Key> rbTree;
};

/*
int main() {
  Set<int> mySet;

  // 插入元素
  mySet.insert(10);
  mySet.insert(20);
  mySet.insert(30);

  // 打印集合大小
  std::cout << "当前集合的大小: " << mySet.size() << std::endl;

  // 检查集合是否包含特定元素
  int keyToCheck = 20;
  std::cout << "集合是否包含元素" << keyToCheck << ": "
            << (mySet.contains(keyToCheck) ? "是" : "否") << std::endl;

  // 删除元素
  int keyToDelete = 20;
  mySet.erase(keyToDelete);
  std::cout << "删除元素" << keyToDelete
            << "后，当前集合的大小: " << mySet.size() << std::endl;

  // 再次检查集合是否包含已删除的元素
  std::cout << "删除元素" << keyToDelete << "后，集合是否包含元素"
            << keyToDelete << ": " << (mySet.contains(keyToCheck) ? "是" : "否")
            << std::endl;

  // 检查集合是否为空
  std::cout << "集合是否为空: " << (mySet.empty() ? "是" : "否") << std::endl;

  return 0;
}
*/

}

#endif // MYTINYSTL_SET_H

/*
1. std::set 的迭代器是什么类型？
答：std::set 的迭代器是双向迭代器（Bidirectional Iterator）。可以向前（++）和向后（--）遍历集合，但不能进行随机访问。

2. std::set 和 std::unordered_set 有什么区别？
答：std::set 是基于红黑树的，元素是排序的，而 std::unordered_set 是基于哈希表的，元素是无序的。因此，std::set 中的操作（如插入、删除和查找）通常具有对数时间复杂度（O(log n)），
而 std::unordered_set 中的相应操作具有平均常数时间复杂度（O(1)），但在最坏情况下可能会退化到线性时间复杂度（O(n)）。

3. std::set 是如何保持元素排序的？
答：std::set 是基于红黑树实现的，它是一种自平衡的二叉搜索树。在二叉搜索树中，所有的元素都是按照其值来组织的，任何一个节点的左子树都不包含比该节点大的值，其右子树不包含比该节点小的值。
红黑树通过旋转和重新着色来维护树的平衡，这样就保持了元素的有序性和有效的操作性能。

4. 为什么std::set的操作是对数时间复杂度的？
答：由于std::set是基于红黑树实现的，而红黑树是近似平衡的二叉搜索树，它能够保证在最坏的情况下基本操作（如插入、查找和删除）的时间复杂度为O(log n)，其中n是树中元素的数量。
这是因为树的高度始终保持在对数级别，所有的操作都要在从根到叶子的路径上进行。

5. 如何在std::set中插入一个新元素？
答：当插入一个新元素时，红黑树将按照二叉搜索树的性质将其放到正确的位置。
如果插入操作破坏了红黑树的性质，就会进行一系列的节点着色和树旋转操作来修复这些性质。

6. 删除std::set中的元素时会发生什么？
答：当从std::set中删除一个元素时，如果简单地移除节点可能会破坏红黑树的性质，
因此需要进行一系列复杂的调整，可能包括改变节点的颜色和进行树旋转，以维持红黑树的平衡。

7. std::set中的迭代器失效的情况有哪些？
答：在std::set中，迭代器的失效主要由元素的删除导致。当删除一个元素时，指向该元素的迭代器将失效。但是，由于红黑树的性质，删除操作不会影响到其他元素的迭代器，所以除了被删除元素的迭代器外，其他迭代器仍然有效。
与此相反，插入操作不会导致现有迭代器失效，因为std::set的元素是不可变的，插入新元素不会改变已有元素的位置。
*/