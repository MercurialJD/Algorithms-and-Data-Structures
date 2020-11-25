#include <iostream>

template <class T>
class Node {
private:
    T kind;
    int quantity;
    Node *down_node;
    Node *up_node;
public:
    Node(T = NULL, int = 0, Node<T> *down_ptr = nullptr, Node<T> *up_ptr = nullptr);
    T retrieveKind() const;
    int retrieveQuantity() const;
    Node<T> *getDown() const;
    Node<T> *getUp() const;
    void setKind(const T &);
    void setQuantity(int);
    void setDown(Node<T> *);
    void setUp(Node<T> *);
};

template <class T>
Node<T>::Node(T input_kind, int input_quantity, Node *down_ptr, Node *up_ptr) {
    kind = input_kind;
    quantity = input_quantity;
    down_node = down_ptr;
    up_node = up_ptr;
}

template <class T>
T Node<T>::retrieveKind() const {
    return kind;
}

template <class T>
int Node<T>::retrieveQuantity() const {
    return quantity;
}

template <class T>
Node<T> *Node<T>::getDown() const {
    return down_node;
}

template <class T>
Node<T> *Node<T>::getUp() const {
    return up_node;
}

template <class T>
void Node<T>::setKind(const T & input_kind) {
    kind = input_kind;
}

template <class T>
void Node<T>::setQuantity(int input_quantity) {
    quantity = input_quantity;
}

template <class T>
void Node<T>::setDown(Node<T> *down_ptr) {
    down_node = down_ptr;
}

template <class T>
void Node<T>::setUp(Node<T> *up_ptr) {
    up_node = up_ptr;
}

class UnderFlow {
};

template <class T>
class DoubleList {
private:
    Node<T> *list_bottom;
    Node<T> *list_top;
    int size;
public:
    DoubleList();
    DoubleList(const DoubleList &);

    //Accessors
    bool isEmpty() const;
    int getSize() const;
    T getBottomKind() const;
    Node<T> *getBottom() const;
    Node<T> *getTop() const;

    //Mutators
    void eraseNode(Node<T> *);
    void pushTop(const T &, int);
    T popBottom();
    void changeSize(int);
};

template <class T>
DoubleList<T>::DoubleList() {
    list_bottom = nullptr;
    list_top = nullptr;
    size = 0;
}

template <class T>
DoubleList<T>::DoubleList(const DoubleList<T> & list) {
    list_bottom = nullptr;
    list_top = nullptr;
    if(list.isEmpty()) {
        return;
    }
    pushBottom(list.getBottomKind());
    for(Node<T> *original = list.getBottom()->getUp(), *copy = getBottom(); original != nullptr; original = original->getUp(), copy = copy->getUp()) {
        copy->setUp(new Node<T>(original->retrieveKind(), nullptr));
        list_top = copy->getUp();
    }
    size = list.getSize();
}

template <class T>
bool DoubleList<T>::isEmpty() const {
    return (list_bottom == nullptr);
}

template <class T>
int DoubleList<T>::getSize() const {
    return size;
}

template <class T>
T DoubleList<T>::getBottomKind() const {
    if(isEmpty())	{
        throw UnderFlow();
    }
    return getBottom()->retrieveKind();
}

template <class T>
Node<T> *DoubleList<T>::getBottom() const {
    return list_bottom;
}

template <class T>
Node<T> *DoubleList<T>::getTop() const {
    return list_top;
}

template <class T>
void DoubleList<T>::eraseNode(Node<T> *node) {
    if(isEmpty()) {
        throw UnderFlow();
    }
    Node<T> *tmp_ptr = node;
    if(tmp_ptr->getDown() && tmp_ptr->getUp()) {
        tmp_ptr->getDown()->setUp(tmp_ptr->getUp());
        tmp_ptr->getUp()->setDown(tmp_ptr->getDown());
    } else if(tmp_ptr->getDown() == nullptr && tmp_ptr->getUp() != nullptr) {
        tmp_ptr->getUp()->setDown(nullptr);
        list_bottom = tmp_ptr->getUp();
    } else if(tmp_ptr->getUp() == nullptr && tmp_ptr->getDown() != nullptr) {
        tmp_ptr->getDown()->setUp(nullptr);
        list_top = tmp_ptr->getDown();
    } else {
        list_top = nullptr;
        list_bottom = nullptr;
    }
    delete(tmp_ptr);
    --size;
}

template <class T>
void DoubleList<T>::pushTop(const T & ele, int num) {
    if(isEmpty()) {
        Node<T> *tmp_ptr = new Node<T>(ele, num, nullptr, nullptr);
        list_bottom = tmp_ptr;
        list_top = tmp_ptr;
    } else {
        list_top->setUp(new Node<T>(ele, num, list_top, nullptr));
        list_top = getTop()->getUp();
    }
    size += num;
}

template <class T>
T DoubleList<T>::popBottom() {
    if(isEmpty()) {
        throw UnderFlow();
    }
    T e = getBottomKind();
    Node<T> *tmp_ptr = list_bottom;
    int list_bottom_pre_quantity = list_bottom->retrieveQuantity();
    if(list_bottom_pre_quantity > 1) {
        list_bottom->setQuantity(list_bottom_pre_quantity - 1);
        --size;
    } else {
        eraseNode(tmp_ptr);
    }
    return e;
}

template <class T>
void DoubleList<T>::changeSize(int change) {
    size += change;
}

void processInputRules(int **rules_array, int rules_count) {
    for (int i = 0; i < rules_count; ++i) {
        int fir_substance, sec_substance, compound;
        std::cin >> fir_substance >> sec_substance >> compound;
        rules_array[fir_substance][sec_substance] = compound;
        rules_array[sec_substance][fir_substance] = compound;
    }
}

template <class T>
bool combineSubstance(DoubleList<T> *furnace, Node<T> *down_ptr, Node<T> *up_ptr) {
    if(down_ptr->retrieveKind() == up_ptr->retrieveKind()) {
        down_ptr->setQuantity(down_ptr->retrieveQuantity() + up_ptr->retrieveQuantity());
        furnace->eraseNode(up_ptr);
        return true;
    } else {
        return false;
    }
}

template <class T>
void operate(DoubleList<T> *furnace, int **rules_array) {
    Node<T> *pre_top = furnace->getTop();
    int substance_index, substance_quantity;
    std::cin >> substance_index >> substance_quantity;
    if(substance_index == -1) {
        for (int i = 0; i < substance_quantity; ++i) {
            furnace->popBottom();
        }
        return;
    } else if(substance_quantity == 0) {
        return;
    } else {
        furnace->pushTop(substance_index, substance_quantity);
        if(furnace->getTop()->getDown()) {
            combineSubstance(furnace, furnace->getTop()->getDown(), furnace->getTop());
        }
    }
    if(pre_top == nullptr || pre_top == furnace->getTop()) {
        return;
    } else {
        while(true) {
            Node<T> *tmp_ptr = pre_top;
            bool no_reaction_happen = true;
            //std::cout << 1;
            while(reactTwoLayers(furnace, tmp_ptr, rules_array)) {
                //std::cout << 2;
                no_reaction_happen = false;
                if(tmp_ptr->getDown()) {
                    tmp_ptr = tmp_ptr->getDown();
                } else {
                    break;
                }
            }
            while(tmp_ptr->getUp() && !no_reaction_happen) {
                if(reactTwoLayers(furnace, tmp_ptr, rules_array) && tmp_ptr->getDown() && tmp_ptr->getDown()->getDown()) {
                    tmp_ptr = tmp_ptr->getDown()->getDown();
                }
                //std::cout << 3;
                if(tmp_ptr->getUp()) {
                    tmp_ptr = tmp_ptr->getUp();
                } else {
                    break;
                }
            }
            if(!tmp_ptr->getDown()) {
                break;
            }
            pre_top = tmp_ptr->getDown();
            if(no_reaction_happen) break;
        }
    }
}

template <class T>
bool reactTwoLayers(DoubleList<T> *furnace, Node<T> *down_ptr, int **rules_array) {
    if(down_ptr->getUp()) {
        combineSubstance(furnace, down_ptr, down_ptr->getUp());
    }
    if(down_ptr->getDown()) {
        combineSubstance(furnace, down_ptr->getDown(), down_ptr);
    }
    int compound = rules_array[down_ptr->retrieveKind()][down_ptr->getUp()->retrieveKind()];
    if(compound != -1) {
        int down_node_quantity = down_ptr->retrieveQuantity();
        int up_node_quantity = down_ptr->getUp()->retrieveQuantity();
        int reaction_quantity = (down_node_quantity < up_node_quantity) ? down_node_quantity : up_node_quantity;
        if(down_node_quantity > up_node_quantity) {
            down_ptr->setQuantity(down_node_quantity - reaction_quantity);
            down_ptr->getUp()->setKind(compound);
            down_ptr->getUp()->setQuantity(reaction_quantity);
        } else if(down_node_quantity < up_node_quantity) {
            down_ptr->getUp()->setQuantity(up_node_quantity - reaction_quantity);
            down_ptr->setKind(compound);
            down_ptr->setQuantity(reaction_quantity);
        } else {
            down_ptr->setKind(compound);
            down_ptr->setQuantity(reaction_quantity);
            furnace->eraseNode(down_ptr->getUp());
            //std::cout << 4;
        }
        return true;
    } else {
        return false;
    }
}

int main() {
    int substance_kinds_count, rules_count, operations_count;
    std::cin >> substance_kinds_count >> rules_count >> operations_count;
    int **rules_array = new int *[substance_kinds_count];
    for (int i = 0; i < substance_kinds_count; ++i) {
        rules_array[i] = new int [substance_kinds_count];
        for (int j = 0; j < substance_kinds_count; ++j) {
            rules_array[i][j] = -1;
        }
    }
    processInputRules(rules_array, rules_count);
    //processInputRules Test
    /*for (int i = 0; i < rules_count; ++i) {
        std::cout << i << ' ';
        for (int j = 0; j < rules_count; ++j) {
            if(rules_array[i][j] != -1) {
                std::cout << j << '(' << rules_array[i][j] << ')' << ' ';
            }
        }
        std::cout << std::endl;
    }*/
    DoubleList<int> furnace;
    for (int i = 0; i < operations_count; ++i) {
        operate(&furnace, rules_array);
    }
    Node<int> *traversing_ptr = furnace.getBottom();
    int sum = 0;
    while(traversing_ptr) {
        sum += traversing_ptr->retrieveQuantity();
        traversing_ptr = traversing_ptr->getUp();
    }
    std::cout << sum;
}
