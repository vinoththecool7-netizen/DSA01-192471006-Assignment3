#ifndef MONEY_HPP
#define MONEY_HPP
#include <cstdint>
#include <iomanip>
#include <istream>
#include <limits>
#include <ostream>
#include <stdexcept>
#include <string>
class Money {
 long long paise_;
 struct PaiseTag{};
 Money(long long p,PaiseTag):paise_{p}{}
 static long long add(long long a,long long b){
  if((b>0&&a>std::numeric_limits<long long>::max()-b)||(b<0&&a<std::numeric_limits<long long>::min()-b))throw std::overflow_error("money addition overflow");return a+b;
 }
 static long long subtract(long long a,long long b){
  if((b>0&&a<std::numeric_limits<long long>::min()+b)||(b<0&&a>std::numeric_limits<long long>::max()+b))throw std::overflow_error("money subtraction overflow");return a-b;
 }
 static bool parse(const std::string& token,long long& result){
  if(token.empty())return false;std::size_t i=0;bool negative=false;
  if(token[i]=='+'||token[i]=='-'){negative=token[i]=='-';if(++i==token.size())return false;}
  const std::uint64_t limit=static_cast<std::uint64_t>(std::numeric_limits<long long>::max())+(negative?1ULL:0ULL);
  std::uint64_t whole=0;std::size_t digits=0;
  while(i<token.size()&&token[i]>='0'&&token[i]<='9'){
   unsigned digit=static_cast<unsigned>(token[i++]-'0');
   if(whole>(limit/100-digit)/10)return false;whole=whole*10+digit;++digits;
  }
  if(!digits)return false;unsigned fraction=0;int count=0;
  if(i<token.size()&&token[i]=='.'){
   ++i;while(i<token.size()&&token[i]>='0'&&token[i]<='9'&&count<2){fraction=fraction*10+static_cast<unsigned>(token[i++]-'0');++count;}
   if(count==0)return false;if(count==1)fraction*=10;
  }
  if(i!=token.size()||whole>limit/100)return false;
  const auto magnitude=whole*100+fraction;if(magnitude>limit)return false;
  if(negative){result=magnitude==limit?std::numeric_limits<long long>::min():-static_cast<long long>(magnitude);}
  else result=static_cast<long long>(magnitude);return true;
 }
public:
 explicit Money(long long rupees=0,int p=0):paise_{0}{
  if(p<-99||p>99)throw std::invalid_argument("paise part outside -99..99");
  if(rupees>std::numeric_limits<long long>::max()/100||rupees<std::numeric_limits<long long>::min()/100)throw std::overflow_error("rupees overflow");
  paise_=add(rupees*100,p);
 }
 static Money fromPaise(long long p){return Money{p,PaiseTag{}};}
 long long paise()const{return paise_;}
 Money& operator+=(const Money& b){paise_=add(paise_,b.paise_);return *this;}
 friend Money operator+(Money a,const Money& b){a+=b;return a;}
 friend Money operator-(const Money& a,const Money& b){return fromPaise(subtract(a.paise_,b.paise_));}
 friend bool operator==(const Money& a,const Money& b){return a.paise_==b.paise_;}
 friend bool operator<(const Money& a,const Money& b){return a.paise_<b.paise_;}
 friend std::ostream& operator<<(std::ostream& out,const Money& m){
  const auto magnitude=m.paise_<0?std::uint64_t{0}-static_cast<std::uint64_t>(m.paise_):static_cast<std::uint64_t>(m.paise_);
  const auto cents=magnitude%100;const auto value=std::string(m.paise_<0?"-":"")+std::to_string(magnitude/100)+'.'+(cents<10?"0":"")+std::to_string(cents);
  return out<<"Rs "<<value;
 }
 friend std::istream& operator>>(std::istream& in,Money& m){std::string token;if(!(in>>token))return in;long long p=0;if(!parse(token,p))in.setstate(std::ios::failbit);else m.paise_=p;return in;}
};
#endif
