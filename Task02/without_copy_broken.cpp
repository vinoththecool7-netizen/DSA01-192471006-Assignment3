#include <iostream>
#include <string>
class Prescription {
 int n;
 std::string* medicines; // dynamically allocated array
public:
 explicit Prescription(int count) : n(count), medicines(new std::string[count]) {}
 // TODO 1 replaced: independent deep-copy constructor.
 // TODO 2 replaced: transactional allocation and self-assignment guard.
 Prescription& operator=(const Prescription& other) {
  if(this==&other)return *this;
  std::string* fresh=new std::string[other.n];
  try {for(int i=0;i<other.n;++i)fresh[i]=other.medicines[i];}
  catch (...) {delete[] fresh;throw;}
  delete[] medicines;medicines=fresh;n=other.n;return *this;
 }
 ~Prescription()
 {
 // TODO 3 replaced: matching array deletion.
 delete[] medicines;
 }
 void set(int i, const std::string& m) { medicines[i] = m; }
 std::string get(int i) const { return medicines[i]; }
};
int main()
{
 Prescription p(2);
 p.set(0, "Paracetamol");
 p.set(1, "ORS");
 Prescription q = p; // copy constructor
 q.set(1, "Cetirizine");
 Prescription r(1);
 r = p; // copy assignment
 p.set(0, "Ibuprofen");
 std::cout << p.get(0) << ' ' << p.get(1) << " | " << q.get(0) << ' ' << q.get(1)
 << " | " << r.get(0) << ' ' << r.get(1) << '\n';
}
