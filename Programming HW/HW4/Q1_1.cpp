#include <iostream>

#define BUCKETS 65536  // 2^16
#define BASE_N 5

void insertionSort(long *array, long first, long last) {
    for (long k = first + 1; k < last; ++k) {
        long tmp = array[k];
        for (long j = k; j > first; --j) {
            if(array[j -1] > tmp) {
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

long findPivot(long *array, long first, long last) {
    long tmp[3] = {array[first], array[(first + last - 1)/2], array[last - 1]};
    insertionSort(tmp, 0, 3);
    array[first] = tmp[0], array[(first + last - 1)/2] = tmp[2], array[last - 1] = tmp[1];
    long pivot = array[last - 1];
    long i = first - 1;
    for (long j = first; j < last - 1; ++j) {
        if(array[j] <= pivot) {
            ++i;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[last - 1]);
    return i + 1;
}

void quickSort(long *array, long first, long last) {
    if(last - first <= BASE_N) {
        insertionSort(array, first, last);
    } else if (last - first > BASE_N) {
        long pivot = findPivot(array, first, last);
        quickSort(array, first, pivot);
        quickSort(array, pivot + 1, last);
    }
}

struct Node {
    long key;
    long value;
    Node *next_node;

    Node(long k, long v, Node *next_ptr) {
        key = k;
        value = v;
        next_node = next_ptr;
    }
};

struct List {
    Node *list_head;
    Node *list_tail;

    List() {
        list_head = nullptr;
        list_tail = nullptr;
    }

    inline bool isEmpty() const {
        return (list_head == nullptr);
    }

    Node *ascendingSearch(long k) const {
        if(isEmpty()) {
            return nullptr;
        } else {
            for(Node *ptr = list_head; ptr != nullptr; ptr = ptr->next_node) {
                if(ptr->key == k) {
                    return ptr;
                } else if(ptr->key > k) {
                    break;
                }
            }
        }
        return nullptr;
    }

    void pushBack(const long k, const long v) {
        if(isEmpty()) {
            Node *tmp_ptr = new Node(k, v, nullptr);
            list_head = tmp_ptr;
            list_tail = tmp_ptr;
        } else {
            list_tail->next_node = new Node(k, v, nullptr);
            list_tail = list_tail->next_node;
        }
    }
};

struct HashTable {
    long buckets;
    List *table;

    HashTable(long b = 0) {
        buckets = b;
        table = new List[b];
    }

    Node *search(long k) const {
        return table[k & (buckets - 1)].ascendingSearch(k);
    }

    inline void ascendingMap(long k, long v) {
        table[k & (buckets - 1)].pushBack(k, v);
    }
};

int gcd(long num1, long num2) {
    if (num1 == 0)
        return num2;
    else
        return gcd(num2 % num1, num1);
}

// Try Stein's algorithm
/*long gcd(long num1, long num2) {
    if(!num1)
        return num2;
    else if(!num2)
        return num1;
    else if(!((num1 | num2) & 1))
        return gcd(num1 >> 1, num2 >> 1) << 1;
    else if(!(num1 & 1))
        return gcd(num1 >> 1, num2);
    else if(!(num2 & 1))
        return gcd(num1, num2 >> 1);
    else
        return gcd(std::abs(num1 - num2), std::min(num1, num2));
}*/

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    long n, q;
    std::cin >> n;
    long *samples = new long[n];
    for (long i = 0; i < n; ++i) {
        std::cin >> samples[i];
    }
    std::cin >> q;
    long *check = new long[q];
    long *for_sort = new long[q];
    HashTable table(BUCKETS);
    for (long i = 0; i < q; ++i) {
        std::cin >> check[i];
        for_sort[i] = check[i];
        table.ascendingMap(check[i], 0);
    }
    quickSort(for_sort, 0 , q);
    for (long i = 0; i < q; ++i) {
        while((i < q - 1) && (for_sort[i] == for_sort[i + 1]))
            ++i;
        table.ascendingMap(for_sort[i], 0);
    }
    for (long i = 0; i < n; ++i) {
        long k = samples[i];
        for (long j = i; j < n; ++j) {
            k = gcd(samples[j], k);
            Node *node = table.search(k);
            if(node != nullptr) {
                if(k == 1) {
                    node->value = (node->value + n - j);
                    break;
                } else {
                    ++(node->value);
                }
            }
        }
    }
    for (long i = 0; i < q; ++i) {
        std::cout << table.search(check[i])->value << ' ';
    }
    std::cout << std::endl;
    return 0;
}
