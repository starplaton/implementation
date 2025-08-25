#include <iostream>

void sort_inplace(long long* a, int n);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;
    long long* a = (long long*)malloc(sizeof(long long) * (size_t)n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    sort_inplace(a, n);
    for (int i = 0; i < n; ++i) {
        if (i) std::cout << ' ';
        std::cout << a[i];
    }
    std::cout << '\n';
    free(a);
    return 0;
}
