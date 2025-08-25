#include <iostream>

bool is_prime_ll(long long n);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    if (!(std::cin >> T)) return 0;
    while (T--) {
        long long n;
        std::cin >> n;
        bool ok = is_prime_ll(n);
        std::cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}
