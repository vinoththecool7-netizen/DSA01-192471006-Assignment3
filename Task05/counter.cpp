#include <iostream>
struct Counter {
 int v;
 Counter& operator++() { ++v; return *this; } // prefix
 Counter operator++(int) { Counter old = *this; ++v; return old; } // postfix
};
int main()
{
 Counter c{5};
 Counter a = c++;
 Counter b = ++c;
 std::cout << a.v << ' ' << b.v << ' ' << c.v << '\n';
}
