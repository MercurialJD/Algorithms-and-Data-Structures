#include <iostream>

#define BUCKETS 262144  //2^18

template <class T>
class DoubleNode {
private:
    T key;
    T value;
    DoubleNode *pre_node;
    DoubleNode *next_node;
public:
    explicit DoubleNode(T = NULL, T  = NULL, DoubleNode<T> * = nullptr, DoubleNode<T> * = nullptr);
    inline constexpr T retrieveKey() const;
    inline constexpr T retrieveValue() const;
    inline constexpr DoubleNode<T> * getPre() const;
    inline constexpr DoubleNode<T> * getNext() const;
    inline void setValue(const T &);
    inline void setPre(DoubleNode<T> * &&);
    inline void setNext(DoubleNode<T> * &&);
};

template <class T>
DoubleNode<T>::DoubleNode(T k, T v, DoubleNode *pre_ptr, DoubleNode *next_ptr) {
    key = k;
    value = v;
    pre_node = pre_ptr;
    next_node = next_ptr;
}
template <class T>
constexpr T DoubleNode<T>::retrieveKey() const {
    return key;
}

template <class T>
constexpr T DoubleNode<T>::retrieveValue() const {
    return value;
}

template <class T>
constexpr DoubleNode<T> *DoubleNode<T>::getPre() const {
    return pre_node;
}

template <class T>
constexpr DoubleNode<T> *DoubleNode<T>::getNext() const {
    return next_node;
}

template <class T>
void DoubleNode<T>::setValue(const T & v) {
    value = v;
}

template <class T>
void DoubleNode<T>::setPre(DoubleNode<T> * && pre_ptr) {
    pre_node = pre_ptr;
}

template <class T>
void DoubleNode<T>::setNext(DoubleNode<T> * && next_ptr) {
    next_node = next_ptr;
}

template <class T>
class DoubleList {
private:
    DoubleNode<T> *list_head;
    DoubleNode<T> *list_tail;
public:
    DoubleList();

    //Accessors
    inline constexpr bool isEmpty() const;
    inline constexpr DoubleNode<T> *getHead() const;
    inline constexpr DoubleNode<T> *getTail() const;
    DoubleNode<T> *searchByKey(T &) const;

    //Mutators
    void pushBack(const T &, const T &);
};

template <class T>
DoubleList<T>::DoubleList() {
    list_head = nullptr;
    list_tail = nullptr;
}

template <class T>
constexpr bool DoubleList<T>::isEmpty() const {
    return (list_head == nullptr);
}

template <class T>
constexpr DoubleNode<T> *DoubleList<T>::getHead() const {
    return list_head;
}

template <class T>
constexpr DoubleNode<T> *DoubleList<T>::getTail() const {
    return list_tail;
}

template <class T>
DoubleNode<T> *DoubleList<T>::searchByKey(T & k) const {
    if(isEmpty()) {
        return nullptr;
    } else {
        for(DoubleNode<T> *ptr = getHead(); ptr != nullptr; ptr = ptr->getNext()) {
            if(ptr->retrieveKey() == k) {
                return ptr;
            }
        }
    }
    return nullptr;
}

template <class T>
void DoubleList<T>::pushBack(const T & k, const T & v) {
    if(isEmpty()) {
        DoubleNode<T> *tmp_ptr = new DoubleNode<T>(k, v, nullptr, nullptr);
        list_head = tmp_ptr;
        list_tail = tmp_ptr;
    } else {
        list_tail->setNext(new DoubleNode<T>(k, v, getTail(), nullptr));
        list_tail = list_tail->getNext();
    }
}

template <class T>
class HashTable {
private:
    int buckets;
    DoubleList<T> *table;
public:
    explicit HashTable(int = 0);
    inline int findBucket(T &) const;
    DoubleNode<T> *searchByKey(T &) const;
    DoubleNode<T> * && map(T &, T &&);
};

template <class T>
HashTable<T>::HashTable(int b) {
    buckets = b;
    table = new DoubleList<T>[b];
}

template <class T>
int HashTable<T>::findBucket(T & k) const {
    return k & (buckets - 1);
}

template <class T>
DoubleNode<T> *HashTable<T>::searchByKey(T & k) const {
    return table[findBucket(k)].searchByKey(k);
}

template <class T>
DoubleNode<T> * && HashTable<T>::map(T & k, T && v) {
    DoubleNode<T> *tmp = searchByKey(k);
    if(tmp == nullptr) {
        table[findBucket(k)].pushBack(k, v);
    } else {
        tmp->setValue(v);
    }
    return std::move(tmp);
}


template <class T>
int gcd(T num1, T num2)
{
    if (num1 == 0)
        return num2;
    else
        return gcd(num2 % num1, num1);
}


int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    HashTable<long> table(BUCKETS);
    int && n = 0;
    std::cin >> n;
    long *samples = new long[n];
    for (int && i = 0; i < n; ++i) {
        std::cin >> samples[i];
    }
    int && q = 0;
    std::cin >> q;
    long *check = new long[q];
    for (int && i = 0; i < q; ++i) {
        long && tmp = 0;
        std::cin >> tmp;
        table.map(tmp, 0);
        check[i] = tmp;
    }
    for (int && i = 0; i < n; ++i) {
        long k = samples[i];
        for (int j = i; j < n; ++j) {
            k = gcd(samples[j], k);
            DoubleNode<long> *node = table.searchByKey(k);
            if(node != nullptr) {
                if(k == 1) {
                    node->setValue(node->retrieveValue() + n - j);
                    break;
                } else {
                    node->setValue(node->retrieveValue() + 1);
                }
            } else {
                continue;
            }
        }
    }
    bool && first_flag = true;
    for (int && i = 0; i < q; ++i) {
        if(first_flag) {
            std::cout << table.searchByKey(check[i])->retrieveValue();
            first_flag = false;
        }
        else
            std::cout << ' ' << table.searchByKey(check[i])->retrieveValue();
    }
    std::cout << std::endl;
    return 0;
}