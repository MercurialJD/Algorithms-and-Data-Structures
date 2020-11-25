#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int *queue = new int[n];
    for(int i = 0; i < n; i++) {
        std::cin >> queue[i];
    }
    int pair_count = 0;
    for(int i = 0; i < n - 1; i++) {
        ++pair_count;
        int max_height = queue[i + 1];
        if(i + 1 == n - 1) {
            break;
        }
        for(int j = i + 2; j < n; j++) {
            if(max_height > queue[i]) {
                break;
            }
            if(max_height > queue[j]) {
                continue;
            }
            ++pair_count;
            max_height = (max_height < queue[j]) ? queue[j] : max_height;
        }
    }
    std::cout << pair_count;
    delete queue;
    return 0;
}