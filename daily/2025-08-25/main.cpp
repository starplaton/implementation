// Allowed: <iostream>, <cstdio>, malloc/free
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long n;
    if (!(std::cin >> n)) return 0;

    long long sum = 0;
    for (long long i = 0; i < n; ++i) {
        long long x;
        std::cin >> x;
        sum += x;
    }
    std::cout << sum << '\n';
    return 0;
}
