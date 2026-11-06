#ifndef PRESCRIPTION_HPP
#define PRESCRIPTION_HPP
#include <algorithm>
#include <memory>
#include <string>
#include <stdexcept>
#include <utility>
class Prescription {
 int n_;
 std::string* medicines_;
 static int checked(int n){if(n<0)throw std::invalid_argument("negative medicine count");return n;}
public:
 inline static unsigned long long copies=0;
 explicit Prescription(int n):n_{checked(n)},medicines_{new std::string[static_cast<std::size_t>(n_)]}{}
 Prescription(const Prescription& o):Prescription(o.n_){
  for(int i=0;i<n_;++i)medicines_[i]=o.medicines_[i];
  ++copies;
 }
 Prescription& operator=(const Prescription& o){
  if(this!=&o){Prescription copy{o};std::swap(n_,copy.n_);std::swap(medicines_,copy.medicines_);}
  return *this;
 }
 ~Prescription(){delete[] medicines_;}
 int size()const{return n_;}
 void set(int i,const std::string& value){if(i<0||i>=n_)throw std::out_of_range("medicine index");medicines_[i]=value;}
 const std::string& get(int i)const{if(i<0||i>=n_)throw std::out_of_range("medicine index");return medicines_[i];}
};
#endif
