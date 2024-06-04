#ifndef MYTINYSTL_VECTOR_H
#define MYTINYSTL_VECTOR_H

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

namespace mystl{

template <typename T>
class vector{
private:
    T *elements; // 指向动态数组的指针
    size_t capacity; // 数组的容量
    size_t size; // 数组的元素个数

public:
    // 构造函数
    vector() : elements(nullptr), capacity(0), size(0) {
   
    }

    // 析构函数
    ~vector(){
        delete[] elements;
    }

    // 拷贝构造函数
    vector(const vector &other) : capacity(other.capacity), size(other.size){
        elements = new T[capacity];
        // C++ 标准库中的一个算法
        std::copy(other.elements, other.elements + size, elements);
    }

    // 拷贝赋值操作符
    vector &operator=(const vector &other){
        if (this != &other) {
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }

        // this表示指向当前对象的指针, *this表示当前对象本身的引用。（解引用（dereferencing）是一个指针操作，它通过指针访问指针指向的对象。解引用使用一元运算符 *。）
        return *this;
    }

public:
    // 添加元素到数组末尾
    void push_back(const T &value){
        if (size == capacity) {
            // 如果数组已满，扩展容量
            reserve(capacity == 0 ? 1 : 2 * capacity);
        }

        elements[size++] = value;
    }

    // 获取数组中元素的个数
    size_t getSize() const{
        return size;
    }

    // 获取数组的容量
    size_t getCapacity() const {
        return capacity;
    }

    // 访问数组中的元素
    T &operator[](size_t index){
        // 查索引是否越界
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        return elements[index];
    }

    // const版本的访问数组中的元素
    const T &operator[](size_t index) const
    {
        // 检查索引是否越界
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    // 在指定位置插入元素
    void insert(size_t index, const T &value)
    {
        if (index > size)
        {
            throw std::out_of_range("Index out of range");
        }
        if (size == capacity)
        {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        for (size_t i = size; i > index; --i)
        {
            elements[i] = elements[i - 1];
        }
        elements[index] = value;
        ++size;
    }

    // 删除数组末尾的元素
    void pop_back()
    {
        if (size > 0)
        {
            --size;
        }
    }

    // 清空数组
    void clear()
    {
        size = 0;
    }

    // 使用迭代器遍历数组的开始位置
    T *begin()
    {
        return elements;
    }

    // 使用迭代器遍历数组的结束位置
    T *end()
    {
        return elements + size;
    }

    // 使用迭代器遍历数组的开始位置（const版本）
    const T *begin() const
    {
        return elements;
    }

    // 使用迭代器遍历数组的结束位置（const版本）
    const T *end() const
    {
        return elements + size;
    }

    // 打印数组中的元素
    void printElements() const
    {
        for (size_t i = 0; i < size; ++i)
        {
            std::cout << elements[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    // 扩展数组容量
    void reserve(size_t newCapacity){
        T *newElements = new T[newCapacity];
        std::copy(elements, elements + size, newElements);
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }

};

/*
int main()
{
    // 创建一个 vector 对象
    vector<int> myvector;

    int N;
    std::cin >> N;

    // 读走回车
    getchar();

    std::string line;
    for (int i = 0; i < N; i++)
    {
        // 读取整行
        std::getline(std::cin, line); // 从输入流（如 std::cin）中读取一行字符串
        std::istringstream iss(line); // 将字符串当作输入流来处理
        std::string command;
        iss >> command; // 使用 >> 运算符从 iss 中提取std::string类型的数据

        if (command == "push")
        {
            int value;
            iss >> value; // 继续使用 >> 运算符从 iss 中提取int类型的数据
            myvector.push_back(value);
        }
        else if (command == "print")
        {
            if (myvector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            myvector.printElements();
        }
        else if (command == "size")
        {
            std::cout << myvector.getSize() << std::endl;
        }
        else if (command == "get")
        {
            int index;
            iss >> index;
            std::cout << myvector[index] << std::endl;
        }
        else if (command == "insert")
        {
            int index, value;
            iss >> index >> value;
            myvector.insert(index, value);
        }
        else if (command == "pop")
        {
            myvector.pop_back();
        }
        else if (command == "iterator")
        {
            if (myvector.getSize() == 0)
            {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (auto it = myvector.begin(); it != myvector.end(); ++it)
            {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
        else if (command == "foreach")
        {
            if (myvector.getSize() == 0)
            {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (const auto &element : myvector)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
        else if (command == "clear")
        {
            myvector.clear();
        }
    }
    return 0;
}
*/

}

#endif // MYTINYSTL_VECTOR_H