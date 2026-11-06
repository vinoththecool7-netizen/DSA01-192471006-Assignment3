#include <iomanip>
#include <iostream>
class Money {
 long long paise;
public:
 Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}
 // TODO 1 replaced: value result.
 Money operator+(const Money& other) const {Money result;result.paise=paise+other.paise;return result;}
 // TODO 2 replaced: member equality and friend insertion.
 bool operator==(const Money& other) const {return paise==other.paise;}
 friend std::ostream& operator<<(std::ostream& out,const Money& m){
  return out<<"Rs "<<m.paise/100<<'.'<<std::setw(2)<<std::setfill('0')<<m.paise%100<<std::setfill(' ');
 }
};
int main()
{
 Money a(120, 75), b(79, 25);
 Money c = a + b;
 std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';
}
