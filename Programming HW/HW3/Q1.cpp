#include <iostream>

template <class T>
class DoubleNode {
private:
    T remain_size;
    T count;
    DoubleNode *pre_node;
    DoubleNode *next_node;
public:
    explicit DoubleNode(T = 0, T = 0, DoubleNode<T> * = nullptr, DoubleNode<T> * = nullptr);
    inline T retrieveRemainSize() const;
    inline T retrieveCount() const;
    inline DoubleNode<T> *getPre() const;
    inline DoubleNode<T> *getNext() const;
    void setRemainSize(const T &);
    void setCount(const T &);
    void setPre(DoubleNode<T> *);
    void setNext(DoubleNode<T> *);
};

template <class T>
DoubleNode<T>::DoubleNode(T size, T num, DoubleNode *pre_ptr, DoubleNode *next_ptr) {
    remain_size = size;
    count = num;
    pre_node = pre_ptr;
    next_node = next_ptr;
}

template <class T>
T DoubleNode<T>::retrieveRemainSize() const {
    return remain_size;
}

template <class T>
T DoubleNode<T>::retrieveCount() const {
    return count;
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
void DoubleNode<T>::setRemainSize(const T & size) {
    remain_size = size;
}

template <class T>
void DoubleNode<T>::setCount(const T & num) {
    count = num;
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
    T getFrontValue() const;
    inline DoubleNode<T> *getHead() const;
    inline DoubleNode<T> *getTail() const;

    //Mutators
    void pushFront(const T &, const T &);
    void pushBack(const T &, const T &);
    void pushBack(DoubleNode<T> *);
    T popFront();
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
T DoubleList<T>::getFrontValue() const {
    if(isEmpty())	{
        throw UnderFlow();
    }
    return getHead()->retrieveCount();
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
void DoubleList<T>::pushFront(const T & i, const T & num) {
    if(isEmpty()) {
        DoubleNode<T> *tmp_ptr = new DoubleNode<T>(i, num, nullptr, nullptr);
        list_head = tmp_ptr;
        list_tail = tmp_ptr;
    } else {
        list_head->setPre(new DoubleNode<T>(i, num, nullptr, getHead()));
        list_head = list_head->getPre();
    }
    ++size;
}

template <class T>
void DoubleList<T>::pushBack(const T & i, const T & num) {
    if(isEmpty()) {
        DoubleNode<T> *tmp_ptr = new DoubleNode<T>(i, num, nullptr, nullptr);
        list_head = tmp_ptr;
        list_tail = tmp_ptr;
    } else {
        list_tail->setNext(new DoubleNode<T>(i, num, getTail(), nullptr));
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
T DoubleList<T>::popFront() {
    if(isEmpty()) {
        throw UnderFlow();
    }
    T e = getFrontValue();
    DoubleNode<T> *tmp_ptr = list_head;
    list_head = list_head->getNext();
    tmp_ptr->setNext(nullptr);
    delete tmp_ptr;
    --size;
    if(list_head == nullptr) {
        list_tail = nullptr;
    } else {
        list_head->setPre(nullptr);
    }
    return e;
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
    size--;
}

//Upward is a template of double linked list
//Downward is the algorithm

long long *initial_mem_array;
long total_chips = 0;

template <class T>
DoubleNode<T> **erase_mem_array;

template <class T>
void processInput() {
    std::cin >> total_chips;
    initial_mem_array = new long long[total_chips];
    erase_mem_array<T> = new DoubleNode<T>* [total_chips];
    for(long i = 0; i < total_chips; ++i) {
        std::cin >> initial_mem_array[i];
    }
}

template <class T>
void startExperiments() {
    DoubleList<T> remain_list;
    for (long i = 0; i < total_chips; ++i) {
        long today_consumption = 0;
        long erase_count = 0;
        std::cin >> today_consumption;
        long long new_mem = initial_mem_array[i];
        long long acc_mem_consumption = 0;
        if(new_mem > today_consumption) {
            bool mem_found = false;
            for (DoubleNode<T> *ptr = remain_list.getHead(); ptr != nullptr; ptr = ptr->getNext()) {
                if (ptr->retrieveRemainSize() == new_mem) {
                    mem_found = true;
                    ptr->setCount(ptr->retrieveCount() + 1);
                }
                if (ptr->retrieveRemainSize() > today_consumption) {
                    ptr->setRemainSize(ptr->retrieveRemainSize() - today_consumption);
                    acc_mem_consumption += today_consumption * (ptr->retrieveCount());
                } else {
                    acc_mem_consumption += (ptr->retrieveRemainSize()) * (ptr->retrieveCount());
                    erase_mem_array<T>[erase_count] = ptr;
                    erase_count++;
                }
            }
            if(!mem_found) {
                remain_list.pushBack((new_mem - today_consumption), 1);
                acc_mem_consumption += today_consumption;
            }
        } else {
            acc_mem_consumption += new_mem;
            for (DoubleNode<T> *ptr = remain_list.getHead(); ptr != nullptr; ptr = ptr->getNext()) {
                if (ptr->retrieveRemainSize() > today_consumption) {
                    ptr->setRemainSize(ptr->retrieveRemainSize() - today_consumption);
                    acc_mem_consumption += today_consumption * (ptr->retrieveCount());
                } else {
                    acc_mem_consumption += (ptr->retrieveRemainSize()) * (ptr->retrieveCount());
                    erase_mem_array<T>[erase_count] = ptr;
                    erase_count++;
                }
            }
        }
        for(long j = 0; j < erase_count; j++) {
            remain_list.erasePointed(erase_mem_array<T>[j]);
        }
        std::cout << acc_mem_consumption << " ";
    }
}

int main() {
    processInput<long long>();
    startExperiments<long long>();
    return 0;
}