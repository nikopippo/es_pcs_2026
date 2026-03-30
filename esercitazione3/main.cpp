#include "rational.hpp"

int main() {
    rational<int> a(4, 2);
    rational<int> b(-0, 4);

    rational<int> c = a + b;
    std::cout << "a + b = " << c << "\n";

    rational<int> d = a * b;
    std::cout << "a * b = " << d << "\n";

    rational<int> e = a / rational<int>(0, 1);
    std::cout << "a / 0 = " << e << "\n";

    return 0;
}