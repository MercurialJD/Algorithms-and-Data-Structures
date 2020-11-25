#include <iostream>

#define NO_SOLUTION -1

template <class T>
class Node {
private:
    T element;
    Node *next_node;
public:
    Node(T = NULL, Node<T> * = nullptr);
    T retrieve() const;
    Node<T> *getNext() const;
    void setElement(const T &);
    void setNext(Node<T> *);
};

template <class T>
Node<T>::Node(T ele, Node *next_ptr) {
    element = ele;
    next_node = next_ptr;
}

template <class T>
T Node<T>::retrieve() const {
    return element;
}

template <class T>
Node<T> *Node<T>::getNext() const {
    return next_node;
}

template <class T>
void Node<T>::setElement(const T & ele) {
    element = ele;
}

template <class T>
void Node<T>::setNext(Node<T> *next_ptr) {
    next_node = next_ptr;
}

class UnderFlow {
};

template <class T>
class SingleList {
private:
    Node<T> *list_head;
    Node<T> *list_tail;
    int size;
public:
    SingleList();
    SingleList(const SingleList &);

    //Accessors
    bool isEmpty() const;
    int getSize() const;
    T getFrontValue() const;
    Node<T> *getHead() const;
    Node<T> *getTail() const;

    //Mutators
    void pushFront(const T &);
    void pushBack(const T &);
    int eraseTarget(const T &);
};

template <class T>
SingleList<T>::SingleList() {
    list_head = nullptr;
    list_tail = nullptr;
    size = 0;
}

template <class T>
SingleList<T>::SingleList(const SingleList<T> & list) {
    list_head = nullptr;
    list_tail = nullptr;
    if(list.isEmpty()) {
        return;
    }
    pushFront(list.getFrontValue());
    for(Node<T> *original = list.getHead()->getNext(), *copy = getHead(); original != nullptr; original = original->getNext(), copy = copy->getNext()) {
        copy->setNext(new Node<T>(original->retrieve(), nullptr));
        list_tail = copy->getNext();
    }
    size = list.getSize();
}

template <class T>
bool SingleList<T>::isEmpty() const {
    return (list_head == nullptr);
}

template <class T>
int SingleList<T>::getSize() const {
    return size;
}

template <class T>
T SingleList<T>::getFrontValue() const {
    if(isEmpty())	{
        throw UnderFlow();
    }
    return getHead()->retrieve();
}

template <class T>
Node<T> *SingleList<T>::getHead() const {
    return list_head;
}

template <class T>
Node<T> *SingleList<T>::getTail() const {
    return list_tail;
}

template <class T>
void SingleList<T>::pushFront(const T & ele) {
    if(isEmpty()) {
        Node<T> *tmp_ptr = new Node<T>(ele, nullptr);
        list_head = tmp_ptr;
        list_tail = tmp_ptr;
    } else {
        list_head = new Node<T>(ele, getHead());
    }
    ++size;
}

template <class T>
void SingleList<T>::pushBack(const T & ele) {
    if(isEmpty()) {
        Node<T> *tmp_ptr = new Node<T>(ele, nullptr);
        list_head = tmp_ptr;
        list_tail = tmp_ptr;
    } else {
        list_tail->setNext(new Node<T>(ele, nullptr));
        list_tail = getTail()->getNext();
    }
    ++size;
}

template <class T>
int SingleList<T>::eraseTarget(const T & target) {
    if(isEmpty()) {
        throw UnderFlow();
    }
    int erase_count = 0;
    Node<T> *pre_ptr = nullptr;
    for(Node<T> *ptr = getHead(); ptr != nullptr; ptr = ptr->getNext()) {
        while(ptr->retrieve() == target) {
            if(ptr->getNext() != nullptr) {
                Node<T> *tmp_ptr = ptr->getNext();
                ptr->setElement(tmp_ptr->retrieve());
                ptr->setNext(tmp_ptr->getNext());
                tmp_ptr->setNext(nullptr);
                delete tmp_ptr;
                --size;
                ++erase_count;
            } else {
                if(pre_ptr == nullptr) {
                    list_head = nullptr;
                    list_tail = nullptr;
                    delete ptr;
                    --size;
                    ++erase_count;
                } else {
                    pre_ptr->setNext(nullptr);
                    delete ptr;
                    --size;
                    ++erase_count;
                    list_tail = pre_ptr;
                }
                return erase_count;
            }
        }
        pre_ptr = ptr;
    }
    return erase_count;
}

template <class T>
class TreeAsList {
private:
    int index;
    T decay_from_parent;
    TreeAsList *parent_node;
    SingleList<TreeAsList *> children;
public:
    TreeAsList(T const & = T(), TreeAsList * = nullptr);

    //Accessors
    int getIndex() const ;
    int getDegree() const;
    int getDecay() const;
    bool isRoot() const;
    bool isLeaf() const;
    TreeAsList *getParent() const;
    TreeAsList *getChild(int) const;
    int getHeight() const;

    //Mutators
    void setDecay(T);
    void setParent(TreeAsList *);
    void attach(TreeAsList *);
    void detach();
};

template <class T>
TreeAsList<T>::TreeAsList(T const & ele, TreeAsList *parent_ptr) {
    index = ele;
    decay_from_parent = 0;
    setParent(parent_ptr);
}

template <class T>
int TreeAsList<T>::getIndex() const {
    return index;
}

template <class T>
int TreeAsList<T>::getDegree()	const {
    return children.getSize();
}

template <class T>
int TreeAsList<T>::getDecay() const {
    return decay_from_parent;
}

template <class T>
bool TreeAsList<T>::isRoot() const {
    return (getParent() == nullptr);
}

template <class T>
bool TreeAsList<T>::isLeaf() const {
    return (getDegree() == 0);
}

template <class T>
TreeAsList<T> *TreeAsList<T>::getParent() const {
    return parent_node;
}

template <class T>
TreeAsList<T> *TreeAsList<T>::getChild(int n) const {
    if(n < 0 || n >= getDegree()) {
        return nullptr;
    }
    Node<TreeAsList<T> *> *node_ptr = children.getHead();
    for(int i = 0; i < n; i++) {
        node_ptr = node_ptr->getNext();
    }
    return node_ptr->retrieve();
}

template <class T>int TreeAsList<T>::getHeight() const {
    int height = 0;
    for(Node<TreeAsList<T> *> *node_ptr = children.getHead(); node_ptr != nullptr; node_ptr = node_ptr->getNext()) {
        height = std::max(height, 1 + node_ptr->retrieve()->getHeight());
    }
    return height;
}

template <class T>
void TreeAsList<T>::setDecay(T decay) {
    decay_from_parent = decay;
}

template <class T>
void TreeAsList<T>::setParent(TreeAsList<T> *parent_ptr) {
    parent_node = parent_ptr;
}

template <class T>
void TreeAsList<T>::attach(TreeAsList<T> *subtree) {
    if(!subtree->isRoot()) {
        subtree->detach();
    }
    subtree->setParent(this);
    children.pushBack(subtree);
}

template <class T>
void TreeAsList<T>::detach() {
    if(isRoot()) {
        return;
    }
    getParent()->children.eraseTarget(this);
    setParent(nullptr);
}

//Up is a template of tree structure
//Down is the main algorithm

template <class T>
static TreeAsList<T> *node_list;
int total_nodes = 0;
int initial_strength = 0;
int max_decay = 0;

template <class T>
void buildTree() {
    std::cin >> total_nodes;
    getchar();
    node_list<T> = new TreeAsList<T>[total_nodes];
    for(int i = 0; i < total_nodes; i++) {
        node_list<T>[i] = TreeAsList<T>(i);
    }
    for (int i = 0; i < total_nodes; ++i) {
        int this_child_count = 0;
        std::cin >> this_child_count;
        for (int j = 0; j < this_child_count; ++j) {
            int child_index, decay_to_child;
            std::cin >> child_index >> decay_to_child;
            max_decay = (decay_to_child > max_decay) ? decay_to_child : max_decay;
            node_list<T>[i].attach(&node_list<T>[child_index - 1]);
            node_list<T>[child_index - 1].setDecay(decay_to_child);
        }
    }
    std::cin >> initial_strength;
}

template <class T>
int processTree() {
    if(max_decay > initial_strength) {
        return NO_SOLUTION;
    }
    int *amp_list = new int[total_nodes];
    for (int i = 0; i < total_nodes; ++i) {
        amp_list[i] = 0;
    }
    traverseChildrenGetDecay(&node_list<T>[0], amp_list);
    int amp_count = 0;
    for (int i = 1; i < total_nodes; ++i) {
        if(amp_list[i] == 1) {
            amp_count++;
            //std::cout << i + 1 << std::endl;
        }
    }
    delete [] amp_list;
    return amp_count;
}

template <class T>
int traverseChildrenGetDecay(TreeAsList<T> *this_node, int *amp_list) {
    if(!this_node->isLeaf()) {
        int max_branch_sum_decay = 0;
        for(int i = 0; i < this_node->getDegree(); i++) {
            int this_branch_decay = traverseChildrenGetDecay(this_node->getChild(i), amp_list);
            max_branch_sum_decay = ((max_branch_sum_decay > this_branch_decay) ? max_branch_sum_decay : this_branch_decay);
        }
        if(max_branch_sum_decay + this_node->getDecay() > initial_strength) {
            amp_list[this_node->getIndex()] = 1;
            return this_node->getDecay();
        } else {
            return (max_branch_sum_decay + this_node->getDecay());
        }
    } else {
        return this_node->getDecay();
    }
}

int main() {
    buildTree<int>();
    int amp_count = processTree<int>();
    if(amp_count == NO_SOLUTION) {
        std::cout << "No solution.";
    } else {
        std::cout << amp_count;
    }
    delete [] node_list<int>;
    return 0;
}
