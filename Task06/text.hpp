#ifndef TEXT_HPP
#define TEXT_HPP
#include <cstring>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <utility>
class Text {
 std::size_t length_;
 char* data_;
 struct Sized{};
 Text(std::size_t n,Sized):length_{n},data_{nullptr}{if(n==std::numeric_limits<std::size_t>::max())throw std::length_error("text size");data_=new char[n+1];data_[n]='\0';}
public:
 inline static unsigned long long copies=0;
 explicit Text(const char* value=""):Text(value?std::strlen(value):0,Sized{}){if(!value)throw std::invalid_argument("null text");std::memcpy(data_,value,length_+1);}
 Text(const Text& other):Text(other.length_,Sized{}){std::memcpy(data_,other.data_,length_+1);++copies;}
 Text& operator=(const Text& other){if(this!=&other){Text copy{other};std::swap(length_,copy.length_);std::swap(data_,copy.data_);}return *this;}
 ~Text(){delete[] data_;}
 std::size_t size()const{return length_;}
 Text& operator+=(const Text& b){Text joined=*this+b;std::swap(length_,joined.length_);std::swap(data_,joined.data_);return *this;}
 friend Text operator+(const Text& a,const Text& b){
  if(b.length_>std::numeric_limits<std::size_t>::max()-a.length_)throw std::length_error("concatenation overflow");
  Text result{a.length_+b.length_,Sized{}};std::memcpy(result.data_,a.data_,a.length_);std::memcpy(result.data_+a.length_,b.data_,b.length_+1);return result;
 }
 friend bool operator==(const Text& a,const Text& b){return a.length_==b.length_&&std::memcmp(a.data_,b.data_,a.length_)==0;}
 friend bool operator!=(const Text& a,const Text& b){return !(a==b);}
 friend std::ostream& operator<<(std::ostream& out,const Text& t){return out<<t.data_;}
};
#endif
