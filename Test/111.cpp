

#include <iostream>


class List {

private:

    struct Node {
    int data;
    Node *next;
    Node *prev;

    Node(int val) : data(val), next(nullptr), prev(nullptr) {}

    friend std::ostream &operator<<(std::ostream &os, const Node *node) {
        os << node->data;
        return os;
    }
};
public:
    List() : head(nullptr), tail(nullptr) {}

    struct Iterator
    {
        Node *node;
        Iterator(Node *node) : node(node) {}

        Iterator &operator++() {
            node = node->next;
            return *this;
        }

        bool operator!=(const Iterator &it) {
            return node != it.node;
        }

        Node *operator*() {
            return node;
        }
    };

    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
    

    void push_back(const int &val) {
        Node *node = new Node(val);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }

public:
    Node *head;
    Node *tail;
};


int main(){

    List list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);

    for (auto it : list)
        std::cout << it << std::endl;

    return 0;
}
