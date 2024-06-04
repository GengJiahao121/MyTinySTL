#ifndef MYTINYSTL_lis_H
#define MYTINYSTL_lis_H

#pragma once // 用于防止头文件被重复包含

#include <iostream> // std::cin, std::cout, std::cerr, std::clog, ...
#include <stdexcept>  // std::exception, std::runtime_error, std::logic_error, std::out_of_range, std::invalid_argument ... 
#include <algorithm> // std::sort, std::find, std::copy, std::transform, std::accumulate ...
#include <sstream> // std::stringstream, std::istringstream, ostringstream
#include <string> // std::string::size(), std::string::substr(), std::to_string
#include <initializer_list> // for std::initializer_lis


/**
 * 实现方法：
 * 1. 无参的构造函数
 * 2. 初始化列表构造函数
 * 3. push_back()：在链表末尾添加元素
 * 4. push_front()：在链表开头添加元素
 * 5. getSize()：获取链表中节点的数量
 * 6. operator[]：访问链表中的元素
 * 7. pop_back()：删除链表末尾的元素
 * 8. pop_front()：删除链表开头的元素
 * 9. getNode(val)：获取指定值的节点
 * 10. remove(val)：删除指定值的节点
 * 11. empty()：判断链表是否为空
 * 12. clear()：清空链表
 * 13. begin()：使用迭代器遍历链表的开始位置
 * 14. end()：使用迭代器遍历链表的结束位置
 * 15. printElements()：打印链表中的元素
 * 16. operator<<：重载 << 运算符
*/


namespace mystl
{

// 定义一个链表类
template <typename T>
class list
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node *prev;

        Node(const T &value, Node *nextNode = nullptr, Node *prevNode = nullptr) 
            : data(value), next(nextNode), prev(prevNode){}  

        template <typename L>
        friend std::ostream &operator<<(std::ostream &os, const list<T>::Node *pt);
    };

    Node *head;
    Node *tail;
    size_t size;

public:
    // 无参的构造函数
    list() : head(nullptr), tail(nullptr), size(0){}

    // 初始化列表构造函数
    list(std::initializer_list<T> initlist) : head(nullptr), tail(nullptr), size(0){
        for (const T& value : initlist){
            push_back(value);
        }
    }
    ~list() { clear(); }

// 迭代器 和 运算符重载友元函数
public:
    template <typename L>
    friend std::ostream &operator<<(std::ostream &os, const list<L> &pt); // 该函数是友元函数的声明

    // 迭代器
    struct Iterator
    {
    public:
        Iterator() : ptr(nullptr) {}

        Iterator(Node *node) : ptr(node) {}

        bool operator!=(const Iterator &it) { return ptr != it.ptr; }

        T &operator*() { return ptr->data; }

        // 重载 -> 运算符
        T *operator->() { return &ptr->data; }

        // 前置++
        Iterator &operator++() { ptr = ptr->next; return *this; }

        // 后置++
        Iterator operator++(int) { Iterator temp = *this; ptr = ptr->next; return temp; }

        // 前置--
        Iterator &operator--() {ptr = ptr->prev; return *this; }

        // 后置--
        Iterator operator--(int) { Iterator temp = *this; ptr = ptr->prev; return temp; }

    private:
        Node *ptr;
    };
    
    // 返回迭代器的开始位置
    Iterator begin() { return Iterator(head); }

    // 返回迭代器的结束位置
    Iterator end() { return Iterator(nullptr); }

    // 访问链表中的元素
    T &operator[](size_t index)
    {   
        // 从头节点开始遍历链表，找到**第 index 个节点**
        Node *current = head;
        for (size_t i = 0; i < index; ++i)
        {
            if (!current)
            {
                throw std::out_of_range("Index out of range");
            }

            current = current->next;
        }

        return current->data;
    }

    // const版本的访问链表中的元素
    const T &operator[](size_t index) const
    {
        // 从头节点开始遍历链表，找到第 index 个节点
        Node *current = head;
        for (size_t i = 0; i < index; ++i)
        {
            if (!current)
            {
                // 如果 index 超出链表长度，则抛出异常
                throw std::out_of_range("Index out of range");
            }
            current = current->next;
        }

        // 返回节点中的数据
        return current->data;
    }

// 常用方法
public:
    void push_back(const T &value){

        Node *newNode = new Node(value, nullptr, tail);

        if (tail)
        {
            tail->next = newNode;
        }
        else
        {
            head = newNode;
        }

        tail = newNode;
        ++size;
    }

    void push_front(const T &value)
    {

        Node *newNode = new Node(value, head, nullptr);

        if (head) 
        {
            head->prev = newNode;
        }
        else
        {
            tail = newNode;
        }

        head = newNode;
        ++size;
    }

    // 获取链表中节点的数量
    size_t getSize() const { return size; }

    // 删除链表末尾的元素
    void pop_back()
    {
        if (size > 0)
        {
            Node *newTail = tail->prev;

            delete tail;

            tail = newTail;
            if (tail)
            {
                tail->next = nullptr;
            }
            else
            {
                head = nullptr;
            }

            --size;
        }
    }

    // 删除链表开头的元素
    void pop_front()
    {
        if (size > 0)
        {
            // 获取头节点的下一个节点
            Node *newHead = head->next;

            // 删除头节点
            delete head;

            // 更新头节点指针和链表大小
            head = newHead;
            if (head)
            {
                head->prev = nullptr;
            }
            else
            {
                tail = nullptr; // 如果链表为空，尾节点也置为空
            }

            --size;
        }
    }

    // 获取指定值的节点
    Node *getNode(const T &val)
    {
        Node *node = head;
        while (node != nullptr && node->data != val)
        {
            node = node->next;
        }

        return node;
    }

    T *find(const T &val)
    {
        Node *node = getNode(val);
        if (node == nullptr)
        {
            return nullptr;
        }
        return &node->val;
    }

    // 删除指定值的节点
    void remove(const T &val)
    {
        Node *node = head;
        while (node != nullptr && node->data != val)
        {
            node = node->next;
        }

        if (node == nullptr)
        {
            // 没有找到
            return;
        }
        if (node != head && node != tail)
        {
            // 既不是头结点也不是尾结点
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        else if (node == head && node == tail)
        {
            // 既是头结点也是尾结点
            head = nullptr;
            node = nullptr;
        }
        else if (node == head)
        {
            // 是头结点
            head = node->next;
            head->prev = nullptr;
        }
        else
        {
            // 是尾结点
            tail = node->prev;
            tail->next = nullptr;
        }

        --size;

        delete node;
        node = nullptr;
    }

    bool empty() { return size == 0; }

    void clear(){
        while (head) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
        size = 0;
    }

    // 打印链表中的元素
    void printElements() const
    {
        for (Node *current = head; current; current = current->next)
        {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }


};

// 重载 << 运算符
template <typename T>
std::ostream &operator<<(std::ostream &os, const mystl::list<T> &pt)
{
    for (typename list<T>::Node *current = pt.head; current;
         current = current->next)
    {
        os << " " << current->data;
    }
    os << std::endl;
    return os;
}

// 模版函数
// 重载 << 运算符
template <typename T>
std::ostream &operator<<(std::ostream &os, const typename mystl::list<T>::Node *pt){
    os << pt->data;
    return os;
}

/*
int main() {

    // 使用参数列表初始化列表
    list<int> mylist1 = {1, 2, 3, 4, 5, 6};
    mylist1.printElements();

    // 创建一个 list 对象
    list<int> mylist;
    
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
            mylist.push_back(value);
        }

        if (command == "push_front") {
            iss >> value;
            mylist.push_front(value);
        }

        if (command == "pop_back") {
            mylist.pop_back();
        }

        if (command == "pop_front") {
            mylist.pop_front();
        }

        if (command == "remove") {
            iss >> value;
            mylist.remove(value);
        }

        if (command == "clear") {
            mylist.clear();
        }

        if (command == "size") {
            std::cout << mylist.getSize() << std::endl;
        }

        if (command == "get") {
            iss >> value;
            std::cout << mylist[value] << std::endl;
        }

        if (command == "print") {
            if (mylist.getSize() == 0) {
                std::cout << "empty" << std::endl;
            } else {
                mylist.printElements();
            }
        }

        if (command == "print_cout") {
            std::cout << mylist
    ;
        }

        if (command == "getNode"){
            std::cout << mylist.getNode(2)->data << std::endl;
        }
    }
    return 0;
}
*/

} // namespace mystl

#endif // MYTINYSTL_lis_H