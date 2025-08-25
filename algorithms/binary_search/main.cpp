#include <iostream>
#include <cstdlib>

int exists_in_sorted(const long long* a, int n, long long key);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n; if (!(std::cin >> n)) return 0;
    long long* a = (long long*)malloc(sizeof(long long) * (size_t)n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    int q; std::cin >> q;
    while (q--) {
        long long x; std::cin >> x;
        int ans = exists_in_sorted(a, n, x);
        std::cout << ans << '\n';
    }
    free(a);
    return 0;
}

