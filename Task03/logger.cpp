#include <iostream>
#include <string>
struct Logger {
 std::string n;
 Logger(const std::string& s) : n(s) { std::cout << '+' << n << ' '; }
 Logger(const Logger& o) : n(o.n + "c") { std::cout << "copy" << n << ' '; }
 ~Logger() { std::cout << '-' << n << ' '; }
};
void use(Logger) { std::cout << "use "; }
int main()
{
 Logger a("A");
 {
 Logger b("B");
 }
 use(a);
 Logger* p = new Logger("P");
 delete p;
 std::cout << "end ";
}
