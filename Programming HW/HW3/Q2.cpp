#include <iostream>

template <class T>
class DoubleNode {
private:
    T vertex_1;
    T vertex_2;
    T weight;
    DoubleNode *pre_node;
    DoubleNode *next_node;
public:
    explicit DoubleNode(T = 0, T = 0, T = 0, DoubleNode<T> * = nullptr, DoubleNode<T> * = nullptr);
    inline T retrieveFromVertex() const;
    inline T retrieveToVertex() const;
    inline T retrieveWeight() const;
    inline DoubleNode<T> *getPre() const;
    inline DoubleNode<T> *getNext() const;
    void setFromVertex(const T &);
    void setToVertex(const T &);
    void setWeight(const T &);
    void setPre(DoubleNode<T> *);
    void setNext(DoubleNode<T> *);
};

template <class T>
DoubleNode<T>::DoubleNode(T vtx_1, T vtx_2, T num, DoubleNode *pre_ptr, DoubleNode *next_ptr) {
    vertex_1 = vtx_1;
    vertex_2 = vtx_2;
    weight = num;
    pre_node = pre_ptr;
    next_node = next_ptr;
}

template <class T>
T DoubleNode<T>::retrieveFromVertex() const {
    return vertex_1;
}

template <class T>
T DoubleNode<T>::retrieveToVertex() const {
    return vertex_2;
}

template <class T>
T DoubleNode<T>::retrieveWeight() const {
    return weight;
}

template <class T>
DoubleNode<T> *DoubleNode<T>::getPre() const {
    return pre_node;
}

template <class T>
DoubleNode<T> *DoubleNode<T>::getNext() const {
    return next_node;
}

template <class T>
void DoubleNode<T>::setFromVertex(const T & num) {
    vertex_1 = num;
}

template <class T>
void DoubleNode<T>::setToVertex(const T & num) {
    vertex_2 = num;
}

template <class T>
void DoubleNode<T>::setWeight(const T & num) {
    weight = num;
}

template <class T>
void DoubleNode<T>::setPre(DoubleNode<T> *pre_ptr) {
    pre_node = pre_ptr;
}

template <class T>
void DoubleNode<T>::setNext(DoubleNode<T> *next_ptr) {
    next_node = next_ptr;
}


class UnderFlow {
};


template <class T>
class DoubleList {
private:
    DoubleNode<T> *list_head;
    DoubleNode<T> *list_tail;
    int size;
public:
    DoubleList();

    //Accessors
    inline bool isEmpty() const;
    inline int getSize() const;
    inline DoubleNode<T> *getHead() const;
    inline DoubleNode<T> *getTail() const;

    //Mutators
    void pushFront(const T &, const T &, const T &);
    void pushBack(const T &, const T &, const T &);
    void pushBack(DoubleNode<T> *);
    void insertBefore(DoubleNode<T> * , const T & , const T & , const T & );
    void erasePointed(DoubleNode<T> *);
};

template <class T>
DoubleList<T>::DoubleList() {
    list_head = nullptr;
    list_tail = nullptr;
    size = 0;
}

template <class T>
bool DoubleList<T>::isEmpty() const {
    return (list_head == nullptr);
}

template <class T>
int DoubleList<T>::getSize() const {
    return size;
}

template <class T>
DoubleNode<T> *DoubleList<T>::getHead() const {
    return list_head;
}

template <class T>
DoubleNode<T> *DoubleList<T>::getTail() const {
    return list_tail;
}

template <class T>
void DoubleList<T>::pushFront(const T & vertex_1, const T & vertex_2, const T & weight) {
    if(isEmpty()) {
        DoubleNode<T> *tmp_ptr = new DoubleNode<T>(vertex_1, vertex_2, weight, nullptr, nullptr);
        list_head = tmp_ptr;
        list_tail = tmp_ptr;
    } else {
        list_head->setPre(new DoubleNode<T>(vertex_1, vertex_2, weight, nullptr, getHead()));
        list_head = list_head->getPre();
    }
    ++size;
}

template <class T>
void DoubleList<T>::pushBack(const T & vertex_1, const T & vertex_2, const T & weight) {
    if(isEmpty()) {
        DoubleNode<T> *tmp_ptr = new DoubleNode<T>(vertex_1, vertex_2, weight, nullptr, nullptr);
        list_head = tmp_ptr;
        list_tail = tmp_ptr;
    } else {
        list_tail->setNext(new DoubleNode<T>(vertex_1, vertex_2, weight, getTail(), nullptr));
        list_tail = list_tail->getNext();
    }
    ++size;
}

template <class T>
void DoubleList<T>::pushBack(DoubleNode<T> *ptr) {
    if(isEmpty()) {
        list_head = list_tail = ptr;
    } else {
        ptr->setPre(list_tail);
        list_tail->setNext(ptr);
        list_tail = ptr;
    }
    ++size;
}

template <class T>
void DoubleList<T>::insertBefore(DoubleNode<T> *ptr, const T & vtx_1, const T & vtx_2, const T & weight) {
    if(ptr->getPre() == nullptr) {
        ptr->setPre(new DoubleNode<T>(vtx_1, vtx_2, weight, nullptr, ptr));
        list_head = ptr->getPre();
    } else {
        DoubleNode<T> *tmp_ptr = new DoubleNode<T>(vtx_1, vtx_2, weight, ptr->getPre(), ptr);
        (ptr->getPre())->setNext(tmp_ptr);
        ptr->setPre(tmp_ptr);
    }
    ++size;
}

template <class T>
void DoubleList<T>::erasePointed(DoubleNode<T> *target) {
    if(target->getPre() != nullptr && target->getNext() != nullptr) {
        (target->getNext())->setPre(target->getPre());
        (target->getPre())->setNext(target->getNext());
        target->setNext(nullptr);
        target->setPre(nullptr);
        delete(target);
    } else if(target->getPre() != nullptr && target->getNext() == nullptr) {
        list_tail = target->getPre();
        list_tail->setNext(nullptr);
        target->setPre(nullptr);
        delete(target);
    } else if(target->getPre() == nullptr && target->getNext() != nullptr) {
        list_head = target->getNext();
        list_head->setPre(nullptr);
        target->setNext(nullptr);
        delete(target);
    } else {
        delete(target);
        list_head = list_tail = nullptr;
    }
    --size;
}

//Upward is a template of double linked list
//Downward is the algorithm

int n, m, k;
int effective_count = 0;
int *vertex_map_array;
int **length_matrix;
bool **connect_matrix;
int *shortest_path;

template <class T>
DoubleList<T> shortest_edges;

template <class T>
void findShortestEdges() {
    std::cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        T vtx_1, vtx_2, weight;
        std::cin >> vtx_1 >> vtx_2 >> weight;
        if(shortest_edges<T>.isEmpty()) {
            shortest_edges<T>.pushFront(vtx_1, vtx_2, weight);
        } else {
            if(shortest_edges<T>.getSize() == k) {
                if(weight >= (shortest_edges<T>.getTail())->retrieveWeight()) {
                    continue;
                } else {
                    for(DoubleNode<T> *ptr = shortest_edges<T>.getTail(); ptr != nullptr; ptr = ptr->getPre()) {
                        if(ptr->getPre() == nullptr) {
                            shortest_edges<T>.insertBefore(ptr, vtx_1, vtx_2, weight);
                            break;
                        } else {
                            if(weight <= ptr->retrieveWeight() && weight >= (ptr->getPre())->retrieveWeight()) {
                                shortest_edges<T>.insertBefore(ptr, vtx_1, vtx_2, weight);
                                break;
                            }
                        }
                    }
                    shortest_edges<T>.erasePointed(shortest_edges<T>.getTail());
                }
            } else if(shortest_edges<T>.getSize() < k) {
                if(weight > (shortest_edges<T>.getTail())->retrieveWeight()) {
                    shortest_edges<T>.pushBack(vtx_1, vtx_2, weight);
                } else {
                    for(DoubleNode<T> *ptr = shortest_edges<T>.getTail(); ptr != nullptr; ptr = ptr->getPre()) {
                        if(ptr->getPre() == nullptr) {
                            shortest_edges<T>.insertBefore(ptr, vtx_1, vtx_2, weight);
                            break;
                        } else {
                            if(weight <= ptr->retrieveWeight() && weight >= (ptr->getPre())->retrieveWeight()) {
                                shortest_edges<T>.insertBefore(ptr, vtx_1, vtx_2, weight);
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

int searchEntry(int vertex) {
    for (int i = 0; i < effective_count; ++i) {
        if(vertex_map_array[i] == vertex) {
            return i;
        }
    }
    return -1;
}

template <class T>
void buildMatrix() {
    vertex_map_array = new T [2 * k];
    length_matrix = new T* [2 * k];
    connect_matrix = new bool* [2 * k];
    for (int i = 0; i < 2 * k; ++i) {
        length_matrix[i] = new T [2 * k];
        connect_matrix[i] = new bool [2 * k];
        for (int j = 0; j < 2 * k; ++j) {
            length_matrix[i][j] = int(10e9);
            connect_matrix[i][j] = false;
        }
        length_matrix[i][i] = 0;
    }
    for(DoubleNode<T> *ptr = shortest_edges<T>.getHead(); ptr != nullptr; ptr = ptr->getNext()) {
        T vtx_1 = ptr->retrieveFromVertex(), vtx_2 = ptr->retrieveToVertex();
        int entry_1, entry_2;
        if((entry_1 = searchEntry(vtx_1)) == -1) {
            vertex_map_array[effective_count] = vtx_1;
            entry_1 = effective_count;
            ++effective_count;
        }
        if((entry_2 = searchEntry(vtx_2)) == -1) {
            vertex_map_array[effective_count] = vtx_2;
            entry_2 = effective_count;
            ++effective_count;
        }
        length_matrix[entry_1][entry_2] = ptr->retrieveWeight();
        length_matrix[entry_2][entry_1] = ptr->retrieveWeight();
        connect_matrix[entry_1][entry_2] = true;
        connect_matrix[entry_2][entry_1] = true;
    }
}

void insertionSort(int *array, int first, int last) {
    for(int s = first + 1; s < last; s++) {
        int tmp = array[s];
        for(int j = s; j > first; --j) {
            if(array[j - 1] > tmp) {
                array[j] = array[j - 1];
            } else {
                array[j] = tmp;
                goto finish;
            }
        }
        array[first] = tmp;
        finish: ;
    }
}

template <class T>
void findShortestPath() {
    for(int s = 0; s < effective_count; s++) {
        for (int i = 0; i < effective_count; ++i) {
            for (int j = 0; j < effective_count; ++j) {
                if(connect_matrix[i][s] && connect_matrix[s][j]) {
                    length_matrix[i][j] = std::min(length_matrix[i][j], length_matrix[i][s] + length_matrix[s][j]);
                    connect_matrix[i][j] = connect_matrix[i][j] || (connect_matrix[i][s] && connect_matrix[s][j]);
                }
                if(connect_matrix[j][s] && connect_matrix[s][i]) {
                    length_matrix[j][i] = std::min(length_matrix[j][i], length_matrix[j][s] + length_matrix[s][i]);
                    connect_matrix[j][i] = connect_matrix[j][i] || (connect_matrix[j][s] && connect_matrix[s][i]);
                }
            }
        }
    }
    shortest_path = new T [effective_count * effective_count];
    int count = 0;
    for (int i = 0; i < effective_count; ++i) {
        for (int j = 0; j < i; ++j) {
            if(connect_matrix[i][j]) {
                shortest_path[count] = length_matrix[i][j];
                ++count;
            }
        }
    }
    insertionSort(shortest_path, 0, count);
}

int main() {
    findShortestEdges<int>();
    buildMatrix<int>();
    findShortestPath<int>();
    std::cout << shortest_path[k - 1];
    return 0;
}