#ifndef MYTINGYSTL_DEQUE_H
#define MYTINGYSTL_DEQUE_H

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <string>

// 迭代器
#include "iterator.h"

namespace mystl{

template <class T>
class DequeIterator : public iterator<random_access_iterator_tag, T>
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef ptrdiff_t difference_type;

    typedef DequeIterator<T> self;

    // 迭代器的成员变量
    T *elements; // 指向deque的数组
    size_t cur; // 当前指向的元素
    size_t first ; // 当前所指缓冲区的头
    size_t last; // 当前所指缓冲区的尾
    size_t capacity; // 缓冲区大小

    // 构造函数
    DequeIterator() : elements(nullptr), cur(0), first(0), last(0), capacity(0) {} 
    DequeIterator(T* elements, size_t cur, size_t first, size_t last, size_t capacity) : elements(elements), cur(cur), first(first), last(last), capacity(capacity) {}
    DequeIterator(const DequeIterator& other) : elements(other.elements), cur(other.cur), first(other.first), last(other.last), capacity(other.capacity) {}

    friend std::ostream& operator<<(std::ostream& os, const self& it) {
        os << *it;
        return os;
    }

    // 解引用
    reference operator*() const {
        return elements[cur]; // 如果是自定义数据类型需要实现[]运算符
    }
    
    // 重载前置++运算符
    self& operator++() {
        cur = (cur + 1) % capacity; 
        return *this;
    }

    // 重载后置++运算符
    self operator++(int) {
        self temp = *this;
        ++*this;
        return temp;
    }

    // 重载前置--运算符
    self& operator--() {
        // 计算新的位置
        // 分情况讨论
        if (cur == first) {
            cur = last;
        }
        --cur;
        return *this;
    }

    // 重载后置--运算符
    self operator--(int) {
        self temp = *this;
        --*this;
        return temp;
    }

    // 重载+=运算符
    self& operator+=(difference_type n) {
        // 计算新的位置
        // 分情况讨论
        size_t data_size = getDataSize();
        // 1. first > last
        if ( first > last ) {
            size_t new_n = n % data_size;
            size_t new_cur = (cur + new_n) % capacity;
            if (new_cur >= last) {
                new_cur = first + (new_cur - last);
            }
            cur = new_cur;
        }
        // 2. first < last
        else {
            size_t new_n = n % data_size; // 防止n > data_size
            size_t new_cur = (cur + new_n) % data_size; // 计算新的cur相对于first的偏移量
            new_cur = new_cur + first; // 计算新的cur
            cur = new_cur;
        }
    }

    // 重载+运算符
    self operator+(difference_type n) {
        return operator+=(n);
    }

    // 重载-=运算符

    // 重载 == 运算符   
    bool operator==(const self& other) const {
        return cur == other.cur;
    }

    // 重载 != 运算符
    bool operator!=(const self& other) const {
        return !(*this == other);
    }




private:
    // 返回缓冲区大小
    size_t getDataSize() const {
        if (first > last) {
            return capacity - (first - last);
        } else {
            return last - first;
        }
    }
    
};


template <typename T>
class Deque
{
private:
    T *elements;
    size_t capacity;
    size_t frontIndex;
    size_t backIndex;
    size_t size;

public:
    typedef DequeIterator<T> iterator;

    iterator begin() { return iterator(elements, frontIndex, frontIndex, backIndex, capacity); }

    iterator end() { return iterator(elements, backIndex, frontIndex, backIndex, capacity); }

public:

    // 构造函数
    Deque() : elements(nullptr), capacity(0), frontIndex(0), backIndex(0), size(0) {}

    // 析构函数
    ~Deque() {
        clear(); // 目的是让frontIndex, backIndex归位
        delete[] elements;
    }

    // 在deque前端插入元素
    void push_front(const T &value){
        // 检查是否需要扩展数组容量
        if (size == capacity) {
            resize();
        }

        // 计算新的前端索引
        // 为了防止数组索引为负, 使其指向尾端
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        // 在新的前端位置插入元素
        elements[frontIndex] = value;

        // 增加deque的元素数量
        ++size;
    }

    // 在deque的后端插入元素
    void push_back(const T &value) {
        // 检查是否需要扩展数组容量
        if (size == capacity) {
            resize();
        }

        // 在后端位置插入元素
        elements[backIndex] = value;
        // 更新backIndex
        backIndex = (backIndex + 1) % capacity;

        // 增加deque的元素数量
        ++size;
    }

    // 前端出队
    void pop_front(){
        if (size == 0) {
            throw std::out_of_range("Deque is empty");
        }

        frontIndex = (frontIndex + 1) % capacity;

        --size;
    }

    // 后端出队
    void pop_back(){
        if (size == 0) {
            throw std::out_of_range("Deque is empty");
        }

        // 为了防止数组索引为负, 使其指向尾端
        backIndex = (backIndex - 1 + capacity) % capacity;

        --size;
    }

    // [] 运算符重载
    T &operator[](int index){
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        return elements[(frontIndex + index) % capacity];
    }

    // 获取deque中的元素数量
    size_t getSize() const {
        return size;
    }

    // 清空deque
    void clear() {
        while (size > 0) {
            pop_front();
        }
    }

    // 打印deque中的元素
    void printElements() const {
        size_t index = frontIndex;
        for (size_t i = 0; i < size; ++i) {
            std::cout << elements[index] << " ";
            index = (index + 1) % capacity;
        }
        std::cout << std::endl;
    }

private:
    void resize(){
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;

        // 创建新的数组
        T* newElements = new T[newCapacity];
        // 复制元素到新数组
        size_t index = frontIndex;
        for (size_t i = 0; i < size; ++i) {
            newElements[i] = elements[index];
            index = (index + 1) % capacity;
        }

        // 释放旧数组的内存
        delete[] elements;

        // 更新成员变量
        elements = newElements; // 指向新数组
        capacity = newCapacity;
        frontIndex = 0;
        backIndex = size;
    }
    
};

/*
int main() {
        // 创建一个 Deque 对象
    Deque<int> myDeque;

    int N;
    std::cin >> N;
    // 读走回车
    getchar();
    std::string line;
    // 接收命令
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        int value;

        if (command == "push_back") {
            iss >> value;
            myDeque.push_back(value);
        }

        if (command == "push_front") {
            iss >> value;
            myDeque.push_front(value);
        }

        if (command == "pop_back") {
            if (myDeque.getSize() == 0) {
                continue;
            }
            myDeque.pop_back();
        }

        if (command == "pop_front") {
            if (myDeque.getSize() == 0) {
                continue;
            }
            myDeque.pop_front();
        }

        if (command == "clear") {
            myDeque.clear();
        }

        if (command == "size") {
            std::cout << myDeque.getSize() << std::endl;
        }

        if (command == "get") {
            iss >> value;
            std::cout << myDeque[value] << std::endl;
        }

        if (command == "print") {
            if (myDeque.getSize() == 0) {
                std::cout << "empty" << std::endl;
            } else {
                myDeque.printElements();
            }
        }
    }
    return 0;
}
*/

}

#endif // MYTINGYSTL_DEQUE_H
