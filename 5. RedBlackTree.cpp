#include <iostream>
#include <sstream>
#include <string>

enum class Color {RED, BLACK};

template <typename Key, typename Value>
class RedBlackTree {
    class Node{
    public:
        Key key;
        Value value;
        Color color;
        Node *left;
        Node *right;
        Node *parent;

        Node(const Key &k, const Value &v, Color c, Node *p = nullptr)
            : key(k), value(v), color(c), left(nullptr), right(nullptr), parent(p) {}

        Node()
            : color(Color::BLACK), left(nullptr), right(nullptr), parent(nullptr) {}
    };

private:
    Node *root;
    size_t size;
    Node *Nil;

    Node *lookUp(Key key) {
        Node *cmpNode = root;
        while (cmpNode) {
            if (key < cmpNode->key) {
                cmpNode = cmpNode->left;
            } else if (key > cmpNode->key) {
                cmpNode = cmpNode->right;
            } else {
                return cmpNode;
            }
        }
        return cmpNode;
    }

    // 右旋
    /*
    解释：与左旋相反，节点x的左孩子y变成x的父节点，x变成了y的右孩子。**如果y有一个右孩子，它会变成x的左孩子。**
    */
    void rightRotate(Node *node) {
        Node *l_son = node->left; // 获取当前节点的左子节点

        /*
        需要考虑的指针变换：
        1. 如何当前结点的左孩子有一个**右孩子**， 要变成当前指针的左孩子
        2. 当前结点和其左孩子结点之间交换（节点x的左孩子y变成x的父节点，x变成了y的右孩子）
        3. 更新所有结点的父亲结点
        4. 更新所有结点的所有孩子指针（不要忘了更新原始当前结点的父亲结点的左右孩子指针，因为涉及到一个结点的变换）
        */
       node->left = l_son->right;
       if (l_son->right) {
            l_son->right->parent = node;
       }

       l_son->parent = node->parent;
       if (!node->parent){
            root = l_son;
       }else if (node == node->parent->left) {
            node->parent->left = l_son;
       }else{
            node->parent->right = l_son;
       }

       l_son->right = node;
       node->parent = l_son;
    }

    // 左旋
    // 是右旋的对称情况, 逻辑和右旋是一样的
    /*
    解释：节点x的右孩子y变成x的父节点，x变成了y的左孩子。**如果y有一个左孩子，它会变成x的右孩子。**
    */
    void leftRotate(Node *node) {
        Node *r_son = node->right;

        node->right = r_son->left;

        if (r_son->left) {
            r_son->left->parent = node;
        }

        r_son->parent = node->parent;
        if (!node->parent) {
            root = r_son;
        } else if (node == node->parent->left) {
            node->parent->left = r_son;
        } else {
            node->parent->right = r_son;
        }

        r_son->left = node;
        node->parent = r_son;
    }

    // 插入修复函数
    /*
    红黑树：左根右、根叶黑、不红红、黑路同
    插入结点默认是红色
    1. 插入结点是根结点 -> 直接变黑
    2. 插入结点的叔叔是红色 -> 1. father, uncle, grandfather红变黑、黑变红 2. 爷爷变插入结点
    3. 插入结点的叔叔是黑色（或者为空结点） -> 1. (LL, RR, LR, RL)旋转（爷爷为旋转点、父亲为旋转中心点） 2. 旋转点、中心点变色（注意RL, LR）
    */
    void insertFixup(Node *target) {
        while(target->parent && target->parent->color == Color::RED) {
            // 1. 父节点是爷爷节点的左孩子
            if (target->parent == target->parent->parent->left) {
                Node *uncle = target->parent->parent->right;
                // 1.1 叔叔节点为红色
                if (uncle && uncle->color == Color::RED){
                    /*
                    1.1.1 更改叔叔节点和父节点为黑色
                    1.1.2 将爷爷节点设为红色
                    1.1.3 以爷爷节点为目标继续判断是否需要调整
                    */
                    target->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;          // 叔叔节点设为黑色
                    target->parent->parent->color = Color::RED; // 祖父节点设为红色
                    target = target->parent->parent; 
                }
                // 1.2 叔叔节点为黑色或者不存在
                else
                {
                    /*
                    1.2.1 如果新节点是父节点的右孩子, 将操作的目标节点变为其父亲, 并左旋（如果新节点是父节点的左孩子，直接进行第二步）
                    1.2.2 将操作节点(可能因为上一步的左旋, 操作节点发生了变化)设为黑色, 爷爷节点设为红色
                    1.2.3 右旋爷爷节点
                    */
                    if (target == target->parent->right) {
                        target = target->parent;
                        leftRotate(target);
                    }
                    target->parent->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    rightRotate(target->parent->parent);
                }
            }
            // 2. 父节点是爷爷节点的右孩子
            else
            {
                // 当目标节点的父节点是祖父节点的右子节点时，与上面对称
                Node *uncle = target->parent->parent->left; // 叔叔节点
                // 2.1 叔叔节点为红色
                if (uncle && uncle->color == Color::RED) {
                    /*
                    2.1.1 更改叔叔节点和父节点为黑色
                    2.1.2 将爷爷节点设为红色
                    2.1.3 以爷爷节点为目标继续判断是否需要调整
                    */
                    target->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    target = target->parent->parent;
                } 
                // 2.2 叔叔节点为黑色或者不存在
                else 
                {   
                    /*
                    2.2.1 如果新节点是父节点的左孩子, 将操作的目标节点变为其父亲, 并右旋（如果新节点是父节点的右孩子，直接进行第二步）
                    2.2.2 将操作节点(可能因为上一步的右旋, 操作节点发生了变化)设为黑色, 爷爷节点设为红色
                    2.2.3 左旋爷爷节点
                    */
                    if (target == target->parent->left) {
                        target = target->parent; // 更新目标节点为父节点
                        rightRotate(target);     // 对目标节点进行右旋
                    }

                    // 调整父节点和祖父节点的颜色，并进行左旋转
                    target->parent->color = Color::BLACK;
                    target->parent->parent->color = Color::RED;
                    leftRotate(target->parent->parent);
                }
            }
        }
        // 能需要向上递归地进行调整，直到根节点，或者直到不再违反红黑树的性质为止。

        // 确保根节点始终为黑色
        root->color = Color::BLACK;
    }

    // 插入节点函数
    /*
    当我们向红黑树中插入一个元素时，会执行以下步骤：
        定位插入位置： 从根节点开始，按照二叉查找树的规则，找到合适的插入位置。
        插入新节点： 在插入位置创建一个新节点，并将其颜色设为红色。
        修复红黑树性质： 如果新节点的父节点是红色，需要通过一系列旋转和重新着色操作来保持红黑树的平衡。
    */
    void insertNode(const Key &key, const Value &value) {
        // 创建一个新节点，节点的颜色初始化为红色
        Node *newNode = new Node(key, value, Color::RED);
        Node *parent = nullptr; // 新节点的父节点指针
        Node *cmpNode = root;   // 用于比较的节点，初始为根节点

        // 遍历树，找到新节点的正确位置
        while (cmpNode) {
            parent = cmpNode; // 保留当前节点作为新节点的潜在父节点
            // 如果新节点的键小于当前比较节点的键，则向左子树移动
            if (newNode->key < cmpNode->key) {
                cmpNode = cmpNode->left;
                // 如果新节点的键大于当前比较节点的键，则向右子树移动
            } else if (newNode->key > cmpNode->key) {
                cmpNode = cmpNode->right;
                // 如果键相等，则说明树中已有相同键的节点，删除新节点并返回
            } else {
                delete newNode;
                return;
            }
        }

        // 树的大小增加
        size++;

        // 将新节点的父节点设置为找到的父节点位置
        newNode->parent = parent;
        // 如果父节点为空，说明树是空的，新节点成为根节点
        if (!parent) {
            root = newNode;
            // 如果新节点的键小于父节点的键，将新节点插入父节点的左子树
        } else if (newNode->key < parent->key) {
            parent->left = newNode;
            // 否则，将新节点插入父节点的右子树
        } else {
            parent->right = newNode;
        }

        // 插入新节点后，调用insertFixup函数来修复可能破坏的红黑树性质
        insertFixup(newNode);
    }

    // 中序遍历
    void inorderTraversal(Node *node) const {
        if (node) {
            inorderTraversal(node->left);
            std::cout << node->key << " ";
            std::cout << node->value << " ";
            inorderTraversal(node->right);
        }
    }

    // 辅助函数，用新节点替换旧节点
    void replaceNode(Node *targetNode, Node *newNode) {
        if (!targetNode->parent) {
            root = newNode;
        } else if (targetNode == targetNode->parent->left) {
            targetNode->parent->left = newNode;
        } else {
            targetNode->parent->right = newNode;
        }

        if (newNode) {
            newNode->parent = targetNode->parent;
        }
    }

    // 寻找以某个节点为根节点的子树中的最小节点
    Node *findMinimumNode(Node *node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    // removeFixup函数用于在删除节点后恢复红黑树的性质
    /*
    红黑树删除：
        1. 只有左/右孩子 -> 左/右孩子代替后变黑
        2. 没有孩子 -> 直接删除 -> **调整红黑树**
        3. 有左右孩子 -> 找到直接前驱去代替（左子树中最大/右子树中最小）-> 结点颜色为原始结点颜色
            替代结点处理（相当于删除替代结点）：
                1. 只有左/右孩子 -> 左/右孩子代替后变黑
                2. 没有孩子 -> 直接删除 -> **调整红黑树**

    -> 总结：可归纳为两种情况 要删除的结点 -> 1. 没有孩子 2. 只有左/右孩子
                
    ---> 调整
        1. 只有左/右孩子
            -> 只能有黑结点为父结点，红结点为其左孩子或者右孩子两种情况（否则会违反黑路同性质）
            -> 左/右孩子代替后变黑
        
        2. 没有孩子
            -> 结点为红色：删除后无需任何调整
            -> 结点为黑色：必然需要调整（违反黑路同）
                -> 删除后变双黑
                -> 调整：
                    -> 兄弟为黑色：
                        -> 兄弟至少有一个红孩子：（LL,RR,LR,RL）变色+旋转
                            p（兄弟的父结点） s(兄弟结点) r（红孩子）
                            -> LL: 1. 变色（r变s，s变p，p变黑） 2. 右旋 3. 双黑变单黑(对称)
                            -> RR: 1. 变色（r变s，s变p，p变黑） 2. 左旋 3. 双黑变单黑(对称)

                            -> LR: 1. 变色（r变p，p变黑）2. 左旋左孩子 3. 右旋 4. 双黑变单黑(对称)
                            -> RL: 1. 变色（r变p，p变黑）2. 右旋右孩子 3. 左旋 4. 双黑变单黑(对称)
                        -> 兄弟的孩子结点都是黑色：
                            -> 兄弟变红，双黑上移（调整双黑结点的父结点）
                                —> 1. 遇红变单黑
                                -> 2. 遇黑根据兄弟结点情况调整 -> 双黑变单黑
                                -> 3. 遇根变单黑
                    -> 兄弟为红色：
                        -> 兄父变色，朝双黑旋转，保持双黑继续调整
    */
    void removeFixup(Node *node) {
        // 如果节点为Nil并且没有父节点，说明它是唯一的节点，直接返回
        if (node == Nil && node->parent == nullptr) {
            return;
        }

        // 当我们没有到达根节点时继续循环
        // 如果节点为Nil并且没有父节点，说明它是唯一的节点，直接返回
        if (node == Nil && node->parent == nullptr) {
            return;
        }

        // 当我们没有到达根节点时继续循环
        while (node != root) {
            // 如果节点是其父节点的左子节点
            if (node == node->parent->left) {
                // 兄弟节点是节点父亲的右子节点
                Node *sibling = node->parent->right;

                // 情况1：节点的兄弟节点是红色
                if (getColor(sibling) == Color::RED) {
                    // 重新着色兄弟节点和父节点，并进行左旋
                    setColor(sibling, Color::BLACK);
                    setColor(node->parent, Color::RED);
                    leftRotate(node->parent);
                    // 旋转后更新兄弟节点
                    sibling = node->parent->right;
                }

                // 情况2：兄弟节点的两个子节点都是黑色
                if (getColor(sibling->left) == Color::BLACK &&
                    getColor(sibling->right) == Color::BLACK) {
                    // 重新着色兄弟节点并向上移动
                    setColor(sibling, Color::RED);
                    node = node->parent;
                    // 如果父节点是红色，将其改为黑色并结束
                    if (node->color == Color::RED) {
                        node->color = Color::BLACK;
                        node = root;
                    }
                } else {
                    // 情况3：兄弟节点的右子节点是黑色（左子节点是红色）
                    if (getColor(sibling->right) == Color::BLACK) {
                        // 重新着色兄弟节点和兄弟节点的左子节点，并进行右旋
                        setColor(sibling->left, Color::BLACK);
                        setColor(sibling, Color::RED);
                        rightRotate(sibling);
                        // 旋转后更新兄弟节点
                        sibling = node->parent->right;
                    }

                    // 情况4：兄弟节点的右子节点是红色
                    setColor(sibling, getColor(node->parent));
                    setColor(node->parent, Color::BLACK);
                    setColor(sibling->right, Color::BLACK);
                    leftRotate(node->parent);
                    // 移动到根节点结束
                    node = root;
                }
            } else {
                // 当节点是其父节点的右子节点时，对称的情况
                Node *sibling = node->parent->left;

                if (getColor(sibling) == Color::RED) {
                    setColor(sibling, Color::BLACK);
                    setColor(node->parent, Color::RED);
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }

                if (getColor(sibling->right) == Color::BLACK && getColor(sibling->left) == Color::BLACK) 
                {
                    setColor(sibling, Color::RED);
                    node = node->parent;
                    if (node->color == Color::RED) {
                        node->color = Color::BLACK;
                        node = root;
                    }
                } 
                else 
                {
                    if (getColor(sibling->left) == Color::BLACK) 
                    {
                        setColor(sibling->right, Color::BLACK);
                        setColor(sibling, Color::RED);
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }
                    setColor(sibling, getColor(node->parent));
                    setColor(node->parent, Color::BLACK);
                    setColor(sibling->left, Color::BLACK);
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        // 确保当前节点是黑色的，以维持红黑树性质
        setColor(node, Color::BLACK);
    }

    // 获取颜色, 空指针为黑色
    Color getColor(Node *node) {
        if (node == nullptr) {
            return Color::BLACK;
        }
        return node->color;
    }

    void setColor(Node *node, Color color) {
        if (node == nullptr) {
            return;
        }
        node->color = color;
    }

    // 取消Nil哨兵的连接
    void dieConnectNil() {
        if (Nil == nullptr) {
            return;
        }
        if (Nil->parent != nullptr) {
            if (Nil == Nil->parent->left) {
                Nil->parent->left = nullptr;
            } else {
                Nil->parent->right = nullptr;
            }
        }
    }

    // 删除节点
    void deleteNode(Node *del){
        Node *rep = del; // rep（替代节点）初始指向要删除的节点
        Node *child = nullptr; // 要删除节点的孩子节点
        Node *parentRP; // 替代节点的父节点
        Color origCol = rep->color; // 保存要删除节点的原始颜色

        // 如果删除节点没有左孩子，用右孩子替换
        if (!del->left){
            rep = del->right; 
            parentRP = del->parent; // parentRP为删除结点的父结点（替换结点未来的父结点）
            origCol = getColor(rep); // 替代结点的原始颜色
            replaceNode(del, rep);
        }
        // 如果删除节点没有右孩子
        else if (!del->right) {
            rep = del->left;         // 替代节点指向删除节点的左孩子
            parentRP = del->parent;  // 更新替代节点的父节点
            origCol = getColor(rep); // 获取替代节点的颜色
            replaceNode(del, rep);   // 用替代节点替换删除节点
        }
        // 如果删除的结点有左右两个孩子
        else {
            rep = findMinimumNode(del->right); // 找到删除节点右子树中的最小节点作为替代节点
            origCol = rep->color; // 保存替代节点的原始颜色(可理解为原始位置由替代结点替换后，颜色是由替代结点决定的)
            // 如果替代节点不是删除节点的直接右孩子
            if (rep != del->right) 
            {
                parentRP = rep->parent; // 更新替代节点的父节点
                child = rep->right; // 替代节点的右孩子变成要处理的孩子节点
                parentRP->left = child; // 替代节点的父节点的左孩子指向替代节点的孩子（因为替代节点是最小节点，所以不可能有左孩子）
                if (child != nullptr) {
                    child->parent = parentRP; // 如果替代节点的孩子存在，则更新其父节点
                }
                // 将替代节点放到删除节点的位置
                del->left->parent = rep;
                del->right->parent = rep;
                rep->left = del->left;
                rep->right = del->right;

                if (del->parent) {
                    if (del == del->parent->left){
                        del->parent->left = rep;
                        rep->parent = del->parent;
                    } else {
                        del->parent->right = rep;
                        rep->parent = del->parent;
                    }
                }else{
                    root = rep;
                    rep->parent = nullptr;
                }
            
            }
            // 如果替代节点是删除节点的直接右孩子
            else
            {
                child = rep->right; // 孩子节点指向替代节点的右孩子（只可能有右孩子）
                rep->left = del->left; // 替代节点的左孩子指向删除节点的左孩子
                del->left->parent = rep; // 更新左孩子的父节点
                // 更新删除节点父节点的孩子指向
                if (del->parent != nullptr) {
                    if (del == del->parent->left) {
                        del->parent->left = rep;
                        rep->parent = del->parent;
                    } else {
                        del->parent->right = rep;
                        rep->parent = del->parent;
                    }
                }
                // 如果删除节点是根节点
                else {
                    root = rep;
                    root->parent = nullptr;
                }
                parentRP = rep; // 更新替代节点的父节点
            }
        }

        // 如果替代节点存在，更新其颜色为删除节点的颜色
        if (rep != nullptr) {
            rep->color = del->color;
        }
        // 如果替代节点不存在，将删除节点的颜色赋给origCol变量
        else {
            origCol = del->color;
        }

        // 如果原始颜色是黑色，需要进行额外的修复操作，因为黑色节点的删除可能会破坏红黑树的性质
        /*
        为什么原始原色为红色就不需要修复？
        
        */
        if (origCol == Color::BLACK) {
            // 如果存在孩子节点，进行修复操作
            if (child != nullptr) {
                removeFixup(child);
            }
            // 如果不存在孩子节点，将Nil节点（代表空节点）的父节点设置为替代节点的父节点
            else{
                Nil->parent = parentRP;
                // 如果替代节点的父节点存在，设置其对应的孩子指针为Nil节点
                if (parentRP != nullptr) {
                    if (parentRP->left == nullptr) {
                        parentRP->left = Nil;
                    } else {
                        parentRP->right = Nil;
                    }
                }

                // 进行修复操作
                removeFixup(Nil);
                // 断开Nil节点与树的连接，因为在红黑树中Nil节点通常是单独存在的
                dieConnectNil();
            }
        }
        // 删除节点
        delete del;
    }

public:
    // 构造函数
    RedBlackTree() : root(nullptr), size(0), Nil(new Node()) {
        Nil->color = Color::BLACK;
    }

    // 插入
    void insert(const Key &key, const Value &value) { insertNode(key, value); }

    // 删除
    void remove(const Key &key) {
        Node *nodeToBeRemoved = lookUp(key);
        if (nodeToBeRemoved != nullptr) {
            deleteNode(nodeToBeRemoved);
            size--;
        }
    }

    Value *at(const Key &key){
        auto ans = lookUp(key);
        if (ans != nullptr){
            return &ans->value;
        }
        return nullptr;
    }

    int getSize() {return size; }

    bool empty() { return size == 0; }

    // 中序遍历打印
    void print() {
        inorderTraversal(root);
        std::cout << std::endl;
    }

    void clear() {
        deleteNode(root);
        size = 0;
    }

    // 析构函数
    ~RedBlackTree() {
        // 释放节点内存
        deleteTree(root);
    }

private:
     // 递归释放节点内存
    void deleteTree(Node *node) {
        if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        }
  }
};

/*
int main(){
    RedBlackTree<int, int> rbTree;

    int N;
    std::cin >> N;
    getchar();

    std::string line;
    for (int i = 0; i < N; i++){
        std::getline(std::cin, line);
        std::istringstream iss(line);

        std::string command;
        iss >> command;

        int key;
        int value;

        if (command == "insert"){
            iss >> key >> value;
            rbTree.insert(key, value);
        }

        if (command == "size")
        {
            std::cout << rbTree.getSize() << std::endl;
        }

        if (command == "at")
        {
            iss >> key;
            int *res = rbTree.at(key);
            if (res == nullptr)
            {
                std::cout << "not exist" << std::endl;
            }
            else
            {
                std::cout << *res << std::endl;
            }
        }

        if (command == "remove")
        {
            iss >> key;
            rbTree.remove(key);
        }


        if (command == "print")
        {
            if (rbTree.empty())
            {
                std::cout << "empty" << std::endl;
            }
            else
            {
                rbTree.print();
            }
        }

    }

    return 0;
}
*/
