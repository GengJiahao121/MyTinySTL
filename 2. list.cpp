#pragma once // 用于防止头文件被重复包含

#include <iostream> // std::cin, std::cout, std::cerr, std::clog, ...
#include <stdexcept>  // std::exception, std::runtime_error, std::logic_error, std::out_of_range, std::invalid_argument ... 
#include <algorithm> // std::sort, std::find, std::copy, std::transform, std::accumulate ...
#include <sstream> // std::stringstream, std::istringstream, ostringstream
#include <string> // std::string::size(), std::string::substr(), std::to_string
#include <initializer_list> // for std::initializer_list

template <typename T>
class List
{
public:
    template <typename L>
    friend std::ostream &operator<<(std::ostream &os, const List<L> &pt); // 该函数是友元函数的声明

private:
    struct Node
    {
        T data;
        Node *next;
        Node *prev;

        Node(const T &value, Node *nextNode = nullptr, Node *prevNode = nullptr) 
            : data(value), next(nextNode), prev(prevNode){}   
    };

    Node *head;
    Node *tail;
    size_t size;

public:
    // 无参的构造函数
    List() : head(nullptr), tail(nullptr), size(0){}

    // 初始化列表构造函数
    List(std::initializer_list<T> initList) : head(nullptr), tail(nullptr), size(0){
        for (const T& value : initList){
            push_back(value);
        }
    }
    ~List() { clear(); }

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

    // 使用迭代器遍历链表的开始位置
    Node *begin() { return head; }

    // 使用迭代器遍历链表的结束位置
    Node *end() { return nullptr; }

    // 使用迭代器遍历链表的开始位置（const版本）
    const Node *begin() const { return head; }

    // 使用迭代器遍历链表的结束位置（const版本）
    const Node *end() const { return nullptr; }

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
std::ostream &operator<<(std::ostream &os, const List<T> &pt)
{
    for (typename List<T>::Node *current = pt.head; current;
         current = current->next)
    {
        os << " " << current->data;
    }
    os << std::endl;
    return os;
}

int main() {

    // 使用参数列表初始化列表
    List<int> myList1 = {1, 2, 3, 4, 5, 6};
    myList1.printElements();

    // 创建一个 List 对象
    List<int> myList;
    
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
            myList.push_back(value);
        }

        if (command == "push_front") {
            iss >> value;
            myList.push_front(value);
        }

        if (command == "pop_back") {
            myList.pop_back();
        }

        if (command == "pop_front") {
            myList.pop_front();
        }

        if (command == "remove") {
            iss >> value;
            myList.remove(value);
        }

        if (command == "clear") {
            myList.clear();
        }

        if (command == "size") {
            std::cout << myList.getSize() << std::endl;
        }

        if (command == "get") {
            iss >> value;
            std::cout << myList[value] << std::endl;
        }

        if (command == "print") {
            if (myList.getSize() == 0) {
                std::cout << "empty" << std::endl;
            } else {
                myList.printElements();
            }
        }

        if (command == "print_cout") {
            std::cout << myList;
        }

        if (command == "getNode"){
            std::cout << myList.getNode(2)->data << std::endl;
        }
    }
    return 0;
}