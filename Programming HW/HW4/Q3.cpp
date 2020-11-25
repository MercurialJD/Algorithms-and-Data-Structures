#include <iostream>

#define N 5

template <class T>
void insertionSort(T *array, int first, int last) {
    for (int k = first + 1; k < last; ++k) {
        T tmp = array[k];
        for (int j = k; j > first; --j) {
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

template <class T>
int findPivot(T *array, int first, int last) {
    T tmp[3] = {array[first], array[(first + last - 1)/2], array[last - 1]};
    insertionSort(tmp, 0, 3);
    array[first] = tmp[0], array[(first + last - 1)/2] = tmp[2], array[last - 1] = tmp[1];
    T pivot = array[last - 1];
    int i = first - 1;
    for (int j = first; j < last - 1; ++j) {
        if(array[j] <= pivot) {
            ++i;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[last - 1]);
    return i + 1;
}

template <class T>
void quickSort(T *array, int first, int last) {
    if(last - first <= 	N) {
        insertionSort(array, first, last);
    } else if (last - first > N) {
        int pivot = findPivot(array, first, last);
        quickSort(array, first, pivot);
        quickSort(array, pivot + 1, last);
    }
}

int main() {
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
    int n = 0, m = 0;
    std::cin >> n >> m;
    long *dragons_hp = new long[n];
    long *knights_cost = new long[m];
    for (int i = 0; i < n; ++i) {
        std::cin >> dragons_hp[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> knights_cost[i];
    }
    quickSort(dragons_hp, 0, n);
    quickSort(knights_cost, 0, m);
    int dragon_index = 0;
    int knight_index = 0;
    long total_cost = 0;
    while(dragon_index < n && knight_index < m) {
        if(dragons_hp[dragon_index] <= knights_cost[knight_index]) {
            total_cost += knights_cost[knight_index];
            ++dragon_index;
            ++knight_index;
        } else {
            ++knight_index;
        }
    }
    if(dragon_index == n) {
        std::cout << total_cost << std::endl;
    } else {
        std::cout << "you died!" <<std::endl;
    }
    return 0;
}