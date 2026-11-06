#include <iostream>
#include <string>
class Prescription {
 std::string* names;
public:
 Prescription():names{new std::string[2]{"A","B"}}{}
 ~Prescription(){delete[] names;}
 void set(const std::string& s){names[0]=s;}
 const std::string& get()const{return names[0];}
 // Intentionally no copy constructor: the owned pointer is copied.
};
int main(){Prescription p;Prescription q=p;q.set("Changed");std::cout<<"original="<<p.get()<<std::endl;}
