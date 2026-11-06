#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <cmath>
#include <ostream>
#include <stdexcept>
class Complex {
 double real_,imag_;
public:
 Complex():Complex(0,0){}
 explicit Complex(double real):Complex(real,0){}
 Complex(double real,double imag):real_{real},imag_{imag}{if(!std::isfinite(real)||!std::isfinite(imag))throw std::invalid_argument("nonfinite complex result or operand");}
 double real()const{return real_;}double imag()const{return imag_;}
 double magnitude()const{return std::hypot(real_,imag_);}
 friend Complex operator+(const Complex& a,const Complex& b){return {a.real_+b.real_,a.imag_+b.imag_};}
 friend Complex operator-(const Complex& a,const Complex& b){return {a.real_-b.real_,a.imag_-b.imag_};}
 friend Complex operator*(const Complex& a,const Complex& b){return {a.real_*b.real_-a.imag_*b.imag_,a.real_*b.imag_+a.imag_*b.real_};}
 friend Complex operator/(const Complex& a,const Complex& b){
  if(b.real_==0&&b.imag_==0)throw std::domain_error("division by zero impedance");
  if(std::abs(b.real_)>=std::abs(b.imag_)){double r=b.imag_/b.real_,d=b.real_+b.imag_*r;return {(a.real_+a.imag_*r)/d,(a.imag_-a.real_*r)/d};}
  double r=b.real_/b.imag_,d=b.imag_+b.real_*r;return {(a.real_*r+a.imag_)/d,(a.imag_*r-a.real_)/d};
 }
 friend bool operator==(const Complex& a,const Complex& b){return a.real_==b.real_&&a.imag_==b.imag_;}
 friend std::ostream& operator<<(std::ostream& out,const Complex& z){return out<<z.real_<<(z.imag_<0?" - ":" + ")<<std::abs(z.imag_)<<'j';}
};
#endif
