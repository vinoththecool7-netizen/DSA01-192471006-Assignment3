#include "complex.hpp"
#include "check.hpp"
#include <complex>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <random>
bool near(double a,double b){return std::abs(a-b)<=1e-10*(1+std::max(std::abs(a),std::abs(b)));}
bool near(const Complex& a,const std::complex<double>& b){return near(a.real(),b.real())&&near(a.imag(),b.imag());}
Complex parallel(const Complex& a,const Complex& b){return (a*b)/(a+b);}
int main(){Checks test;std::cout<<std::setprecision(12);
 Complex zero;Complex resistor{100};const double omega=1000,L=.05,C=.00001;Complex inductor{0,omega*L},capacitor{0,-1/(omega*C)};
 const auto series=resistor+inductor+capacitor,combined=parallel(parallel(resistor,inductor),capacitor);
 std::cout<<"omega="<<omega<<" R=100 L="<<L<<" C="<<C<<'\n'<<"series "<<series<<" magnitude="<<series.magnitude()<<'\n'<<"parallel "<<combined<<" magnitude="<<combined.magnitude()<<'\n';
 test.expect("series hand calculation",near(series.real(),100)&&near(series.imag(),-50)&&near(series.magnitude(),std::sqrt(12500.0)));
 test.expect("parallel hand calculation",near(combined.real(),50)&&near(combined.imag(),50)&&near(combined.magnitude(),std::sqrt(5000.0)));
 const std::complex<double> r{100,0},l{0,50},c{0,-100};test.expect("series std complex",near(series,r+l+c));test.expect("parallel std complex",near(combined,1.0/(1.0/r+1.0/l+1.0/c)));
 test.expect("default and real constructors",zero==Complex{0,0}&&resistor==Complex{100,0});
 test.rejects<std::domain_error>("zero division",[&]{(void)(resistor/zero);});test.rejects<std::domain_error>("singular parallel",[&]{(void)parallel(inductor,Complex{0,-50});});
 test.rejects<std::invalid_argument>("nonfinite input",[]{Complex bad{std::numeric_limits<double>::infinity(),0};});
 std::mt19937 rng{192471006};std::uniform_real_distribution<double> distribution{-1000,1000};int mismatches=0;
 for(int i=0;i<1000;++i){const double ar=distribution(rng),ai=distribution(rng),br=distribution(rng),bi=distribution(rng);Complex a{ar,ai},b{br,bi};std::complex<double> sa{ar,ai},sb{br,bi};
  if(!near(a+b,sa+sb)||!near(a-b,sa-sb)||!near(a*b,sa*sb)||!near(a/b,sa/sb))++mismatches;}
 test.expect("4000 arithmetic reference comparisons",mismatches==0);std::cout<<"reference_mismatches="<<mismatches<<" sizeof Complex="<<sizeof(Complex)<<" sizeof std::complex<double>="<<sizeof(std::complex<double>)<<'\n';return test.finish();}
