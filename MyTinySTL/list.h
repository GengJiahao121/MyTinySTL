#ifndef MYTINYSTL_lis_H
#define MYTINYSTL_lis_H

#pragma once // 用于防止头文件被重复包含

#include <iostream> 
#include <stdexcept>  
#include <initializer_list> 
#include "iterator.h" 

namespace mystl
{

// Node
template <typename T>
struct Node
{
    T data;
    Node *next;
    Node *prev;

    Node(const T &value, Node *nextNode = nullptr, Node *prevNode = nullptr) 
        : data(value), next(nextNode), prev(prevNode){}  
};

// iterator
template <class T>
class list_iterator : public mystl::iterator<mystl::bidirectional_iterator_tag, T>
{
    /**
     * list_iterator虽然公有继承了iterator，但是并没有继承iterator的成员，因为iterator是一个模板struct，其成员默认是私有的
     * -> 所以这里要重新定义iterator的五个成员
    */
public:
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef list_iterator<T> self;

    Node<T> *ptr;

    // 构造函数
    list_iterator() : ptr(nullptr) {}
    list_iterator(Node<T> *p) : ptr(p) {}
    list_iterator(const list_iterator &rhs) : ptr(rhs.ptr) {}

    // 重载运算符
    reference operator*() const { return ptr->data; }
    pointer operator->() const { return &(operator*()); }

    // prefix increment
    self &operator++()
    {
        ptr = ptr->next;
        return *this;
    }

    // postfix increment
    self operator++(int)
    {
        list_iterator temp = *this; //调用的是拷贝构造函数，没有调用*构造函数，*this作为拷贝构造函数的参数了
        ++*this; // 调用的是前置++，没有调用*构造函数，*this作为前置++的参数了
        return temp;
    }

    self &operator--()
    {
        ptr = ptr->prev;
        return *this;
    }

    self operator--(int)
    {
        self temp = *this;
        --*this;
        return temp;
    }

    bool operator==(const self &rhs) const { return ptr == rhs.ptr; }

    bool operator!=(const self &rhs) const { return ptr != rhs.ptr; }

};

// list类
template <typename T>
class list
{
private:
    typedef Node<T> list_node;
    typedef list_iterator<T> iterator;

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

// 迭代器
public:
    iterator begin() { return iterator(head); }
    iterator end() { return iterator(nullptr); }

// 运算符重载
public:
    template <typename L>
    friend std::ostream &operator<<(std::ostream &os, const list<L> &pt); // 该函数是友元函数的声明

    // 访问链表中的元素
    T &operator[](size_t index)
    {   
        // 从头节点开始遍历链表，找到**第 index 个节点**
        list_node *current = head;
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
        list_node *current = head;
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

    // 在指定的位置插入元素并返回指向新元素的迭代器
    iterator insert(iterator pos, const T &value) {
        // 创建一个新节点
        list_node *newNode = new list_node(value);

        if (pos.ptr == nullptr) {
            // 如果 pos 为空，则在链表末尾插入新节点
            push_back(value);
            return iterator(tail);
        } 
        else if (pos.ptr == head) {
            // 如果 pos 为头结点，则在链表开头插入新节点
            push_front(value);
            return iterator(head);
        } 
        else {
            // 在 pos 之前插入新节点
            list_node *prevNode = pos.ptr->prev;
            newNode->next = pos.ptr;
            newNode->prev = prevNode;
            prevNode->next = newNode;
            pos.ptr->prev = newNode;
            ++size;
            return iterator(newNode);
        }
    }

    // 归并排序
    /*
    iterator list_sort(iterator first1, iterator last2, size_t n) {
        if (n == 0) {
            return iterator(nullptr);
        }
        if (n == 1) {
            return first1;
        }
        
        size_t n1 = n / 2;
        size_t n2 = n - n1;
        iterator first2 = first1;
        mystl::advance(first2, n1);
        iterator last1 = first2;

        first1 = list_sort(first1, last1, n1);
        first2 = last1 = list_sort(first2, last2, n2);

        // merge
        // 选取两个链表的头结点中较小的一个作为新链表的头结点
        if (*first2 < *first1) {
            // first2为新的头结点
            iterator newHead = first2;

            // 指向末尾元素
            list_node *tail = newHead.ptr;
            while (first2 != last2 && first1 != last1)
            {
                if ( *first1 < *first2 ){
                    iterator next = first1;
                    ++next;

                    // *first1 插入到 *fisrt2的前面
                    list_node *prev_node = first2.ptr->prev;
                    first1.ptr->next = first2.ptr;
                    prev_node->next = first1.ptr;
                    first1.ptr->prev = prev_node;
                    first2.ptr->prev = first1.ptr;
                    first2.ptr->next = nullptr;

                    first1 = next;
                }
                else {
                    tail = first2.ptr;
                    ++first2;
                }
            }

            if ( first1 != last1 ) {
                tail->next = first1.ptr;
                first1.ptr->prev = tail;
                list_node *last1_prev = last1.ptr->prev;
                last1.ptr->prev = nullptr;
                last1_prev->next = nullptr;

            }

            return newHead;
            
            

        } else {
            /// first1为新的头结点
            iterator newHead = first1;

            // 指向末尾元素
            list_node *tail = newHead.ptr;
            while (first2 != last2 && first1 != last1)
            {
                if ( *first2 < *first1 ){
                    iterator next = first2;
                    ++next;

                    // *first2 插入到 *fisrt1的前面
                    list_node *prev_node = first1.ptr->prev;
                    first2.ptr->next = first1.ptr;
                    prev_node->next = first2.ptr;
                    first2.ptr->prev = prev_node;
                    first1.ptr->prev = first2.ptr;
                    first1.ptr->next = nullptr;

                    first2 = next;
                }
                else {
                    tail = first1.ptr;
                    ++first1;
                }
            }

            if ( first2 != last2 ) {
                tail->next = first2.ptr;
                first2.ptr->prev = tail;
                list_node *last1_prev = last2.ptr->prev;
                last2.ptr->prev = nullptr;
                last2.ptr->next = nullptr;

            }

            return newHead;
        }
    }
    void sort() {
        list_sort(begin(), end(), size);
    }
    */
    
    // sort()
    

    void push_back(const T &value){

        list_node *newNode = new list_node(value, nullptr, tail);

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

        list_node *newNode = new list_node(value, head, nullptr);

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
            list_node *newTail = tail->prev;

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
            list_node *newHead = head->next;

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
    list_node *getNode(const T &val)
    {
        list_node *Node = head;
        while (Node != nullptr && Node->data != val)
        {
            Node = Node->next;
        }

        return Node;
    }

    T *find(const T &val)
    {
        list_node *Node = getNode(val);
        if (Node == nullptr)
        {
            return nullptr;
        }
        return &Node->val;
    }

    // 删除指定值的节点
    void remove(const T &val)
    {
        list_node *Node = head;
        while (Node != nullptr && Node->data != val)
        {
            Node = Node->next;
        }

        if (Node == nullptr)
        {
            // 没有找到
            return;
        }
        if (Node != head && Node != tail)
        {
            // 既不是头结点也不是尾结点
            Node->prev->next = Node->next;
            Node->next->prev = Node->prev;
        }
        else if (Node == head && Node == tail)
        {
            // 既是头结点也是尾结点
            head = nullptr;
            Node = nullptr;
        }
        else if (Node == head)
        {
            // 是头结点
            head = Node->next;
            head->prev = nullptr;
        }
        else
        {
            // 是尾结点
            tail = Node->prev;
            tail->next = nullptr;
        }

        --size;

        delete Node;
        Node = nullptr;
    }

    bool empty() { return size == 0; }

    void clear(){
        while (head) {
            list_node *temp = head;
            head = head->next;
            delete temp;
        }

        tail = nullptr;
        size = 0;
    }

    // 打印链表中的元素
    void printElements() const
    {
        for (list_node *current = head; current; current = current->next)
        {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }

public:
    list_node *head;
    list_node *tail;
    size_t size;

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