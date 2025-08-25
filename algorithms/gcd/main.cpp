#include <iostream>

long long gcd_ll(long long a, long long b);

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    if (!(std::cin >> T)) return 0;
    while (T--) {
        long long a, b;
        std::cin >> a >> b;
        long long g = gcd_ll(a, b);
        std::cout << g << '\n';
    }
    return 0;
}
