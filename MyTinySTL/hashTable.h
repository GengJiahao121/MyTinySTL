#ifndef MYTINYSTL_HASHTABLE_H
#define MYTINYSTL_HASHTABLE_H

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <sstream>
#include <string>
#include <list>

namespace mystl{

template <typename Key, typename Value, typename Hash = std::hash<Key> >
class HashTable
{
    class HashNode {
    public:
        Key key;
        Value value;

        explicit HashNode (const Key &key) : key(key), value() {}

        // 从Key和Value构造节点
        HashNode(const Key &key, const Value &value) : key(key), value(value) {}

        // 比较算符重载，只按照key进行比较
        bool operator==(const HashNode &other) const { return key == other.key; }

        bool operator!=(const HashNode &other) const { return key != other.key; }

        bool operator<(const HashNode &other) const { return key < other.key; }

        bool operator>(const HashNode &other) const { return key > other.key; }

        bool operator==(const Key &key_) const { return key == key_; }

        void print() const {
            std::cout << key << " "<< value << " ";
        }
    };

private:
    /*
    using Bucket = std::list<HashNode>; 是C++11引入的一种类型别名声明，
    的是为现有的类型定义一个新的名字，以便更简洁或更有意义地使用该类型。
    */
    using Bucket = std::list<HashNode>;

    std::vector<Bucket> buckets;

    Hash hashFunction;

    size_t tableSize; // 哈希表的大小，即桶的数量

    size_t numElements; // 哈希表中元素的数量

    float maxLoadFactor = 0.75; // 默认的最大负载因子

    // 计算键的哈希值，并将其映射到桶的索引
    size_t hash(const Key &key) const { return hashFunction(key) % tableSize; }

    void rehash(size_t newSize)
    {
        std::vector<Bucket> newBuckets(newSize); // 创建新的桶数组
        for (Bucket &bucket : buckets) {      // 遍历旧桶
            for (HashNode &hashNode : bucket) { // 遍历桶中的每个键
                size_t newIndex =
                    hashFunction(hashNode.key) % newSize; // 为键计算新的索引
                newBuckets[newIndex].push_back(hashNode); // 将键添加到新桶中
            }
        }

        buckets = std::move(newBuckets); // 使用移动语义更新桶数组
        tableSize = newSize;   
    }

public:

    HashTable() {}

    HashTable(ssize_t size = 10, const Hash &hashFunc = Hash())
        : buckets(size), hashFunction(hashFunc), tableSize(size), numElements(0) {
    }
    
    void insert(const Key &key, const Value &value) {
        if ((numElements + 1) > maxLoadFactor * tableSize) { // 检查是否需要重哈希
            // 处理 clear 后再次插入元素时 tableSize = 0 的情况
            if (tableSize == 0) tableSize = 1;
                rehash(tableSize * 2); // 重哈希，桶数量翻倍
        }

        size_t index = hash(key);

        std::list<HashNode> &bucket = buckets[index]; // 获取对应的桶

        // 如果元素不存在，则返回指向容器末尾的迭代器。
        if (std::find(bucket.begin(), bucket.end(), key) == bucket.end()) {

            bucket.push_back(HashNode(key, value));
            ++numElements; // 增加元素数量
        }
    }

    void insertKey(const Key &key) { insert(key, Value{}); }

    void erase(const Key &key) {
        size_t index = hash(key);      // 计算键的索引
        auto &bucket = buckets[index]; // 获取对应的桶
        auto it = std::find(bucket.begin(), bucket.end(), key); // 查找键
        if (it != bucket.end()) {                               // 如果找到键
            bucket.erase(it); // 从桶中移除键
            numElements--;    // 减少元素数量
        }
    }

    // 查找键是否存在于哈希表中
    Value *find(const Key &key) {
        size_t index = hash(key);      // 计算键的索引
        auto &bucket = buckets[index]; // 获取对应的桶
        // 返回键是否在桶中
        auto ans = std::find(bucket.begin(), bucket.end(), key);
        if (ans != bucket.end()) {
            return &ans->value;
        };
        return nullptr;
    }

    // 获取哈希表中元素的数量
    size_t size() const { return numElements; }

    // 打印哈希表中的所有元素
    void print() const {
        for (size_t i = 0; i < buckets.size(); ++i) {
            for (const HashNode &element : buckets[i]) {
                element.print();
            }
        }
        std::cout << std::endl;
    }

    void clear() {
        this->buckets.clear(); // 调用了 std::vector 的 clear 成员函数
        this->numElements = 0;
        this->tableSize = 0;
    }
};

/*
int main() {
  // 创建一个哈希表实例
  HashTable<int, int> hashTable;

  int N;
  std::cin >> N;
  getchar();

  std::string line;
  for (int i = 0; i < N; i++) {
      std::getline(std::cin, line);
      std::istringstream iss(line);
      std::string command;
      iss >> command;
      
      int key;
      int value;

      if (command == "insert") {
          iss >> key >> value;
          hashTable.insert(key, value);
      }

      if (command == "erase") {
          if (hashTable.size() == 0) {
              continue;
          }
          iss >> key;
          hashTable.erase(key);
      }

      if (command == "find") {
          if (hashTable.size() == 0) {
              std::cout << "not exist" << std::endl;
              continue;
          }
          iss >> key;
          int* res = hashTable.find(key);
          if (res != nullptr) {
              std::cout << *res << std::endl;
          } else {
              std::cout << "not exist" << std::endl;
          }
      }

      if (command == "print") {
          if (hashTable.size() == 0) {
              std::cout << "empty" << std::endl;
          } else {
              hashTable.print();
          }
      }

      if (command == "size") {
          std::cout << hashTable.size() << std::endl;
      }

      if (command == "clear") {
          hashTable.clear();
      }
  }
  return 0;
}

*/

}

#endif //MYTINYSTL_HASHTABLE_H