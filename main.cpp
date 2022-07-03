#include <vector>
#include <iostream>

using Pair = std::pair<int, int>;

std::vector<Pair> f = {{0, -11}, {0, -8}, {1, 2}};

int foo(Pair x, Pair y) {
    return std::max(x.second, y.second);
}

int main() {
    for (int J = 0; J < 1; J++) {
        f[J] = f[0];
        if(J == 0)
            f[J] = f[2];
        std::cout << foo(f[J], f[1]) << std::endl;
    }
}

